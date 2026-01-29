/*
 * Sceptre from Port Macdunn.
 * TAPAKAH, 10/2005
 * Holding it increases player's discipline
 */

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../../faction.h"

inherit "/d/Khalakhor/std/object";
inherit "/lib/holdable_item";
inherit FACTION;

#define V_SCEPTRE_MOD 1.2

void
create_khalakhor_object()
{
  if(!IS_CLONE)
    return;
  ::create_khalakhor_object();

  set_name("sceptre");
  add_name(V_OBJID + "sceptre");
  
  set_adj(({"oblong","wolf-headed"}));
  set_short("oblong wolf-headed sceptre");
  set_long("An oblong wolf-headed sceptre lords of Khalakhor humans held.");
  
  add_prop(OBJ_I_VOLUME, 250);
  add_prop(OBJ_I_WEIGHT,1250);
  add_prop(OBJ_I_VALUE,  550);
  add_prop(OBJ_S_WIZINFO,
	   "Increases holder's discipline by 20% for holders of Human/Elven "+
	   "faction.\n");

  set_slots(W_ANYH);
}

mixed
hold()
{
  int modifier;

  if(query_this_faction(FACTION_PORTMACDUNN) > 0 ||
     query_this_faction(FACTION_SAMORGAN) > 0) {
    write("You feel more confident as you hold the sceptre.\n");
    modifier = ftoi(itof(TP->query_stat(SS_DIS))*V_SCEPTRE_MOD);
    TP->set_stat_extra(
		       SS_DIS,
		       modifier
		       );
  }
  return 1;
}

mixed
release()
{

  if(query_this_faction(FACTION_PORTMACDUNN) > 0 ||
     query_this_faction(FACTION_SAMORGAN) > 0) {
    write("You feel less confident as you release the sceptre.\n");
    TP->set_stat_extra(
		       SS_DIS,
		       0,
		       );
  }
  return 1;
}
