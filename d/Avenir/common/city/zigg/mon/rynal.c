// Ry'nal ("rynal.c")
// creator(s):   Zielia 2006 
// last update:
// purpose:      Gives players makeovers by masking their physical beauty
// note:
// bug(s):
// to-do:  Add interesting combat chat/acts. Adjust the damage bits. Fix combat
//		messages so that those who shouldn't see can't.
#pragma strict_types

#include <alignment.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include <stdproperties.h>

#include "zigg.h"

inherit QUEST;
inherit "/std/monster";
inherit "/lib/unique";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/hair_eyes";
inherit "/d/Avenir/inherit/logrotate";

/* Swap between debug / no-debug */
//#define D(x)	tell_room(ENV(TO), (x) +"\n", 0, TO);
#define D(x)

#define IVAL	5.0
#define ACT	(45 + random(15))
#define BLIND_OBJ	(ZIG_OBJ +"r_blind")
#define BLINDED(x)	present("rynal::blind", x)
#define MAKEOVER_SHADOW		(ZIG_OBJ + "makeover_shadow")
#define MAKEOVER_PARALYZE	(ZIG_OBJ + "makeover_paralyze")

#define SOLVER	(ZIG_RL3 + "makeovers")
#define CHECK_QUEST(x) \
    (x)->test_bit("Avenir", ZQ_GROUP, ZQB_RYNAL)

/* adjectives for makeovers neuter/female/male, neutral/good/bad */
private string *adjs = ({ "adorably", "alluringly", "beautifully", 
  "becomingly", "bewitchingly", "boyishly", "breathtakingly", 
  "captivatingly", "dashingly", "delicately", "disturbingly", 
  "dramatically", "eerily", "enchantingly", "enthrallingly", "enticingly", 
  "exceedingly", "exceptionally", "exotically", "extraordinarily", 
  "fascinatingly", "fetchingly", "fiercely", "flawlessly", "frighteningly", 
  "gallantly", "glamourously", "grotesquely", "hideously", "masculinely", 
  "mysteriously", "pleasantly", "radiantly", "rakishly", "ravishingly",
  "really", "repulsively", "resplendently", "roguishly", "ruggedly", 
  "salaciously", "savagely", "seductively", "sensuously", "startlingly",
  "strikingly", "stunningly", "sweetly", "unspeakably", "very", "wildly",
  "torridly", "tantalizingly", "painfully", "unusually", "mezmerizingly",
  "hypnotically", "ferociously", "elegantly", "uniquely", "absolutely",
  "positively",
});

/* beauty types for makeovers neuter/female/male, neutral/beauty/ugly */

private string *types = ({ "adorable", "alluring", "attractive", 
  "beautiful", "becoming", "bewitching", "boyish", "breathtaking", 
  "captivating", "coarse", "cute", "dapper", "dashing", "delicate", 
  "enchanting", "enthralling", "enticing", "exotic", "fetching", "fierce", 
  "fine", "flawless", "foxy", "gallant", "ghastly", "glamorous", 
  "good-looking", "gorgeous", "grotesque", "handsome", "hideous", 
  "horrific", "hunky", "lovely", "masculine", "mysterious", "nauseating", 
  "nice", "nubile", "plain", "pleasant", "pretty", "radiant", "rakish", 
  "ravishing", "refined", "repulsive", "resplendent", "roguish", "rugged", 
  "salacious", "savage", "seductive", "sensuous", "sexy", "statuesque", 
  "striking", "stunning", "sweet", "tantalizing", "torrid", "ugly", 
  "unpleasant", "wild",  "winsome",
});

private string where = one_of_list(({
    "forehead", "cheeks", "nose", "lips", "face"
}));
private static object para;
private static string adj, beauty;
private static mapping m_idle = ([]), m_victors = ([]), m_grow = ([]);
private static int am_busy, alarm, count, copper, t_alarm, aseq, trans;

/*
 * Responses
 */
public string
ask_seq(string *ask, int count = 0, object tp = TP)
{
    set_this_player(tp);  
  
    if (count == 0 && am_busy)
    {
        command("emote is too busy to answer right now.");
        return "";
    }
        
    am_busy = 0;

    if (ENV(TO) != ENV(tp))
        return "";
    	
    command(ask[count]);
    
    if (++count != sizeof(ask))
	am_busy = set_alarm(2.5, 0.0, &ask_seq(ask, count, tp));
    
    return "";
}

public string
default_answer(void)
{
    if (am_busy)
    {
	command("emote appears too busy to answer.");
	return "";
    }

#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       CAP(query_name()) +" about: "+ query_question() +".\n");
#endif

    switch(random(5))
    {
    case 0:
	command("say to "+ OB_NAME(TP) +" That is no concern of mine.");
	break;
    case 1:
	command("emote looks at you blankly.");
	break;
    case 2:
	command("say to "+ OB_NAME(TP) +" I have no knowledge of that.");
	break;
    case 3:
	command("emote studies his nails, looking bored.");
    default:
	command("emote sighs dramatically, appearing pestered.");
	break;
    }
    return "";
}

