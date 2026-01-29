/*
 * /d/Calia/eldoral/objects/vamp_moss.c
 *
 * Vampiric moss: Coded by Khail, Nov. 12/96.
 *
 * A very rare herb (available in 1 room in eldoral, which is a 
 * a death trap.) that drains health and mana from any living
 * it comes into contact with. It stores the hp and mana drained,
 * and will 'release' it to whoever eats it. It will not drain
 * when carried in a container, only if it's in a living's
 * 'direct' inventory. Also, it can only be given to npc's once,
 * they'll refuse to touch it after that (which will probably
 * make having a herbalist identify it a bitch *grin*)
 * But, because I'm such a nice guy, players who are being
 * drained and who've been idle for more than 10 minutes
 * will be forced to drop the moss to avoid being killed
 * by it while LD.
 *
 * Change log:   Baldacin, May 10, 2004.
 *                 I added to see if environment() was a valid
 *                 object before checking for herbs. In function
 *                 check_for_herbs().
 *               Petros, May 2008.
 *                 Due to abuses in the vampiric moss, the max
 *                 healing and mana restore has been capped at
 *                 300. This, I thought, is a reasonable number
 *                 since the difficulty to obtain the herb is
 *                 quite high, risking death.
 */
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include "../guru_quest.h"

#define NPC_I_NO_DRAIN_AGAIN "_npc_i_no_drain_again"
#define MANA                 50
#define HP                   100
#define MAX_HP_HEAL          300
#define MAX_MANA_RESTORE     300

int mana_drained,
    hp_drained,
    drain_alarm;

/*
 * Function name: hp_effect
 * Description  : Returns the total hp drained by the moss.
 * Arguments    : n/a
 * Returns      : Integer value of hp drained.
 */
public int
hp_effect()
{
    return hp_drained;
}

/*
 * Function name: mana_effect
 * Description  : Returns the total amount of mana drained by
 *                the moss.
 * Arguments    : n/a
 * Returns      : Integer value of total mana drained.
 */
public int
mana_effect()
{
    return mana_drained;
}

/*
 * Function name: create_herb
 * Description  : Turns this object into vampiric moss.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_herb()
{
    set_name("moss");
    add_name(C_GURU_MOSS_NAME);
    set_adj(({"blood", "red"}));
    set_herb_name("vampiric moss");
    set_short("blood red moss");
    set_pshort("blood red mosses");
    set_pname(({"mosses", "herbs"}));
    set_ingest_verb("eat");
    set_unid_long("This horrid-looking moss probably " +
        "came from a tree somewhere, but it looks like it's been " +
        "soaked in blood.\n");
    set_id_long("This is a piece of vampiric moss. It is a herb " +
        "of legend, incredibly rare and unknown to all but the " +
        "most skilled herbalists. Said to exist in only a handful " +
        "of the older places in the world, it has the power to " +
        "absorb health and mana from a being through skin contact. " +
        "Once eaten, however, it releases whatever it absorbed to " +
        "the person who ate it.\n");
    set_herb_value(5000);
    set_id_diff(90);
    set_find_diff(10);
    set_decay_time(5000);
    add_prop(OBJ_M_NO_SELL, "Nobody with a brain in their head " +
        "wants that moss within a mile of them, let alone their " +
        "inventory.\n");
    add_prop(OBJ_M_NO_BUY, 1);
}

/*
 * Function name: query_find_diff (MASK)
 * Description  : Returns the difficulty to find the herb.
 *                Masked here so we can make it easier than normal
 *                to find, since it's for a quest, but still have
 *                a finding difficulty otherwise that corresponds
 *                with the fact this herb only exists in one room.
 * Arguments    : n/a
 * Returns      : Find difficulty as an int 1 - 10
 */
public int
query_find_diff()
{
    if (calling_function() == "search_for_herbs")
        return 1;
    else
        return ::query_find_diff();
}

/*
 * Function name: drain_this
 * Description  : Attempts to drain the given object of health and
 *                mana.
 * Arguments    : who - Object pointer to the object to try to
 *                      drain.
 * Returns      : n/a
 */
