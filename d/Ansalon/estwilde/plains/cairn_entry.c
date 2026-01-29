#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit PLAINS_OUT;

#define INNER_CAIRN "/d/Ansalon/estwilde/plains/c1"
#define QUERY_THIEF ob->query_guild_style_occ() == "thief" || ob->query_guild_style_lay() == "thief" || ob->query_race_name() == "kender"

int door_open = 0;
object ob;

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("You stand on top of a steep hill overlooking "+
      "the plains of Estwilde. Beside you stands a squat cairn of "+
      "weathered granite, a lonely monolith that gazes over "+
      "untamed wilderness.@@door_desc@@ A goat trail leads down "+
      "the hill to your northeast.\n");

    add_item(({"weathered cairn","cairn","squat cairn"}),
      "Sitting atop this steep hill is a cairn of black "+
      "granite, weathered by time. Carved along the side "+
      "of one of the larger granite boulders are faint carvings.\n");
    add_item(({"granite boulders","boulders"}),
      "large granite boulders that have been weathered by time "+
      "make up this cairn.\n");
    add_item(({"faint carvings","carvings"}),
      "Faint, dwarven carvings of mighty battles have been carved "+
      "along the base of the cairn. You notice an inscription above "+
      "them you could probably read.\n");
    add_item("inscription","You notice a dwarven inscription " +
      "along the base of the cairn you could probably read.\n");
    add_item(({"goat trail","trail"}),
      "A goat trail leads down the hill to your northeast.\n");
    add_item(({"steep hill","hill"}),
      "You stand on top of a large hill. A great expanse "+
      "of grasslands stretch out before you, the plains "+
      "of Estwilde.\n");
    add_item(({"base", "base of cairn", "base of the cairn"}),
      "You notice faint carvings and inscriptions at the base " +
      "of the cairn.\n");
    add_item(({"portal","gloom","darkness"}),
      "@@portal_desc");

    add_exit(ROOM + "trail5","northeast",0);
    add_cmd_item("inscription","read","@@read_inscription");
    add_search(({"base","base of cairn"}), 2, "open_door", 1);

    reset_estwilde_room();
}

string
read_inscription()
{
    if(TP->query_race_name() != "dwarf")
	return "The inscription is in dwarven. You can't read it.\n";

    return "The inscription reads in ancient dwarven: "+
    "Here marks the grave of "+
    "Teregul Stormbolt, Hero of Iron Delving. His skill "+
    "at arms was unparalleled. May he rest in peace in the "+
    "arms of Reorx.\n";
}

string
short_descr()
{
    return "On top of a steep hill before a weathered "+
    "cairn";
}

string
door_desc()
{
    if(door_open)
    {
	return " You notice an open portal at the "+
	"base of the cairn, leading into gloomy darkness.";
    }
    return "";
}

string
portal_desc()
{
    if(door_open)
    {
	return "An open portal leads into the gloomy darkness "+
	"of the dwarven cairn.\n";
    }
    return "You do not notice anything of that sort.\n";
}

int
enter_cairn()
{
    write("You step into the gloom of the dwarven cairn...\n");
    return 0;
}

/* Note : Do not call lock_cairn_door() from this room.
 * In ~plains/c1.c call close_door() instead. When opening
 * the door, call from here unlock_cairn_door()
 */

void
lock_cairn_door()
{
    if(!door_open)
	return;

    door_open = 0;
    TO->remove_exit("portal");
    tell_room(TO, "The portal suddenly grinds shut " +
      "with a resounding 'thud'.\n");
}

void
unlock_cairn_door()
{
    if(door_open)
	return;

    door_open = 1;
    TO->add_exit(ROOM + "c1","portal","@@enter_cairn");
    INNER_CAIRN->open_door();
}

string
open_door(object who, string what)
{
    ob = TP;

    if(door_open)
	return 0;

    if(QUERY_THIEF)
    {

	say(QCTNAME(TP)+ "'s face suddenly widens into a crafty grin " +
	  "as " +HE(TP)+ " plays with something at the base of the cairn...\n\n" +
	  "A portal suddenly grinds open at the base of the cairn!\n");

	TO->unlock_cairn_door();

	return "Your experience as a master thief seems "+
	"to have payed off! Your expert hands have found a craftily "+
	"hidden mechanism within the inscriptions at the base "+
	"of the cairn, that with a quick flick of the wrist...\n\n"+
	"A portal suddenly grinds open at the base of the cairn!\n";
    }

    return "You find nothing of interest about the base of " +
    "the cairn.\n";

}
