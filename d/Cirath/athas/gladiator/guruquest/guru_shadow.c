/*
 * This is the NPC shadow for the Gladiator Guru quest.
 */
#pragma no_inherit
#pragma strict_types

inherit "/std/shadow";
#include "guruquest.h"

#define RESET 10.0

#define D(x) if (debug) tell_object(debug, "GGQ: " + x + "\n")


static object questor, debug;
static int reset, valid_kill, quest_bit, attack_time;

public void
enable_debug()
{
    if (debug = find_player(geteuid(calling_object())))
	D("Glad Guru Quest Debugging Enabled!!\n");
}

public void
disable_debug()
{
    if (debug)
	D("Debugging Disabled!");
    debug = 0;
}

/*
 * Set which bit we govern/.
 */
public void
set_guru_bit(int bit)
{
    quest_bit = bit;
    D("Bit set to: "+ quest_bit);
}

/*
 * Reset the quest if it's been invalidated.
 */
private void
reset_quest()
{
    reset = questor = valid_kill = 0;
    D("Quest reset");
}

/*
 * Track our atackers.
 */
public void
attacked_by(object ob)
{
    D(sprintf("ATTACKD_BY called: %O", ob));

    if (shadow_who->query_attack())
    {
	D("NPC is under attack already, quick skipped");
	shadow_who->attacked_by(ob);
	return;
    }

    if (!questor && MANAGER->guru_quest(ob->query_real_name()))
    {
	if (shadow_who->query_hp() < shadow_who->query_max_hp())
	{
	    D("NPC is not at max HP, quest not activated");
	}
	else
	{
	    questor = ob;
	    valid_kill = 1;
	    attack_time = time();
	    D("attacked_by: quest activated");
	}
    }
    else if (questor && (questor != ob))
    {
	valid_kill = 0;
	if (!reset)
	    reset = set_alarm(RESET, 0.0, reset_quest);
	D("attacked_by: quest invalidated");
    }
    shadow_who->attacked_by(ob);
}

/*
 * Verify we did the quest as hoped for.
 */
public void
do_die(object killer)
{
    D(sprintf("DO_DIE called: killer: %O", killer));

    // Sanity check
    if (shadow_who->query_hp() > 0)
    {
	D("Npc still has HP, bailing");
	return;
    }

    D(sprintf("do_die: questor: %O", questor));
    D("do_die: valid_kill == "+ valid_kill);

    if ((questor == killer) && valid_kill)
    {
	D("do_die: Kill validated");
        // check to see if the player is doing the glad guru quest
        if (MANAGER->guru_quest(killer->query_real_name()))
        {
	    D("do_die: Quest accomplished");
            killer->catch_tell("You feel a sense of accomplishment as you "+
		"watch " + shadow_who->query_the_name(killer) +
		" die by your hand and your hand alone.\n");
            MANAGER->guru_quest_set(killer->query_real_name(), quest_bit);
        }
    }
    reset = questor = valid_kill = 0;
    shadow_who->do_die(killer);
}

/*
 * Make sure our questor hasn't flee'd and re-entered.
 */
public void
init_living()
{
    D(sprintf("INIT_LIVING called: %O", this_player()));

    if (!questor)
    {
	D("init_living: No questor, bailing");
	shadow_who->init_living();
	return;
    }

    D("time == "+ time());
    D("attack_time == "+ attack_time);
    
    if ((time() != attack_time) &&
	(this_player() == questor) ||
	!present(questor, environment(shadow_who)))
    {
	D("init_living: questor re-entered or not present, reset");
	valid_kill = 0;
	if (!reset)
	    reset = set_alarm(RESET, 0.0, reset_quest);
    }

    shadow_who->init_living();
}

