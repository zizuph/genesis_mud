inherit "/d/Emerald/npc/guard"; 

#include "../defs.h";
#include "../alarm.h"
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#define BOWFIRE_RATE (itof(20 / random(3 + 1)))

static int bowfire_alarm;

void stop_bowfire();

void 
create_guard() 
{
    config_guard(90); 

    set_name("bowman");

    setuid();
    seteuid(getuid());
    ALARM_NOTIFY;

}

/*
 * Function name: valid_target
 * Description:   See if the target can be fired upon
 * Arguments:     object target - the intended target
 * Returns:       1/0 - valid target/invalid target
 */
int
valid_target(object target)
{
    object env = environment(target);

    if (env->query_prop(ROOM_I_INSIDE) ||
        env->query_prop("_room_i_no_bowfire"))
    {
        return 0;
    }

    return 1;
}

/*
 * Function name: bowfire
 * Description:   Fire upon enemies
 */
void
bowfire()
{
    object *enemies;
    object target;

    if (query_attack())
    {
        return;
    }

    if (!sizeof(enemies = ALARM_ENEMIES) ||
        !sizeof(enemies = filter(enemies, valid_target)))
    {
        return;
    }

    target = enemies[random(sizeof(enemies))];

    tell_room(environment(this_object()), QCTNAME(this_object()) +
        " fires a bow.\n", this_object());

    target->hit_me((random(5000) ? 150 : 2000), W_IMPALE, this_object(), -1);

    target->catch_tell("An arrow hits you!\n");
}

/*
 * Function name: start_bowfire
 * Description:   Notify the object that it's time to start looking for
 *                targets on whom to fire.
 */
void
start_bowfire()
{
    if (!bowfire_alarm)
    {
        bowfire_alarm = set_alarm(BOWFIRE_RATE, BOWFIRE_RATE, bowfire);
    }
}

/*
 * Function name: stop_bowfire
 * Description:   Cease firing on targets
 */
void
stop_bowfire()
{
    if (bowfire_alarm)
    {
        remove_alarm(bowfire_alarm);
        bowfire_alarm = 0;
    }
}

/*
 * Function name: alarm_activated
 * Description:   This is called when the outpost alarm has been activated
 */
void
alarm_activated()
{
    start_bowfire();
}

/*
 * Function name: alarm_deactivated
 * Description:   This is called when the outpost alarm has been deactivated
 */
void
alarm_deactivated()
{
    stop_bowfire();
}
