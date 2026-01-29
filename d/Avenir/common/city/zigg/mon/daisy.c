// Daisy ("daisy.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Shopkeeper for flowers.c
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

#define ACT	(45 + random(15))
#define MAKEOVER_SHADOW    (ZIG_OBJ + "makeover_shadow")

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
        command("emote is too busy to answer.\n");
        return "";
    }
	
#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       CAP(query_name()) +" about: "+ query_question() +".\n");
#endif

    switch(random(4))
    {
    case 0:
        ask_seq(({"say to "+ OB_NAME(TP) +" I shouldn't speak of such things "+
            "whilst I'm working.", "smile apologetic"}));
        break;
    case 1:
        ask_seq(({"emote brushes the silky blonde hair away from her eye, "+
	    "but it immediately falls back into place.", "say to "+ 
	    OB_NAME(TP) +" I'm afraid I don't know about that."}));
        break;
    case 2:
        command("say to "+ OB_NAME(TP) +" Maybe one of the gardeners knows "+
	    "about that.");
        break;
    default:
        ask_seq(({"bite", "say I just arrange the flowers."}));
        break;
    }

    return "";
}

private string
ask_help(void)
{
    if (am_busy)
    {
        return "emote is too busy to answer.\n";
    }
    	
    return "say to "+ OB_NAME(TP) +" I'm not trained for that.";    
}

private string
ask_quest(void)
{
    if (am_busy)
    {
        return "emote is too busy to answer.\n";
    }
    	
    return "say to "+ OB_NAME(TP) +" If you check back later, I might have "+
	"something.";
}

private void
zig_npc(void)
{
    setuid();
    seteuid(getuid());

    /* Name, rank and serial number */
    set_name("daisy");
    set_race_name("elf");
    set_adj(({"short", "willowy"}));
    set_title("Ardura dei Adayr, Ziggurat Florist");
    set_syb_house("Adayr");

    /* Gender, outlook and buffness */
    set_opinion(90);
    set_appearance(99);
    set_gender(G_FEMALE);
    set_size_descs("short", "lean");
    set_alignment(ALIGN_TRUSTWORTHY);
    set_stats(({ 50, 150, 80, 70, 80, 50 }), 25);

    configure_eyes("warm", "golden brown", 2);
    configure_hair("short", "pale gold", "styled in a silky cap that covers "+
        "one eye");

    /* Properties */
    add_prop(LIVE_I_NON_REMEMBER, 1);

    /* Skills */
    set_skill(SS_ACROBAT,    100);
    set_skill(SS_TRADING,    60);
    set_skill(SS_APPR_OBJ,   70);
    set_skill(SS_APPR_VAL,   70);
    set_skill(SS_LANGUAGE,   80);
    set_skill(SS_AWARENESS,  80);
    set_skill(SS_LOC_SENSE,  40);
    set_skill(SS_LANGUAGE,80);
    set_skill(SS_ALCHEMY,    50);
    set_skill(SS_HERBALISM,  50);
    set_skill(SS_SPELLCRAFT, 50);

    set_skill(SS_ELEMENT_AIR,   60);
    set_skill(SS_ELEMENT_LIFE,  60);
    set_skill(SS_ELEMENT_EARTH, 60);
    set_skill(SS_ELEMENT_WATER, 60);
    set_skill(SS_ELEMENT_DEATH, 60);
    set_skill(SS_FORM_ENCHANTMENT,   70);
    set_skill(SS_FORM_TRANSMUTATION, 70);

    /* Questions and answers */
    set_dont_answer_unseen(1);
    set_default_answer("@@default_answer@@");

    add_ask(({ "flowers", "plants" }), &ask_seq(({
        "say All the flowers come from the Ziggurat's tiered garden, but "+
        "we only take as much as Sachluph permits... and Maree."})), 0);

    add_ask(({ "garden", "tiered garden", "public garden", "gardens",}),
        &ask_seq(({"say The Ziggurat's gardens are the best in Sybarus. "+
        "Such a pleasure!", "say Unfortunately the public is only allowed "+
        "on levels three and eight and only Nobles on eight.", "say Much "+
        "of our food that is not imported comes from the gardens on the "+
        "other levels."})), 0);

    add_ask(({ "posy", "posies", "bouquet", "bouquets" }), &ask_seq(({
        "say It's my job to arrange the posies and bouquets for those who "+
        "don't wish to make their own."})), 0);

    add_ask(({ "help", "beautiful" }), ask_help, 1);
    add_ask(({ "quest", "task", "job" }), ask_quest, 1);
    add_ask(({ "rynal", "ry'nal", "makeover", "makeovers", }), 
        &ask_seq(({"say His hands always seemed clammy to me."})), 0);
    add_ask(({"market", "bazaar", "marketplace", "merchantile pale"}),
	&ask_seq(({"say There bazaar caters to Outlanders but Sybarites "+
	"shop in the merchantile pale for the most part, though there "+
	"are many fine shops in the City as well and the Ziggurat "+
	"offers many indulgences"})), 0);
    add_ask(({"park","island", "holm", "Holm"}), &ask_seq(({"say The "+
	"Holm of the Icondite is where the Hegemon's favored Hunt."})), 0);
    add_ask(({"bath", "melchior's bath"}), &ask_seq(({
	"say I don't get to go very often, but it is a welcome treat after "+
	"being on my feet all day."})), 0);
    add_ask(({"bridge","bridge of sighs"}), &ask_seq(({
	"say It is the link between the City and the Bazaar."})), 0);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}),
	&ask_seq(({"say The Ziggurat is at the heart of the City, if you "+
	"go out into the garden, there is a lovely view."})), 0);
    add_ask(({"infidel", "infidels"}), &ask_seq(({
	"say We mustn't speak of them lest our attention be mistaken for "+
	"sympathy."})), 0);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
	&ask_seq(({"say We serve the Will of the Idrys and so we will "+
	"live forever in the light of the Source."})), 0);
    add_ask(({"sachluph", "Sachluph"}), &ask_seq(({
	"say Sachluph is the Idrys of the Eleventh Hour, regent of all "+
	"that grows from the earth."})), 0);
    add_ask(({"union", "shadow union", "shadow warrior"}),
	&ask_seq(({"emote entones: Each one more lovely than a flower's "+
	"tender bloom.", "say To see beneath their veils is to witness "+
	"Jazur's perfection."})), 0);
    add_ask(({"dej-minha"}),&ask_seq(({"say They are lovely and fierce, "+
    	"sweet and spicy.", "It is every Sybarite girl's dream to be one "+
    	"of the Hegemon's chosen."})), 0);
    add_ask(({"hegemon", "Hegemon"}), &ask_seq(({
	"say He is nearest the Idrys and the Source shines brightly upon "+
	"him.", "say Many question his choice to allow Outlanders into the "+
	"Ziggurat, but I say that is heresy!"})), 0);
    add_ask(({"idrys", "Idrys"}), &ask_seq(({"say They are "+ 
	"true Gods. They give us all that we might ever need.", "say It "+
	"is a small thing that they ask our Service in return."})), 0);
    add_ask(({"garden",}), &ask_seq(({
	"say Every level of the Ziggurat has lovely gardens.", "say They "+
	"provide us with beautiful flowers and delicious food.", "say "+
	"Truly Sachluph blesses us!"})), 0);
    add_ask(({"sachluph", "Sachluph"}), &ask_seq(({
	"say Sachluph is the Idrys of the Eleventh Hour, regent of all "+
	"that grows from the earth."})), 0);
    add_ask(({"ziggurat","Ziggurat"}), &ask_seq(({
	"say The Ziggurat is an altar to beauty and pleasure and passion.",
	"say Every indulgence is a prayer to the Idrys who grant us lives "+
	"of Joy as well as Duty."})), 0);
    add_ask(({"flower","flowers"}), &ask_seq(({
	"say All the flowers I sell come from the garden of the Ziggurat.",
	"say Sachluph's blessing enables Maree to grow all kinds of flowers "+
	"regardless of time or climate. It seems to be rather taxing though.",
	"say I'm glad, I just have to arrange them."})), 0);
    add_ask(({"Maree","maree","spell","power"}), &ask_seq(({"say She is the "+
	"head gardener of the Ziggurat and a servant of Sachluph."})), 1);

    set_act_time(ACT);
    add_act("@@do_act");

    set_cact_time(10);
    add_cact("scream");
    add_cact("whimper");
    add_cact("spit enemy");

    set_cchat_time(5);
    add_cchat("I did nothing to you!");
    add_cchat("S'nay! Plalgus will judge you.");
    add_cchat("Die in Darkness, sin'ur!");

}

