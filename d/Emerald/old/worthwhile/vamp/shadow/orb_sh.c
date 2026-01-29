inherit "/std/shadow";

#include "../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>

#define SW       shadow_who
#define WRITE(x) SW->catch_tell(x)
#define TELL_ROOM(x) tell_room(environment(SW), x, SW)

void finish();
void remove_vamp_orb_shadow();

void
do_die(object killer)
{
    object sh, *obs;
    mapping m;
    int i, *prefs;

    if (SW->query_hp() > 0)
    {
        return;
    }

    setuid();
    seteuid(getuid());

    if (!(sh = clone_object(VAMP_SHADOW)))
    {
        SW->do_die(killer);
        return;
    }

    m = restore_map(VAMP_LOG_DIR + "member_save/old/" + SW->query_real_name());

    if (!m_sizeof(m))
    {
        SW->do_die(killer);
        return;
    }

    if (sh->make_new_vamp(SW, m["sire"], m["base_power_offset"], "Emerald") != 1)
    {
        SW->do_die(killer);
        return;
    }

    SW->notify_death(killer);
    killer->notify_you_killed_me(SW);
    SW->query_combat_object()->cb_death_occured(killer);
    killer->stop_fight(SW);

    WRITE("As you fall to the ground, a strange sensation overcomes you.  " +
       "Looking down, you notice that the aperture in the mithril orb " +
       "has opened.  Black tendrils corruscating with energy issue forth " +
       "from the opening, wrapping around you, their immaterial form " +
       "penetrating your body.  A rush of memories and emotions overcomes " +
       "you, as if from the consciousness of several beings.  The tendrils " +
       "dissipate into your body, and you feel a pulse of energy jolt your " +
       "heart, sending a paralyzing wave of pain through you.\n");

    TELL_ROOM("As " + QTNAME(SW) + " falls to the ground, black tendrils " +
        "corruscating with energy issue forth from the mithril orb " +
        SW->query_pronoun() + " is holding.  They envelop and penetrate " +
        SW->query_possessive() + " body and quickly dissipate.\n" +
        "Suddenly, " + QTNAME(SW) + "'s body arches as if overcome by " +
        "unbearable pain.\n");

    obs = ({ SW->query_tool(W_RIGHT),
             SW->query_tool(W_LEFT),
             SW->query_tool(W_BOTH) }) - ({ 0 });

    obs = filter(obs, not @ &->move(environment(SW)));

    if (sizeof(obs))
    {
        TELL_ROOM(QCTNAME(SW) + " drops " + COMPOSITE_ALL_DEAD(obs) + ".\n");
    }

    set_alarm(12.0, 0.0, finish);

    clone_object(VAMP_OBJ_DIR + "paralysis")->move(SW, 1);

    MANAGER->set_generation(SW, m["generation"]);

    /* Don't quite give them back all their age */
    i = SW->query_age() - m["start_age"];
    i = (random(i) + random(i) + random(i) + random(i)) / 4;
    MANAGER->set_start_age(SW, m["start_age"] + i);

    /* Restore guild xp */
    m = restore_map(VAMP_LOG_DIR + "saved_xp");
    if (i = m[SW->query_real_name()])
    {
        SW->set_guild_stat(SS_OCCUP, i);
    }
      
    write_file(VAMP_LOG_DIR + "embrace.log", 
        SW->query_real_name() + " RESTORED " + ctime(time()) + "\n");
}

void finish()
{
    filter(all_inventory(SW), &->id("vamp_paralysis_ob"))->remove_object();
    WRITE("Slowly, the pain recedes, replaced with the new, but " +
       "familiar, sensation of preternatural essence.\n");
    TELL_ROOM(QCTNAME(SW) + "'s body slowly relaxes, and " +
       SW->query_pronoun() + " rises to " + SW->query_possessive() +
       " feet--obviously shaken, but also appearing strangely--even " +
       "supernaturally--revitalized.\n");

    remove_vamp_orb_shadow();
}

void
remove_vamp_orb_shadow()
{
    remove_shadow();
}

int
query_vamp_orb_shadow()
{
    return 1;
}
