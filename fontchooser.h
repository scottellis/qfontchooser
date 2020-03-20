#ifndef FONTCHOOSER_H
#define FONTCHOOSER_H

#include <QtWidgets/QMainWindow>
#include <qfontcombobox.h>
#include <qcombobox.h>
#include <qtextedit.h>
#include <qpushbutton.h>

#include "ui_fontchooser.h"

class FontChooser : public QMainWindow
{
    Q_OBJECT

public:
    FontChooser(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *);

protected slots:
    void fontChanged(const QFont &font);
    void sizeChanged(const QString &text);

private:
    void layoutWindow();
    void restoreWindowState();
    void saveWindowState();
    void loadCache();
    void saveCache();

    QString settingsFile();
    QString cacheFile();

    Ui::FontChooserClass ui;

    QFontComboBox *m_fontCombo;
    QComboBox *m_sizeCombo;
    QTextEdit *m_edit;
    QPushButton *m_exitBtn;
};

#endif // FONTCHOOSER_H
