/*
 *  /d/Sparkle/area/orc_temple/1_hall6.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
 *
 *  Created August 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    add_name("_runt_key_guard");

    set_short("in a long north-south corridor");
    set_long("This dank corridor heads a ways to the south where"
      + " it trails into the gloom. A short distance to the north, you"
      + " can faintly make out a turn to the west.\n\n");

    try_item( ({ "turn", "turn to the west" }),
        "You'd have to head north for a clearer view.\n");
    try_item( ({ "dank corridor", "north-south corridor" }),
        "This corridor stretches on to the north and south.\n");
    try_item( ({ "gloom" }),
        "It is a depressing sight.\n");
    try_item( ({ "corridor", "dank corridor", "long corridor",
                 "north-south corridor",
                 "long north-south corridor" }),
        "There are a lot of spider webs clinging to the corridor"
      + " here.\n");
    try_item( ({ "web", "webs", "spider webs" }),
        "There are plenty of webs, but where are the spiders?\n");
    try_item( ({ "spider", "spiders" }),
        "For so many webs, it seems strange that the spiders should"
      + " be missing. Perhaps someone has taken them?\n");
    add_cmd_item( ({ "web", "webs", "spider webs" }),
                  ({ "search" }),
        "You search through the spider webs, and find an old oven"
      + " mit tangled in one of the thicker clumps of the silk.\n");
    try_item( ({ "silk", "spider silk", "spiders silk",
                 "spider's silk" }),
        "Spiders silk is sometimes beautiful. This stuff is coated"
      + " with filthy dust and grime.\n");
    try_item( ({ "dust", "grime", "filthy dust",
                 "filthy dust and grime" }),
        "Looks sort of like a pirate's dreadlocks.\n");
    try_item( ({ "dreadlock", "dreadlocks", "pirate's dreadlocks",
                 "pirates dreadlocks" }),
        "Arrrrrrrrr ...\n");
    try_item( ({ "mit", "oven mit", "old oven mit" }),
        "The oven mit looks to have been lost here by whoever was after"
      + " the spiders. Hmmm ... what could it all mean?\n");
    try_item( ({ "clump", "clumps", "thick clump", "thick clumps",
                 "thicker clump", "thicker clumps" }),
        "Yuck.\n");
    add_cmd_item( ({ "oven mit", "mit", "old oven mit" }),
                  ({ "get", "remove", "take" }),
        "The oven mit is held fast by the web.\n");
    add_cmd_item( ({ "mit", "mit from web", "mit out of web",
                     "the mit", "the mit from web", "the mit out of web",
                     "the mit from the web", "the mit out of the web",
                     "mit from the web", "mit out of the web" }),
                  ({ "cut" }),
        "The webs seem to be too thick to cut.\n");
    add_cmd_item( ({ "web", "spider web", "spider's web",
                     "spider webs", "web with torch",
                     "webs with torch", "spider web with torch",
                     "spider's web with torch",
                     "spider webs with torch" }),
                  ({ "burn", "ignite" }),
        "The webs refuse to catch fire.\n");
    

    add_dungeon_items();

    add_npc(NPC_DIR + "goblin_runt", 3 + (random(3)), &->arm_me());
    add_npc(NPC_DIR + "tough_runt", 1, &->arm_me());

    add_exit("1_hall5", "north");
    add_exit("1_hall7", "south");

    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest", "west" }),
        "You boldly stroll directly into a wall. OOOF!\n");

    room_add_object(DOORS_DIR + "1_armour_w");

    /* If the other room isn't loaded, it can bug when a player tries
     * the exit for the first time, so lets make sure it is loaded.
     */
    (ROOMS_DIR + "1_armoury")->teleldeningsanka();
    
} /* create_dungeon_room */
