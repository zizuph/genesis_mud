#pragma save_binary

inherit "/d/Shire/room";

#include "/d/Shire/hobbit/hobbit.h"

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <std.h>


void reset_room();
static void create_board();

void
create_room()
{
        object board;

     set_short("Hobbit discussion chamber");
       set_long("This is the discussion chamber, where "+
   "all points of discussion may take place on almost any "+
   "topic.  Please keep discussion on a civilized level, however, "+
   "for you do not want other members discussing YOUR family heritage, "+
   "do you?  There are benches lining all the walls, except to "+
   "the southeast and southwest, where there are doorways. To "+
   "the north is a strange room and "+
   "the southwest is the training room and southeast is the "+
   "library.\n");

   add_item("chamber","The chamber is a fairly "+
   "large room, nicely rounded to encourage conversation.\n");
   add_item(({"bench","benches"}),
   "The benches are finely crafted out of oak.\n");
   add_item(({"wall","walls"}),
   "The walls are covered with scrawlings, mostly in pencil, "+
   "obviously predating the bulletin board. The writings are "+
   "quite illegible.\n");
   add_item(({"doorway","doorways"}),
   "The doorways are arched, and made of earth, finely packed and "+
   "supported by wooden beams as lintel posts.\n");

   add_exit(HOBGLD_DIR + "trainroom","southwest",0,1);
   add_exit(HOBGLD_DIR + "libraryroom","southeast",0,1);
   add_exit(HOBGLD_DIR + "common","north",0,1);

   add_prop(ROOM_I_INSIDE,1); /* added by Elwing, Jul 28,1996 */

    reset_room();
}

reset_room()
{
    if (!present("board", TO))
        create_board();
}

static void
create_board()
{
    object board;

    if ((board = clone_object("/std/board")))
    {
        board->set_board_name("/d/Shire/hobbit/board");
        board->set_num_notes(30);
        board->set_silent(1);
         board->set_show_lvl(0);
         board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str("Sorry, mortals are not allowed to remove notes.\n");
        board->move(TO);
    }
    return 0;
}
