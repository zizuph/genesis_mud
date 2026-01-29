#define LIVE_I_RAUM_UNDEAD_KILLED    "_live_i_raum_undead_killed"
#define LIVE_I_KILLED_CHOGAROS       "_live_i_killed_chogaros"
#define SUMMON_COUNT        15

/* When an undead is killed, within the standard undead.c do_die function,
 * the player's property is added to, using an add_prop()
 * Additionally, there needs to be a check that will call the actual
 * summoning code that brings the lich in.
 */

void
do_die(object killer)
{
    killer->inc_prop(LIVE_I_RAUM_UNDEAD_KILLED, 1);
    if (!find_living("chogaros"))
    {
        if (((killer->query_prop(LIVE_I_RAUM_UNDEAD_KILLED)) > SUMMON_COUNT) &&
            !(killer->query_prop(LIVE_I_KILLED_CHOGAROS)))
        {
            objectp("/d/Raumdor/development/shanoga/common/npc/lich.c")->move(ENV(killer))
            killer->add_prop(LIVE_I_KILLED_CHOGAROS);
            killer->remove_prop(LIVE_I_RAUM_UNDEAD_KILLED);
            add_alarm(600.0,0.0,killer->remove_prop(LIVE_I_KILLED_CHOGAROS));
        }
    }
    ::do_die(killer);
}