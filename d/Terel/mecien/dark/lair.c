inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define TO this_object()
#define PATH "/d/Terel/mecien/dark/"

create_room(){

object mon;

set_short("Dark Lair");
set_long(
"A smooth stone chamber, warm and smokey.It has an oval shape and a concave "
+ "ceiling, both smooth and the stone the color of blood. In the center of the " +
"chamber is a bed of sand.\n");

add_prop(ROOM_I_LIGHT, -1);
add_prop(ROOM_I_INSIDE, 1);

add_exit(PATH + "stair1", "south", 0);

add_item("bed", "It is sand in the center of the chamber.\n");
add_item("sand", "It is a large bed of sand in the chamber.\n");
add_item("ceiling", "It is concave, the stone smooth and fiery.\n");

seteuid(getuid(TO));
mon = clone_object(PATH + "mon/chimera");
mon->move(TO);


}

void
treasures(object here)
{
    if (!objectp(here))
    {
        here = TO;
    }

    setuid();
    seteuid(getuid());

    tell_room(here, "A radiant light passes through this place, followed " +
	"by a rushing wind.\n");
    clone_object("/d/Terel/mecien/valley/guild/obj/sword3")->move(here, 1);
}


void
treasures_alarm(object here)
{
    set_alarm(5.0, 0.0, &treasures(here) );
}
