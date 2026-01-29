/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";
#include <macros.h>
#include <ss_types.h>
#include <money.h>

#define FOUND_HOB_CHEST			"_i_found_pal_hob_chest"
#define FOUND_HOB_CHEST_TRAP	"_i_found_pal_hob_chest_trap"

inherit CAVE_BASE

int chesthere = 0, chesttrap = 0;
object rdog, hob, hob2, hob3;

// Prototypes
int spring_trap(object victim);

void
reset_vin_mount_room()
{
	if (!hob)
	{
		hob = clone_object(LIV + "vmhobgoblin_cmdr");
		hob->move(TO);
	}

	if (!hob2)
	{
		hob2 = clone_object(LIV + "vmhobgoblin_low");
		hob2->move(TO);
	}

	if (!hob3)
	{
		hob3 = clone_object(LIV + "vmhobgoblin_low");
		hob3->move(TO);
	}

	if (!rdog)
	{
		rdog = clone_object(LIV + "rockdog");
		rdog->set_monster_home(CAVE + "cave19");
		rdog->set_restrain_path(CAVE);
		rdog->set_random_move(80);
		rdog->move(TO);
	}

	if (random(3) == 1)
	{
		chesthere = 0;
		chesttrap = 0;
	}
}

void
create_vin_mount_room() 
{
	SHORT("Chiseled passageway");
	LONG("This three by three meter passage has been mined several meters "
	+ "west to a rough chiseled dead end.  The floor is covered in straw, "
	+ "dead leaves, and topped with a patchwork cotton blanket.  Holding "
	+ "the blanket down in the northwest corner is an old wooden stump.  "
	+ "A large natural cavern opens to the east.\n");

	ITEM(({"wall", "walls", "floor", "ground", "ceiling"}), "The walls of "
	+ "this mostly straight passage have been chiseled and mined out.\n");
	ITEM(({"stalactite", "stalactites", "stalagmite", "stalagmites",
	"formation", "formations", "pillar", "pillars"}), "Unlike the rest of "
	+ "this cave system, this passage does not bear such a feature.\n");
	ITEM(({"straw", "leaf", "leaves", "dead leaves"}), "The floor has been "
	+ "matted with a layer of straw and dead leaves, and topped with a "
	+ "patchwork cotton blanket.  Judging by the weight that must have "
	+ "pressed down upon it, you suspect it has been used as bedding for "
	+ "something large.\n");
	ITEM("blanket", "Crudely sewn together with large patches of cotton, "
	+ "the blanket covers a layer of straw and dead leaves to form "
	+ "bedding.  It is held down in the northwest corner by an old wooden "
	+ "stump.\n");
	ITEM("stump", "Old and somewhat damp, this half meter long stump of a "
	+ "mountain pine leans against the wall in the northwest corner and "
	+ "holds down the patchwork blanket covering the mat of straw and "
	+ "dead leaves upon the floor." + "@@stump_search");
	ITEM("chest", "@@chest_search");
	ITEM("shaft", "@@exa_shaft");
	ITEM("trap", "@@exa_trap");

	DARK;

	CMD("chest", "open", "@@chest_open");

	EXIT(CAVE + "cave18", "east", 0, 0);

	reset_vin_mount_room();
}

void 
init()
{
    ::init();
	ADD("disarm_chest", "disarm");
	ADD("pick_chest", "pick");
}

string
stump_search()
{
	string cfound = "  There is a small chest jammed into the hollow of the "
	+ "stump.\n";

	if (TP->query_prop(FOUND_HOB_CHEST) == 1)
		return cfound;

	if (chesthere == 0 && TP->query_skill(SS_AWARENESS) > 20 + random(10))
	{
		TP->add_prop(FOUND_HOB_CHEST, 1);
		return cfound;
	}

	return "\n";
}

string
chest_search()
{
	string chestdesc = "The chest is yellow poplar bound with thick, green "
		+ "vines and is jammed snugly into the hollow of the stump with its "
		+ "lid facing you.  ";

	if (TP->query_prop(FOUND_HOB_CHEST) != 1)
		return "You find no chest.\n";

	if (chesthere == 1)
		return chestdesc + "It has been unlocked and is empty.\n";

	if (chesttrap == 0 && TP->query_prop(FOUND_HOB_CHEST_TRAP) == 1)
		return chestdesc + "It is latched shut and locked.  You notice a "
		+ "strange shaft jammed beside it pointing up where your hand "
		+ "would reach in to release the latch.\nThe chest is trapped!\n";
	
	if (chesttrap == 0 && TP->query_skill(SS_FR_TRAP) >= 20 + random(10))
	{
		TP->add_prop(FOUND_HOB_CHEST_TRAP, 1);
		return chestdesc + "It is latched shut and locked.  You notice a "
		+ "strange shaft jammed beside it pointing up where your hand "
		+ "would reach in to release the latch.\nThe chest is trapped!\n";
	}

	return chestdesc + "It is latched shut and locked.\n";
}

