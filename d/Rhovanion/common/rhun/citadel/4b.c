
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_citadel_shadowlord"))
    {
        object guard;
        guard=clone_object(RHUN+"npc/citadel_shadowlord");
        guard->move(TO);
    }
}
        

create_room()
{
    set_short("Shadowlord's room");
	set_long(
        "You have entered a vast, vaulted chamber.  It is black-- totally "+
        "and completely.  The walls are of shiny black stone that reflects "+
        "what little light you can produce here, polished to the "+
        "point of being mirror-like.  The ceiling, a high, vast "+
        "dome, is also black, though within its "+
        "surface you can make out small runes etched into the stone.  "+
        "Lastly, the floor here is also of black stone-- not just "+
        "dark marble like the rest of the citadel, but truly black.  "+
        "It is almost like floating amidst a dark emptiness, and "+
        "you feel uneasy just being here.\n");

    AE(RHUN+"citadel/4a","north");

    add_item(({"ceiling","roof","rune","runes"}),
        "The ceiling is solidly black, with tiny runes etched into its "+
        "stone surface.  You can not make out the details of the "+
        "individual runes.\n");
    add_item(({"walls","wall","stone","floor"}),
        "The walls and floor here are made of a shiny, reflective "+
        "black stone, though you cannot name its make.\n");

    IN;
    add_prop(ROOM_I_LIGHT,0);  /* Dark room! */

    reset_room();

}

