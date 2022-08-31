﻿using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Data;
using System.Text;
using System.Linq.Expressions;
using RaGlib;
using RaGlib.Core;
using RaGlib.Grammars;

namespace RaGsystems {

  class Program {

    static void Dialog() {
      Console.WriteLine("Наберите соответствующий номер лабораторной или курсовой и нажмите <Enter>");
      Console.WriteLine("Лабораторные работы:");
      Console.WriteLine("1.1  Лемма о накачке рег., КС языки");
      Console.WriteLine("1.2  Составные автоматы");
      Console.WriteLine("2    Спроектировать конечный автомат DFS (lab 2)");
      Console.WriteLine("2.1  Алгоритм построения КА по заданной грамматике");
      Console.WriteLine("3    НДКА ");
      Console.WriteLine("3.1  Convert NDFS to DFS (lab 3)");
      Console.WriteLine("3.2  Convert NDFS to DFS (lab 3) example");
      Console.WriteLine("");
      Console.WriteLine("4.0  Генератор заданий Grammar_generator");
      Console.WriteLine("");
      Console.WriteLine("4.1  Приведение граматики к нормальной форме CFGrammar (lab 4 - 6)");
      Console.WriteLine("6.1  Grammar in Greibach normal form");
      Console.WriteLine("6.2  Grammar in Chomsky normal form");
      Console.WriteLine("7    Алгоритм построения МП автомата по приведенной КС-грамматики PDA (lab 7-8)");
      Console.WriteLine("7.1 КС-грамматика в МП-автомат пример 1");
      Console.WriteLine("7.2 КС-грамматика в МП-автомат пример 2");
      Console.WriteLine("7.3 МП - автомат пример 3");
      Console.WriteLine("7.4 НДМП - автомат пример 4");
      Console.WriteLine("7.5 МП - автомат пример 5");

      Console.WriteLine("");
      Console.WriteLine("9.1  Для LL(1) анализатора построить управляющую таблицу M.\n"+
          "     Аналитически написать такты работы LL(1) анализатора для выведенной цепочки.");
      Console.WriteLine("9.2  Для LL(1) анализатора построить управляющую таблицу M.\n"+
          "     Аналитически написать такты работы LL(1) анализатора для выведенной цепочки с подробным разбором.");
      Console.WriteLine("");
      Console.WriteLine("14   Построить каноническую форму множества ситуаций.\n"+
          "     Построить управляющую таблицу для функции перехода  g(х) и действий f(u)");
      Console.WriteLine("16.1 LR(0) using g(X), f(a)");
      Console.WriteLine("16.2 LR(0) using g(X), f(a) example");
      Console.WriteLine("16.3 LR(1) using g(X), f(a)");
      Console.WriteLine("16.4 LR(1) using g(X), f(a) example ");
      Console.WriteLine("");
      Console.WriteLine("Курсовые проеты: I");
      Console.WriteLine("I1   Терия перевода SDTSchemata");
      Console.WriteLine("I2   Преобразование КС-грамматики в транслирующую с операционными символами");
      Console.WriteLine("I3   Grammar to AT-Grammar");
      Console.WriteLine("I4   AT-Grammar");
      Console.WriteLine("I5   AT-Grammar for python vars types");
      Console.WriteLine("I6   AT-grammar for translating for C ++ into Python");
      Console.WriteLine("");
      Console.WriteLine("I7   Chain Translation example");
      Console.WriteLine("I8   L-attribute translation");
      Console.WriteLine("I9   Parse Tree translation");
    }

