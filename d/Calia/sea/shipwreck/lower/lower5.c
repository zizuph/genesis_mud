/*   lower5.c
 *
 * lower levels of the Shipwreck.
 *
 * Baldacin@Genesis, July 2003
 * Patched room for lacedon resetting - Tapakah, June 2011
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
    set_short("Storage room on a wrecked ship");
    set_long("You are floating underwater in the northern parts of a "+
        "big storage room in the shipwreck. An iron chest is secured to "+
        "the floor and some boxes have been placed along the eastern wall. "+
        "It is possible to swim west to reach the lower central "+
        "part of the ship, and to the southern parts of the storage "+
        "room.\n");

/* Room tells borrowed from the sea rooms, created by Maniac & Khail. */
    set_tell_time(45);
    add_tell("A great, dark shape cuts through the water off to one " +
        "side, but it's gone again before you can see any details.\n");
    add_tell("A school of small, brightly coloured fish appear directly " +
        "in front of you, and accelerate around you on their way past. " +
        "Tickles a bit, doesn't it?\n");
    add_tell("Something bumps you playfully from behind, at least you hope " +
        "it was playful, because it was gone when you looked around.\n");
        
    add_item(({"box", "boxes", "broken box", "broken boxes"}), "They have "+
        "been scattered all over the deck when the ship sunk, some broken"+
        "and collapsed, others are in good shape, considering the treatment "+
        "they've been through.\n");

    add_prop(OBJ_S_SEARCH_FUN,"search_func");

    clone_object(OBJ + "chest2")->move(TO);
    add_npc(SEA_CREATURES + "lacedon");
    
    add_swim_exit(WRECKL + "lower2","west");
    add_swim_exit(WRECKL + "lower6","south");

	reset_room();
    
}

void reset_room()
{
	room_searched = 0;
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

	   set_alarm(300.0, 0.0, &reset_room());
   }
   
   return "";
}
