/*
 *  std_magic_obj.c
 *
 *  Inherit this to create objects that can make use of spell
 *  effects using the spell system - such as wands.
 *
 *  Created by Carnak June 2017
 *
 * * * * * * * * * * * * * * * * * *
 *
 *  Example code:
 *
 *  inherit "/d/Krynn/std/std_magic_obj";
 *
 *  #include <macros.h>
 *  #include <wa_types.h>
 *  #include <ss_types.h>
 *  #include <stdproperties.h>
 *
 *  public void
 *  create_magic_obj()
 *  {
 *      set_name("tome");
 *      add_adj("leather-bound");
 *      set_long("This is a thin delicate leather-bound tome covered in " +
 *      "runes.\n");
 *
 *      add_prop(OBJ_I_WEIGHT,20);
 *      add_prop(OBJ_I_VOLUME,20);
 *      add_prop(OBJ_I_VALUE, 100);
 *      add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
 *      add_prop(MAGIC_AM_ID_INFO,
 *      ({ "This is a rune-clad tome granting you magic.. yadayada.\n", 20 }));
 *        
 *      set_keep(1);
 *
 *      set_holdable(0);
 *
 *      set_magic_spellbook(1);
 *    
 *      set_magic_obj_soul("/d/Krynn/std/spells/light_wand_soul.c");
 *  }
 *
 * * * * * * * * * * * * * * * * * *
 *
 *  Comments:
 *
 */


#pragma strict_types
#pragma save_binary
#pragma no_clone

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

object  magic_obj_shadow,
        mana_shadow;
string *magic_obj_spell,
       *magic_obj_effect,
        magic_obj_soul,
        magic_obj_shadow_loc;
int     holdable,
        magic_spellbook;

public void     add_magic_obj_effects(object player);
public void     remove_magic_obj_effects(object player);
public string   hook_magic_obj_hold();
public string   hook_magic_obj_release();

/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

public void
create_magic_obj()
{
    // Mask this function to customize the magic obj.
}

/*
 * Function:    set_magic_obj_spell
 * Description: Sets spells that the object grans its user.
 * Argument:    mixed spell - array of strings
 */
public void
set_magic_obj_spell(mixed spell)
{
    if (!pointerp(spell))
        spell = ({ spell });
    
    magic_obj_spell = spell;
}

/*
 * Function:    query_magic_obj_spell
 * Description: Returns the specified spell files.
 * Returns:     string *magic_obj_spell - array of strings
 */
public string *
query_magic_obj_spell()
{
    return magic_obj_spell;
}

/*
 * Function:    set_magic_obj_effect
 * Description: Sets effect names for the effects of the spells.
 * Argument:    mixed effect - array of strings
 */
public void
set_magic_obj_effect(mixed effect)
{
    if (!pointerp(effect))
        effect = ({ effect });
    
    magic_obj_effect = effect;
}

/*
 * Function:    query_magic_obj_effect
 * Description: Returns the specified effect names.
 * Returns:     string *magic_obj_effects - array of strings
 */
public string *
query_magic_obj_effect()
{
    return magic_obj_effect;
}

/*
 * Function:    set_magic_obj_soul
 * Description: Sets the soul associated with the item, most commonly a
 *              spell soul.
 * Argument:    string soul - the souls master_ob
 */
public void
set_magic_obj_soul(string soul)
{
    magic_obj_soul = soul;
}

/*
 * Function:    query_magic_obj_soul
 * Description: Returns the specified soul master_ob
 * Returns:     string magic_obj_soul - soul file_name
 */
public string
query_magic_obj_soul()
{
    return magic_obj_soul;
}

/*
 * Function:    set_magic_obj_shadow
 * Description: Sets the shadow associated with the item.
 * Argument:    string shadow - the shadow master_ob
 */
public void
set_magic_obj_shadow(string shadow)
{
    magic_obj_shadow_loc = shadow;
}

/*
 * Function:    query_magic_obj_shadow
 * Description: Returns the specified shadow master_ob
 * Returns:     string magic_obj_shadow_loc - shadow file_name
 */
public mixed
query_magic_obj_shadow()
{
    if (objectp(magic_obj_shadow))
        return magic_obj_shadow;
    
    return magic_obj_shadow_loc;
}

/*
 * Function:    set_holdable
 * Description: Determines if the object is holdable or not
 * Argument:    int hold - 1: holdable, 0: not holdable
 */
public void
set_holdable(int hold)
{
    holdable = hold;
}

/*
 * Function:    query_holdable
 * Description: Returns the objects holdable status.
 * Returns:     int holdable - 1: holdable, 0: not holdable
 */
public int
query_holdable()
{
    return holdable;
}

/*
 * Function:    set_magic_spellbook
 * Description: Makes the object react on environment, adding
 *              spells when entering the inventory
 * Argument:    int spellbook - 1: reacts to inventory,
 *                              0: does not add spells
 */
public void
set_magic_spellbook(int spellbook)
{
    magic_spellbook = spellbook;
}

