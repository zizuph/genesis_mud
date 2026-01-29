/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust. */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

create_room()
{
    set_short("Pathway in the gnome village");

    set_long("You are standing on a well-trodden pathway" +
        " inside a great forest. Judging from the hard-packed" +
        " path, huts, and hollow trees you see here, this is a village." +
        " You can faintly hear the sound of a rushing river, to the" +
        " north. An old hollow tree lies east.\n");

    add_item(({"path", "paths", "pathway"}), "The path is winding" +
        " between the trees and is easy to follow.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item("village", "It's too small by far to be called a town.\n");
    add_item(({"trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n");
    add_item(({"old hollow tree","old tree","hollow tree"}),"This old" +
        " oak tree has been expertly hollowed" +
        " out. There are no windows, and a fur has been draped across the" +
        " entrance, preventing you from seeing inside.\n");
    add_item(({"hollow trees","huts","small huts"}),"You have to move" +
        " further into the village to get a look.\n");
    add_item(({"fur"}), "They must have well prepared, for they feel almost" +
        " like the fur of a live animal to the touch.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_path15","north",0,1);
    add_exit(VILLAGE+"village_path5","south",0,1);
    add_exit(VILLAGE+"village_home7","in",0,1);
}
