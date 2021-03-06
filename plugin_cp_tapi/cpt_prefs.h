#ifndef TAPI_PREFS_H_INCLUDED
#define TAPI_PREFS_H_INCLUDED

// This file is part of c'mon, a lightweight telephony monitor.
//
// Copyright (C) 2012 Peter Schaefer-Hutter ("THE AUTHOR")
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

// ----------------------------------------------------------------------------
// NOTE: This License does NOT permit incorporating this file (or parts or
//       changed versions of it) into proprietary programs that are
//       distributed to third-parties in binary form only.
// ----------------------------------------------------------------------------

// You can contact the original author by email at peter.schaefer@gmx.de
// if you need different license-terms or other modifications to c'mon.

// $Revision: 10 $ $Date: 2012-09-21 21:35:29 +0200 (Fri, 21 Sep 2012) $

#include "wx/wx.h"
#include "wx/config.h"
#include "wx/string.h"

// --------------------------------------------------------------------

#include <vector>

// --------------------------------------------------------------------

class IPrefChangeListener
{
  public:
    IPrefChangeListener() {  }
    virtual ~IPrefChangeListener() {  }

    virtual void OnPrefChange() = 0;
};

// --------------------------------------------------------------------

class CPTPREFS;
class CCptGui;

typedef std::vector<unsigned> TPrefLines;

class CCptPrefs
{
public:
  CCptPrefs();

  const TPrefLines& getSelectedLines() const      { return m_vSelectedLines;   }

  bool operator==(const CCptPrefs& r) {
    return (m_vSelectedLines == r.m_vSelectedLines);
  }

protected:
  TPrefLines m_vSelectedLines;

  friend class CPTPREFS;
  friend class CCptGui;
};

// --------------------------------------------------------------------

class CPTPREFS
{
  public:
    static void init();
    static void free();

    static CCptPrefs&  getPrefs();
    static void        readPrefs();
    static void        savePrefs();

    static void registerListener(IPrefChangeListener *);
    static void unregisterListener(IPrefChangeListener *l);
    static void notify();

  protected:
    static void readLines();
    static void saveLines();

  private:
    static CCptPrefs                     m_Prefs;
    static wxConfig                      *m_pConfig;
    static std::vector<IPrefChangeListener*> m_Listeners;

    CPTPREFS() {};
    ~CPTPREFS() {};
};

#endif /* TAPI_PREFS_H_INCLUDED */
