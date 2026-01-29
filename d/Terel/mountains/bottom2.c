/*
 * Lucius, Jan 2018: ROOM_M_NO_TELEPORT_TO added.
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>

#define TEREL_TRIBUTE	"_terel_tribute"

#define TREASURE_ROOM    "/d/Terel/mountains/bottom3"

public static object dragon;


void
reset_room()
{
    if (!dragon)
	dragon = clone_here("/d/Terel/mountains/obj/dragon");

    if (!present(dragon))
	dragon->move_living("away", this_object());

    LOAD_ERR(TREASURE_ROOM);
    find_object(TREASURE_ROOM)->reset_treasure();
}

void
create_room()
{
    set_short("Cave");
    set_long("This massive cavern is hewn from ice and stone. "+
	"The floor of the cavern is littered with scales, bones "+
	"and shards of different objects. There is a great deal of "+
	"ash about. There are many markings upon the walls.\n");

    add_item(({"walls","wall","marking","markings"}),
	"The markings on the walls are those of huge claws.\n");

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);

    add_exit("bottom1", "north", 0);
    add_exit("bottom3", "east", "@@guarded@@");
    add_exit("bottom_t", "west", "@@tribute@@",1,1);

    reset_room();
}

int
tribute()
{
    if (TP->query_prop(TEREL_TRIBUTE))
	return 0;

    write("There is no obvious exit west.\n");
    return 1;
}

int
guarded()
{
    if (!present(dragon))
	return 0;

    write("The dragon is blocking the way.\n");
    say("The dragon blocks "+ QTPNAME(this_player()) +" way.\n");
    return 1;
}
