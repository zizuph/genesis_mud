/*
 * Vekpos Poison for the Spirit Circle.
 *
 */
#pragma strict_types
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

int ill_alarm = 0;

void 
create_poison_effect()
{
    ::create_poison_effect();
    set_name("Scop Vekpos Poison");
    set_interval(20);
    set_silent(2);
    set_time(300);
    set_damage(({ POISON_HP, 150, 
                  POISON_FATIGUE, 75,
		  POISON_STAT, SS_CON}));
    set_strength(100);
    set_poison_type("scop_vekpos_poison");
}

public void
timeout()
{
    tell_object(poisonee, "You feel the effects of the holy prayer disappear.\n");
    ::timeout();
}

void feel_ill()
{
    if(!poisonee) return;
    poisonee->catch_tell("You feel ill and feeble from the prayer.\n");
}

void feel_ill_cont()
{
    if(!poisonee) return;
    poisonee->catch_tell("You feel more ill from the effects of the holy prayer.\n");
}

public varargs void
start_poison(object poisoner)
{
    set_alarm(1.0, 0.0, &feel_ill());
    ill_alarm = set_alarm(20.0, 20.0, &feel_ill_cont());
    ::start_poison(poisoner);
}



