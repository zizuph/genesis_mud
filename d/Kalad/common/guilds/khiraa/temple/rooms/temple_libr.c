inherit "/d/Kalad/common/guilds/khiraa/temple/rooms/klib.c";
#pragma save_binary

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

/* Sarr */
/* Revamped by Sarr, 3.Sep.97 */

void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("A dark library");

    set_long("\n   You are within a dark, square chamber of jet-black "+
    "stone. The walls are as cold as the solid, black marble floor. "+
    "The air is filled with the musty scent of old paper, as well as "+
    "the air of death and decay that seems to prevade this entire "+
    "complex. The ceiling and walls are unadorned.\n"+
    "   All around you, you see shelves of black wooden oak holding "+
    "dozens of books in all shapes and sizes. Most of them are binded "+
    "in black, but there are a few other colors as well. There are a "+
    "few tables of solid marble, as well as some wooden chairs, "+
    "strewn about. A large brazier sits in the corner, a purple "+
    "and black flame burning and illuminating the room.\n\n");
    add_item("shelves","They are made of black oak, and look very "+
    "sturdy. They hold dozens of books. Next to the shelves on "+
    "one wall, you see a sign.\n");
    add_item("books","Many books fill the shelves here, with an "+
    "assortment of shapes, sizes and colors. Some look very old, "+
    "while others look rather new.\n");
    add_item("tables","There are large tables made of heavy solid "+
    "black marble, not unlike the floor. There are three of them "+
    "place in the room, surrounded by chairs.\n");
    add_item("chairs","The chairs are made of black oak wood, and "+
    "are very heavy and uncomfortable looking.\n");


    add_item(({"sign"}),"There are many words on it, you should read it.\n");
    add_cmd_item("sign","read",
       "The sign states the procedures for borrowing books:\n"+
       "\nYou must return any previously borrowed books before\n"+
       "you are allowed to borrow any new book, and you are not\n"+
       "allowed to leave the library without returning all books.\n"+
       "\nThe following commands are used:\n"+
       "borrow <book> - borrow a book\n"+
       "return book   - return a book\n"+
       "list          - list all books currently in the library\n\n"+
       "write book    - write a book and submit it to the library.\n"+
       "                The circle will review it before adding it.\n");
    
    add_exit(KHIRAA_DIR(temple/rooms/bookroom),"north","@@check@@",-1);
    add_exit(KHIRAA_DIR(temple/rooms/t10),"south","@@block@@",-1);
    set_librarian_room(KHIRAA_DIR(temple/rooms/bookroom));
    load_library();
}

int
block()
{
    if(present("_khiraabook_",TP))
    {
        write("Return the book before leaving.\n");
        return 1;
    }
    return 0;
}

int
check()
{
    if(TP->query_circle())
        return 0;
    write("Only Circle Members may enter that room.\n");
    return 1;
}

