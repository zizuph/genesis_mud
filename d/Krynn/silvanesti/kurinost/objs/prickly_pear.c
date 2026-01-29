/*
 * prickly_pear.c
 *
 * The pear that you can collect from cactus plants on the rocky
 * shores of Silvanesti.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit "/std/food";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_food
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creating the food with descriptions.
 *
 */
public void
create_food()
{
    set_name(({ "pear", "prickly pear", "cactus pear", "cactus" }));
    add_name("uncut_prickly_pear");
    add_pname("cacti");
    set_adj(({ "red", "purple", "purple-red" }));
    set_short("purple-red prickly pear");
    set_pshort("purple-red prickly pears");

    set_long("Deep purple and red and shaped like an avocado or " +
        "pear, this fruit is protected by a thick outer skin and " +
        "big thorns as is common on most cacti. Tasting like a " +
        "somewhat tough green pepper, the pears grow throughout " +
        "the year on the top of large oval cactus pads.\n");

    add_item(({ "thorn", "thorns" }), "Thick, tough and with a " +
        "piercing point, the thorns protrude all around on the " +
        "purple-red prickly pear.\n");
    set_amount(1);

    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, 5);

    // We need to be able to clone another pear from here.
    setuid();
    seteuid(getuid());
}


/*
 *  FUNCTION : cut_thorns
 *  Arguments: string - arguments given after the cut command.
 *  Returns  : int - 0 if fail, 1 if success.
 * 
 *  Checks if you want to cut the thorns on the prickly pear and if
 *  you have a weapon to do so.
 *
 */
public int
cut_thorns(string arg)
{
    object *item_list = TP->query_weapon(-1);
    string one_desc = "";
    status cut_more = 0, blade_found = 0;
    int tv, wp_num;

    if (arg == "" || !stringp(arg))
    {
        NF("Cut what?\n");

        return 0;
    }

    if (sizeof(item_list))
    {
        for (tv = 0; tv < sizeof(item_list); tv++)
        {
            switch (item_list[tv]->query_wt())
            {
            case 0:
            case 2..3:
                blade_found = 1;
                wp_num = tv;
                break;

            default:
                blade_found = 0;
            }
        }
    }

    if (!sizeof(item_list) || !blade_found)
    {
        NF("You have to wield a bladed weapon, such as a knife, " +
            "sword, or an axe before you can cut the thorns from " +
            "the prickly cactus pear.\n");

        return 0;
    }

    if (arg == "pears" || arg == "pear" || arg == "thorns" ||
        arg == "thorns from pear" || arg == "thorns from pears")
    {
        // Plural form - cut one at the time:
        if (arg == "pears" || arg == "thorns from pears")
        {
            write("Trimming the thorns is a demanding task and you " +
                "decide to cut one cactus pear at the time.\n");
        }

        if (TO->num_heap() > 1)
        {
            one_desc = "one of the purple-red prickly pears.";
        }
        else
        {
            one_desc = "the purple-red prickly pear.";
        }


        write("Using the " + item_list[wp_num]->short() + " you " +
            "carefully trim away the thorns from " + one_desc + "\n");
        say(QCTNAME(TP) + " cuts some thorns from a purple-red " +
            "cactus.\n");

        clone_object(RSOBJS + "prickly_pear_cut")->move(TP, 1);
        reduce_heap_size(1);

        return 1;
    }

    NF("Cut what?\n");

    return 0;
}


/*
 *  FUNCTION : init
 *  Arguments: none
 *  Returns  : void
 * 
 *  Adds the action to cut the thorns.
 *
 */
public void
init()
{
    ::init();

    ADD(cut_thorns, "cut");
}


/*
 *  FUNCTION : command_eat
 *  Arguments: none
 *  Returns  : string - fail message.
 * 
 *  Used when player tries to eat the pear. Fail message is generated.
 *
 */
public mixed
command_eat()
{
    return "OUCH! Trying to eat the purple-red prickly pear is a " +
        "pain. The thorns are simply too big and you have to give " +
        "up eating the pear. You must find some way to cut the " +
        "thorns from the pear before you try to eat it.\n";
}
