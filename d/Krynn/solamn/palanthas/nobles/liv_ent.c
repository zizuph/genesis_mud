/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "east";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the west is the Solamnian Livery manor house.  The "
	+ "stable longhouse runs north from it, and to the south is a corral.  "
	+ "Several tall, old buildings line the field to the north and south.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The short grass of this small field flutters in small waves "
	+ "on the the cool, misty breeze blowing south from the bay as the "
	+ "morning sun peeks above the mountains in the east." + road;
	break;

    case TOD_DAY:
	desc += "The short grass of this small field flutters in small waves "
	+ "on the midday breeze blowing south from the bay.  Nobles, knights, "
	+ "and some other citizens come and go here, some testing out new mounts "
	+ "and others showing off their finest." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The short grass of this small field flutters in small waves "
	+ "on the the cool, misty breeze blowing south from the bay as the "
	+ "evening sun lowers above the mountains to the west.  Several "
	+ "equestrians are here fetching their horses while visitors just "
	+ "arriving lead their horses west to be stabled." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the short grass of "
	+ "this field as a cool, misty breeze blows south off the bay.  Late "
	+ "night arriving visitors lead their horses west to be stabled."
	+ road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("In a field east of the Solamnian Livery");
    LONG("@@get_time_desc@@");

	ITEM(({"livery", "solamnian livery", "house", "manor", "manor house"}),
	  "The great, marble manor house to "
	+ "your west is an old, translucent marble building whose grounds were "
	+ "converted ages ago to accomodate the field, wood-fenced corral, and "
	+ "stables.  The stables are a great longhouse of wood with a fenced in "
	+ "area for bringing horses to and from the stalls.  It extends north "
	+ "from the manor house while the corral is to the south.\n");

	ITEM(({"stable", "stables", "longhouse"}), "The stable longhouse runs "
	+ "north from the livery manor house.  It's as large as a barn but much "
	+ "longer.  It is the only wooden building in the noble district built "
	+ "a generation ago when this estate changed hands.  A run of fenced "
	+ "corridors extends down the length of the stables for bringing horses "
	+ "to and from it in an orderly fashion.\n");

	ITEM(({"grass", "field"}), "Short, green grass with light tints of "
	+ "brown form a small field for equestrians to gather.  It is well "
	+ "trampled and dotted with the occasional pile of manure.  A gravel "
	+ "path leads east where the marble of Livery Street begins.\n");

	ITEM("manure", "Piles of horse sized droppings dot the field around "
	+ "you.\n");

	ITEM(({"gravel", "path", "gravel path"}), "White marble gravel has "
	+ "been smoothed out to create a stately path from livery field to "
	+ "Livery Street in the east.\n");

	ITEM("corral", "The corral is a round fenced in area approximately "
	+ "thirty feet in diameter for training or viewing horses.  Its "
	+ "wooden fence is seven feet high and very sturdy.\n");

	ITEM(({"horse", "horses"}), "There are horses coming and going at all "
	+ "hours at the Solamnian Livery from the corral to the field, to the "
	+ "stables.\n");

	ITEM(({"n alley", "north alley"}), "An alley opens between a pair of "
	+ "stately marble buildings north of the equestrian field.  It appears "
	+ "to end after a block, but it's difficult to be certain from here.\n");

	ITEM(({"s alley", "south alley"}), "A side street leads south from the "
	+ "equestrian field.  It appears to be heading through a block of grand "
	+ "marble buildings towards Nobles' Way.\n");

	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the pungent smell of fresh cut hay, boiled leather, and well "
	+ "groomed horses.  Though strong here, these scents pale to the smell "
	+ "of manure from the field corrupting your senses.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of horses and leather to your west.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of fresh cut hay, leather, and horses.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the smells of fresh cut hay, tanned leather, and well cared for "
	+ "horses to your west alongside the fumes from the droppings in "
	+ "this field.");
	add_smell("goblin", "The fresh smells of horses and hay from the "
	+ "west mix here with manure and misty air blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of hay, tanned and boiled leathers, and horses from "
	+ "your west.  Your keen dwarven nose doesn't miss the steamy smells "
	+ "of horse manure on the field either.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the relaxing smell of fresh cut hay, the warm smell of leather, "
	+ "and horse scents coming from your west.  There is an unappetizing "
	+ "odour of horse poop here.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of hay, horses, and "
	+ "leather from the livery to your west.  The piles of manure on the "
	+ "field don't fail to register to your gnomish senses.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the familiar smells of well groomed horses and leather as well "
	+ "as fresh, crunchy hay to your west and the smell of manure.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the familiar smells of hay, horses, and leather to your west.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of fresh cut hay, leather, and horses "
	+ "coming from your west and you don't fail to miss the smell of manure.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the mouth-watering smell of horse flesh and leather to your west and "
	+ "horse crap from the field.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of well groomed horse, good leather, and fresh hay to "
	+ "your west and the stink of horse crap from the field.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the relaxing smell of fresh cut hay, the warm smell of leather, "
	+ "and horse scents coming from your west.  What's that musky smell from "
	+ "the numerous brown piles on the field?  Oh, it's horse poo.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of fresh cut hay, leather, and groomed horses from "
	+ "the livery to your west.  You pay no heed to the odour of horse "
	+ "offings on the field.");
	add_smell("unknown", "You smell the horses and such to your west, but "
	+ "your race is unknown to the immortals!  Please mail Krynn with your "
	+ "race.");

	add_alley("n", "north", NOBLE + "alley001");
	add_alley("s", "south", NOBLE + "alley004");

	EXIT(NOBLE + "livery", "west", 0, 0);
	EXIT(NOBLE + "n01", "east", 0, 0);

}