/*
 * Function:    query_magic_spellbook
 * Description: Returns the objects reaction to environment.
 * Returns:     int spellbook - 1: reacts to inventory,
 *                              0: does not add spells
 */
public int
query_magic_spellbook()
{
    return magic_spellbook;
}

public nomask void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("_magic_object_");
    set_long("This is a magic object.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({ "This is a magic object.\n", 20 }));
        
    set_slots(W_ANYH);
    set_holdable(0);
    
    set_keep(1);
    
    set_magic_obj_spell(({""}));
    set_magic_obj_effect(({""}));
    set_magic_obj_soul("");
    set_magic_obj_shadow("");
    
    // Call the create_magic_obj function for customization purposes
    create_magic_obj();
}

/*
 * Function:    is_valid_spell_obj
 * Description: Checks if there are any valid spell objects
 * Argument:    object caster, object obj - object to check
 * Returns:     1 - success, 0 - failure
 */
public int
is_valid_spell_obj(object caster, object obj)
{
    string *effects = ({});
    
    if (!sizeof(magic_obj_effect) || !objectp(obj))
        return 0;
    
    foreach(string effect: magic_obj_effect)
    {
        if (obj->id(effect))
            effects += ({ effect });
    }
    
    if (!sizeof(effects))
        return 0;
    
    return 1;
}

/*
 * Function name: hold
 * Description  : Called when the person wants to hold an item. This function
 *                may allow or disallow the object to be held, and it may
 *                print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be held, print default messages.
 *                 1 - The item can be held, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be held. Print default messages.
 *                string - The item cannot be held. The string contains the
 *                         fail message.
 */
public nomask mixed
hold()
{
    if (!query_holdable())
        return "You seem unable to hold that.\n";
    
    hook_magic_obj_hold();
    add_magic_obj_effects(this_player());

    return 0;
}

/*
 * Function:    hook_magic_obj_hold
 * Description: The string hook for successfully holding the object.
 */
public string
hook_magic_obj_hold()
{
    // Add hold description
}

/*
 * Function:    add_magic_obj_effects
 * Description: Adds the soul, shadow and mana shadow to the target
 * Argument:    object player - target to shadow
 */
public void
add_magic_obj_effects(object player)
{
    if (strlen(magic_obj_soul) && player->add_cmdsoul(magic_obj_soul))
        player->update_hooks();
    
    if (strlen(magic_obj_shadow_loc) && safely_load_master_file(magic_obj_shadow_loc))
    {
        magic_obj_shadow = clone_object(magic_obj_shadow_loc);
        magic_obj_shadow->shadow_me(player);
        magic_obj_shadow->add_shadow_effects();
    }
    
    if (!player->has_mana_shadow())
    {
        mana_shadow = clone_object(MANA_SHADOW);
        mana_shadow->shadow_me(player);
    }
}

/* 
 * Function name: release
 * Description  : Called when the person wants to release the item. This
 *                function may allow or disallow the object to be released,
 *                and it may print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be relased, print default messages.
 *                 1 - The item can be relased, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be released. Print default messages.
 *                string - The item cannot be relased. The string contains the
 *                         fail message.
 */
public nomask mixed
release()
{
    if (!query_holdable())
        return "You seem unable to release that.\n";
    
    hook_magic_obj_release();
    remove_magic_obj_effects(this_player());
    return 0;
}

/*
 * Function:    hook_magic_obj_release
 * Description: The string hook for successfully releasing the object.
 */
public string
hook_magic_obj_release()
{
    // Add release description
}

/*
 * Function:    remove_magic_obj_effects
 * Description: Removes the soul and shadows from the target, also dispels
 *              any active spell object.
 * Argument:    object player
 */
public void
remove_magic_obj_effects(object player)
{
    if (strlen(magic_obj_soul) && player->remove_cmdsoul(magic_obj_soul))
        player->update_hooks();
    
    if (objectp(magic_obj_shadow))
        magic_obj_shadow->remove_shadow_effects();
    
    if (objectp(mana_shadow))
        mana_shadow->remove_mana_shadow();
    
    if (!objectp(player) && !living(player = environment(this_object())))
        return;
    
    object *spell_obj;
    spell_obj = filter(all_inventory(player), &is_valid_spell_obj(player,));

    if(sizeof(spell_obj))
    {
        foreach(object s_obj : spell_obj)
        {
            s_obj->set_dispel_time(1);
        }
    }
}

/*
 * Function:    leave_env
 * Description: Standard leave_env, removes magic effects and
 *              handles holdable object.
 * Arguments:   object from - the environment we are leaving.
 *              object to   - the environment we are entering.
 */
void
leave_env(object env, object to)
{
    if (!query_holdable())
    {
        remove_magic_obj_effects(env);
    }
    
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}


/*
 * Function:    leave_env
 * Description: Standard enter_env, adds magic effects if the
 *              environment is living and the magic_spellbook
 *              has been set.
 * Arguments:   object env  - the environment we are entering.
 *              object from - the environment we are leaving.
 */
void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    
    if (magic_spellbook && living(env) && !query_holdable())
        add_magic_obj_effects(env);
}