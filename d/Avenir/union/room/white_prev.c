/* One of the  training rooms for the      */
/*           Shadow Union                  */
/*           Cirion 031996                 */
/* 23 May 2004 Lilith: per Elders, raised max skill for trainees */
// 09 Sep 2001 Lilith:
// added functionality to saying Plantilsi amon Dowd
// If Dowd is present when the ineffable words are pronounced,
// he remains.  He becomes mobile and aggressive, following
// the Summoner through the halls, attacking anyone not of the 
// Union, for a limited time.
// If the words are uttered by anyone when he is not present,
// then we get the broken effect only, because he gets trapped 
// behind the panel. The force of the passion unleased is great 
// enough that it shifts the stones on their foundation.

#pragma save_binary
#pragma strict_types

inherit "/lib/skill_raise";
inherit "/std/room";

#include "../defs.h"
#include "../lib/skills.h"
#include <money.h>
#include <filter_funs.h>
#include <composite.h>

#define OPR "_live_i_seeunionwhiteoutline"

object trainer,
       rms;
int    broken,
       amon;

void reset_room();
void set_up_skills();

string 
awa_check()
{
    if(TP->query_skill(SS_AWARENESS) > 29)
    {
        TP->add_prop(OPR, 1);
        return " There seems to be a faint outline traced in the "
            +"sandstone wall to the north.";
    }
    else
    return "";
}

void 
create_room() 
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
        "north wall"}),"The walls are all made from stark white "
        +"sandstone, soft and powdery, almost luminescent.@@awa_check@@\n");
    add_item(({"ceiling","roof"}),"It, like the walls, is made from "
        +"sandstone. There seems to be something written in "
        +"the stone.\n");
    add_item(({"arch","archway"}),"It is made from black granite, "
        +"strong and wide. It is quite low, however, and leads "
        +"out into the hallway to the south.\n");
    add_item(({"hall","hallway"}),"The hallway to the south "
        +"seems to shed a greenish light through the archway, "
        +"falling on the floor and making eerie shadows that seem "
        +"to dance.\n");

    ACI(({"wall","walls","granite"}),({"touch","feel"}),
        "The sandstone walls are soft, almost powdery, and "
        +"smooth.\n");
    ACI(({"ceiling","roof","writing"}),"read","Plantilsi amon "
        +"Dowd\n");

    ANTIMAGIC;

    add_exit(HALL+"_ne2","south");

    add_prop(ROOM_I_INSIDE, 1);

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

    rms = clone_object("/std/room");
    reset_room();
}

string 
check_outl()
{
    if(TP->query_skill(SS_AWARENESS) > 30 || TP->query_prop(OPR))
    {
        TP->add_prop(OPR, 1);
        return "It is a very faint outline in the sandstone of the "
        +"north wall, like a perfectly square panel.\n";
    }
    else
    return "You see no outline.\n";
}

void 
reset_dowd()
{
    if (!amon)
    {
      trainer->command("emote seems to fade from sight, like a dream.");
      trainer->move_living("M", rms);
    }
    amon = 0;
}

void 
reset_room()
{
    if(broken)
    {
        broken = 0;
        tell_room(TO, "A rushing noise, like a wind you cannot feel, "
            +"arises in the room.\n");
    }

    if(!trainer)
    {
        trainer = clone_object(NPC+"dowd");
        trainer->arm_me();
    }

    trainer->command("wear all");
    trainer->command("wield all");
    trainer->command("emote seems to fade from sight, like a dream.");
    trainer->move_living("M", rms);
}

void 
init()
{
    ::init();
    add_action("push","push");
    add_action("push","press");
    add_action("say","say");
    add_action("say","shout");
    add_action("say","us");
    add_action("say","usay");

    init_skill_raise();
}

void 
break_it(object summoner)
{

    broken = 1;
    tell_room(TO, "The floor seems to rumble slightly, making the "
        +"walls and ceiling expel clouds of white dust.\n");
    tell_room(TO, "You hear a crash from far away!\n");
    set_alarm(4000.0, 0.0, reset_dowd);    

    if (present(trainer))
    {
        trainer->remove_object();
        reset_room();
        trainer->move_living("M", TO);
        trainer->plantilsi_amon();   
        amon = 1;
    }
}

