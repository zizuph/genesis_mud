/* Automatically call do_despawn() when an NPC has not encountered a living
 * for a given period of time.
 *
 * For proper function, call reset_despawn() in init_living(). For example,
 * to ignore NPCs:
 *
 * void
 * init_living()
 * {
 *     ::init_living();
 *     if (interactive(TP))
 *         reset_despawn();
 * }
 *
 * Call init_despawn(delay) (default 120.0) to turn on. Can be done in
 * create_monster() or as needed
 *
 */
#include "defs.h"

int   despawn_alarm = 0;
float despawn_delay;

public void reset_despawn();

public void
do_despawn()
{
    TELL_CAN_SEE(E(TO), QCTNAME(TO) + " strays out of view.\n");
    this_object()->remove_object();
}

public void
check_despawn()
{
    if (!E(TO)) {
        KLOG("ghoul", implode(STACK,"\n"));
        return;
    }

    if (this_object()->query_attack() || sizeof(FILTER_PLAYERS(AINV(E(TO)))))
        reset_despawn();
    else
        do_despawn();
}

public void
reset_despawn()
{
    if (despawn_alarm != 0)
    {
        remove_alarm(despawn_alarm);
        despawn_alarm = set_alarm(despawn_delay, 0.0, &check_despawn());
    }
}

public void
init_despawn(float delay = 120.0)
{
    despawn_delay = delay;
    despawn_alarm = -1;
    reset_despawn();
}
