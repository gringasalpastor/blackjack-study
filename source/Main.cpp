#include <KAboutData>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>

#include "MainWindow.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  KLocalizedString::setApplicationDomain("blackjack-study");

  KAboutData aboutData(QStringLiteral("BlackjackStudy"),                      // Component name for the .rc file
                       i18n("blackjack-study"),                               // DisplayName
                       QStringLiteral("1.0"),                                 // Version
                       i18n("A program to study blackjack basic strategy."),  // ShortDescription
                       KAboutLicense::Unknown, i18n("Michael Hancock"),
                       i18n("A program to study blackjack basic strategy."),  // OtherText
                       QStringLiteral("https://github.com/gringasalpastor/blackjack-study"),
                       QStringLiteral("220162+gringasalpastor@users.noreply.github.com"));
  aboutData.addAuthor(i18n("Michael Hancock"), i18n("Task"),
                      QStringLiteral("220162+gringasalpastor@users.noreply.github.com"),
                      QStringLiteral("https://github.com/gringasalpastor/"), QStringLiteral("gringasalpastor"));
  KAboutData::setApplicationData(aboutData);

  QCommandLineParser parser;
  aboutData.setupCommandLine(&parser);
  parser.process(app);
  aboutData.processCommandLine(&parser);

  MainWindow* window = new MainWindow();
  window->setWindowIcon(QIcon::fromTheme(QStringLiteral("blackjack-study")));
  window->show();

  return app.exec();
}
