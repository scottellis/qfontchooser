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

	m_sizeCombo->setCurrentText("12");

	restoreWindowState();
}

void FontChooser::fontChanged(const QFont &font)
{
	QFont newFont(font);
	int size = m_sizeCombo->currentText().toInt();
	newFont.setPixelSize(size);
	m_sampleEdit->setFont(newFont);
	update();
}

void FontChooser::sizeChanged(const QString &text)
{
	int size = text.toInt();
	QFont newFont(m_sampleEdit->font());
	newFont.setPixelSize(size);
	m_sampleEdit->setFont(newFont);
}

void FontChooser::layoutWindow()
{
	m_fontCombo = new QFontComboBox;
	m_sizeCombo = new QComboBox;
	m_sizeCombo->setMaximumWidth(60);

	m_sizeCombo->addItem("8");
	m_sizeCombo->addItem("9");
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

	m_sampleEdit = new QTextEdit;
	m_exitBtn = new QPushButton("Exit");

	m_sampleEdit->setText("In Xanadu did Kubla Khan\n" \
	                       "A stately pleasure-dome decree:\n" \
	                       "Where Alph, the sacred river, ran\n" \
	                       "Through caverns measureless to man\n" \
	                       "   Down to a sunless sea.\n"); 

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow("Font", m_fontCombo);
	formLayout->addRow("Size", m_sizeCombo);

	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addStretch();
	hLayout->addWidget(m_exitBtn);
	hLayout->addStretch();

	QVBoxLayout *vLayout = new QVBoxLayout;

	vLayout->addLayout(formLayout);
	vLayout->addWidget(m_sampleEdit);
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

	delete settings;
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

	delete settings;
}

QString FontChooser::settingsFile()
{
	QString home = QDir::homePath();

	if (home.contains("root"))
		return "";

	return home + "/qfontchooser.ini";
}
