/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

void
create_shire_room()
{
    object board, book;
    int i, j;
    string *arr;
    
    if (!objectp( board) )
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name( "/d/Shire/misty/new_angmar/board");
        board->move(this_object());
    }

    set_short("Private room");
    set_long("This is the room for members of Angmar's Army. Here, members " +
        "were able to discuss private matters or leave a message for other " +
        "members. To the north is the council room while east is the " +
        "entrance to a small store room. Next to the entrance hangs a simple " +
        "sign. To the south you see yet another store room. It is a bit " +
        "smaller than eastern one. There is a faded sign hanging next to " +
        "the entrance. Buried under the rubble is the remains of the " +
        "board that once stood here. The board once contained announcements " +
        "for the guild.\n");

    
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    
    add_exit(NEW_ANGMAR + "vote", "north");
    add_exit(NEW_ANGMAR + "train", "west");
    add_exit(NEW_ANGMAR + "store2", "south");
    add_exit(NEW_ANGMAR + "store", "east");
    
    add_item(({"sign","faded sign"}), "It is a faded sign with writing on it.\n");
    add_item("writing", "Can you read it?\n");
    add_cmd_item(({"sign","faded sign","writing"}), "read", "\n"+
        "            AUTHORIZED PERSONNEL ONLY!!!\n\n"+
        "  Unauthorized persons will be cooked and served as dinner!\n\n"+
        "  Soldiers can:\n"+
        "       'list authorized'\n"+
        "       'list removed authorizations'\n"+
        "       'who is <short desc>'\n"+
        "  Captain, lieutenants and council members can:\n"+
        "       'allow entry to <name>'\n"+
        "       'disallow entry to <name>'\n\n"+
        "                                    Dark Lord\n\n");
/*    
    FIXEUID;
    book = clone_object(AA_DIR+"books/book");
    book->move(TO);
    book->set_book_is_private(1);
*/  
}

