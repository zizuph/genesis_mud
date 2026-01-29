/* Created 29/9/98 by Bishop, of Calia. This is a room in the
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
        " The path forks here, and the entrance to the village" +
        " lies directly to your south." + 
        " The path bends, leading north and east here. Further" +
        " west is an enormous tree, that's been hollowed out." +
        " On occasion boisterous laughter and song can be heard" +
        " from inside. You can hear the very faint" +
        " sound of a rushing river from the north.\n");

    add_item(({"path", "paths", "pathway"}), "The path is winding" +
        " between the trees and is easy to follow.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item("village", "It's too small by far to be called a town.\n");
    add_item(({"trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n");
    add_item(({"tree","hollow tree","enormous tree"}),"It's hundreds of" +
        " feet tall and very broad at the base. If it's all hollowed out," +
        " an army could fit inside.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_tavern","in",0,1);
    add_exit(VILLAGE+"village_path2","east",0,1);
    add_exit(VILLAGE+"village_path6","north",0,1);
}
