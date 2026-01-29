/*
 * D1.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit "/d/Gondor/common/lib/area_room";
inherit "/lib/unique";

inherit E_STD + "vale.c";

#include <stdproperties.h>
#include <ss_types.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();
int                 dis_test();

/*
 * Function name:    create_area_room()
 * Definition   :    Creates the room.
 */
public void
create_area_room()
{
    set_short("In the vale of Erech.");
    set_areatype(AREATYPE_ROAD);
    set_area("northern");
    set_areadesc("mountain side");
    set_areaname("Erech");
    set_extraline("To the north the White Mountains towers up, while " +
	"to the south the vale of Erech widens out. A road goes " +
	"southeast and southwest along the sides of the vale, and " +
	"north into a tunnel. There is a sign here.");

    vale_items();
    path_items();

    add_item("tunnel", "A tunnel leads into the mountains to the north.\n");
    add_item( ({ "mountain", "mountain side" }), "The White Mountains " +
             "towers up to the north. The mountain side is steap and " +
             "rocky, a few plants make some scatered green spots.\n");
    add_item("sign", "\n" +
	     "+-----------------+\n" +
	     "|        <>       |\n" +
	     "|  Enter at your  |\n" +
	     "|   own risk. '   |\n" +
	     "|        <>       |\n" +
	     "+-----------------+\n" +
	     "         ||\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_PATH + "mouth.c", "north", "@@dis_test", 2, 0);
    add_exit(E_VALE + "C2.c", "southwest", 0, 2, 0);
    add_exit(E_VALE + "E2.c", "southeast", 0, 2, 0);

    reset_room();
}

/*
 * Function name:    dis_test()
 * Description  :    Tests if the players are brave enough to pass the 
 *                   exit.
 * Returns      :    0 = If the players have enough self disipline to
 *                       enter it keeps the entrance open.
 *                   1 = If the players are afraid of entering. Retuns also
 *                       a string msg in this case.
 */
int
dis_test()
{
    int dis = this_player()->query_stat(SS_DIS);
    if (dis < 25 )
    {
        write("You don't dare to enter.\n");
	return 1;
    }
    return 0;
}

void
reset_room()
{
    object o;

    o=clone_unique(E_NPC + "farmer", 6);
    o->move(this_object());
    o=clone_unique(E_NPC + "farmer", 6);
    o->move(this_object());
}
