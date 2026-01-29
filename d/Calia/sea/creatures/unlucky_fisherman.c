/*  file:  /d/Calia/sea/creatures/unlucky_fisherman.c
 *  coder:  Tigerlily
 *  date:  2002-09-02
 *
 * This is the guy who gives the lucky lure quest
 * He lives on the Calian beach and spends his life
 * in a futile quest to catch a fish that gets away.
 *
 *    (for further info see /d/Calia/private/QUESTS/lucky_lure_quest.doc)
 */
inherit "/std/monster";
inherit "/d/Genesis/lib/intro";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <composite.h>
#include <formulas.h>
#include <cmdparse.h>
#include "defs.h"
#include SEA_QUESTS

// questions that the fisherman will respond to

#define HELP ({"help", "task", "quest"})
#define LUCK ({"luck", "about luck"})
#define LURE ({"lucky lure", "lure", "about lure"})
#define FISH ({"fish", "about fish"})
#define WIFE ({"wife", "about wife", "bump"})
#define POLE ({"fishing pole", "about fishing pole",\
"pole", "about pole"})

// functions
string help_me();
string lucky_msg();
string give_quest(object tp);
string fish_story(object tp);
string lure_desc();
string fish_response();
string wife_response();
string pole_response();
string dumb_looks();
int reset_fisherman();
int reset_busy_flag();
int reward_giver(object giver);

int busy_yacking = 0;
int busy_fishing = 0;

void equip_me();
string rub_head();

void
create_monster()
{
    set_name("ydd");
    add_name("fisherman");
    set_adj(({"unlucky", "old"}));
    add_name("man");
    set_race_name("human");
    set_long("The old man before you has clearly"+
      " spent much time in the outdoors. He has tanned,"+
      " wrinkled skin and his eyes are in a permanent squint from"+
      " staring at the sea for long hours. His gnarled calloused hands"+
      " tell you that he has done hard labour his whole life, and the"+
      " aroma tells you that he is a fisherman.\n");

    set_act_time(10);
    add_act("emote peers unhappily at his fishing pole.");
    add_act("scratch");
    add_act("scratch");
    add_act("spit");
    add_act("grumble");
    add_act("emote makes the sign against the evil eye.");
    add_act("emote shields his eyes with one hand"+
      " looking out over the waves.");
    set_chat_time(10);

    add_chat("@@rub_head");
    add_chat("Don't try to teach your grandpa"+
      " how to chew cheese!");


    set_stats(({20,25,20,25,20,25}));
    set_skill(SS_DEFENCE, 15); 
    set_skill(SS_PARRY, 15); 
    set_skill(SS_UNARM_COMBAT, 15); 

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 75000);

    add_ask(HELP, &help_me(), 1);
    add_ask(LUCK, &lucky_msg(), 1);
    add_ask(LURE, &lure_desc(), 1);
    add_ask(FISH, &fish_response(), 1);
    add_ask(WIFE, &wife_response(), 1);
    add_ask(POLE, &pole_response(), 1);


    set_default_answer("@@dumb_looks");
    equip_me();
}
/*******************************************************************
 * Function name: help_me
 * Description  : This function is a general response to the add_ask
 *                for help or for task, etc. (see set above)
 * Arguments    : none
 * Returns      : empty string
 */
string
help_me()
{
    object tp = this_player();

    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    // check if player has already done quest
    // if so, give him message that he has
    // already helped before and it didn't
    // work last time ;)
    if (tp->test_bit(LUCKYQ_DOMAIN, LUCKYQ_GROUP, LUCKYQ_BIT))
    {
	command("say You have helped me once before!");
	return "";
    }

    if (tp->query_prop(LIVE_I_LUCKY_LURE_QUEST))
    {
	command("say Well I think you already know how"+
	  " you can help me.");
	command("say Now hop to it! I haven't got all day!");
	return "";
    }
    command("peer " + OB_NAME(tp));
    command("whisper "+ OB_NAME(tp) + " I need to get"+
      " my luck back!");
    tp->add_prop(LIVE_I_LUCKY_LURE_QUEST,1);
    return "";
}
/*******************************************************************
 * Function name: lucky_msg
 * Description  : This function is a response to add_ask
 * Arguments    : none
 * Returns      : empty string
 */

string
lucky_msg()
{
    object tp = this_player();

    if (busy_yacking)
    {
	command("say Hold on, youngster, let me finish"+
	  " my thought!");
	command("emote smacks his gums together and"+
	  " thinks real hard.");
	return "";
    }

    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    command("whisper " + OB_NAME(tp) + " One day I found"+
      " the biggest fish you ever saw.");
    command("frown");
    command("whisper " + OB_NAME(tp) + " I had him on the"+
      " hook and was starting to pull him in.");
    busy_yacking = 1;
    set_alarm(5.0, 0.0, &fish_story(tp));
    return "";
}
/*******************************************************************
 * Function name: fish_story
 * Description  : This function is part of response to add_ask
 * Arguments    : none
 * Returns      : empty string
 */

