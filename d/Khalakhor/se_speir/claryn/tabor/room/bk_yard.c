/*
 * bk_yard.c
 *
 * Front yard of the bee keeper's home
 *
 * Zima - May 16, 98
 */
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#include <macros.h>
#include <stdproperties.h>
#include "room.h"
inherit "/d/Khalakhor/std/room";
 
int    pots=3;
 
void reset_room() { pots=3; }
 
public void create_khalakhor_room()
{
   set_short("In the yard of a rural home");
   set_long("   You are standing the yard of a rural home in the low grass-"+
            "covered hills outside the village of Tabor Sogh. A small "+
            "house with a thatched roof stands just to the south, "+
            "where there is a heap of broken pottery piled next to "+
            "the stone wall of the dwelling. There is a small stand "+
            "of trees to the northeast, while the trail leading into "+
            "the village is to the northwest. You notice a small note "+
            "pegged to the doorpost of the home.\n");
 
   BEES; // bees will follow victim into yard
 
   add_item(({"heap of broken pottery","pile","pottery","broken pottery",
      "trash","heap"}),
      "It is just a heap of broken pottery, carelessly discarded but "+
      "neatly piled up next to the wall of the home. It looks like "+
      "it might also serve as a trash pile.\n");
   add_item("yard",
      "Just a dip between a couple of low grass-covered hills, the "+
      "yard in front of the house is fairly empty, except for the "+
      "heap of broken pottery piled next to the house.\n");
   add_item(({"home","house","dwelling"}),
      "Crudely built of stones and covered with a thatched roof, the "+
      "house is typical of those in this area.\n");
   add_item(({"ground","grass"}),
       "The grass here has been lightly trampled, but still " +
       "appears to have seen little enough traffic to cover " +
       "the earth beneath.\n");
   add_item("hills",
       "The low grass-covered hills span out in all directions, "+
       "leading to the shores of Lear Min far to the west.\n");
   add_item(({"water","sea","Lear Min","lear min"}),
       "Gazing far out to the west, you see "+
       "the waters of Lear Min. They are slate grey in colour, " +
       "with white caps topping the larger of the waves in " +
       "the choppy waters as far as the eye can see.\n");
   add_item(({"town","village","tabor sogh","Tabor Sogh"}),
       "Tabor Sogh is an old fishing village, but has never " +
       "grown much beyond a handful of homes and a few " +
       "necessities for fishing. The village consists of " +
       "a single road upon which all buildings are built " +
       "of dark grey stone. You can see it further further "+
       "south along the shore of Lear Min.\n");
   add_item(({"stand","trees","stand of trees","orchard"}),
       "There is a stand of trees to the northeast, which looks "+
       "a bit out of place on these tree-less, low grassy hills. "+
       "It must be an orchard of some type.\n");
   add_item("trail",
      "It is to the northwest and leads to the village.\n");
   add_item("note",
      "It is a small, dirty, torn piece of paper on which something "+
      "has been written with a poor or quick hand. It is pegged "+
      "to the frame of the door of the home.\n");
   add_cmd_item(({"note","writing"}), "read",
      "AYE 'MA G'OWN 'A FISHIN'!\n");
 
   add_exit(ROOM+"trail_3",  "northwest");
   add_exit(ROOM+"bk_grove1","northeast");
   add_exit(ROOM+"home_bk",  "south");
 
   add_prop(OBJ_S_SEARCH_FUN, "find_pot");
   add_prop(OBJ_I_SEARCH_TIME, 3);
   add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_PLAIN);
}
 
string find_pot(object player, string str)
{
    object pot;
 
    if (((str=="heap")||(str=="pottery")||(str=="pile"))&&(pots>0))
       {
       pot = clone_object(OBJ+"honeypot");
       if (pot->move(player)) pot->move(TO);
       pots--;
       return ("You find a "+(pot->short())+" in the heap!\n");
       }
    return "Your search reveals nothing special.\n";
 
}
