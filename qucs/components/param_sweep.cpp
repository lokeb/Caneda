/***************************************************************************
                          param_sweep.cpp  -  description
                             -------------------
    begin                : Sat Aug 23 2003
    copyright            : (C) 2003 by Michael Margraf
    email                : michael.margraf@alumni.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "param_sweep.h"
#include "../main.h"


Param_Sweep::Param_Sweep()
{
  Description = QObject::tr("Parameter sweep");

  QString  s = Description;
  s.replace(" ","\n");
  QFontMetrics  metrics(QucsSettings.largeFont);
  QSize r = metrics.size(0, s);
  int xb = (r.width()  >> 1) + 6;
  int yb = (r.height() >> 1) + 4;

  Lines.append(new Line(-xb,-yb, xb,-yb,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-xb, yb, xb, yb,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-xb,-yb,-xb, yb,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( xb,-yb, xb, yb,QPen(QPen::darkBlue,2)));

  Lines.append(new Line(-xb+5, yb+5, xb+4, yb+5,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-xb,   yb,  -xb+5, yb+5,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( xb,   yb,   xb+4, yb+5,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( xb+4,-yb+5, xb+4, yb+5,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( xb,  -yb,   xb+4,-yb+5,QPen(QPen::darkBlue,2)));

  x1 = -xb-4; y1 = -yb-4;
  x2 =  xb+8; y2 =  yb+9;

  tx = x1+8;
  ty = y2+4;
  Model = ".SW";
  Name  = "SW";

  Props.append(new Property("Sim", "", true,
		QObject::tr("simulation to perform parameter sweep on")));
  Props.append(new Property("Type", "lin", true,
		QObject::tr("sweep type")+" [lin, log]"));
  Props.append(new Property("Param", "R1", true,
		QObject::tr("parameter to sweep")));
  Props.append(new Property("Start", "5 Ohm", true,
		QObject::tr("start value for sweep")));
  Props.append(new Property("Stop", "50 Ohm", true,
		QObject::tr("stop value for sweep")));
  Props.append(new Property("Points", "20", true,
		QObject::tr("number of simulation steps")));
}

Param_Sweep::~Param_Sweep()
{
}

Component* Param_Sweep::newOne()
{
  return new Param_Sweep();
}

Component* Param_Sweep::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("Parameter sweep");
  BitmapFile = "sweep";

  if(getNewOne)  return new Param_Sweep();
  return 0;
}
