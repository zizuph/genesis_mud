/* Created 28/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust.*/

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

create_room()
{
    set_short("Pathway in the gnome village");

    set_long("You are standing on a well-trodden pathway" +
        " inside a great forest. Judging from the hard-packed" +
        " path, huts, and hollow trees you see here, this is a village." +
        " You can hear the very faint sound of a rushing river from the" +
        " north. A hollow tree lies to your north.\n");
 
    add_item(({"path", "paths", "pathway"}), "The path is winding" +
        " between the trees and is easy to follow.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item(({"tree","hollow tree"}), "This tree has been expertly" +
        " hollowed out. There's no way to see inside, as the tree" +
        " lacks windows, and the entrance is covered by a fur.\n");
    add_item("village", "It's too small by far to be called a town.\n");
    add_item(({"trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n");
    add_item("entrance", "There is a fur hanging in front of the opening," +
        " preventing you from seeing inside.\n");
    add_item("fur", "It must have been well prepared, for it feels almost" +
        " like the fur of a live animal to the touch.\n");
    add_item(({"huts","small huts"}),"You have to move" +
        " further into the village to get a look.\n");


    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_home1","in",0,1);
    add_exit(VILLAGE+"village_path1","west",0,1);
    add_exit(VILLAGE+"village_path5","east",0,1);
}
