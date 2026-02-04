/* death.c created by Shiva@Genesis.
 * This file takes care of what should happen to a vampire upon death.
 * This is part of the vampire guild shadow.
 */

#include "../guild.h"
#include <stdproperties.h>

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
  
    return clone_object(OBJ_DIR + "vamp_dust");
}

/*
 * Function name: death_sequence
 * Description:   Start the vampire death sequence
 */
void death_sequence()
{
  
    if (!QSW->query_ghost())
    {
        return;
    }
  
    SW->catch_tell(
        "Your soul almost slips away, but your preternatural flesh "+
        "maintains its immortal grip, pulling your soul back to you.\n\n"+
        "Suddenly you lose all senses.  You know, however, that you "+
        "are moving...somehow...back to your precious resting place.\n\n");
  
    tell_room(environment(QSW),
        capitalize(POSS(QSW)) + " body crumbles to the ground, "+
        "disintegrating into a clear dust as a heavy, swirling mist "+
        "rises from the ashes and drifts away.\n", QSW);
  
    setuid();
    seteuid(getuid());
  
    clone_object(OBJ_DIR+"death_ob")->move(QSW,1);

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
    return QSW->second_life(killer);
}

/*
 * Function name: vampire_death
 * Description:   Officially kill a vampire...i.e. make a vampire mortal
 *                again.
 * Arguments:     object ob - The object causing the death (passed to do_die())
 */
varargs void remove_vampire()
{
    query_manager()->remove_member(QSW->query_real_name());
 
    if (QSW->remove_cmdsoul(SOUL_DIR+"occ_soul"))
    {
        (SOUL_DIR+"occ_soul")->remove_spells(QSW);
        QSW->update_hooks();
    }
    if (QSW->remove_cmdsoul(SOUL_DIR+"cm_soul"))
    {
        QSW->update_hooks();
    }
 
    QSW->clear_guild_stat(SS_OCCUP);
    QSW->clear_guild_stat(SS_LAYMAN);
    QSW->clear_guild_stat(SS_RACE);

    QSW->catch_tell("You feel your soul losing its grip on your immortal "+
    "form, fading away from the darkness that granted you eternal "+
    "life.\n\n\n");
    
    QSW->remove_prop(LIVE_I_UNDEAD);
    COFFIN_MANAGER->remove_coffin(QSW);

    tell_room(environment(QSW),
        QCTNAME(QSW) + "'s body suddenly crumbles to the ground, "+
        "disintegrating into a clear dust as a heavy, swirling mist "+
        "rises from the ashes and drifts away.\n", QSW);

    //Reset their default start loc 
    QSW->set_default_start_location(QSW->query_def_start());
    QSW->move_living("M", QSW->query_def_start(), 1, 0);

    write_file(VAMP_JOIN_LOG,ctime(time())+ ":  "+
        QSW->query_real_name()+ " has left the guild.\n");

    QSW->remove_subloc(HAIR_SUBLOC,TO);
    QSW->remove_subloc(EYES_SUBLOC,TO);
    QSW->remove_subloc(INCOGNITO_SUBLOC,TO);
    QSW->remove_subloc(SKIN_SUBLOC,TO);

    QSW->remove_skill(VAMP_SKILL_BITE);
    QSW->remove_skill(VAMP_SKILL_FLURRY);
    QSW->remove_skill(VAMP_BLOOD);
    QSW->remove_skill(VAMP_FAVOR);

    QSW->set_guild_pref(SS_LAYMAN, 0);
    QSW->set_guild_pref(SS_RACE, 0);
        
    remove_guild_occ();
}
