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
        " This seems to be a densely inhabited part of it." +
        " You can hear the faint sound of a rushing river, from the" +
        " north.\n");

    add_item(({"path", "paths", "pathway"}), "The path is winding" +
        " between the trees and is easy to follow.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item("village", "It's too small by far to be called a town.\n");
    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n");
    add_item(({"huts","hollow trees"}),"Judging from the sounds coming" +
        " from inside of them, they are the homes of families.\n");
    add_item(({"hut"}),"This small building, made out of" +
        " oak branches, has a fur draped in front of the entrance," +
        " preventing you from seeing inside.\n");
    add_item("fur", "It must have been well prepared, for it feels almost" +
        " like the fur of a live animal to the touch.\n");
    add_item(({"branches","oak branches"}),"They're of varying size," +
        " and seem to form a fairly sturdy hut.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_path4","south",0,1);
    add_exit(VILLAGE+"village_home2","in",0,1);
    add_exit(VILLAGE+"village_path7","north",0,1);
}
