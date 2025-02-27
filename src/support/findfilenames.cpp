#
/*
 *    Copyright (C)  2015, 2016, 2017, 2018, 2019, 2020
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    This file is part of the Qt-DAB 
 *
 *    Qt-DAB is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    Qt-DAB is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Qt-DAB; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include	"findfilenames.h"
#include	"dab-constants.h"
#include	<QDebug>
static inline
bool    isValid (QChar c) {
	return c. isLetter () || c. isDigit () || (c == '-');
}

	findfileNames::findfileNames (QSettings *s) {
	dabSettings	= s;
}

	findfileNames::~findfileNames	() {}


FILE	*findfileNames::findContentDump_fileName (const QString &channel) {
QString	saveDir		= dabSettings -> value ("contentDir",
	                                        QDir::homePath ()). toString ();
QString theTime         = QDateTime::currentDateTime (). toString ();
QString suggestedFileName;

	if ((saveDir != "") && (!saveDir. endsWith ('/')))
	   saveDir = saveDir + '/';

	for (int i = 0; i < theTime. length (); i ++)
	   if (!isValid (theTime. at (i)))
	      theTime. replace (i, 1, '-');
	suggestedFileName = saveDir + "Qt-DAB-" + channel +
	                                          "-" + theTime + ".txt";

	QString fileName = QFileDialog::getSaveFileName (nullptr,
	                                                 "Save file ...",
	                                                  suggestedFileName,
	                                                  "Text (*.txt)");
	if (fileName == "")
	   return nullptr;

	fileName	= QDir::toNativeSeparators (fileName);
	FILE *fileP	= fopen (fileName. toUtf8(). data(), "w");

	if (fileP == nullptr) {
	   fprintf (stderr, "Could not open file %s\n",
	                              fileName. toUtf8(). data());
	   return nullptr;
	}

	QString	dumper	= QDir::fromNativeSeparators (fileName);
	int x           = dumper. lastIndexOf ("/");
	saveDir         = dumper. remove (x, dumper. count () - x);
	dabSettings     -> setValue ("contentDir", saveDir);
	return fileP;
}

//
FILE	*findfileNames::findFrameDump_fileName (const QString &service) {
QString	saveDir	= dabSettings -> value ("saveDir_frameDump",
	                                QDir::homePath ()).  toString ();
QString theTime         = QDateTime::currentDateTime (). toString ();

	if ((saveDir != "") && (!saveDir. endsWith ('/')))
	   saveDir = saveDir + '/';

	QString tailS	= service + "-" + theTime;
	for (int i = 0; i < tailS. length (); i ++)
	   if (!isValid (tailS. at (i)))
	      tailS. replace (i,1, '-');

	QString suggestedFileName = saveDir + tailS + ".aac";
	QString file = QFileDialog::getSaveFileName (nullptr,
	                                             "Save file ...",
	                                             suggestedFileName,
	                                             "aac data (*.aac)");
	if (file == QString (""))       // apparently cancelled
	   return nullptr;
	if (!file.endsWith (".aac", Qt::CaseInsensitive))
	   file.append (".aac");
	file		= QDir::toNativeSeparators (file);
	FILE *theFile	= fopen (file. toLatin1 (). data (), "w+b");
	if (theFile == nullptr) {
	   QString s = QString ("cannot open ") + file;
	   QMessageBox::warning (nullptr, "Warning",
	                               s. toLatin1 (). data ());
	   return nullptr;
	}

	QString dumper	= QDir::fromNativeSeparators (file);
	int x		= dumper. lastIndexOf ("/");
	saveDir		= dumper. remove (x, dumper. count () - x);
	dabSettings	-> setValue ("saveDir_frameDump", saveDir);
	
	return theFile;
}

SNDFILE	*findfileNames::findAudioDump_fileName (const QString &service) {
SF_INFO	*sf_info	= (SF_INFO *)alloca (sizeof (SF_INFO));
QString theTime		= QDateTime::currentDateTime (). toString ();
QString	saveDir	 = dabSettings -> value ("saveDir_audioDump",
	                                 QDir::homePath ()).  toString ();

	if ((saveDir != "") && (!saveDir. endsWith ('/')))
	   saveDir = saveDir + '/';

	QString tailS = service + "-" + theTime;
	for (int i = 0; i < tailS. length (); i ++)
	   if (!isValid (tailS. at (i))) 
	      tailS. replace (i, 1, '-');

	QString suggestedFileName = saveDir + tailS + ".wav";
	QString file = QFileDialog::getSaveFileName (nullptr,
	                                             "Save file ...",
	                                             suggestedFileName,
	                                             "PCM wave file (*.wav)");
	if (file == QString (""))
	   return nullptr;
	if (!file.endsWith (".wav", Qt::CaseInsensitive))
	   file.append (".wav");
	file		= QDir::toNativeSeparators (file);
	sf_info		-> samplerate	= 48000;
	sf_info		-> channels	= 2;
	sf_info		-> format	= SF_FORMAT_WAV | SF_FORMAT_PCM_16;

	SNDFILE *theFile	= sf_open (file. toUtf8(). data(),
	                                   SFM_WRITE, sf_info);
	if (theFile == nullptr) {
	   qDebug() << "Cannot open " << file. toUtf8(). data();
	   return nullptr;
	}

	QString	dumper	= QDir::fromNativeSeparators (file);
	int x		= dumper. lastIndexOf ("/");
	saveDir		= dumper. remove (x, dumper. count () - x);
	dabSettings	-> setValue ("saveDir_audioDump", saveDir);

	return theFile;
}

SNDFILE *findfileNames::findRawDump_fileName (const QString &deviceName,
	                                       const QString &channelName) {
SF_INFO *sf_info        = (SF_INFO *)alloca (sizeof (SF_INFO));
QString theTime		= QDateTime::currentDateTime (). toString ();
QString	saveDir		= dabSettings -> value ("saveDir_rawDump",
	                                        QDir::homePath ()). toString ();
SNDFILE	*theFile;
	for (int i = 0; i < theTime. length (); i ++)
	   if (!isValid (theTime. at (i)))
	      theTime. replace (i, 1, '-');


	if ((saveDir != "") && (!saveDir. endsWith ('/')))
	   saveDir = saveDir + '/';
	QString suggestedFileName = saveDir +
		                    deviceName + "-" +
	                            channelName + "-" + theTime + ".sdr";
	QString file = QFileDialog::getSaveFileName (nullptr,
	                                             "Save file ...",
	                                             suggestedFileName,
	                                             "raw data (*.sdr)");

	if (file == QString (""))       // apparently cancelled
	   return nullptr;
	if (!file.endsWith (".sdr", Qt::CaseInsensitive))
	   file.append (".sdr");

	file	= QDir::toNativeSeparators (file);
	sf_info -> samplerate   = INPUT_RATE;
	sf_info -> channels     = 2;
	sf_info -> format       = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	theFile = sf_open (file. toUtf8 (). data(),
	                                   SFM_WRITE, sf_info);
	fprintf (stderr, "the file %s is open?\n", 
	                              file. toUtf8 (). data ());
	if (theFile == nullptr) {
	   fprintf (stderr, "foute boel\n");
	   qDebug() << "cannot open " << file. toUtf8(). data();
	   return nullptr;
	}

	QString dumper	= QDir::fromNativeSeparators (file);
	int x		= dumper. lastIndexOf ("/");
	saveDir		= dumper. remove (x, dumper. count () - x);
	dabSettings	-> setValue ("saveDir_rawDump", saveDir);
	fprintf (stderr, "theffile is open\n");
	return theFile;
}

FILE	*findfileNames::findScanDump_fileName		() {
	QMessageBox::StandardButton resultButton =
	             QMessageBox::question (nullptr, "Qt-DAB",
	                                    "save the scan?\n",
	                                    QMessageBox::No | QMessageBox::Yes,
	                                    QMessageBox::Yes);
	if (resultButton != QMessageBox::Yes)
	   return nullptr;

	QString   saveDir = dabSettings -> value ("contentDir",
	                                        QDir::homePath ()). toString ();

	if ((saveDir != "") && (!saveDir. endsWith ('/')))
	   saveDir = saveDir + '/';

	QString theTime = QDateTime::currentDateTime (). toString ();
	for (int i = 0; i < theTime. length (); i ++)
	   if (!isValid (theTime. at (i)))
	      theTime. replace (i, 1, '-');
	QString suggestedFileName =
	                       saveDir + "Qt-DAB-scan" + "-" + theTime + ".txt";

	QString fileName = QFileDialog::getSaveFileName (nullptr,
	                                                 "Save file ...",
	                                                 suggestedFileName,
	                                                 "Text (*.txt)");
	return  fopen (fileName. toUtf8 (). data (), "w");
}

FILE	*findfileNames::findSummary_fileName	() {
	QMessageBox::StandardButton resultButton =
	             QMessageBox::question (nullptr, "Qt-DAB",
	                                    "save summary?\n",
	                                    QMessageBox::No | QMessageBox::Yes,
	                                    QMessageBox::Yes);
	if (resultButton != QMessageBox::Yes)
	   return nullptr;

	QString   saveDir = dabSettings -> value ("contentDir",
	                                        QDir::homePath ()). toString ();

	if ((saveDir != "") && (!saveDir. endsWith ('/')))
	   saveDir = saveDir + '/';

	QString theTime = QDateTime::currentDateTime (). toString ();
	for (int i = 0; i < theTime. length (); i ++)
	   if (!isValid (theTime. at (i)))
	      theTime. replace (i, 1, '-');
	QString suggestedFileName =
	                  saveDir + "Qt-DAB-summary" + "-" + theTime + ".txt";

	QString fileName = QFileDialog::getSaveFileName (nullptr,
	                                                 "Save file ...",
	                                                 suggestedFileName,
	                                                 "Text (*.txt)");
	return  fopen (fileName. toUtf8 (). data (), "w");
}

const
QString	findfileNames::findskipFile_fileName	() {
	QString   saveDir = dabSettings -> value ("contentDir",
	                                        QDir::homePath ()). toString ();

	if ((saveDir != "") && (!saveDir. endsWith ('/')))
	   saveDir = saveDir + '/';

	QString suggestedFileName =
	                  saveDir + "Qt-DAB-skipFile" + ".xml";

	QString fileName =
	   QFileDialog::getSaveFileName (nullptr,
	                                 "Open file ...",
	                                 suggestedFileName,
	                                 "Xml (*.xml)", 0,
	                                 QFileDialog::DontConfirmOverwrite);
	fileName	= QDir::toNativeSeparators (fileName);
	return  fileName;
}

QString findfileNames::finddlText_fileName	() {
QString   saveDir = dabSettings -> value ("contentDir",
                                                QDir::homePath ()). toString ();
QString theTime         = QDateTime::currentDateTime (). toString ();

        if ((saveDir != "") && (!saveDir. endsWith ('/')))
           saveDir = saveDir + '/';

	for (int i = 0; i < theTime. length (); i ++)
	   if (!isValid (theTime. at (i)))
	      theTime. replace (i, 1, '-');

        QString suggestedFileName = saveDir + "Qt-DAB-dlText"  +
                                                  "-" + theTime + ".txt";
	fprintf (stderr, "save file %s\n", suggestedFileName. toLatin1 (). data ());
        QString fileName =
           QFileDialog::getSaveFileName (nullptr,
                                         "Open file ...",
                                         suggestedFileName. toLatin1 (). data (),
                                         "Text (*.txt)");
        fileName        = QDir::toNativeSeparators (fileName);
        return  fileName;
}



