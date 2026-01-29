
#pragma strict_types
#pragma save_binary
#pragma no_clone

inherit "/std/scroll";

#include "/d/Genesis/specials/local.h"

#define MANA_SHADOW              ("/d/Genesis/specials/guilds/shadows/mana_shadow")

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

object mana_shadow;
mapping magic_obj_spell = ([]);

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
create_spell_scroll()
{
    // Mask this function to customize the magic obj.
}

nomask varargs void
add_spell(mixed spell)
{
    object ob;
    string name;

    if (objectp(spell))
    {
        ob = spell;
    }
    else if (stringp(spell))
    {
        setuid();
        seteuid(getuid());
        LOAD_ERR(spell);
        ob = find_object(spell);
    }

    if (!ob)
    {
        return;
    }

    name = ob->query_spell_name();

    if (!strlen(name))
    {
        return;
    }
    magic_obj_spell[name] = MASTER_OB(ob);
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
    
    foreach(string filename : spell)
    {
        add_spell(filename);
    }
}


/*
 * Function:    query_magic_obj_spell
 * Description: Returns the specified spell files.
 * Returns:     string *magic_obj_spell - array of strings
 */
public string *
query_magic_obj_spell()
{
    return m_values(magic_obj_spell);
}


public nomask void
create_scroll()
{
    setuid();
    seteuid(getuid());
    
    set_name("_magic_scroll_");
    set_long("This is a magic scroll.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({ "This is a magic object.\n", 20 }));
        
    set_magic_obj_spell(({}));
    
    // Call the create_magic_obj function for customization purposes
    create_spell_scroll();
}


/*
 * Function:    add_magic_obj_effects
 * Description: Adds the soul, shadow and mana shadow to the target
 * Argument:    object player - target to shadow
 */
public void
add_magic_obj_effects(object player)
{
    if (!player->has_mana_shadow())
    {
        mana_shadow = clone_object(MANA_SHADOW);
        mana_shadow->shadow_me(player);
    }
}


public object
get_spell_object(string name)
{
    mixed spell = magic_obj_spell[name];

    if (stringp(spell))
    {
        setuid();
        seteuid(getuid());
        LOAD_ERR(spell);
        return find_object(spell);
    }

    if (objectp(spell))
    {
        return spell;
    }

    return 0;
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    int i;
    string *verbs = m_indices(magic_obj_spell);
    string desc;
    object ob;

    i = sizeof(verbs);
    while (i--)
    {
        if (ob = get_spell_object(verbs[i]))
        {
            desc = ob->query_spell_desc() || "";
            write(sprintf("        %s\n", desc));
        }
    }
}

public int
start_spell_fail(string verb, string arg)
{
    object spell;
    if (!(spell = get_spell_object(verb)))
    {
        return 1;
    }
    return spell->do_ability(arg);
}

/* 
 * Function name: exist_command
 * Description  : Check if a spell exists.
 * Returns      : 1/0 depending on success.
 */
nomask public int
exist_command(string verb)
{
    return !!magic_obj_spell[verb];
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
    env->remove_spellobj(this_object());
    ::leave_env(env, to);
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
    if (living(env))
    {
        env->add_spellobj(this_object());
    }
}