/*
 *    tree2.c  
 *
 * Training and joining room for the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */

inherit "/std/room";
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include "../defs.h"

object guild_trainer;
string gConfirm;

private static  object  guild_trainer; /* the trainer npc               */

/*
 * Function name : trainer
 * Description   : function returns the object pointer of the npc trainer
 * Arguments     : void    - no arguments
 * Returns       : object  - the trainer npc
 */
public nomask object
trainer()
{
    if (!objectp(trainer))
    {
        return (guild_trainer = present("trainer_", this_object()));
    }

    return guild_trainer;
}

int
sk_hook_no_list_improve()
{
    trainer()->command("say I have already taught you everything I know.");
    return 1;
}

void
sk_hook_write_header(int steps)
{
    if (!steps)
    {
        steps = 1;
    }
    if (query_verb() == "learn")
	    trainer()->command("say These are the skills you are able to learn here.");
	else
        trainer()->command("say These are the skills you are able to " +
		    "practice "+ LANG_WNUM(steps) + ((steps == 1) ? " step" : " steps") + " here.");
    write("  Skill:                Cost:      "+
        "Next level:           Max level:\n"+
        "--------------------------------------"+
        "--------------------------------------\n");

}

int
sk_hook_allow_train(object who, string str, string verb)
{
    if (!objectp(trainer()))
    {
        write("There is noone here to teach you.\n");
        return 0;
    }

    if (!IS_MEMBER(this_player()) && !this_player()->query_wiz_level())
    {
        trainer()->command("say The knowledge I offer is for members of "+
		   "the Amazons only.");
        return 0;
    }

    return 1;
}

int
sk_hook_unknown_skill(string skill, string verb)
{
    trainer()->command("say What '" + skill + "' are you talking about?");
    return 1;
}

public int
sk_hook_improved_max(string skill)
{
    trainer()->command("say I cannot teach you any further, in this" +
      " skill, seek knowledge in other places.");
    return 1;
}

public int
sk_hook_cant_train(string skill, int level)
{
    int number = sk_find_skill(skill);

    this_player()->catch_tell(trainer()->query_The_name(this_player())  +
      " tries to teach you to " + sk_tdesc[number][0] + ", but"     +
      " you fail to adopt it.\n");

    say(QCTNAME(trainer()) + " tries to teach " + QTNAME(this_player()) +
      " to " + sk_tdesc[number][1] + ", but "                     +
      this_player()->query_pronoun() + " fails to adopt it.\n");

    return 1;
}

public int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    trainer()->command("say And what do you plan to pay with?");
    trainer()->command("grumble");
    return 1;
}

int
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank = sk_rank(to_lev);

    this_player()->catch_tell(trainer()->query_The_name(this_player())   +
      " teaches you to " + sk_tdesc[snum][0] + " to the rank of "   +
      rank + ".\n");

    say(QCTNAME(trainer()) + " taught " + QTNAME(this_player()) + " to "+
      sk_tdesc[snum][1] + " to the rank of " + rank + ".\n");

    return 1;
}

/*
 * === initiating functions ==============================================
 * =============================================================== *** ===
 */

public void
initiate_practice()
{
    sk_add_train(SS_DEFENCE, ({"defend yourself", "defend "+HIM(TP)+"self"}), "defence", 0, 30);
    sk_add_train(SS_WEP_MISSILE, ({"use the bow and arrow", "use the bow and arrow"}), "missiles", 0, 40);
    sk_add_train(SS_WEP_POLEARM, ({"stab with a spear", "stab with a spear"}), "polearm", 0, 50);    
    sk_add_train(SS_TRACKING, ({"search for tracks", "search for tracks"}), "tracking", 0, 30);
    sk_add_train(SS_HUNTING, ({"hunt for food", "hunt for food"}), "hunting", 0, 30);
    sk_add_train(SS_AWARENESS, ({"be more aware of your surroundings", "be more aware of "+
                                HIS(TP)+ "surroundings"}), "awareness", 0, 40);
    sk_add_train(SS_ANI_HANDL, ({"handle animals", "handle animals"}), "animal handling", 0, 30);
    sk_add_train(SS_LOC_SENSE, ({"locate your surrounding", "locate "+HIS(TP)+" surrounding"}), "location sense", 0, 30);
    sk_add_train(SS_CLIMB, ({"climb trees", "climb trees"}), "climb", 0, 40);
    sk_add_train(SS_APPR_MON, ({"appraise enemies", "appraise enemies"}), "appraise enemy", 0, 30);
}

