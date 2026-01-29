// -*-C++-*-
// file name: infidel
// creator: Ilyian (September 9, 1995)
// last update:
// purpose: Inheritable room for all /bazaar/infidel/* rooms
// note: 
// bug(s):
// to_do:

inherit "/std/room";

#include "infidel.h"

int guard_exit()
{
    object guard;
    object player;

    player = TP;
    guard = present("avenir_infidel_id", TO);

    if(!guard || !interactive(player))
        return 0;

    if(CAN_SEE(guard,player) && CAN_SEE_IN_ROOM(guard) &&
      player->query_prop("_live_i_attacked_infidel_guard") )
        {
          if(player->query_stat(SS_DEX) > random(300) + 50)
             {
               player->catch_msg("You manage to slip past "
                   +QTNAME(guard)+".\n");
               tell_room(ENV(player), QCTNAME(player)
                   +" manages to slip past "+QTNAME(guard)
                   +".\n", player);
               return 0;
              }
           else
             {
               player->catch_msg(QCTNAME(guard)+" stands in "
                    +"your way, blocking that exit.\n");
               tell_room(ENV(player), QCTNAME(guard)
                   +" stops "+QTNAME(player)
                   +" from leaving.\n", player);
               return 1;
              }
          }
     return 0;
}


/* 
 *************************************************
 * Some small functions to make adding exits to these
 * areas easier.
 ***************************************************
 */
void
hall_exit(string where, string dir)
{
   add_exit(INFID+"hall"+where,dir,"@@guard_exit@@",1);
   AI((dir),"The hall extends into darkness. You cannot make anything "
         +"out further down the hall.\n");
}

void
quar_exit(string where, string dir)
{
   add_exit(INFID+"quar"+where,dir,0,1);
   AI(({"room","quarter",dir}),"You cannot tell what is in the room "
        +"from here.\n");
   AI(({"rooms","quarters"}),"You cannot tell what is in the rooms "
        +"from here.\n");
}

/* 
 ***************************************************
 * Now some functions to create the rooms.
 ***************************************************
 */
void
hall_long(string desc)
{
  set_short("hallway");
  set_long("This is a narrow dingy hallway, held up by "
              +"tall wooden support beams. The floor is of "
              +"rough-hewn rock, as are the walls. "+desc+"\n");
   AI(({"floor","ground"}),"The floor looks like it was carved from "
              +"hard granite base of the island. It is rough and uneven, "
              +"and here and there are some traces of feldspar.\n");
   AI(("feldspar"),"The small traces of feldspar are dark and glittering.\n");
   AI(({"wall","walls"}),"The walls of the hallway are made from the "
              +"granite base of the island. They are marked with deep "
              +"scars from the tools that were used to chisel out the "
              +"hall. Heavy wooden beams run up the walls to support "
              +"the ceiling overhead.\n");
   AI(({"scars","marks","scar"}),"They are the reminants of the "
              +"heavy tools that must have been used in digging out "
              +"this hallway.\n");
   AI(({"ceiling","roof"}),"The ceiling overhead is also of granite, and "
              +"is supported by heavy wooden beams that run along the "
              +"walls.\n");
   AI(({"beam","beams","wooden beams","wooden beam","wood"}),"The "
              +"heavy beams run from the floor to the ceiling. They seem to "
              +"be made from some dark and strong oak.\n");

   add_prop(ROOM_I_LIGHT,1);
   IN;
   IN_IN;  // defined in /d/Avenir/common/common.h
}

void
quar_long(string desc)
{
   set_short("quarters");
   set_long("These seem to be some sort of quarters for the inhabitants "
              +"of the area. "+desc+"\n");
   add_prop(ROOM_I_LIGHT,1);

   IN;
   IN_IN;
}
