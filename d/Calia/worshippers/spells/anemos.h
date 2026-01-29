
/*
 * Anemos (Tell Line) Spell for the Elemental Worshippers of Calia
 * by Jaacar & Cirion (Thanks Cirion!)
 * July 23rd, 1996
 * Modifications by Maniac, 12/10/96
 * Mercade, 5Dec2004 - Wizards can hear this communication.
 */

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <options.h>
#include <filter_funs.h>
#include <flags.h>
#include <stdproperties.h>

#define FEATHER "_worshipper_feather_id_"

/* Looks like we have to store the tell message in a global
 * variable. Ugly, but it seems there is no way to send any
 * information between the target finding function and the
 * message bearing function, except for the pre-defined
 * caster and targets. 
 */

public string   anemos_msg;

/* Prototypes. Always handy. */

object *anemos_target(string str);
void anemos_message(object caster, object *targets);
string anemos_fail(); 

object gFeather;

public void
create_spell_anemos()
{
    set_spell_element(SS_ELEMENT_AIR, 10);  // Need 10 in Air spells
    set_spell_form(SS_FORM_DIVINATION, 10); // And 10 in Divination
    set_spell_time(1);                      // 3 seconds
    set_spell_mana(10);                     // 10 mana
    set_find_target(anemos_target);         // Target finding function
    set_spell_message(anemos_message);      // Successful send message
    set_spell_task(TASK_SIMPLE, 0);         // Not too hard to do ;)
    set_spell_fail(anemos_fail); 
}


string
anemos_fail()
{
    "You fail to reach Lady Aeria with your request.\n";
}

int
is_worshipper(object pl)
{
    return (pl->query_guild_name_lay() == GUILD_NAME); 
}

int
is_spirit(object pl)
{
    return (pl->query_skill(SS_SPIRIT_CHOSEN));
}

public int
anemos(string str)
{
    return cast_spell();
}


object
*anemos_target(string str)
{
    object   person;
    string  *strs,
             who,
             name;

    if(!str || !strlen(str))
    {
        write("Anemos whom?\n");
        return 0;
    }

    strs = explode(str, " ");  // break the message up into an array
    who = lower_case(strs[0]); // find_living needs lower cases
  
    if(sizeof(strs) > 1)  // make a sting message out of the rest of the array
        anemos_msg = implode(strs[1 .. sizeof(strs) - 1], " ");
    else
    {
        write("What message shall you send?\n");
        return 0;
    }

    person = find_player(who);
   
    if(!person || (!query_caster()->query_met(person) && !is_worshipper(person)))
    {
        if (!person || (!is_spirit(person)))
        {
            write("Anemos your message to whom?\n");
            return 0;
        }
    }

    if (!is_worshipper(person) && !query_caster()->query_wiz_level())
    {
        if (!is_spirit(person) && !query_caster()->query_wiz_level())
        {
            write("You cannot use the power of Anemos on one who does not "+
                "worship the Elementals.\n");
            return 0;
        }
    }

    if (person->query_wiz_level() && !is_worshipper(person))
    {
        if (person->query_wiz_level() && !is_spirit(person))
        {
            write("That mind is too distant for you to speak with.\n");
            return 0;
        }
    }

    if(person->query_linkdead())
    {
        write("Your message is lost in the void.\n");
        return 0;
    }

    if (person->query_wiz_level())
    {
        if ((person->query_wiz_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M) || 
            person->query_invis())
        {
            write("Your message is lost in the void.\n");
            return 0;
        }
    }

    return ({ person });
}

int
anemos_message(object caster, object *targets)
{
    object   person;
    string   message2, name;
    object *wizards;

    if(!sizeof(targets))  // Sanity check
        return 0;

    person = targets[0];

    if(person->query_met(this_player()))
        name = this_player()->query_name(); // Met? -> 'Cirion'
    else
        name = LANG_ADDART(this_player()->query_gender_string()) + " " +
            this_player()->query_race_name(); // Unmet? -> 'a male human'

    if (environment(person)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        message2 = "The water around your ear vibrates carrying "+
            "the voice of "+name+" saying:\n"+
            anemos_msg+"\n";
    }
    else
    {
        message2 = "A soft wind blows around your ears carrying "+
            "the voice of "+name+" whispering:\n"+
            anemos_msg+"\n";
    }
    person->catch_msg(message2);

    if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        caster->catch_tell("You speak silently into the water and it carries "+
            "your message away.\n");
    }
    else
        caster->catch_tell("You speak silently into the air and it carries your message away.\n");
    
    say(QCTNAME(caster)+" places "+C_HIS+" fingers upon "+C_HIS+" forehead briefly.\n");
    if (caster->query_option(OPT_ECHO))
        caster->catch_msg("You use the power of Anemos to speak to "+
            QTNAME(person)+": "+anemos_msg+"\n");

    /* Give the message to all wizards, too, if the target is in the room. */
    if (environment(caster) == environment(person))
    {
        wizards = FILTER_IS_WIZARD(all_inventory(environment(this_player()))) -
            ({ caster, person });
        wizards->catch_tell("As wizard, you hear " + C_HIM + " speak: " + anemos_msg + "\n");
    }

    return 1;
}
