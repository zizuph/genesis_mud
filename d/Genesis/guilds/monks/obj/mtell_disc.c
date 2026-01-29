/*
 * File:      mtell_disc
 * Created:   Cirion, 1998.08.16
 * Purpose:   disc that allows monks to send messages to
 *            each other. They can be prayed for in the
 *            chapel.
 * Form:      SS_FORM_DIVINATION (1)
 * Element:   SS_ELEMENT_AIR (1)
 * Mana:      10 (note that there is also a mana cost associated
 *                with obtaining the disc)
 * Delay:     4
 * Ingedient: This object 
 * Modification Log:
 *
 */
#pragma strict_types

#include "defs.h"
#include <tasks.h>      /* spellcasting tasks  */
#include <ss_types.h>   /* spellcasting skills */
#include <flags.h>      /* busy statuses       */
#include <math.h>       /* NAME_TO_RANDOM()    */

#define MTELL_OBJECT   "_monk_mtell_object"

inherit "/d/Genesis/magic/spellcasting";
inherit "/d/Genesis/magic/spells/tell";
inherit "/std/object";
inherit "/lib/keep";
inherit MONKLIB;

public string   tell_msg;
public int      mtell_recoverable;

public int create_spell_tell(object caster, object *targets, string argument);
object *find_tell_targets(object caster, string str);
string tell_fail(); 

void
create_object()
{
    set_name("disc");
    add_name(MTELL_OBJECT);
    set_short("small iron disc");
    set_long("It is a small disc made from dull, beaten "
        + "iron. In the center of the disc is a tiny square hole. "
        + "The hole seems to shimmer and refract the light passing "
        + "through it.\n");
    
    add_spell("telioy", "Speak to distant Monks",
         create_spell_tell, target_tell);

    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_VALUE, 188);

    // set the flag to see if it will survive reboot (66% chance)
    mtell_recoverable = NAME_TO_RANDOM("C" + OB_NUM(this_object()),
        4324542, 3);

    set_keep();

    add_prop(OBJ_S_WIZINFO, "This spell object is used to "
        + "send a tell message to other monks. The ingredient "
        + "is the object itself (i.e., it can be used once, "
        + "and is consumed). It is prayed for in "
        + MONK_ROOM + "chapel\n"
        + "Form:    SS_FORM_DIVINATION (1)\n"
        + "Element: SS_ELEMENT_AIR (1)\n"
        + "Time:    4\n"
        + "Mana:    10\n");
}

public int
create_spell_tell(object caster, object *targets, string argument)
{
    // use all the other defaults for a tell spell
    ::create_spell_tell (caster, targets, argument);

    set_spell_element(SS_ELEMENT_AIR, 1); 
    set_spell_form(SS_FORM_DIVINATION, 1);
    set_spell_ingredients(({ MTELL_OBJECT }));
    set_spell_effect(tell);

    return 0;
}

void
list_spells()
{
    object      env;

    env = environment(this_object());

    // if we are not the first disc in the inventory, then
    // don't display, since we only want one spell to show
    // up.
    if(present(MTELL_OBJECT, env) != this_object())
        return;
    else
        return ::list_spells();
}


void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if(m_query_monk(env)) // spell is given only to monks
        add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    if(m_query_monk(env))
        remove_spell_object(env);
}

string
tell_fail()
{
    "Your call fails.\n";
}

public object *
find_tell_targets(object caster, string str)
{
    return tell_target_one_distant_guild_member(caster, str, MONK_OCC_NAME);
}

/*
 * Function name: query_recover
 * Description  : Check to see if the object will recover. 2/3rd
 *                of the discs will recover.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    if(mtell_recoverable)
        return MASTER + ":";
    else
        return "";
}

