// file name:   ~Avenir/common/bazaar/NPCS/dancer.c
// creator(s):  Kanga Sept 1994 & Grace May  1995
// last update: Lilith, April 29, 1997
//		Sirra, Aug 2002 (added tasks, qualita mark, add_the_asks())
//		Lucius, May 2007: Fixed typos.
// purpose:     To provide 'colour' for Bazaar
// note:        club idea: a minor guild for females
//              in the style of Dancers of the Seven Veils
//
// bug(s):      none anymore *hope hope*
//		Fixed command and TP->query_real_name bug.
//			-Sirra, Aug 2002
//
// to-do:       add grovel emote hook (if slave grovels, special response)
//		add tasks
//		add response when slave enters her environment.
#pragma strict_types

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

#include <money.h>
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/common/bazaar/bazaar.h"

#define L(str)  lower_case(str)

int add_the_acts();

int dance_id = 0;
int TASK_BUSY = 0;

void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_name("qalita");
    set_living_name("qalita");
    add_name(({"dancer", "woman", "female", "qalita"}));
    set_race_name("human");
    set_adj(({"veiled", "dark-eyed"}));
    set_title("the Dancer of Veils");
    set_long("This small human is supple and sensuous, draped from "+
      "head to toe in veils and bedecked in jewels. "+
      "Her dark eyes, ringed as they are with glittering "+
      "gold, seem to stare boldly at you from beneath her lowered "+
      "veil.\nIt would appear that she is a dancer of sorts.\nShe"+
      " looks like the image of perfection.\n");

    set_gender(G_FEMALE);
    set_aggressive(0);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop("_live_m_attack_thief", "thief_fun");
    add_prop(CONT_I_HEIGHT, 150);
    add_prop(CONT_I_WEIGHT, 50000);

    set_stats(({60, 75, 60, 50, 50, 40}));
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_CLUB, 40);
    set_alignment(0);

    add_the_acts();

    add_ask(({"city","forbidden city"}),
      "say The Forbidden City is the island where the Shadow Elves "+
      "live. It is a marvellous place. For those permitted to enter, "+
      "it is a great honour.",1);
    add_ask(({"zuggarat", "zugarat", "ziggarat", "pleasure palace"}),
      "say It is the Pleasure Palace at the center of the Forbidden City. "+
      "It is the place where every sexual fantasy can be fulfilled..."+
      "for a price.", 1);
    add_ask(({"dance", "dance for me", "perform"}),
      "say I will dance for you for the small fee of one gold coin.", 1);
    add_ask(({"dance of veils", "teach dance", "teach",
	"test", "test for dance"}),
      "say Go to the room north of here, and there shall you be tested.", 1);
}

int
add_the_acts()
{
    set_act_time(5);
    add_act("emote rustles a veil, briefly exposing a slender thigh.");
    add_act("emote catches your eyes with her bold, dark stare.");
    add_act("emote twirls around, setting her multi-coloured veils "+
      "aflutter.");
    add_act("emote caresses herself with slender, beringed hands.");

    add_act("say I will dance for you. I charge but one gold piece.");
    add_act("emote jingles her bracelets. They make a delightful "+
      "tinkling sound.");
    add_act("say I will show you something you have never seen before.");
    add_act("say A gold coin, and you shall see me dance.");
    add_act("emote hums a tune and moves her shoulders sinuously.");
    add_act("emote lowers her veil over her face in a coquettish "+
      "show of modesty.\n");

    return 1;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!from)
	return;

    if (IS_INFIDEL(from))
    {
	command("You are even more foolish than you look.");
	command("shout Guards! I've found an infidel!");
	return;
    }

    if (ob->id("gold coin") || ob->id("platinum coin"))
    {
	set_alarm(1.0,0.0, "dance_test");
	return;
    }
    else
	set_alarm(1.0,0.0,&command("thank " + from->QRN));
}

