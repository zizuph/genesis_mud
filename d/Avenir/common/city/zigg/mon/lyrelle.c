// Lyrelle the Apprentice Cosmetician ("lyrelle.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Shopkeeper for makeupshop.c
// note:
// bug(s):
// to-do:

#pragma no_inherit
#pragma no_shadow
#pragma strict_types

#include "zigg.h"

#include <alignment.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit ZIG_NPC;
inherit QUEST;

#define CHECK_QUEST(x) \
    (x)->test_bit("Avenir", ZQ_GROUP, ZQB_GEMDUST)

private static int am_busy;

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
        command("emote is too busy to answer right now.");
        return "";
    }	
	
#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       CAP(query_name()) +" about: "+ query_question() +".\n");
#endif

    switch(random(4))
    {
    case 0:
        command("say to "+ OB_NAME(TP) +" That sounds dull. Maybe we should "+
        "talk about makeup instead.");
        break;
    case 1:
        ask_seq(({"bite", "say to "+ OB_NAME(TP) +" Is that some kind of "+
        "Outlander thing?"}));
        break;
    case 2:
        ask_seq(({"lashlower ", "say to "+ OB_NAME(TP) +" I have no "+
        "knowledge of that."}));
        break;
    default:
        ask_seq(({"pout prettily", "say Questions, questions. Can't I "+
        "make people pretty in peace?"}));
        break;
    }

    return "";
}

private string
ask_help(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" T'cael I can help anyone look "+
    	"better!", "say to "+ OB_NAME(TP) +" That won't be hard at all in "+
    	"your case.", "say Just try some of my cosmetics."}));
    	
    return "";
}

private string
ask_quest(void)
{
    ask_seq(({"fidget .", "say to "+ OB_NAME(TP) +" I am actually "+
        "running dreadfully low on lotions.", "say to "+ OB_NAME(TP) +
        " But I cannot make more until I receive my order of gemdust "+
        "from Imlis in the bazaar.", "say But the delivery is long "+
        "overdue.", "say Would you be a dear and see if my order "+
	"is ready?"})); 
    
    return "";     
}

private string
ask_secret(void)
{
    ask_seq(({"squirm .", "asay conspiratorially to "+ OB_NAME(TP) +
        " Trust me, you don't really want to know."}));
        
    return "";
}

private string
ask_soap(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" I make soaps for the Faithful all "+
        "over Syb'arus. I even supply the temple with my emblem soaps.", 
        "beam proudly"}));
        
    return "";
}

private string
ask_ssoap(void)
{
    ask_seq(({"emote gets an odd gleam in her blue eyes which for just a "+
	"moment appear viciously cunning.", "say to "+ OB_NAME(TP) +
	" Those are only for very special people."}));
	
    return "";
}

private string
ask_rynal(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" Ry'nal is so handsome and talented.", 
        "sigh dreamily", "say to "+ OB_NAME(TP) +" I only hope that with "+
        "my private lessons, I'll have his skill one day.", "say He gives "+
        "wonderful makeovers that last for days. Only scrubbing with my "+
        "soaps will remove them.", "say But who would want to?"}));
        
    return "";
}

