/*
 * The bulletin board in Telseron
 * By Finwe, September 1996
 */
 
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
inherit "/std/room";
 
void reset_room();
 
public void
create_room()
{
    object board;
    if (!objectp( board) )
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name( TOWNSHIP_DIR + "/boards/town");
        board->move(this_object());
    }
 
    set_short("An arbor");
    set_long("   This is a shaded arbor. It is shaded by " +
        "vining plants which grow up and over the lattice " +
        "of the arbor. oddly enough, th flowers never seem to " +
        "fade away, or so it seems, because they look fresh and " +
        "there are no signs of any wilted flowers here. Many of " +
        "the elves gather here to post notes of interest on the " +
        "board that is here. Another odd thing is that you may " +
        "be transported to a common board here. Amaryllis street " +
        "runs north and south from here while the Plaza is on " +
        "either side of the arbor.\n\n");
 
    add_item(({"canopy", "ceiling"}),
        "The canopy is covered with blossoms of sweet peas. The " +
        "blossoms hang from the ceiling like miniature jewels " +
        "swaying in the breeze. Sunlight shines through the " +
        "canopy lighting the board and the room.\n");
    add_item("trees",
        "The trees are large with branches that shade the " +
        "arbor.\n");
    add_item("ground",
        "A cobblestone path connects the arbor with Amaryllis " +
        "street and the Plaza.\n");
    add_item("arbor",
        "The arbor is shady, with ivy growing up the sides. " +
        "Sweet pea flowers grow up and over the top, creating a " +
        "jeweled ceiling. The fragrance drifts about the arbor.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TOWNSHIP_DIR + "rd04", "north");
    add_exit(TOWNSHIP_DIR + "pk02", "south");
    add_exit(TOWNSHIP_DIR + "pz02", "east");
    add_exit(TOWNSHIP_DIR + "pz01", "west");
    add_exit("common", "common", 0);
 
}
 
void
reset_room()
{
}
