/* One of the  training rooms for the      *
 *           Shadow Union                  *
 *           Cirion 031996                 *
 *
 * Revisions:
 * 	Lilith, Sep 2001: Added functionality to saying Plantilsi amon Dowd
 * 	Lucius, Aug 2017: Removed npc-teaming with Dowd.
 *  Lilith, Oct 2021: Bringing back ogre raids. Making it possible to 
 *                    summon Dowd to the Gate but not team with him.
 */
#pragma strict_types
#include "../defs.h"
#include "../lib/skills.h"

inherit BASE;
inherit "/lib/skill_raise";

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>

#define OPR	"_live_i_seeunionwhiteoutline"

public object dowd;
public int broken, alarm;
public int alarm_id = 0;
public void set_up_skills(void);


public void
reset_room(void)
{
    if (broken)
    {
	broken = 0;
	tell_room(TO, "A rushing noise, like a wind you cannot feel, "+
	    "arises in the room.\n");
    }
}

public string
awa_check(void)
{
    if (TP->query_skill(SS_AWARENESS) < 30)
	return "";

    TP->add_prop(OPR, 1);
    return " There seems to be a faint outline traced in the "+
	"sandstone wall to the north.";
}

public void
union_room(void)
{
    set_short("white room");
    set_long("A soft glow seems to emanate from the sandstone "
      +"walls framing this large, empty room. The floor is "
      +"smooth and hard, made from light grey marble, and "
      +"the ceiling is constructed from the same material "
      +"as the walls. A low archway opens out to a hall to "
      +"the south.@@awa_check@@\n");

    add_item(({"panel", "outline"}), "@@check_outl@@");
    add_item(({"wall","walls","south wall","east wall","west wall",
	    "north wall"}), "The walls are all made from stark white "+
	"sandstone, soft and powdery, almost luminescent.@@awa_check@@\n");
    add_item(({"ceiling","roof"}), "The ceiling, like the walls, is "+
	"made from sandstone. There seems to be something written in "+
	"the stone.\n");
    add_item(({"arch","archway"}), "It is made from black granite, "+
	"strong and wide. It is quite low, however, and leads "+
	"out into the hallway to the south.\n");
    add_item(({"hall","hallway"}), "The hallway to the south seems "+
	"to shed a greenish light through the archway, falling on "+
	"the floor and making eerie shadows that seem to dance.\n");

    add_cmd_item(({"wall","walls","granite"}),({"touch","feel"}),
	"The sandstone walls are soft, almost powdery, and smooth.\n");
    add_cmd_item(({"ceiling","roof","writing","words"}),"read",
	"Plantilsi amon Dowd\n");

    add_exit("hall_ne2","south");

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
}

public string
check_outl(void)
{
    if (TP->query_skill(SS_AWARENESS) > 30 || TP->query_prop(OPR))
    {
	TP->add_prop(OPR, 1);
	return "It is a very faint outline in the sandstone of the "+
	    "north wall, like a perfectly square panel.\n";
    }
    else return "You see no outline.\n";
}

private void
reset_dowd(void)
{
    if (dowd)
    {
	dowd->command("emote seems to fade from sight, like a dream.");
	dowd->remove_object();
    }
	
	broken = 0;
}

private void
break_it(void)
{
    tell_room(TO, "The floor seems to rumble slightly, making the "+
	"walls and ceiling expel clouds of white dust.\n");
    tell_room(TO, "You hear a crash from far away!\n");

    if (alarm_id)
		remove_alarm(alarm_id);
  
    if (objectp(dowd))
    {
        dowd->remove_object();
        dowd = clone_object(NPC +"dowd_amon");
        dowd->move_living("M", TO);
        dowd->plantilsi_amon();   
		alarm_id = set_alarm(3600.0, 0.0, reset_dowd);    // An hour
		return;
    }
	else 
    alarm_id = set_alarm(1.5, 0.0, reset_dowd);

}

public int
say(string str)
{
    if (!broken && wildmatch("*lantilsi*", str))
    {
	    broken = 1;
	    set_alarm(1.5, 0.0, break_it);
		TP->add_prop("_i_summoned_dowd", 1);
    }
    return 0;
}

public void
lift_dark(void)
{

    if (!dowd)
    {
	dowd = clone_object(NPC +"dowd");
	dowd->move_living("M", TO);
	dowd->command("emote whispers in a low voice nearby.");
    }

    add_prop(ROOM_I_LIGHT, 1);
    tell_room(TO, "The shadow passes.\n");
    alarm_id = set_alarm(60.0, 0.0, reset_dowd);
}

public int
push(string str)
{
    NF(CAP(query_verb())+" what?\n");
    if (!strlen(str) || !TP->query_prop(OPR) || !CAN_SEE_IN_ROOM(TP))
	return 0;

    if (!parse_command(str, ({}),
	    "[on] / [against] [the] 'panel'"))
	return 0;

    if (alarm || alarm_id || broken || !IS_MEMBER(TP) ||
	(objectp(dowd) && present(dowd)) ||
	U_IS_PUNISHED(TP, U_PUNISHED_NOTRAIN))
	return NF("Nothing happens.\n");

    write("You place your hands against the outline, and hear "+
	"a very faint 'click' from far away.\n");
    say(QCTNAME(TP)+ " places "+ HIS(TP) +" hands against the north "+
	"wall.\n");

    add_prop(ROOM_I_LIGHT, ALWAYS_DARK);
    tell_room(TO, "An inky shadow seems to descend upon the room.\n");
    alarm = set_alarm(7.0, 0.0, lift_dark);
    return 1;
}

public void
leave_inv(object ob, object where)
{
    ::leave_inv(ob, where);
    ob->remove_prop(OPR);
}

public void
init(void)
{
    ::init();
    add_action(push, "push");
    add_action(push, "press");
    add_action(say,  "say");
    add_action(say,  "us");
    add_action(say,  "usay");
    add_action(say,  "shout");

    if (IS_MEMBER(TP))
	init_skill_raise();
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

    if (!dowd || !present(dowd))
	return 0;

    if (!IS_MEMBER(TP))
    {
	dowd->command("shake");
	set_alarm(1.0, 0.0, reset_dowd);
	return 1;
    }

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOTRAIN))
    {
	dowd->command("glare "+ TP->query_real_name());
	set_alarm(1.0, 0.0, reset_dowd);
	return 1;
    }

    if (!STATE)
    {
	dowd->command("emote cups his hands, and raises them upwards.\n");
	set_alarm(1.0, 0.0, reset_dowd);
	return 1;
    }

    if (IS_MEMBER(TP) && ENEMY(TP))
    {
	dowd->command("eyebrow .");
	set_alarm(1.0, 0.0, reset_dowd);
	return 1;
    }

    return ::sk_improve(str);
}

public void
set_up_skills(void)
{
    sk_add_train(SS_DEFENCE,
      "defend against attacks",
      0, 200,
      MAX_DEFENCE );

    sk_add_train(SS_SWAY,
      "enter the Sway",
      "sway", 200,
      MAX_SWAY );
}

public varargs int
sk_query_max(int sknum, int silent)
{
    int max;

    switch(sknum)
    {
    case SS_DEFENCE:  max = TP->query_stat(SS_DEX);          break;
    case SS_SWAY:     max = TP->query_stat(SS_WIS);          break;
    default:          max = TP->query_stat(SS_OCCUP);        break;
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
    TP->catch_msg("You fail to adopt what "+ QTNAME(dowd) +
	" attempts to teach you.\n");
    dowd->command("sigh");
    return 1;
}