public void
drain_this(object who)
{
    int mana,
        mana_remain,
        hp,
        hp_remain;

  /* Make sure we're in 'who's inventory. */
    if (who != environment())
        return;

  /* If somehow this got called while an alarm to it was already */
  /* running, cancel this call, and the alarm, and start a new */
  /* one. */ 
    if (get_alarm(drain_alarm))
    {
        remove_alarm(drain_alarm);
        drain_alarm = set_alarm(60.0, 0.0, &drain_this(environment()));
        return;
    }

    mana = MANA + random(MANA);
    hp = HP + random(HP);
    who->command("$wince");
    tell_object(who, "You suddenly feel a burning sensation from " +
        "around the blood red moss.\n");
    mana_remain = mana - who->query_mana();
    who->add_mana(-mana);
    hp_remain = hp - who->query_hp();
    who->heal_hp(-hp);

  /* Make it so npc's can only be drained once. Not very */
  /* realistic, but prevents players from using the moss */
  /* for free kills. */
    if (!interactive(who))
    {
        who->add_prop(NPC_I_NO_DRAIN_AGAIN, 1);
        who->command("emote suddenly looks horrified.");
        who->command("drop " + OB_NAME(this_object()));
    }

    if (hp_remain > 0)
        hp -= hp_remain;
    if (mana_remain > 0)
        mana -= mana_remain;
    hp_drained += hp;
    mana_drained += mana;

  /* Reset the effects to the new drained values. */
    clear_effect();
    set_effect(HERB_HEALING, "hp", hp_drained > MAX_HP_HEAL ?
                                   MAX_HP_HEAL : hp_drained);
    add_effect(HERB_HEALING, "mana", mana_drained > MAX_MANA_RESTORE ?
                                   MAX_MANA_RESTORE : mana_drained);

  /* Kill the player if we've drained all hp, otherwise reset */
  /* a new alarm to do this again in 60 seconds. */
    if (who->query_hp() <= 0)
        who->do_die(this_object());
    else
        drain_alarm = set_alarm(60.0, 0.0, &drain_this(who));

  /* A little safety to avoid killing players who've been idle */
  /* for 10 minutes or more. */
    if (interactive(who) && query_idle(who) >= 600)
        who->command("drop " + OB_NAME(this_object()));
}

/*
 * Function name: check_for_herbs
 * Description  : Looks in the moss's environment for other herbs
 *                for it to try and kill.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
check_for_herbs()
{
    object *herbs,
           to_decay;
    int i;

  /* Find all herbs in the environment that haven't been dried */
  /* and try to kill them (or dry them, as the case may be) */
    if (!objectp(environment()))
    {
    	/* If the herb doesnt have a valid environment
    	   who knows where we might be! bail out!
    	 */
    	return;
    }     
    herbs = all_inventory(environment()) - ({TO});
    herbs = filter(herbs, &not() @ &->id(C_GURU_MOSS_NAME));
    herbs = filter(herbs, &->query_herb_value());
    herbs = filter(herbs, &not() @ &->query_dried());
   
    if (!sizeof(herbs))
        return;

  /* Decay 10 herbs at random from the ones available. */
    for (i = 0; i < random(10); i++)
    {
        if (i > sizeof(herbs))
            break;
        to_decay = herbs[random(sizeof(herbs))];
        herbs -= ({to_decay});
        to_decay->decay();
    }
  
  /* Try again in another 60 seconds. */  
    set_alarm(60.0, 0.0, check_for_herbs);
}

/*
 * Function name: enter_env (MASK)
 * Description  : Called when this object enters a new environment.
 * Arguments    : to - Object pointer to the new environment.
 *                from - Object pointer to the last environment.
 * Returns      : n/a
 */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
  /* Do nothing if the destination environment is an npc that's */
  /* already been drained except force it to drop this herb. */
    if (to->query_prop(NPC_I_NO_DRAIN_AGAIN))
    {
        to->command("emote appears to have learned the hard " +
            "way what the blood red moss does, and drops it " +
            "instantly.");
        to->command("drop " + OB_NAME(this_object()));
        return;
    }
  /* If the environment is living, try to drain it. */
    if (living(to))
        drain_this(to);
  /* If the environment isn't living, look for herbs to */
  /* destroy. */
    else
        set_alarm(0.0, 0.0, check_for_herbs);       
}

/*
 * Function name: query_recover
 * Description  : Allows the herb to be recovered, and the
 *                health and mana drained vars to be saved.
 * Arguments    : n/a
 * Returns      : A full recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_herb_recover() +
        "$" + hp_drained + "$" + mana_drained;
}

/*
 * Function name: init_recover
 * Description  : Called when this object is loaded by the recovery
 *                routine. Parses out the hp and mana drained 
 *                variables from the recovery string and sets
 *                them as current values.
 * Arguments    : arg - String argument from the recovery string
 *                      generated by query_recover
 * Returns      : n/a
 */
public void
init_recover(string arg)
{
    string temp;
    sscanf(arg, "%s$%d$%d", temp, hp_drained, mana_drained);
    init_herb_recover(arg);
}

/*
 * Function name: stat_object (MASK)
 * Description  : Provides some information about this object
 *                when the stat command is used on it. Masked
 *                here to provide additional information about
 *                the health and mana drained by it.
 * Arguments    : n/a
 * Returns      : A formatted output string as described above.
 */
public string
stat_object()
{
    string str;

    str = ::stat_object();
    str += "Hp drained: " + hp_drained + "\n";
    str += "Mana drained: " + mana_drained + "\n";

    return str;
}
