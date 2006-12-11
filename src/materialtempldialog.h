/***************************************************************************
             materialtempldialog  -
                             -------------------
    begin                : 2006-12-04
    copyright            : (C) 2006 by Klaas Freitag
    email                : freitag@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _MATERIALTEMPLDIALOG_H
#define _MATERIALTEMPLDIALOG_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files
#include <klocale.h>

#include "kraftglobals.h"
#include "materialdialog.h"
#include "stockmaterial.h"
/**
 *
 */
class Katalog;

class MaterialTemplDialog : public MaterialDialogBase
{
    Q_OBJECT

public:
    MaterialTemplDialog(QWidget *parent=0, const char* name=0, bool modal=false, WFlags fl=0);
    ~MaterialTemplDialog();

    void setMaterial( StockMaterial* t, const QString&, bool );
    bool templateIsNew() {
      return m_templateIsNew;
    };
signals:
    void editAccepted( StockMaterial* );
    void editRejected();
    void chapterChanged(int);

public slots:

protected slots:
  virtual void accept();
  virtual void reject();

  void slSalePriceChanged( double );
  void slPurchPriceChanged( double );
  void slSaleAddChanged( double );

private:
  bool askChapterChange( StockMaterial*, int);
  void setPriceCalc( double, double, double );

  StockMaterial *mSaveMaterial;
  bool m_templateIsNew;
  Katalog *m_katalog;
  const double Eta;
};

#endif

/* END */
