/* The graveyard
*
* Nick
*/

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit GRAVE_STD;

create_solace_room()
{
    set_short("Graveyard");
    set_long(BS("You are standing in the graveyard of Solace. This part of " +
                "the graveyard is mostly for common people. The ground here " +
                "is very soggy and you are ankle deep in mud. Some of the gr" +
                "avestones here are not standing as straight as the others t" +
                "hat you have seen.", 70));

    ADD_GRAVES;
    ADD_GRAVEYARD;
    READ_GRAVE;
    
    add_item(({"gravestone","gravestones"}),
	     "The tilted gravestones look like they haven't been tended in " +
	     "a while. They have sunk into the mud a little.\n");
    add_item(({"mud","ground"}),
	     "The ground is all covered with mud here in this part of the " +
	     "graveyard. It's just ordinary, dirty mud.\n");
    
    add_exit(TDIR + "grave6", "west", 0);

}

