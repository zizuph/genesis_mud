/*
 * Power Tool Base for Elemental Guilds of Calia
 *
 * A Power Tool is something that has to be constructed by the
 * member of the guild in order to gain access to the powers of
 * the guild. It's basically like an entrance quest.
 * 
 * In the old version of the Worshippers guild, these were
 * actually spell objects that were required to have access to
 * the spells. In the recoded Elemental Guilds, these are just
 * autoloading objects. The spells are actually managed elsewhere.
 *
 * Created by Petros, March 2014
 */
#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <files.h>
#include "defs.h"

inherit "/std/object";

// Defines

// Prototypes
public void set_element_flag(int element_flag);
public int  query_element_flag();

// Global Variables
int count = 0;
public int ELEMENT_FLAG = 0;

/*
 * Function:    is_elemental_power_tool
 * Description: An identifying function for Elemental power
 *              tools.
 */
public int
is_elemental_power_tool()
{
    return 1;
}

/*
 * Function:    create_power_tool
 * Description: Override this to customize the power tool
 */
public void
create_power_tool()
{
}

public nomask void
create_object()
{
    set_name("_elemental_guild_power_tool");
    add_name("tool");
    add_adj("elemental");
    add_adj("power");
    set_short("elemental power tool");
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL,1);
    set_element_flag(0);

    create_power_tool();
    // Customization of the long description should be done through
    // the hook functions. By calling it after create_power_tool, there
    // is no way to override it except here.
    set_long("@@hook_describe_long@@" + "@@hook_describe_runes@@");
}

/*
 * Function:    hook_destroy_message
 * Description: Override this hook to show your custom message for the
 *              destruction of the power tool.
 */
public string
hook_destroy_message(object env)
{
    return "The power tool is destroyed.\n";
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
    return "This is the long description for the base power tool for the Elemental "
        + "Guild of Calia.\n";
}

/*
 * Function:    hook_describe_power_word
 * Description: Returns the power word that should be carved into
 *              the power tool.
 */
public string
hook_describe_power_word()
{
    return "PowerWord";
}

/*
 * Function:    hook_describe_deity_name
 * Description: Returns the name of the Deity, which is shown on
 *              the runes on the power tool.
 */
public string
hook_describe_deity_name()
{
    return "Deity";
}

/*
 * Function:    hook_describe_runes
 * Description: Called via VBFC for the long description, this shows the
 *              text of the runes and displays whether the power word has
 *              been carved into the tool or not.
 */
public string
hook_describe_runes()
{
    string description;
    setuid();
    seteuid(getuid());
    if (!IS_MEMBER(this_player()))
    {
        return "\n";
    }
    
    // If they are a child cleric, no diety needs to be shown
    if (GUILD_MANAGER->query_is_child_cleric(this_player()))
    {
        description = "The runes read: " + capitalize(this_player()->query_real_name());
    }
    
    // Otherwise show the diety
    else
    {
        description = "The runes read: " + hook_describe_deity_name() + ", "
            + capitalize(this_player()->query_real_name());
    }
    
    if (GUILD_MANAGER->is_element_carved(this_player(), query_element_flag()))
    {
        description = description + ", " + hook_describe_power_word() + ".\n";
    }
    else
    {
        description = description + ".\n";
    }
    
    if (IS_SEEKER(this_player()))
    	description = description + "You also see <help seeker>.\n";
    if (IS_WORSHIPPER(this_player()))
    	description = description + "You also see <help worshipper>.\n";
    if (IS_CLERIC(this_player()))
        description = description + "You also see <help cleric>.\n";
    if (this_player()->is_elemental_racial_cleric())
    	description = description + "You also see <help kyrullian>.\n";
    return description;
}

/*
 * Function:    destroy_tool
 * Description: If the user wants to get rid of the object because they
 *              don't like it in their inventory, we define what needs to
 *              happen in this function.
 */
public int
destroy_tool()
{
    object e = environment(this_object());
    string destroy_message = hook_destroy_message(e);
    if (IS_ROOM_OBJECT(e))
    {
        tell_room(e, destroy_message);
    }
    else if (interactive(e))
    {
        e->catch_msg(destroy_message);
    }
    set_alarm(0.0, 0.0, &remove_object());
    return 1;
}

/*
 * Function:    query_element_flag
 * Description: Returns the flag for the particular element. Should be set
 *              in the create function by calling set_element_flag
 */
public int
query_element_flag()
{
    return ELEMENT_FLAG;
}

/*
 * Function:    set_element_flag
 * Description: Sets the element flag, which will determine how to check
 *              whether the tool is carved or not.
 */
public void
set_element_flag(int element_flag)
{
    ELEMENT_FLAG = element_flag;
}

/*
 * Function:    query_auto_load
 * Description: Power tools are auto-loaded upon login.
 */
public string
query_auto_load()
{
    return MASTER + ":" + count;
}

/* We don't let non-worshippers keep hold of these for long. */
public void
init_arg(string arg)
{
    if (!IS_MEMBER(this_player()))
    {
        count = atoi(arg) + 1;
        if (count >= 50)
        {
            set_alarm(5.0, 0.0, destroy_tool);
        }
    }
}

