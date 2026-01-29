/* death.c created by Shiva@Genesis.
 * This file takes care of what should happen to a vampire upon death.
 * This is part of the vampire guild shadow.
 */

#include "../guild.h"
#include <stdproperties.h>

#define SW shadow_who

static int final_vamp_death;

/*
 * Function name: make_corpse
 * Description:   Specify an object that will be left behind
 *                as this vampire's corpse
 * Returns:       The object to be used as a corpse
 */
object make_corpse()
{
    setuid();
    seteuid(getuid());
  
    return clone_object(VAMP_OBJ_DIR + "vamp_dust");
}

/*
 * Function name: death_sequence
 * Description:   Start the vampire death sequence
 */
void death_sequence()
{
    if (final_vamp_death)
    {
        SW->death_sequence();
        return;
    }
  
    if (!SW->query_ghost())
    {
        return;
    }
  
    SW->catch_tell(
        "Your soul almost slips away, but your preternatural flesh\n"+
        "maintains its immortal grip, pulling your soul back to you.\n\n"+
        "Suddenly you lose all senses.  You know, however, that you\n"+
        "are moving...somehow...back to your precious resting place.\n\n");
  
    tell_room(E(SW),
        capitalize(POS(SW)) + " body crumbles to the ground, disintegrating into a " +
            "clear\ndust as a heavy, swirling mist rises from the ashes " +
            "and drifts away.\n", SW);
  
    setuid();
    seteuid(getuid());
  
    COTO(VAMP_OBJ_DIR + "death_ob", SW);
}

/* 
 * Function name: second_life
 * Description:   Called when this vampire dies, it handles
 *                a few things that should happen at the
 *                vampire's death.
 * Returns:       as second_life() on /std/player_sec.c
 */
int second_life(object killer)
{
    add_thirst(20);
    return SW->second_life(killer);
}

/*
 * Function name: vampire_death
 * Description:   Officially kill a vampire...i.e. make a vampire mortal
 *                again.
 * Arguments:     object ob - The object causing the death (passed to do_die())
 */
varargs void
vampire_death(object ob, int extra_xp_loss)
{
    final_vamp_death = 1;
  
    if (SW->query_default_start_location() == VAMP_STARTLOC)
    {
        SW->remove_default_start_location();
    }

#ifdef VAMP_CMDSOUL
    if (SW->remove_cmdsoul(VAMP_CMDSOUL))
    {
        SW->update_hooks();
    }
#endif

    SW->clear_guild_stat(SS_OCCUP);

    if (extra_xp_loss)
    {
        SW->add_exp(-SW->query_exp_combat() / 3);
    }

    SW->set_hp(0);
    SW->do_die(ob);
    remove_guild_occ();
}
