/*
 * Road in Bree
 * By Finwe, June  2001
 * 
 * Added some add_items and a path so people
 * can get behind the adventurer's guild and 
 * climb into the attic for the quest in the 
 * Foaming Mug (/d/Shire/eastroad/western/foam_mug)
 *
 * Raymundo, Jan 2020
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit ROAD_BASE;

object human;

void
create_road_room()
{

    set_areadesc("large");
    set_area("busy");
    set_areaname("road");
    set_land("Bree");

    add_my_desc("The road winds northeast and south. East is a " +
        "square building. Houses line the road while a stone wall " +
        "runs along the western side of the road. Looking south and " +
        "west is a large inn.\n");
    
    add_item(({"prancing pony", "prancing pony inn", "the prancing pony", 
            "the prancing pony inn", "inn"}),
        "The large inn stands to the southeast. It is clearly one " +
        "of the biggest buildings in Bree.\n");
    add_item(({"square building", "adventurer's guild", "adventurers guild"}),
        "The square building is shorter than others in the town. It's a "
        + "simple wooden building, made of rough-hewn logs. Neverthless, it "
        + "looks sturdy. Up under the roof, you see a vent that's indicative of "
        + "an attic. You notice a small grassy path along the north side of "
        + "the building. There is an open door leading east and a " +
        "sign swings from above the door.\n");
    add_item( ({"log", "rough-hewn logs", "logs", "rough logs"}),
        "The logs still have axe marks on them. Whoever build this building didso "
        + "quickly and cheaply. Nevertheless, the logs are straight and the "
        + "gaps between them have been patched up tight. This building "
        + "will stand the test of time.\n");
    add_item("gaps", "There are no gaps. They have been patched.\n");
    add_item( ({"patch", "patched", "patches"}), "The patches seem to be "
        + "made of mud and straw. They will bake hard in the summer sun and "
        + "make a serviceable seal for many years.\n");
    add_item("roof", "Where the roof overhangs the wall, you notice an attic "
        + "vent. On top of the roof, you see a weathermane.\n");
    add_item("weathermane", "The weathermane is made of iron, as best as you "
        + "can tell. It depicts a large chicken standing on an arrow. The "
        + "arrow points to the east, which tells you there is a slight "
        + "breeze coming from Grey Havens to the west.\n");
    add_item("vent", "The vent is small, much too small to crawl through, "
        + "but it is a vent nonthless and so there is a room it services.\n");
    add_item("room", "You see a room to the east.\n");
    add_item("door", "The door is open. Walk on in!\n");
    add_item( ({"path", "grassy path"}), "The path is covered in at least "
        + "ankle high grass. You almost didn't see it there! However, "
        + "it looks like a good path. You could walk along it.\n");
    add_item("wall", "The wall is about head high on a hobbit and made of "
        + "river stones. It's on the west side of the street, opposite "
        + "the square building and the path that runs along side it.\n");
    add_cmd_item( ({"along path", "path"}), ({"walk", "follow"}), "@@follow_path@@");
    
    add_item("sign", 
        "It is square and hangs above the door. A figure of a man, " +
        "straining and lifting a large boulder above his head, is " +
        "painted on the sign.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    set_add_houses();
    set_add_hill();
    reset_shire_room();


    add_exit(ROAD_DIR + "broad07", "northeast");
    add_exit(ROAD_DIR + "broad02", "south");
    add_exit(TOWN_DIR + "adv_guild", "east");

}

string
read_sign()
{
    return "On the sign, above the figure of the man, painted in " +
        "bright silver letters are the words: 'Adventurers Guild " +
        "of Bree'.\n";
}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(human))
    {
        human = clone_object(NPC_DIR + "human");
        human->move(TO);
        human->set_restrain_path("/d/Shire/bree");
        human->set_random_move(2);

    }
}

int
follow_path()
{
    say(QCTNAME(TP) + " follows the path to the north of the square "
        + "building.\n");
    write("You follow the path alongside the north of the square "
        + "building.\n");
    tell_room( (ROAD_DIR + "path1"), QCTNAME(TP) + " arrives "
        + "following the path.\n");
    TP->move_living("M", ROAD_DIR + "path1");
    return 1;
}