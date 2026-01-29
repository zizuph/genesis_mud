#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

string
random_extra()
{
    int i;
    i = random(5);
    if (i < 2)
	return "gaelen";
    else if (i < 3)
	return "galann";
    else if (i < 4)
	return "kharn";
    else
	return "nader";
}

void
create_kalad_monster()
{
    string extra;
    extra = random_extra();
    set_name(extra);
    add_name("gatekeeper");
    add_name("cg_gatekeeper");
    set_race_name("human");
    set_adj("patient");
    set_short("gatekeeper");
    set_long("This man has large rippling muscles on his arms and chest, "+
      "probably because he is the person that works the winch that opens up "+
      "the Caravan Gate. He stands here patiently waiting for any passersby "+
      "that may need his services.\n");
    set_stats(({300, 25, 30, 20, 20, 30}));
    set_exp_factor(50);  // To make up for the 300 str.
    set_alignment(600);
    set_skill(SS_AWARENESS, 100);
    set_act_time(6);
    add_act("say Greetings travellers!");
    add_act("smile patiently");
    set_title("the Gatekeeper");
    add_speak("It's been such a long time since I've heard someone laugh.\n");
    set_default_answer("The gatekeeper says: Eh? What was that?\n");
    add_ask(({"services", "service"}), "The gatekeeper says: Won't you "+
      "laugh for me and brighten up my day?\n");
    add_ask(({"doors", "door", "caravan gate", "gate"}), "The gatekeeper "+
      "says: Would you laugh for me and brighten my day?\n");
    set_knight_prestige(-6);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
}

void
react_laugh(object who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
	command("say Its so good to hear you laugh, " + obj->query_nonmet_name() + ".");
	command("emote starts cranking the winch.");
	command("open doors");
    }
}

void
react_frown(object who)
{
    object obj;

    if (obj = present(who, environment()))
    {
	command("say I don't like seeing people unhappy, especially you, " + obj->query_nonmet_name() + ".");
	command("emote starts cranking the winch.");
	command("close doors");
    }
}

void
react_smile(object who)
{
    object obj;

    if (obj = present(who, environment()))
    {
	command("say Its enlightening to see you smile, " + obj->query_met_name() + ".");
	command("smile cheer");
    }
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("shout Attackers at the gate!");
	command("say The gate must be secured!");
	command("open doors");
	command("s");
	command("close doors");
	command("in");
    }
}

void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (emote=="laugh") set_alarm(1.0, 0.0, &react_laugh(actor));
    if (emote=="smile") set_alarm(1.0, 0.0, &react_smile(actor));
    if (emote=="frown") set_alarm(1.0, 0.0, &react_frown(actor));
}
