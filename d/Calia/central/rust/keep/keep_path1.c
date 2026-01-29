/* Created 29/9/98 by Bishop, of Calia. This is a room just
outside the keep protecting Rust. */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

create_room()
{
    set_short("On a path");

    set_long("You are on a narrow path trailing through the" +
        " forest. Trees and dense underbrush crowds you from both" +
        " sides, making it impossible to leave the path.\n");

    add_item("path","The path is easy to follow, as you have no" +
        " other way to go. It's winding left and right slightly," +
        " so you can't see far ahead.\n");
    add_item("forest","The great forest is all around you.\n");
    add_item("trees","The dense and thorny underbrush stops you" +
        " from reaching any of the towering trees.\n");
    add_item("underbrush","It's very dense, with many a sharp" + 
        " thorn.\n");
    add_item("path","It looks fairly well used.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(KEEP+"keep_path2","south",0,1);
    add_exit(VILLAGE+"village_entrance","north",0,1);
}
