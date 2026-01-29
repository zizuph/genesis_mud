/* A bee keepers suit; protects wearer from sting of honey bees
** in room/bk_treeX.c
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           5/18/98  Created
**
** Converted to wearable_item to allow minotaur usage and the nuisance of
** handling armours
** Tapakah, 07/2021
**/

#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "../village.h"

inherit "/std/object";
inherit "/lib/wearable_item";

void
create_object ()
{
  set_name("suit");
  add_name(BEE_KEEPER_SUIT);
  add_adj(({"new","leather","beekeepers","beekeeper's"}));
  set_short("beekeepers suit");
  set_long("It is a new leather beekeepers suit which covers the "+
           "entire body of the wearer, including a round large-brimmed "+
           "hat with a net over the head and attatched gloves.\n");
  set_looseness(4);
  set_slots(TS_HBODY|TS_RHAND|TS_LHAND);
  add_prop(OBJ_I_VALUE, 100);
  add_prop(OBJ_I_VOLUME, 7000);
  add_prop(OBJ_I_WEIGHT, 7000);
}
 
//
// check_bees - cause any bees in the room to attack - invoked when removed
//
void check_bees ()
{
  object rm, env=ENV(TO), *inv;
  int    i;
 
  // find the room
  if (env->query_prop(ROOM_I_IS))
    rm=env;
  else if (env->query_prop(LIVE_I_IS))
    rm=ENV(env);
  else
    return;
 
  // check the room for bees and invoke init_attack() in any found
  inv=all_inventory(rm);
  for (i=0; i<sizeof(inv); i++)
    if ((inv[i])->query_prop(BK_BEE))
      (inv[i])->init_attack();
}
 
int
remove (object obj)
{
  set_alarm(1.0,0.0,&check_bees());
  return 0; // remove normally
}