private string
ask_quest(void)
{
    if (am_busy)
	return "emote appears too busy to answer.";

    /* Can only solve this once a reboot. */
    if (SOLVER->query_solved(TP, ZQN_RYNAL))
    {
	return "say You've helped me too many times already, "+
	    "try again another day.";
    }

    if (TP->query_prop(RYNAL_I_QUEST))
	return "say I thought you were already working on one?";

    /* Put here to allow for repeatability (get diadem). */
    TP->add_prop(RYNAL_I_QUEST, 1);

    if (CHECK_QUEST(TP))
    {
	return "say I misplaced Lyrelle's diadem again. You may find it if "+
	"you'd like though you might not find the effort very rewarding.";
    }

    ask_seq(({"emote looks thoughtful.", "say to "+ OB_NAME(TP) +" "+
    	"There may be something...", "say I recently paid a tiny fortune "+
    	"to have a special piece of jewelry made for Lyrelle.", "say I "+
    	"think it will convince her that I'm serious in my courting.", 
    	"say but somehow, I lost it earlier.", 
    	"say If you really wish to help me, go and find it for me."}));

    return "";    	
}

private string
ask_gift(void)
{
    if (am_busy)
	return "emote appears too busy to answer.";

    if (!TP->query_prop(RYNAL_I_QUEST))
    {
	ask_seq(({"say I accept neither gifts nor gratuities."}));
	return "";
    }
    
    ask_seq(({"say to "+ OB_NAME(TP) +" Don't mention it to Lyrelle, "+
        "of course...", "say It is a beautiful diadem made of finely "+
    	"wrought silver.", "say I've never seen one so nice. I hope "+
    	"you can find it."}));

    return "";    	
}

private string
ask_steps(void)
{
    if (am_busy)
	return "emote appears too busy to answer.";

    if (!TP->query_prop(RYNAL_I_QUEST))
    {
	ask_seq(({"say I have no idea what you mean."}));
        return "";	
    }	

    ask_seq(({"say to "+ OB_NAME(TP) +" I don't have time to retrace "+
        "my steps.", "say I've been all over the Ziggurat today."}));
    return "";        
}

private string
ask_tleth(void)
{
    if (am_busy)
	return "emote appears too busy to answer.";

    if (!TP->query_prop(RYNAL_I_QUEST))
    {
	ask_seq(({"say I have no idea what you mean."}));
        return "";	
    }	

    ask_seq(({"say to "+ OB_NAME(TP) +" A t'leth? You know-- it's one of "+
        "those little furry rodent-like creatures with the twitchy "+
        "little noses and beady little eyes.", "say They're a little "+
        "creepy if you ask me, but most people find them adorable.", "say "+
        "Which I suppose is why t'leth is a term of endearment."}));
    return "";        
}

private string
ask_lost(void)
{
    if (am_busy)
	return "emote appears too busy to answer.";

    if (!TP->query_prop(RYNAL_I_QUEST))
    {
	ask_seq(({"say You're in the northwest part of the Galleria. I don't "+
	"see how you could be lost. Most people consider me a landmark."}));
        return "";	
    }
    
    ask_seq(({"say to "+ OB_NAME(TP) +" I bought Lyrelle a splendid "+
        "diadem as a courtship gift.", "frown", 
        "say Unfortunately, my little t'leth has never been "+
        "very trusting and has a habit of looking through my things.", 
    	"say I took the gift to Cahor's altar and beseeched her to veil "+
    	"it from sight so I'd be able to surprise Lyrelle when I am ready.", 
    	"say Mistress Cahor has always favored me with her blessings.", 
    	"say She hid the gift so that none but her favored could see it.", 
    	"sigh", "say The problem is that I must have dropped it somewhere "+
    	"after that.", "say I've looked all over the shop and cannot find "+
    	"it, and I don't have time to retrace my steps.",}));

    return "";
}

private string
ask_beauty(void)
{
    if (am_busy)
	return "emote appears too busy to answer.";

    return "say to "+ OB_NAME(TP) +" Through Cahor's blessings I am "+
	"able to transform physical beauty in many ways. If you'd like "+
	"me to give you a makeover, simply 'order' one.";
}

private string
ask_cahor(void)
{
    if (am_busy)
	return "emote appears too busy to answer.";

    return "say to "+ OB_NAME(TP) +" They call Cahor the Mistress of "+
      "Deception. By Her will truths are veiled and lies unmasked.";
}

static void
add_clothing(void)
{
    object shirt = clone_object(BAZAAR +"Obj/worn/menshirts");
    shirt->move(TO, 1);
    shirt->set_style("shirts");
    shirt->set_substyle("poet blouse");
    shirt->set_type("silk");
    shirt->set_colour("white");
    shirt->set_desc("luxurious");
    shirt->create_tailored();

    object shoes = clone_object(COM +"village/obj/custom_shoes");
    shoes->move(TO, 1);
    shoes->set_fabric("suede");;
    shoes->set_style("moccasins");
    shoes->set_colour("white");
    shoes->set_desc("clean");
    shoes->create_tailored();

    object codpiece = clone_object(ZIG_OBJ +"rynal_codpiece");
    codpiece->move(TO, 1);

    object amulet = clone_unique(ZIG_OBJ +"camulet");
    if (amulet)  amulet->move(TO, 1);

    command("wear all");
}

