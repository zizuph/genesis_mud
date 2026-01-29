/*
 * THANDUIN.c
 * This is the old man who owns the sanctuary/hut in the middle of the
 * misty forest of Coramar. He is extremely important in just about all quests
 * relating to this area, including the entrance quest to the Druid's guild.
 * Started 2/19/98 - Alaron
 */

#include "../coramar.h"
#include "../dirheader.h"
#include "/d/Emerald/defs.h"
#include <seqaction.h>
#include <ss_types.h>

inherit EMERALD_MONSTER;

void
create_emerald_monster()
{
    set_name("thanduin");

    set_race_name("human");
    set_adj("hearty");
    add_adj("old");

    /* This name has been banished from the administrator's workroom */
    set_living_name("thanduin");


    set_title("the Keeper of the Coramar Forest");

    /* Let's describe Thanduin .. give him some physical features */
    set_long("This middle-aged man has a strong, weathered look about his face. His "+
	     "eyes are underlined with subtle wrinkles and a hardness likely gained "+
	     "through hardship or battle. His piercing green eyes seem to glow with "+
	     "a wisdom beyond his years. His clothing is heavy and sturdy, but far "+
	     "from fancy. Everything about his attire seems designed to weather the "+
             "cold, damp conditions of the forest where he lives. His pleasant, "+
	     "comforting smile betrays a few teeth bordering on the edge of rot, but "+
	     "that doesn't take away from his warm, father-like countenance. He looks "+
	     "as though he would enjoy speaking with you.\n");

    /* Set Thanduin's base stats, STR, CON, DEX, DIS, WIS, INT */
    set_alignment(50);

    set_base_stat(SS_CON, 80);
    set_base_stat(SS_STR, 45);
    set_base_stat(SS_INT, 80);
    set_base_stat(SS_DIS, 40);
    set_base_stat(SS_WIS, 110);
    set_base_stat(SS_DEX, 50);

    heal_hp(99999);

    /* Emerald standard function - will cause Thanduin to clone and wear/wield
     * his boots, cloak, leather chestplate, and hunting knife. Also, it will clone
     * the gloves which are a requirement for the mist wraith quest.
     */
    add_equipment( ({ CORAMAR_ARM + "l_boots",
	              CORAMAR_ARM + "l_gloves",
                      CORAMAR_ARM + "cloak",
	              CORAMAR_ARM + "l_chest",
		      CORAMAR_WEP + "hunting_knife" }) );

    set_speak( ({"Good day to ye! I almost never run into people out here, it is good" +
	         "to hear the sound of another voice.",
		 "It is a good life here. Nobody ever bothers me in these woods.",
		 "They let me stay and keep my hut sheltered, so I earn my board by keepin' the "+
		 "troublemakers out.",
		 "Most 'o the time I don't need to do much. The wraiths livin' in "+
		 "this mist don't take too kindly t'strangers, 'specially ones that be"+
		 " wieldin' their weapons like they be meanin' to do some harm in "+
		 "here.",
		 "I've seen them wraiths do some amazin' feats. I saw one float right "+
		 "through a tree once. Didn't even shake a leaf I tell ya!",
		 "Some say the skin on those wraiths is like ice, and it'll burn "+
	         "yer fingers if ya try t'capture one!",
		 "Well, I certainly appreciate yer neighborliness in talkin' to an "+
		 "old trapper. Good day to ye!"
	       }) );

 
    /*
     * The below commands create a sequence which will make Thanduin appear fairly  
     * lifelike and realistic. He'll go outside, dig through the bushes for some
     * herbs, head out into the forest and check one of his traps, and then come
     * back after a 'long days work', and he'll sit down, take off his boots, take
     * off his cape, his chest plate and his hunting knife, putting them all on the
     * table and hanging up the chest plate and cape. Then he'll take off his gloves 
     * and sit by the fire for a while... The player needs to take the gloves and 
     * run once Thanduin falls asleep. If the player tries while Thanduin is awake,
     * the player is in deep do-do.
     *
     * (this should work) When he goes to sleep, he'll remove the sequence and set
     * an alarm to wake up. When he wakes up, he will re-add the sequence, which 
     * should make him do everything over again.
     */
   
    seq_new("meander_forest", SEQ_F_NONSTOP);
    seq_addfirst("meander_forest", ({"burp", 2, "burp", "@@redo_seq"}));
}

public void
add_introduced(string str)
{
    if (this_player()->query_npc())  return;

    set_alarm(2.0, 0.0, &command("introduce myself to "+str));
}

int
redo_seq()
{
    set_alarm(2.0, 0.0, "redo_seq2");
    return 4;
}

int
redo_seq2()
{
    seq_delete("meander_forest");
    command("emote bends over and adjusts the kettle over the fire.");
    seq_new("meander_forest");
    seq_addfirst("meander_forest", ({"burp", 2, "burp", "@@redo_seq"}));
}



/*
 * THIS IS A COMPLETE REMASK OF PREVIOUS VERSION OF SEQ_HEARTBEAT
 */

/*
 *   Description: The core function that actually runs the commands
 */
public void
seq_heartbeat(int steps)
{
    int il, newstep, stopseq, stopped;
    mixed cmd;
    mixed cmdres;
    mixed *calls;

    set_alarm(rnd() * SEQ_SLOW + SEQ_SLOW / 2.0, 0.0, &seq_heartbeat(1));

/*
 *    stopseq = ((time() -
 *		this_object()->query_last_met_interactive()) > SEQ_STAY_AWAKE);
 */

    stopseq = 0; /* ABSOLUTELY NEVER STOP */ 

    newstep = 0;
    stopped = 0;
    if (!steps)
	steps = 1;

    if (stopseq)
	stopped = 1;
    
    for (il = 0; il < sizeof(seq_names); il++)
    {
	if (seq_cpos[il] < sizeof(seq_commands[il]))
	{
	    if (!stopseq || (seq_flags[il] & SEQ_F_NONSTOP) || !stopped)
		stopped = 0;

	    cmd = seq_commands[il][seq_cpos[il]];
	    seq_cpos[il]++;

	    if (stringp(cmd) || functionp(cmd))
		cmdres = this_object()->check_call(cmd);
	    else if (intp(cmd))
		cmdres = cmd - steps;
	    else
	    {
		newstep = 1;
		continue;
	    }

	    if (stringp(cmdres))
	    {
		command(cmdres);
		newstep = 1;
	    }
	    else if (intp(cmdres) && cmdres > 0)
	    {
		newstep = ((newstep) && (cmdres > newstep) ? newstep : cmdres);
		seq_cpos[il]--;
		seq_commands[il][seq_cpos[il]] = cmdres;
	    }
	    else 
	    {
		newstep = 1;
	    }
	}
	else
	{
	    seq_cpos[il] = 0;
	    seq_commands[il] = ({});
	}
    }

    calls = get_all_alarms();
    if (stopped)
    {
	for (il = 0 ; il < sizeof(calls) ; il++)
	    if (calls[il][1] == "seq_heartbeat")
		remove_alarm(calls[il][0]);
	this_object()->add_notify_meet_interactive("seq_restart");
	if (!newstep)
	{
	    seq_active = 0;
	}
    }
    if (newstep > 1)
    {
	for (il = 0 ; il < sizeof(calls) ; il++)
	    if (calls[il][1] == "seq_heartbeat")
		remove_alarm(calls[il][0]);
	set_alarm(itof(newstep) * (SEQ_SLOW / 2.0 + rnd() * SEQ_SLOW), 0.0,
		  &seq_heartbeat(newstep));
    }
}

