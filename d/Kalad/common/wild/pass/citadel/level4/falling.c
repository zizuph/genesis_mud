/*
 * Made by Korat
 * may 1996
 * A room where all players will fall downwards and be moved out of it.
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   set_short("You are falling down a shaft");
   set_long("You are falling down a shaft!\n");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_item("shaft","You want to examine the shaft??? "+
      "Really ... right now you are just hoping this fall won't "+
      "kill you. Ohwell, the shaft has stonewalls that just are "+
      "too smooth for you to hang onto it. Nice try though.\n");
}

void
init()
{
   ::init();

   TP->catch_msg("You hit your head on something during your "+
      "fall downwards!\n");
   set_alarm(2.0,0.0,"do_fall",TP);
}

void
do_fall(object player)
{
   player->catch_msg("You are gaining an incredible speed, and regularly bump "+
      "into the walls of the shaft!\n");
   set_alarm(4.0,0.0,"do_land",player);
}

void
do_land(object player)
{
   object stun;
   player->catch_msg("You hit the bottom hard! Ouch!!\n");
   player->heal_hp(-(player->query_hp()/4)); /* take away 1/4 of hp left */
   player->move_living("arrives falling from the shaft in the ceiling",
      CPASS(citadel/level1/a3));
   player->catch_msg("You feel dazed from the hard hit you took from the fall.\n");
   clone_object("/d/Kalad/common/wild/pass/citadel/obj/stun")->move(player);
   tell_room(E(player),QCTNAME(player)+" hits the floor hard, and looks very "+
      "dazed.\n",player);
}
