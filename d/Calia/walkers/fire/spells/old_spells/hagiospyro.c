
 /*
  *
  * Hagiospyro (Holy Fires) spell for the Firewalkers of Thalassia
  * by Jaacar   August 7th, 1996
  * coverted to the new spell system May 19th, 1998
  *
  */

#pragma strict_types

inherit "/d/Genesis/magic/spells/bolt";
inherit "/d/Genesis/magic/targeting";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>
#include <composite.h>
#include <stdproperties.h>
#include "defs.h"
#include FIRE_HEADER

public int create_spell_hagiospyro(object caster, object *targets,
    string argument);
private void desc_hagiospyro_casting(object caster, object *targets);
private void desc_hagiospyro_damage(object caster, object *targets, mixed *results);
private void desc_hagiospyro_miss(object caster, object target);

private object *
hagiospyro_target_one_other_present_living(object caster, string str)
{
    object *oblist;

    if (!strlen(str))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You "+
            "can only select one target.\n");
        return ({});
    }

    if (!present("_hagiospyro_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "hagiospyro potion.\n");
        return ({});
    }

    if (environment(caster)->query_prop(ROOM_UNDER_WATER))
    {
        write("You cannot use the power of Hagiospyro underwater!\n");
        return ({});
    }
    return oblist;
}

public int
create_spell_hagiospyro(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_PRAYER, 60);
    set_spell_ingredients(({ }));  // Uses a potion
    set_spell_time(3);
    set_spell_mana(216);
    set_spell_task(TASK_ROUTINE+100);
    set_bolt_pen(600);
    set_bolt_desc("holy fires");
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_bolt_casting_msg(desc_hagiospyro_casting);
    set_bolt_damage_msg(desc_hagiospyro_damage);
    set_bolt_miss_msg(desc_hagiospyro_miss);
    return 0;
}

private int
try_to_hit(object caster, object target)
{
    /* Should make a better formula */
    return (target->resolve_task(TASK_ROUTINE+100, ({ TS_DEX, SS_DEFENSE })) > 0);
}

private void
desc_hagiospyro_casting(object caster, object *targets)
{
    string msg, his, he, bolt;

    his = caster->query_possessive();
    he = caster->query_pronoun();

    caster->catch_tell("You close your eyes and concentrate on the "+
        "image of "+FO_COMPOSITE_ALL_LIVE(targets, caster) + " and "+
        "summon forth the powers granted to you by Lord Pyros.\n" +
        "Upon opening your eyes, you see massive red clouds rolling "+
        "in from the north.  They stop moving above you, and grow in "+
        "volume rapidly.  They do not appear to be clouds any longer, "+
        "but rather massive volumes of fire gathering in the sky.\n"+
        "With a slight nod of your head, the flames form a massive red "+
        "fireball that plummets down towards "+
        FO_COMPOSITE_ALL_LIVE(targets, caster)+".\n");

    targets->catch_tell(caster->query_The_name(targets)+" closes "+C_HIS+
            " eyes for a moment.  When "+C_HE+" opens them again, "+
            "massive red clouds begin rolling in from the north.\n"+
            "They stop moving above you, and grow in volume rapidly.  "+
            "They do not appear to be clouds any longer, but rather "+
            "massive volumes of fire gathering in the sky.\nWith a "+
            "slight nod of "+caster->query_the_name(targets)+"'s head, "+
            "the flames form a massive red fireball that plummets down "+
            "toward you.\n");
                           
    caster->tell_watcher(QCTNAME(caster)+" closes "+C_HIS+" eyes for "+
            "a moment.  When "+C_HE+" opens them again, massive red "+
            "clouds being rolling in from the north.  They stop moving "+
            "above you, and grow in volume rapidly.  They do not appear "+
            "to be clouds any longer, but rather massive volumes of fire "+
            "gathering in the sky.\nWith a slight nod of "+QTNAME(caster)+
            "'s head, the flames form a massive red fireball that plummets "+
            "down towards "+
            FO_COMPOSITE_LIVE(targets, caster)+".\n", targets);
}

private void
desc_hagiospyro_damage(object caster, object target, mixed *result)
{
    string how;

    switch (result[0])
    {
    case 0..10:
        how = "licking "; 
        break;
    case 11..20:
        how = "scorching "; 
        break;
    case 21..30:
        how = "burning "; 
        break;
    case 31..40:
        how = "withering "; 
        break;
    case 41..70:
        how = "shrivelling "; 
        break;
    case 71..99:
        how = "consuming "; 
        break;
    default:
        break;
    }

    if (!how) // Death Blow
    {
        caster->catch_tell("The fireball hits "+
            target->query_the_name(caster)+" in its entirety, leaving "+
            "nothing but "+T_HIS+" burning corpse on the ground.  The sky "+
            "returns to normal.\n");
        target->catch_tell("The fireball hits you in its "+
            "entirety, devestating you completely and leaving nothing "+
            "but your burning corpse on the ground.  The "+
            "sky returns to normal.\n");
        caster->tell_watcher("The fireball hits "+
            target->query_the_name(caster)+" in its entirety, leaving "+
            "nothing but "+T_HIS+" burning corpse on the ground.  The sky "+
            "returns to normal.\n",target);
    }

    else // All other blows
    {
        caster->catch_tell("The fireball strikes " + 
            target->query_the_name(caster) + ", " + how + T_HIM +
            ".  The sky returns to normal.\n");

        target->catch_tell("The fireball strikes you, " +how+
            "you.\nThe sky returns to normal.\n");

        caster->tell_watcher("The fireball strikes " + 
            QTNAME(target) + ", " + how + T_HIM +
            ".  The sky returns to normal.\n",target); 
    }
}

private void
desc_hagiospyro_miss(object caster, object target)
{
    string bolt = "The fireball just misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher(bolt + QCTNAME(target) + ".\n", target);
}