public void
create_monster(void)
{
    setuid();
    seteuid(getuid());

    /* Name, rank and serial number */
    set_living_name("rynal");
    set_name(({"ry'nal", "rynal", "sybarite"}));
    set_race_name("elf");
    set_adj(({"tall", "impressive"}));
    set_title("the Master Cosmotologist");
    set_long("@@my_long");

    add_clothing();

    /* Gender, outlook and buffness */
    set_gender(G_MALE);
    set_alignment(ALIGN_TRUSTWORTHY);
    set_stats(({ 95, 115, 95, 155, 105, 65 }), 10);

    /* Properties */
    MAKE_SYBARITE;    
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_FEAR, 1);    
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

    /* Skills */
    set_skill(SS_DEFENCE,    100);
    set_skill(SS_UNARM_COMBAT,    100);
    set_skill(SS_TRADING,    60);
    set_skill(SS_APPR_OBJ,   70);
    set_skill(SS_APPR_VAL,   70);
    set_skill(SS_LANGUAGE,   80);
    set_skill(SS_AWARENESS,  80);
    set_skill(SS_LANGUAGE,80);

    set_skill(SS_ALCHEMY,      100);
    set_skill(SS_HERBALISM,    100);
    set_skill(SS_SPELLCRAFT,   100);

    set_skill(SS_FORM_DIVINATION ,   100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_FORM_ILLUSION,      100);

    set_exp_factor(150);
    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10, 10);

    /* Questions and answers */
    set_dont_answer_unseen(1);
    set_default_answer("@@default_answer@@");

    add_ask(({"makeover", "beauty", "appearance", "order", "blessings",
    	"blessing"}), ask_beauty, 1);
    add_ask(({ "lyrelle" }), &ask_seq(({
      "say Lyrelle is a decent apprentice, but she needs to learn "+
      "that Cahor's blessings are more appropriate for this craft.",
      "say Still her...", "emote seems to searching for the right word.", 
      "say talents can be... quite enjoyable.", "say And her family may "+
      "be ranked soon: a good opportunity for someone who knows how to "+
      "take advantage of it."})), 0);
    add_ask(({ "cahor" }), ask_cahor, 1);
    add_ask(({ "help", "quest", "task", "job" }), ask_quest, 1);
    add_ask(({ "gift", "present", "diadem", "gifts" }), ask_gift, 1);
    add_ask(({ "steps", "retrace",}), ask_steps, 1);
    add_ask(({ "t'leth", "tleth",}), ask_tleth, 1);       
    add_ask(({ "lost",}), ask_lost, 1);

    set_act_time(ACT);
    add_act("@@do_act");

    set_cchat_time(15);
    add_cchat("I have no fear of Mascarvin, but you should.");

    set_mm_in("appears in a swirl of white mist.");
    set_mm_out("disappears in a swirl of white mist.");

    /* Restore variables */
    m_idle  = ([]);

    catch( m_victors = restore_map( MASTER ) );

    /* Needed for quests. */
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

/* 
 * He is a troloby using illusionary magic to disguise himself. he looks
 * different if you can see through the magic or when he transforms for
 * combat.
 */
public string
my_long(void)
{
    if (trans)
    {
	return
	"He is renowned for his gifts in altering appearance.\n"+
	"He is hulking with bulging muscles beneath stretched-looking skin.\n"+
	"He has puffy, swollen, red lips.\n"+
	"His hair is a straw-colored, tufted mane.\n"+
	"His eyes are huge, round and luminous amber.\n"+
	"His skin is pale, almost translucent and oddly shiny.\n"+
	"He is very tall and of normal width for a troloby.\n"+
	"He looks fascinatingly grotesque.\n";
    }

    return
    "He is renowned for his gifts in altering appearance.\n"+
    "He possesses a kind of masculine beauty with finely "+
    "sculpted features and full, sensuous lips.\n"+
    "His hair is the color of honey in shadow and cascades "+
    "down his back in thick waves.\n"+
    "His eyes are the rich brown color of kahve beans.\n"+
    "His skin is flawless alabaster.\n"+
    "He is very tall and of normal width for an elf.\n"+
    "He looks breathtakingly handsome.\n";
}

public string
query_long(void)
{
    string res;

    if (!notmet_me(TP))
    {
	res = TO->query_name() + " is " +
	LANG_ADDART(TO->query_nonmet_name()) +
	", presenting " + TO->query_objective() + "self as:\n" +
	query_presentation() + ".\n";
    }
    else if (!(TO->short(TP)))
    {
	return "";
    }
    else
    {
	res = CAP(TO->query_pronoun()) + " is " +
	LANG_ADDART(TO->short(TP)) +".\n";
    }

    if (obj_long)
	res += check_call(obj_long);

    return res;
}

public string 
query_exp_title(void)	
{ 
    if (trans)
	return "";
    else
	return "sybarite"; 
}


/*
 * His voice changes too.
 */
