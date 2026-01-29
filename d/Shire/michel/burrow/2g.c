/*
 * Hobbit burrow in Michel Delving
 * Updated by Finwe, September 1997
 * Updates include adding the hobbitmaker
 */

#pragma strict_types
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/d/Shire/eastroad/smial";

void reset_room();

object hobbit, bottle;

void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving_burrows.txt");

    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 6;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/

    extraline = "This bedroom has no actual beds in it, only " +
    "piles of down-fills to rest on.  A doorway " +
    "leads north.";

    add_item(({"pillows","pillow","down-filled pillows","piles"}),
      "These piles, though humble lodgings, look " +
      "comfortable, and in some places downright inviting.\n");

    add_exit(MICH_DIR + "burrow/2f","north",0,1);

    make_the_room();
    reset_room();
}

void
reset_room()
{
    if (!hobbit)
    {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CITIZEN);
	hobbit->set_power(100);
	hobbit->move(TO);
    }

    if(!present("bottle"))
    {
	set_alarm(1.2,0.0,"make_bottle");
    }
}
void
make_bottle()
{

    object ob;

    setuid(); seteuid(getuid());
    ob = clone_object(MICH_DIR + "obj/bottle");
    ob->move(TO);
    ob->add_prop(OBJ_I_HIDE, 10);
}
