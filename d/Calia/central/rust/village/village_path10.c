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
        " You are standing close to the bank of a frothing river, to" +
        " your north.\n");

    add_item(({"path", "paths", "pathway"}), "The path is winding" +
        " between the trees and is easy to follow.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item("village", "It's too small by far to be called a town.\n");
    add_item(({"trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n");
    add_item(({"bank","river bank"}),"The bank is very steep at first" +
        " and flattening out as it reaches the river. The river might" +
        " be as much as 50 meters below you.\n");
    add_item(({"frothing river","river"}),"It's moving quite fast, and is" +
        " about a 100 meters wide. You would have to be a" +
        " fish to manage the swim over to the other bank, where the great" +
        " forest continues.\n");
    add_item(({"hollow trees","huts"}),"You have to move" +
        " further into the village to get a look.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_path9","west",0,1);
    add_exit(VILLAGE+"village_path11","east",0,1);
}
