/*
 * Air blast
 *
 * by jeremiah 950625
 */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>


public object *airblast_target(string arg);
public void airblast_message(object caster, object target, mixed hitresults);
public mixed airblast_success(object caster, object *targets);
public void airblast_fail();


public void
create_spell_airblast()
{
    set_element(SS_ELEMENT_AIR, 40);
    set_form(SS_FORM_CONJURATION, 20);

    set_spell_time(3);

    /* set_ingredients("cotton wool"); */

    set_mana_spell(10); /* low mana cost for test purposes ONLY */
    set_find_target(airblast_target);

    set_spell_message(airblast_message);
    set_spell_success(airblast_success);
    set_spell_fail(airblast_fail);
}


public int
air_blast(string str)
{
    return cast_spell();
}

public object *
airblast_target(string str)
{
    object target;

    if (!str)
    {
       write("You need to specify a target.\n");
       return 0;
    }

    target = present(str,E(query_caster()));

    if(target == query_caster())
    {
       write("Are you mad ? Airblast yourself ?\n");
       return 0;
    }

    if (!target)
    {
       write("There is no such ting here.\n");
       return 0;
    }

    if (!living(target))
    {
       write("You can only airblast a living being.\n");
       return 0;
    }

    return ({ target });
}

public void
airblast_message(object caster, object target, mixed hitresults)
{
    object *nomsg;

    nomsg = ({ caster }) + ({ target });

    target[0]->catch_msg("Suddenly you are hit by a tremendous " +
        "invisible force. You are thrown voilently backwards through " +
        "the air unable to hold on to anything.\n");

    tell_room(E(target[0]), QCTNAME(target[0]) + 
        " is suddenly hit by an invisible force. " + C(PRONOUN(target[0])) +
        " is thrown violently backwards through the air.\n", nomsg);

    caster->catch_msg("Your spell hits " + QCTNAME(target[0]) +
        " with a tremendous force. " + C(PRONOUN(target[0])) + " is " +
        "thrown violently backwards through the air.\n");
   
    seteuid(getuid());
    target[0]->command("drop all");
}


public mixed
airblast_success(object caster, object *targets)
{
    int result;

    if ((result = caster->resolve_task(TASK_SIMPLE,
          ({ SS_WIS, SKILL_AVG, SS_SPELLCRAFT, SS_ELEMENT_AIR,
             SS_FORM_CONJURATION, SKILL_END }) )) <= 0)
        return 0;

    return result;
}


public void
airblast_fail()
{
    tell_room(environment(query_caster()), QCTNAME(query_caster()) +
       " looks confused.\n");
    write("Something went wrong! You feel your energies flow into " +
       "nothingness. Your spell failed.\n");
}