private void
zig_npc(void)
{
    setuid();
    seteuid(getuid());

    /* Name, rank and serial number */
    set_name("lyrelle");
    set_race_name("elf");
    set_adj(({"pretty", "long-haired"}));
    set_title("dei Tor-loral the Apprentice Cosmetician");
    set_syb_house("Tor-loral");

    /* Gender, outlook and buffness */
    set_opinion(90);
    set_appearance(99);
    set_gender(G_FEMALE);
    set_size_descs("short", "lean");
    set_alignment(ALIGN_TRUSTWORTHY);
    set_stats(({ 50, 80, 80, 70, 150, 50 }), 25);

    configure_eyes("vacuous", "light blue", 2);
    configure_hair("long", "glossy black", "cascades down her back in soft "+
        "waves");

    /* Properties */
    add_prop(LIVE_I_NON_REMEMBER, 1);

    /* Skills */
    set_skill(SS_ACROBAT,    25);
    set_skill(SS_TRADING,    60);
    set_skill(SS_APPR_OBJ,   70);
    set_skill(SS_APPR_VAL,   70);
    set_skill(SS_LANGUAGE,   80);
    set_skill(SS_AWARENESS,  80);
    set_skill(SS_LOC_SENSE,  40);
    set_skill(SS_LANGUAGE,80);
    set_skill(SS_ALCHEMY,   100);
    set_skill(SS_HERBALISM, 100);
    set_skill(SS_SPELLCRAFT, 80);

    set_skill(SS_ELEMENT_AIR,   60);
    set_skill(SS_ELEMENT_LIFE,  60);
    set_skill(SS_ELEMENT_EARTH, 60);
    set_skill(SS_ELEMENT_WATER, 60);
    set_skill(SS_ELEMENT_DEATH, 60);
    set_skill(SS_FORM_ENCHANTMENT,   70);
    set_skill(SS_FORM_TRANSMUTATION, 70);

    /* Worn Stuff*/

    clone_object(ZIG_OBJ +"lashes.c")->move(TO, 1);
    clone_object(ZIG_OBJ +"brush.c")->move(TO, 1);
    object gloss = clone_object(ZIG_OBJ +"pomade.c");
    gloss->set_tint("clear");
    gloss->move(TO, 1);
    gloss->f_apply("pomade");

    /* Questions and answers */
    set_dont_answer_unseen(1);
    set_default_answer("@@default_answer@@");

    add_ask(({ "cosmetics", "makeup" }), &ask_seq(({
        "say I do business with traders from all parts of Syb'arus and "+
        "even the Outlands to find the best ingredients for my "+
        "cosmetics."})), 0);

    add_ask(({ "pomade", "pomades", "lips", "lip gloss", "lip stick" }),
        &ask_seq(({"say I got the recipe from this darling Outlander named "+
        "Adriel in exchange for some rare herbs.", "say Then I added my "+
        "own ingredients for color and flavor.", "say They make your lips "+
        "so kissable and the dancers love them!"})), 0);

    add_ask(({ "mesdemet" }), &ask_seq(({
        "say It's made from an old recipe, and a secret one.", "say I've "+
        "found nothing else to make eyes look so glamorous."})), 0);

    add_ask(({ "secret", "recipe" }), ask_secret, 1);
    add_ask(({ "help", "beautiful" }), ask_help, 1);
    add_ask(({ "quest", "task", "job" }), ask_quest, 1);
    add_ask(({ "quest", "task", "job" }), ask_quest, 1);
    add_ask(({ "soap", "soaps", }), ask_soap, 1);
    add_ask(({ "special soap", "special soaps", "exploding soap"}), 
    	ask_ssoap, 1);
    add_ask(({ "rynal", "makeover", "makeovers", }), ask_rynal, 1);

    add_ask(({"dust", "gemdust"}), &ask_seq(({
	"say I'll not reveal my process, but suffice to say "+
	"they are a necessary ingredient to my body lotions.",
	"say The process renders it all inert and quite harmless "+
	"so you needn't worry about any side effects."})), 0);
    add_ask(({"Imlis", "imlis"}), &ask_seq(({
	"say Imlis is a dear of a gnome.","say He runs the "+
	"lapidary over at the bazaar.", "say He's also my sole "+
        "supplier of high-grade gemdust."})), 0);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}),
	&ask_seq(({"say 'Tis where the shadow-elves live. You must "+
	"have noticed it on your way to the Ziggurat."})), 0);
    add_ask(({"infidel", "infidels"}), &ask_seq(({
	"say They make the best kindling."})), 0);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
	&ask_seq(({"say I am. Are you?"})), 0);
    add_ask(({"Jazur", "jazur"}), &ask_seq(({
	"say Jazur is the Goddess of the Twelfth Hour, regent of Passion.", 
	"say Grace and Beauty inspire Passion. We honor Jazur when we "+
	"display these things."})), 0);
    add_ask(({"Sisera", "sisera"}), &ask_seq(({
	"say Sisera is the God of the Twelfth Hour, regent of Carnal "+
	"Delights.", "say If the Ziggurat is a temple to any one of the "+
	"Idrys, surly it is his.", "say But many Gods inspire pleasure and "+
	"we feel their presence here."})), 0);
    add_ask(({"Cahor", "cahor"}), &ask_seq(({
	"say I don't disagree that the Mistress of the Seventh Hour "+
	"can make even an old goat look like a fresh lamb.", "say But I hope "+
	"to reveal and adorn existing beauty, not create an illusion. ",
	"say Ry'nal has never understood this."})), 0);
    add_ask(({"union", "shadow union", "shadow warrior"}), &ask_seq(({"say "+
	"They still use my products beneath their veils, trust me."})), 0);
    add_ask(({"dej-minha"}), &ask_seq(({
	"say They are chosen for beauty and skill alike, but a little "+
	"mesdemet wouldn't be amiss."})), 0);
    add_ask(({"hegemon", "Hegemon"}), &ask_seq(({
	"say If he wants to let all manner of people into the Ziggurat, "+
	"'tis his choice and we will obey.", "emote mentions: 'Tisn't like "+
	"Hegemons usually live that long anyway."})), 0);
    add_ask(({"idrys", "Idrys"}), &ask_seq(({
	"say They are true Gods. Our existence is to Serve."})), 0);
    add_ask(({"ziggurat","Ziggurat"}), &ask_seq(({
	"say The Ziggurat is a monument to pleasures of every kind. Here "+
	"you will find objects to please the eye, the nose the tongue. ",
	"emote adds: And if the guards will let you venture lower, a "+
	"few other body parts, mayhap.", "emote winks meaningfully."})), 0);

    set_act_time(40);
    add_act("@@do_act");
    
    set_cact_time(10);
    add_cact("scream");
    add_cact("pout");
    add_cact("panic");

    set_cchat_time(5);
    add_cchat("I'm too pretty to die!");
    add_cchat("Not the face!");
    add_cchat("Curse you! I hope you live a long, ugly life.");

    /* Needed for quests. */
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

