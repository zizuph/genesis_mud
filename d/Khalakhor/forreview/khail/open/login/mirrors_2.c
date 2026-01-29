/*
 * /d/Genesis/login/mirror_1.c
 *
 * This is the second of two mirror rooms where player's select their
 * height and width. In this one, they select their width by choosing
 * from various shaped mirrors.
 *
 * Khail, May 17/96
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include "login.h"

#define TP this_player()

inherit "/std/room";

public int check_bodies_exit();
public int check_height_exit();
public int read_book();
public int all_cmd(string str);
public int examine_mirrors(string str);
public int enter_something(string str);
public int get_help(string str);

/*
 * Function name: extra_long
 * Description  : Modifies the long description if the player shouldn't
 *                be here.
 * Returns      : The extra string, if any.
 */
public string
extra_long()
{
    if (!TP->query_ghost() & GP_MANGLE)
        return "You realize you shouldn't be here, and might as well " +
            "'enter first mirror', as it won't matter which one you " +
            "enter at the moment.\n\n";
    else
        return "";
}

public void
create_room()
{
    set_short("hall of mirrors");
    set_long("You find yourself in a very strange room, surrounded by " +
        "mirrors of all shapes and sizes. You somehow feel that you " +
        "should look at them, and that it might even be possible to " +
        "enter one to leave this place. In the center of the room " +
        "a pedestal supports a heavy book, open to a single, well-" +
        "worn page.\n\nIf you get really stuck, 'help here' might " +
        "provide some help.\n\n" +
        "@@extra_long");
    add_item(({"pedestal"}),
        "A large pedestal stands in the middle of the room. An " +
        "important looking book rests atop it, probably worth " +
        "reading.\n");
    add_item(({"book"}),
        "It's got writing in it, you should probably read it.\n");
    add_cmd_item(({"writing", "book"}), ({"read"}),
        "@@read_book");

    add_exit(PATH + "bodies", "bodies",
        "@@check_bodies_exit");
    add_exit(PATH + "mirrors_1", "height",
        "@@check_height_exit");
}

public int
check_bodies_exit()
{
    write("\nCode to be added\n\n");
    return 0;
}

public int
check_height_exit()
{
    write("\nCode to be added\n\n");
    return 0;
}

public int
read_book()
{
    string ret;

    ret = "Welcome to the first Hall of Mirrors. Here you may select the " +
        "width of your new body. You can accomplish this by examining " +
        "the various mirrors, and entering whichever mirror holds the " +
        "form you like. For example, 'enter first mirror' if you want " +
        "to be very skinny.\n";
    ret += "Once you enter a mirror, you will pass beyond with your " +
        "new width.\n";
    ret += "Note this will be permanent after you have entered the " +
        "world, although you may return here from any point previous " +
        "to that. You will be warned once before the final exit, wherever " +
        "it is.\n";
    write("\n" + ret + "\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(all_cmd, "", 1);
}

public int
all_cmd(string str)
{
    switch(query_verb())
    {
        case "exa":
        case "examine":
            return examine_mirrors(str);
            break;
        case "enter":
            return enter_something(str);
            break;
        case "help":
            return get_help(str);
            break;
        default:
            return 0;
    }
}

public int
enter_something(string str)
{
    string which;
    int width,
        index,
        *attr;

    attr = RACEATTR[TP->query_race_name()];

    notify_fail("Enter what? One of the mirrors?\n");

    if (!str || !strlen(str) || sscanf(str, "%s mirror", which) != 1)
        return 0;

    index = LANG_ORDW(which) - 1;
    if (index >= sizeof(WIDTHDESC))
    {
        notify_fail("Please enter either one of the following mirrors: " +
            COMPOSITE_WORDS(WIDTHDESC) + ".\n");
        return 0;
    }

    if (!TP->query_ghost() & GP_MANGLE)
    {
        write("\nYou suddenly realize that you aren't supposed to be here, " +
            "and find yourself moving along with no changes being made.\n\n");
        if (TP->query_ghost() & GP_FEATURES)
        {
            TP->move_living("X", PATH + "features");
            return 1;
        }
        else if (TP->query_ghost() & GP_SKILLS)
        {
            TP->move_living("X", PATH + "features");
            return 1;
        }
        else
        {
            write("\nFinal game entry sequence goes here, REMIND ME! - Khail.\n\n");
            return 1;
        }
    }

    write("\nYou step into the " + which + " mirror, and surprisingly find " +
        "yourself in another room rather than chewing glass.\n\n");

    width = (attr[5] * TP->query_prop(CONT_I_HEIGHT) *
        (index * 7) / 10);
    if (random(2))
        width = width - random(width * attr[5] / 8000);
    else
        width = width + random(width * attr[5] / 5000);

    TP->add_prop(CONT_I_WEIGHT, width);
    TP->add_prop(CONT_I_VOLUME, width);
    TP->set_ghost(TP->query_ghost() - GP_MANGLE);

    if (TP->query_ghost() & GP_FEATURES)
        TP->move_living("X", PATH + "features");
    else if (TP->query_ghost() & GP_SKILLS)
        TP->move_living("X", PATH + "skills");
    else
    {
        TP->set_ghost(0);
        TP->ghost_ready();
    }
    return 1;
}
        
public int
examine_mirrors(string str)
{
    int index;
    string ret,
           which;

    if (!str || !strlen(str))
        return 0;

    if (str == "mirrors")
    {
        write("\nGazing into the various mirrors, you see yourself looking " +
            "into images of yourself in different widths:\n" +
            COMPOSITE_WORDS(WIDTHDESC) + ".\n\n");
        return 1;
    }

    if (sscanf(str, "%s mirror", which) != 1)
    {
        notify_fail("Examine which mirror?\n");
        return 0;
    }

    index = LANG_ORDW(which) - 1;
    if (index >= sizeof(WIDTHDESC))
    {
        notify_fail("Examine which mirror?\n");
        return 0;
    }

    ret = "Gazing into the mirror, you see yourself looking ";
    ret += WIDTHDESC[index] + ". ";
    ret += "You get the impression by entering the " + which + " mirror " +
        "you might permanently look that way.\n";

    write("\n" + ret + "\n");

    return 1;
}

public int
get_help(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (str == "here")
    {
        TP->more(read_file(PATH + "width_help"));
        return 1;
    }

    return 0;
}
