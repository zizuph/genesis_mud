/*     Created by:     Sir Toby, 97-07-04
 *     Purpose:        The great hall of the Lizards lair.
 *     Location:       /d/Kalad/common/sewers/ll30.c
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
    set_long("This is the northwestern end of a great hall. " +
	     "The ceiling is a huge dome and it radiates a " +
	     "strange strong light. The floor is so smooth " +
	     "and polished that you can almost see your own " +
	     "reflection. On the north wall you see a tapestry " +
	     "and far east seem to be a throne. You can move " +
	     "further into the great hall going east, south " +
	     "and southeast. You can also leave the hall " +
	     "going west. " + "@@dwarf_check");

    add_item("ceiling","The ceiling is huge and vaulted, creating " +
	     "a huge dome. It radiates a strange strong light.\n");
    add_item("floor","The floor is so smooth and polished that " +
		     "you can almost see your own reflection.\n");
    add_item("wall","On the wall is a great tapestry.\n");
    add_item("tapestry","The tapestry pictures two lizard warriors " +
	     "fighting each other in an underground tunnel. They " +
	     "are wearing magnificent black scale armours.\n" +
	     "They fight using their teeth and claws.\n");
    add_item("throne","You can not see the throne clearly enough " +
	     "from this point to get any details. You would have " +
	     "to move closer.\n");

    add_exit(PATH + "ll13.c","west",0,1);
    add_exit(PATH + "ll33.c","east",0,1);
    add_exit(PATH + "ll31.c","south",0,1);
    add_exit(PATH + "ll34.c","southeast",0,1);
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