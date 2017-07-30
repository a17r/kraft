/***************************************************************************
                                docdigest.cpp
                             -------------------
    begin                : Wed Mar 15 2006
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

#include <QString>
#include <QLocale>

#include <kcontacts/addressee.h>

#include "docdigest.h"
#include "defaultprovider.h"

DocDigest::DocDigest( dbID id, const QString& type, const QString& clientID )
  :mID(id), mType( type ), mClientId( clientID ), mLocale( "kraft" )
{

}

DocDigest::DocDigest()
  :mLocale( "kraft" )
{
}

QString DocDigest::date() const
{
    return mDate.toString();
  // return mLocale.formatDate( mDate, QLocale::ShortDate );
}

QDate DocDigest::rawDate() const
{
    return mDate;
}

QString DocDigest::lastModified() const
{
    return mLastModified.toString();
}

void DocDigest::appendArchDocDigest( const ArchDocDigest& digest )
{
    mArchDocs.append( digest );
}

ArchDocDigestList DocDigest::archDocDigestList()
{
    return mArchDocs;
}

void DocDigest::setCountryLanguage( const QString& country, const QString& lang )
{

    // FIXME KF5 porting - how to do this?
#if 0
    KConfig *cfg = KGlobal::config().data();
    mLocale.setCountry( country, cfg );
    mLocale.setLanguage( lang, cfg ); // FIXME !!
#endif
}

KContacts::Addressee DocDigest::addressee() const
{
  return mContact;
}
void DocDigest::setAddressee( const KContacts::Addressee& contact )
{
  mContact = contact;
}


/* *************************************************************************** */

DocDigestsTimeline::DocDigestsTimeline()
  :mMonth( 0 ), mYear( 0 )
{

}

DocDigestsTimeline::DocDigestsTimeline( int m,  int y )
  :mMonth( m ), mYear( y )
{

}

void DocDigestsTimeline::setDigestList( const DocDigestList& list )
{
  mDigests = list;
}