string
fish_story(object tp)
{
    if (!objectp(present(tp, environment(this_object()))))
    {
	command("say Now where did that youngster get off to?");
	command("scratch");
	busy_yacking = 0;
	return "";
    }

    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    command("whisper " + OB_NAME(tp) + " that fish was so large"+
      " that he broke the line!");
    command("whisper " + OB_NAME(tp) + " He bit off the hook"+
      " and took my lucky lure with him.");
    command("show full pole to " + OB_NAME(tp));
    set_alarm(5.0, 0.0, &give_quest(tp));
    return "";
}
/*******************************************************************
 * Function name: give_quest
 * Description  : This function is a response to add_ask
 *                player is set with prop for LIVE_I_LUCKY_LURE_QUEST
 *                so that we know player was assigned quest
 * Arguments    : none
 * Returns      : empty string
 */

string
give_quest(object tp)
{
    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    // reset yacking response
    busy_yacking = 0;

    if (!objectp(present(tp, environment(this_object()))))
    {
	command("emote looks around confused.");
	command("scratch");
	command("ponder young folks always in a hurry.");
	return "";
    }

    if (tp->test_bit(LUCKYQ_DOMAIN, LUCKYQ_GROUP, LUCKYQ_BIT))
    {
	command("say Hey but you have helped me once before!");
	command("say Some fresh blood might help me though.");
	return "";
    }

    if (tp->query_prop(LIVE_I_LUCKY_LURE_QUEST))
    {
	command("say Well I think you already know how"+
	  " you can help me.");
	command("say Now hop to it! I haven't got all day!");
	return "";
    }

    tp->add_prop(LIVE_I_LUCKY_LURE_QUEST, 1);
    command("whisper " + OB_NAME(tp) + " I'd be real grateful"+
      " if you could find and return my lure somehow.");
    command("emote grins toothlessly.");
    command("whisper " + OB_NAME(tp) + " I can't catch anything"+
      " without it!");
    return "";
}
/*******************************************************************
 * Function name: rub_head
 * Description  : This function is an emote (add_act)
 * Arguments    : none
 * Returns      : empty string
 */

string
rub_head()
{
    command("say I better not come home empty-handed again!");
    command("emote rubs a swollen bump on his head");
    command("say The wife sure has a temper on her.");
    return "";
}
/*******************************************************************
 * Function name: lure_desc
 * Description  : This function is a response to add_ask
 * Arguments    : none
 * Returns      : empty string
 */

string
lure_desc()
{
    object tp = this_player();

    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    if (busy_yacking)
    {
	command("say Just hold on a moment.");
	command("emote seems to lose his train of"+
	  " thought for a moment.");
	return "";
    }
    command("whisper " + OB_NAME(tp) + " A lure is a gizmo"+
      " that you attach to your fishing line. It attracts fish.");
    command("whisper " + OB_NAME(tp) + " This one was special"+
      " on account of I made it myself and put a special spell on it.");
    command("whisper " + OB_NAME(tp) + " It's molded in the form"+
      " of a blue Calian frog--it makes the fish go crazy!");
    command("wink");
    command("whisper " + OB_NAME(tp) + " It's my lucky lure and"+
      " without it I can't catch a darn thing.");
    command("grumble");
    return "";
}
/*******************************************************************
 * Function name: fish_response
 * Description  : This function is a response to add_ask
 * Arguments    : none
 * Returns      : empty string
 */

string
fish_response()
{
    object tp = this_player();

    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    if (busy_yacking)
    {
	command("say Don't interrupt your elders!"+
	  " you young whipper-snapper!");
	command("emote grumbles something about young people"+
	  " today.");
	return "";
    }

    command("whisper " + OB_NAME(tp) + " That darn fish swam away"+
      " to the deeps! I don't know how I'll ever get my lure back.");
    command("sigh");
    return "";
}
/*******************************************************************
 * Function name: wife_response
 * Description  : This function is a response to add_ask
 * Arguments    : none
 * Returns      : empty string
 */

string
wife_response()
{
    if (busy_yacking)
    {
	command("say Don't interrupt your elders!"+
	  " you young whipper-snapper!");
	command("emote grumbles something about young people"+
	  " today.");
	return "";
    }
    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    command("rolleyes");
    command("say My wife has a great temper.");
    command("say She has a fit when I come home"+
      " empty-handed.");
    return "";
}
/*******************************************************************
 * Function name: pole_response
 * Description  : This function is a response to add_ask
 * Arguments    : none
 * Returns      : empty string
 */
