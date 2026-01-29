/*   upper5.c
 *
 * Upper levels of the Shipwreck.
 *
 * Baldacin@Genesis, July 2003
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
inherit "/d/Calia/std/water_room";

int room_searched;

void
create_water_room()
{
    set_short("Main deck of a wrecked ship");
    set_long("You are floating underwater at the southern parts of the "+
        "open main deck of the shipwreck. Boxes of various sizes and shapes "+
        "that used to be stacked against the corroded railing have been "+
        "scattered all over the deck. You can swim in the direction of the "+
        "wooden railwork northwest or head directly north to the center of "+
        "the main deck of the shipwreck.\n");

/* Room tells borrowed from the sea rooms, created by Maniac & Khail. */
    set_tell_time(45);
    add_tell("A great, dark shape cuts through the water off to one " +
        "side, but it's gone again before you can see any details.\n");
    add_tell("A school of small, brightly coloured fish appear directly " +
        "in front of you, and accelerate around you on their way past. " +
        "Tickles a bit, doesn't it?\n");
    add_tell("The deep water darkens slightly as the sun is blocked by " +
        "a cloud high above.\n");
    add_tell("Something bumps you playfully from behind, at least you hope " +
        "it was playful, because it was gone when you looked around.\n");



    add_item(({"railwork","rails","railing"}),"They are etched "+   
        "with what was once, obviously, detailed engravings but have "+ 
        "now rotted beyond recognition.\n");
    add_item(({"wreck","shipwreck"}),"It used to be a pretty small ship, "+
        "about 25 meters, some sort of transportation ship. The ship is "+
        "decayed and rotting, it must have been down here for quite some "+
        "time. The salty water probably did its share of corroding too.\n");
    add_item(({"box", "boxes", "broken box", "broken boxes"}), "They have "+
        "been scattered all over the deck when the ship sunk, some broken "+
        "and collapsed, others are in good shape, considering the treatment "+
        "they've been through.\n");     
    add_item("deck", "It is the floorlike covering of the ship's surface. "+
        "It is made of wood, you can't see anything special about it.\n");
        
    add_prop(OBJ_S_SEARCH_FUN,"search_func");
    room_searched = 0;
    
    add_swim_exit(WRECKU + "upper2","northwest");
    add_swim_exit(WRECKU + "upper4","north");
    
}

string
search_func(object me, string arg)
{
   string *allowed_args = ({"box", "boxes", "broken box", "broken boxes"});
   string item = one_of_list(({ OBJ+"comb.c", OBJ+"drum.c", OBJ+"harp.c", OBJ+"mocha.c", OBJ+"rope.c" }));
   
   if (member_array(arg, allowed_args) != -1)
   {     
       if(room_searched || me->query_skill(SS_AWARENESS) < (15 + random(5)))
           return "";
       
       clone_object(item)->move(me, 1);
       room_searched = 1;
       return "You find "+LANG_ASHORT(item)+"!\n";
   }
   
   return "";
}