int
disarm_chest(string str)
{
	NF("What?\n");
	if (TP->query_prop(FOUND_HOB_CHEST_TRAP) != 1)
		return 0;

	if (!str && TP->query_prop(FOUND_HOB_CHEST_TRAP) != 1)
		return 0;

	if(!str && TP->query_prop(FOUND_HOB_CHEST_TRAP))
	{
	  NF("Disarm what?\n");
	  return 0;
	}

	NF("Disarm what?\n");
	if (!parse_command(str, ({}), "[the] 'trap' / 'chest'"))
		return 0;
	
	if (chesttrap == 1)
	{
		write("The trap on the chest has already been disarmed.\n");
		return 1;
	}

	if (chesttrap == 0 && TP->query_skill(SS_FR_TRAP) > 20 + random(10))
	{
		chesttrap = 1;
		write("You re-attach a string from the shaft to the latch to a knob "
		+ "on the stump instead.  You are confident you've disabled the "
		+ "trap... for a while.\n");
		return 1;
	}

	spring_trap(TP);
	return 1;
}

int
spring_trap(object victim)
{
	int dmg = -200 - random(101);

	write("You hear a \"Slitch\"... \"SHOOP!\"  ...as a thick spear tip "
	+ "juts out from a shaft beside the chest's latch impaling you!\n");
	say("You hear a sick shooping noise from inside the wooden stump as "
	+ QTNAME(TP) + " sticks " + HIS(TP) + " hand inside gropingly.\n");

	victim->heal_hp(dmg);

	if (victim->query_hp() <= 0)
		victim->do_die(E(victim));
}

int
pick_chest(string str)
{
	if (!str)
		return 0;

	if (TP->query_prop(FOUND_HOB_CHEST) != 1)
		return 0;

	if (!parse_command(str, ({}), "[the] 'lock' / 'chest' [on] [the] [chest]"))
		return 0;

	NF("The chest has already been unlocked and looted.\n");
	if (chesthere == 1)
		return 0;

	NF("But the chest is trapped!  Just trying to pick it looks like it will "
	+ "spring the trap and impale your hands, and you don't want that, do "
	+ "you?\n");
	if (chesttrap == 0 && TP->query_prop(FOUND_HOB_CHEST_TRAP) == 1)
		return 0;

	if (chesttrap == 0)
	{
		spring_trap(TP);
		return 1;
	}

	if (TP->query_skill(SS_OPEN_LOCK) > 20 + random(10))
	{
		clone_object("/d/Genesis/gems/obj/jasper")->move(TP);
		if (random(4) == 1)
			clone_object("/d/Genesis/gems/obj/opal")->move(TP);

		clone_object("/d/Genesis/gems/obj/beryl_red")->move(TP);
		if (random(2) == 1)
			clone_object("/d/Genesis/gems/obj/beryl_red")->move(TP);
		if (random(3) == 1)
			clone_object("/d/Genesis/gems/obj/beryl_red")->move(TP);

		MONEY_MAKE_SC(100 + random(145))->move(TP);
		chesthere = 1;
		write("You unlock the chest with a satisfying \"chi-koonk\" noise "
		+ "from within as you open the lid quietly before looting a pile "
		+ "of silver and gems inside the chest.\n");
		return 1;
	}

	write("You fumble with the lock on the chest but instead of a satisfying "
	+ "\"chi-koonk\" noise from within, you hear the ominous click of a gear "
	+ "below the stump.\nNothing happens.\n");
	chesttrap = 0;
	return 1;
}

int
chest_open()
{
	if (chesthere != 0 && TP->query_prop(FOUND_HOB_CHEST) == 1)
	{
		write("The chest is empty inside.\n");
		return 1;
	}

	if (chesthere == 0 && TP->query_prop(FOUND_HOB_CHEST) == 1)
	{
		write("The chest is locked.  You can't figure this thing out.\n");
		return 1;
	}
	return 0;
}

string
exa_shaft()
{
	if (TP->query_prop(FOUND_HOB_CHEST_TRAP) == 1)
	{
		return "There is a strange shaft jammed beside the chest pointing "
		+ "up where your hand would reach in to release the latch.  You "
		+ "believe it is a trap triggered by meddling with the chest.\n";
	}

	return "You find no shaft.\n";
}

string
exa_trap()
{
	if (TP->query_prop(FOUND_HOB_CHEST_TRAP) == 1)
	{
		return "There is a strange shaft jammed beside the chest pointing "
		+ "up where your hand would reach in to release the latch.  You "
		+ "believe it is a trap triggered by meddling with the chest.\n";
	}

	return "You find no trap.\n";
}
