/*

  Distant tell spell
  
 */

#include "spells.h"
#include <filter_funs.h>
#include <composite.h>
#define GENESIS_SPELL_DIR    "/d/Genesis/newmagic/"
#define SPELL_TELL    (GENESIS_SPELL_DIR + "spells/tell")

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
do_stell_spell( object caster, object *targets, int *resist, int result )
{

        caster->catch_tell( "With the power the Sindar has bestowed "+
            "upon you, you send a message to " + 
            targets[0]->query_met_name() + ".\n" );

    targets[0]->catch_tell( "With the power of the Sinda, "+
        caster->query_art_name(targets[0]) + " tells you:\n" +
        break_string( query_tell_message(), 60, "\t" ) + "\n" );

}



int
create_stell_spell(object caster, string args, object *targets)
{
    default_heren_istimor_spell_config();
    set_spell_time(1);
    set_spell_mana(5);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_OCCUP) / 2));
    set_spell_ingredients(0);
    set_spell_peaceful(0);
    set_spell_element(SS_ELEMENT_AIR, 1);
    set_spell_form(SS_FORM_CONJURATION, 1);
    set_spell_effect(do_stell_spell);
}
