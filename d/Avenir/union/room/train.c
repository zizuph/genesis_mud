/*  One of the training rooms for the      */
/*           Shadow Union                  */
/*           Cirion 031996                 */
#pragma strict_types

#include "../defs.h"
#include "../lib/skills.h"

inherit BASE;
inherit "/lib/skill_raise";

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

public void set_up_skills();

public object trainer;
public int *target_hits = allocate(6);
public string *target_descs = ({
    "outside the target area",
    "on the outer circle",
    "on the second circle in",
    "on the third circle in",
    "one circle from the centre",
    "right on the bullseye",
});


public void
reset_room(void)
{
    if (!trainer)
    {
	if (!objectp(query_prop(UCORPSE_PROP("anglentis"))))
	    trainer = clone_here(NPC+"anglentis");
    }

    if (trainer && !present(trainer))
	trainer->move_living("away", TO);
}

public void
union_room(void)
{
    set_short("wide stone chamber");
    set_long("High smooth walls of marble rise up "+
	"to the vaulted ceiling here, and a thin, "+
	"old rug is spread out along the floor. Along "+
	"the walls are murals of old battles and "+
	"proud heroes, and on the east wall is a "+
	"large padded target.\n");

    add_item("target","The target is large and round, divided "+
	"into five concentric circles, with one small "+
	"green circle in the very centre.@@target_state@@\n");
    add_item(({"rug","carpet"}),"The rug is old and threadbare, "+
	"made from a thin weave cloth.\n");
    add_item(({"floor","ground"}),"The floor is dull, hard stone. "+
	"Most of it is covered by an old, threadbare rug.\n");
    add_item(({"wall","walls"}),"The walls are covered with "+
	"murals in base relief, of warriors and sublime "+
	"depictions of battles.\nOn the east wall is "+
	"a large, padded target.\n");
    add_item(({"mural","murals","depiction","depictions","battle",
	"battles"}),"The murals on the walls are done in elegant "+
	"and sublime artistry. They show a number of battles, with "+
	"tall, dark-eyed warriors leading attacks against an "+
	"opposing army.\nOne tall warrior, wearing a great mithril "+
	"helm, seems to be leading the ranks.\n");
    add_item("warrior","He is great and tall, with long, flowing "+
	"white hair in stark contrast to his abysmally black "+
	"eyes. He wears a high-crowned helm and holds "+
	"a very long sword in his right hand.\nThe depiction "+
	"shows him as being noble and proud, a great leader.\n");
    add_item(({"ceiling","roof"}),"It is high overhead, made from "+
	"light, even stone.\n");

    add_cmd_item(({"mural","murals","walls","bas relief","carvings"}),
	({"touch","feel"}),"The carvings are done in shallow relief, "+
	"so that the figures in the battles stand out slightly from "+
	"the wall.\n");
    add_cmd_item(({"mural","wall"}),"push","It does not move.\n");
    add_cmd_item(({"rug","carpet"}),({"lift","move","look under"}),
	"There is nothing beneath it.\n");

    add_exit("hall_w1", "north");

    create_skill_raise();
    set_up_skills();

    /* Wiz info for stat_object */
    add_prop(OBJ_S_WIZINFO, "This is one of the training halls "
      +"for the Union of the Warriors of Shadow. If a problem "
      +"occurs and you find it necessary to shut down the "
      +"guild, do 'Call /d/Avenir/union/list close_guild' (NOT "
      +"Call here close_guild). Note that this will shut down "
      +"ALL of the training rooms in the guild, and it will "
      +"remain so until someone calls open_guild (ie, it will "
      +"last through reboots). In other words, make sure you "
      +"have a good reason for doing it!\n");

    reset_room();
}

public string
target_state(void)
{
    string str, *tmpstr = ({ });

    for (int i = 0; i < 6; i++)
    {
	if (!target_hits[i])
	    continue;

	if (target_hits[i] == 1)
	    str = " time ";
	else
	    str = " times ";

	tmpstr += ({
	    LANG_WNUM(target_hits[i]) + str + target_descs[i] });
    }

    if (!sizeof(tmpstr))
	return " The target is clean and has not been hit at all.";

    str = "";

    if (sizeof(tmpstr) == 1)
	return " The target has been hit " + tmpstr[0] + ".";

    for (int i = 0; i < sizeof(tmpstr); i++)
    {
	if ((i + 1) == sizeof(tmpstr))
	    str += " and " + tmpstr[i] + ".";
	else if (sizeof(tmpstr) == 2)
	    str += " " + tmpstr[i];
	else
	    str += " " + tmpstr[i] + ",";
    }

    return " The target has been hit" + str;
}

