#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/kalaman/local.h"

#include <wa_types.h>

inherit AM_FILE

#define PLAYER_I_CLIMB_TOWER "_player_i_climb_tower"

void
create_krynn_monster()
{

    if(!IS_CLONE)
	return;

    set_name("wanderfoot");
    set_title("Treeclimber, Wandering Handler");
    set_race_name("kender");
    set_adj("curious");
    set_short("curious kender");
    set_long("Before you stands a curious kender, one of a race " +
      "of small child-like creatures looked upon by many with " +
      "as much horror as they would a rampaging goblin warrior. " +
      "This kender's innocent looks are marred by a frown, as he " +
      "seems to be thinking hard about something.\n");

    set_stats(({45, 45, 45, 45, 45}));
    set_hp(query_max_hp());

    set_alignment(0);
    set_knight_prestige(-3);

    add_ask(({"quest","task","help"}),
      VBFC_ME("quest_hint"));
    add_ask("hoopak",
      VBFC_ME("hoopak_hint"));
    set_act_time(0);
    add_act("think");
    add_act("say Where did I leave my hoopak?");
    add_act("say I'll bet Uncle Trapspringer never got " +
      "chased by seagulls before!");
    add_act("giggle");
    add_act("emote flips back his topknot absentmindedly.");
    add_act("say Climbing towers is fun, but tiring.");


    trig_new("%w 'introduces' %s","react_to_intro");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    seteuid(getuid());
}


void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

string
quest_hint()
{
    if(TP->test_bit("ansalon", 0, 13))
    {
	command("say Thanks, but I don't need any help today!");

	return "";
    }

    command("think");
    command("say Actually, I don't have any quest for you, but " +
      "if you really want to do something, could you " +
      "help me find my hoopak?");
    command("say I left it somewhere, and I can't find it " +
      "now... and as they say, every road needs a hoopak.");
    command("grin merril");

    return "";
}


string
hoopak_hint()
{
    command("say If I knew where it was, " +
      "I wouldn't be asking for help!");
    command("sigh");

    return "";
}


void
return_give_hoopak(object from)
{

    object spirit;
    string who,
    what;

    who = from->query_real_name();

    if(TP->query_prop(PLAYER_I_CLIMB_TOWER))
    {
	command("say Hey! You found my hoopak! Thanks!");
	command("peer at " + who);
	command("say Looks like you you've been attacked by " +
	  "some rather nasty seagulls.");
	command("giggle");
	command("say Here, you can clean up with this...");
	command("emote rummages through his pouches.");
	spirit = clone_object(KOBJ + "handkerchief");
	what = spirit->query_short();
	spirit->move(TO);
	command("give " + what + " to " + who);

	command("emote smiles happily, and bounces off down the street, " +
	  "forgetting to give out any reward for finding " +
	  "his hoopak!");
	remove_object();
    }
    else
    {
	command("say Hey! My hoopak! Thanks!");
	command("say Well, it was nice meeting you!");
	command("wave");
	command("emote smiles happily, and bounces off down the street, " +
	  "forgetting to give out any reward for finding his hoopak!");
	remove_object();
    }
}

void
give_it_back(object ob, object from)
{
    string what,
    who;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("emote looks at it, but isn't really " +
      "interested in it.");
    command("say Gee. How boring is this.");
    command("drop " + what);
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_ansalon_quest_hoopak_"))
    {
	set_alarm(1.0, 0.0, &return_give_hoopak(from));
	return;
    }
    if(ob->query_no_show())
	return;

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}


