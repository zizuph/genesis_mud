/* 
 * Small, dark alley east of Kirk's hq on Jems Court.
 * Dwarf scalp found in trash part of quest.  Update
 * functions with QUEST BIT checks when quest is
 * implemented.
 *
 * Mortis 06.2006
 * 
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>

inherit MONKS_BASE;

/* 0 - Not aware
   1 - Found
   2 - Recovered */
#define BRIX_FOUND_DWARF_REMAINS		"_brix_found_dwarf_remains"

// Prototypes
int recover(string str);
string mega_rat();
string exa_trash();

int rats_in_trash, trash_piled;

void
reset_palan_room()
{
	rats_in_trash = 8 + random(4);
	trash_piled = 0;
}

void
create_palan_room()
{
    SHORT("In a small, dark alley east of a two-story, run-down house");
    LONG("This small, dark alley is filled with bags of trash, "
	+ "broken barrels, splintered wood, and the skittering noises of the "
	+ "scurrying feet of rats.  It is completely boxed in by tightly "
	+ "packed houses in disrepair.  The largest is a run-down, two-story "
	+ "house to your west with filthy, tan brick walls.\n");

	ITEM(({"court", "jems court", "jems", "housing district", "houses"}),
	  "A large housing district unfolds around you to.  The houses are "
	+ "densely arranged around Jems court, a long "
	+ "oval of a street.  Though mostly well-worn marble, portions of the "
	+ "street have been replaced with beige, clay bricks while some blocks "
	+ "are missing entirely and are potholes of dirt and muck.  The houses "
	+ "are smaller than most in the city.  Several are two-stories, but a "
	+ "good deal are only one.  Marble isn't uncommon here, but it's no "
	+ "more prevalent than brick and wood.  Street lamps are not arranged "
	+ "so orderly in this part of the city either.\n");
	ITEM("house", "Any house in particular?  North?  South?  East?  "
	+ "West?\n");
	ITEM(({"north house", "south house", "east house"}), "Tightly packed "
	+ "houses of which you can only see the backs.\n");
	ITEM(({"west house", "run-down house", "two-story"}), "A run-down, "
	+ "two-story house is before you to the west.  It is built from tan "
	+ "bricks with old, gray mortar and an aging, wood shingled roof.  It "
	+ "is covered in dirt and spots of mold.\n");
	ITEM(({"wall", "walls"}), "The walls of the run-down, two-story "
	+ "house to the west are made of old, tan bricks whose mortar is "
	+ "cracked and crumbling.\n");
	ITEM(({"bag", "bags", "trash", "wood", "barrel", "barrels"}),
	  "Rotten bags of trash, old grey planks of splintered wood, and the "
	+ "remains of shattered barrels litter the ground here piled against "
	+ "the backs of the houses." + "@@exa_trash@@" + "\n");
	ITEM(({"rat", "rats"}), "@@mega_rat@@");

	add_smell("vampire", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, urine, and rotting corpses.  The scent of blood "
	+ "is tainted here, but grows strong inside the house to the west.");
	add_smell("morgul", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, urine.");
	add_smell("human", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine, and rotting corpses.");
	add_smell("elf", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, urine, and rotting corpses.  The ghastly combination turns "
	+ "your stomach.");
	add_smell("goblin", "The air is filled with the smells of old booze, "
	+ "smoke, piss, and rotting corpses.  It reminds you of home.");
	add_smell("dwarf", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, urine, and rotting corpses.");
	add_smell("hobbit", "The air is tainted with the smells of stale alcohol, "
	+ "urine, and rotting corpses, but the leaf smoke in the air makes your "
	+ "nose twitch curiously.");
	add_smell("gnome", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, urine, and rotting corpses.  By human standards this must "
	+ "be acceptable, but your gnomish nose tells you the air quality has "
	+ "been compromised to highly dangerous levels.");
	add_smell("minotaur", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, urine, and rotting corpses.");
	add_smell("halfhuman", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, urine, and rotting corpses.");
	add_smell("halfelf", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, urine, and rotting corpses.  It is rather "
	+ "unpleasant.");
	add_smell("orc", "The air is filled with the smells of old booze, "
	+ "smoke, urine, and rotting corpses.  It reminds you of home.");
	add_smell("hobgoblin", "The air is filled with the smells of old booze, "
	+ "smoke, piss, and rotting corpses.  Filthy but welcoming in a homely "
	+ "sort of way.");
	add_smell("kender", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, urine, and rotting corpses.  Sick!");
	add_smell("drow", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, urine, and rotting corpses.  These surface dwellers live "
	+ "like pigs.");
	add_smell("noldor", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, urine, and rotting corpses.  The revolting combination "
	+ "sickens you.");
	add_smell("uruk", "The air is filled with the smells of old booze, "
	+ "smoke, piss, and rotting corpses.  Filthy but welcoming in a homely "
	+ "sort of way.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air filled with the bad smells of a human back alley.");
	add_smell("unknown", "You smell the air rich with the bad smells of a "
	+ "human back alley, but what the heck race are you?  Why not mail Krynn "
	+ "for fun?");

	CMD(({"bag", "bags", "trash", "wood", "barrel", "barrels"}), ({"pile",
		"stack"}), "@@pile_trash");

	EXIT(MONKS + "brix_kirk_roof", "up", "@@climb_wall", 0);

	reset_palan_room();
}

string
exa_trash()
{
	if (trash_piled == 1)
		return "  Some of the trash has been piled against the wall of the "
		+ "house to the west perhaps to aid in climbing out of here.";

	return "";
}

string
mega_rat()
{
	if (rats_in_trash <= 0)
	{
		write("You poke, prod, and sift through the trash but find no rats "
		+ "left, although there is enough rat crap and the like to equal "
		+ "the volume of several of the vermin.");
		say(QCTNAME(TP) + " pokes, prods, and sifts through the trash");

		// If quest finished, add quest bit check here.
		if (TP->query_prop(BRIX_FOUND_DWARF_REMAINS) == 2)
		{
			write("  Other than that you find nothing else of interest.\n");
			say(" fruitlessly.\n");
			return "";
		}

		TP->add_prop(BRIX_FOUND_DWARF_REMAINS, 1);
		write("  Underneath the pieces of a shattered barrel you discover "
		+ "the badly decayed remains of what must have been a dwarf.  At a "
		+ "glance the bits of flesh still hanging to the bone hint at a "
		+ "violent murder.  Despite their wretched state, you feel confident "
		+ "you could <recover> these remains.\n");
		say(" and uncovers some badly decayed remains beneath the pieces of "
		+ "a shattered barrel.\n");
		return "";
	}

	string rat_rand = one_of_list(({"burrowing through the bags of trash",
	"scurrying under a shattered barrel", "darting through planks of rotten, "
	+ "splintered wood"}));

	write("You spot an enormous rat " + rat_rand + " as it leaps for your "
	+ "throat!\n");
	say(QCTNAME(TP) + " rummages through the trash and spots an enormous "
	+ "rat " + rat_rand + " as it leaps for " + HIS(TP) + " throat!\n");

	rats_in_trash--;

	object trat = clone_object(MONKS + "living/brix_trash_rat");
	trat->move(TO);
	trat->command("kill " + TP->query_name());

	return " ";
}

void
init()
{
	::init();

	ADA("recover");
}

int
recover(string str)
{
	NF("You've already recovered what remains you could.  The rest "
	+ "disintegrated, remember?\n");
	if (TP->query_prop(BRIX_FOUND_DWARF_REMAINS) == 2)
		return 0;

	NF("What?\n");
	if (TP->query_prop(BRIX_FOUND_DWARF_REMAINS) != 1)
		return 0;

	NF("Recover what?\n");
	if (!str)
		return 0;

	NF("Attempt to recover what?  The remains?\n");
	if (str != "remains")
		return 0;

	/* Duplicate prop addition to prevent multiple set_alarms from being
	 * triggered during the 2 second delay until recover2 is called. */
	TP->add_prop(BRIX_FOUND_DWARF_REMAINS, 2);
	write("Propping the pieces of shattered barrel up with one hand, you "
	+ "grab a fistful of the dwarf's auburn hair and tug appropriately...\n");
	say(QCTNAME(TP) + " props up the pieces of a shattered barrel with one "
	+ " hand as " + HE(TP) + " grabs a fistful of reddish hair from beneath "
	+ "and tugs.\n");
	set_alarm(2.0, 0.0, "recover2", TP);
	return 1;
}

int
recover2(object tugger)
{
	object dscalp;

	tugger->add_prop(BRIX_FOUND_DWARF_REMAINS, 2);
	tugger->catch_msg("The shattered barrel pieces collapse disintegrating "
	+ "into a dust cloud along with the remains of the dwarf leaving you "
	+ "standing in surprise with a rotted auburn haired scalp in your "
	+ "hand.\n");
	tell_room(E(tugger), "The shattered barrel pieces collapse "
	+ "disintegrating into a dust cloud leaving " + QTNAME(tugger)
	+ " standing with " + HIS(tugger) + " mouth agape and a rotten auburn "
	+ "haired scalp in " + HIS(tugger) + " hand.\n", tugger);
	
	dscalp = clone_object(MONKS + "obj/dwarf_scalp");
	dscalp->move(tugger);
	
	/* No, I don't want a prop/var set in the room to keep someone from
	 * getting a scalp right after someone else.  Preventing a person
	 * from getting more than one is my goal, not delaying the next
	 * person interested in the quest. */

	return 1;
}

int
climb_wall()
{
	int climb_diff = 38 + random(4);

	if (trash_piled == 1)
		climb_diff = 22 + random(16);

	if (TP->query_skill(SS_CLIMB) < climb_diff)
	{
		write("You try to climb up to the roof but slip and fall!\n"
		+ "You just can't seem to make it.  Maybe you need climbing "
		+ "assistance of some sort, or maybe the trash isn't piled "
		+ "high enough for you?\n");
		say(QCTNAME(TP) + " " + one_of_list(({"tries to climb up the "
		+ "walls of the run-down house to the west but slips, falls, and "
		+ "lands on " + HIS(TP) + " butt in a heap on the ground.",
		  "lays flat against the wall of the run-down house to the west "
		+ "and humps it impotently in a failed attempt to scale it, "
		+ "or so you guess.",
		  "pounds " + HIS(TP) + " fists against the nicked walls of the "
		+ "run-down house to the west in a feeble attempt to climb it.",
		  "sighs as " + HE(TP) + " wishes " + HE(TP) + " had a rope"
		+ "."})) + "\n");
		return 1;
	}

	write("Using the missing chunks and nicks as handholds, you "
	+ "successfully climb onto the sagging roof of the two-story, "
	+ "run-down house to the west.\n"); 
	say("Using the missing chunks and nicks in the wall as handholds, "
	+ QCTNAME(TP) + " successfully climbs onto the sagging roof of the "
	+ "two-story, run-down house to the west.\n");

	return 0;
}

int
pile_trash()
{
	if (trash_piled == 1)
	{
		write("The trash has already been piled against the wall of the "
		+ "house to the west.  It should be easier to climb out now.\n");
		return 1;
	}

	if (mega_rat() != " ")
	{
		write("You pile enough trash against the wall of the house to the "
		+ "west to increase your chances of climbing out.\n");
		say(QCTNAME(TP) + " piles some of the trash against the wall of the "
		+ "house to the west.\n");
		trash_piled = 1;
		return 1;
	}

	write("Oh no, the trash is infested with rats, and they don't like being "
	+ "disturbed!\n");
	return 1;
}