public string 
race_sound(void)
{
    if (trans)
	return "rasps";
    else
	return "mellifluously intones";
}

/*
 * Stuff for him to do while standing about.
 */
public string
do_act(void)
{
    int num = random(6);

    /* lets not do other stuff while someone is ordering. */    
    if (am_busy || TO->query_attack())
	return "";

    switch(num)
    {
    case 0:
	command("emote whispers a quiet prayer.");
	break;
    case 1:
	command("emote smooths his fastidious white clothing.");
	break;
    case 2:
	command("say If you'd like me to give you a makeover, "+
	    "simply 'order' one.");
	break;
    case 3:
	command("say Cahor has blessed me in so many ways.");
	break;
    case 4:
	command("say No one in all the Cavern can create beauty as I can.");
	break;
    case 5:
	command("smile haughtily");
	break;
    }

    return "";
}

/* React to emotes. */
public void
emote_hook(string emote, object actor, string adverb, object *oblist,
  int attr, int target)
{
    string oname;

    if (!target)
	return;

    oname = OB_NAME(actor);

    if (IS_INFIDEL(actor))
    {
	command("glare "+ oname);
	return;
    }

    if ((attr & ACTION_OFFENSIVE) || (attr & ACTION_THREATENING) ||
	(attr & ACTION_INTIMATE) || (attr & ACTION_INGRATIATORY))
    {
	actor->catch_tell(TO->query_The_name(actor) +" looks disdainfully "+
	  "down his nose at you.\n");
	say(QCTNAME(TO) +" looks disdainfully down his nose at "+
	  QTNAME(actor) +".\n");
    }
    else switch(random(3))
    {
    case 0:
	command("smirk arrogant");
	break;
    case 1:
	command("smile amuse");
	break;
    default:
	/* No response. */
	break;
    }
}

/* React to introductions. */
static void
return_intro(object who, string oname)
{
    if (IS_INFIDEL(who))
	return;

    command("emote stands to his full height, radiating arrogance.");
    command("say to "+ oname +" Who you are is of little import "+
      "to me, and I'm sure I need no introduction.");
}

/*
 * Ordering
 */

/* Take too long/lose link. */
private void
timeout(mixed arg)
{
    if (intp(arg))
    {
	remove_alarm(t_alarm);
	am_busy = t_alarm = 0;
	return;
    }

    if (strlen(arg))
	m_idle[arg] = 1;

    count = am_busy = alarm = t_alarm = 0;

    if (objectp(arg = present(arg, environment())))
    {
	command("emote rolls his eyes.");
	command("say to "+ OB_NAME(arg) +" Let me know when you are ready.");
    }

    command("say I'm ready to help another customer.");
}

/* Tell people things while ordering. */
private void
tell_me(string what)
{
    tell_object(TP, this_object()->query_The_name(TP) +
      " tells you: "+ what +"\n");

    switch(random(3))
    {
    case 0:
	say(QCTNAME(this_object()) +" speaks privately with "+
	  QTNAME(TP) +".\n");
	break;
    case 1:
	say(QCTNAME(TP) +" speaks privately with "+
	  QTNAME(this_object()) +".\n");
	break;
    default:
	/* do nothing*/
	break;
    }
}

/* Determine cost. */
private int
query_cost(void)
{
    return (copper = (12 + random(6)) * MONEY_VALUES[MONEY_GC_INDEX]);
}

/* Charge the player. */
private int
charge_me(string rname)
{
    if (!MONEY_ADD(TP, -copper))
	return 0;
    else
	return 1;
}

