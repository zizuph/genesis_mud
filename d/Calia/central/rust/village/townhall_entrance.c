/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust. */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>


create_room()
{
    set_short("Entrance to town hall");

    set_long("This is a corridor just inside the town hall of this" +
        " village. The walls are made out of long, wooden logs that" +
        " have been lafted together. Pictures adorn on each side of" +
        " the corridor, and lamps hang from the ceiling. A soft carpet" +
        " covers the floorboards, and you can exit the" +
        " building through the double furs draped across the opening" +
        " to the east.\n");

    add_item(({"wall","walls"}),"The walls look solid.\n");
    add_item(({"logs","wooden logs","long logs"}),"They all seem to be" +
        " oaken, and about as thick as gnome's head.\n");
    add_item("pictures","The pictures mostly depict scenes from nature." +
        " One of them is a detailed picture of a mushroom, another is" +
        " a bird's eye view of a wide river snaking through a forest." +
        " One of the pictures is particularly striking, as it portrays" +
        " a flawless white diamond in great detail.\n");
    add_item("mushroom","It looks big and meaty, but you can't identify" +
        " the type.\n");
    add_item(({"white diamond","flawless diamond","diamond"}),"It truly" +
        " looks perfect. You can't help but think that this diamond must" +
        " exist, for such a picture of perfect detail could not have" +
        " sprung from the imagination.\n");
    add_item("lamps","They're oil lamps, and cast the room in good light.\n");
    add_item("carpet","It's red and plush.\n");
    add_item(({"floor","floorboards"}),"You assume it's made out of wooden" +
        " planks, but the carpet covers it, so you can't actually see.\n");
    add_item(({"double furs","furs","fur"}),"These big furs are draped" +
        " across the entrance to keep the cold outside. They must have" +
        " well prepared, for they feel almost like the fur of a live" +
        " animal to the touch.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_path15","east",0,1);
    add_exit(VILLAGE+"townhall_meetingroom","west",0,1);
}