public string
do_act(void)
{
    if (am_busy)
	return "";

    switch(random(8))
    {
    case 0:
	command("emote surreptitiously admires her reflection "+
	    "in one of the many mirrors.");
	break;
    case 1:
	command("brush hair");
	break;
    case 2:
	command("lashlower");
	break;
    case 3:
	command("sigh dreamily");
	break;
    case 4:
	command("pchew");
	break;
    case 5:
	command("emote cleans some smudges from a mirror.");
	break;
    case 6:
	command("emote breathes: Perhaps someday I'll be able to "+
	    "make people as beautiful as Ry'nal does.");
	break;
    case 7:
	command("emote straightens the cherry-wood baskets so they "+
	    "display her products to their best advantage.");	
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

    if ((attr & ACTION_OFFENSIVE) || (attr & ACTION_THREATENING))
    {
        switch(random(3))
        {
        case 0:
            command("sneer");
            command("say to "+ oname +" Your manners match your appearance!");
            break;
        case 1:
            command("emote trembles with anger for a moment, but seems to "+
                "contain it as she smiles politely.");
            break;
        case 2:
            command("say to "+ oname +" Such behavior might be acceptable "+
                "in the bazaar, but this is the City!");
            break;
        case 3:
	    command("smile slowly");
            command("say to "+ oname +" Can I interest you in one of my "+
		"very special soaps?");
            break;
        }
    }
    else if ((attr & ACTION_INTIMATE) || (attr & ACTION_INGRATIATORY))
    {
        switch(random(5))
        {
        case 0:
            command("emote rolls her eyes.");
            command("say I get this all the time.");
            break;
        case 1:
            command("frown disdainfully");
            command("say to "+ oname +" Perhaps you should try that with "+
                "the pleasure slaves. I'm not that easy to impress.");
            break;
        case 2:
            command("say to "+ oname +" You'd have to be Ry'nal or Sisera "+
                "for that to work with me.");
            break;
        case 3:
            command("say to "+ oname +" Oh you!");
            command("paddle "+ oname +" with brush");
            break;
        default:
            command("say to "+ oname +" None of that here!");
            command("spank "+ oname +" with brush");
            command("bat");
            break;
        }
    }
    else switch(random(3))
    {
    case 0:
        command("lashtilt thoughtfully at "+ oname);
        break;
    case 1:
        command("smile slightly");
        break;
    default:
        /* No response. */
        break;
    }
}

/*
 * React to introductions.
 */
static void
return_intro(object who, string oname)
{
    if (IS_INFIDEL(who))
        return;

    command("curtsey politely");
    command("introduce me to "+ oname);
    command("say to "+ oname +" Ta'haveth, "+
	who->query_name() +"! How may I help you?");
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
static void
check_meet(object who, string oname)
{
    if (IS_INFIDEL(who))
    {
        ask_seq(({"emote 's vacuous light blue eyes blaze with hatred.", 
            "asay menacing to "+ oname +" Leave here loathsome "+
            "creature. You are ugly to the core and there is no help "+
            "for you here!"}));
        return;
    }

    int i = random(15);

    if (IS_UNION(who))
    {
        if (i < 5)           
            command("say to "+ oname +" Jazur bless you with "+
                "beauty and grace!");
        return;
    }

    if (who->query_prop(DANCER))
    {
        if (i == 1)
            command("say to "+ oname +" Let the Source shine "+
            	"brightly on your beauty, Sister!");
	else if (i == 4)
            command("say to "+ oname +
                " You simply must try the new pomades! They'll make "+
		"your lips so yummy.");
        return;		
    }       

    command("say to "+ oname +" Beauty and Passion to you! "+
        "Welcome to my shop!");
}

/* Toss stuff. */
private void
toss_it(object what, int quiet)
{
    set_alarm(1.0, 0.0, &(what)->remove_object());

    if (!quiet)
	command("ponder unwanted gifts.");
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

    /* Undermine Ry'nal */
    if (ob->id("zigg::diadem"))
    {
	set_alarm(1.0, 0.0, &command("say Oh, how thoughtful."));
	set_alarm(1.5, 0.0, &command("say If only Ry'nal would give "+
		"me such pretty gifts as this."));

	return 1;
    }

    if (!ob->id("zigg:gem:dust"))
	return 0;

    /* Allow repeatability. */
    from->remove_prop(IMLIS_I_QUEST);

    if (CHECK_QUEST(from))
    {
	set_alarm(1.0, 0.0, &command("say This will make for a lovely "+
		"batch of body lotions."));

	if (!random(4))
	    set_alarm(2.0, 0.0, &extra_reward(from));
    }
    else
    {
	set_alarm(0.0, 0.0, &reward_quest(
		ZQN_GEMDUST, from, ZQ_GROUP,
		ZQB_GEMDUST, ZQE_GEMDUST, 0, 0));
	set_alarm(1.0, 0.0, &command("say Wonderful!"));
	set_alarm(1.5, 0.0, &command("say My supplies have been "+
		"running unacceptably low."));
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