/* Apply the makeover */
private void
do_makeover(int max)
{
    string rname = TP->query_real_name();

    if (count >= max)
    {
	remove_alarm(alarm);
	count = alarm = 0;

	seq_restart();

	if (strlen(TP->query_unique_look()))
	    TP->remove_unique_looks();

	object shadow = clone_object(MAKEOVER_SHADOW);

	/* Must set this immediately. */
	shadow->set_unique_look(adj + beauty);

	if (!objectp(shadow) || !shadow->shadow_me(TP))
	{
	    shadow->remove_unique_looks(0);

	    write("There seems to be a problem with your makeover, "+
	      "make a bug report.\n");
	    timeout(1);
	    return;
	}

	command("emote smiles with smug satisfaction.");
	command("say Perfection again.");
	write(TO->query_The_name(TP) +" helps you off the stool.\n");
	say(QCTNAME(TO) +" helps "+ QTNAME(TP) +" back to the ground.\n");
	command("say to "+ OB_NAME(TP) +" That should last you a few days, "+
	  "though if you change your mind, Lyrelle has some soaps that "+
	  "can restore your old look.");

	timeout(1);
	ENV()->set_no_attack(0);
	return;
    }

    switch(count++)
    {
    case 0:
	para = clone_object(MAKEOVER_PARALYZE);

	max   = 9 + random(6);
	alarm = set_alarm(IVAL, IVAL, &do_makeover(max));

	command("say It will take me about "+ ftoi(itof(max) * IVAL) +
	    " seconds to change your look.");

	para->set_remove_time(max * ftoi(IVAL));
	para->move(TP, 1);
	break;

    case 1:
	write(TO->query_The_name(TP) +" guides you to what appears "+
	    "to be a stool, hidden in the mist, and helps you sit down.\n");
	say(QCTNAME(TO) +" guides "+ QTNAME(TP) +" further into the mist "+
	  "where to your surpise, "+ QTNAME(TP) +" takes a seat on a "+
	  "pillar of air. Tendrils of mist curl beneath "+ HIM(TP) +
	  " seeming to support "+ HIM(TP) +".\n");
	break;
    case 2:
	command("emote produces a small clay pot full of some kind of "+
	    "liquid and a clean linen cloth from out of the fog.");
	break;
    case 3:
	write(TO->query_The_name(TP) +" dabs a cool, herbal-smelling "+
	    "liquid on your "+ where +" with the linen cloth.\n");
	say(QCTNAME(TO) +" dabs an herbal-smelling liquid on "+
	    QTPNAME(TP) +" "+ where +" with the linen cloth.\n");
	break;
    case 4:
	write("The liquid is refreshing as it seems to seep "+
	    "into your skin.\n");
	break;
    case 5:
	command("emote chants in low, mellifluous tones. You can't quite "+
	  "make out what he says, but you hear the name Cahor repeatedly.");
	break;
    case 6:
	write("Your skin suddenly begins to tingle, an unnatural yet "+
	    "relaxing warmth radiates from your "+ where +" where "+
	    TO->query_the_name(TP) +" dabbed it with the cloth.\n");
	break;
    default:
	switch(random(3))
	{
	case 0:
	    where = one_of_list(({
		"forehead", "cheeks", "nose", "lips", "face"
	    }));
	    write(TO->query_The_name(TP) +" dabs a cool, herbal-smelling "+
	      "liquid on your "+ where +" with the linen cloth.\n");
	    say(QCTNAME(TO) +" dabs an herbal-smelling liquid on "+
	      QTPNAME(TP) +" "+ where +" with the linen cloth.\n");
	    break;
	case 1:
	    command("emote chants in low, mellifluous tones.");
	    break;
	case 2:
	    write("Your skin tingles, growing warmer.\n");
	    break;
	default:
	    command("emote chants in mellifluous tones.");
	    break;
	}
	break;
    }
}

/* Handle ordering information. */
private void
resolve_order(string opt, string *choice, int stage)
{
    string rname = this_player()->query_real_name();

    if (m_idle[rname])
    {
	m_delkey(m_idle, rname);
	return;
    }

    remove_alarm(t_alarm);
    t_alarm = set_alarm(90.0, 0.0, &timeout(rname));

    /* No argument given, give options and prompt. */
    if (!strlen(opt))
    {
	write("\nYou may enter \"l\" to relist or \"q\""+
	   " to cancel ordering.\n");

	write("Your choice? ");
	input_to(&resolve_order(, choice, stage));
	return;
    }

    /* Wants a new listing. */
    if (opt == "l")
    {
	tell_me("You have these choices:\n");

	write(sprintf("%-#75s\n", implode(choice, "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, choice, stage));
	return;
    }

    /* Wants to cancel. */
    if (opt == "q")
    {
	seq_restart();
	timeout(1);

	tell_me("Very well then, perhaps another time.");
	command("smile brief");
	return;
    }

    switch(stage)
    {
    case 0: /* Chose kind. */
	if (!IN_ARRAY(opt, choice))
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, choice, stage));
	    break;
	}

	beauty = opt;
	/* Fallthru */

    case 1: /* Choose second adjective. */
	choice = sort_array(adjs);

	tell_me("Interesting choice. Now that you've chosen what kind of "+
	  "look you'd like, we can decide just what kind of "+
	  beauty +" to make you.");

	tell_me("You may choose from these options or 'none':\n");

	write(sprintf("%-#75s\n", implode(choice, "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, choice, 2));
	break;

    case 2:

	if (!IN_ARRAY(opt, choice) && opt != "none")
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, choice, 2));
	    break;
	}

	if (opt == "none")
	    adj = "";
	else
	    adj = opt +" ";

	/* Fallthru */

    case 3: /* Should have the order info we need */
	tell_me("Very well. That will cost you "+
	  MONEY_TEXT_SPLIT(query_cost()) +".");

	if (!charge_me(rname))
	{
	    command("smirk slight");
	    command("say It seems you cannot afford my services. Perhaps "+
	      "another time.");
	    seq_restart();
	    timeout(1);
	    break;
	}

	timeout(1);
	do_makeover(99);
	ENV()->set_no_attack(1);
	break;
    default:
	write("ERROR ENCOUNTERED, notify a wizard.\n");
	seq_restart();
	timeout(1);
	break;
    }
}

