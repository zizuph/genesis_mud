/*
 *  The Minas Morgul Adventurers' Hang-out
 *
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public int    wizcheck();

public void
create_morgul_room()
{
    object board;

    set_extraline(
     "Here travelling thugs, unemployed mercenaries, hit men looking " 
   + "for a contract, and other unpleasant contemporaries meet to "
   + "exchange news and to find partners to gang with. They also brag "
   + "of their feats slaughtering innocents and trade information "
   + "on new territories to loot and ransack. For these and other "
   + "purposes you can use the board here. "
   + "A passage is leading south into a training hall.");
    set_road(9);
    set_short_desc("in the thugs' hang-out in Minas Morgul");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_item(({"floor","plank","planks"}), BSN(
        "The floor is made of rough wooden planks. "));
    add_item(({"passage"}), BSN(
        "The passage leading south seems to enter into another room."));
    add_item(({"thug","thugs","hit man","hit men","mercenary","mercenaries"}), BSN(
    "Right now, there seem to be none of them here. Perhaps " +
    "they are doing their bloody work somewhere, but perhaps they " +
    "just went to a place where they cab get some booze while " +
    "bragging about their deeds."));

    add_exit("/d/Gondor/workroom","north", wizcheck);
    add_exit(MORGUL_DIR + "city/darkstr1","east", check_exit);
    add_exit(MORGUL_DIR + "city/rooms/trainhall", "south", check_exit);
    add_exit(MORGUL_DIR + "city/rooms/commonb", "up", check_exit);

    board = clone_object(STD_DIR + "board");
    board->set_board_name(BOARD_DIR + "morgul_board");
    board->set_num_notes(25);         /* Number of notes         */
    board->set_anonymous(1);          /* You may write anonymous */
    board->set_silent(0);             /* Make noise when reading */
    board->set_show_lvl(0);           /* Full wizards or higher  */
    board->set_remove_lvl(15);         /* Full wizards or higher  */
    board->set_remove_str("You somehow failed.");
    board->set_use_gedit(0);          /* Don't use that marvellous editor */
    board->move(TO);
}

public int
wizcheck() 
{
    string  name;
  
    if (!TP->query_wiz_level())
    {
        write("A strong olog appears from the room to the north. \n" +
            "The strong olog stops you. \n" +
            "The guard says: Be off! Only wizards may enter that room. \n" +
            "Then the olog returns to the room to the north.\n");
        return 1;
    }

    write("\nWelcome, " + SECURITY->query_wiz_pretitle(TP) + " " + 
        CAP(TP->query_real_name()) + ", Wizard of " + 
        SECURITY->query_wiz_dom(TP->query_real_name()) + "!\n\n");
    return 0;
}

