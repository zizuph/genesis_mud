/*
 * A normal house in Solace
 *
 * By Rastlin
 * Add_items and descrips by Teth
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  SOLINROOM;

object gDoor;

public void
create_solace_room()
{
    seteuid(getuid());

    set_short("An abandoned herbalist's house in Solace");
    set_long("@@my_desc@@");

    add_item("kitchen", "You can make neither heads nor tails of the " +
             "design of the kitchen. Abandoned and broken glassware " +
             "rests, stained with forgotten concoctions and painted " +
             "with dust. It looks as if the herbalist seldom ate here.\n");

    add_item("glassware", "Nothing of value can be found by inspecting " +
             "the glassware more carefully. It is either broken or " +
             "stained beyond usefulness.\n");

    add_item(({"stove", "wood stove"}), "Stained and blackened by " +
             "having potions brewed in containers on its surface, the " +
             "wood stove still looks like it could do its intended job.\n");

    add_item("bed", "Bereft of pillows and sheets, this simple cot " +
             "would be uncomfortable during a cold winter night. The " +
             "herbalist must have taken the linens and pillows with him.\n");

    add_item("rug", "Cloying scents rise from the rug as you breathe " +
             "in while examining it. Apparently, herbs of some sort " +
             "were grounded into the material of the rug, such that it " +
             "is covered with greenish smears on the cottonish coloured " +
             "material.\n");

    add_item(({"smear", "smears"}), "The chlorophyll-coloured stains " +
             "are definitely the source of the pungent scent.\n");

    add_item("dresser", "This dresser is plain, with the scent of a " +
             "resinous tree invading its drawers.\n");

    add_item(({"drawer", "drawers"}), "The drawers are sadly empty, " +
             "with the exception of the strong smell of cedar or pine.\n");

    add_item(({"shelf", "shelves"}), "The shelves stand tall above you, " +
             "bearing the day to day treasures of one who has had to " +
             "abandon his or her home suddenly.\n");

    add_item(({"treasure", "treasures"}), "Books, jars, a cracked " +
             "mortar and pestle, a torn satchel, drying rack..." +
             "all line the shelves.\n");

    add_item(({"book", "books"}), "Written in a heavy script, they are " +
             "either in a language foreign to you or of interest only " +
             "to those who study the extreme details of herbalism. You " +
             "can't help but wonder 'Who really cares?' after reading " +
             "a passage about whether bracts on one orchid qualifies it " +
             "to be a new species, a subspecies, or a variety.\n");

    add_item("jars", "Mostly broken and empty, two jars stand out as " +
             "possible candidates for further inspection: an earthen " +
             "brown jar and a forest-green glass jar.\n");

    add_item("jar", "Which one?\n");

    add_item(({"brown jar", "earthen jar", "earthen brown jar"}), "The " +
             "earthen brown jar appears to be made out of clay or some " +
             "other dusky mineral material.\n");

    add_item(({"glass jar", "forest-green jar", "forest-green glass jar"}),
             "Made out of a dark green glass, this jar appears to be " +
             "hiding something inside it.\n");

    add_item(({"drying rack", "rack"}), "The rack stands empty, its " +
             "purpose no longer cared about.\n");

    add_item(({"mortar", "pestle", "cracked mortar", "mortar and pestle",
             "cracked mortar and pestle"}), "Cracked and chipped, " +
             "the mortar and pestle look as if they were valuable and " +
             "well-used once upon a time, but never again.\n");

    add_item(({"satchel", "torn satchel"}), "This small pouch is of no " +
             "use to anyone, its leather chewed by a mouse or other " +
             "creature to the point of beyond repair.\n");

    gDoor = clone_object(OBJ + "d_house6");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "This dusty abode, by the sights and smells of it, is an " +
	  "abandoned herbalist's house. A greenish ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += " door is set into the entrance of the room, north from here. " +
           "The kitchen and wood stove look somewhat modified, perhaps to " +
          "fit the needs of the herbalist. Directly opposite the " +
           "kitchen rests a lonely bed and dresser. The south wall " +
           "is hidden by an immense shelf that holds books, jars, and " +
           "other tools of the herbalist's trade. The herbalist seems " +
           "to have left in quite a hurry, but unfortunately most of the " +
           "items left behind are quite useless. You are standing on a " +
           "rug that has a pleasant scent.\n";

    return str;
}

