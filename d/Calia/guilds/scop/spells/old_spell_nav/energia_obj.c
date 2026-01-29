/*

    Object for the Energia spell for the SCoP. 

    Coded by Bishop of Calia, 04. aug. 2004.
*/

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

#include "defs.h"
#include SPIRIT_HEADER

#define TEMP_I_SYNDESI_DISABLE "_temp_i_syndesi_disable"

object linked_person;
string other_desc;


/* This function returns true if we are allowed to share damage with them */
int
check_applicable(object ob)
{
    if (!objectp(ob))
    {
        return 0;
    }
    if (ob->query_linkdead())
    {
        return 0;
    }
    if (ob->query_prop(TEMP_I_SYNDESI_DISABLE))
    {
        return 0;
    }
    if (ob != shadow_who)
    {
        if (!objectp(ob->has_syndesi_shadow()))
        {
            return 0;
        }
    }


    return 1;
}


varargs public int
dispel_spell_effect(object dispeller)
{
    shadow_who->catch_msg("The magical energies connecting you to " + 
        other_desc + " dissipate, and the link is severed.\n");
    
    if (objectp(linked_person))
    {
        linked_person->remove_link();
    }
    
    remove_spell_effect_object();

    return 1;
}

/* Check if the link is severed. */
void
check_dispel()
{
    if (!(check_applicable(shadow_who) && check_applicable(linked_person)))
    {
        dispel_spell_effect();
    }
}

public int
start()
{
    int duration;

    set_spell_effect_desc("spiritual link");

    if (!shadow_me(spell_target))
    {
        return 0;
    }
    
    if (shadow_who == spell_caster)
    {
        duration = spell_caster->query_stat(SS_WIS) + 
            spell_caster->query_stat(SS_OCCUP) + 
            spell_caster->query_casting_bonus();
        duration = duration * 3; 
        
        
        set_alarm(itof(duration), 0.0, &dispel_spell_effect());
    
    }

    set_alarm(10.0, 10.0, &check_dispel());  
    
    return 1;
}

void
remove_link()
{
    shadow_who->catch_msg("The magical energies connecting you to " + 
        other_desc + " dissipate, and the link is severed.\n");
        
    remove_spell_effect_object();        
}
    

/*
   This function is to identify someone as being under the effects of the spell
 */
object
has_syndesi_shadow()
{
    return shadow_who;
}

/* 
   This function is called from the spell to set up the other member of the link
*/
void
set_linked(object linkee)
{
    linked_person = linkee;
    
    //To use for description in case the linked person is not available
    //when the spell ends:
    other_desc = linked_person->query_the_name(shadow_who);
}



/* Shadowed functions below this point. */

void
heal_hp(int hp)
{
    string msg;

    if (check_applicable(linked_person) && check_applicable(shadow_who))
    {
        hp = hp/2;
        
        
        linked_person->add_prop(TEMP_I_SYNDESI_DISABLE, 1);
        linked_person->heal_hp(hp);
        linked_person->remove_prop(TEMP_I_SYNDESI_DISABLE);
        
        if (hp >= 20)
        {
            msg = "Warmth floods into you through your link to " 
            + shadow_who->query_the_name(linked_person) + ".\n";
        }
        else
        if (hp <= -20)
        {
            msg = "Pain blossoms through your link to " +
                shadow_who->query_the_name(linked_person) + ".\n";
        }
        
        
        if (strlen(msg))
        {
            linked_person->catch_msg(msg);
        }
        
        if (linked_person->query_hp() <= 0)
        {
            linked_person->do_die(shadow_who);
        }
    
    }
   
    shadow_who->heal_hp(hp);
}

void
add_mana(int sp)
{
    string msg;

    if (check_applicable(linked_person) && check_applicable(shadow_who))
    {
        sp = sp/2;
        
        linked_person->add_prop(TEMP_I_SYNDESI_DISABLE, 1);
        linked_person->add_mana(sp);
        linked_person->remove_prop(TEMP_I_SYNDESI_DISABLE);
        
        if (sp >= 20)
        {
            msg = "Energy floods into you through your link to " 
            + shadow_who->query_the_name(linked_person) + ".\n";
        }
        else
        if (sp <= -20)
        {
            msg = "Energy drains from you through your link to " +
                shadow_who->query_the_name(linked_person) + ".\n";
        }
        
        
        if (strlen(msg))
        {
            linked_person->catch_msg(msg);
        }
    }
   
    shadow_who->add_mana(sp);
}