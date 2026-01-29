// file name:        post_guard.c
// creator(s):       Nikklaus, Jul'97
// revision history:
// purpose:          One half of the comedy team of Baertuuk and Simeon. A quest
//                   npc, eventually, but also collects news, takes reports of
//                   non-drow entering and leaving the gate, also takes crime
//                   reports.
// note:
// bug(s):
// to-do:
/*
 * Re-patriated code back to the Kalad domain.
 * 	- Lucius, June 2017
 */
# pragma strict_types
# include <const.h>
# include <macros.h>
# include <ss_types.h>
# include <stdproperties.h>

#include "/d/Kalad/defs.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit CPASS(drow/npc/npc_std);

object simeon;

string
check_adj()
{
    if (sizeof(TO->query_enemy(-1)))
	return "alert";
    else
	return "bored";
}

public void
create_monster()
{
    set_living_name("baertuuk");
    set_name("baertuuk");
    set_adj("bored");
    add_adj("scarred");
    set_gender(G_MALE);
    set_alignment(-650);
    set_knight_prestige(-1);
    set_long("@@check_long@@ A raised line of textured scar "+
      "tissue crosses his throat and curls up along the jawline "+
      "beneath his ear. The fact that it has been tattooed permanently "+
      "red shows an interesting sense of pride (or humor) in his no "+
      "doubt near fatal wound.\n");
    set_act_time(4);
    add_act("emote grumbles with resentment as he watches fellow "+
      "streaakh leave to return to their posts.");
    add_act("emote snarls in frustration at his inactivity, then "+
      "growls menacingly at a bewildered Scout. This appears to improve "+
      "his mood.");
    add_act("emote dourly drums his fingers on the counter, then "+
      "spins a dagger on the smooth surface, watching it twirl.");
    add_act("emote busies himself by copying a sheet of his records "+
      "onto an even cleaner sheet.");
    set_default_answer(QCTNAME(TO) + " nods absently at you, then "+
      "stares across the room, ignoring your question entirely.\n");
    set_speak("I keep records of the passage of foreigners through "+
      "gates, and collect news. I can also take a <report> of the name "+
      "or description of a witnessed murderer.\n"+
      "But if only I could go inflict justice myself, and protect my "+
      "city..!\n");
    add_ask(({"simeon", "Simeon", "half elf", "halfelf",
	"half-elf"}),
      QCTNAME(TO)+" snickers sardonically, but not without some "+
      "fondness:  Only a surface dweller would do that kind of work.\n");
}

public void
reset_monster()
{
    if (!sizeof(TO->query_enemies(-1)))
	set_adj("bored");
}

string
check_long()
{
    if (sizeof(TO->query_enemy(-1)))
	return "An eagerness gleams in the drow's eye; he bristles "+
	"with excitement, hand clenching the hilt of his weapon. A "+
	"broad grin spreads across his face, curling his lips apart "+
	"from his gnashing white teeth.";
    else
	return "An expression of ennui occupies this drow's features, "+
	"somewhat softening the typically drowish sharpness. His eyes "+
	"cast lusterlessly across the counter and room that he obviously "+
	"finds confining.";
}
public void
attack_object(object attacker)
{
    ::attack_object(attacker);
    set_adj("alert");
}

public void
help_friend(object ob)
{
    say(QCTNAME(TO)+"'s eyes flare as he cackles with the thrill "+
      "of unexpected violence!");
    command("emote eagerly draws his scimitar as he hurdles "+
      "the counter!");
    set_adj("alert");
    ::help_friend(ob);
}

#if 0

int
report_outlaw(string str)
{
    int i;
    mapping profiles;
    string *nonmetnames;

    notify_fail(TO->query_The_name(TO)+
      " doesn't appear to notice you.\n");
    if (!strlen(str) || !CAN_SEE(TO, TP))
	return 0;

    str = lower_case(str);
    profiles = TP->query_witnessed();
    if (m_sizeof(profiles))
    {
	if (member_array(str, m_indexes(profiles)) > -1)
	{
	    D_LEGAL->report_outlaw(str, profiles[str]);
	    TP->witness_reported(str);

	    command("say to "+TP->query_name()+" "+
	      capitalize(profiles[str])+", you say?");
	    command("emote nods grimly and rises behind the counter, quickly "+
	      "jotting down a note in a heavy book.");
	    command("emote barks to a Scout and beckons "+(random(2) ? "him" : "her")+
	      " to him.  He quietly growls a few instructions, then sends the Scout "+
	      "out the door.");
	    command("bow appreciat "+TP->query_name());
	    command("emote sits back down and begins scrawling "+
	      "a more detailed report.");
	    return 1;
	}
	nonmetnames = m_values(profiles);
	for (i = sizeof(nonmetnames) - 1; i >=0; i--)
	    if (profiles[nonmetnames[i]] = str)
	    {
		str = profiles[nonmetnames[i]];
		D_LEGAL->report_outlaw(str, profiles[str]);
		TP->witness_reported(str);

		command("say to "+TP->query_name()+" "+
		  capitalize(LANG_ART(str))+", you say?");
		command("emote nods grimly and rises behind the counter, quickly "+
		  "jotting down a note in a heavy book.");
		command("emote barks to a Scout and beckons "+(random(2) ? "him" : "her")+
		  " to him.  He quietly growls a few instructions, then sends the "+
		  "Scout out the door.");
		command("bow appreciat "+TP->query_name());
		command("emote sits back down and begins scrawling "+
		  "a more detailed report.");
		return 1;
	    }
    }
    command("frown thoughful");
    command("emote clears his throat skeptically.");
    command("say to "+TP->query_name()+
      " So did you actually see this..."+capitalize(str)+
      "kill someone?");
    DROW_MASTER_OBJ->demote_rank(TP, 5);
    return 0;
}

void
init_living()
{
    ::init_living();
    add_action(report_outlaw, "report");
}

#endif

public int
team_join(object member)
{
    if (!simeon)
	simeon = member;
    return ::team_join(member);
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (simeon = present("simeon", environment(TO)))
	TO->team_join(simeon);
}

public mixed
query_companion()
{
    return simeon;
}
