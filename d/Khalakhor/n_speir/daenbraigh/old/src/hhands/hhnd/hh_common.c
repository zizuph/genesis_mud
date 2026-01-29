/*
 * Hammerhand guild common routines
 * TAPAKAH, 11/2005
 */

#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "/d/Khalakhor/sys/defs.h"
#include "../../daenbraigh.h"
#include "../hhands.h"
#include "hh_guild.h"

int
hh_wep_skill(object who, int wep_type)
{
  int skill;

  skill = 0;
  foreach(int this_weapon_type: HH_WEAPON_TYPES)
    if(wep_type == this_weapon_type &&
       who->query_skill(this_weapon_type) >= HH_SKILL)
      return skill;
  return 0;
}

int
hh_valid_weapon(object weapon)
{
  return weapon->query_dt() & W_BLUDGEON;
}

object *
hh_parse_command(string command)
{
  object *weplist,weapon,target;

  string wep,verb;
  int i,wps;

  verb = query_verb();
  notify_fail(capitalize(verb) + " what [at whom?]\n");
  if (command)
    if (!parse_command(command,ENV(TP),"%s 'at' [the] %o",wep,target))
      if(!parse_command(command,ENV(TP),"%s",wep)) 
	return ({});

  if(!command) {
    weplist = TP->query_weapon(-1);
    for(i=0;i<sizeof(weplist);i++)
      if(! hh_valid_weapon(weplist[i]))
	weplist -= ({weplist[i]});
    if (!sizeof(weplist))
      return ({});
  }
  else {
    weplist = FIND_STR_IN_OBJECT(wep, TP);
    if (!sizeof(weplist))
      return ({});
    
    if (sizeof(weplist) > 1)    {
      NF("You can only " + verb + " one weapon at a time.\n");
      return ({});
    }
  }
  weapon = weplist[0];

  if (! hh_valid_weapon(weapon)) {
    NF("You can only "+ verb + " a bludgeon.\n");
    return ({});
  }
      
  if (!(weapon->query_wielded()) ||
      weapon->query_wielded() != TP) {
    NF("You are not wielding the " + weapon->short() + ".\n");
    return ({});
  }

  if (! hh_
  if(target)
    return ({weapon, target});
  else
    return ({weapon});
}
