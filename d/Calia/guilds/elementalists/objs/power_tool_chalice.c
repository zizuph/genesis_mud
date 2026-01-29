/*
 * Water Chalice for the Elemental Worshippers
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
    set_name("chalice");
    add_name("cup");
    add_adj("gold");
    add_adj("water");
    add_name("_elemental_guild_chalice");
    set_short("gold water chalice");
    set_element_flag(WATER_FLAG);
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
    return "This " + short() + " is also known as a Water Chalice. It "
        + "is shaped like a typical wine glass and coated in gold. "
        + "Strange runes are written vertically and evenly spaced "
        + "around the outside of the cup.\n";
}

/*
 * Function:    hook_describe_power_word
 * Description: Returns the power word that should be carved into
 *              the power tool.
 */
public string
hook_describe_power_word()
{
    return "Meizon";
}

/*
 * Function:    hook_describe_deity_name
 * Description: Returns the name of the Deity, which is shown on
 *              the runes on the power tool.
 */
public string
hook_describe_deity_name()
{
    return "Diabrecho";
}

public int
do_offer(string str)
{
    object target = PARSE_COMMAND_ONE(str, 0, "%i");
    if (!target)
    {
        notify_fail("Offer whom water from your water chalice?\n");
        return 0;
    }
    
    if (!present("ceremonial water",TP))
    {
        NF("You don't have any ceremonial water.\n");
        return 0;
    }
    
    this_player()->catch_msg("You pour the ceremonial water in your "+
        "water chalice and offer it to "+(target->query_The_name(this_player())) + 
        ". "+capitalize(target->query_pronoun())+" drinks the water from the chalice.\n");
    target->catch_msg((TP->query_The_name(target))+" pours some water into "+
        TP->query_possessive()+" water chalice and offers it to you. You drink "+
        "the water from the chalice. You feel a cold surge of energy flowing "+
        "throughout your body.\n");
    tell_room(TO,QCTNAME(TP) + " pours some water into "+TP->query_possessive()+
        " water chalice and offers it to "+QTNAME(target)+". "+
        capitalize(target->query_pronoun())+ " drinks the water from the chalice.\n",
        ({target,TP}));
    present("ceremonial water",TP)->remove_object();
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_offer, "offer");
}
