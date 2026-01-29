/* spellcasting.c - Spellcasting routines
 *
 * Usage:
 * 1) inherit this module in your spellcasting object
 * 2) add calls to add_spell_object() and remove_spell_object()
 *    to your object (generally in enter_env() and leave_env(), 
 *    respectively).
 * 3) in the constructor of your object, add each spell using
 *    add_spell()
 * 4) configure your spells
 *
 * Example:
 * inherit "/std/object";
 * inherit "/d/Genesis/magic/spellcasting";
 *
 * void
 * create_object()
 * {
 *     set_name("talisman");
 *     ... configure object ...
 *    
 *     add_spell("/d/Genesis/magic/spells/identify");
 * }
 *
 * void
 * enter_env(object env, object from)
 * {
 *     ::enter_env(env, from);
 *     add_spell_object(env);
 * }
 *
 * void
 * leave_env(object env, object to)
 * {
 *     ::leave_env(env, to);
 *     remove_spell_object(env);
 * }
 *     
 */

/* TODO
 *      Check for a LIVE_O_SPELL_ATTACK before allowing another
 *      spell to be started.
 *
 *      Verify that in all cases of failure, that it removes the
 *      concentrating prop.
 */

#pragma strict_types

#define SPELL_ARR_DESC         0
#define SPELL_ARR_SPELLOBJ     1
#define SPELL_ARR_SIZE         2

#include <macros.h>

static object *gTargets;
static object gCaster;
static string gArg;
                           
static mapping gSpells = ([]);

public object get_spell_object(string name);

/*
 * Function name: add_spell
 * Description:   Add the spell to the list of active spells.
 * Arguments:     string name           - The activating verb string
 */
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

#if 0
    ob->do_spell_setup(0);
#endif

    name = ob->query_spell_name();

    if (!strlen(name))
    {
        return;
    }

    gSpells[name] = spell;
}

/*
 * Function name: remove_spell
 * Description:   Remove the spell with the given verb string.
 * Arguments:     string name - The name of the spell to remove.
 */
nomask public void
remove_spell(string name)
{
    gSpells = m_delete(gSpells, name);
}

public object
get_spell_object(string name)
{
    mixed spell = gSpells[name];

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
    string *verbs = m_indices(gSpells);
    string desc;
    object ob;

    i = sizeof(verbs);
    while (i--)
    {
        if (ob = get_spell_object(verbs[i]))
        {
            desc = ob->query_spell_desc() || "";
            write(sprintf("%-15s %s\n", verbs[i], desc));
        }
    }
}

/*
 * Function name: query_spell_map
 * Description:   Get the spell mapping (gSpells)
 * Returns:       A mapping.
 */
public mapping
query_spell_map()
{
    return secure_var(gSpells);
}

/*
 * Spell object registration functions
 */

/*
 * Function name: add_spell_object
 * Decription:    Call this to add the spells defined by this object to
 *                a living
 * Arguments:     object ob - the living receiving the spells
 */
public void
add_spell_object(object ob)
{
    ob->add_spellobj(this_object());
}

/*
 * Function name: remove_spell_object
 * Description:   Call this to remove the spells definied by this object from
 *                a living
 * Arguments:     object ob - the living from whom the spells are to be removed
 */
public void
remove_spell_object(object ob)
{
    ob->remove_spellobj(this_object());
}
    
/*
 * The following functions called by the basic spell routines
 * found in the player object.
 */

/*
 * Function name: break_spell
 * Description:   Called when concentration is broken
 * Arguments:     string spell   - the spell that was broken
 *                object breaker - what broke the spell
 */
public void
break_spell(string spell, object breaker)
{
    get_spell_object(spell)->break_spell(gCaster, breaker);
}

/*
 * Function name: abort_spell
 * Description:   Called when concentration is aborted
 * Arguments:     string spell - the spell that was aborted
 */
public void
abort_spell(string spell)
{
    get_spell_object(spell)->abort_spell(this_player());
}