    static void Main() {
      // "ε", "\u03B5"  Greek alphabet
      Console.OutputEncoding=System.Text.Encoding.Unicode;  

      for (;;) {
        Dialog();
        switch (Console.ReadLine()) {
          case "1.1": // Pumping lemma

            var check_pumping = new Pumping();
            check_pumping.Dialog();

            break;
          case "1.2": // Compound automata  Lab 1.
            FSAutomate[] automats = new FSAutomate[] {
                new FSAutomate(
                        new List<Symbol>() { "S01", "A1", "B1", "C1", "qf1" },
                        new List<Symbol>() { "0" },
                        new List<Symbol>() { "qf1" },
                        "S01"
                    ),
                new FSAutomate(
                        new List<Symbol>() { "S02", "A2", "B2", "C2", "D2", "qf2" },
                        new List<Symbol>() { "0", "1", "(", ")", "+" },
                        new List<Symbol>() { "qf2" },
                        "S02"
                    ),
                new FSAutomate(
                        new List<Symbol>() { "S03", "qf3" },
                        new List<Symbol>() { "0", "1" },
                        new List<Symbol>() { "qf3" },
                        "S03"
                    ),
            };
            //deltas
            automats[0].AddRule("S01","0","A1");
            automats[0].AddRule("A1","0","B1");
            automats[0].AddRule("B1","0","C1");
            automats[0].AddRule("C1","0","A1");
            automats[0].AddRule("C1","0","qf1");

            automats[1].AddRule("S02","(","A2");
            automats[1].AddRule("A2","0","B2");
            automats[1].AddRule("B2","+","C2");
            automats[1].AddRule("C2","1","D2");
            automats[1].AddRule("D2",")","qf2");

            automats[2].AddRule("S03","0","S03");
            automats[2].AddRule("S03","0","qf3");
            automats[2].AddRule("S03","1","S03");
            automats[2].AddRule("S03","1","qf3");
            automats[2].AddRule("S03","","qf3");

            var dka1 = new FSAutomate(); // правильно
            dka1.BuildDeltaDKAutomate(automats[0]); // правильно
            var dka2 = new FSAutomate();
            dka2.BuildDeltaDKAutomate(automats[1]);
            var dka3 = new FSAutomate();
            dka3.BuildDeltaDKAutomate(automats[2]);

            // правильно
            var automats1 = new FSAutomate[] { dka1, dka2, dka3, };
            //merge
            var merged12 = Compound_FSAutomate.Merge2(dka1,dka2); // неправильно
            var merged23 = Compound_FSAutomate.Merge2(dka2,dka3);
            var merged123 = Compound_FSAutomate.Merge(automats1);
            var union12 = Compound_FSAutomate.Union2(dka1,dka2);
            var union1 = new FSAutomate();
            union1.BuildDeltaDKAutomate(union12);
            var union123 = Compound_FSAutomate.Union(automats1);
            var union2 = new FSAutomate();
            union2.BuildDeltaDKAutomate(union123);

            var exectionOrder = new FSAutomate[] { union1,union2,merged12,merged23,merged123 };
            string[] names = { "объединение КА1, КА2","объединение КА1, КА2, КА3","КА1+КА2","КА2+КА3","КА1+КА2+КА3" };

            Console.WriteLine();

            Console.WriteLine("Были построены составные автоматы:");
            Console.WriteLine("1. объединение КА1, КА2;");
            Console.WriteLine("2. объединение КА1, КА2, КА3;");
            Console.WriteLine("3. КА1 +КА2;");
            Console.WriteLine("4. КА2+КА3;");
            Console.WriteLine("5. КА1+КА2+КА3;");

            Console.WriteLine();
            Console.WriteLine("Примеры цепочек для постоенных составных автоматов 1, 2, 3, 4, 5: ");
            Console.WriteLine("0, 1, 01, 0000, 0000000, (0+1), 0000(0+1), 0000(0+1)0, 0000(0+1)1");
            for (; ; ) {
              Console.WriteLine();
              Console.WriteLine("Введите цепочку (или выйти stop):");
              string s = Console.ReadLine();
              Console.WriteLine();
              if (s=="stop") break;

              for (int i = 0; i<exectionOrder.Length; i++) {
                if (exectionOrder[i].Execute_FSA(s)) {
                  Console.WriteLine("Автомат "+names[i]+" распознал цепочку "+s);
                  break;
                } else {
                  Console.WriteLine("Автомат "+names[i]+" не распознал цепочку "+s);
                  if (i==exectionOrder.Length-1)
                    Console.WriteLine("Данная цепочка не была распознана");
                  //  Console.ReadLine();
                }
              }
            }
            break;
          case "2":
            var ka6 = new FSAutomate(new List<Symbol>() { "S0", "A", "B", "C", "D", "E", "F", "G", "H", "I", "qf" },
            new List<Symbol>() { "p", "o", "#", " ", "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" },
            new List<Symbol>() { "qf" }, "S0");
            ka6.AddRule("S0","p","A");
            ka6.AddRule("A","o","B");
            ka6.AddRule("B","#","C");
            ka6.AddRule("B", "-", "C");
            ka6.AddRule("B", " ", "C");
            ka6.AddRule("C","0","D"); ka6.AddRule("C", "1", "D"); ka6.AddRule("C", "2", "D"); ka6.AddRule("C", "3", "D"); ka6.AddRule("C", "4", "D"); ka6.AddRule("C", "5", "D"); ka6.AddRule("C", "6", "D"); ka6.AddRule("C", "7", "D"); ka6.AddRule("C", "8", "D"); ka6.AddRule("C", "9", "D");
            ka6.AddRule("D","0","E"); ka6.AddRule("D", "1", "E"); ka6.AddRule("D", "2", "E"); ka6.AddRule("D", "3", "E"); ka6.AddRule("D", "4", "E"); ka6.AddRule("D", "5", "E"); ka6.AddRule("D", "6", "E"); ka6.AddRule("D", "7", "E"); ka6.AddRule("D", "8", "E"); ka6.AddRule("D", "9", "E");
            ka6.AddRule("E","-","F");
            ka6.AddRule("E", " ", "F");
            ka6.AddRule("F","0","G"); ka6.AddRule("F", "1", "G"); ka6.AddRule("F", "2", "G"); ka6.AddRule("F", "3", "G"); ka6.AddRule("F", "4", "G"); ka6.AddRule("F", "5", "G"); ka6.AddRule("F", "6", "E"); ka6.AddRule("F", "7", "E"); ka6.AddRule("F", "8", "E"); ka6.AddRule("F", "9", "E");
            ka6.AddRule("G","0","H"); ka6.AddRule("G", "1", "H"); ka6.AddRule("G", "2", "H"); ka6.AddRule("G", "3", "H"); ka6.AddRule("G", "4", "H"); ka6.AddRule("G", "5", "H"); ka6.AddRule("G", "6", "H"); ka6.AddRule("G", "7", "H"); ka6.AddRule("G", "8", "H"); ka6.AddRule("G", "9", "H");
            ka6.AddRule("H","0", "I"); ka6.AddRule("H", "1", "I"); ka6.AddRule("H", "2", "I"); ka6.AddRule("H", "3", "I"); ka6.AddRule("H", "4", "I"); ka6.AddRule("H", "5", "I"); ka6.AddRule("H", "6", "I"); ka6.AddRule("H", "7", "I"); ka6.AddRule("H", "8", "I"); ka6.AddRule("H", "9", "I");
            ka6.AddRule("I","0","qf"); ka6.AddRule("I", "1", "qf"); ka6.AddRule("I", "2", "qf"); ka6.AddRule("I", "3", "qf"); ka6.AddRule("I", "4", "qf"); ka6.AddRule("I", "5", "qf"); ka6.AddRule("I", "6", "qf"); ka6.AddRule("I", "7", "qf"); ka6.AddRule("I", "8", "qf"); ka6.AddRule("I", "9", "qf");

            Console.WriteLine("Enter line to execute :");
            ka6.Execute(Console.ReadLine());
            break;

          case "2.1":
            var Gram = new Grammar(new List<Symbol>() { "0","1" },
            new List<Symbol>() { "S0","A","B" },
            "S0");
            Gram.AddRule("S0",new List<Symbol>() { "0" });
            Gram.AddRule("S0",new List<Symbol>() { "0","A" });
            Gram.AddRule("A",new List<Symbol>() { "1","B" });
            Gram.AddRule("B",new List<Symbol>() { "0" });
            Gram.AddRule("B",new List<Symbol>() { "0","A" });

            // From Automaton Grammar to State Machine(KA)
            var KA = Gram.Transform();
            KA.DebugAuto();
            break;
          case "3.1":
            var ndfsa = new FSAutomate(new List<Symbol>() { "S0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","qf" },
                                       new List<Symbol>() { "1","0","+","2" },
                                       new List<Symbol>() { "qf" },
                                       "S0");
            ndfsa.AddRule("S0","1","1");          //W1
            ndfsa.AddRule("1","0","2");
            ndfsa.AddRule("2","+","3");

            ndfsa.AddRule("3","","4");            //W2
            ndfsa.AddRule("4","","5");
            ndfsa.AddRule("4","","7");
            ndfsa.AddRule("4","","9");
            ndfsa.AddRule("5","1","6");
            ndfsa.AddRule("7","2","8");
            ndfsa.AddRule("6","","9");
            ndfsa.AddRule("8","","9");
            ndfsa.AddRule("9","","4");
            ndfsa.AddRule("9","","10");

            ndfsa.AddRule("10","1","11");          //W3
            ndfsa.AddRule("11","0","12");
            ndfsa.AddRule("12","","13");
            ndfsa.AddRule("13","","9");
            ndfsa.AddRule("13","","14");

            ndfsa.AddRule("14","","15");           //W4
            ndfsa.AddRule("14","","17");
            ndfsa.AddRule("15","0","16");
            ndfsa.AddRule("17","1","18");
            ndfsa.AddRule("16","","19");
            ndfsa.AddRule("18","","19");
            ndfsa.AddRule("19","","14");
            ndfsa.AddRule("19","","20");
            ndfsa.AddRule("20","","15");
            ndfsa.AddRule("14","","qf");
            ndfsa.AddRule("20","","qf");

            var dka = new FSAutomate();
            dka.BuildDeltaDKAutomate(ndfsa);
            dka.DebugAuto();
            Console.WriteLine("Enter line to execute :");
            dka.Execute(Console.ReadLine());
            break;

          case "3.2":
            var example = new FSAutomate(new List<Symbol>() { "S0","1","2","3","4","5","6","7","8","9","qf" },
                                         new List<Symbol>() { "a","b" },
                                         new List<Symbol>() { "qf" },
                                         "S0");
            example.AddRule("S0","","1");
            example.AddRule("S0","","7");
            example.AddRule("1","","2");
            example.AddRule("1","","4");
            example.AddRule("2","a","3");
            example.AddRule("4","b","5");
            example.AddRule("3","","6");
            example.AddRule("5","","6");
            example.AddRule("6","","1");
            example.AddRule("6","","7");
            example.AddRule("7","a","8");
            example.AddRule("8","b","9");
            example.AddRule("9","b","qf");

            var dkaEX = new FSAutomate();
            dkaEX.BuildDeltaDKAutomate(example);
            dkaEX.DebugAuto();
            Console.WriteLine("Enter line to execute :");
            dkaEX.Execute(Console.ReadLine());
            break;

          case "4.0": // Assignment 
            var generator = new Assignment.GrammarGenerator();
            var grammar = generator.GenerateGrammar();
            Console.ReadKey();
            break;
          case "4.1":
            var regGr = new Grammar(new List<Symbol>() { "b","c" },
                                    new List<Symbol>() { "S","A","B","C" },
                                    "S");

            regGr.AddRule("S",new List<Symbol>() { "c","A","B" });
            regGr.AddRule("S",new List<Symbol>() { "b" });
            regGr.AddRule("B",new List<Symbol>() { "c","B" });
            regGr.AddRule("B",new List<Symbol>() { "b" });
            regGr.AddRule("A",new List<Symbol>() { "Ab" });
            regGr.AddRule("A",new List<Symbol>() { "B" });
            regGr.AddRule("A",new List<Symbol>() { "" });
            Console.WriteLine("Grammar:");
            regGr.Debug("T",regGr.T);
            regGr.Debug("T",regGr.V);
            regGr.DebugPrules();

            Grammar G1 = regGr.EpsDelete();
            G1.DebugPrules();

            Grammar G2 = G1.unUsefulDelete();
            G2.DebugPrules();

            Grammar G3 = G2.ChainRuleDelete();
            G3.DebugPrules();

            Grammar G4 = G3.LeftRecursDelete_new6();
            G4.DebugPrules();
            // G4 - приведенная грамматика

            Console.WriteLine("--------------------------------------------");
            Console.WriteLine("Normal Grammatic:");
            G4.Debug("T",G4.T);
            G4.Debug("V",G4.V);
            G4.DebugPrules();
            Console.Write("Start symbol: ");
            Console.WriteLine(G4.S0+"\n");
            break;
          case "6.1": {
              var g = new Grammar(new List<Symbol>() { "+","*","(",")","i" },
                                    new List<Symbol>() { "S","F","L","K" },
                                    "S");
              g.AddRule("S",new List<Symbol>() { "S","+","F" });
              g.AddRule("S",new List<Symbol>() { "F" });
              g.AddRule("F",new List<Symbol>() { "F","*","L" });
              g.AddRule("F",new List<Symbol>() { "L" });
              g.AddRule("L",new List<Symbol>() { "(","S",")" });
              g.AddRule("L",new List<Symbol>() { "i" });
              g.AddRule("K",new List<Symbol>() { "i" });

              Console.WriteLine("Grammar:");
              g.Debug("T",g.T);
              g.Debug("T",g.V);
              g.DebugPrules();

              var g1 = g.DeleteLongRules();

              var g2 = g1.unUsefulDelete();

              var g3 = g2.EpsDelete();

              var g4 = g3.DeleteS0Rules();

              var g5 = g4.ChainRuleDelete();

              var g6 = g5.DeleteTermRules();
              g6.DebugPrules();

              var g7 = g6.LeftRecursDelete_new6();
              g7.DebugPrules();
              g7.Debug("V",g7.V);

              var g9 = g7.TransformGrForm();

              Console.WriteLine("--------------------------------------------");
              Console.WriteLine("Greibach normal form:");
              g9.Debug("T",g9.T);
              g9.Debug("V",g9.V);
              g9.DebugPrules();
              Console.Write("Start symbol: ");
              Console.WriteLine(g9.S0+"\n");
              break;
          } 
          case "6.2": {  // Algorithms приведенная грамматика G            
              var g = new Grammar(new List<Symbol>() { "+","*","(",")","i" },
                                   new List<Symbol>() { "S","F","L","K" },
                                   "S");
              g.AddRule("S",new List<Symbol>() { "S","+","F" });
              g.AddRule("S",new List<Symbol>() { "F" });
              g.AddRule("F",new List<Symbol>() { "F","*","L" });
              g.AddRule("F",new List<Symbol>() { "L" });
              g.AddRule("L",new List<Symbol>() { "(","S",")" });
              g.AddRule("L",new List<Symbol>() { "i" });
              g.AddRule("K",new List<Symbol>() { "i" });

              Console.WriteLine("Grammar:");
              g.Debug("T",g.T);
              g.Debug("T",g.V);
              g.DebugPrules();

              var g1 = g.DeleteLongRules();
              g1.Debug("T",g1.T);
              g1.Debug("V",g1.V);
              g1.DebugPrules();

              var g2 = g1.unUsefulDelete();
              g2.DebugPrules();

              var g3 = g2.EpsDelete();
              g3.DebugPrules();

              var g4 = g3.DeleteS0Rules();
              g4.Debug("T",g4.T);
              g4.Debug("V",g4.V);
              g4.DebugPrules();
              Console.Write("Start symbol: ");
              Console.WriteLine(g4.S0+"\n");

              var g5 = g4.ChainRuleDelete();
              g5.DebugPrules();

              var g6 = g5.DeleteTermRules();

              Console.WriteLine("--------------------------------------------");
              Console.WriteLine("Chomsky normal form:");
              g6.Debug("T",g6.T);
              g6.Debug("V",g6.V);
              g6.DebugPrules();
              Console.Write("Start symbol: ");
              Console.WriteLine(g6.S0+"\n");              
              break;
          }
          case "7": { // Algorithm Grammar to PDA 
            var CFGrammar = new Grammar(new List<Symbol>() { "b","c" },
                                        new List<Symbol>() { "S","A","B","D" },
                                        "S");

              CFGrammar.AddRule("S",new List<Symbol>() { "b" });
              CFGrammar.AddRule("S",new List<Symbol>() { "c","A","B" });
              CFGrammar.AddRule("S",new List<Symbol>() { "c","B" });

              CFGrammar.AddRule("A",new List<Symbol>() { "b","D" });
              CFGrammar.AddRule("A",new List<Symbol>() { "b" });
              CFGrammar.AddRule("A",new List<Symbol>() { "c","B","D" });
              CFGrammar.AddRule("A",new List<Symbol>() { "c","B" });

              CFGrammar.AddRule("D",new List<Symbol>() { "b" });
              CFGrammar.AddRule("D",new List<Symbol>() { "b","D" });

              CFGrammar.AddRule("B",new List<Symbol>() { "b" });
              CFGrammar.AddRule("B",new List<Symbol>() { "cB" });

              Console.Write("Debug KC-Grammar ");
              CFGrammar.DebugPrules();

              var pda = new PDA(CFGrammar);
              pda.Debug();

              Console.WriteLine("\nEnter the line :");
              Console.WriteLine(pda.Execute(Console.ReadLine()).ToString());
              break;
          }
          case "7.1": { // !! Algorithm Grammar to PDA {aabb, aaaabbbb}
              // see 7.2 PDA  
              var cfgr = new Grammar(new List<Symbol>() { "a","b" },
                                     new List<Symbol>() { "S","A","B" },
                                     "S");

              cfgr.AddRule("S",new List<Symbol>() { "a","A","b" }); // S -> aAb
              cfgr.AddRule("A",new List<Symbol>() { "a","B","b" }); // A -> aBb
              cfgr.AddRule("B",new List<Symbol>() { "a","b" }); // B -> ab
              Console.Write("Debug KC-Grammar ");
              cfgr.DebugPrules();

                var pda = new PDA(new List<Symbol>() { "q0", "q1","q2","qf"},
                                                       new List<Symbol>() { "a","b"},
                                                       new List<Symbol>() {"z0","a","b","S","A","B"},
                                                       "q0",
                                                       "S",
                                                       new List<Symbol>() {"qf"});
                pda.addDeltaRule("q0", "ε", "S",new List<Symbol>() { "q1" },new List<Symbol>() { "a","A","b" }); //δ(q0,ε,S) = (a,A,b)
                pda.addDeltaRule("q", "ε", "A",new List<Symbol>() { "q" },new List<Symbol>() {"a","B","b" }); //δ(q,ε,A) = (a,B,b)
                pda.addDeltaRule("q", "ε", "B",new List<Symbol>() { "q" },new List<Symbol>() { "a","b" }); //δ(q,ε,B) = (a,b)
                pda.addDeltaRule("q","a","a",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,a,a) = (ε)
                pda.addDeltaRule("q","a","b",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,a,b) = (ε)
                pda.addDeltaRule("q","b","b",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,b,b) = (ε)
                pda.addDeltaRule("q","b","a",new List<Symbol>() { "qf" },new List<Symbol>() { "ε" }); //δ(q,b,a) = (ε)


                            pda.Debug();

                Console.WriteLine("\nВведите строку, пример :"); // aaabbb
                Console.WriteLine(pda.Execute(Console.ReadLine()).ToString());
              
            
              break;
          }
          case "7.2": { // !! Algorithm Grammar to PDA {aabb, aaaabbbb}
              // see 7.2 PDA
                //
              // example expression  i = i  
              var cfgr1 = new Grammar(new List<Symbol>() { "i","=" },
                                      new List<Symbol>() { "S","F","L" },
                                      "S");

              cfgr1.AddRule("S",new List<Symbol>() { "F","=","L" }); //S -> F=L
              cfgr1.AddRule("F",new List<Symbol>() { "i" });    //F -> i
              cfgr1.AddRule("L",new List<Symbol>() { "F" });    //L -> F
              Console.Write("Debug KC-Grammar ");
              cfgr1.DebugPrules();
                var pda = new PDA(new List<Symbol>() { "q0","q1","q2","qf" },
                                                       new List<Symbol>() { "i","="},
                                                       new List<Symbol>() {"z0","i"},
                                                       "q0",
                                                       "z0",
                                                       new List<Symbol>() {"qf"});
                pda.addDeltaRule("q0", "i", "z0",new List<Symbol>() { "q1" },new List<Symbol>() { "i", "z0" });//δ(q0,i,z0) = (i,z0)
                pda.addDeltaRule("q", "=", "i",new List<Symbol>() { "q" },new List<Symbol>() { "ε" });  //δ(q,=,i) = (ε)
                pda.addDeltaRule("q", "i", "i",new List<Symbol>() { "q" },new List<Symbol>() { "i", "i"}); //δ(q,i,i) = (i,i)
                pda.addDeltaRule("q", "ε", "i",new List<Symbol>() { "qf" },new List<Symbol>() { "ε" });   //δ(q,ε,i) = (ε)

                            pda.Debug();

                Console.WriteLine("\nВведите строку, пример :"); // i=i
                Console.WriteLine(pda.Execute(Console.ReadLine()).ToString());
              break;
          }
          case "7.3": { //МП - автоматы  {ab, aaaabbbb}         
              var pda = new PDA(new List<Symbol>() { "q0","q1","q2","qf" },
                                 new List<Symbol>() { "a","b" },
                                 new List<Symbol>() { "z0","a" },
                                 "q0",
                                 "z0",
                                 new List<Symbol>() { "qf" });
              pda.addDeltaRule("q0","a","z0",new List<Symbol>() { "q1"},new List<Symbol>() { "a","z0"}); //δ(q0,a,z0) = (a, z0)
              pda.addDeltaRule("q","a","a",  new List<Symbol>() { "q" },new List<Symbol>() { "a","a" }); //δ(q,a,a) = (a,a)
              pda.addDeltaRule("q","b","a",  new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,b,a) = (ε)
              pda.addDeltaRule("q","ε","z0",new List<Symbol>() { "qf" },new List<Symbol>() { "ε" });  //δ(q,ε,z0) = (ε)

                            pda.Debug();
              // Console.ReadKey();
              //              Console.WriteLine("\nEnter the line :");
              //              Console.WriteLine(pda.Execute(Console.ReadLine()).ToString());
              Console.WriteLine("Execute example: ab");
              Console.WriteLine(pda.Execute("ab"));
              //pda.Execute("aaabbb");
              break;
          }
          case "7.4": {// NPDA  automata  (v + v )
            var npda = new PDA(
                    new List<Symbol>() { "q","qf" },
                    new List<Symbol>() { "v","+","*","(",")" },
                    new List<Symbol>() { "v", "+", "*", "(", ")", "S", "F", "L"},
                    "q0",
                    "S",
                    new List<Symbol>() { "qf" });

            // S -> S + F | F
            // F -> F * L || L
            // L -> v || (S)
            npda.addDeltaRule("q","v","v",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,v,v) = (ε)
            npda.addDeltaRule("q","+","+",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,+,+) = (ε)
            npda.addDeltaRule("q","*","*",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,*,*) = (ε)
            npda.addDeltaRule("q","(","(",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,(,() = (ε)
            npda.addDeltaRule("q",")",")",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,),) ) = (ε)

            npda.addDeltaRule("q", "+", "*",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,+,*) = (ε)
            npda.addDeltaRule("q", "ε", "*",new List<Symbol>() { "qf" },new List<Symbol>() { "ε" }); //δ(q,ε,*) = (ε)
            npda.addDeltaRule("q", "(", "v",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,(,v) = (ε)
            npda.addDeltaRule("q", "v", "*",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,v,*) = (ε)
            npda.addDeltaRule("q", "+", "v",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,+,v) = (ε)
            npda.addDeltaRule("q", ")", "v",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,),v) = (ε)

            npda.addDeltaRule("q", "ε", "S",new List<Symbol>() { "q" },new List<Symbol>() { "F" }); //δ(q,ε,S) = (F)
            npda.addDeltaRule("q", "ε", "F",new List<Symbol>() { "q" },new List<Symbol>() { "F","*","L" }); //δ(q,ε,F) = (F,*,L)
            npda.addDeltaRule("q", "ε", "F",new List<Symbol>() { "q" },new List<Symbol>() { "L" }); //δ(q,ε,F) = (L)
            npda.addDeltaRule("q", "ε", "L",new List<Symbol>() { "q" },new List<Symbol>() { "v" }); //δ(q,ε,L) = (v)
            npda.addDeltaRule("q", "ε", "L",new List<Symbol>() { "q" },new List<Symbol>() { "(","S",")" }); //δ(q,ε,L) = ((,S,))

                            npda.Debug();
            Console.WriteLine("\nEnter the line :");
                            // Example: v+v
                            //          v*(v+v)
            Console.WriteLine(npda.Execute(Console.ReadLine()).ToString());

            break;
          }
          case "7.5" : { // i @ i
                            // S -> F@L
                            // F -> i
                            // L -> i
              var pda = new PDA(new List<Symbol>() { "q0","q1","q2","qf" },
                                 new List<Symbol>() { "i","@" },
                                 new List<Symbol>() { "z0","i", },
                                 "q0",
                                 "z0",
                                 new List<Symbol>() { "qf" });
              pda.addDeltaRule("q0", "i", "z0",new List<Symbol>() { "q1" },new List<Symbol>() { "i", "z0" }); //δ(q0,i,z0) = (i,z0)
              pda.addDeltaRule("q", "@", "i",new List<Symbol>() { "q" },new List<Symbol>() { "ε" }); //δ(q,@,i) = (ε)
              pda.addDeltaRule("q", "i", "i",new List<Symbol>() { "q" },new List<Symbol>() { "i", "i"}); //δ(q,i,i) = (i, i)
              pda.addDeltaRule("q", "ε", "i",new List<Symbol>() { "qf" },new List<Symbol>() { "ε" }); //δ(q,ε,i) = (ε)
                            pda.Debug();
              Console.WriteLine("Example: i@i\n");
              Console.WriteLine(pda.Execute("i@i"));
              break;
                      
          }
          case "9.1": { // LL Разбор
              var LL = new Grammar(new List<Symbol>() { "i","(",")","+","*" },
                                   new List<Symbol>() { "S","F","L" },
                                   "S");

              LL.AddRule("S",new List<Symbol>() { "(","F","+","L",")" });
              LL.AddRule("F",new List<Symbol>() { "*","L" });
              LL.AddRule("F",new List<Symbol>() { "i" });
              LL.AddRule("L",new List<Symbol>() { "F" });

              var parser = new LLParser(LL);
              Console.WriteLine("Пример вводимых строк: (i+i), (i+*i)");
              Console.WriteLine("Введите строку: ");
              string stringChain = Console.ReadLine();

              var chain = new List<Symbol> { };              
              foreach (var x in stringChain)
                chain.Add(new Symbol(x.ToString()));
              if (parser.Parse(chain)) {
                Console.WriteLine("Допуск. Цепочка символов = L(G).");
                Console.WriteLine(parser.OutputConfigure);
              } else {
                Console.WriteLine("Не допуск. Цепочка символов не = L(G).");
              }
              break;
          }
          case "9.2": { // LL Разбор
              var LL1 = new Grammar(new List<Symbol>() { "i","&","^","(",")","" },
                                    new List<Symbol>() { "S","S'","F" },
                                    "S");

              LL1.AddRule("S",new List<Symbol>() { "(","S'" });
              LL1.AddRule("S'",new List<Symbol>() { "F","^","F",")" });
              LL1.AddRule("S'",new List<Symbol>() { "S",")" });
              LL1.AddRule("F",new List<Symbol>() { "&","F" });
              LL1.AddRule("F",new List<Symbol>() { "i" });

              var parser1 = new LLParser(LL1);
              Console.WriteLine("Введите строку: ");
              string stringChain = Console.ReadLine();

              var chain = new List<Symbol> { };              
              foreach (var x in stringChain)
                chain.Add(new Symbol(x.ToString()));
              if (parser1.Parse1(chain)) {
                Console.WriteLine("Допуск. Цепочка символов = L(G).");
                Console.WriteLine(parser1.OutputConfigure);
              } else {
                Console.WriteLine("Не допуск. Цепочка символов не = L(G).");
              }
              break;
          }
          case "14":
            var LR0Grammar = new SLRGrammar(new List<Symbol>() { "i","j","&","^","(",")" },
                                            new List<Symbol>() { "S","F","L" },
                                            new List<Production>(),
                                            "S");

            LR0Grammar.AddRule("S",new List<Symbol>() { "F","^","L" });
            LR0Grammar.AddRule("S",new List<Symbol>() { "(","S",")" });
            LR0Grammar.AddRule("F",new List<Symbol>() { "&","L" });
            LR0Grammar.AddRule("F",new List<Symbol>() { "i" });
            LR0Grammar.AddRule("L",new List<Symbol>() { "j" });

            LR0Grammar.Construct();
            LR0Grammar.Inference();
            break;
          case "16.1": {
              var parser = new MyLRParser();
              parser.ReadGrammar();
              parser.Execute();
              break;
          }
          case "16.2": {
              var parser = new MyLRParser();
              Console.WriteLine("Пример ввода продукций:");
              parser.Example();
              parser.Execute();
              break;
          }
          case "16.3": {
              var parser = new MyLRParser();
              parser.ReadGrammar();
              parser.Execute_LR1();
              break;
          }
          case "16.4": {
              var parser = new MyLRParser();
              Console.WriteLine("Пример ввода продукций:");
              parser.Example_LR1();
              parser.Execute_LR1();
              break;
          }
          case "I1": // SDT
            try {
              var sdt = new mySDTSchemata(new List<Symbol>() { "S","A" },
                        new List<Symbol>() { "0","1" },
                        new List<Symbol>() { "a","b" },
                        "S");

              sdt.addRule(new Symbol("S"),
                      new List<Symbol>() { "0","A","S" },
                      new List<Symbol>() { "S","A","a" });
              sdt.addRule(new Symbol("A"),
                      new List<Symbol>() { "0","S","A" },
                      new List<Symbol>() { "A","S","a" });
              sdt.addRule(new Symbol("S"),
                      new List<Symbol>() { "1" },
                      new List<Symbol>() { "b" });
              sdt.addRule(new Symbol("A"),
                      new List<Symbol>() { "1" },
                      new List<Symbol>() { "b" });

              Console.Write("\nDebug SDTranslator:");
              sdt.debugSDTS();

              sdt.Translate(new List<Symbol>() { "0","0","1","0","1","1","1" });

            } catch (Exception e) {
              Console.WriteLine($"\nОшибка: {e.Message}");
            }

            // Homomorphism
            try {
              var h_table = new myHTable(new List<Symbol>() { "0","1" },
                                          new List<Symbol>() { "1","0" });

              Console.WriteLine("\nDebug Homomorphism:");
              h_table.debugHTable();

              Console.WriteLine("\nInput chain:");
              var r = new List<Symbol>() { "0","1","0","0","1","1" };
              Console.WriteLine(Utility.convert(r));
              Console.WriteLine("\nTranslation:");
              Console.WriteLine(h_table.h(r));
            } catch (Exception e) {
              Console.WriteLine($"\nОшибка: {e.Message}");
            }

            try {
              var sdt = new mySDTSchemata(new List<Symbol>() { "S" },
                                          new List<Symbol>() { "+","i" },
                                          new List<Symbol>() { "+","i" },
                                          "S");

              sdt.addRule(new Symbol("S"),
                              new List<Symbol>() { "+","S_1","S_2" },
                              new List<Symbol>() { "S_2","+","S_1" });

              sdt.addRule(new Symbol("S"),
                              new List<Symbol>() { "i" },
                              new List<Symbol>() { "i" });

              Console.Write("\nDebug SDTranslator:");
              sdt.debugSDTS();

              sdt.Translate(new List<Symbol>() { "+","+","+","i","i","i","i" });

            } catch (Exception e) {
              Console.WriteLine($"\nОшибка: {e.Message}");
            }
            break;

          case "I2":
            var inputGrammar = new Grammar(new List<Symbol>() { "i","+","*","(",")" },
                                           new List<Symbol>() { "E","T","P" },
                                           new List<Production>(),
                                           "E");

            inputGrammar.AddRule("E",new List<Symbol> { "T","+","E" });
            inputGrammar.AddRule("E",new List<Symbol> { "T" });
            inputGrammar.AddRule("T",new List<Symbol> { "P","*","T" });
            inputGrammar.AddRule("T",new List<Symbol> { "P" });
            inputGrammar.AddRule("P",new List<Symbol> { "i" });
            inputGrammar.AddRule("P",new List<Symbol> { "(","E",")" });

            var converter = new ConverterInTransGrammar(new List<Symbol>() { "i","+","*","(",")" },
                                                        new List<Symbol>() { "E","T","P" },
                                                        new List<Production>(),
                                                        "E");

            converter.AddRule("E",new List<Symbol> { "T","+","E" });
            converter.AddRule("E",new List<Symbol> { "T" });
            converter.AddRule("T",new List<Symbol> { "P","*","T" });
            converter.AddRule("T",new List<Symbol> { "P" });
            converter.AddRule("P",new List<Symbol> { "i" });
            converter.AddRule("P",new List<Symbol> { "(","E",")" });

            converter.Construct();
            var tgrm = new TransGrammar();
            tgrm= converter.ConvertInTransGrammar(inputGrammar,"i+i*i","iii*+");

            break;
          case "I3": { // ATGrammar(V,T,OP,S,P)
              var atgr = new ATGrammar(new List<Symbol>() { "P","E","T","S" },
                                       new List<Symbol>() { "*","+","(",")","c" },
                                       new List<OPSymbol>(),"S");

              //правила для грамматики
              atgr.Addrule("S",new List<Symbol>() { "E" });
              atgr.Addrule("E",new List<Symbol>() { "E","+","T" });
              atgr.Addrule("E",new List<Symbol>() { "T" });
              atgr.Addrule("T",new List<Symbol>() { "T","*","P" });
              atgr.Addrule("T",new List<Symbol>() { "P" });
              atgr.Addrule("P",new List<Symbol>() { "c" });
              atgr.Addrule("P",new List<Symbol>() { "(","E",")" });

              atgr.NewAT(new List<Symbol>() { "p","q","r" },new List<Symbol>() { "*","+" },new List<Symbol>() { "c" });

              atgr.Print();
              break;
          }
          case "I4": { // ATGrammar(V,T,OP,S,P)
              // S, Er    *, +, cr     {ANS}r
              var atgr = new ATGrammar(
                new List<Symbol>() { "S",new Symbol("E",new List<Symbol>() { "r" }) },
                new List<Symbol>() { "*","+",new Symbol("c",new List<Symbol>() { "r" }) },
                new List<OPSymbol>() { new OPSymbol("{ANS}",new List<Symbol>() { "r" }) },
                new Symbol("S"));
              atgr.Addrule(new Symbol("S"), // LHS        LHS -> RHS  
                                       new List<Symbol>() { // RHS
                                              new Symbol("E", // S -> Ep {ANS}r r -> p
                                              new List<Symbol>() { "p" }), new Symbol("{ANS}",new List<Symbol>() { "r" }) },
              new List<AttrFunction>() { new AttrFunction(new List<Symbol>() {"r" },new List<Symbol> { "p" })
                                               }
                                      );

              atgr.Addrule(new Symbol("E",new List<Symbol>() { "p" }), // Ep -> +EpEr p -> q + r
                      new List<Symbol>() { "+",new Symbol("E",new List<Symbol>() { "p" }),
                                                                         new Symbol("E",new List<Symbol>() { "r" }) },
                      new List<AttrFunction>() { new AttrFunction(new List<Symbol>() {
                                     "p" },new List<Symbol> { "q", "+", "r" })
                      });

              atgr.Addrule(new Symbol("E",new List<Symbol>() { "p" }),  // Ep -> *EpEr   p -> q * r
                      new List<Symbol>() { "*",new Symbol("E",new List<Symbol>() { "p" }),new Symbol("E",new List<Symbol>() { "r" }) },
                      new List<AttrFunction>() { new AttrFunction(new List<Symbol>() {
                                     "p" },new List<Symbol> { "q", "+", "r" })
                      });

              atgr.Addrule(new Symbol("E",new List<Symbol>() { "p" }), // Ep -> Cr   p -> r
                   new List<Symbol>() { new Symbol("C",new List<Symbol>() { "r" }) },
                   new List<AttrFunction>() { new AttrFunction(new List<Symbol>() {
                                 "p" },new List<Symbol> { "r" })
                   });

              atgr.Print();

              atgr.transform();

              Console.WriteLine("\nPress Enter to show result\n");
              Console.ReadLine();

              atgr.Print();
              Console.WriteLine("\nPress Enter to end\n");
              Console.ReadLine();
              break;
          } 
          case "I5": {
             /* нужна доработка пример  Минеева 201, 2021  i1 , i2=i3 , i4
              D, Lr, E, F      i_b, =, <,>, n_e    {type}a,c , {push}k, {pull}t
               ATGrammar(V,T,OP,S,P) 
             */
             var atgr = new ATGrammar(
                new List<Symbol>() { "D",new Symbol("L",new List<Symbol>() { "r" }),"E","F" },
                new List<Symbol>() { "=",",",new Symbol("i",new List<Symbol>() { "b" }),new Symbol("n",new List<Symbol>() { "e" }) },
                new List<OPSymbol>() {
                    new OPSymbol("{type}",new List<Symbol>() { "a", "c" }),
                    new OPSymbol("{push}",new List<Symbol>() { "k" }),
                    new OPSymbol("{pull}",new List<Symbol>() { "t" }),
                    new OPSymbol("{stack}",new List<Symbol>() { "u" }) },
                new Symbol("D"));
              atgr.Addrule(new Symbol("D"), // LHS
                   new List<Symbol>() { // RHS
                        new Symbol("i", // D -> i_b {тип}a,c Lr   a <- b c <- r
                        new List<Symbol>() { "b" }),new Symbol("{type}",new List<Symbol>() { "a", "c"}),
                        new Symbol("L",
                        new List<Symbol>() { "r" })  },

                        new List<AttrFunction>() {
                          new AttrFunction(new List<Symbol>() { "a" },new List<Symbol> { "b" }),
                          new AttrFunction(new List<Symbol>() { "c" },new List<Symbol> { "r" })
                        }
                   );

              atgr.Addrule(new Symbol("L",
              new List<Symbol>() { new Symbol("r") }), // Lr -> n_e    r <- e
              new List<Symbol>() {
                        new Symbol("n",
                        new List<Symbol>() { "e" }) },

              new List<AttrFunction>() {
                        new AttrFunction(new List<Symbol>() { "r" },new List<Symbol> { "e" })
              });

              atgr.Addrule(new Symbol("L",new List<Symbol>() { "r" }),
              new List<Symbol>() {
                            new Symbol("i",
                            new List<Symbol>() { "b" }),
                            new Symbol("{type}",
                            new List<Symbol>() { "a", "c" })
          },

          new List<AttrFunction>() {
             new AttrFunction(new List<Symbol>() { "a" },new List<Symbol> { "b" }),
              new AttrFunction(new List<Symbol>() { "r" },new List<Symbol> { "c" })
          });

              atgr.Addrule(new Symbol("L",new List<Symbol>() { "r" }),
              new List<Symbol>() {
                            ",",
                            new Symbol("i",
                            new List<Symbol>() { "b" }),
                            new Symbol("{type}",
                            new List<Symbol>() { "a", "c" }),
                            new Symbol("{pull}",
                            new List<Symbol>() { "t" }),
                            new Symbol("{pull}",
                            new List<Symbol>() { "p" }),
                            "E"
          },


          new List<AttrFunction>() {
             new AttrFunction(new List<Symbol>() { "a" },new List<Symbol> { "b" }),
             new AttrFunction(new List<Symbol>() { "c" },new List<Symbol> { "t" }),
             new AttrFunction(new List<Symbol>() { "r" },new List<Symbol> { "p" })
          });

              atgr.Addrule(new Symbol("E"),
                  new List<Symbol>() {
                            ",",
                            new Symbol("i",
                            new List<Symbol>() { "b" }),
                            new Symbol("{type}",
                            new List<Symbol>() { "a", "c" }),
                            new Symbol("{pull}",
                            new List<Symbol>() { "t" }),
                            "E"
                  },

                  new List<AttrFunction>() {
                            new AttrFunction(new List<Symbol>() { "a" },new List<Symbol> { "b" }),
                            new AttrFunction(new List<Symbol>() { "c" },new List<Symbol> { "t" })
                  });

              atgr.Addrule(new Symbol("E"),
                  new List<Symbol>() {
                            "=",
                            new Symbol("i",
                            new List<Symbol>() { "b" }),
                            new Symbol("{type}",
                            new List<Symbol>() { "a", "c" }),
                            new Symbol("{push}",
                            new List<Symbol>() { "k" }),
                            "F"
                          },

              new List<AttrFunction>() {
                            new AttrFunction(new List<Symbol>() { "a" },new List<Symbol> { "" }),
                            new AttrFunction(new List<Symbol>() { "k" },new List<Symbol> { "c" })
              });

              atgr.Addrule(new Symbol("F"),
                  new List<Symbol>() {
                            ",",
                            new Symbol("i",
                            new List<Symbol>() { "b" }),
                            new Symbol("{type}",
                            new List<Symbol>() { "a", "c" }),
                            new Symbol("{push}",
                            new List<Symbol>() { "k" }),
                            "F"
                  },

                  new List<AttrFunction>() {
                            new AttrFunction(new List<Symbol>() { "a" },new List<Symbol> { "b" }),
                            new AttrFunction(new List<Symbol>() { "k" },new List<Symbol> { "c" })
                  });

              atgr.Addrule(new Symbol("F"),
                  new List<Symbol>() {
                            new Symbol("{stack}",
                            new List<Symbol>() { "u" })
              },


              new List<AttrFunction>() {
                            new AttrFunction(new List<Symbol>() { "u" },new List<Symbol> { "1" })
              });

              atgr.Print();

              atgr.transform();

              Console.WriteLine("\nPress Enter to show result\n");
              Console.ReadLine();

              atgr.Print();
              Console.WriteLine("\nPress Enter to end\n");
              Console.ReadLine();
              break;
              //###### Тимофеев 207 2021  ###### 
          }
          case "I6": {
              var atgr = new ATGrammar(
                new List<Symbol>() { "A","B","C","D","E","F","S" },
                new List<Symbol>() { "for","+","(",")","int","=","id",";","<","const2","const1","const3","{","body","}" },
                new List<OPSymbol>() { new OPSymbol  ("D->{ OUT1:= ' for idn1 in range(const1, '}", new List<Symbol>() { "r" }),
                      new OPSymbol("E->{OUT2:= 'const2,'}", new List<Symbol>() { "r" }),
                      new OPSymbol("F->{OUT1:= 'const3): '}", new List<Symbol>() { "r" }),
                      new OPSymbol("B->{ OUT1:= ' body '}", new List<Symbol>() { "r" }),
                      new OPSymbol("C->{ if n3 > n4 then Error}", new List<Symbol>() { "n3", "n4" }) },
                      new Symbol("S"));

              atgr.Addrule("S0",new List<Symbol>() { "S","{ OUT1 := OUT1 || OUT2 }" });
              atgr.Addrule("S",new List<Symbol>() { "A","B","C" });
              atgr.Addrule("A",new List<Symbol>() { "for","(","D","E","F" });
              atgr.Addrule("B",new List<Symbol>() { "body","{OUT1:= ' body'}" });
              atgr.Addrule("C",new List<Symbol>() { "}" });
              atgr.Addrule("D",new List<Symbol>() { "int","id","=","const1",";",new Symbol("{ OUT1:= ' for id_a in range(const1_n, '}",new List<Symbol>() { "n" }) });
              atgr.Addrule("E",new List<Symbol>() { "id","<","const2",";",new Symbol("{OUT2:= 'const2_p,'}",new List<Symbol>() { "p" }) });
              atgr.Addrule("F",new List<Symbol>() { "id","+","const3",")","{",new Symbol("{OUT2:= 'const3_p): '}",new List<Symbol>() { "p" }) });

              atgr.ATG_C_Py(new List<Symbol>() { "s","a","n","p","q","r" },new List<Symbol>() { "=","<","+" });

              atgr.Print();

              Console.WriteLine("\nPress Enter to end\n");
              Console.ReadLine();
              break;
          }
          //######    ######

          case "I7": {
              /* Пример "цепочечного" перевода  11 12 13   
              Грамматика транслирует выражения из инфиксной записи в постфиксную
              Выражения состоят из i, +, * и скобок
              i+i*i без чисел 
              */
              var chainPostfix = new SDT.Scheme(new List<SDT.Symbol>() { "i","+","*","(",")" },
                                                       new List<SDT.Symbol>() { "E","E'","T","T'","F" },
                                                       "E");

              chainPostfix.AddRule("E",new List<SDT.Symbol>() { "T","E'" });
              chainPostfix.AddRule("E'",new List<SDT.Symbol>() { "+","T",SDT.Actions.Print("+"),"E'" });
              chainPostfix.AddRule("E'",new List<SDT.Symbol>() { SDT.Symbol.Epsilon });
              chainPostfix.AddRule("T",new List<SDT.Symbol>() { "F","T'" });
              chainPostfix.AddRule("T'",new List<SDT.Symbol>() { "*","F",SDT.Actions.Print("*"),"T'" });
              chainPostfix.AddRule("T'",new List<SDT.Symbol>() { SDT.Symbol.Epsilon });
              chainPostfix.AddRule("F",new List<SDT.Symbol>() { "i",SDT.Actions.Print("i") });
              chainPostfix.AddRule("F",new List<SDT.Symbol>() { "(","E",")" });

              SDT.LLTranslator chainTranslator = new(chainPostfix);
              // Console.WriteLine("Введите строку: ");
              var inp_str = new SDT.SimpleLexer().Parse(Console.ReadLine());
              if (chainTranslator.Parse(inp_str)) {
                Console.WriteLine("\nУспех. Строка соответствует грамматике.");
              } else {
                Console.WriteLine("\nНе успех. Строка не соответствует грамматике.");
              }
              break;
          }
          case "I8": {
              /* L-атрибутивная грамматика
                 Грамматика вычисляет результат арифметического выражения
                 Выражения состоят из целых положительных чисел, +, * и скобок
                 1+2*3 без чисел
              */
/*
              SDT.Types.Attrs sAttrs = new() { ["value"]=0 };
              SDT.Types.Attrs lAttrs = new() { ["inh"]=0,["syn"]=0 };
              var lAttrSDT = new SDT.Scheme(new List<SDT.Symbol>() { new SDT.Symbol("number",sAttrs),"+","*","(",")" },
                                                    new List<SDT.Symbol>() { "S", new SDT.Symbol("E", sAttrs), new SDT.Symbol("E'", lAttrs),
                                                                                       new SDT.Symbol("T", sAttrs), new SDT.Symbol("T'", lAttrs), new SDT.Symbol("F", sAttrs) },
                                                    "S");

              lAttrSDT.AddRule("S",new List<SDT.Symbol>() { "E",new SDT.Types.Actions((S) => Console.Write(S["E"]["value"].ToString())) });

              lAttrSDT.AddRule("E",new List<SDT.Symbol>() { "T",new SDT.Types.Actions((S) => S["E'"]["inh"]=S["T"]["value"]),"E'",new SDT.Types.Actions((S) => S["E"]["value"]=S["E'"]["syn"]) });

              lAttrSDT.AddRule("E'",new List<SDT.Symbol>() { "+","T",new SDT.Types.Actions((S) => S["E'1"]["inh"]=(int)S["E'"]["inh"]+(int)S["T"]["value"]),"E'",new SDT.Types.Actions((S) => S["E'"]["syn"]=S["E'1"]["syn"]) });

              lAttrSDT.AddRule("E'",new List<SDT.Symbol>() { SDT.Symbol.Epsilon,new SDT.Types.Actions((S) => S["E'"]["syn"]=S["E'"]["inh"]) });

              lAttrSDT.AddRule("T",new List<SDT.Symbol>() { "F",new SDT.Types.Actions((S) => S["T'"]["inh"]=S["F"]["value"]),"T'",new SDT.Types.Actions((S) => S["T"]["value"]=S["T'"]["syn"]) });

              lAttrSDT.AddRule("T'",new List<SDT.Symbol>() { "*","F",new SDT.Types.Actions((S) => S["T'1"]["inh"]=(int)S["T'"]["inh"]*(int)S["F"]["value"]),"T'",new SDT.Types.Actions((S) => S["T'"]["syn"]=S["T'1"]["syn"]) });

              lAttrSDT.AddRule("T'",new List<SDT.Symbol>() { SDT.Symbol.Epsilon,new SDT.Types.Actions((S) => S["T'"]["syn"]=S["T'"]["inh"]) });

              lAttrSDT.AddRule("F",new List<SDT.Symbol>() { "number",new SDT.Types.Actions((S) => S["F"]["value"]=S["number"]["value"]) });

              lAttrSDT.AddRule("F",new List<SDT.Symbol>() { "(","E",")",new SDT.Types.Actions((S) => S["F"]["value"]=S["E"]["value"]) });

              SDT.LLTranslator lAttrTranslator = new(lAttrSDT);
              if (lAttrTranslator.Parse(new SDT.ArithmLexer().Parse(Console.ReadLine()))) {
                Console.WriteLine("\nУспех. Строка соответствует грамматике.");
              } else {
                Console.WriteLine("\nНе успех. Строка не соответствует грамматике.");
              }
*/
              break;
          }

          case "I9": {
              /* Дерево разбора  1*3 только для умножения 
                 Грамматика вычисляет арифметические выражения состоящие из произведений целых положительных числе
                 Дерево разбора печатается на экран, конвертируется в .dot файл и выполняется
              */
/*
              SDT.Types.Attrs sAttrs2 = new() { ["value"]=0 };
              SDT.Types.Attrs lAttrs2 = new() { ["inh"]=0,["syn"]=0 };
              SDT.Scheme treeGrammar = new SDT.Scheme(new List<SDT.Symbol>() { new SDT.Symbol("number",sAttrs2),"*" },
                                                      new List<SDT.Symbol>() { "S",new SDT.Symbol("T",sAttrs2),new SDT.Symbol("T'",lAttrs2),new SDT.Symbol("F",sAttrs2) },
                                                      "S");

              SDT.OperationSymbol op1 = new(new SDT.Types.Actions((S) => Console.Write(S["T"]["value"].ToString())),"print(T.value)");
              SDT.OperationSymbol op2 = new(new SDT.Types.Actions((S) => S["T'"]["inh"]=S["F"]["value"]),"T'.inh = F.value",new() { "T'.inh" },new() { "F.value" });
              SDT.OperationSymbol op3 = new(new SDT.Types.Actions((S) => S["T"]["value"]=S["T'"]["syn"]),"T.value = T'.syn",new() { "T.value" },new() { "T'.syn" });
              SDT.OperationSymbol op4 = new(new SDT.Types.Actions((S) => S["T'1"]["inh"]=(int)S["T'"]["inh"]*(int)S["F"]["value"]),"T'1.inh = T'.inh * F.value",new() { "T'1.inh" },new() { "T'.inh","F.value" });
              SDT.OperationSymbol op5 = new(new SDT.Types.Actions((S) => S["T'"]["syn"]=S["T'1"]["syn"]),"T'.syn = T'1.syn",new() { "T'.syn" },new() { "T'1.syn" });
              SDT.OperationSymbol op6 = new(new SDT.Types.Actions((S) => S["T'"]["syn"]=S["T'"]["inh"]),"T'.syn = T'.inh",new() { "T'.syn" },new() { "T'.inh" });
              SDT.OperationSymbol op7 = new(new SDT.Types.Actions((S) => S["F"]["value"]=S["number"]["value"]),"F.value = number.value",new() { "F.value" },new() { "number.value" });

              treeGrammar.AddRule("S",new List<SDT.Symbol>() { "T",op1 });
              treeGrammar.AddRule("T",new List<SDT.Symbol>() { "F",op2,"T'",op3 });
              treeGrammar.AddRule("T'",new List<SDT.Symbol>() { "*","F",op4,"T'",op5 });
              treeGrammar.AddRule("T'",new List<SDT.Symbol>() { SDT.Symbol.Epsilon,op6 });
              treeGrammar.AddRule("F",new List<SDT.Symbol>() { "number",op7 });

              SDT.ParseTreeTranslator treeTr = new(treeGrammar);
              SDT.ParseTree root = treeTr.Parse(new SDT.ArithmLexer().Parse(Console.ReadLine()));
              if (root!=null) {
                root.Print();
                root.Execute();
                // утилиты для прорисовки дерева в файл  
                root.PrintToFile("../../../../parse_tree.dot",true);
                root.PrintToFile("../../../../parse_tree2.dot",false);
              } else {
                Console.WriteLine("Строка не соответствует грамматике");
              }
*/
              break;
          }

          default:
            Console.WriteLine("Выход из программы");
            return;
        } // end switch
      } // end while
    } // end void Main()

  } // end class Program
}