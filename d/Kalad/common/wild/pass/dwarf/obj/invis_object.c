inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>

int firstalarm;

/* made by Korat */
/* This object is the spell-object that the priest's clode
moves to the players. It works only as long as the player
does not fight anyone/anything. It also stops after some time */

void
create_object()
{
   ::create_object();
   set_name("invis_object");
   set_long("an object that will invis the carrier.\n");
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_INVIS, 99);
   add_prop(OBJ_I_NO_DROP,1);
   firstalarm=set_alarm(2.0,10.0,"check_fighting");
   set_alarm(1.0,0.0,"start_invis");
   set_alarm(1200.0,0.0,"stop_invis");
}


void
stop_invis()
{
   tell_room(E(E(TO)),QCTNAME(E(TO))+" suddenly stands next to you!\n");
   E(TO)->catch_msg("You suddenly feel yourself turning visible again!\n");
   E(TO)->remove_prop(OBJ_I_INVIS);
   remove_object();
}

void
start_invis()
{
   tell_room(E(E(TO)),"A ghostly figure seems to rise out of the thin "+
     "air. Slowly it drifts towards "+QCTNAME(E(TO))+"...\n");
   E(TO)->add_prop(OBJ_I_INVIS,1);
}


void
check_fighting()
{
   object killing;
   killing = E(TO)->query_attack(id(E(TO)));
   if(killing)
      {
      E(TO)->catch_msg("You feel that the spell starts to fade in power.\n");
      remove_alarm(firstalarm);
      set_alarm(1.0,0.0,"stop_invis");
   }
}

