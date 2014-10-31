#pragma once
/*
 *      Copyright (C) 2005-2012 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "kodi/util/StdString.h"

#include <boost/shared_ptr.hpp>

extern "C" {
#include <cmyth/cmyth.h>
};

template <class T> class MythPointer;

class MythTimestamp
{
public:
  friend class MythConnection;

  MythTimestamp();
  MythTimestamp(cmyth_timestamp_t cmyth_timestamp);
  MythTimestamp(CStdString time);
  MythTimestamp(time_t time, bool utc);

  bool operator==(const MythTimestamp &other);
  bool operator!=(const MythTimestamp &other) { return !(*this == other); }
  bool operator>(const MythTimestamp &other);
  bool operator>=(const MythTimestamp &other) { return (*this == other || *this > other); }
  bool operator<(const MythTimestamp &other);
  bool operator<=(const MythTimestamp &other) { return (*this == other || *this < other); }

  bool IsNull() const;

  time_t UnixTime();
  CStdString String();
  CStdString IsoString();
  CStdString DisplayString(bool use12hClock);
  CStdString NumString();

  bool IsUTC();
  MythTimestamp ToUTC();

private:
  boost::shared_ptr<MythPointer<cmyth_timestamp_t> > m_timestamp_t;
};
