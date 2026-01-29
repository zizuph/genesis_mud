/*
 * Mandala for the Elemental Child Clerics
 *
 * Created by Jaacar, July 2016
 */


#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"

inherit ELEMENTALIST_OBJS + "power_tool_base";

// Defines

// Global Variables
string color1 = "silver";
string color2 = "black";

/*
 * Function:    create_power_tool
 * Description: Override this to customize the power tool
 */
public void
create_power_tool()
{
    set_name("mandala");
    add_name("symbol");
    add_adj(({"sacred",color1,color2}));
    add_name("_elemental_guild_mandala");
    add_name("_elemental_child_mandala");
    set_short("sacred "+color1+" and "+color2+" mandala");
    set_element_flag(AIR_FLAG);
}

/*
 * Function:    hook_destroy_message
 * Description: Override this hook to show your custom message for the
 *              destruction of the power tool.
 */
public string
hook_destroy_message(object env)
{
    return "The " + short() + " shatters into thousands of tiny pieces.\n";
}

/*
 * Function:    hook_describe_long
 * Description: Override this for the main part of the description for
 *              the power tool. The rune information will be added at
 *              the end.
 */
public string
hook_describe_long()
{	
    return "This " + short() + " is the holy symbol of the Elementals. "+
        "It is a small "+color1+", round symbol with a pattern of "+
        color2+" in the middle. The pattern consists of a circle "+
        "with a square inside of it.\n";
}

/*
 * Function:    hook_describe_power_word
 * Description: Returns the power word that should be carved into
 *              the power tool.
 */
public string
hook_describe_power_word()
{
    return "None";
}

/*
 * Function:    hook_describe_deity_name
 * Description: Returns the name of the Deity, which is shown on
 *              the runes on the power tool.
 */
public string
hook_describe_deity_name()
{
    return "None";
}


int
do_clasp(string str)
{
    if (!str)
        return 0;

    if (str != "symbol" && str != "mandala" &&
        str != "sacred mandala")
    {
        NF("Clasp what? Your sacred mandala?\n");
        return 0;
    }

    write("You clasp your sacred mandala and hold it close to your chest.\n");
    say(QCTNAME(TP)+" clasps "+HIS+" sacred "+color1+" and "+color2+
        " mandala and holds it close to "+HIS+" chest.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_clasp,"clasp");
}
