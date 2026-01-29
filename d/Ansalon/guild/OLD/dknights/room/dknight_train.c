/*
 * File Name        : dknight_training.c
 * By               : Elmore.
 * From             : Neidar Clan, training room by Arman.
 * Date             : Nov. 2000.
 * Description      : The training room of the pirates.
 *                    I might add an npc that teaches them
 *                    the skills.
 *
 */

#pragma strict_types


#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <stdproperties.h>

inherit GUILD_IN;
inherit "/lib/skill_raise";

#define CHANGE_CHOICE "_want_to_change_death_kight_weapon"

object trainer;

void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 70);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 90);
    sk_add_train(SS_PARRY, "parry attacks", "parry", 0, 90);
    sk_add_train(SS_WEP_SWORD, "fight with a sword", "sword", 0, 90);
    sk_add_train(SS_WEP_CLUB, "fight with a club", "club", 0, 90);
    sk_add_train(SS_APPR_MON, "consider enemies", "appraise monster", 0, 60);
    sk_add_train(SS_2H_COMBAT,  "fight with two weapons",0, 0, 85 );
    sk_add_train(SS_GUILD_SPECIAL_DASSAULT, "assault enemies", "assault", 100, 100);

}


void
reset_guild_room()
{
   if(!objectp(trainer))
   {
      trainer = clone_object(GUILD_NPC + "mordlust");
      trainer->move(TO);
   }
}


void
create_room()
{
    set_short("Weapon training room");
    set_long("As you enter this room you can't help to notice all "+
             "the various peaces of weaponry that decorate the walls. "+
             "A small fighting arena has been constructed in the "+
             "center of the room, allowing the followers of Lord Soth "+
             "to train their various weapon skills. The path to the west "+
             "takes you back to the gloomy hallway.\n");

    add_exit(GUILD_ROOM + "room9","west",0);


    /* configure the trainer */
    set_up_skills();
    reset_guild_room();
}


int
can_train_this_skill(object who, string skill, int step)
{
    int allow, s = sk_find_skill(skill);

    if(step < 0) return 1;

    if(s == SS_WEP_CLUB)
    {
	if(who->query_base_skill(SS_WEP_CLUB) + step <= 30)
	    return 1;
	if(who->query_skill(WEAPON_SPEC_SKILL) == 1)
	    return 1;
	notify_fail("You cannot train any higher at the moment!\n");
	return 0;
    }

    if(s == SS_WEP_SWORD)
    {
	if(who->query_base_skill(SS_WEP_AXE) + step <= 30)
	    return 1;
	if(who->query_skill(WEAPON_SPEC_SKILL) != 1)
	    return 1;
	notify_fail("You have chosen club as your primary weapon!\n" +
	  "It is impossible to train your skill in sword any higher.\n");
	return 0;
    }
    return 1;
}

public varargs int
sk_query_max(int snum, int silent)
{
   /* Squires can only train to level 50 in skills */
   if (!TP->test_bit("ansalon", 3, 9) &&   
       !TP->test_bit("ansalon", 3, 8) &&   
       !TP->test_bit("ansalon", 3, 7))
       return 50;

    if(snum == SS_WEP_CLUB)
	if(TP->query_skill(WEAPON_SPEC_SKILL) != 1)
	    return 30;
	else
	if(TP->test_bit("ansalon", 3, 4)) /* Guru quest */
	    return 100;
	else
	    return 90;

    if(snum == SS_WEP_SWORD)
	if(TP->query_skill(WEAPON_SPEC_SKILL) == 1)
	    return 30;
	else
	if(TP->test_bit("ansalon", 3, 12)) /* Guru quest */
	    return 100;
	else
	    return 90;

    return ::sk_query_max(snum, silent);
}


public int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;

    if (!sk || sscanf(sk, "%d", steps))
    {
	if (!TP->query_guild_member(GUILD_NAME))
	{
	    write("Only a Death Knight may train here.\n");
	    return 1;
	}
	return sk_list(steps);
    }


    tmp = explode(sk, " ");
    if(sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1)
	skill = implode(tmp[0 .. sizeof(tmp) -2], " ");
    else
    {
	skill = sk;
	steps = 1;
    }

    if(!(present("trainer",TO)))
    {
	write("Without a trainer, you are unable to improve " +
	  "your skills to any extent.\n");
	return 1;
    }
    if(!TP->query_guild_member(GUILD_NAME))
    {
	write("Only a Death Knight may train here.\n");
	return 1;
    }
    if(can_train_this_skill(TP, skill, steps))
	return ::sk_improve(sk);
}

int
train(string str)
{

    if(TP->query_guild_name_occ() != GUILD_NAME)
    {
	notify_fail("Only a Death Knight may train here.\n");
	return 0;
    }
    if(!str)
    {
	notify_fail("Train what? Sword or club?\n");
	return 0;
    }

    if(str != "sword" && str != "club")
    {
	notify_fail("You can only choose sword or " +
	  "club to train in.\n");
	return 0;
    }

    if(!TP->test_bit("ansalon", 3, 9) &&
       !TP->test_bit("ansalon", 3, 8) &&
       !TP->test_bit("ansalon", 3, 7))
    {
	notify_fail("Only experienced death knights may train a different "+
                    "weapon style.\n");
	return 0;
    }

    if(!TP->query_prop(CHANGE_CHOICE))
    {
	write("Are you sure you want to change your preferences? " +
	  "Doing so will remove your other weapon skill. If so, " +
	  "repeat your last command.\n");
	TP->add_prop(CHANGE_CHOICE, 1);
	return 1;
    }

    if(str == "sword")
    {
	if(TP->query_skill(WEAPON_SPEC_SKILL) == 0)
	{
	    notify_fail("You are already specializing in sword!\n");
	    return 0;
	}
	write("You now specialize in wielding a sword!\n");
	TP->set_skill(WEAPON_SPEC_SKILL, 0);
	TP->remove_skill(SS_WEP_CLUB);
	return 1;
    }
    if(str == "club")
    {
	if(TP->query_skill(WEAPON_SPEC_SKILL) == 1)
	{
	    notify_fail("You are already specializing in club!\n");
	    return 0;
	}
	write("You now specialize in swinging a club!\n");
	TP->set_skill(WEAPON_SPEC_SKILL, 1);
	TP->remove_skill(SS_WEP_SWORD);
	return 1;
    }
    return 1;
}

void
init()
{
    ::init();

    ADA("train");
    /* add the trainer's commands */
    init_skill_raise();
}
