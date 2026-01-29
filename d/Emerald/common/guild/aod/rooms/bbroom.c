/*
 *  /d/Emerald/common/guild/aod/rooms/bbroom.c
 *
 *  This room houses the bulletin board for the Army of Darkness.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Emerald/sys/paths.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_cave_room();
public object      make_board();


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    object   board;

    set_short("a chamber housing a massive bulletin board");
    set_em_long("Roughly hewn walls have been bluntly formed here to"
      + " create a massive chamber within the rock. An astonishing"
      + " sight rises high above the floor here. The southwestern"
      + " wall has been leveled flat, and upon it an absolutely"
      + " enormous bulletin board has been erected. Strange purple"
      + " energy floats around the board to assist the otherwise"
      + " illiterate Army members with board functions. Wide tunnels"
      + " travel north and northeast, and to the southwest, the rock"
      + " seems to fall away to reveal some other strange substance.\n");

    add_item( ({ "energy", "purple energy", "strange energy",
                 "strange purple energy" }),
        "The energy floats around the board, helping Ogres to"
      + " read and write - actions far beyond their natural"
      + " abilities. Oooo ... Darkling magic!\n");
    add_item( ({ "magic" }),
        "Oooooooooo ... \n");
    add_item( ({ "darkling magic" }),
        "Its purple! So exciting! You feel like clapping.\n");
    add_item( ({ "purple", "purple magic" }),
        "Purple and strange! Darklings are so exciting!\n");
    add_item( ({ "strange", "strange magic" }),
        "So purple ... so strange ... it makes an Ogre want to clap!\n");
    add_item( ({ "strange purple magic", "purple strange magic" }),
        "So purple and magic and strange!! Darklings are best!!\n");
    add_item( ({ "sight", "astonishing sight", "southwestern wall",
                 "sw wall", "southwest wall", "wall" }),
        "To the southwest, a bulletin board of truly enormous proportions"
      + " rises to fill the wall.\n");
    add_item( ({ "tunnel", "tunnels", "north tunnel", "northeast tunnel",
                 "northern tunnel", "northeastern tunnel",
                 "wide tunnel", "wide tunnels" }),
        "Two tunnels lead out of this chamber further into these"
      + " caverns - north and northeast.\n");
    add_item( ({ "southwest", "strange substance", "substance",
                 "black stone", "polished black stone" }),
        "Southwest of here, the rock of the cavern falls away to"
      + " reveal polished black stone. The base of the Darkling Tower"
      + " is that direction.\n");
    add_item( ({ "tower", "darkling tower", "base", "tower base",
                 "base of the tower", "base of the darkling tower" }),
        "The tower is some distance to the southwest.\n");
    add_item( ({ "roughly hewn walls" }),
        "These walls appear to have been bludgeoned into shape!\n");

    add_cave_items();
    add_spike("bbroom");

    add_exit("tower", "southwest");
    add_exit("tunnel5", "north");
    add_exit("start", "northeast");

    if (!(board = make_board()))
    {
        add_my_desc("ERROR: Board not created. Please mail Gorboth.\n");
    }
} /* create_cave_room */


/*
 * Function name:        make_board
 * Description  :        set up the bulletin board
 * Returns      :        the board object - success,
 *                       0                - failure, board not created.
 */
public object
make_board()
{
    object  bboard;

    bboard = clone_object("/std/board");
    if (bboard)
    {
        bboard->set_board_name(BOARD_DIR + "army_of_darkness_board");
        bboard->set_num_notes(50);         /* Number of notes         */
        bboard->set_anonymous(1);          /* You may write anonymous */
        bboard->set_silent(0);             /* Make noise when reading */
        bboard->set_show_lvl(0);           /* Full wizards or higher  */
        bboard->set_remove_lvl(15);        /* Full wizards or higher  */
        bboard->set_remove_str("Only full wizards can remove notes.");
        bboard->set_use_gedit(0);          /* Don't use that editor   */
        bboard->set_keep_discarded(1);     /* Posterity!              */
        bboard->move(this_object());

        return bboard;
    }
    return 0;
} /* make_board */