int 
say(string str)
{
    string s1, s2;


    if(!broken && sscanf(str, "%slantilsi%s", s1, s2))
    {
        if (present(trainer))
            TP->add_prop("_i_summoned_dowd", 1);
        set_alarm(1.0, 0.0, break_it);
    }

    return 0;
}

void 
lift_dark()
{
    if(!trainer || present(trainer))
    {
        tell_room(TO, "The shadow passes.\n");
        add_prop(ROOM_I_LIGHT, 1);
        return;
    }

    trainer->move_living("M", TO);
    trainer->command("emote whispers in a low voice nearby.");
    tell_room(TO, "The shadow passes.\n");
    add_prop(ROOM_I_LIGHT, 1);
    
    set_alarm(20.0, 0.0, reset_dowd);
}

int 
push(string str)
{
    NF(CAP(QVB)+" what?\n");
    if(!strlen(str) || !TP->query_prop(OPR) || !CAN_SEE_IN_ROOM(TP))
        return 0;

    if(!parse_command(str, ({}), 
        "[on] / [against] [the] 'panel'"))
        return 0;

    if(present(trainer) || !trainer || broken ||
	!IS_MEMBER(TP) || U_IS_PUNISHED(TP, U_PUNISHED_NOTRAIN))
        return NF("Nothing happens.\n");

    write("You place your hands against the outline, and hear "
        +"a very faint 'click' from far away.\n");
    say(QCTNAME(TP)+" places "+POSSESS(TP)+" hands against the north "
        +"wall.\n");
    tell_room(TO, "An inky shadow seems to descend upon the room.\n");
    add_prop(ROOM_I_LIGHT, -1000);
    set_alarm(7.0, 0.0, lift_dark);
    return 1;
}    

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:	  str - The rest of the command player made
 * Returns:	  1/0
 */
int
sk_improve(string str)
{
  if(GUILD_CLOSED)
  {
     write("The Union has been shut down due to problems, so "
          +"training is impossible.\nTry back later.\n");
     return 1;
  }

  if(!present(trainer))
  {
    return 0;
  }

  if(!IS_MEMBER(TP))
  {
    trainer->command("shake");
    set_alarm(1.0, 0.0, reset_dowd);
    return 1;
  }

  if(U_IS_PUNISHED(TP, U_PUNISHED_NOTRAIN))
  {
    trainer->command("glare "+TP->query_real_name());
    set_alarm(1.0, 0.0, reset_dowd);
    return 1;
  }

  if(!STATE)
  {
    trainer->command("emote cups his hands, and raises them upwards.\n");
    set_alarm(1.0, 0.0, reset_dowd);
    return 1;
  }

  if(IS_MEMBER(TP) && ENEMY(TP))
  {
    trainer->command("eyebrow .");
    set_alarm(1.0, 0.0, reset_dowd);
    return 1;
  }

  return ::sk_improve(str);
}

void set_up_skills()
{
  sk_add_train(SS_DEFENCE,
               "defend against attacks", 
               0, 
               200, 
               MAX_DEFENCE );

  sk_add_train(SS_SWAY,
               "enter the Sway", 
               "sway", 
               200, 
               MAX_SWAY );

}

varargs int sk_query_max(int sknum, int silent)
{
  int  max;

  switch(sknum)
  {
    case SS_DEFENCE:  max = TP->query_stat(SS_DEX);          break;
    case SS_SWAY:     max = TP->query_stat(SS_WIS);          break;
    default:          max = TP->query_stat(SS_OCCUP);        break;
  }

  /* Players that are trainees will not be able to train very high */
  if(!TP->query_skill(OCC_LEVEL))
     max = 50;

  return MIN(max, ::sk_query_max(sknum, silent));
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 * Returns:	  0
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    TP->catch_msg("You fail to adopt what "+QTNAME(trainer)
         +" attempts to teach you.\n");
    trainer->command("sigh");
    return 1;
}


#if 0
/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:	  skill - The skill player wanted to improve
 * Returns:	  0
 */
int
sk_hook_improved_max(string skill)
{
    switch(skill)
    {
      case "defence": TP->catch_msg("You are not agile enough "
          +"to grasp what "+QTNAME(trainer)+" tries to teach you.\n");
       return 1;
       break;
      case "sway": write("You mind is not quick enough "
          +"to gain any more insight into the Sway.\n");
       return 1;
       break;
      default: write("You have not advanced far enough "
          +"in the Union to learn that far.\n");
       return 1;
       break;
    }
}

#endif
