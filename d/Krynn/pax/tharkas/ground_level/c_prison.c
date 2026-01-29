/*
   Pax Tharkas, Ground level, Childrens prison.

   c_prison.c
   ----------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/05/06
   By ...........: Jeremiah


   In here the players will find the little girl that is necessary to 
   solve the quest, freeing the prisoners. Her mother has to be 
   present in this room, or she won't follow the player.

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

object quest_npc_girl;


void
reset_pax_room()
{
   if(objectp(quest_npc_girl))
      return;

   quest_npc_girl = clone_object(PMONSTER + "girl");
   quest_npc_girl->move_living("stands up.", TO);
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("Childrens prison");
   set_long("You are in a dimly lit and badly ventilated room. The air " +
            "in here feels heavy and damp. Straw mats line the walls " +
            "and cover most of the floor. Small bundles of clothes lie " +
            "next to each mat. The " +
            "room is filled with children sitting or standing in small " +
            "groups. They are all staring wide eyed at you.\n");

   INSIDE;

   add_item(({"mat", "mats", "straw mats"}), "Rude straw mats. They look " +
           "more like old sacks filled with straw, than actual " +
           "matresses.\n");	

   add_item(({"bundles", "clothes"}), "Little bundles of clothings. They " +
            "look like rolled up cloaks and other extra clothings.\n");

   add_item(({"child", "children"}), "Children of almost all ages. They " +
            "are poorly dressed and most of them look undernourished. " +
            "They stare at you with a look of surprise on their little " +
            "faces.\n");
 
   add_exit(GROUND_LEVEL + "nurseroom", "southwest",0);
}
