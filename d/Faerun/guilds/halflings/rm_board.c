/*
 * Private board room of rhe Halflings guild
 * Finwe, September 2015
 */

#pragma save_binary
#pragma strict_types

#include "halflings.h"
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>

inherit GUILD_ROOMS;

void reset_room()
{
    ::reset_room;

}

void create_guild_room()
{
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    setuid();
    seteuid(getuid());

    object board;

    set_short("Discussion Room");
    set_long("This is the discussion room of the Halflings. It is here " +
        "they gather to discuss their travels with each other and what " +
        "they have learned. A large fireplace is set against the back " +
        "wall, filling the room with warmth. Candles are spread around " +
        "the room with golden light. A large bulletin board is set against " +
        "a wall.\n");

    add_prop(OBJ_I_HAS_FIRE,1);
    add_item("mantel",
        "This is a long, wide mantel. It is made of granite and sits " +
        "above the fireplace.\n");
    add_item("fire",
        "Red and yellow flames dance across logs, filling the room with a " +
        "yellow light and a gentle warmth.\n");
    add_item(({"log", "logs"}),
        "Large logs of maple, oak, and cedar burn brightly in the fire.\n");
    add_item("fireplace",
        "The large fireplace sits against a wall and is made from large " +
        "blocks of stone. It is as tall a and burns continuously. The fire " +
        "light fills the room a gentle yelllow glow and the warmth comforts " +
        "you. The fireplace has a large brass screen in front of it to " +
        "prevent logs from rolling out and to keep sparks inside. A large " +
        "stone hearth sits in front of the fireplace.\n");
    add_item(({"screen", "brass screen", "large brass screen"}),
        "The brass screen is made up of several panels of brass. The panels " +
        "are made of woven brass wires that have been stretched across " +
        "each panel, preventing sparks from flying out but allowing light " +
        "to fill the room.\n");
    add_item(({"hearth", "stone hearth", "large stone hearth"}),
        "The stone hearth is made of smooth stones. Its purpose is to catch " +
        "ny falling items or errant sparks from the fire. The hearth extends " +
        "a little bit the width of the fireplace. It extends out from " +
        "the fireplace about the length of a human.\n");
     add_item("fire irons",
        "These tools are set on the hearth and are used to tend the fire " +
        "nd stoke it when necessary. They are made of hardened steel and " +
        "include a shovel, poker, and a set of tongs.\n");
    add_item("shovel",
        "Made from hardened steel, the large shovel is used to clean the " +
        "fireplace out. It is about the size of a snow shovel with a large " +
        "mouth for scooping ashes and fireplace debris.\n");
    add_item("ashes",
        "The ashes sitting closest to the hot flames are white and turn " +
        "from gray to black the further from the flames they are.\n");
    add_item("fireplace debris",
        "Around the edges of the fire you see partially burned twigs, " +
        "sticks, and a few logs.\n");
    add_item(({"partially burned twigs", "partially burned sticks",
                "partially burned logs", "burned logs", 
                "burned twigs", "burned sticks"}),
        "They are the remains from yesterday's fire and are scattered " +
        "around the perimeter of the fire. The ends are burned.\n");
    add_item("poker",
        "This long pole is made of hardened steel. One end has a point " +
        "and just below the point is a curved claw, useful for poking the " +
        "fire and moving logs around.\n");
    add_item("tongs",
        "This instrument is made of two arms that are joined together by a " +
        "steel pin. The ends of the tongs are shaped like claws and are " +
        "used for grasping logs and placing them in the fire or for " +
        "moving wood around within the fireplace. They are made of hardened " +
        "steel.\n");
    add_item("bellows",
        "The bellows are made of two pieces of smooth wood. They are joined " +
        "together at the front with a strip of leather. A tube is set into " +
        "the center to direct the airflow. The sides and back of the " +
        "instrument are joined together with a large piece of tanned hide. " +
        "When pumped, the bellows blow a stream of air into the fire, " +
        "improving the draft of the fire.\n");

    if (!objectp(board))
    {
        board = clone_object("/std/board");
        board->set_board_name(HALFGLD_DIR + "pri_board");
        board->set_num_notes(30);
        board->set_silent(1);
        board->set_show_lvl(1);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str("You may not do that.\n");
        board->move(this_object());
    }

    reset_room();

    add_exit(HALFGLD_DIR + "rm_join", "north");
    add_exit(HALFGLD_DIR + "rm_start", "south");
    
}

void 
init()
{
    ::init();
}