string
pole_response()
{
    object tp = this_player();

    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    command("whisper " + OB_NAME(tp) + " Can't fish"+
      " with no lure nor hook on my pole!");
    command("scratch");
    return "";
}
/*******************************************************************
 * Function name: dumb_looks
 * Description  : This function is response to set_default_answer
 *                and contains a little hint for the quest
 * Arguments    : none
 * Returns      : empty string
 */

string
dumb_looks()
{
    string str;
    int num = random(4);

    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	return "";
    }

    switch(num)
    {
    case 0:
	str = QCTNAME(this_object()) + 
	" shrugs and looks out over the waves"+
	" where there is a large bird diving into"+
	" the waters.\n";
	break;

    case 1:
	str = QCTNAME(this_object()) + " gazes sadly at"+
	" his fishing pole, fingering the empty line.\n";
	break;

    case 2:
	str = QCTNAME(this_object()) + " puts his hand to"+
	" his ear as if he didn't hear you correctly.\n";
	break;

    case 3:
	str = QCTNAME(this_object()) + " says: "+
	" Well I don't know if I understand your question.\n";
	break;

    default:
	str = QCTNAME(this_object()) + " looks dumbfounded.\n";

    }
    tell_room(environment(this_object()), str, ({}));
    return "";
}

/****************************************************************
 * Function:     equip_me 
 * Description:  Equip the npc with the items he should start with. 
 */ 
void 
equip_me() 
{ 
    seteuid(getuid());   // Required for npcs to have cloning rights. 

    clone_object(SEA_ARMOURS + "tunic")->move(this_object());
    command("wear tunic"); 
    clone_object(SEA_WEAPONS + "fishing_pole")->move(this_object());
    command("wield pole");
    return; 
} 

/**********************************************************************
 * Function name:   introduce (borrowed from example auleb.c)
 * Description:     This function makes the npc do an introduction to a 
 *                  player that has not been introed to it earlier. The 
 *                  function may be redefined to create variety. 
 * Arguments:       object who - the living that introduced to me 
 * 
 */
public void 
introduce(object who)
{
    // He won't intro to an enemy 
    if (member_array(who, query_enemy(-1)) > -1) 
    { 
	command("spit");
    } 
    else 
    { 
	command("introduce myself to " + OB_NAME(who)); 
	command("bow " + OB_NAME(who)); 
    } 
} 

/*****************************************************************
 *  Function:     react_give 
 *  Description:  React to receiving an object from a living. This 
 *                is called by alarm from "enter_inv" below. If 
 *                player is working on quest and gives fisherman
 *                the cleaned version of the lucky lure, he
 *                will get rewarded
 * 
 *  Arguments:    object gift   -    the given object 
 *                object giver  -    the living who gave it 
 */ 
void 
react_give(object gift, object giver) 
{ 
    string giver_name = OB_NAME(giver);

    if (busy_yacking)
    {
	command("say Don't interrupt! Where's your "+
	  " manners? Were you born in a barn??");
	command("drop " + OB_NAME(gift));
	command("scowl");
	return;
    }

    if (busy_fishing)
    {
	command("say Can't you see I'm busy? Just"+
	  " hold on a minute there, Bub!");
	command("say Anyways I don't need that right now!!");
	command("drop " + OB_NAME(gift));
	return;
    }

    /* 
     * If the gift giver has gone or can't be seen, what should 
     * be done? This monster will get suspicious and drop the 
     * item. 
     */ 
    if (!objectp(giver) || 
      !objectp(present(giver, environment(this_object()))) || 
      !CAN_SEE(this_object(), giver) ||
      !CAN_SEE_IN_ROOM(this_object())) 
    { 
	command("say Where'd this come from?"); 
	command("confused");
	command("drop " + OB_NAME(gift)); 
	return; 
    } 
    // .. else if the giver is an enemy, don't accept it.. 
    else if (member_array(giver, query_enemy(-1)) > -1) 
    { 
	command("shout I don't take gifts from the likes of you!");
	if (query_attack() == giver) 
	{ 
	    command("poke " + OB_NAME(giver) + " eye"); 
	} 
	command("drop " + OB_NAME(gift)); 
	return; 
    } 

    if (gift->id(LUCKY_LURE) && giver->query_prop(LIVE_I_LUCKY_LURE_QUEST))
    {

	// giver is trying to do the quest again?

	if (giver->test_bit(LUCKYQ_DOMAIN, LUCKYQ_GROUP, LUCKYQ_BIT))
	{
	    command("say Hey thanks! But I think you have helped me before, "+
	      "so I can't reward you this time!");
	    gift->remove_object();
	    return;
	}	

	// set busy flag for quest reward actions




	if (!giver->test_bit(LUCKYQ_DOMAIN, LUCKYQ_GROUP, LUCKYQ_BIT))
	{
	    busy_fishing = 1;

	    // reward player and set sequence of actions
	    // in motion

	    set_alarm(4.0, 0.0, &reward_giver(giver));

	    // get rid of lure and call unlucky event

	    gift->remove_object();


	    set_alarm(7.0, 0.0, &command("say This lure has never failed to "+
		"attract the big fish!"));
	    set_alarm(9.0, 0.0, &command("wink knowingly"));
	    set_alarm(10.0, 0.0, &command("emote attaches the lure to his"+
		" fishing line and casts the line into the sea."));
	    set_alarm(15.0, 0.0, &reset_fisherman());
	    return;
	}
    }

    // give it back 
    command("scratch");
    command("say What's this for?"); 
    if (!command("give " + OB_NAME(gift) + " to " + 
	OB_NAME(giver))) 
    { 
	command("drop " + OB_NAME(gift)); 
    } 
    return;
}
/*******************************************************************
 * Function name: reward_giver
 * Description  : If earned, give xp
 * Arguments    : giver--player who gave lure to fisherman
 * Returns      : 1
 */
