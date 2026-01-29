/*
 *	/d/Gondor/common/dunedain/rooms/hall.c
 *
 *	Coded by Olorin, November 1994
 *
 *	Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

public int
leave_hall()
{
    write("You leave the Assembly Hall through the great gates and "
        + "return to the street.\n");
    return 0;
}

public void
create_gondor()
{
    set_short("Assembly Hall");
    set_long(BSN(
        "The great Assembly Hall of Gondor. Here the Dunedain from all"
      + " corners of the land come together for discussions, for"
      + " performances of the arts, or to meet with friends and"
      + " relatives. The hall is lit by deep windows on both sides of"
      + " the gate which is leading back onto the street to the east,"
      + " while two hallways go off to the south and to the north."));

    add_exit(DUNEDAIN_DIR + "rooms/hallw_n", "north", 0,  0);
    add_exit(PELAR_DIR + "streets/belfalas05", "east", leave_hall, 0);
    add_exit(DUNEDAIN_DIR + "rooms/hallw_s", "south", check_exit,  0);
    add_exit(DUNEDAIN_DIR + "rooms/board_room", "west", 0,  0);

    floor();
    add_item(({"roof", "ceiling", "dome", }), BSN(
        "In a mighty dome the roof rises high above the walls "
      + "on which it rests. Marvellously, there are no pillars to "
      + "support the aspiring construction."));
    add_item(({"hallway", "hallways", }), BSN(
        "Two hallways are leading out of the hall deeper into the "
      + "building, one to the north, the other to the south."));
    add_item(({"wall", "walls", }), BSN(
        "The walls are formed by large stone blocks hewn from black "
      + "rock piled one upon the other. The rock has been smoothed "
      + "and polished so that the walls are gleaming in the light "
      + "entering through the windows. The rocks were fitted together "
      + "with expert craftsmanship so that there are no grooves between "
      + "the blocks. Only the hallways, the windows, the gate, "
      + "a small stone arc leading west, and twelves recesses interrupt "
      + "their surface."));
    add_item(({"window", "windows", }), BSN(
        "On both sides of the gate are two deep arched window through "
      + "which light can enter into the Hall."));
    add_item(({"gate", "gates", }), BSN(
        "The gate leading into the hall must be even larger than the "
      + "city gates themselves, although it is probably less sturdy. "
      + "The two wings of the gate are presently open. Through the "
      + "gate the street outside is visible."));
    add_item(({"recess", "recesses", "statue", "statues", }), BSN(
        "Twelve recesses are in the walls opposite to the windows, "
      + "six in the northwestern arc of the hall, and six in the "
      + "southwestern one. Inside the recesses there are statues carved "
      + "from black marble showing the first Lords and Ladies of the "
      + "Houses of the Dunedain. There are Beor the Old; the Lady "
      + "Haleth of the Haladin; Hador the Goldenhaired; Hurin Thalion, "
      + "son of Galdor; Hurin of Emyn Arnen, Steward of King Minardil; "
      + "Aranrath of Fornost, first chieftain of the Dunedain of the "
      + "North; Amandil, last Lord of Andunie, father of Elendil; "
      + "Belecthor, the fifteenth Ruling Steward of Gondor; Borlad, son "
      + "of Bor; Hallacar, Lord of Hyarastorni of Numenor; Agarwaen, the "
      + "Bloodstained; and Umarth, Lord of Ladros."));

    add_prop(ROOM_I_INSIDE, 1);
}

