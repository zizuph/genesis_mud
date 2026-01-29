/*
 * The bandage effect object.
 *
 * This object will heal a player for a certain % of his max
 * health every HEAL_INTERVAL seconds HEAL_TICKS tmes.
 *
 * Cotillion - 2008
 */
inherit "/std/object";

#include <files.h>
#include <stdproperties.h>

#define HEAL_INTERVAL 6     /* second interval */
#define HEAL_AMOUNT   10    /* % of max hp */
#define HEAL_TICKS 8        /* number of heals */

static object me;
static int effect_count, previous_health;

void stop_bandage();

void
create_object()
{
    set_name("_bandage_effect");
    set_short("bandage effect");

    set_no_show();
    
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
}

void
bandage_effect()
{
    if (!objectp(me) || (me->query_hp() <= 0) || me->query_attack() ||
        me->query_combat_time() > (time() - (HEAL_INTERVAL * 2)) ||
        me->query_hp() == me->query_max_hp() ||
        me->query_hp() < previous_health ||
        sizeof(FILTER_POISON_OBJECTS(all_inventory(me))))
    {
        stop_bandage();
        return;
    }
    
    effect_count++;
    me->catch_msg("You feel healthier.\n");
    me->heal_hp(me->query_max_hp() * 10 / 100);
    previous_health = me->query_hp();
    
    if (effect_count == HEAL_TICKS)
        stop_bandage();
}

void
start_bandage()
{
    me = environment();
    previous_health = me->query_hp();
    
    set_alarm(itof(HEAL_INTERVAL), itof(HEAL_INTERVAL), bandage_effect);
}


void
stop_bandage()
{
    remove_object();
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (objectp(to))
        start_bandage();
}

