/*
 *   Staff of Magius
 *   _______________
 *
 *   current owner: Kentari
 *   created: 2/97
 */

inherit "/std/weapon.c";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
	set_name("staff");
	set_pname("staffs");
	set_adj(({ "magius", "plain"}));
	set_short("Staff of Magius");
	set_pshort("Staffs of Magius");
	set_long("This is a plain wooden staff with a ball of bright " +
		"crystal, clutched in a disembodied golden claw carved " +
		"to resemble the talon of a dragon, gleaming at the top. " +
		"As the original staff used by Magius, it has much power " +
		"and mystery contained within it, though its secrets and " +
		"its use are allowed only to its current owner, who isn't " +
		"always the one possessing it. Be warned, for this " +
		"artifact is ancient in nature and will protect itself " +
		"from harm.\n");

	set_default_weapon(28, 25, W_POLEARM, W_BLUDGEON, W_ANYH);
	update_prop_settings();
	set_wf(TO);
	add_prop(MAGIC_AM_MAGIC,({100,"enchantment"}));
	add_prop(OBJ_M_NO_BUY, 1);
        add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	add_prop(OBJ_I_VOLUME, 7500);
	add_prop(OBJ_I_WEIGHT, 7500);
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28, 25) + 2500);
}

mixed
wield(object what)
{
   if(TP->query_name() == "Kentari")
	{
	write("You comfortably grasp the staff, secure in the knowledge " +
		"of its power.\n");
	say(QCTNAME(TP) + " comfortably grasps the Staff of Magius, " +
		"secure in the knowledge of its power.\n");
	return 0;
	}
   write("As you grasp the Staff of Magius, it feels very uncomfortable and falls " +
		"out of your hands. Apparently, only its current owner may " +
		"use the staff and its benfits.\n");
   say(QCTNAME(TP) + " fumbles with the Staff of Magius, trying to use " +
		"it, but to no avail.\n");
   TP->heal_hp(-50);
   TP->command("drop staff");
   return "Your hand is numb where you touched the Staff.\n";
}

init()
{
   ::init();
   add_action("command","command");
}

command(s)
{
   if(!query_wielded(TO))
	{
	write("You must be grasping the Staff of Magius first.\n");
	return "You feel the need to be grasping it";
	}
   NF(query_verb() + " what?\n");

   if(!s)
	return 0;
   if(query_verb() == "command")
	switch (s)
	 {  
	 case "shirak":
	  write("You give the word of command 'Shirak' and the " +
		"crystal atop your staff begins to glow.\n");
	  say(QCTNAME(TP) + " gives the word of command 'Shirak' and " +
		"the crystal atop "+HIS(TP)+" staff begins to glow.\n");
	  add_prop(OBJ_I_LIGHT, 1);
	  return 1;
	  break;
	 case "shirak!":
	  write("You bark the word of command 'Shirak' with such " +
		"authority that the crystal atop your staff flares " +
		"into life, casting bright light all around.\n");
	  say(QCTNAME(TP) + " gives the word of command 'Shirak' with " +
		"such authority that the crystal atop "+HIS(TP)+" staff " +
		"flares into life, casting bright light all around.\n");
	  add_prop(OBJ_I_LIGHT, 3);
	  return 1;
	  break;
	 case "dumak":
	  write("You give the counter-command of 'Dumak' and the " +
		"light from the crystal atop your staff fades away.\n");
	  say(QCTNAME(TP) + " gives the counter-command 'Dumak' and the " +
		"light from the crystal atop "+HIS(TP)+" staff fades " +
		"away.\n");
	  add_prop(OBJ_I_LIGHT, 0);
	  return 1;
	  break;
	 default:
	  write("You attempt a word of command but nothing happens.\n");
	  return 1;
	  break;
	}
}
