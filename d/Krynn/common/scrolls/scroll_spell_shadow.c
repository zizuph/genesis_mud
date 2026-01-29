/*
 *  /d/Sparkle/area/city/auction/obj/scroll_spell_shadow.c
 *
 *  This shadow allows scrolls to cast a spell from a one use scroll
 *
 *  Created November 2016 by Britanica
 */
#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include <files.h>


/*
 * Function:    has_sufficient_skill
 * Description: This function is called by can_start_ability
 *              Shadowing to allow one shot scrolls
 * Arguments    : n/a
 * Returns      : n/a
 */
public int
has_sufficient_skill(object who)
{
    this_player()->catch_tell("Shadow has_sufficient_skill returning 1.\n");
    return 1;
}

/*
 * Function:    : query_is_restricted
 * Description  : This function is called by can_start_ability
 *                Shadowing to allow one shot scrolls
 * Arguments    : object actor - check for already casting
 * Returns      : 1 
 */
public int
query_is_restricted(object actor)
{
    return 1;
}

/*
 * Function:    : query_is_restricted
 * Description  : This function is called by can_start_ability
 *                Shadowing to allow one shot scrolls
 * Arguments    : object actor - check for already casting
 * Returns      : 1 
 */
public string *
query_spell_ingredients (int bShowAlways = 0)
{
    string * result = ({ });
    result += ({ "parchment" });
    if (!objectp(result))
    {
        write("not an objectp.\n");
    }
    else
    {
        write("string * with " + sizeof(result) + " length.\n");
    }
    return ({ });
}

/*
 * Function:    query_spell_can_be_learned
 * Description: This function is called by can_start_ability
 *              Shadowing to allow one shot scrolls
 */
public int
query_spell_can_be_learned(object who)
{
    this_player()->catch_tell("shadow query_spell_can_be_learned returning 1.\n");
    return 1;
}

/*
 * Function:    find_components
 * Description: This function is called by can_start_ability
 *              Shadowing to allow one shot scrolls
 */
public varargs mixed
find_components(object caster, mixed component_list, object *itemlist)
{
    object scroll = present("parchment", caster);
    write("Finding components.\n");
    return ({ scroll });
}

/*
 * Function:    query_ability_prep_time
 * Description: Function that overrides the default prep time
 *              Shadowing to allow one shot scrolls
 */
public int 
query_ability_prep_time()
{
    return 1;
}

/* Unmaskable 
public void
can_execute_ability(object actor, mixed * targets, string arg)
{
    write("can_execute_ability called.\n");
}

public void
resolve_spell(object caster, mixed *targets, int *resist, int result)
{
    write("resolve_spell called.\n");
}
*/