/* Begin the order process. */
public int
f_order(string str)
{
    string *choice;
    string oname = OB_NAME(TP);
    string rname = TP->query_real_name();

    /* Can't order right now. */
    if (am_busy || query_attack())
    {
	write(TO->query_The_name(TP) +
	    " is too busy to take your order.\n");
	return 1;
    }

    if (IS_INFIDEL(TP))
    {
	command("say to "+ oname + " You are not welcome here, Sin'ur. You "+
	  "should leave.");
	return 1;
    }

    /* Need to order what we have. */
    if (str != "makeover")
    {
	command("say to "+ oname +" What is it you'd like to order? A "+
	  "makeover perhaps?");
	command("eyebrow at "+ oname);
	return 1;
    }

    /* Okay, legit order. */

    choice = sort_array(types);
    am_busy = 1;

    tell_me("How would you like to look?");
    tell_me("I have the following choices:\n");

    write(sprintf("%-#75s\n", implode(choice, "\n")));
    resolve_order("", choice, 0);
    return 1;
}

public void
init_living(void)
{
    ::init_living();
    add_action( f_order, "order" );
}

public void
seq_heartbeat(int steps)
{
    if (am_busy)
	return;

    ::seq_heartbeat(steps);
}

#if 1
public void
enter_env(object dest, object old) 
{
    ::enter_env(dest, old);

    if (file_name(dest) != (ZIG_RL3 +"makeovers"))
	TO->move_living("X", ZIG_RL3 +"makeovers", 0, 1);
}
#endif

/*
 * Combat
 */

/* which enemies are in the room with me?*/
public mixed
query_p_enemies(void)
{
    return TO->query_enemy(-1) &
	filter(all_inventory(environment(TO)), living);
}

/* make me handsome again after I'm peaceful awhile.*/
private void
trans_back(void)
{
    object room = environment(TO);

    trans = 0;   

    if (TO->query_attack())
    {
	trans = set_alarm(900.0, 0.0, trans_back); 
	return;
    }

    tell_room(room, QCTNAME(TO) +" produces a bowl from out of the mist and "+
      "begins liberally dousing himself with its contents while praying "+
      "fervently to Cahor.\n", 0, TO);

    set_alarm(2.0, 0.0, &tell_room(room, QCTNAME(TO) +" begins to glow, "+
	"becoming brighter and brighter until it hurts to look at "+
	"him. Just as suddenly he stops, and you notice he now looks "+
	"much more handsome.\n", 0, TO));

    set_race_name("elf");
    set_adj(({"tall", "impressive"}));	
    set_stats(({ 95, 115, 95, 155, 105, 65 }), 10);

    m_grow = ([]);
    refresh_living();	

    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(5, 5);
    set_attackuse(100);
    update_procuse();
}

/* reveal my true nature, make me buff.*/
public void
transform(void)
{
    object room = environment(TO);

    tell_room(room, QCTNAME(TO) +" blurs before your eyes, his features "+
      "dissolving and shifting, becoming as hazy as the mist around him "+
      "before solidifying again into the form of a hulking intimidating "+
      "male troloby.\n", 0, TO);

    set_race_name("troloby");
    set_adj(({"hulking", "intimidating"}));
    set_stats(({ 170, 180, 170, 230, 180, 120 }), 0);
    trans = set_alarm(900.0, 0.0, trans_back);   

    refresh_living();
    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(15, 15);
}

/*
 *  You've killed me before, so now it's going to be harder:
 */
public void
grow(object ob)
{
    string rname = ob->query_real_name();

    /* don't grow again if I already have from this attacker */
    if (m_grow[rname])
	return;

    /* Remember damage already taken before I grow */
    int hps = query_max_hp() - query_hp();
    int mna = query_max_mana() - query_mana();
    int fat = query_max_fatigue() - query_fatigue();

    /* 
     * add 5% of the total stat average of all present enemies weighted by 
     * the number of times each has defeated me before to my stats.
     */
    int g = (5 * m_victors[rname] * ob->query_average_stat()) / (100);

D("growth = "+ g);
    if ((170 + g) < query_stat(SS_STR))
	return;    
    
    /* grow grow grow!*/    
    m_grow[rname] = time();    
    
    command("emote howls in rage!");
    command("say to "+ rname +" You again! You may have defeated me "+ 
      m_victors[rname] + (m_victors[rname] > 1 ? " times" : " time") +
      " before, but you won't defeat me this time!");

    command("emote flexes his hulking muscles. Is it a trick of the "+
      "mist or is he suddenly bigger?!");

    set_stats(({ 170 + g, 180 + g, 170 + g, 230 + g, 180 + g, 120 + g}), 0);  
    refresh_living();

    g = min(50, max(15, g / 2));

    set_all_hitloc_unarmed(g);
    set_all_attack_unarmed(g, g);
    set_attackuse(100 + g);
    update_procuse();

    /* Adjust for damage already taken before I grow */
    heal_hp(-hps);
    add_mana(-mna);
    add_fatigue(-fat);
}

/*
 *  I transform into a huge troloby when attacked, and if you've beat me 
 *  in the past, you'll get a tougher challenge.
 */
public void
attacked_by(object ob)
{
    if (!trans)
	transform();
	
    ::attacked_by(ob);

    if (m_victors[ob->query_real_name()])    
	set_alarm(2.5, 0.0, &grow(ob));
}

/*
 *  Slam attack
 */
