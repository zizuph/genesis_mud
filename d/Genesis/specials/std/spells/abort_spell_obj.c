/*
 * Abort Spell Object
 *
 * This object allows one to abort the spell that one is casting.
 * This should actually be handled in /std/living/spells.c, so
 * when it is, we should remove this object from being used.
 *
 * Created by Petros, February 2009.
 *
 * Added a query spell file function, Arman - November 2020.
 */
 
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>

// Global Variables
public string       spell_file;

// Prototypes
public int      abort_spell(string arg);
public string   query_spell_file();

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("spell_aborter");
    add_name("_abort_spell_object");

    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    set_short("hidden spell aborter object");
    set_long("This is the spell abort object so that spells based on "
        + "abilities can be aborted.\n");    

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);        
}

public string
query_spell_file()
{
    return spell_file;
}

public void
set_spell_file(string file)
{
    spell_file = file;
}

/*
 * Function name: init
 * Description  : Add the 'command items' of this object. Note that if
 *                you redefine this function, the command items will not
 *                work unless you do ::init(); in your code!
 */
public void
init()
{
    ::init();

    add_action(abort_spell, "abort");
}

public int
abort_spell(string arg)
{
    object spellobj;
    
    if (!strlen(arg)
        || (arg != "spell" && arg != "prayer")
        || !strlen(spell_file)
        || !objectp(spellobj = find_object(spell_file))
        || !spellobj->query_spell())
    {
        notify_fail("Abort what?\n");
        return 0;
    }

    if (!spellobj->query_ability_active(this_player()))
    {
        switch (arg)
        {
        case "spell":
            notify_fail("You aren't casting a spell, though.\n");
            break;
        
        case "prayer":
            notify_fail("You aren't invoking a prayer, though.\n");
            break;
        }
        set_alarm(0.0, 0.0, remove_object);
        return 0;
    }
    
    spellobj->stop_ability(this_player());
    return 1;
}
