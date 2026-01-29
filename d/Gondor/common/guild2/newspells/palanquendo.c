/* Modified by Eowul on 6-9-2004 to allow NPC's to cast during combat
 *
 * 2007-05-10, Toby:
 *    Modified the spell to be able to cast it in combat
 *    to a higher cost naturally.
 */


#include "spells.h"
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"


inherit SPELL_TELL;
inherit SPELL_INHERIT;

public object *find_tell_targets( object caster, string str )
{
    return spell_target_one_distant_living( caster, str );
}

void hook_targets_gone()
{
    write( "Your message couldn't reach its destination and was lost in "+
        "the void.\n" );
}

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
    string cast_str = one_of_list( ({
                         "With the power the Dark Lord has bestowed upon you, you tell ",
                         "Using the powers the Black Master has bestowed upon you, you tell ",
                         "With a touch of the Dark Lord's powers, you tell ",
                         "Using a touch of the power the Black Master has granted you, you tell ",
                         }) );
    if (check_mage( caster ))
    {
        return;
    }
    
    if(targets[0]->query_wiz_level())
    {
	    caster->catch_tell("The Dark Lord does not intend for you to contact immortals this way.\n");
	    return;
    }
    
    can_see_caster( caster )->catch_msg( "Employing Dark Sorcery, "+
        QTNAME( caster ) + " casts a spell.\n" );
    if (caster->query_option( OPT_ECHO ))
    {
        caster->catch_tell( cast_str + targets[0]->query_met_name()+ 
            ":\n"+ break_string( query_tell_message(), 60, "\t" )+ "\n" );
    }
    else
    {
        caster->catch_tell( "With the power the Dark Lord has bestowed "+
            "upon you, you send a message to " + 
            targets[0]->query_met_name() + ".\n" );
    }
    
    if (targets[0]->query_npc()) {
        targets[0]->hook_received_palanquendo(caster, query_tell_message());
    }
    
    targets[0]->catch_tell( "With the help of Dark Sorcery, "+
        caster->query_art_name(targets[0]) + " tells you:\n" +
        break_string( query_tell_message(), 60, "\t" ) + "\n" );
    IDLENESS->increase_activity( caster, SMALL_SPELL );
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "palanquendo" );
    set_spell_desc( "Far tell." );
    set_spell_target(target_tell);
                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }

                                /*Special configuration for morgul npcs.  */
    if (caster->query_npc())
    {
        set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),2,5 ));
        set_spell_mana( 10 );
        set_spell_task( TASK_SIMPLE );
        set_spell_element( SS_ELEMENT_AIR, 10 );
        set_spell_form( SS_FORM_CONJURATION, 10 );
        set_spell_visual( 0 );
        set_spell_vocal( 0 );
        set_spell_ingredients( 0 );
        set_spell_resist( 0 );
        set_spell_peaceful( 0 );
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time(max(spell_resolve_time( caster->query_stat(SS_OCCUP),2,5 ),NORMAL_SPELL_I_MIN_PREP_TIME));
    set_spell_task( TASK_SIMPLE );
    set_spell_element( SS_ELEMENT_AIR, 10 );
    set_spell_form( SS_FORM_CONJURATION, 10 );
    set_spell_visual( 0 );
    set_spell_vocal( 0 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        if(caster->query_attack())
        {
            set_spell_mana( 30 );
            set_spell_ingredients( ({ "silver coin" }) );
        }
        else
        {
            set_spell_mana( 10 );
            set_spell_ingredients( ({ "copper coin" }) );
        }
    }
    set_spell_resist( 0 );
    set_spell_peaceful( 0 );
    return 0;
}