/*
 * Function name: query_spell_time
 * Description:   It is called from cmdhooks.c, and should return the time
 *                in seconds it takes to prepare the spell. The actual time
 *                will be (time + 2 + LIVE_I_ATTACK_DELAY).
 * Arguments:     verb - The verb that initiated this spell.
 *                arg  - The arguments to the verb.
 * Returns:       The time in seconds.
 */
public int
query_spell_time(string verb, mixed arg)
{
    return get_spell_object(verb)->query_spell_time(gCaster, gTargets, arg);
}

/*
 * Function name: query_spell_mess
 * Description:   It is called from cmdhooks.c, and it us used to change the
 *                standard message given when a spell is being prepared. You
 *                should handle all the printouts by yourself.
 * Arguments:     verb - The verb that initiated this spell.
 *                arg  - The arguments to the verb.
 * Returns:       True if you are handling the printouts yourself, 
 *                false otherwise.
 */
public int
query_spell_mess(string verb, mixed arg)
{
    return get_spell_object(verb)->query_spell_mess(gCaster, gTargets, arg);
}

/*
 * Function name: start_spell_fail
 * Description:   Called to initiate spell concentration.  This is where
 *                we initialize the spell, do some preliminary checks. and
 *                apply initial spell costs
 * Arguments:     verb - The verb that initiated this spell.
 *                arg  - The arguments to the verb.
 * Returns:       True if the spell failed, false otherwise
 */
public int
start_spell_fail(string verb, string arg)
{
    object spell;

    gArg = arg;
    gCaster = this_player();
    gTargets = ({});

    if (!(spell = get_spell_object(verb)))
    {
        return 1;
    }

#if 0
    /* I hate to have to do this here and again when the target is
     * acquired.  The problem is that I need to get information from
     * the spell to do the targeting, so I need to do setup for that.
     * I also want to allow the spell to be configured depending on
     * the targets, so I need to do setup for that as well.  The
     * alternative to repeating setup is to have a separate config
     * hook that only gets called after targets are found.  For now
     * I'm leaning toward repeating setup.
     */
    if (spell->do_spell_setup(0))
    {
        return 1;
    }
#endif

    if (spell->query_spell_pretarget())
    {
        gTargets = spell->target_spell(gCaster, arg);
    
        if (!sizeof(gTargets))
        {
            return 1;
        }
    }

    if (spell->do_spell_setup(gCaster, gTargets, arg))
    {
        return 1;
    }

    return spell->concentrate_spell(gCaster, gTargets, arg);
}

/* 
 * Function name: do_command
 * Description:   Called to initiate the actual spell casting
 * Returns:       1 - success
 *                0/string - failure
 */
nomask public mixed
do_command(string verb, string arg)
{
    gArg = arg;
    return get_spell_object(verb)->cast_spell(gCaster, gTargets, arg);
}

/* 
 * Function name: exist_command
 * Description  : Check if a spell exists.
 * Returns      : 1/0 depending on success.
 */
nomask public int
exist_command(string verb)
{
    return !!gSpells[verb];
}

public object *
query_targets()
{
    return gTargets;
}

public string
query_arg()
{
    return gArg;
}

public object
query_caster()
{
    return gCaster;
}

/*
 * Function name: cleanup_spells
 * Descrption:    A utility function that removes any *cloned* spell objects.
 *                This should generally be called when this spellcasting object
 *                is removed so that there are no lingering spell objects left,
 *                wasting memory.
 *                See /d/Genesis/newmagic/examples/spell_test. for an example.
 */
public void
cleanup_spells()
{
    int i;
    object *spells;

    spells = map(m_indices(gSpells), get_spell_object);
    for (i = 0; i < sizeof(spells); i++)
    {
        if (spells[i] && (file_name(spells[i]) != MASTER_OB(spells[i])))
        {
            spells[i]->remove_object();
        }
    }
}    
