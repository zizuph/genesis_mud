// cyprian ("cyprian.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Shopkeeper for candy.c
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

private static int am_busy;

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
        command("say to "+ OB_NAME(TP) +" I am not permitted to speak of "+
	"that.");
        break;
    case 1:
        command("say to "+ OB_NAME(TP) +" I am but a slave, you must ask "+
	"my Master");
        break;
    case 2:
        command("shrug helpless");
        break;
    default:
        command("say My duties now are only to make and sell the candy, I "+
	"should not speak of anything else.");
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
    
    return "say to "+ OB_NAME(TP) +" I cannot help you.";
}

private string
ask_quest(void)
{
    if (am_busy)
    {
        return "emote is too busy to answer.\n";
    }
    	
    return "say to "+ OB_NAME(TP) +" I know of none.";
}

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


private string
ask_hegemon(void)
{
    ask_seq(({"asay proud to "+ OB_NAME(TP) +" I was his favorite "+
        "for a time. I pleased him more than any of the other slaves and I "+
	"have the scars to prove it.", "emote runs his finger over a jagged "+
	"scar on what must have once been a beautiful cheek.", 
	"say When I was no longer fit to serve, he ordered the Master "+
	"Confectioner to train me and allow me to serve here."}));

    return "";
}

private string
ask_slave(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" I was a pleasure slave for "+
        "many years and favored by the nobility, even the High Lords "+
	"themselves.","say But too many years left their mark on me and I "+
	"am too scarred to be enjoyed that way. Those who I would serve "+
	"like the illusion of innocence.","say But I am blessed by Sabrus "+
	"and the Hegemon to be able to cultivate new talents and "+
	"offer new temptations here."}));
	
    return "";
}

private string
ask_scars(void)
{
    ask_seq(({"lashlower humbly", "say to "+ OB_NAME(TP) +" They are "+
        "evidence of the pleasure I gave many during my time as a "+
	"pleasure slave.", "say to "+ OB_NAME(TP) +" Unfortunately my "+
	"skin scars too easily, a bad trait for such a slave. I am no "+
	"longer fit to serve.", "say to "+ OB_NAME(TP) +" I still offer "+
	"pleasure through my culinary skills though."}));
	
    return "";
}

private void
zig_npc(void)
{
    setuid();
    seteuid(getuid());

    set_name("cyprian");
    set_race_name("half-elf");
    set_adj(({"supple", "scarred"}));
    set_title("the Confectioner");

    set_opinion(90);
    set_appearance(79);
    set_gender(G_MALE);
    set_size_descs("short", "plump");
    set_alignment(ALIGN_TRUSTWORTHY);
    set_stats(({ 50, 80, 80, 70, 150, 50 }), 25);

    skin_tone("ivory, scar-streaked");
    configure_eyes("humble", "hazel", 2);
    configure_hair("long", "russet", "gathered into a single tail at "+
        "the nape of his neck");

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

    clone_object(ZIG_OBJ +"lashes.c")->move(TO, 1);

    /* Questions and answers */
    set_dont_answer_unseen(1);
    set_default_answer("@@default_answer@@");

    add_ask(({ "candy", "candies", "confection", "confections" }),
        &ask_seq(({"say We sell many kinds of candies and confections. "+
	"Read the sign for a complete listing."})), 0);
    add_ask(({ "rynal", "ry'nal"}),
        &ask_seq(({"say He is gorgeous, I'll admit.", "say But I was the "+
        "Hegemon's favorite, and am not so easily impressed."})), 0);
    add_ask(({ "truffle", "truffles"}), &ask_seq(({
        "say We use the finest ingredients for the soft, creamy centers "+
	"and dip them in premium chocolate.", "say My favorite are the Kesoit "+
	"Fruit ones, but I don't suppose that is a surprise to many "+
	"people."})), 0);
    add_ask(({ "kesoit", "kesoit fruit", "kesoit truffle", "kesoit truffles",
	"kesoit fruit truffle", "kesoit fruit truffles"}), &ask_seq(({
        "say The fruit of the kesoit tree ripens only in flame and is quite "+
	"rare, making it a true delicacy.", "say When it is ripe, the kesoit "+
	"fruit is both sweet and picant.", "say Much like the cinnamon "+
	"candies, the spicy heat is the price of the unique flavor, making "+
	"them even sweeter and more pleasing for those of us who appreciate "+
	"such things."})), 0);
    add_ask(({ "help",}), ask_help, 1);
    add_ask(({ "quest", "task", "job" }), ask_quest, 1);
    add_ask(({ "scar", "scars", }), ask_scars, 1);
    add_ask(({ "slave", "slaves", "pleasure slave"}), ask_slave, 1);
    add_ask(({"hegemon", "Hegemon"}), ask_hegemon, 1);
    add_ask(({"marzipan",}), &ask_seq(({
	"say Marzipan is a paste made of finely ground almonds, egg whites "+
	"and sugar.", "say It is deliciously sweet and in some places it is "+
	"regarded as an aphrodisiac, but so are many of our treats."})), 0);
    add_ask(({"aphrodisiac", "aphrodisiacs"}), &ask_seq(({
	"say Marzipan, chocolate, strawberries, even blood oranges are "+
	"thought by some to arouse carnal desire.", "say Some even say "+
	"these things are blessed by Sisera.", "say I do not know if "+
	"it is true. Perhaps it is merely indulging in something you enjoy.",
	"say I have personally always found the sweet sting of the cinnamon "+
	"buttons most exciting."})), 0);
    add_ask(({"Sisera", "sisera"}), &ask_seq(({
	"say He reigns over carnal desire. There are many pleasures in the "+
	"Ziggurat which are in homage to Him.", "say Marzipan, chocolate, "+
	"strawberries, even blood oranges are all sometimes said to rouse "+
	"his blessings.", "Perhaps you should try some and see."})), 0);	
    add_ask(({"hard candies", "hard candy", "hard boiled candy", "drops",
	"hard boiled candies", "drop", "button", "buttons"}), &ask_seq(({
	"say Flavorful extracts are added to sugar and sweet corn syrup "+
	"and boiled with water to extreme temperatures.", "say They are then "+
	"poured into little molds and cooled into drops and buttons."})), 0);
    add_ask(({"cinnamon", "cinnamon buttons", "cinnamon candy",
	"cinnamon candies",}), &ask_seq(({
	"say Their fiery heat warms the blood and stings the tongue, "+
	"reminding us that for every moment of sweetness there is a "+
	"price to be paid and that the flavors of pain and pleasure are not "+
	"always so different.", "emote adds: They are my favorite.", 
	"lashlower shyly"})), 0);
    add_ask(({"fruit", "fruits"}), &ask_seq(({
	"say We get our fruits from the Ziggurat gardens, or the Outlands "+
	"when we have to.", "say We make sure every fruit we use is fresh "+
	"and ripe and of the highest quality."})), 0);
    add_ask(({"ziggurat","Ziggurat"}), &ask_seq(({
	"say The Ziggurat caters to every taste.", "say The only Duties here "+
	"are to please and be pleased.", "smile pleasantly"})), 0);
    add_ask(({"pleasure","pleasure palace"}), &ask_seq(({"say Pleasure "+
    	"comes in many forms, and all are available to be had at the "+
    	"Ziggurat."})), 0);
    	
    set_act_time(60);
    add_act("@@do_act");

    set_cact_time(10);
    add_cact("scream");
    add_cact("whimper faint");
    add_cact("panic");
}