int
dance_test()
{
    if (dance_id > 0)
    {
	command("emote gives an irritated look.");
	command("say I am already performing a dance. Please "
	  +"wait your turn and I will dance for you, too.");
	return 1;
    }

    if (TASK_BUSY > 0)
    {
	command("say I am busy just now. Come back later.");
	command("emote pockets her coin.");

	return 1;
    }

    //shut her up while she dances.
    clear_act();
    command("introduce myself");
    dance_id = set_alarm(2.0,0.0,"dance_for_them");
    return 1;
}

int
dance_for_them()
{
    if (TP->query_gender() > 0)
    {
	say("Qalita gives "+ QTNAME(TP) +" a sultry look.\n");
	write("Qalita gives you a sultry look.\n");
	command("say I like to dance for women.");
	command("wield tambourine");
	set_alarm(4.0,0.0,"dance_step1");
	return 1;
    }
    command("say Thank you.");
    command("emote smiles. Her rosebud mouth parts enticingly.");
    command("wield tambourine");
    set_alarm(4.0,0.0,"dance_step1");
    return 1;
}

int
dance_step1()
{
    command("emote raises one hand and shakes a tambourine.");
    write("The tambourine makes a wonderful jingling sound.\n");
    say("The tambourine makes a wonderful jingling sound.\n");
    set_alarm(7.0,0.0,"dance_step2");
    return 1;
}

int
dance_step2()
{
    write("Qalita steps close to you and raises her voice in an odd "+
      "ululating chant.\n");
    say("She steps close to "+ QTNAME(TP) +" and raises her voice "+
      "in an odd ululating chant.\n");
    set_alarm(7.0,0.0,"dance_step3");
    return 1;
}

int
dance_step3()
{
    command("emote moves sinuously to the complementary music of voice "+
      "and tambourine.");
    set_alarm(7.0,0.0,"dance_step4");
    return 1;
}

int
dance_step4()
{
    command("emote loosens a veil at her waist, "+
	"exposing a smooth brown thigh.");
    write("She brushes close to you and then whirls away, leaving "+
      "behind the scent of patchouli and the memory of softest silk.\n");
    say("She dances close to "+ QTNAME(TP) + " and then whirls away.\n"+
      QCTNAME(TP) +" watches her dance away, an odd look on "+
      TP->query_possessive() +" face.\n");
    set_alarm(6.0,0.0,"dance_step5");
    return 1;
}

int
dance_step5()
{
    command("emote dances slowly, her fluttering veils allowing fleeting "+
      "glimpses of belly, arm, and thigh.");
    set_alarm(6.0,0.0,"dance_step6");
    return 1;
}

int
dance_step6()
{
    command("emote rattles the tambourine faster and bangs it against her "+
      "hip.");
    write("Qalita whirls around you with her arms raised.\nThe veils brush "+
      "against you, tempting you to reach out so you can feel the silk "+
      "slide between your fingers.\n");
    say("Qalita whirls around "+ QTNAME(TP) +", her arms raised and her "+
      "veils brushing against "+ TP->query_objective() +".\n");
    set_alarm(7.0, 0.0, "dance_step7");
    return 1;
}

int
dance_step7()
{
    command("unwield tambourine");
    say("Qalita takes "+ QTPNAME(TP) +" hands into her own.\n");
    write("Qalita takes your hands in hers.\n");
    say("She dances closer to "+ TP->query_objective() +".\n");
    write("She dances closer to you, brushing her silken, perfumed "+
      "body against yours.\n");

    if (TP->query_gender() > 0)
    {
	say(QCTNAME(this_object())+" whispers something to "+QTNAME(TP)+".\n");
	write("Qalita whispers in your ear: I like to dance "
	  +"with women, don't you?\n");
	command("wiggle erot");
	set_alarm(7.0,0.0,"dance_woman");
	return 1;
    }

    say(QCTNAME(this_object())+" whispers something to "+QTNAME(TP)+ ".\n");
    write("Qalita whispers in your ear: I find you attractive.\n");

    command("wiggle erot");
    set_alarm(7.0,0.0,"dance_male");
    return 1;
}

int
dance_male()
{
    write("You suddenly feel quite warm.\n");
    say("Sweat breaks out on " + QTPNAME(TP) + " forehead.\n");
    set_alarm(7.0, 0.0, "dance_step8");
    return 1;
}

