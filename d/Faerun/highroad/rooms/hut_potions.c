/*
 * Alchemist hut
 * -- Finwe, November 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_INDOORS_BASE;
inherit "/d/Shire/lib/inn";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

static object hut_npc;

void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("inside a round hut");
    set_extraline("It is round and small like the others. The walls are made of wood stacked on each other. Wind whistles through some cracks in the walls, most of which have been filled. A shelf sits against the wall and a fireplace opposite it, filling the room with warmth and golden light. Hanging from the ceiling is a swinging lamp. A sign is posted on a wall.");

    add_item(({"walls"}),
        "They are made of wood stacked on top of each other. There are chinks in the walls where cold air blows through. The walls look sturdy and have some shelves against them. There is a sign tacked on it.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is peaked and supported by strong beams. Hanging from the beams is a single lamp and some dried plants.\n");
    add_item(({"beams"}),
        "They are squared logs and support the ceiling. Hanging from the beams is a single lamp and many dried plants.\n");
    add_item(({"logs", "squared logs"}),
        "They are large and were hauled up here from the mountains. They are square and support the ceiling.\n");
    add_item(({"plants", "dried plants"}),
        "These are bunches of plants, hanging upside down. They are dried and used to make potions.\n");
    add_item(({"lamp"}),
        "The lamp hangs from the ceiling, casting a warm glow around the room. The lamp is large and and unusually bright.\n");
    add_item(({"shelves"}),
        "The shelves are set against the wall. They are stacked with bowls, vials, and jars.\n");
    add_item(({"bowls"}),
        "They are all sizes and used to hold potions and store things for the alchemist. They are made of ceramic and look well used.\n");
    add_item(({"vials"}),
        "They are small and made of glass. The vials look well used and hold potions. They are stacked neatly on the shelves.\n");
    add_item(({"jars"}),
        "They are all sizes and shapes. They are made of glass and hold a variety of ingredients used by the alchemist. The jars are neatly stacked on the shelves.\n");
    add_item(({"floor", "ground"}),
        "The floor is swept clean. It is made of hard-packed dirt and is oddly warm.\n");

// fireplace
    add_prop(OBJ_I_HAS_FIRE,1);
    add_item("fire",
        "Red and yellow flames dance across logs, filling the " +
        "room with a yellow light and a gentle warmth.\n");
    add_item(({"log", "logs"}),
        "Large logs of maple, oak, and cedar burn brightly " +
        "in the fire.\n");
    add_item("fireplace",
        "The large fireplace sits against a wall and is " +
        "made from large blocks of stone. It is as tall as an " +
        "elf and burns continuously. The fire light fills the " +
        "room a gentle yelllow glow and the warmth comforts " +
        "you. The fireplace has a large brass screen in front of " +
        "it to prevent logs from rolling out and to keep sparks " +
        "inside. A large stone hearth sits in front of the " +
        "fireplace.\n");
    add_item(({"screen", "brass screen", "large brass screen"}),
        "The brass screen is made up of several panels of " +
        "brass. The panels are made of woven brass wires that " +
        "have been stretched across each panel, preventing " +
        "sparks from flying out but allowing light to fill " +
        "the room.\n");
    add_item(({"hearth", "stone hearth", "large stone hearth"}),
        "The stone hearth is made of smooth stones. Its purpose " +
        "is to catch any falling items or errant sparks from " +
        "the fire. The hearth extends a little bit the width of " +
        "the fireplace. It extends out from the fireplace about " +
        "the length of a human. \n");
     add_item("fire irons",
        "These tools are set on the hearth and are used to tend " +
        "the fire and stoke it when necessary. They are made of " +
        "hardened steel and include a shovel, poker, and a set " +
        "of tongs.\n");
    add_item("shovel",
        "Made from hardened steel, the large shovel is used to " +
        "clean the fireplace out. It is about the size of a " +
        "snow shovel with a large mouth for scooping ashes and " +
        "fireplace debris.\n");
    add_item("ashes",
        "The ashes sitting closest to the hot flames are white " +
        "and turn from gray to black the further from the " +
        "flames they are.\n");
    add_item("fireplace debris",
        "Around the edges of the fire you see partially burned " +
        "twigs, sticks, and a few logs.\n");
    add_item(({"partially burned twigs", "partially burned sticks",
                "partially burned logs", "burned logs",
                "burned twigs", "burned sticks"}),
        "They are the remains from yesterday's fire and are " +
        "scattered around the perimeter of the fire. The ends " +
        "are burned.\n");
    add_item("poker",
        "This long pole is made of hardened steel. One end has a " +
        "point and just below the point is a curved claw, " +
        "useful for poking the fire and moving logs around.\n");
    add_item("tongs",
        "This instrument is made of two arms that are joined " +
        "together by a steel pin. The ends of the tongs are " +
        "shaped like claws and are used for grasping logs and " +
        "placing them in the fire or for moving wood around " +
        "within the fireplace. They are made of hardened steel.\n");
    add_item("bellows",
        "The bellows are made of two pieces of smooth wood. " +
        "They are joined together at the front with a strip of " +
        "leather. A tube is set into the center to direct the " +
        "airflow. The sides and back of the instrument are " +
        "joined together with a large piece of tanned hide. " +
        "When pumped, the bellows blow a stream of air into " +
        "the fire, improving the draft of the fire.\n");
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    set_room_tell_time(300);
    add_room_tell("The lamp swings overhead, casting shadows around the room.");
    add_room_tell("A cold breeze blows through a chink in the walls.");
    add_room_tell("A loud pop erupts from the fireplace.");
    add_room_tell("The fire flares up briefly.");
    add_room_tell("A log breaks, sending a shower of sparks flying up the chimney.");
    add_room_tell("The fire flares, filling the room with a dim yellow glow.");
    add_room_tell("The wood burns, slumping further into the fireplace.");
    add_room_tell("The fire slumps down slightly.");
    add_room_tell("Shadows from the flames dance across the room.");

    add_item("sign", "It is large with something written on it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");


    add_exit(HR_DIR + "htr14", "southeast");

    reset_faerun_room();
}

// Sign
string
pricelist_desc()
{
    return "\n"+
        "   0-----------------------------------------0\n"+
        "   |                                         |\n"+
        "   |            Alchemist Shop               |\n"+
        "   |                                         |\n"+
        "   |  These are the items offered for you    |\n"+
        "   |  to aid in your herbing and alchemy.    |\n"+
        "   |  <pay for 'item'> to purchase an item.  |\n"+
        "   |                                         |\n"+
        "   |  Black stone bowl . . . . 9 gc          |\n"+
        "   |  Vials                                  |\n"+
        "   |  -------------------------------------  |\n"+
        "   |  Bat, Bell, Bloody-head, Demon-face,    |\n"+
        "   |  Lightning bolt, Skull, Spider          |\n"+
        "   |                                         |\n"+
        "   |  All vials cost 3 sc each.              |\n"+
        "   |                                         |\n"+
        "   |  You may 'list potions' if the alche-   |\n"+
        "   |  mist is available.                     |\n"+
        "   |                                         |\n"+
        "   0-----------------------------------------0\n\n";
}


void
reset_faerun_room()
{
    if (!hut_npc)
        hut_npc = clone_object(NPC_DIR + "hut_potions");
    if (!present(hut_npc,this_object()))
        hut_npc->move(this_object());
}

void
init()
{
    ::init();
    init_shire_inn();
}

int
do_read(string str)
{
    if (!str)
        return 0;
    if (member_array(str, PRICELIST_ID) == -1)
        return 0;
    write(pricelist_desc());
    return 1;
}

