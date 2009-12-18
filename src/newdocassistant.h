/***************************************************************************
                 new doc assistant - widget to select Addresses
                             -------------------
    begin                : 2008-02-12
    copyright            : (C) 2008 by Klaas Freitag
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

#ifndef NEWDOCASSISTANT_H
#define NEWDOCASSISTANT_H

#include <QMap>
#include <QLabel>

#include <kabc/addressee.h>
#include <kassistantdialog.h>

class KComboBox;
class FilterHeader;
class AddressSelection;
class KPushButton;
class DocText;
class TextSelection;
class KDateWidget;
class KraftWizard;
class KTextEdit;
class KHBox;
class KPageWidgetItem;

using namespace KABC;


// ---------------------------------------------------------------------------

class CustomerSelectPage: public QWidget
{
  Q_OBJECT

  friend class KraftWizard;

public:
  CustomerSelectPage( QWidget *parent = 0 );
  ~CustomerSelectPage();

signals:
  void addresseeSelected( const Addressee& );
  void startAddressbook();
private:
  AddressSelection *mAddresses;
};

// ---------------------------------------------------------------------------

class DocDetailsPage : public QWidget
{
  Q_OBJECT

  friend class KraftWizard;

public:
  DocDetailsPage( QWidget *parent = 0 );
  ~DocDetailsPage();

private:
  QLabel      *mCustomerLabel;
  KDateWidget *mDateEdit;
  KComboBox   *mTypeCombo;
  KTextEdit   *mWhiteboardEdit;
};

// ---------------------------------------------------------------------------

class KraftWizard: public KAssistantDialog
{
  Q_OBJECT

public:
  KraftWizard(QWidget *parent = 0, const char* name = 0, bool modal = FALSE );
  void init();

  ~KraftWizard();

  QDate date() const ;
  QString addressUid() const;
  QString docType() const;
  QString whiteboard() const;
  void setCustomer( const QString& );
  void setDocIdentifier( const QString& );
  void setAvailDocTypes( const QStringList& );

protected slots:
  void slotAddressee( const Addressee& );
  void slotStartAddressbook();

private:
  CustomerSelectPage *mCustomerPage;
  DocDetailsPage *mDetailsPage;
  KHBox *mCustomerBox;
  QWidget *mParent;

  KPageWidgetItem *mCustomerPageItem;
  KPageWidgetItem *mDetailsPageItem;
};

#endif
