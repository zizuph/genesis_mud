/* A simple guild trainer */
/* Fixed a runtime error in sk_improve -- 980902 Ashlar */
/* 26.09.2003 - added 15 skill levels in appraise enemy - Blizzard */

#pragma strict_types

/* Base file for skill trainers */
inherit "/lib/skill_raise";

#include "guild.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/d/Ansalon/estwilde/std/dwarf_out.c";

#include "/d/Ansalon/estwilde/iron_delving/river_drink.h"

#define CHANGE_CHOICE "_want_to_change_clan_weapon"

object trainer;

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();

    sk_add_train(SS_TRADING, "make deals", "trading", 0, 75);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 90);
    sk_add_train(SS_PARRY, "parry attacks", "parry", 0, 60);
    sk_add_train(SS_BLIND_COMBAT, "fight while blind",
      "blindfighting", 0, 60);
    sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 75);
    sk_add_train(SS_APPR_VAL, "value objects", "appraise value", 0, 60);
    sk_add_train(SS_APPR_OBJ, "appraise objects", "appraise object", 0, 60);
    sk_add_train(SS_WEP_AXE, "fight with an axe", "axe", 0, 100);
    sk_add_train(SS_WEP_CLUB, "fight with a hammer", "club", 0, 100);
    sk_add_train(SS_GUILD_SPECIAL_SKILL, "chop enemies with an axe " +
      "and crush foes with a hammer", "chop and crush", 80, 100);
    sk_add_train(SLAM_SPECIAL_SKILL,"take hits while in a dwarven battlerage",
      "battleraging", 80, 100);
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

    if(s == SS_WEP_AXE)
    {
	if(who->query_base_skill(SS_WEP_AXE) + step <= 30)
	    return 1;
	if(who->query_skill(WEAPON_SPEC_SKILL) != 1)
	    return 1;
	notify_fail("You have chosen club as your primary weapon! " +
	  "You cannot train any higher in axe.\n");
	return 0;
    }
    return 1;
}

public varargs int
sk_query_max(int snum, int silent)
{

    if(snum == SS_WEP_CLUB)
	if(this_player()->query_skill(WEAPON_SPEC_SKILL) != 1)
	    return 30;
	else
	if(TP->test_bit("ansalon", 3, 5)) /* Guru quest */
	    return 100;
	else
	    return 90;
    if(snum == SS_WEP_AXE)
	if(this_player()->query_skill(WEAPON_SPEC_SKILL) == 1)
	    return 30;
	else
	if(TP->test_bit("ansalon", 3, 5)) /* Guru quest */
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
	if (!TP->query_guild_member("Dwarven Warriors of the Neidar Clan"))
	{
	    write("Only Clan members may train here.\n");
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
    if(!TP->query_guild_member("Dwarven Warriors of the Neidar Clan"))
    {
	write("Only Clan members may train here.\n");
	return 1;
    }
    if(can_train_this_skill(this_player(), skill, steps))
	return ::sk_improve(sk);
}

void
reset_dwarf_room()
{
    if(!objectp(trainer))
    {
	trainer = clone_object("/d/Ansalon/estwilde/living/trainer");
	trainer->arm_me();
	trainer->move(TO);
    }
}

void
create_dwarf_room()
{
    set_short("In a clearing at the base of a steep hill");
    set_long("You stand at the base of a steep, barren hill " +
      "in a clearing set aside by the dwarves of Iron Delving " +
      "to train their skills. A bubbling stream flows out of " +
      "a great rent in the face of the hillside to your northwest.\n");

    add_item(({"steep hill","hill","barren hill","hillside","rent",
	"great rent"}),
      "You stand at the base of a steep and barren hill. It is so " +
      "steep you doubt you could climb it even with climbing " +
      "equipment. A great rent in the face of the hillside to your " +
      "northwest reminds you of a nasty wound in the side of " +
      "the hill face, while a bubbling stream rushes out of it, " +
      "running down to the southwest.\n");
    add_item(({"bubbling stream","stream"}),
      "A bubbling stream flows out of a rent in the hillside.\n");
    add_item("clearing",
      "You stand in a clearing set aside for the training of Clan members. " +
      "If a clan member, you may <improve> or <learn> new " +
      "skills. If you are a clan warrior, you may choose to " +
      "<train> a different weapon specialization.\n");

    add_exit("/d/Ansalon/estwilde/iron_delving/r9","southwest",0);
    add_cmd_item(({"stream","from stream","water"}),"drink","@@drink_water");

    /* configure the trainer */
    set_up_skills();
    reset_dwarf_room();
}

int
train(string str)
{

    if(this_player()->query_guild_name_occ() != GUILD_NAME)
    {
	notify_fail("Only Clan Warriors can train here.\n");
	return 0;
    }
    if(!str)
    {
	notify_fail("Train what? Axe or club?\n");
	return 0;
    }

    if(str != "axe" && str != "club")
    {
	notify_fail("You can only choose axe or " +
	  "club to train in.\n");
	return 0;
    }

    if(this_player()->query_stat(SS_OCCUP) < 56)
    {
	notify_fail("Only Warriors in the clan may have the " +
	  "options of training in club rather than axe.\n");
	return 0;
    }

    if(!this_player()->query_prop(CHANGE_CHOICE))
    {
	write("Are you sure you want to change your preferences? " +
	  "Doing so will remove your other weapon skill. If so, " +
	  "repeat your last command.\n");
	this_player()->add_prop(CHANGE_CHOICE, 1);
	return 1;
    }

    int neidar_skill_change = 30;

    if(str == "axe")
    {
        if(this_player()->query_guild_name_race() == "Rockfriend guild")
          neidar_skill_change = 50;

	if(this_player()->query_skill(WEAPON_SPEC_SKILL) == 0)
	{
	    notify_fail("You are already specializing in axe!\n");
	    return 0;
	}
	write("You now specialize in swinging an axe!\n");
	this_player()->set_skill(WEAPON_SPEC_SKILL, 0);
	this_player()->set_skill(SS_WEP_CLUB, neidar_skill_change);
	return 1;
    }
    if(str == "club")
    {
	if(this_player()->query_skill(WEAPON_SPEC_SKILL) == 1)
	{
	    notify_fail("You are already specializing in club!\n");
	    return 0;
	}

        if(this_player()->query_guild_name_race() == "Rockfriend guild")
          neidar_skill_change = 50;

	write("You now specialize in swinging a club!\n");
	this_player()->set_skill(WEAPON_SPEC_SKILL, 1);
	this_player()->set_skill(SS_WEP_AXE, neidar_skill_change);
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
