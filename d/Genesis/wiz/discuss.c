#pragma save_binary

#include "default.h"

void
create_room() 
{
    object board;

    set_short("Wizard Discussion room");
    set_long( "Wizard discussion room.\n" +
      "This is a room for discussions and planning ideas.\n" +
      "To the north is the lounge, east is the discussion room\n" +
      "for spells and magic. The room for discussing special projects\n" +
      "is to the west.\n");

    add_exit(THIS_DIR + "lounge", "north");
    add_exit(THIS_DIR + "magic", "east");
    add_exit(THIS_DIR + "projects", "west");

    board = load_board("discussions");
    board->set_num_notes(99);

    add_default_exits();
}