int
reward_giver(object giver)
{
    string giver_name = giver->query_real_name();


    // give player experience and set the bits
    // write to log
    command("cheer");
    command("thank "+ giver_name);
    giver->set_bit(LUCKYQ_GROUP, LUCKYQ_BIT);
    giver->add_exp(LUCKYQ_EXP);
    giver->catch_msg("You feel more experienced!\n");
    giver->command("save");
    log_file("lucky_lure_quest", giver->query_real_name() +
      " solved lucky lure quest:"+
      " " + ctime(time())+".\n");
    giver->remove_prop(LIVE_I_LUCKY_LURE_QUEST,1);

    return 1;
}

/*******************************************************************
 * Function name: reset_fisherman
 * Description  : Quest ending--boy this guy is unlucky!
 * Arguments    : none
 * Returns      : 1
 */

int
reset_fisherman()
{
    set_alarm(3.0, 0.0, &command("emote jumps up"+
	" and down with glee as suddenly"+
	" an enormous silver-coloured fish leaps out"+
	" of the water and snaps the blue frog"+
	" lure into its mouth."));
    set_alarm(5.0, 0.0, &command("emote struggles to pull "+
	"in the line.\nThe fish jumps and leaps in the water!"));
    set_alarm(9.0, 0.0, &command("emote breaks into a sweat "+
	"as he strains back to pull in the big fish!\n"+
	"The line goes taught!"));
    set_alarm(11.0, 0.0, &command("emote grunts as he"+
	" gives the line a last yank to haul in the fish."));
    set_alarm(13.0, 0.0, &command("emote "+
	"grins triumphantly as he reaches for the fish."));
    set_alarm(15.0, 0.0, &tell_room(environment(),
	"Suddenly the line snaps!\nThe fish makes a"+
	" huge leap and disappears,"+
	" taking the lure along with him as"+
	" he dives deep into the sea.\n"));
    set_alarm(18.0, 0.0, &command("curse"));
    set_alarm(20.0, 0.0, &command("say There he goes again!"+
	" Damn my bad luck!"));
    set_alarm(25.0, 0.0, &command("sigh"));
    set_alarm(30.0, 0.0, &command("say Oh well! I guess I was just"+
	" born unlucky."));
    set_alarm(31.0, 0.0, &reset_busy_flag());
    return 1;
}
/**********************************************************
 * Function   :  reset_busy_flag();
 * Description:  Resets busy flag in fisherman so that he can
 *               give the quest again
 * Arguments  :  none
 * Returns    :  1
 */
int
reset_busy_flag()
{

    // reset flags to 0

    busy_fishing = 0;
    busy_yacking = 0;
    return 1;
}



/* ********************************************************
* The function enter_inv is defined in /std/container.c 
* It is a very useful and widely used. In this case it's 
* used in reacting to something given to this monster 
* by a living. See "sman enter_inv" for general information. 
*/ 
void 
enter_inv(object obj, object from) 
{ 
    // Call the inherited function code 
    ::enter_inv(obj, from); 

    // If it's a gift, set up a reaction one second after.. 
    if (living(from)) 
	set_alarm(1.0, 0.0, &react_give(obj, from)); 
} 
