# Qt-DAB-4/0 [![Build Status](https://travis-ci.org/JvanKatwijk/qt-dab.svg?branch=master)](https://travis-ci.org/JvanKatwijk/qt-dab)

Qt-DAB-4.0 is software for Linux and Raspberry Pi for listening to terrestrial Digital Audio Broadcasting (DAB and DAB+). Qt-DAB is accompanied by its little sister dabMini, built on the same set of sources.

Since the original 3.71 version there were quite many changes, both visible
and invisible. So, it was time for a new version number

![overview](/qt-dab-screen.png?raw=true)

------------------------------------------------------------------
Table of Contents
------------------------------------------------------------------

* [Introduction](#introduction)
* [Features](#features)
* [Widgets and scopes](#widgets-and-scopes-for-qt-dab)
* [dabMini](#dabMini)
* [Documentation](#documentation)
* [Presets](#presets-for-qt-dab)
* [Colors](#colors-for-qt-dab)
* [Maintaining History](#maintaining-history)
* [Comment on some config settings](#comment-on-some--configuration-settings)
* [Obsolete properties](#obsolete-properties)
* [Installation on Windows](#installation-on-windows)
* [Installation on Linux x64](#installation-on-linux-x64)
* [Configuring](#configuring)
* [Interfacing to another device](#interfacing-to-another-device)
* [Using other bands than Band III or L Band](#using-other-bands-than-band-iii-or-l-band)
* [xml-files and support](#xml-files-and-support)
* [EPG-Handling](#epg-handling)
* [Recording the SNR](#recording-the-snr)
* [Scanning and the skip table](#scanning-and-the-skip-table)
* [Pluto device and fm transmission](#pluto-device-and-fm-transmission)
* [Copyright](#copyright)

------------------------------------------------------------------
Introduction
------------------------------------------------------------------

**Qt-DAB-4.0** is a rich implementation of a DAB decoder for use on Linux and Windows based PC's, including some ARM based boards, such as the Raspberry PI, both 2 and 3.

It provides an abundant amount of selectors and displays, most of
which can be switched off, but are of interest for those who want to see aspects of the DAB signal.

While it is not very complicated to generate an executable for either
Qt-DAB or dabMini, for Linux-x64 appImages exist  for both Qt-DAB and dabMini.
For Windows an installer is available.

Qt-DAB makes extensive use of a GUI. Personally, grown up in the time of
ASR-33 terminals and "command lines", I often prefer a simple command line
over a GUI.
Therefore, a **terminal-DAB-xxx** version was developed, a
simpler version, just for listening to a DAB service, making use of 
command line

![Qt-DAB terminal DAB](/qt-dab-terminal-dab.png?raw=true)

For those who are nostalgic to the era of nice wooden radios with glowing tubes,
Qt-DAB can be configured such that - using the Adalm Pluto as device -
the audio of a selected service is transmitted on a user specified frequency
 in FM stereo with the "dynamic label" sent as RDS.

------------------------------------------------------------------
Features
------------------------------------------------------------------

  * DAB (mp2) and DAB+ (HE-AAC v1, HE-AAC v2 and LC-AAC) decoding
  * MOT SlideShow (SLS)
  * Dynamic Label (DLS) 
  * Both DAB bands supported): 
  	* VHF Band III (default),
   	* L-Band (obsolete now),
	* a user defined Band
  * Modes I, II and IV (Mode I default, Modes II and IV obsolete, but can be set in the ".ini" file)m
  * Views on the signal: spectrum view incl. constellation diagram, correlation result, TII spectrum and the SNR over time.
  * Detailed information for selected service (SNR, bitrate, frequency, ensemble name, ensemble ID, subchannel ID, used CUs, protection level, CPU usage, program type, language, alternative FM frequency if available, 4 quality bars),
  * Detailed information for *other* services by right-clicking on their name (bitrate, subchannel ID, used CU's protection level, program type),
  * Automatic display of TII (Transmitter Identification Information) data when transmitted,
  * *Presets* for easy switching of programs in different ensembles (see section *Presets*),
  * Dumping of the input data of the DAB channel (Warning: produces large raw files!) into \* sdr files or xml file formats and playing them again later (see section on xml format),
  * Saving audio as uncompressed wave files,
  * Saving aac frames from DAB+ services for processing by e.g. VLC,
  * Saving the ensemble content description: audio and data streams, including almost all technical data) into a text file readable by e.g *LibreOfficeCalc*
  * Scanning function (scan the band, show the results on the screen and save a detailed description of the services found in a file),
  * ip output: when configured the ip data - if selected - is sent to a specificied ip address (default: 127.0.0.1:8888),
  * TPEG output: when configured the data is sent to a specified ip address,
  * EPG detection and building up a time table,
  * Supports configuration as input device:
	- Adalm Pluto,
   	- SDR DAB sticks (RTL2838U or similar), 
	- HACKRF One, 
  	- Airspy, including Airspy mini,
  	- SDRplay (RSP I, RSP II, RSP Duo and RSP Dx), with separate entries for v2 and v3 library
	- limeSDR, 
	- Soapy (experimental, Linux only), 
	- ExtIO (expertimental, Windows only),
	- rtl_tcp servers.
  *Always supported input from:
   	- prerecorded dump (*.raw, *.iq and *.sdr),
	- xml format files.
  * Clean interface to add other devices, see below.

Not yet or partly implemented:

  * DMB (Audio and Video)
  * TPEG: when configured, TPEG messages are being sent to a TCP port; sources for a simple client are part of the source distribution.
  * Journaline (an untested Journaline implementation is part of the sources).
  * Other bands than used for terrestrial broadcasting in Europe (like DAB over cable)

Note:
While the 2.13 support for SDRplay devices is able to handle
the RSP 1, RSP II, RSP Ia and RSP duo, for handling the RSP-Dx one
needs 3.0X support

------------------------------------------------------------------
Widgets and scopes for Qt-DAB
------------------------------------------------------------------

Qt-DAB always shows a main widget; a number of  **optional**
widgets is visible or invisible under user's control

  * a widget with controls for the attached device,
  * a widget for additional configuration settings,
  * a widget showing the technical information of the *selected service* as well
as some information on the quality of the decoding, 
  * a widget showing the spectrum of the received radio signal, the constellation of the decoded signal and some quality parameters,,
  * a widget showing the spectrum of the NULL period between successive DAB frames from which the TII is derived,
  * a widget showing the correlations response(s) from different transmitters in the SFN,
  * a widget showing the development - over time - of the SNR,
  * if configured and data is detected, the time table for the current audio service

![Qt-DAB totaal](/qt-dab-totaal.png?raw=true)

Another - an eight' - widget shows when running a *scan*; the widget will show the contents of the ensembles found in the selected channel. In 3.5 the
possibility was created to save a detailed description of the services
in the different channels, in a format easy to process with LibreOffice
or comparable programs.

While the main window is **always** shown, visibility of the others is
under user control, the main widget contains a button for each..

![Qt-DAB main widget](/qt-dab-main-widget.png?raw=true)

The buttons and other controls on the main widget are equipped with
*tool tips* briefly explaining the (in most cases obvious) function
of the element (the tooltip on the copyright label shows (a.o) the date the executable was generated.)

The elements in the **left part** of the widget, below the list of services,
 are concerned with selecting a channel and a service. To ease operation the channel selector is augmented with a "-" and a "+" button for selecting the previous resp. next channel.

To ease selection of a service, a second pair of "-" and "+" buttons is available, now for selecting the previous resp. the next service on the list.

Some general data is displayed on the top right part of the widget, 
such as run time and current time, frequency offset and (overall) processor load.

In the middle part, name of the ensemble and name of the selected service
are displayed, complemented with the text of the dynamic label.

Some data on the selected service - if any - can be found on
a separate widget, the "technical data" widget. 
This widget will show where the data for the
service is to be found in the DAB frames, and how it is encoded.

Depending on a setting in the ".ini" file, a logo or slide, transmitted
as Program Associated Data with the audio transmission, will be shown here or on a separate widget
(the setting can be modified from the configuration widget).

Most selectors are concentrated on the bottom part of the right side
of the widget. Buttons to make scopes visible, to store input and or
output into a file, to select input device and the audio and to
scan and store a description of the ensemble are in that section.

![qt-dan controls ](/qt-dab-main-controls.png?raw=true)

During *scanning*, a separate window will be shown with the results
of the scan as shown in the picture. Note that what is shown is a *subset*
of what will be recorded if a choice is made to save the output of the scan. 

![Qt-DAB scan result](/qt-dab-scan-result.png?raw=true)

---------------------------------------------------------------------
dabMini
---------------------------------------------------------------------

**dabMini** is a version of the DAB decoder with a minimal GUI.
dabMini is built from the same  sources as Qt-DAB, so
modifications to the Qt-DAB sources are automatically applied to
dabMini as well.

![Qt-DAB dabMini](/dab-mini.png?raw=true)

Other than Qt-DAB, there is no selector for the device. On program start up
the software polls the availability of the configured devices, the first
one that seems OK is selected.

The "main" GUI contains some selectors for setting device properties,
depending on the selected device. The picture shows the program using
an SDRplay device, with agc not selected and selectors for if gain and
lna state.

--------------------------------------------------------------------
Documentation
--------------------------------------------------------------------

An extensive "user's guide" - in pdf format - can be found in the "docs"
section of the source tree. The documentation contains a complete
description of the widgets, of the values in the ".ini" file,
on configuring for creating an executable (Linux), and even a
complete description on how to add a device to the configuration.

![Qt-DAB documentation](/qt-usersguide.png?raw=true)

Note: the documentation is still for 3.72

----------------------------------------------------------------------
Presets for Qt-DAB and dabMini
----------------------------------------------------------------------

A *preset* option is available to allow storing and selecting
"favorit" services. Touching the name of the currently selected
audio service with the right hand mouse button will save the
"channel:serviceName" pair in the preset list.

The presets are stored in an xml file, `.qt-dab-presets.xml`.

Clicking with the *left* mouse button on the servicename in the service
list instructs the software to select the channel and
select the service with that name).

Of course, one is also able to *remove* an entry from the presets.
To do this, select the entry (by putting the curson on it without
clicking any of the mouse buttons) and press the *shift* and the *delete*
button on the keyboard simultaneously.

----------------------------------------------------------------------
Storing gain settings
----------------------------------------------------------------------

It is often the case that, for a particular device the optimal gain setting
for channel X is not the same as for channel Y (assuming X != Y).
This is especially annoying during scanning. Therefore, 
the gain settings for each channel are recorded and used whenever
that channel is selected.

----------------------------------------------------------------------
Colors for Qt-DAB
----------------------------------------------------------------------

Setting colors is rather personal, that is why Qt-DAB provides
the possibility of setting a color to buttons and displays.
(in total there are 20 push buttons, 18 on the main GUI, 2 on the
technical data widget).

To ease life a little, selecting a color setting for a button is
now made easy: right clock with the mouse on the button, and a
small menu appears on which the color for the button can be
selected (one of a predefined list), and next a similar menu appears
for selecting the color of the text on the button.

The settings are saved in the ".ini" file.

For setting the colors on the scopes, right click on the scope. Three
questions will be asked: what will be the color of the display (background),
what will be the color of the grid and what will be the color of the curve.

---------------------------------------------------------------------------
Maintaining History
---------------------------------------------------------------------------

Qt-DAB saves all service names found.
The list of Pairs "Channel:serviceName"
will be made (in)visible when touching the appropriate button (the
one labeled with "list").

The data in stored in a file in xml format.
This *history* can be cleared by a click of the right mouse button.
Clicking on a channel:servicename combination with the left
mouse button will cause the QT-DAB software to attempt to set the channel and
select the name.

---------------------------------------------------------------------------
Comment on some  configuration settings
-------------------------------------------------------------------------------

Various settings are maintained between program invocations in a
so-called ".ini" file, ususally "qt-dab.ini", stored in the home directory.
Typical settings are the channel/service combination at program termination,
values, used to initialize the software at program start up and the colors
for buttons and displays.
A complete description of the settings can be found in the user's manual
(in the subdirectory *docs*).

-------------------------------------------------------------------------
Obsolete properties
-------------------------------------------------------------------------

The current DAB standard eliminated the support for Modes other than Mode 1 and Bands other than VHF Band III. The Qt-DAB implementation still supports these features, however, since they are obsolete, there are no controls on the GUI anymore (the control for the Mode was already removed from earlier versions). 

Explicitly setting the Mode and/or the Band is possible by
including appropriate command lines in the ".qt-dab.ini" file.

For the *Mode*, one will add/set a line

	dabMode=Mode x, where x is either 1, 2 or 4

For the *Band*, one will add/set a line

	dabBand=band, where band is either VHF Band III or L_Band

------------------------------------------------------------------
Installation on Windows
--------------------------------------------------------------------

Development of Qt-DAB and related software is on Linux, 
the cross compilation facilities of MINGW64 make it possible to
cross compile the software for windows.

For windows  **installers** can be found in the releases section, https://github.com/JvanKatwijk/qt-dab/releases. The installer will install the executable as well as required libraries.

The installer will also call the official installer for the dll implementing
the 2.3 api for getting access to the SDRplay devices.

------------------------------------------------------------------
Installation on Linux-x64
------------------------------------------------------------------

For Linux-x64 systems, an **appImage** is available.

The appImage can be found in "https://github.com/JvanKatwijk/qt-dab/releases".
The appImage is configured for

	* RTL_TCP
	* AIRSPY
	* SDRPLAY
	* SDRPLAY_V3
	* LIMESDR
	* HACKRF

Of course it is possible to generate an executable, the 
aforementioned user's manual
contains a complete script that can be used to install all required
libraries, download the sources and build an executable on an Ubuntu
(Debian) based system.

Since Buster, the current system on the RPI's, has the same roots
as Ubuntu, the script for Ubuntu can be used to install Qt-DAB
on an RPI.

Note that the source tree contains two variants next to the Qt-DAB program,
a **dabMini** program, a dab decoder with a minimal interface, and **dab-2**
an experimental variant. Both use large parts of the same sources as Qt-DAB does.
 
For the dabMini, an appImage is available for use on an x64 based
Linux system, and the user's manual contains a complete
script, tested on an RPI 2 and 3.

**dab-2** is experimental and not - officially - supported

----------------------------------------------------------------------
Configuring 
----------------------------------------------------------------------

The  user's guide contains a detailed description of the configuration
options (mainly choices for including or excluding a device).

-----------------------------------------------------------------------
Interfacing to another device
-----------------------------------------------------------------------

There exist - obviously - other devices than the ones supported
here. Interfacing another device is not very complicated,
it might be done using the "Soapy" interface, or one might
write a new interface class.

While the handling of devices in dabMini and Qt-DAB is - apart
from handling the user interaction - the same,
it differs from the way device handling is done in dab-2. The description
here relates to device interfacing in Qt-DAB (the handler for the dabMini
differs since it lacks a separate widget for the control).

Device handlers are implemented as a class, derived from
the class *deviceHandler*. Only a few functions have to
be implemented.

A complete description of how to interface a device to Qt-DAB
is given in the user's manual.

------------------------------------------------------------------------
Using other bands than Band III or L Band
------------------------------------------------------------------------

While it is known that the DAB transmissions are now all in Band III,
there are situations where it might is desirable to use other frequencies.
If you want to experiment with a modulator, connected to an SDR device
on different frequencies than the default one (or you want just to
have a restricted number of channels from Band III or L Band), Qt-DAB
offers a possibility to specify a list of channels to be used.
Specify in a file a list of channels, e.g.

	jan	227360
	twee	220352
	drie	1294000
	vier	252650

and pass the file on with the "-A" command line switch.
The channel name is just any identifier, the channel frequency is
given in KHz.

-------------------------------------------------------------------------
xml-files and support
-------------------------------------------------------------------------

Clemens Schmidt, author of the QiRX program and me defined a format
for storing and exchanging "raw" data: xml-files.
Such a file contains in the first bytes - up to 5000 - a description
in xml - as source - of the data contents. This xml description
describes in detail  the coding of the elements.
As an example, a description of data obtained by dumping AIRspy
input. 

 ```
	<?xml version="1.0" encoding="utf-8"?>
	<SDR>
	  <Recorder Name="Qt-DAB" Version="3.2-Beta"/>
	  <Device Name="AIRspy" Model="I"/>
	  <Time Value="Wed Dec 18 12:39:34 2019" Unit="UTC"/>
	  <!--The Sample information holds for the whole recording-->
	  <Sample>
	    <Samplerate Value="2500000" Unit="Hz"/>
	    <Channels Bits="12" Container="int16" Ordering="LSB">
	      <Channel Value="I"/>
	      <Channel Value="Q"/>
	    </Channels>
	  </Sample>
	  <!--Here follow one or more data blocks-->
	  <Datablocks>
	    <Datablock Number="1" Count="375783424" Unit="Channel">
	      <Frequency Value="227360" Unit="KHz"/>
	      <Modulation Value="DAB"/>
	    </Datablock>
	  </Datablocks>
	</SDR>

 ```

The device handlers in Qt-DAB support the generation of 
such an xml file.

While the current implementation for reading such files is limited to
a single data block, the reader contains a *cont* button that, when
touched while playing the data, will cause continuous playing of the
data in the data block.

![Qt-DAB with xml input](/qt-dab-xml.png?raw=true)

The picture shows the reader when reading a file, generated from raw
data emitted by the Hackrf device.

----------------------------------------------------------------------
EPG-Handling
----------------------------------------------------------------------

In Qt-DAB a first step is made to implement support for
EPG (Electronic Program Guide).

In the current implementation, an EPG Handler is automatically started
whenever within an ensemble a service is recognized as carrier of
EPG data.
The handler will collect information about the program guides for the
various services, and when collected, allow the user to view it
(it will take some time to have the relevant data collected).

Whenever the software has collected time table information of
a given service, the technical Data widget will show, when selecting
the service, a button labeled **timeTable** .

![epg data](/qt-dab-epg-data.png?raw=true)

The software is experimental though and - at least here - the times
on the time table are two hours off.

----------------------------------------------------------------------
Recording the dynamic label text (new in 4.0)
----------------------------------------------------------------------

Touching the "dlText" button will show a menu for file selection and
will instruct the software to record the text fragments sent as
dynamic label text. The texts are prefixed with the channel, the
name of the service and the data of recording.

	9D.Omroep Zeeland   2021-07-24 16:20:00  Je luistert naar Omroep Zeeland
	9D.Omroep Brabant   2021-07-24 16:20:00  Omroep Brabant: De Platenbeld
	9D.RADIONL Zeeland  2021-07-24 16:21:00  RADIONL - ALTIJD AAN!
	9D.Radio Rijnmond   2021-07-24 16:21:00  Radio Rijnmond
	9D.Omroep Zeeland   2021-07-24 16:21:00  In heel Zeeland de eerste keus voor nieuws en muziek

As usual, touching the button a second time will close the file

-----------------------------------------------------------------------
Recording the SNR
-----------------------------------------------------------------------

Just as an experiment, a widget was added that shows the development of the 
SNR over time. The main purpose of the widget is to look at the
performance of antennas. 

Computation of the SNR is done with all DAB frames. As is known,
a sampled DAB frame starts with a null period of app 2600 samples, followed by
76 blocks (each about 2500 samples) with data. SNR is computed as the ratio between the amplitudes in the data blocks and the amplitudes of the
samples in the null period.

For every second DAB frame, such a computation is performed, 
and, depending on the settings, shown.
The configuration widget contains a spinbox that can be used to set the
"speed" of displaying data.
If the value "1" is chosen, the result of each snr computation is shown,
if a value larger than "1" is chosen that number of computations will be
averaged and the result shown.
The default value for the X-axis of the display in the widget is 312.

As configuration option, the widget can be equipped with a **dump** button,
touching the button will show a menu for file selection. Once a file
is selected, the results of the computations are not only shown, but recorded
in the file as well.

To view the recording, a simple utility is made to make the contents
of the recording visible. Sources for the utility are to be found
in the (sub)directory **dumpviewer**.

![dumpViewer](/dumpViewer.png?raw=true)

The picture shows the variations in the SNR when moving the antenna
and - the dip - when switching antennas.

----------------------------------------------------------------------
Scanning and the skip table
----------------------------------------------------------------------

As known, Qt-DAB provides a possibility of scanning the band. Band III
contains 39 channels, so - depending on your position - there is
quite a number of channels where no DAB signal is to be found.

As in **dabChannel**, Qt-DAB has an extended mechanism to skip
specified channels during a scan, a **skipTable**.
The configuration widget contains a button to make the **skipTable**
visible. The skipTable shows all channels in the selected band, 
each channel labeled with a field containing a "+" or a "-" sign.
Double clicking on the field will invert its setting.
Obviously. such a skipTable will be maintained between program invocations.

When DX-ing, one wants to direct the antenna to different countries
in different directions.
Ideally there is a skipTable for each direction, and
Qt-DAB supports that.
The configuration widget contains a button **skipFile**,
when touched a file selection menu appears where one can select a skipfile.
**If the file does not exist yet, it will be created.**
If one cancels the file selection, the default skipTable will be used,
the same table that is used when no skipFile is selected.

-----------------------------------------------------------------------
# PLuto device and fm transmission
-----------------------------------------------------------------------

As (probably) known, the **Adalm Pluto** device has receive and transmit
capabilities. In a previous project, an extension was made to a
dab-cmdline version using the Adalm pluto device,
to allow the transmission on FM of a preselected
service.

As an exercise - and slightly experimental - the functionality was
added to qt-dab.

If - on configuration - pluto-rxtx is taken as device rather than
pluto, and if pluto-rxtx is selected as device, the audio
of the selected service, augmented with the text of the dynamic label
encoded as RDS signal, will be transmitted on a specified frequency.

As default, the transmit frequency is 110 MHz, however, the user can specify
the frequency (obviously within the range supported by the Adalm-Pluto)
as command line parameter: starting the program from the command line
with as parameter

	-F XXX

will instruct the software to start the
transmitter of the Adalm pluto - if the pluto-rxtx is the selected device -
on the given frequency (specified in KHz)

![dab2fm](/dab2fm.png?raw=true)

-----------------------------------------------------------------------
# Copyright
------------------------------------------------------------------------

	Copyright (C)  2016 .. 2021
	Jan van Katwijk (J.vanKatwijk@gmail.com)
	Lazy Chair Computing

	The Qt-DAB software is made available under the GPL-2.0.
	The SDR-J software, of which the Qt-DAB software is a part, 
	is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