public void
attack_1(int count, object victim = TO->query_attack())
{
    object room = environment(TO);
    int success, pen, dam;  
    mixed *hitres;      

    if ((!objectp(victim)) || (room != environment(victim)))
    {
	aseq = 0;    
	return;
    }  

    switch(++count)
    {
    case 1:
	/* Needs line of sight for this one */
	if (!CAN_SEE(TO, victim))
	{
	    aseq = 0;		
	    return;
	} 

	tell_room(room, QCTNAME(TO) +" makes a slight gesture with "+
	  HIS(TO) +" hand.\n", 0, TO);
	break;

    case 2:
	string dir = one_of_list(({"right", "left"}));

	success = TO->resolve_task(TASK_ROUTINE, ({TS_WIS, SS_FORM_ILLUSION, 
	    SS_SPELLCRAFT}), victim, 
	  ({TS_DEX, SS_AWARENESS, SS_FORM_ILLUSION, SS_ACROBAT})); 

D("success = "+ success);
	/* Darn! He caught on to me! */
	if (success <= 0 && victim->can_see_in_room())
	{
	    victim->catch_tell("You dodge to the "+ dir +" just "+
		"in time to avoid being hit by a giant fist made "+
		"out of mist!\n");
	    tell_room(room, QCTNAME(victim) +" darts to the "+ dir +
		" in time to avoid being hit by a rushing clump of "+
		"the eerie mist!\n", victim, TO);
	    aseq = 0;
	    return;
	}

	if (victim->can_see_in_room())
	{
	    victim->catch_tell("Suddenly the swirling mist on your "+
	      dir +" seems to rush toward you, gathering "+
	      "together and solidifying just before it hits your "+
	      "head painfully hard.\n");
	}
	else 
	{
	    victim->catch_tell("Something large and very hard slams into "+
	      "your head from the "+ dir +".\n");
	}

	tell_room(room, "Suddenly the swirling mist on "+ QTPNAME(victim)+
	  " "+ one_of_list(({"right", "left"})) +" seems to rush toward "+
	  HIM(victim) +", gathering together and solidifying just before "+
	  "it slams into "+ HIS(victim) +" head.\n", victim, TO);
	
	pen = 750 + success + (query_average_stat() * random(10));
	pen -= pen * victim->query_magic_res(MAGIC_I_RES_ILLUSION) / 100;
	hitres = victim->hit_me(pen, W_BLUDGEON, TO, -1, A_HEAD);
	dam = hitres[0];
		
D("dam = "+ dam);
	break;
    }

    if (count < 2)
	aseq = set_alarm(1.0, 0.0, &attack_1(count, victim));
    else
	aseq = 0;
}

/* variation of the sybarite stun kick */
void
attack2(int count, object victim = TO->query_attack())
{
    object room = environment(TO);
    int success, pen, dam;
    mixed *hitres;

    if ((!objectp(victim)) || (room != environment(victim)))
    {
	aseq = 0;    
	return;
    }  

    switch(++count)
    {
    case 1:    

	success = TO->resolve_task(TASK_ROUTINE, ({TS_WIS, SS_FORM_ILLUSION, 
	    SS_SPELLCRAFT}), victim, 
	  ({TS_DEX, SS_AWARENESS, SS_FORM_ILLUSION, SS_ACROBAT}));

D("success = "+ success);
	/* Darn! He caught on to me! */
	if (success <= 0 && victim->can_see_in_room())
	{
	    victim->catch_tell("You notice the mist seems to be "+
		"coalescing about your legs. You quickly dart to "+
		"the side before it can ensnare you!\n");
	    tell_room(room, QCTNAME(victim) +" darts to the side in "+
		"time to avoid thick wisps of mist attempting to tangle "+
		"about "+ HIS(victim) +" legs.\n", victim, TO);
	    aseq = 0;    
	    return;
	}

	if (victim->can_see_in_room())
	{
	    victim->catch_tell("Suddenly the tendrils of mist snaking "+
	      "around your legs seem to solidify! They tangle up your "+
	      "step and snap tight, tripping you and throwing you to "+
	      "the ground!\n");
	}
	else 
	{
	    victim->catch_tell("Something tangles around your feet and "+
		"sends you sprawling to the ground!\n");
	}

	tell_room(room, "Suddenly the tendrils of mist "+
	    "snaking around "+ QPNAME(victim) + " legs seem to solidify! "+
	    "They tangle up "+ HIS(victim) +" step and send "+ HIM(TP) +
	    " flailing to the ground!\n", victim, TO);

	break;
    case 2:       
	pen = (success + victim->query_stat(SS_CON)) * (10 + random(5));
	hitres = victim->hit_me(pen, W_BLUDGEON, TO, -1, A_BACK);
	dam = hitres[0];

	if (dam <= 0)
	    dam = 1;

D("dam = "+ dam);

	switch(dam)
	{
	case 0..10:
	    victim->catch_tell("You roll quickly back to your feet in "+
	      "time to meet your opponent's next attack.\n");
	    tell_room(room, QCTNAME(victim)+" rolls quickly back to " + 
	      HIS(victim) +" feet, apparently unharmed.\n", victim, TO);
	    break;
	case 11..24:
	    victim->add_attack_delay(3, 0);	
	    victim->catch_tell("You are only slightly injured in the "+
	      "fall, but you do feel a bit winded.\n");
	    tell_room(room, QCTNAME(victim)+" looks a bit winded as "+ 
	      HE(victim) +" staggers back to "+ HIS(victim) +
	      " feet.\n", victim, TO);
	    break;
	default:
	    victim->add_attack_delay(10, 0);
	    victim->catch_tell("You land hard on your back, knocking "+
		"the wind from your lungs. Unable to breathe, "+
		"you cannot fight!\n");
	    tell_room(room, QCTNAME(victim)+" lands hard on the stone "+
		"floor and gasps futilely for breath as "+ HE(victim) +
		" struggles to "+ HIS(victim) +" knees.\n", victim, TO);
	    break;
	} 
    }

    if (count < 2)
	aseq = set_alarm(1.0, 0.0, &attack2(count, victim));
    else
	aseq = 0;
}

