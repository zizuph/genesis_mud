/* Created by Dajala
 * Members recieve promotions in this room and may put their 
 * suggestions for new modules up on the board.
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

#include "../guild.h"

inherit "/d/Krynn/std/room";

object board;
int stored_max_level, create_again = 0;

/* prototype */
void reset_room();

string
name()
{
    if (!strlen(MANAGER->query_headtin_name()))
        return "vacant";
    
    return "held by " + capitalize(MANAGER->query_headtin_name());
}

string
title()
{
    if(MANAGER->query_headtin_gender() == 1)
        return GNOME_TITLES_F[14];
    
    return GNOME_TITLES[14];
}

int
tinkerer()
{
    write("The poster reads: The office of " + title() + " of the Inventors " +
    "Guild is currently " + name() + ".\n");
	
	return 1;
}

void
create_room()
{
    set_short("Planning chamber");

    set_long("This room is a mess! Piles of papers are stacked " +
    "on desks all around the cave. Papers cover the floor. " +
    "You see gnomes working at blackboards inventing and " +
    "drawing new fantastic machines. You feel obliged to " +
    "become busy and contribute to the technological advance " +
    "of gnomekind.\nA bulletin board is placed in the middle " +
    "of the room and a red poster on the south wall.\n");

    add_exit(ROOMS + "joinroom", "north", 0);
    add_exit(ROOMS + "folderro", "south", 0);
    add_exit(ROOMS + "conference", "east", 0);

    INSIDE;
    LIGHT;

    add_item(({"paper", "papers"}), "You cannot find any order, but "
      + "what you find are bins hidden underneath.\n");
    add_item(({"bin", "bins"}), "They are filled with papers.\n");
    add_item(({"blackboard", "blackboards"}), "You watch amazed and "
      + "feel proud to be a part of it all.\n");
    add_item(({"box", "black box"}), "It is rather featureless, black "
      + "and has a little hole in the front staring at you.\n");
      
    add_cmd_item(({"poster", "red poster"}), "read", "@@tinkerer");
    reset_room();
}

void
reset_room()
{

    seteuid(getuid(TO));
    if (!board)
    {
        board = clone_object(GOBJ + "noteboard");
        board->set_board_name(LOG + "board_data");
        board->set_long("        This is the private inventor's board.\n"
        + "\nUse it to share your inventions of new modules and "
        + "machines with your fellow inventors and the "
        + "Guildmaster or for discussion of odler subjects.\n"
        + "You are welcome to post frequently "
        + "but please do not abuse it.\n\n");
        board->set_silent(0);
        board->set_keep_discarded(1);
        board->set_num_notes(30);
        board->set_remove_str("Sorry, only the guildmaster may remove the "
        + "notes.\n");
        board->set_short("Board for New Inventions");
        board->add_name("Board for New Inventions");
        board->add_name("board for new inventions");
        board->move(TO,1);
    }
}
