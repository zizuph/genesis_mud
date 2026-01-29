/*
 * Daenbraigh base file for common inheritance needs
 */

#pragma strict_types

#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";
#include "daenbraigh.h"
#include "faction.h"

inherit "/d/Khalakhor/std/monster";
inherit FACTION;

int
check_aggression()
{
  int align = TP->query_alignment();
  string race = TP->query_race_name();
  
  if(TP->query_wiz_level())
    return 0;
  return 0; // until factions are implemented
  if(align > 0)
    return 1;
  if(TP->query_prop(GV_ENEMY))
    return 1;
  switch(race)
    {
    case "elf":
    case "hobbit":
      return 1;
      break;
    case "goblin":
      return 0;
      break;
    default:
      if(align > 400)
	return 1;
      else
	return 0;
    }
}

varargs void
set_faction(string faction, int alignment, object who = TO)
{
  mixed factiondata;
  
  factiondata = who->query_prop(FACTION);
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
  return who->query_prop(FACTION);
}

varargs int
query_this_faction(string this_faction, object who = TO)
{
  mixed factiondata;
  string *faction;

  factiondata = who->query_prop(FACTION);
  if(factiondata) {
    faction = m_indices(factiondata);
    return IN_ARRAY(this_faction,faction) ? factiondata[this_faction] : 0;
  }
  return 0;
}

void
attacked_by(object enemy)
{
  mixed myfactiondata;
  mixed enemyfactiondata;
  mapping fdata;
  string *faction;
  string *enemyfaction;
  int f,fs,ef;
  
  myfactiondata = query_faction();
  if(myfactiondata) {
    faction = m_indices(myfactiondata);
    fs = sizeof(faction);
    enemyfactiondata = enemy->query_prop(FACTION);
    if(enemyfactiondata) {
      enemyfaction = m_indices(myfactiondata);
      for(f=0;f<fs;f++)
	if(IN_ARRAY(faction[f],enemyfaction)) 
	  enemyfactiondata[faction[f]] -= myfactiondata[faction[f]];
	else 
	  enemyfactiondata += ([faction[f]:-myfactiondata[faction[f]]]);
      enemy->add_prop(FACTION,enemyfactiondata);
    }
    else {
      fdata = ([]);
      for(f=0;f<fs;f++)
	fdata += ([faction[f]:-myfactiondata[faction[f]]]);
      enemy->add_prop(FACTION,fdata);
    }
  }
  ::attacked_by(enemy);

}
