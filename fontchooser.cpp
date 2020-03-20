#include <qdir.h>
#include <qsettings.h>
#include <qboxlayout.h>
#include <qformlayout.h>

#include "fontchooser.h"

FontChooser::FontChooser(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    layoutWindow();

    connect(m_exitBtn, SIGNAL(pressed()), SLOT(close()));
    connect(m_fontCombo, SIGNAL(currentFontChanged(const QFont &)), SLOT(fontChanged(const QFont &)));
    connect(m_sizeCombo, SIGNAL(currentIndexChanged(const QString &)), SLOT(sizeChanged(const QString &)));

    restoreWindowState();
}

void FontChooser::fontChanged(const QFont &font)
{
    QFont newFont(font);
    int size = m_sizeCombo->currentText().toInt();
    newFont.setPixelSize(size);
    m_edit->setFont(newFont);
}

void FontChooser::sizeChanged(const QString &text)
{
    int size = text.toInt();
    QFont newFont(m_edit->font());
    newFont.setPixelSize(size);
    m_edit->setFont(newFont);
}

void FontChooser::layoutWindow()
{
    m_fontCombo = new QFontComboBox;
    m_sizeCombo = new QComboBox;
    m_sizeCombo->setMaximumWidth(64);

    m_sizeCombo->addItem("10");
    m_sizeCombo->addItem("12");
    m_sizeCombo->addItem("14");
    m_sizeCombo->addItem("16");
    m_sizeCombo->addItem("18");
    m_sizeCombo->addItem("20");
    m_sizeCombo->addItem("22");
    m_sizeCombo->addItem("24");
    m_sizeCombo->addItem("26");
    m_sizeCombo->addItem("28");
    m_sizeCombo->addItem("32");
    m_sizeCombo->addItem("36");
    m_sizeCombo->addItem("40");
    m_sizeCombo->addItem("44");
    m_sizeCombo->addItem("48");

    m_edit = new QTextEdit;
    m_exitBtn = new QPushButton("Exit");

    m_edit->setText("In Xanadu did Kubla Khan\n" \
                           "A stately pleasure-dome decree:\n" \
                           "Where Alph, the sacred river, ran\n" \
                           "Through caverns measureless to man\n" \
                           "   Down to a sunless sea.\n"); 

    QVBoxLayout *vLayout = new QVBoxLayout;

    QHBoxLayout *hLayout = new QHBoxLayout;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Font", m_fontCombo);
    hLayout->addLayout(formLayout);

    formLayout = new QFormLayout;
    formLayout->addRow("Size", m_sizeCombo);
    hLayout->addLayout(formLayout);

    vLayout->addLayout(hLayout);

    vLayout->addWidget(m_edit);

    hLayout = new QHBoxLayout;
    hLayout->addStretch();
    hLayout->addWidget(m_exitBtn);
    hLayout->addStretch();
    vLayout->addLayout(hLayout);

    centralWidget()->setLayout(vLayout);
}

void FontChooser::closeEvent(QCloseEvent *)
{
    saveWindowState();
}

void FontChooser::restoreWindowState()
{
    QString iniFile = settingsFile();

    if (iniFile.isEmpty())
    	return;

    QSettings *settings = new QSettings(iniFile, QSettings::IniFormat);

    if (!settings)
    	return;

    settings->beginGroup("Window");
    restoreGeometry(settings->value("Geometry").toByteArray());
    restoreState(settings->value("State").toByteArray());
    settings->endGroup();

    settings->beginGroup("Font");
    QString family = settings->value("Family").toString();
    int pointSize = settings->value("PointSize").toInt();
    int weight = settings->value("Weight").toInt();
    QString fontSize = settings->value("Size", "32").toString();
    settings->endGroup();

    delete settings;

    if (family.length() > 0)
        m_fontCombo->setCurrentFont(QFont(family, pointSize, weight));

    m_sizeCombo->setCurrentText(fontSize);
}

void FontChooser::saveWindowState()
{
    QString iniFile = settingsFile();

    if (iniFile.isEmpty())
    	return;

    QSettings *settings = new QSettings(iniFile, QSettings::IniFormat);

    if (!settings)
    	return;

    settings->beginGroup("Window");
    settings->setValue("Geometry", saveGeometry());
    settings->setValue("State", saveState());
    settings->endGroup();

    settings->beginGroup("Font");
    QFont font = m_fontCombo->currentFont();
    settings->setValue("Family", font.family());
    settings->setValue("PointSize", font.pointSize());
    settings->setValue("Weight", font.weight());
    settings->setValue("Size", m_sizeCombo->currentText());
    settings->endGroup();

    delete settings;
}

QString FontChooser::settingsFile()
{
    QString home = QDir::homePath();

    return home + "/qfontchooser.ini";
}
