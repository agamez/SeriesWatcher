/*
 * Copyright (C) 2010 Corentin Chary <corentin.chary@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <QtSql/QSqlRecord>
#include <QtCore/QDateTime>
#include <QtGui/QPixmap>
#include <QtGui/QIcon>

#include "tvdbcache.h"
#include "showmodel.h"

ShowModel::ShowModel(TvDBCache *c, QObject *parent)
  : QSqlQueryModel(parent), cache(c)
{
  /* next episode, number of season */
  setQuery("SELECT shows.name, shows.id, COUNT(DISTINCT episodes.id) as episodes, "
	   "COUNT(DISTINCT episodes.season) as seasons, banners.id as bannerId "
	   "FROM shows "
	   "LEFT JOIN banners ON (shows.id = banners.showId AND banners.type = 'poster' "
	   "AND banners.language = 'en') "
	   "LEFT JOIN episodes ON shows.id = episodes.showId "
	   "GROUP BY shows.id");
}

QVariant ShowModel::data(const QModelIndex &index, int role) const
{
  if (role >= Qt::UserRole) {
    QSqlRecord rec = record(index.row());

    if (role == ShowModel::Id)
      return rec.value("id").toInt();
    if (role == ShowModel::Seasons)
      return rec.value("seasons").toInt();
    if (role == ShowModel::NextEpisode)
      return QDateTime();
    if (role == ShowModel::Episodes)
      return rec.value("episodes").toInt();
    if (role == ShowModel::EpisodesNotWatched)
      return rec.value("episodes").toInt();
  }

  QVariant value = QSqlQueryModel::data(index, role);

  if (role == Qt::DisplayRole)
    return value.toString();
  if (role == Qt::DecorationRole)
    return QIcon(cache->fetchBannerFile(record(index.row()).value("bannerId").toInt(), TvDBCache::Poster));
  return value;
}
