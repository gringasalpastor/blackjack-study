#include <fstream>
#include <iostream>

using namespace std;

#include <QList>
#include <string>

/*
 * This program generates a list of all possible hards hands. The output is used to define hand generator
 **/

QList<QList<int> > GenerateAllPossibleHands(int sum);
void               PrintList(ofstream& CppFileOut, ofstream& HeaderFileOut, int sum, string name, int max_cards);
string             StringToUpper(string strToConvert);

int main() {
  string Name = "HardHandData";

  string CppFile = Name;
  CppFile += ".cpp";
  ofstream CppFileOut(CppFile.c_str());

  string HeaderFile = Name;
  HeaderFile += ".h";
  ofstream HeaderFileOut(HeaderFile.c_str());

  HeaderFileOut << "#ifndef " << StringToUpper(Name) << "_H" << endl;
  HeaderFileOut << "#define " << StringToUpper(Name) << "_H" << endl;

  // .cpp file
  HeaderFileOut << "#include <QVector>" << endl;
  CppFileOut << "#include \"" << Name << ".h\"" << endl;

  CppFileOut << Name << "::" << Name << "()" << endl << "{" << endl;

  //.h file
  HeaderFileOut << "class " << Name << endl << "{" << endl;
  HeaderFileOut << "\tpublic:" << endl;
  HeaderFileOut << "\t\t" << Name << "();" << endl;

  CppFileOut << "\tQVector <int> tmp;" << endl;

  PrintList(CppFileOut, HeaderFileOut, 8, "eights", 2);
  PrintList(CppFileOut, HeaderFileOut, 9, "nines", 2);
  PrintList(CppFileOut, HeaderFileOut, 10, "tens", 2);
  PrintList(CppFileOut, HeaderFileOut, 11, "elevens", 2);
  PrintList(CppFileOut, HeaderFileOut, 12, "twelves", 5);
  PrintList(CppFileOut, HeaderFileOut, 13, "thirteens", 5);
  PrintList(CppFileOut, HeaderFileOut, 14, "fourteens", 5);
  PrintList(CppFileOut, HeaderFileOut, 15, "fifthteens", 5);
  PrintList(CppFileOut, HeaderFileOut, 16, "sixteens", 5);
  PrintList(CppFileOut, HeaderFileOut, 17, "seventeens", 5);

  CppFileOut << "}";

  HeaderFileOut << "};" << endl;
  HeaderFileOut << "#endif" << endl;
  return 0;
}

void PrintList(ofstream& CppFileOut, ofstream& HeaderFileOut, int sum, string name, int max_cards) {
  QList<QList<int> > List = GenerateAllPossibleHands(sum);

  HeaderFileOut << "\t\t\tQVector < QVector <int> > " << name << ";" << endl;

  for (int i = 0; i < List.size(); i++) {
    if (List[i].size() < 2 || List[i].size() > max_cards) {
      continue;
    }
    // Remove piared hands
    if ((List[i].size() == 2) && (List[i][0] == List[i][1])) {
      continue;
    }
    CppFileOut << "\t"
               << "tmp.resize(0);" << endl;
    CppFileOut << "\t"
               << "tmp";

    for (int j = 0; j < List[i].size(); j++) {
      CppFileOut << " << " << List[i][j];
    }
    CppFileOut << ";" << endl;
    CppFileOut << "\t" << name << " << "
               << "tmp;" << endl;
  }
}

QList<QList<int> > GenerateAllPossibleHands(int sum) {
  QList<QList<int> > AllHands;
  int                new_sum = sum - 2;
  int                card    = 2;
  if (sum >= 2 && sum <= 10) {
    QList<int> singleton;
    singleton << sum;
    AllHands << singleton;
  }

  while (new_sum >= 2 && card <= 10) {
    QList<QList<int> > ThisTry = GenerateAllPossibleHands(new_sum);

    for (int i = 0; i < ThisTry.size(); i++) {
      ThisTry[i] << card;
    }
    AllHands << ThisTry;

    new_sum--;
    card++;
  }
  return AllHands;
}

string StringToUpper(string strToConvert) {
  for (unsigned int i = 0; i < strToConvert.length(); i++) {
    strToConvert[i] = toupper(strToConvert[i]);
  }
  return strToConvert;
}