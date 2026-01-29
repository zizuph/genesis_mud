inherit "/std/paralyze";
#include "/d/Kalad/defs.h"
/* by korat */
void
create_paralyze()
{
   set_name("stun");
   set_long("A paralyze.\n");
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_INVIS, 99);
   add_prop(OBJ_I_NO_DROP,1);
   set_remove_time(20);
   set_stop_verb("slutt");
   set_fail_message("You are paralyzed from fright!\n");
   set_stop_message("You feel your blood starting to flow again.\n");
}