int
dance_step8()
{
    write("Qalita places your hands on her hips and runs the palms "+
      "of her hands over your chest.\nQalita's dancing body rubs "+
      "lightly against your more intimate parts.\n");
    say(QCTNAME(TP) +" seems to pull Qalita's delightfully wriggling body "+
      "against his own.\n");
    set_alarm(10.0, 0.0, "dance_step9");
    return 1;
}

int
dance_woman()
{
    write("Qalita places your hands around her neck, forcing you to "+
      "draw her nearer.\nYou feel stunned as Qalita presses her breasts "+
      "against yours and dances sinuously against you.\n");
    say(QCTNAME(TP) +" looks stunned as Qalita deliberately rubs "+
      "her delightfully wriggling body against her own.\n");
    set_alarm(10.0, 0.0, "dance_step9");
    return 1;
}

int
dance_step9()
{
    command("emote finishes her dance.\nThe silken veils settle "+
      "around her, once again covering her from head to toe.");
    set_alarm(3.0, 0.0, "dance_step10");
    return 1;
}

int
dance_step10()
{
    command("say If you would like to see me complete the dance, you must "+
      "find a way to enter the City and come see me at the Ziggurat.");
    say("Qalita blows "+ QTNAME(TP) +" a kiss.\n");
    write("Qalita blows you a kiss.\n");
    set_alarm(1.0, 0.0, "end_the_dance");
    return 1;
}

void
end_the_dance()
{
    remove_alarm(dance_id);
    add_the_acts();
    dance_id = 0;
}

/*
 * Function name: return_hug
 * Description  : When the NPC is hugeed, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_hug(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
      (environment(actor) != environment()))
    {
	return;
    }

    command("smile slight "+ OB_NAME(actor));
    command("say Demonstrations of affection are quite nice, but I'd rather "+
      "have gold in my purse.");
}

/*
 * Function name: return_hit
 * Description  : When the NPC is groped, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_hit(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) || (environment(actor) != environment()))
    {
	return;
    }

    command("frown "+ OB_NAME(actor));
    command("say I am here to dance, not be abused.");
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
    if (!objectp(actor) || (environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    command("smile erotically");
    command("snuggle " + OB_NAME(actor));
    command("say Give me a gold coin and I'll dance for you.");
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
    if (!objectp(actor) || (environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    command("poke " + OB_NAME(actor));
    command("say You must be a friend of Tricky's.");
    command("say Any friend of Tricky's is welcome, he used to spend a " +
      "lot of gold watching me dance.");
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
	set_alarm(3.0, 0.0, &return_grope(actor, adverb) );
	return;

    case "poke":
	set_alarm(3.0, 0.0, &return_poke(actor, adverb) );
	return;
    case "hug":
    case "kiss":
    case "cuddle":
    case "sunggle":
	set_alarm(3.0, 0.0, &return_hug(actor, adverb));
	return;
    case "slap":
    case "kick":
	set_alarm(3.0, 0.0, &return_hit(actor, adverb));
	return;
    }
}

void
arm_me()
{
    seteuid(getuid());
    clone_object(OBJ + "worn/qbracel")->move(this_object());
    clone_object(OBJ + "worn/qbracer")->move(this_object());
    clone_object(OBJ + "worn/blouse")->move(this_object());
    clone_object(OBJ + "worn/qring1")->move(this_object());
    clone_object(OBJ + "worn/qskirt")->move(this_object());
    clone_object(OBJ + "worn/qring2")->move(this_object());
    clone_object("/d/Avenir/common/clubs/dance/anklet")->move(this_object());
    clone_object("/d/Avenir/common/clubs/dance/veil")->move(this_object());
    command("wear all");
    command("bells on");
}

void
thief_fun(object thief, object victim, object ob)
{

    say(QCTNAME(this_object())+" glares seductively at "+QTNAME(TP));
    write("Qalita glares seductively at you.\n");

    set_alarm(3.0, 0.0, &command("say Now what "
	+"exactly are you trying to steal?"));
    set_alarm(4.0, 0.0, &command("smile sexily"));
}