void
reset_room()
{
    if (!objectp(guild_trainer))
    {
        guild_trainer = clone_object(NPC + "trainer");
        guild_trainer->move(this_object());
    }
}

public void
create_room()
{
    set_short("In the north part of a camouflaged treehouse");
    set_long("In the north part of a camouflaged treehouse. Here, "+
      "in this part of the tree the warriors and trainees come "+
      "to train all the skills needed to survive in the wilderness "+
      "as an Amazon. Going south will take you directly to the "+
      "center of the treehouse and southwest will take you to the big "+
      "board, used to place notes on. A small plaque has been nailed "+
      "to the wall here.\n");
      
    add_item(({"plaque","small plaque"}), "It got some writing, you "+
      "should try reading it.\n");
    add_item(({"treehouse","treetop","hut"}), "This fairly large treehouse "+
      "has been constructed in what seems to be one of the largest trees "+
      "in the whole forest. It can easily hold a large group of people.\n");
    add_item(({"wall","walls"}), "The walls are made from branches, "+
      "twined together, forming a wall. In some places it has been "+
      "reinforced by some planks, making it sturdy.\n");
    add_item(({"board", "big board"}), "It is the board the Amazons "+
      "use to communicate with eachother.\n");
    add_item("amazon warrior", "She is training some younger womens "+
      "in the art of spearing.\n");

	add_cmd_item(({"plaque","small plaque"}),
        "read","@@read_sign");

    add_exit(ROOMS + "tree3","south");
    add_exit(ROOMS + "tree4","southwest");
	
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();

	create_guild_support(); 
    create_skill_raise();
    initiate_practice();
}

int
read_sign()
{     
    write(" ------------------------------------- \n"+
          "|                                     |\n"+
          "| Here, Amazons may train some of the |\n"+
          "| skills needed to survive the rough  |\n"+
          "| and sometimes tough challenge of    |\n"+
          "| living as an Amazon. It is also     |\n"+
          "| possible to 'obtain' a new token    |\n"+
          "| here, if you lost yours.            |\n"+
          " ------------------------------------- \n");
    return 1;
}

int
can_npc_see(object npc, object player)
{
	if (CAN_SEE(npc, player) && CAN_SEE_IN_ROOM(npc))
		return 1;
	return 0;
}

int
leave_guild(string str)
{
    object token, who = this_player();

    if (!strlen(str) || !parse_command(lower_case(str), ({}), 
	"[from] [the] [amazon] [guild]"))
    {
	    notify_fail("Depart from guild?\n");
	    return 0;
    }
    else if (!objectp(trainer()))
    {
	    notify_fail("Azealia is not here to release you.\n");
	    return 0;
    }
	else if (!can_npc_see(trainer(), TP))
	{
	    trainer()->command("say What?! Who's there!");  
		return 1;
	}
    else if (!IS_MEMBER(who))
    {
	trainer()->command("smile thought");
	trainer()->command("say to "+who->query_name()+" How do you suppose "+
		"you're going to leave if you haven't even joined yet?");
	return 1;
    }
    else if (gConfirm != who->query_real_name())
    {
	trainer()->command("say to "+who->query_name()+" Are you sure you want "+
		"to leave the guild? Try again if you're sure.");
	gConfirm = who->query_real_name();
	return 1;
    }
    
    trainer()->command("say Ok.");
    say(QCTNAME(who) + " leaves the guild.\n");
    who->leave_amazons("You left the guild.\n");
    return 1;
}

