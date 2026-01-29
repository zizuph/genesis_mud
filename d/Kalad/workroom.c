inherit "/std/workroom";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define DOM_BOARD KALAD(private/private_board)


/*
 * Globals
 */
object board;


/*
 * prototypes
 */
void load_board();


create_workroom()
{
    set_short("Kalad workroom");
    set_long(BS(
"This room looks like it belongs in a Victorian mansion. Soft, plush "+
"chairs "+
"are abundant, and a crystal chandelier throws multi-colored light onto"+
" the far walls. To the north is the Wizard's Lounge, to the " +
"west is the Visitor's Center, and to the east is " +
"your workroom. This is where the wizards of Kalad " +
"discuss domain projects and this board is only for " +
"their eyes, and those of Arches and Keepers. " +
"For questions, complaints, suggestions, or " +
"discussion of inter-domain topics, Visitors " +
"may use the board in the Visitor's Center. " +
"\n"));
    add_exit("@@goto_start","east",0);
add_exit("/d/Genesis/wiz/lounge", "north",0);
    add_exit("/d/Kalad/common/domain_entr","west",0);
    remove_exit("start");
    load_board();
}


goto_start()
{
    return (string) this_player()->query_default_start_location();
}


void
load_board()
{
   if (!P(board,TO))
      board = DOM_BOARD->move(TO);
}


void
init()
{
   ::init();
   load_board();
}