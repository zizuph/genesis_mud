
/**  DARGAARD KEEP ROOM **/


#pragma strict_types


#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <stdproperties.h>

inherit GUILD_IN;
inherit "/lib/skill_raise";

object trainer;

void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_ELEMENT_FIRE, "cast firebased spells", "fire spells", 0, 60);
    sk_add_train(SS_ELEMENT_DEATH, "cast deathbased spells", "death spells", 0, 60);
    sk_add_train(SS_SPELLCRAFT, "cast spells", "spellcraft", 0, 60);
    sk_add_train(SS_FORM_CONJURATION, "conjure spells", "Conjuration", 0, 60);
    sk_add_train(SS_GUILD_SPECIAL_REAP, "reap the lifeforce of the living", "reap", 100, 100);

}

void
reset_dargaard_room()
{
   if(!objectp(trainer))
   {
      trainer = clone_object(GUILD_NPC + "lich");
      trainer->move(TO);
   }
}

void
create_dargaard_room()
{
    set_short("Laboratory");
    set_long("You enter an old laboratory caved into the very bedrock "+
             "of the Nightlund plains. This room is obviously not a "+
             "part of the original construction of Dargaard Keep. "+
             "Different sized glass bottles containing colourful liquids "+
             "are placed on a large table in the middle of the room. "+
             "Old scrolls and dark-blue books are lying in a pile on "+
             "the floor. The north and south walls are occupied by some "+
             "torches, casting a bright light on everything in this "+
             "room. The path to the west takes you to a gloomy "+
             "corridor.\n");

    add_exit(GUILD_ROOM + "room11","west",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    /* configure the trainer */
    set_up_skills();

    reset_dargaard_room();
}

public varargs int
sk_query_max(int snum, int silent)
{
   /* Squires can only train to level 50 in skills */
   if (!TP->test_bit("ansalon", 3, 9) &&   
       !TP->test_bit("ansalon", 3, 8) &&   
       !TP->test_bit("ansalon", 3, 7))
       return 50;

/*
    if(snum == SS_WEP_CLUB)
	if(TP->query_skill(WEAPON_SPEC_SKILL) != 1)
	    return 30;
	else
	if(TP->test_bit("ansalon", 3, 4))
	    return 100;
	else
	    return 90;

    if(snum == SS_WEP_SWORD)
	if(TP->query_skill(WEAPON_SPEC_SKILL) == 1)
	    return 30;
	else
	if(TP->test_bit("ansalon", 4, 4)) 
	    return 100;
	else
	    return 90;*/

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
 
    return ::sk_improve(sk);
}


void
init()
{
    ::init();

    /* add the trainer's commands */
    init_skill_raise();
}
