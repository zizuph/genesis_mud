/*
 * Earth Pentacle for the Elemental Worshippers
 *
 * Created by Petros, March 2014
 */

#pragma save_binary

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"

inherit ELEMENTALIST_OBJS + "power_tool_base";

// Defines

// Global Variables

/*
 * Function:    create_power_tool
 * Description: Override this to customize the power tool
 */
public void
create_power_tool()
{
    set_name("pentacle");
    add_adj("platinum");
    add_adj("earth");
    add_name("_elemental_guild_pentacle");
    set_short("platinum earth pentacle");
    set_element_flag(EARTH_FLAG);
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
    return "This " + short() + " is also known as an Earth Pentacle. "
        + "It is roughly shaped like a shallow bowl, sheathed in pure "
        + "platinum. A pentagram has been engraved along the inner "
        + "surface, and the inner rim bears strange runes.\n";
}

/*
 * Function:    hook_describe_power_word
 * Description: Returns the power word that should be carved into
 *              the power tool.
 */
public string
hook_describe_power_word()
{
    return "Ischuroteros";
}

/*
 * Function:    hook_describe_deity_name
 * Description: Returns the name of the Deity, which is shown on
 *              the runes on the power tool.
 */
public string
hook_describe_deity_name()
{
    return "Gu";
}

public int
do_efeed(string str)
{
    object target = PARSE_COMMAND_ONE(str, 0, "%i");
    if (!target)
    {
        notify_fail("Feed whom from your earth pentacle?\n");
        return 0;
    }
    
    if (!present("ceremonial bread",TP))
    {
        NF("You don't have any ceremonial bread.\n");
        return 0;
    }
    
    this_player()->catch_msg("You place the ceremonial bread in your "+
        "earth pentacle and offer it to "+(target->query_The_name(this_player())) + 
        ". "+capitalize(target->query_pronoun())+" picks up the bread and "+
        "eats it.\n");
    target->catch_msg((TP->query_The_name(target))+" places some bread into "+
        TP->query_possessive()+" earth pentacle and offers it to you. You pick "+
        "up the bread and eat it. You feel energized and alive like never before.\n");
    tell_room(TO,QCTNAME(TP) + " places some bread into "+TP->query_possessive()+
        " earth pentacle and offers it to "+QTNAME(target)+". "+
        capitalize(target->query_pronoun())+ " picks up the bread and eats it.\n",
        ({target,TP}));
    present("ceremonial bread",TP)->remove_object();
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_efeed, "efeed");
}
