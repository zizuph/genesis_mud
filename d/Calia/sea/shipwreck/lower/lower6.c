/*   lower6.c
 *
 * lower levels of the Shipwreck.
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
    set_short("Storage room on a wrecked ship");
    set_long("You are floating underwater in the southern parts of a "+
        "big storage room in the shipwreck. The room is quite empty, "+
        "only some barrels are scattered around the floor. "+
        "It is possible to swim northwest to reach the lower central "+
        "part of the ship, and to the northern parts of the storage "+
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

    add_item(({"barrel","barrels", "rotting barrel", "rotting barrels"}),""+
        "They are all decayed and rotting, you can't really see anything "+
        "special about them.\n");

    add_prop(OBJ_S_SEARCH_FUN,"search_func");
    
    add_swim_exit(WRECKL + "lower2","northwest");
    add_swim_exit(WRECKL + "lower5","north");

	reset_room();
    
}

void reset_room()
{
	room_searched = 0;
}

string
search_func(object me, string arg)
{
   string *allowed_args = ({"barrel", "barrels", "rotting barrel", "rotting barrels"});
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