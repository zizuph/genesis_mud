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
        " You can clearly hear the sound of a rushing river, to the" +
        " north. A less used path trails up on a hill to the east.\n");

    add_item(({"pathway"}), "The path is winding" +
        " between the trees and is easy to follow.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item("village", "It's too small by far to be called a town.\n");
    add_item(({"trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n");
    add_item("path","It is clearly a path, but isn't much traversed it" +
        " seems.\n");
    add_item("hill","It's not a big hill, and there are no trees on it." +
        " Still, the trees of the rest of the forest tower far above" +
        " it.\n");
    add_item(({"hollow trees","huts","small huts"}),"You have to move" +
        " further into the village to get a look.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_path13","north",0,1);
    add_exit(VILLAGE+"village_path15","south",0,1);
    add_exit(VILLAGE+"village_hill","east",0,5);
}