/* Skill functions and hooks */
public void
set_up_skills(void)
{
    sk_add_train(SS_WEP_KNIFE,  /* sknum         */
      "use a knife with skill", /* desc          */
      0,                        /* skname        */
      5,                        /* cost factor   */
      MAX_KNIFE,                /* max skill     */
      SS_OCCUP,                 /* limiting stat */
      100 );                    /* limit weight  */


    sk_add_train(SS_WEP_SWORD,
      "fight with a sword",
      0,
      4,
      MAX_SWORD,
      SS_OCCUP,
      100 );

    sk_add_train(SS_SLASH,
      "slash with a knife and sword",
      "slash",
      75,
      MAX_SLASH,
      SS_OCCUP,
      90 );

    sk_add_train(SS_FLING,
      "throw knives and daggers",
      "fling",
      75,
      MAX_FLING,
      SS_DEX,
      90 );

    sk_add_train(SS_PARRY,
      "parry blows with a weapon",
      0,
      25,
      MAX_PARRY,
      SS_DEX,
      100 );

    sk_add_train(SS_2H_COMBAT,
      "battle with two weapons",
      0,
      25,
      MAX_2H_COMBAT,
      SS_DEX,
      80 );
}

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 */
public int
sk_improve(string str)
{
    if (GUILD_CLOSED)
    {
	write("The Union has been shut down due to problems, so "+
	    "training is impossible.\nTry back later.\n");
	return 1;
    }

    if (!present(trainer))
	return 0;

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOTRAIN))
    {
	trainer->command("us I have been told that you "+
	    "are to be denied instruction.");
	trainer->command("shrug .");
	trainer->command("us Sorry.");
	return 1;
    }

    if (!STATE)
    {
	trainer->command("us You have let the flame go out. I "+
	    "will teach you nothing.\n");
	return 1;
    }

    if (ENEMY(TP))
    {
	trainer->command("us Traitor and fool! Do you honestly "+
	    "think I will teach you after your actions?");
	trainer->command("shout Begone before I slay you!");
	return 1;
    }

    return ::sk_improve(str);
}

/*  Just a toy ....... */
public int
do_throw(string str)
{
    int chances, hit;
    object knife, gman;

    NF("Throw what at what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, TP,
	    "[the] / [a] / [an] %o 'at' [the] 'target'", knife) || !knife)
	return 0;

    NF("You can only throw knives at the target.\n");
    if (!function_exists("create_weapon", knife) ||
	knife->query_wt() != W_KNIFE)
	return 0;

    if (DRUNK(TP) > 50)
    {
	write("You try to throw your "+ knife->short() +
	    ", but you are far too drunk.\n");
	say(QCTNAME(TP)+" stumbles around drunkenly, "+
	    "looking like a fool.\n");
	return 1;
    }

    chances = TP->query_skill(SS_FLING) +
	TP->query_skill(SS_WEP_KNIFE) +
	TP->query_skill(SS_ACROBAT) +
	TP->query_stat(SS_DEX) +
	TP->query_skill(SS_AWARENESS) +
	random(900) - 300;

    if (chances < 0) chances = 0;
    if (chances > 1000) chances = 1000;

    switch(chances)
    {
    case 0 .. 150:	hit = 0;	break;
    case 151 .. 300:	hit = 1;	break;
    case 301 .. 500:	hit = 2;	break;
    case 501 .. 700:	hit = 3;	break;
    case 701 .. 890:	hit = 4;	break;
    default:		hit = 5;	break;
    }

    write("You aim carefully at the target, and then "+
	"throw the "+ knife->short() +" at it.\n");
    say(QCTNAME(TP)+" aims carefully at the target, and then "+
	"throws "+ LANG_ASHORT(knife) +" at it.\n");

    target_hits[hit]++;
    knife->move(ENV(TP), 1);

    if (TP != trainer && present(trainer))
	gman = trainer;

    str = CAP(LANG_THESHORT(knife));

    switch(hit)
    {
    case 0:
	tell_room(TO, str +" completely misses the target.\n");
	gman->command("chuckle soft");
	break;
    case 1:
	tell_room(TO, str +" hits the target on the outer circle.\n");
	gman->command("smirk");
	break;
    case 2:
	tell_room(TO, str +" hits the target on the second circle in.\n");
	gman->command("nod apprec "+ TP->query_real_name());
	break;
    case 3:
	tell_room(TO, str +" hits the target on the third circle in.\n");
	gman->command("whistle");
	break;
    case 4:
	tell_room(TO, str +" hits the target one circle from the centre.\n");
	gman->command("congrat "+ TP->query_real_name());
	break;
    case 5:
	tell_room(TO, str +" slams into the target right on the bullseye!\n");
	gman->command("gasp");
	gman->command("applaud");
	break;
    }
    return 1;
}

public varargs int
sk_query_max(int sknum, int silent)
{
    int max;

    switch(sknum)
    {
    case SS_WEP_SWORD:   max = TP->query_stat(SS_OCCUP);     break;
    case SS_WEP_KNIFE:   max = TP->query_stat(SS_DEX);       break;
    case SS_FLING:       max = TP->query_stat(SS_DEX);       break;
    case SS_SLASH:       max = TP->query_stat(SS_OCCUP);     break;
    case SS_PARRY:       max = TP->query_stat(SS_DEX);       break;
    case SS_2H_COMBAT:   max = TP->query_stat(SS_DEX);       break;
    default:             max = TP->query_stat(SS_OCCUP);     break;
    }

    /* Players that are trainees will not be able to train very high */
    if (TP->query_skill(OCC_LEVEL) < NORMAL)
	max = 50;

    return min(max, ::sk_query_max(sknum, silent));
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 */
public int
sk_hook_cant_train(string skill, int to_lev)
{
    TP->catch_msg("You fail to adopt what "+ QTNAME(trainer) +
	" attempts to teach you.\n");
    trainer->command("grumble");
    return 1;
}

/*
 * Function name: sk_hook_learn_known
 * Description:	  Player wants to learn an already known skill
 */
public int
sk_hook_learn_known(string skill)
{
    notify_fail("You already know that skill, try to practice it.\n");
    return 0;
}

/*
 * Function name: sk_hook_no_list_learn
 * Description:   No more unknown skills for the player in this guild
 */
public int
sk_hook_no_list_learn(void)
{
    write("For you there are no unknown skills here. You might want to "+
	"practice those you already know.\n");
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(do_throw,  "throw");

    if (IS_MEMBER(TP))
    {
	add_action(sk_improve, "practice");
	add_action(sk_improve, "learn");
    }
}
