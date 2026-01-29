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
        " The path bemds here, leading north and west." +
        " You see a small hut to the southeast. Occasionally a" +
        " pigeon will fly out of a hole in the roof of the hut, and" +
        " sometimes one lands inside as well. You can hear the very" +
        " faint sound of a rushing river from the north.\n");

    
    add_item(({"path", "paths", "pathway"}), "The path is winding" +
        " between the trees and is easy to follow.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item("village", "It's too small by far to be called a town.\n");
    add_item("entrance", "There is a fur hanging in front of the opening," +
        " preventing you from seeing inside.\n");
    add_item("keep", "It looks rather big, but at this distance, you" +
        " can't really see any details.\n");
    add_item("pigeon", "They're flying quite fast, and most seem to be" +
        " carrying something.\n");
    add_item(({"hole in roof","roof","hole"}),"It's too high up to really" +
        " see, you just assume it's there since pigeons are disappearing" +
        " into, and coming out of the roof.\n");
    add_item(({"hut","small hut"}), "It's made out of oak branches," +
        " and seems functional, but not ornate.\n");
    add_item(({"branches","oak branches"}),"They're of varying size" +
        " but seem to fit together well.\n");
    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n");
    add_item("fur", "It must have been well prepared, for it feels almost" +
        " like the fur of a live animal to the touch.\n");
    add_item("hollow trees","You have to move" +
        " further into the village to get a look.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_path3","west",0,1);
    add_exit(VILLAGE+"village_post","in",0,1);
    add_exit(VILLAGE+"village_path16","north",0,1);
}
