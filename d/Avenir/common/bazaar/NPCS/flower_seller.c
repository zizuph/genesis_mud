// for the flower_stall  Lilith July 1997
// Lucius, Apr 2018: Some cleanups and added 'say' capturing to
//                   the npc for flower ordering.
// Lilith May 2022: changed to inherit call_for_help
#include "../bazaar.h"

// Call_for_help drags killers to the pillory.
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

inherit "/d/Avenir/inherit/intro";
inherit NPC + "call_for_help";

public int alarm, timer;

void
create_monster()
{
   ::create_monster();

    seteuid(getuid());

    set_name("shabaz");
    set_living_name("shabaz");
    add_name(({"merchant", "woman", "shopkeeper"}));
    set_race_name("gnome");
    set_adj(({"pleasant", "dark-eyed"}));
    set_title("icu Imnal, Florist");
    set_long("This is a small, busy gnome. Her hands are stained "+
       "green from handling flowers all day.\n");

    set_gender(G_FEMALE);
    set_aggressive(0);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop("_live_m_attack_thief", "thief_fun");

    set_stats(({60, 75, 60, 50, 50, 40}));
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_CLUB, 40);
    set_alignment(0);

    set_act_time(25);
    add_act("emote hums happily to herself while she trims a flower stem.");
    add_act("shout Flowers for sale!");
    add_act("smile hope");
    add_act("emote carefully plucks a fading blossom from its stem.");

    add_ask(({"city","forbidden city"}),
         "say The Forbidden City is the island where the Shadow Elves "+
         "live. It is a marvellous place. For those permitted to enter, "+
         "it is a great honour.",1);
    add_ask(({"zuggarat", "zugarat", "ziggarat", "ziggurat", "pleasure palace"}),
         "say It is the Pleasure Palace at the center of the Forbidden City. "+
         "It is where the Hanging Gardens are.", 1);
    add_ask(({"gardens", "hanging gardens"}),
         "say It is my honour to be able to care for the Gardens and sell "+
         "the fruits of my labours.", 1);

    set_default_answer(VBFC_ME("what_me"));

    equip(({(OBJ + "worn/qbracel"),
	    (OBJ + "worn/qbracer"),
	    (OBJ + "worn/blouse"),
	    (OBJ + "worn/trouser") }));
}

string
what_me()
{
   command("smile swee");
   command("say If you want flowers, you can <order flower>"+
         ". Otherwise, you may as well go. I've got work to do.");
   return "";
}

/*
 * Function name: return_hit
 * Description  : When the NPC is groped, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not used.
 */
void
return_hit(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    command("frown "+ OB_NAME(actor));
    command("say I am here to sell flowers, not be abused.");
    command("say If beating women is your pleasure, visit the Ziggurat "+
        "in the Forbidden City...");
    command("say They take all kinds there...even yours.");
    command("spit");
}

/*
 * Function name: return_grope
 * Description  : When the NPC is groped, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_grope(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    command("bite " + OB_NAME(actor));
    command("say Go away, before I call the guards.");
}

/*
 * Function name: return_poke
 * Description  : When the NPC is poked, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_poke(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    command("poke " + OB_NAME(actor));
}

/*
 * Function name: emote_hook
 * Description  : This hook is called whenever an emotion is performed on this
 *                NPC. If it is an emotion that we hook on, call a little
 *                alarm and then call the return function.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 */
void
emote_hook(string emote, object actor, string adverb)
{
    /* See if we want to trigger on the emote. If so, call a little alarm
     * for the reaction function.
     */
    switch(emote)
    {
        case "caress":
        case "grope":
        case "fondle":
        case "lick":
            set_alarm(2.0, 0.0, &return_grope(actor, adverb) );
            return;

        case "poke":
	    set_alarm(2.0, 0.0, &return_poke(actor, adverb) );
	    return;
        case "slap":
        case "kick":
            set_alarm(2.0, 0.0, &return_hit(actor, adverb));
            return;
    }
}

void
thief_fun(object thief, object victim, object ob)
{
    set_alarm(1.0, 0.0, &command("glare ang "+ OB_NAME(thief)));
    set_alarm(2.0, 0.0, &command("say Now what exactly are you "+
	    "trying to steal?"));
    set_alarm(3.0, 0.0, &command("grin"));
}

public void
react_speech(object who, string msg, int do_say)
{
    alarm = 0;

    if (!strlen(msg) || !objectp(who) || !present(who, environment()))
	return;

    if (do_say)
	environment()->do_say(msg);
    else
	command(msg);
}

public void
speech_hook(string verb, object actor, string adverb,
    		object *oblist, string text, int target)
{
    switch(verb)
    {
    case "whisper":
	text = "emote whispers loudly: Why are you whispering?";
	break;
    case "shout":
	text = "say There is no need for shouting!";
	break;
    case "say":
	alarm = set_alarm(0.5, 0.0, &react_speech(actor, text, 1));
	return;
    }

    if (alarm)
	return;

    if (time() < timer)
	return;

    timer = time() + 120;
    alarm = set_alarm(1.5, 0.0, &react_speech(actor, text, 0));
}
