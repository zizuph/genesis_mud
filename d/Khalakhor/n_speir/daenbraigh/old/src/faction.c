/*
 * faction routines
 */

#pragma strict_types

#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";
#include "daenbraigh.h"
#include "faction.h"

varargs void
set_faction(string faction, int alignment, object who = TO)
{
  mixed factiondata;
  
  factiondata = who->query_prop(FACTION_PROP);
  if(factiondata) {
    if(IN_ARRAY(faction,m_indices(factiondata))) 
      factiondata[faction] = alignment;
    else 
      factiondata += ([faction:alignment]);
  }
  else
    factiondata = ([faction:alignment]);
  who->add_prop(FACTION,factiondata);
}

varargs mixed
query_faction(object who = TO)
{
  return who->query_prop(FACTION_PROP);
}

varargs int
query_this_faction(string this_faction, object who = TO)
{
  mixed factiondata;
  string *faction;

  factiondata = who->query_prop(FACTION_PROP);
  if(factiondata) {
    faction = m_indices(factiondata);
    return IN_ARRAY(this_faction,faction) ? factiondata[this_faction] : 0;
  }
  return 0;
}