public void
do_die(object killer)
{
    if (query_hp() > 0)
	return;

    if (!killer)
	killer = previous_object();	

    string rname = killer->query_real_name();

    command("say Death is only an illusion.");
    (ZIG_RL3 +"makeovers")->clear_tells();

    if (!m_victors[rname])
	m_victors[rname] = 1;
    else
	m_victors[rname] += 1;

    save_map(m_victors, MASTER);
    ::do_die(killer);
}

public int
special_attack(object victim)
{
    object room = environment(TO);
    object *enemies = query_p_enemies();
    object enemy = one_of_list(enemies);
    
    if (!random(33))
    {		
	tell_room(room,
	    QCPNAME(TO) +" wounds seem to fade away.\n", enemy, TO);

	TO->heal_hp(TO->query_max_hp());
	return 1;
    }

    /* We don't want special attack each round */
    if (random(3))
        return 0;     
    
    if (aseq)
	return 0;

    if (TO->query_mana() < 10)
	return 0;

    TO->add_mana(-10);

    switch(random(3))
    {
    case 0:		D("SLAM ATTACK");
	/* Slam attack */
	aseq = set_alarm(0.0, 0.0, &attack_1(0));
	break;
    case 1:		D("BLINDING ATTACK");
	if (random(3))
	    break;

	/* Blinding - might blind one or all*/
	if (!BLINDED(enemy))
	{
	    enemy->catch_msg(QCTNAME(TO) +" points at you "+
	      "and whispers a word of Power which echoes in your ears like "+
	      "thunder.\n");		
	    tell_room(room, QCTNAME(TO) +" points at "+ QTNAME(enemy) +
	      " and whispers a word of Power which echoes like thunder"+
	      ".\n", enemy, TO);
	    clone_object(BLIND_OBJ)->move(enemy, 1);
	}
	else if (!random(4)) 
	{
	    tell_room(room, QCTNAME(TO) +" whispers a word of Power which "+
	      "echoes like thunder throughout the room.\n", 0, TO);

	    foreach(object who : enemies)
	    {
		if (!BLINDED(who))
		    clone_object(BLIND_OBJ)->move(who, 1);
	    }
	}
	break;
    case 2:		D("TRIP ATTACK");
	/* Tripping */
	aseq = set_alarm(0.0, 0.0, &attack2(0, victim));
	break;
    }
    return 1;
}

public int
query_disallow_mercy(void)
{
    return 1;
}

/* Toss stuff. */
private void
toss_it(object what, int quiet)
{
    set_alarm(1.0, 0.0, &(what)->remove_object());

    if (!quiet)
    {
	command("sneer disdain");
	command("emote tosses away "+ LANG_THESHORT(what) +".");
    }
}

private void
extra_reward(object who)
{
    object coin;

    if (ENV(who) != ENV(TO))
	return;

    command("say A token for your efforts.");

    coin = clone_object(COM + "obj/syb_coin");
    coin->move(TO);

    if (!command("give "+ OB_NAME(coin) +" to "+ OB_NAME(who)))
	command("put "+ OB_NAME(coin));
}

/* Check for wanted items. */
private int
wanted_item(object ob, object from)
{
    string who = from->query_cap_name();

    if (!ob->id("zigg::diadem"))
	return 0;

    if (CHECK_QUEST(from))
    {
	set_alarm(1.0, 0.0, &command("say I cannot afford to "+
		"reward you again, but thank you nontheless."));
    }
    else
    {
	set_alarm(0.0, 0.0, &reward_quest(
		ZQN_RYNAL, from, ZQ_GROUP,
		ZQB_RYNAL, ZQE_RYNAL, 0, 0));
	set_alarm(1.0, 0.0, &command("say Ahh, you've found the diadem!"));
	set_alarm(1.5, 0.0, &command("say Lyrelle shall soon "+
		"be swooning to the tune of courtship."));
	set_alarm(2.0, 0.0, &extra_reward(from));
    }

    return 1;
}

/* Check for wanted items. */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!query_interactive(from))
	return;

    if (!wanted_item(ob, from))
	set_alarm(1.0, 0.0, &toss_it(ob, 0));
    else
	set_alarm(1.0, 0.0, &toss_it(ob, 1));
}
