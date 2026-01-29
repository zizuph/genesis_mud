/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust. */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

object mayor;

void
reset_room()
{
    seteuid(getuid());

    if (!objectp(mayor))
    {
        mayor = clone_object(RUST_NPCS +"gnome_mayor");
        mayor->equip_me();
        mayor->move_living("in", TO);
    }
}

create_room()
{
    set_short("Mayor's office");

    set_long("You are inside an office in the building that serves" +
        " as a town hall in this village. On the east wall is a" +
        " window that lets some sunlight into this room. A couple" +
        " of lamps hang on the walls nonetheless. The room is" +
        " dominated by a broad desk. While it is not very tall," +
        " it's probably broad enough to have a dozen gnomes" +
        " lying side by side on it. Various papers are strewn" +
        " all over it.\n");

    add_item("office","You are standing in it.\n");
    add_item("window","It's dusty, but you can see the forest" +
        " outside through it.\n");
    add_item("forest","You study the forest through the window," +
        " but to get a good look you'd have to go outside.\n");
    add_item(({"wall","walls"}), "The walls look solid, being" +
        " made out of long, wooden logs that have been lafted" +
        " together.\n");
    add_item(({"wooden logs","logs"}), "They all seem to be oaken" +
        " and about as thick as a gnome's head.\n");
    add_item("lamps","They're oil lamps, and aren't lit at the" +
        " moment.\n");
    add_item("desk", "A massive piece of furniture indeed. It must" +
        " have been constructed in this room, for there is no way" +
        " it would fit through the opening.\n");
    add_item("opening", "It leads into the meeting room to the" +
        " north.\n");
    add_item("papers", "They seem to be official documents of" +
        " little significance. Sifting through them all would take" +
        " hours and hours.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"townhall_meetingroom","north",0,1);
    reset_room();
}
