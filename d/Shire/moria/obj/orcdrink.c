/*  -*- LPC -*-  */
//
// orcdrink.c
//
// The orc's usually bring with them amounts of a bitter drink which
// gives them means of healing. They can drink some of it to gain
// hit points, however - it will drop their concentration for a while
// thus removing some mana.
//
// Sir Rogon.
//
//   Replaced the IM_TELL_FILE functions  -Igneous- Dec 5th 96
//
// Recoded to take into account the orc racial guild. The affects will
// be the same for orc racial is it would be for a goblin. Doubt it was
// ever intended to give a player orc 350 hp ;)
// Altrus, June 2005

#include "defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <poison_types.h>

inherit "/std/drink";

#define MANA_DROP_OTHER 200
#define HEAL_OTHER      30

#define MANA_DROP_ORC   100
#define HEAL_ORC        350

create_drink()
{
    set_soft_amount(330);// A small bottle containing 0.33l.
    set_name("bottle");
    add_name(({"_tarin_tar_", "liquid", "water", "orc-water", "yummy", "drink"}));
    set_pname(({"bottles", "liquids", "orc-waters"}));
    add_adj(({"black", "smelling", "orc", "orcish"}));
    set_short("bottle of a bad smelling black liquid");
    set_pshort("bottles of a bad smelling black liquid");
    set_long("This is a bottle of a bad smelling black liquid.\n"+
      "Smelling it, you almost vomit on spot, and you sure "+
      "would not like to drink it. It looks like orc-water.\n");
    add_prop(OBJ_I_VALUE,  10+random(10));
    add_prop(OBJ_M_NO_SELL,0);

}

public void 
special_effect(int num)
{
    object poison, *poisons = ({});
    string race;
    int i;

    race = TP->query_race_name();

    if ((race != "orc") && (race != "troll"))
    {
	i = -1;
	while (++i < num)
	{
	    if (race != "goblin" || TP->query_mana() < MANA_DROP_OTHER)
	    {
		//   FIXEUID add by Igneous
		FIXEUID;
		poison = clone_object("/std/poison_effect");
		poison -> set_interval(20);
		poison -> set_time(500);
		poison -> set_damage(({POISON_FATIGUE, 100, POISON_HP, 30}));
		poison -> set_poison_type("orc drink");
		poison -> move(TP, 1);
		poisons += ({ poison });
		TP->add_mana(-MANA_DROP_OTHER);
	    }
	    else
	    {
		TP->add_mana(-MANA_DROP_OTHER);
		TP->heal_hp(HEAL_OTHER);
	    }
	}
	if (sizeof(poisons)) {
	    write("You feel your belly revolt! You have been poisoned!\n");
	    say(QCTNAME(TP) + " breathes heavily realizing that " + 
	      HE_SHE(TP) + " has been poisoned!\n");
	    poisons -> start_poison();
	}
    }
    else
    {
	if(TP->query_guild_name_race() == "Orcs of Middle Earth")
	{
		TP->add_mana(-MANA_DROP_OTHER);
		TP->heal_hp(HEAL_OTHER);
	}
	
	else
	{
		TP->add_mana(-num*MANA_DROP_ORC);
		TP->heal_hp(num*HEAL_ORC);
	}
    }
}
