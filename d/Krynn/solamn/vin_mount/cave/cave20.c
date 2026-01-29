/* 
 * New cave expansion.
 *
 * Mortis 11.2006
 */

#include "../local.h";
#include <macros.h>
#include <wa_types.h>

inherit CAVE_BASE

// Prototypes
int shovel_it();
void it_lands(string trash);

void
create_vin_mount_room() 
{
	SHORT("Small natural cavern");
	LONG("A small natural cavern opens before you, its floor covered with "
	+ "the broken remains of stalagmites, scraps of bone, refuse, and a "
	+ "brownish-black sludge that slowly drips through a hole in the floor "
	+ "and down the stalactites in the cavern below.  The odour is "
	+ "rotten.\n");

	ITEM(({"sludge", "floor", "remains", "scraps", "bone", "refuse", 
	"trash"}), "Gnawed bones, clumps of feces, and refuse make up a "
	+ "brownish-black sludge covering the floor and slowly dripping through "
	+ "a hole in the floor.  You can shovel some of it down if it suits your "
	+ "fancy.\n");
	ITEM(({"stalagmite", "stalagmites"}), "Most of the stalagmites on the "
	+ "floor are broken and covered in sludge.\n");
	ITEM("opening", "A small, oval opening is recessed into the darkness of "
	+ "the floor among the sludge stained stalactites.  It is too small "
	+ "to get through, but you could shovel something through it.\n");

	DARK;

	CMD(({"sludge", "trash", "remains", "scraps", "bone", "refuse",
	"clumps", "feces", "shit", "crap", "filth"}), "shovel", shovel_it);

	EXIT(CAVE + "cave16", "north", 0, 0);
}

int
shovel_it()
{
	object footwear = TP->query_armour(A_FEET);
	string trash = one_of_list(({"clump of sludge", "beaver remains",
	"bone", "beaver tail", "sludge dripping bone", "sludge dripping "
	+ "beaver bone", "boner", "poop log", "hobgoblin ear", "brownish-"
	+ "black hunk of fecalesque crapulence"}));
	string sfeet = "bare feet";

	if (objectp(footwear))
		sfeet = footwear->query_short();

	write("Using your " + sfeet + ", you shovel a " + trash + " into the "
	+ "opening in the floor.\n");
	say(QCTNAME(TP) + " uses " + HIS(TP) + " " + sfeet + " to shovel a "
	+ trash + " into the opening in the floor.\n");

	set_alarm(3.0, 0.0, "it_lands", trash);
	return 1;
}

void
it_lands(string trash)
{
	object obtrash;

	tell_room(CAVE + "cave20", "You hear a squick noise as the "
	+ trash + " lands down below.\n");
	tell_room(CAVE + "cave02", "From out of the ceiling flies a " + trash
	+ " landing with a squick noise into the heaps of refuse.\n");
	
	obtrash = clone_object("/std/object");
	obtrash->set_short(trash);
	obtrash->set_long("This is a nasty " + trash + " covered in filthy "
	+ "sludge.\n");
	obtrash->add_name(trash);
	obtrash->move(CAVE + "cave02");
}