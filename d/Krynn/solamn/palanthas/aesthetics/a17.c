/* Mortis 11.2005
 * Housing smells.
 * 
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MONKS_BASE;

string
query_to_jail()
{
	return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Jems court curves in an oval west and north from here.  "
	+ "Row upon row of tightly packed houses are all you can see in this "
	+ "housing district.  The street is dusty.  The street cleaners must "
	+ "not come here.  The city wall towers above the homes to the south.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Jems court and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn, dusty marble of Jems court and its buildings lights "
	+ "up in the midday sun as people and maroon robed aesthetics travel "
	+ "throughout the Aesthetics quarter filling the street with the "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn, dusty marble of Jems court catches the "
	+ "last rays of the sun appearing to glow in a dull fashion "
	+ "as travellers and the occasional maroon robed aesthetics make their "
	+ "way about the court." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Jems court amplifying the yellow glow of the street lamps.  "
	+ "A few poorly dressed people still make their way about at "
	+ "this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Jems court in the southwest housing district of the "
	+ "aesthetics quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the south.  It is faced with "
	+ "large block panels of polished, translucent marble.\n");
	ITEM(({"court", "jems court", "jems", "housing district", "houses"}),
		"A large housing district unfolds before you to the north and "
	+ "west.  The houses are densely arranged around Jems court, a long "
	+ "oval of a street.  Though mostly well-worn marble, portions of the "
	+ "street have been replaced with beige, clay bricks while some blocks "
	+ "are missing entirely and are potholes of dirt and muck.  The houses "
	+ "are smaller than most in the city.  Several are two-stories, but a "
	+ "good deal are only one.  Marble isn't uncommon here, but it's no "
	+ "more prevalent than brick and wood.  Street lamps are not arranged "
	+ "so orderly in this part of the city either.\n");

	add_smell("vampire", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its inhabitants are crowded out by the dirt and debris of the unswept "
	+ "streets, and the smell of cooking fires is tainted by an odd leaf "
	+ "smoke from the alleys to the north where cheap alcohol lingers in "
	+ "the air.  There is blood to be found closeby in this neighborhood.");
	add_smell("morgul", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its inhabitants are crowded out by the dirt and debris of the unswept "
	+ "streets, and the smell of cooking fires is tainted by an odd leaf "
	+ "smoke from the alleys to the north.");
	add_smell("human", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its inhabitants are crowded out by the dirt and debris of the unswept "
	+ "streets, and the smell of cooking fires is tainted by an odd leaf "
	+ "smoke from the alleys to the north.");
	add_smell("elf", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the dirt and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "potent leaf smoke from the alleys to the north from where the reek of "
	+ "alcohol wafts.");
	add_smell("goblin", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the dirt and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "strong leaf smoke from the alleys to the north from where the reek "
	+ "of alcohol and piss wafts.");
	add_smell("dwarf", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its inhabitants are crowded out by the dirt and debris of the unswept "
	+ "streets, and the smell of cooking fires is tainted by a curiously "
	+ "strong leaf smoke from the alleys to the north.");
	add_smell("hobbit", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its inhabitants are crowded out by the dirt and debris of the unswept "
	+ "streets, and the smell of cooking fires is tainted by a curiously "
	+ "enticing leaf smoke from the alleys to the north.");
	add_smell("gnome", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its inhabitants are crowded out by the dirt and debris of the unswept "
	+ "streets, and the smell of cooking fires is tainted by a curiously "
	+ "dangerous leaf smoke from the alleys to the north.  The air quality "
	+ "is definitely subpar here but survivable.");
	add_smell("minotaur", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the dirt and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "strong leaf smoke from the alleys to the north from where the reek "
	+ "of alcohol and piss wafts.");
	add_smell("halfhuman", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the dirt and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "potent leaf smoke from the alleys to the north from where the reek of "
	+ "alcohol wafts.");
	add_smell("halfelf", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the dirt and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "potent leaf smoke from the alleys to the north from where the reek of "
	+ "alcohol wafts.");
	add_smell("orc", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the dirt and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "strong leaf smoke from the alleys to the north from where the reek "
	+ "of alcohol and piss wafts.");
	add_smell("hobgoblin", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the dirt and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "strong leaf smoke from the alleys to the north from where the reek "
	+ "of alcohol and piss wafts.");
	add_smell("kender", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its inhabitants are crowded out by the dirt and debris of the unswept "
	+ "streets, and the smell of cooking fires is tainted by a curious "
	+ "leaf smoke from the alleys to the north.  What is that smoke, and "
	+ "what could they be cooking?");
	add_smell("drow", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the filth and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "potent leaf smoke from the alleys to the north from where the reek of "
	+ "alcohol wafts.");
	add_smell("noldor", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the filth and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "dangerous leaf smoke from the alleys to the north from where the reek "
	+ "of old alcohol wafts.");
	add_smell("uruk", "The salty breezes from the bay barely penetrate the "
	+ "dusty air of this neighborhood.  The smells of the daily lives of "
	+ "its human inhabitants are crowded out by the dirt and debris of the "
	+ "unswept streets, and the smell of cooking fires is tainted by a "
	+ "strong leaf smoke from the alleys to the north from where the reek "
	+ "of alcohol and piss wafts.");
	add_smell("presence", "You get little from the dusty air in your present "
	+ "form.");
	add_smell("unknown", "The dusty air and smells of a dirty human "
	+ "neighborhood come to you, but what the heck race are you?  Why not "
	+ "mail Krynn for fun?");

	EXIT(MONKS + "a16", "north", 0, 0);
	EXIT(MONKS + "w16", "south", 0, 0);
	EXIT(MONKS + "a18", "west", 0, 0);

}
