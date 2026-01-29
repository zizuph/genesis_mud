/*
 * /d/Gondor/std/board.c
 * 
 * Generic Middle Earth board. Extends the functionality of the mudlib boards
 * with the announcement functionality for Arda. Notes posted on the domain
 * announcement board will be displayed at the bottom of the notes list and can
 * be read from any of the boards.
 *
 * The announcement board is found in /d/Gondor/private/boards/announceroom
 *
 * Created by Eowul, Oktober 3rd, 2008
 */
 
#include <time.h>

inherit "/std/board";

#define BOARD_LOCATION "/d/Gondor/private/boards/announceroom"
#define ANNOUNCEMENT_LETTERS ({ "a", "b", "c", "d", "e", "f", "g", "h", "i", \
    "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "x", \
    "y", "z" })
#define BOARD_LONG "It is a bulletin board.\n"

private object get_board()
{
    setuid();
    seteuid(getuid());
    BOARD_LOCATION->teleledningsanka();
    if(!find_object(BOARD_LOCATION) || 
       !objectp(BOARD_LOCATION->query_board())) {
       return 0;
    }
    
    return BOARD_LOCATION->query_board();
}

string get_linked_board_long()
{    
    object board = get_board();
    if(!objectp(board)) return BOARD_LONG;
    
    mixed headers = board->query_headers();
    if(sizeof(headers) == 0) return BOARD_LONG;
    
    string str = BOARD_LONG + "##\nAdditionally, you can read "
        + "one of the following Middle Earth announcements:\n\n";

    for(int i = 0; i < sizeof(headers); i++)
    {
        string letter = capitalize(ANNOUNCEMENT_LETTERS[i]);
        
	    str += sprintf("%2s: %s\n", letter, 
            headers[i][0] + " " +
	        TIME2FORMAT(atoi(headers[i][1][1..]),
	            (board->query_show_lvl() ? "yy" : "yyyy")));
    }
    
    return str;
}

void create_board()
{
    set_long(get_linked_board_long);
}

int linked_read_cmd(string what_msg)
{
    string note_text;
 
    object board = get_board();
    if(!objectp(board)) 
    {
        return 0;
    }
    
    if (!stringp(what_msg))
    {
    	return 0;
    }
    
    if (!sscanf(what_msg, "note %s", note_text) &&
        !sscanf(what_msg, "%s", note_text))
    {
    	return 0;
    }
    
    note_text = lower_case(note_text);
    int note = member_array(note_text, ANNOUNCEMENT_LETTERS);
    if(note == -1) return 0;
    
    return board->read_msg("" + (note + 1), 0);
}

void init()
{
    ::init();
    add_action(linked_read_cmd, "read");
    add_action(linked_read_cmd, "mread");
}