int
join_guild(string str)
{
    int ret;
    string reason;
    object token, shadow, who = this_player();

    if (!strlen(str) || (!parse_command(lower_case(str), ({}),
	  "[myself] [with] [the] [amazons] / [amazon] [guild]")))
    {
	    notify_fail("Affiliate yourself with the amazons?\n");
	    return 0;
    }
    else if (!objectp(trainer()))
    {
	    notify_fail("Azealia is not here to let you in.\n");
	    return 0;
    }
	else if (!can_npc_see(trainer(), TP))
	{
	    trainer()->command("say What?! Who's there!");  
		return 1;
	}
	
#ifdef NOT_ACCEPTING_NEW_MEMBERS
      trainer()->command("say to "+who->query_name()+" We do currently not recruit new members. "+
	     "Come back another day!");
	 return 1;  
#endif
	
    if (IS_MEMBER(who))
    {
	trainer()->command("say to "+who->query_name()+" You are already an Amazon!");
	return 1;
    }
    else if (who->query_guild_member("race"))
    {
	trainer()->command("say to "+who->query_name()+" You already have a racial guild!");
	return 1;
    }
    else if (who->query_wiz_level())
    {
	write("Wizards must add the shadow and soul to themselves.\n");
	return 1;
    }

    shadow = clone_object(SHADOW);
    ret = shadow->shadow_me(who, "race", STYLE, GUILD_NAME);
    
    switch(ret)
            {
            case 1:
	    /* The player has been successfully shadowed. */
	    
            trainer()->command("say to "+who->query_name()+" Ok, you "+
	       "seem to be of the right material.\n");
	    
	    
	    set_alarm(0.5, 0.0, &who->catch_msg(QCTNAME(trainer())+" draws a sharp dagger "+
	    "from her belt.\n"));
	    set_alarm(1.5, 0.0, &who->catch_msg(QCTNAME(trainer())+" quickly brings the "+
	    "dagger over the palm of her hand, cutting a small wound.\n"));
	    set_alarm(2.5, 0.0, &who->catch_msg(QCTNAME(trainer())+" then gets a hold of "+
	    "your hand, cutting a small wound in your palm.. Ouch.\n"));
	    set_alarm(3.5, 0.0, &write("Reciting a sacred oath of blood she "+
	      "grasps your hand with hers, welcoming you to the blood.\n"));
	      
	    set_alarm(0.5, 0.0, &say(QCTNAME(trainer())+" draws a sharp dagger "+
	    "from her belt.\n", who));
	    set_alarm(1.5, 0.0, &say(QCTNAME(trainer())+" quickly brings the "+
	    "dagger over the palm of her hand, cutting a small wound.\n", who));
	    set_alarm(2.5, 0.0, &say(QCTNAME(trainer())+" then gets a hold of "+
	    QTPNAME(who)+" hand, cutting a small wound in "+HIS(who)+" palm.. Ouch.\n", who));
	    set_alarm(3.5, 0.0, &say("Reciting a sacred oath of blood she "+
	      "grasps "+QTPNAME(who)+" hand with hers, Welcoming "+HIS(who)+" to the blood.\n", who));				
				
				
            SERVER->add_member(who->query_real_name());
	    who->add_cmdsoul(SOUL);
	    who->update_hooks();
	    LOGFILE("join_leave", capitalize(who->query_real_name())+
              " joined the guild.\n");
	    return 1;
            case -4:
	    /* The player has a racial guild already, or */
	    /* one of his existing guilds has blocked this one. */
	    trainer()->command("say to "+who->query_name()+" Your other "+
	      "guild affiliations prohibit you "+
	      "from joining this one!");
	    return 1;
            default:
	    /* Shadowing error */
	    trainer()->command("say to "+who->query_name()+" You were unable "+
	      "to join the Amazon guild due to problems beyond your "+
	      "control. Contact the guildmaster or make a bug report.");
	    return 1;
            }
    
    /* We couldn't shadow the player, so remove the shadow. */
    shadow->remove_shadow();
    LOGFILE("join_leave", capitalize(who->query_real_name())+
      " tried to join the guild, but failed.\n");
    return 1;
}

int
obtain_item(string str)
{
    object token;

    if (!strlen(str) || (!parse_command(lower_case(str), ({}),
	  " [a] [new] [guild] 'item' / 'token' ")))
    {
	    notify_fail("Obtain what? A new token?\n");
	    return 0;
    }
    else if (!objectp(trainer()))
    {
	    notify_fail("Azealia is not here to help you.\n");
	    return 0;
    }
	else if (!can_npc_see(trainer(), TP))
	{
	    trainer()->command("say What?! Who's there!");  
		return 1;
	}
    else if (!IS_MEMBER(TP))
    {
	trainer()->command("say You can't have a token, you are not "+
	  "an Amazon!");
	return 1;
    }
    else if (present("amazon_race_token", TP))
    {
	trainer()->command("say You already have a token!");
	return 1;
    }

    token = clone_object(OBJ+"token");
    token->move(TP, 1);
    TP->catch_msg(QCTNAME(trainer()) + " gives you a token.\n");
    say(QCTNAME(trainer()) + " gives " + QTNAME(TP) + " a token.\n");
    return 1;
}

void
leave_inv(object ob, mixed to)
{
   ::leave_inv(ob, to);
   gs_leave_inv(ob, to);
}

void
init()
{
    ::init();
	add_action(leave_guild, "depart");
    add_action(join_guild, "affiliate");
    add_action(obtain_item, "obtain");
    init_skill_raise();
	init_guild_support();
}