static void
add_clothing(void)
{
    object cm = CM->get_this_object();

    cm->set_cset("bright");
    cm->make_girl(TO, -1);

    object flower = clone_object(ZIG_RLG +"single");
    flower->set_flower("daisy", 0);
    flower->move(TO, 1);

    command("wear garments");
    set_alarm(2.0, 0.0, &command("tuck flower"));
}

public string
do_act(void)
{
    int num = random(4);

    if (am_busy)
    {
	return "";
    }

    switch(num)
    {
    case 0:
	command("hbrush");
	break;
    case 1:
	command("emote hums a lovely tune as she arranges some flowers.");
	break;
    case 2:
	command("eyesta thought");
	break;
    case 3:
	command("emote trims the stems on some fresh flowers and quickly "+
	"places them in an urn full of water.");
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
     
    if (am_busy)
    {
	return;
    }           

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
            command("smile calmly");
            command("say to "+ oname +" It takes more than that to bait me.");
            break;
        case 1:
            command("emote ingores you.");
            break;
        case 2:
            command("sigh");
            break;
        case 3:
	    command("emote offers a strained but polite smile.");
            break;
        }
    }
    else if ((attr & ACTION_INTIMATE) || (attr & ACTION_INGRATIATORY))
    {
        switch(random(5))
        {
        case 0:
            command("eyespa bright");
            break;
        case 1:
            command("whisper to "+ oname +" There are pleasure slaves in the "+
                "levels below if that is what you seek.");
            break;
        case 2:
            command("eyelower "+ oname);
            break;
        case 3:
            command("emote raises one golden eyebrow in amusement.");
            break;
        default:
            command("smile shy");
            break;
        }
    }
    else switch(random(5))
    {
    case 0:
        command("smile politely");
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
    if (am_busy)
	return;
    
    if (IS_INFIDEL(who))
        return;

    command("curtsey politely");
    command("introduce me to "+ oname);
    command("say to "+ oname +" Sirli, "+
	who->query_name() +". Welcome to the Gardens.");
}
