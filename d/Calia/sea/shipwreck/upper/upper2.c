/*   upper2.c
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

#define BARREL (WRECKU+"barrel.c")

int room_searched;

void
create_water_room()
{
    set_short("Main deck of a wrecked ship");
    set_long("You are floating underwater at the western parts of the "+
        "open main deck of the shipwreck. The decaying remains of a small "+
        "stub is all that's left from the jib mast of the ship. And a few "+
        "rotting barrels are standing on the northern edge of the railing. "+
        "You can swim in the direction of the wooden railwork northeast and "+
        "southeast or head directly east to the center of the main deck "+
        "of the shipwreck.\n");

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
    add_item(({"jib mast","mast", "stub"}),"A small broken stub is all that's "+
        "left of the ship's jib mast.\n");
    add_item(({"barrel","barrels", "rotting barrel", "rotting barrels"}),""+
        "They are all decayed and rotting, one of them is bigger than the "+
        "rest of them.\n");
    add_item(({"big barrel", "bigger barrel"}), "It is decayed and rotting, "+
        "you can't help getting the feeling that it is something special "+
        "about the barrel though.\n");
    add_item(({"wreck","shipwreck"}),"It used to be a pretty small ship, "+
        "about 25 meters, some sort of transportation ship. The ship is "+
        "decayed and rotting, it must have been down here for quite some "+
        "time. The salty water probably did its share of corroding too.\n");
    add_item("deck", "It is the floorlike covering of the ship's surface. "+
        "It is made of wood, you can't see anything special about it.\n");
        
    add_cmd_item(({"barrel", "big barrel", "bigger barrel"}),
        "enter","@@enter_barrel");     

    add_prop(OBJ_S_SEARCH_FUN,"search_func");
    room_searched = 0;

    add_swim_exit(WRECKU + "upper1","west");
    add_swim_exit(WRECKU + "upper3","northeast");
    add_swim_exit(WRECKU + "upper4","east");
    add_swim_exit(WRECKU + "upper5","southeast");
    
}

int
enter_barrel()
{     
    if (!BARREL->is_occupied())
    {
        write("You easily slide down into the barrel.\n");
        TP->move_living("entering the barrel", BARREL, 0, 0);
    }
    else
        write("There is not enough room for you there.\n");
        
    return 1;
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
   }
   
   if (member_array(arg, ({"big barrel", "bigger barrel"})) != -1)
   {
       if(me->query_skill(SS_AWARENESS) < (5 + random(5)))
           return "";
       
       return "It might be possible to enter the barrel.\n";          
   }
   
   return "";
}