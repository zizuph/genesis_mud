/* 
 * Kirk's hq parlour off Jems Court.  Can draw graffiti
 * on the walls.
 *
 * Mortis 06.2006
 * 
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>

#define MAP_FILE		MONKS + "brix_graffiti_map"

inherit MONKS_ROOMBASE;

// Prototypes
int graffiti(string str);
int write_more(string str);
int post_graffiti();
int generate_graf_loc();
string player_graffiti();

int graffiti_busy = 0;
string graffiti;
object hood1, hood2, hood3;

void
reset_palan_room()
{
	if (!hood1)
	{
		hood1 = clone_object(MONKS + "living/brix_ganger_low");
		hood1->move(TO);
	}

	if (!hood2)
	{
		hood2 = clone_object(MONKS + "living/brix_ganger_low");
		hood2->move(TO);
	}

	if (!hood3)
	{
		hood3 = clone_object(MONKS + "living/brix_ganger_low");
		hood3->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("In the parlour of a dilapidated, crumbling gang house");
    LONG("With walls of dirty, moldy, tan brick and a floor and ceiling "
	+ "of warped and aged, grey wood this one time parlour is now a hovel "
	+ "for the gangs of Jems court.  The windows are boarded up, the walls "
	+ "covered with chalk graffiti, and the floor littered with trash.  "
	+ "A twisted, dilapidated staircase spirals up in the east, and an old "
	+ "door leads west out into the alley.\n");

	ITEM("house", "Any house in particular?  You're in a house.  Why not "
	+ "have a <look> around?\n");
	ITEM(({"floor", "ceiling"}), "The aged, grey wooden boards of the ceiling "
	+ "and floor are warped and creak when walked upon.  Bits of trash litter "
	+ "the place especially in the corners.  There are markings on the floor "
	+ "near the north and east walls that give you the impression that walls "
	+ "once stood there but have long since been knocked down.\n");
	ITEM(({"corner", "corners", "trash", "litter", "bottle", "bottles",
		"paper", "papers", "sock", "dirty sock"}), "Broken bottles, "
	+ "crumpled papers, and even a dirty sock litter the floor especially "
	+ "in the corners.\n");
	ITEM(({"wall", "walls"}), "Built of old, tan bricks spotted with mold "
	+ "and covered with dirt, the walls are in extreme disrepair.  The "
	+ "north wall is bowed inward, and much of the mortar in the south is "
	+ "cracked and brittle.\n");
	ITEM(({"graffiti", "chalk graffiti"}), "Chalk graffiti is scattered "
	+ "across the walls of the house running the gamut from poorly "
	+ "spelled profanity to obscene stick figures to knives and skulls."
	+ "@@player_graffiti@@" + "\nIf you have some chalk, you can add your "
	+ "own with <graffiti>.\n");

	add_smell("vampire", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.  The scent of blood is stronger "
	+ "here.");
	add_smell("morgul", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("human", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("elf", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  The ghastly combination turns your stomach.");
	add_smell("goblin", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  It reminds you of home.");
	add_smell("dwarf", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("hobbit", "The air is tainted with the smells of stale alcohol "
	+ "and urine, but the leaf smoke in the air makes your nose twitch "
	+ "curiously.");
	add_smell("gnome", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  By human standards this must be acceptable, "
	+ "but your gnomish nose tells you the air quality has been compromised "
	+ "to dangerous levels.");
	add_smell("minotaur", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.");
	add_smell("halfhuman", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.");
	add_smell("halfelf", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.  It is rather unpleasant.");
	add_smell("orc", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  It reminds you of home.");
	add_smell("hobgoblin", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  Filthy but welcoming in a homely sort of way.");
	add_smell("kender", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  Gross!");
	add_smell("drow", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  These surface dwellers live like pigs.");
	add_smell("noldor", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  The revolting combination sickens you.");
	add_smell("uruk", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  Filthy but welcoming in a homely sort of way.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air filled with the smells of a human back alley.");
	add_smell("unknown", "You smell the air rich with the smells of a human "
	+ "back alley, but what the heck race are you?  Why not mail Krynn for "
	+ "fun?");

	clone_object(MONKS + "doors/brix_kirk_door_in")->move(TO);

	EXIT(MONKS + "brix_kirk_hq", "up", 0, 0);
	
	reset_palan_room();
}

void
init()
{
	::init();
	ADA("graffiti");
}

int
graffiti(string str)
{
	object *chalks;

	NF("Simply use <graffiti> to open the graffiti drawing dialogue.\n");
	if (str)
		return 0;

	chalks = FIND_STR_IN_OBJECT("stick of chalk", TP);
	NF("You'll need to find a big stick of chalk before you can draw any "
	+ "graffiti.\n");
	if (sizeof(chalks) == 0)
		return 0;

	NF("Someone else is already drawing graffiti here.  If you wait until "
	+ "they're done, you can draw next.\n");
	if (graffiti_busy == 1)
		return 0;

	write("You may draw your graffiti below.\n"
	+ "On any line you can give ** to end, or ~q to abort the message.\n");
	graffiti = "";
	graffiti_busy = 1;
	write("-->");
	input_to("write_more");

	return 1;
}

int
write_more(string str)
{
	if (str == "**")
	{
		post_graffiti();
		graffiti_busy = 0;
		return 1;
	}

	if (str == "~q")
	{
		write("Graffiti aborted.\n");
		graffiti_busy = 0;
		return 1;
	}

	graffiti += (str + "\n");
	write("-->");
	input_to("write_more");
	return 1;
}

int
post_graffiti()
{
	mapping graf_map = ([]);
	int graf_loc;
	string graf_loc_str;
	mixed time_graffiti;

	NF("That drawing was too small to see.  Graffiti aborted.\n");
	if (graffiti == "")
		return 0;

	NF("There isn't enough space to draw that much graffiti!  Graffiti "
	+ "aborted.\n");
	if (strlen(graffiti) > 328)	// 4 x 80 + \n's at the end.
		return 0;

	write("You scrawl some graffiti across the walls with your stick of "
	+ "chalk.\n");
	say(QCTNAME(TP) + " scrawls some graffiti across the walls with " + HIS(TP)
	+ " chalk.\n");

	graffiti_busy = 0;

	graf_loc = generate_graf_loc();
	graf_loc_str = LANG_WNUM(graf_loc);
	time_graffiti = (({time(), graffiti}));
	graf_map = restore_map(MAP_FILE);
		
	graf_map += ([graf_loc_str : time_graffiti]);

	save_map(graf_map, MAP_FILE);

    return 1;
}

int
generate_graf_loc()
{
	mapping graf_map = ([ ]),
		    array1   = ([ ]),
		    array2   = ([ ]);
	int i, thetime, thetime_next;
	mixed time_graffiti;
	string thegraf;

	graf_map = restore_map(MAP_FILE);

	for (i=0; i < 12; i++)
	{
		string j = LANG_WNUM(i);
		
		if (!pointerp(graf_map[j]))
			return i;
	}

	for (i=0; i < 12; i++)
	{
		int ii = i + 1;
		if (ii == 11)
			ii = 0;

		string j  = LANG_WNUM(i),
			   jj = LANG_WNUM(ii);

		array1 = graf_map[j];
		array2 = graf_map[jj];

		thetime = array1[0];
		thetime_next = array2[0];

		if (thetime < thetime_next)
			return i;
	}

	return 1;	// Shouldn't reach this.
}

string
player_graffiti()
{
	mapping graffiti_pics = ([ ]),
		    array1        = ([ ]);

	int i;
	string thegraf, see_graf = "";
	mixed time_graffiti = ({});

	graffiti_pics = restore_map(MAP_FILE);

	for (i=0; i < 12; i++)
	{
		string j = LANG_WNUM(i);

		if (!pointerp(graffiti_pics["no"]))
			return see_graf;

		if (!pointerp(graffiti_pics[j]))
			return "  Recently someone has drawn:\n" + see_graf + "\n";

		array1 = graffiti_pics[j];		
		thegraf = array1[1];

		see_graf += "~~~~~\n" + thegraf;
	}

	return "  Recently someone has drawn:\n" + see_graf + "\n";
}
