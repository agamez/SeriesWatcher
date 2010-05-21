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

#ifndef TVDB_CACHE_H
# define TVDB_CACHE_H

#include <QtSql/QSqlDatabase>

#include <QtTvDB>

class TvDBCache
{
public:
  enum BannerType { Poster, Banner, Search, Episode };

  TvDBCache(const QString & name = QLatin1String(QSqlDatabase::defaultConnection));
  ~TvDBCache();

  void storeShow(QtTvDB::Show *show);
  void storeShows(QList < QtTvDB::Show * > shows);
  void storeEpisode(QtTvDB::Episode *episode);
  void storeEpisodes(QList < QtTvDB::Episode * > episodes);
  void storeBanner(QtTvDB::Banner *banner, qint64 showId);
  void storeBanners(QList < QtTvDB::Banner * > banners, qint64 showId);
  void storeBannerFile(qint64 id, BannerType type, const QByteArray &data);

  QtTvDB::Show *fetchShow(qint64 id);
  QList < QtTvDB::Show * > fetchShows();

  QtTvDB::Episode *fetchEpisode(qint64 id);
  QList < QtTvDB::Episode * > fetchEpisodes(qint64 showId, qint64 seasonId = -1);

  QtTvDB::Banner *fetchBanner(qint64 id);
  QList < QtTvDB::Banner * > fetchBanners(qint64 showId);

  bool hasBannerFile(qint64 id, BannerType type);
  QPixmap fetchBannerFile(qint64 id, BannerType type);
  QString name();
  void sync();

 private:
  bool connectDb(const QString & name = QLatin1String(QSqlDatabase::defaultConnection));
  QtTvDB::Show *showFromRecord(QSqlRecord record);
  QtTvDB::Episode *episodeFromRecord(QSqlRecord record);
  QtTvDB::Banner *bannerFromRecord(QSqlRecord record);

 private:
  QString bannerPath(qint64 id, BannerType type);

  QSqlDatabase db;
  QString dbName;
};

#endif
