/*
 * Fire Wand for the Elemental Worshippers
 *
 * Created by Petros, March 2014
 */

#pragma save_binary

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"

inherit ELEMENTALIST_OBJS + "power_tool_base";

// Defines
#define WAND_SUBLOC "_elemental_guild_subloc_wand"

// Global Variables
public int worn = 0;

/*
 * Function:    create_power_tool
 * Description: Override this to customize the power tool
 */
public void
create_power_tool()
{
    set_name("wand");
    add_adj("copper");
    add_adj("fire");
    add_name("_elemental_guild_wand");
    set_short("copper fire wand");
    set_element_flag(FIRE_FLAG);
}

/*
 * Function:    is_worn
 * Description: This is not a real wearable object. Instead, we just keep
 *              track of the worn variable ourselves.
 */
public int
is_worn()
{
    return worn;
}

/*
 * Function:    remove
 * Description: Removes the wand from the belt subloc
 */
public int
remove(string str)
{
    object this = this_object();
    object tp = this_player();
    if (!present(this,tp))
    {
        notify_fail("You don't have the " + short() + "!\n");
        return 0;
    }
    if (!worn)
    {
        notify_fail("You don't have the " + short() + " on your belt!\n");
        return 0;
    }
    tp->remove_subloc(WAND_SUBLOC);
    worn = 0;
    write("You remove the " + short() + " from your belt.\n");
    say(QCTNAME(tp)+" removes a " + short() + " from " 
        + tp->query_possessive() + " belt.\n");
    set_no_show_composite(0);
    return 1;
}

/*
 * Function:    show_subloc
 * Description: Displays the appropriate message when the belt is hanging
 *              on the player's belt.
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != WAND_SUBLOC)
    {
        return "";
    }

    string data;
    if (for_obj != on)
    {
        data = capitalize(on->query_pronoun())+ " has a " + short()
            + " hanging from " + on->query_possessive() + " belt.\n";
    }
    else
    {
        data = "You have a " + short() + " hanging from your belt.\n";
    }
    return data;
}

/*
 * Function:    wear
 * Description: Puts the wand into the subloc on the player.
 */
public int
wear(string str)
{
    object this = this_object();
    object tp = this_player();
    if (!present(this, tp))
    {
        notify_fail("You don't have the " + short() + "!\n");
        return 0;
    }
    if (worn)
    {
        notify_fail("You already have the " + short() + " hanging from your belt!\n");
        return 0;
    }
    tp->add_subloc(WAND_SUBLOC, this);
    worn = 1;
    write("You hang the " + short() + " from your belt.\n");
    say(QCTNAME(tp)+" hangs a " + short() + " from " 
        + tp->query_possessive() + " belt.\n");
    this->set_no_show_composite(1);
    return 1;
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
    return "This " + short() + " is also known as a Fire Wand. It is a "
        + "smoothly carved wooden shaft that is two feet in length, "
        + "sheathed in copper, and has strange runes carved along it. "
        + "Alongside the runes, you see the words 'whang' and 'wremove'.\n";
}

/*
 * Function:    hook_describe_power_word
 * Description: Returns the power word that should be carved into
 *              the power tool.
 */
public string
hook_describe_power_word()
{
    return "Ergon";
}

/*
 * Function:    hook_describe_deity_name
 * Description: Returns the name of the Deity, which is shown on
 *              the runes on the power tool.
 */
public string
hook_describe_deity_name()
{
    return "Pyros";
}

public int
wield(string str)
{
    object target = PARSE_COMMAND_ONE(str, this_player(), "[the] %i");
    if (objectp(target) && target == this_object())
    {
        write("It would be disrespectful to use one of the Elemental "
                + "Tools in combat!\n");
        return 1;
    }

    return 0;
}

public int
do_touch(string str)
{
    object target = PARSE_COMMAND_ONE(str, 0, "%i");
    if (!target)
    {
        notify_fail("Touch whom with your fire wand?\n");
        return 0;
    }
    
    this_player()->catch_msg("You touch "+(target->query_The_name(this_player())) + 
        " on the right shoulder with your fire wand briefly.\n");
    target->catch_msg((TP->query_The_name(target))+" touches you on the right shoulder "+
        "with "+TP->query_possessive()+" fire wand briefly. You feel a fiery wave of "+
        "energy pass through your body.\n");
    tell_room(TO,QCTNAME(TP) + " touches "+QTNAME(target)+" on the right shoulder with "+
        TP->query_possessive()+" fire wand briefly.\n",
        ({target,TP}));
    return 1;
}

public void
init()
{
    ::init();

    add_action(wield, "wield");
    add_action(wear,"whang");
    add_action(remove,"wremove");
    add_action(do_touch, "rtouch");
}
