/*     Created by:     Sir Toby, 97-07-22
 *     Purpose:        The great hall of the Lizards lair.
 *     Location:       /d/Kalad/common/sewers/ll34.c
 *     Modified:       
 */


#pragma strict_types

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"

void
create_room()
{
::create_room();

    set_short("In a great hall");
    set_long("This is the centre of the great hall. " +
	     "The ceiling is a huge dome and it radiates a " +
	     "strange strong light. The floor is so smooth " +
	     "and polished that you can almost see your own " +
	     "reflection. To the east there is a throne. " +
	     "You can move closer to the exits of the great " +
	     "hall going west, northwest and southwest. And " +
	     "move to the north and south walls. " +
	     "@@dwarf_check");

    add_item("ceiling","The ceiling is huge and vaulted, creating " +
	     "a huge dome. It radiates a strange strong light.\n");
    add_item("floor","The floor is so smooth and polished that " +
		     "you can almost see your own reflection.\n");
    add_item("throne","You can not see the throne clearly enough " +
	     "from this point to get any details. You would have " +
	     "to step closer to it.\n");

    add_exit(PATH + "ll33.c","north",0,1);
    add_exit(PATH + "ll35.c","south",0,1);
    add_exit(PATH + "ll36.c","east",0,1);
    add_exit(PATH + "ll31.c","west",0,1);
    add_exit(PATH + "ll30.c","northwest",0,1);
    add_exit(PATH + "ll32.c","southwest",0,1);
    set_noshow_obvious(1);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,50);  // It is a magical light...

return;
}

string
dwarf_check()
{

    if(TP->query_race() == "dwarf")
        return"You sence that the ground " +
              "is totally flat and that you are deep under " +
              "the surface of Kabal.\n"; 

       return"\n";

}