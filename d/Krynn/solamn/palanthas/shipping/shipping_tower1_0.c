/* Mortis 02.2006 
 * 
 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_ROOMBASE;

string
query_to_jail()
{
  return "up";
}

void
reset_palan_room()
{
}

void
create_palan_room()
{
    SHORT("The cellar of a Palanthas guard tower");
    LONG("Beige tinted, translucent marble blocks line the floor of this, "
	+ "chill, dank tower cellar.  The walls are of curving, translucent "
	+ "white marble forming a perfectly circular room.  Grey, stone stairs "
	+ "curve along the wall leading up to the ground floor, and the ceiling "
	+ "above is ten feet high.  Locked weapon cases and armour chests line "
	+ "the walls.\n");

	ITEM(({"floor"}), "The floor is laid with beige tinted, translucent "
	+ "marble blocks that are cold to the touch.\n");	
	ITEM(({"wall", "walls"}), "Built entirely of large, translucent white "
	+ "marble blocks, the walls are at least two feet thick and have become "
	+ "beige tinted from the earth in which they have been laid.\n");
	ITEM(({"weapon cases", "cases", "case", "armour chests", "chest",
		"chests"}), "Locked weapon cases contain various clubbers, short "
	+ "swords, and mancatchers commonly used by the city guard to subdue "
	+ "miscreants.  Armour chests contain various chainmailed pieces and "
	+ "open white guard tunics.\n");
	ITEM("ceiling", "Thick, wide boards of polished oak reinforced with "
	+ "small, triangular wall supports form a high ceiling and the floor of "
	+ "the level above.  It is perhaps ten feet high, tall enough "
	+ "for most weapons to stand upright.  An iron chain suspends a large, "
	+ "oil lamp providing indoor light.\n");
	ITEM(({"large oil lamp", "ceiling lamp", "oil lamp", "large lamp"}),
	  "Hanging from a two foot, iron chain in the center of the ceiling is "
	+ "a large, oil lamp shedding steady light in the room.\n");
	ITEM("stairs", "Stairs of rough, grey, stone lead up to the second floor "
	+ "and down into the cellar.\n");
	ITEM("grey stone", "Neatly cut but left rough for traction, the grey "
	+ "stone of the stairs contrasts with the translucent white of the "
	+ "marble walls.\n");
	ITEM("cellar", "You are now in the cellar.  Have a <look> around?\n");

	add_smell("vampire", "The air in this cellar is comfortably dank and "
	+ "chill.  The familliar smell of earth and stone is strong here along "
	+ "with the smells of armament oils and leather.  There is no blood "
	+ "here, but it is not far.");
	add_smell("morgul", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("human", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("elf", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("goblin", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("dwarf", "The air in this cellar is dank and chill.  The "
	+ "familiar smell of earth and stone is strong here along with the "
	+ "smells of armament oils and leather.  These humans must not have "
	+ "mortared the stone here thoroughly for such earthy smells to be "
	+ "leaking in so strongly.");
	add_smell("hobbit", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("gnome", "The air in this cellar is dank, chill, and heavy "
	+ "with the familiar smells of earth and stone at such levels as to "
	+ "call into question the quality of mortar used to bind the marble "
	+ "blocks in the walls.  The smells of armament oils and leather is "
	+ "also present in detectable quantities.");
	add_smell("minotaur", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("halfhuman", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("halfelf", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("orc", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("hobgoblin", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("kender", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.  Why is it so earthy smelling in here "
	+ "you wonder?");
	add_smell("drow", "The air in this cellar is dank and chill.  The "
	+ "familiar smell of earth and stone is strong here along with the "
	+ "smells of armament oils and leather reminding you of past battles "
	+ "fought in the deep dark.");
	add_smell("noldor", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("uruk", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather.");
	add_smell("presence", "The air in this cellar is dank, chill, and "
	+ "earthy.");
	add_smell("unknown", "The air in this cellar is dank and chill.  The "
	+ "smell of earth and stone is strong here along with the smells of "
	+ "armament oils and leather, but what the heck race are you?  Why "
	+ "not mail Krynn for fun?");

	EXIT(SHIP + "shipping_tower1", "up", 0, 0);

	reset_palan_room();
}

