#pragma save_binary

#include "default.h"

void
create_room() 
{
    object board;

    set_short("Inter-Domain Quests Cooperation room");
    set_long("This room is for the co-operative brainstorming\n"+
	"of possible inter-domain quest ideas. All wizards with\n" +
	"ideas for quests involving multiple domains are welcome\n" +
	"here.\n" );

    add_exit(THIS_DIR + "domain", "domain");
    add_exit(THIS_DIR + "virtual", "virtual");

    board = load_board("cooperation");
    board->set_num_notes(30);

}