public void
f_act1(int count)
{
    object room = environment(TO);

    switch(++count)
    {
    case 1:
	command("emote leaves east into the back room.");
	TO->set_no_show();
	break;
    case 2:
	TO->unset_no_show();
	TO->set_no_show_composite(0);
	command("emote returns from the back room carring a large silver "+
	    "tray to the counter and begins refilling the silver salvers.");
	break;
    }
    if (count < 2)
    {
	am_busy = set_alarm(7.0, 0.0, &f_act1(count));
    }
    else
    {
	am_busy = 0;
    }
}

public string
do_act(void)
{
    if (am_busy)
    {
	return "";
    }

    switch(random(10))
    {
    case 0:
        f_act1(0);
        break;
    case 1:
        command("hstroke");
        break;
    case 2:
        command("emote wipes down the counter with a clean cloth.");
        break;
    case 3:
        command("emote smiles unobtrusively.");
        break;
    case 4:
        command("say I make confections for all tastes.");
        break;
    case 5:
        command("say Don't forget to buy a sweet for your sweetheart.");
        break;
    case 6:
        command("emote absentmindedly runs his thumb over one of his "+
	    "pale pink scars.");
        break;
    case 7:
        command("We use only the finest ingredients available.");
        break;
    case 8:
        command("blink");
        break;   
    case 9:
        command("lashlower submissive");
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
            command("say to "+ oname +" If you wish to be offensive you "+
		"will have to find a slave trained for it below. "+
		"I no longer serve that way.");
            break;
        case 1:
            command("emote smiles impassively.");
            break;
        case 2:
            command("lashtilt amused "+ oname );
            break;
        case 3:
	    command("smile faintly");
            command("say to "+ oname +" Not bad. You could use some "+
		"practice though. One day you may truly be intimidating.");
            break;
        }
    }

    else if ((attr & ACTION_INTIMATE) || (attr & ACTION_INGRATIATORY))
    {
        switch(random(6))
        {
        case 0:
            command("eyelower "+ oname);
            command("say I know I am no longer fit to serve that way. "+
		"There is no need to mock me.");
            break;
        case 1:
            command("sigh regret");
            command("say to "+ oname +" My days as a pleasure slave are "+
                "over. I can give you only candy now.");
            break;
        case 2:
            command("say to "+ oname +" You are kind, but there are others "+
		"who can serve you in that manner on the lower levels.");
            break;
        case 3:
            command("smile distant");
            break;
        case 4:
            command("bat flirt at "+ oname);
            break;            
        default:
            command("sigh reminiscent");
            break;
        }
    }
    else switch(random(3))
    {
    case 0:
        command("smile thoughtfully at "+ oname);
        break;
    case 1:
        command("emote looks away quickly, trying to hide a smile.");
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

    command("bow graceful");
    command("introduce me to "+ oname);
    command("say to "+ oname +" Sirli, "+
	who->query_name() +"! What will be your pleasure today?");
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
        command("Leave this place. There is nothing for you here sin'ur.");
        return;
    }

    int i = random(15);

    if (IS_UNION(who))
    {
        if (i == 0)           
            command("say to "+ oname +" Quansu Faithful Warrior!");
	else if (i == 2)
            command("bow respect "+ oname);
	else if (i == 5)
            command("say to "+ oname +" I am honored by your "+
		"presence, Favored of Jazur.");
    }
    else
    {
        if (i > 9)
           command("say Sirli and welcome!");
	else if (i < 4)
           command("say to "+ oname +" Celebrate the Source!");
    }
}
