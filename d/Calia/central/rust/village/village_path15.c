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
        " You can hear the sound of a rushing river, to the" +
        " north. You see a long hall you can enter by going west.\n");

    add_item(({"path", "paths", "pathway"}), "The path is winding" +
        " between the trees and is easy to follow.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item("village", "It's too small by far to be called a town.\n");
    add_item(({"trees", "oak tree", "oak trees", "oaks"}), "The" +
        " great oak trees tower above you and have been stripped of" +
        " limbs close to the ground.\n");
    add_item(({"hollow trees","huts","small huts"}),"You have to move" +
        " further into the village to get a look.\n");
    add_item("hall","It probably has only one floor, but extends quite a" +
        " distance west. Unlike other buildings here, it's made out of logs" +
        " that have been lafted together. Two large furs cover the opening." +
        "\n");
    add_item("logs","They're probably from some of the smaller trees in" +
        " this forest.\n");
    add_item(({"double furs","furs","fur"}),"These big furs are draped" +
        " across the entrance to keep the cold outside. They must have" +
        " well prepared, for they feel almost like the fur of a live" +
        " animal to the touch.\n");



    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_path14","north",0,1);
    add_exit(VILLAGE+"village_path16","south",0,1);
    add_exit(VILLAGE+"townhall_entrance","west",0,1);
}
