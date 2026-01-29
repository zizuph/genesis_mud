/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust. */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

void
load_board()
{
    object bb;
    bb = clone_object("/d/Calia/central/rust/objects/rust_board");
    bb->move(TO);
}

create_room()
{
    set_short("Board room in town hall");

    set_long("You are standing in what appears to be a meeting" +
        " room. The walls are made out of long, wooden logs that" +
        " have been lafted together. A long, solid oaken table" +
        " dominates the room. About a dozen chairs are pulled up" +
        " to it. A board for posting messages has been affixed" +
        " to the west wall, and you can see an office to the north." +
        "\n");

    add_item(({"wall","walls"}),"The walls look solid.\n");
    add_item(({"logs","wooden logs","long logs"}),"They all seem to be" +
        " oaken, and about as thick as gnome's head.\n");
    add_item(({"table","oaken table"}),"It's a massive piece of" +
        " furniture. Most likely it has been constructed in this" +
        " room.\n");
    add_item("chairs", "These wooden chairs are solidly crafted," +
        " but obviously made for small folk.\n");
    add_item("office", "Judging from the sign over the opening," +
        " it's the mayor's office.\n");
    

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"townhall_mayoroffice","south",0,1);
    add_exit(VILLAGE+"townhall_entrance","east",0,1);


    seteuid(getuid(TO)); 
    load_board();
}


