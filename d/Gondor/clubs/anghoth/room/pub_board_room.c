/*
 *  pub_board_room.c
 *
 *  Public bulletin board room of the Anghoth Barracks
 *    For the use of prospective Shields to make themselves
 *    known to the Lords of Minas Morgul
 *
 *  Alto, 13 June 2002
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../anghoth_defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <std.h>
#include "/d/Gondor/defs.h"

inherit ANGHOTH_ROOM + "room_funcs.c";

public int     check_anghoth();
public string  long_func();
public string  read_plaque();

public void
create_gondor()
{
    object  board, closet;

    set_short("below the private quarters of the Anghoth of Morgul");
    set_long(long_func);

    anghoth_add_items();

    add_prop(ROOM_I_INSIDE,1);

    add_exit(MORGUL_DIR + "city/rooms/b5up",        "east",  0, 0);
    add_exit(ANGHOTH_ROOM + "priv_board_room",      "up", check_anghoth, 0);

    add_item("plaque", read_plaque);
    add_cmd_item("plaque", "read", read_plaque);

    add_item(({"room", "building"}), &long_func());
    add_item(({"north wall"}), "On the north wall a window stands open.\n");
    add_item(({"window"}), "The air coming in through the window is stuffy "
        + "and oppressive. You feel your strength flagging with every "
        + "breath.\n");
    add_item(({"south wall"}), "Upon the south wall has been bolted a "
        + "plaque. Perhaps you should read it before venturing further.\n"
        + "You also notice something strange about the west wall.\n");
    add_item(({"west wall"}), "There appears to be a concealed closet built "
        + "into the west wall.\n");
    add_item(({"stairwell", "stairs", "stair", "stone stairs"}), 
        "The stairs curve up into the darkness. What transpires there "
        + "remains secret unto the Anghoth and their Lords.\n");

    FIX_EUID;
    board = clone_object(STD_DIR + "board");
    board->set_board_name(ANGHOTH_BOARD_DIR + "ang_pub_board");
    board->set_num_notes(50);
    board->set_silent(0);
    board->set_show_lvl(0);
    board->set_remove_lvl(WIZ_NORMAL);
    board->set_remove_str("The note is firmly affixed to the board.");
    board->move(TO);

    closet = clone_object(ANGHOTH_OBJ + "equipment_closet");
    closet->move(TO);

    reset_room();
}

public string
read_plaque()
{
    return "\n --------------------------------------------------------- \n"
         + "|o _____________                                       _ o|\n"
         + "| |                                                     | |\n"
         + "|      Hail in the name of the Lidless Eye!             | |\n"
         + "|                                                       | |\n"
         + "|      In the darkness above are the barracks of the      |\n"
         + "|      Anghoth, the living Shields of the Lords of        |\n"
         + "|      Minas Morgul. Our enemies hear the march of our    |\n"
         + "|      feet and feel a despair second only to that        |\n"
         + "|      brought by our feared Lords.                       |\n"
         + "|                                                         |\n"
         + "|      Few are worthy of the honour of our ranks. If,     |\n"
         + "|      in your arrogance, you feel worthy, begone Dog!    |\n"
         + "|      We have no need of strutting braggarts.            |\n"
         + "|                                                         |\n"
         + "|      If however you have the wisdom to curry favour     |\n"
         + "|      with the Lords of Morgul, the humility to serve    |\n"
         + "|      the needs of the Tower without question, and       |\n"
         + "|      strength to stand as Shield against the            |\n"
         + "|      treachery of the West, here you may beg the        |\n"
         + "|      attention of our Lords, whose boots you are        |\n"
         + "|      assuredly not worthy to lick.                      |\n"
         + "|                                                         |\n"
         + "| |                                Arganthal, Durub       |\n"
         + "| |                          Captain of the Anghoth       |\n"
         + "| |_                                     _______________| |\n"
         + "|o                                                       o|\n"
         + " --------------------------------------------------------- \n\n";

}

public string
long_func()
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            longtxt = 
        "You are in a dark building in the northern parts of Minas Morgul. "
        + "Save the bulletin board in its center and the stone stairs rising "
        + "into the darkness above, the room is entirely empty. The sterile "
        + "cleanliness of the place, however, suggests that it is a room "
        + "of some significance despite its lack of ornamentation. Perhaps "
        + "the plaque bolted to the south wall would be informative."; 

    switch (time)
    {
    case "night":
        longtxt += " A window on the north wall opens onto silky darkness.";
        break;
    case "early morning":
        longtxt += " A window on the north wall admits a few weak rays "
            + "of the early morning light.";
        break;
    case "morning":
    case "noon":
    case "afternoon":
        longtxt += " Through a window on the north wall dim light enters.";
        break;
    case "evening":
        longtxt += " Dull evening sunlight can be seen through a window "
            + "on the north wall.";
        break;
    }
    return (longtxt + "\n");
}

public int
check_anghoth()
{
    if (ANGHOTH_MEMBER(TP))
        {
        write("Welcome, Anghoth of Minas Morgul!\n");
        return 0;
        }

    if (IS_MORGUL_MAGE(TP))
        {
        write("Welcome, Mage of the Society!\n");
        return 0;
        }

    if (TP->query_wiz_level())
        {
        write("Welcome, Wizard!\n");
        return 0;
        }

    else
        {
        write("As you obviously have no business up there, you decide "
            + "to remain downstairs and respect the privacy of the "
            + "Anghoth of Minas Morgul.\n");
        return 1;
        }
}
