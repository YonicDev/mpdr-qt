#include "randomizergui.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator app_translator,qt_translator;

    QString qt_translations_path = QCoreApplication::applicationDirPath().append("/translations/");
    QString qt_trans_system_path = QLibraryInfo::location(QLibraryInfo::TranslationsPath).append("/");

    QString locale = QLocale::system().name();
    locale.truncate(locale.lastIndexOf("_"));

    QString languagepacks_path = QCoreApplication::applicationDirPath().append("/LanguagePacks/");

    #ifdef WIN32
    QString translation_file = QString("qt_%1.qm").arg(locale);
    #else
    // We don't know why, but qt_LOCALE.qm files can't be opened in Linux
    // so we load qtbase_LOCALE.qm instead
    QString translation_file = QString("qtbase_%1.qm").arg(locale);
    #endif

    if(qt_translator.load(qt_translations_path + translation_file))
        a.installTranslator(&qt_translator);
    else if(qt_translator.load(qt_trans_system_path + translation_file))
        a.installTranslator(&qt_translator);
    if(app_translator.load(languagepacks_path + QString("mpdr_%1.qm").arg(locale))) {
        a.installTranslator(&app_translator);
    }

    RandomizerGUI w;
    w.show();
    return a.exec();
}
