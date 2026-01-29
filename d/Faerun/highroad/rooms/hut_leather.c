/*
 * Nov hut to sell foods and drinks
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

    set_short("inside a sturdy hut");
    set_extraline("The hut is small and made of wood, and sturdier than the others. The ceiling is peaked and has a single lamp swinging from it. A fireplace is set against a wall, warming the hut and filling it with golden light. Animal skins and a sign are tacked on the walls. A large work table sits against another wall.");

    add_item(({"walls"}),
        "They are made of wood stacked on top of each other. There are chinks in the walls where cold air blows through. The sturdy walls have animal skins and a sign tacked on them.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is peaked and supported by strong beams. Hanging from the beams is a single lamp\n");
    add_item(({"beams"}),
        "They are squared logs and support the ceiling. Hanging from the beams is a single lamp. It swings back and forth, casting light everywhere.\n");
    add_item(({"logs", "squared logs"}),
        "They are large and were hauled up here from the mountains. They are square and support the ceiling.\n");
    add_item(({"animals", "animal skins", "skins"}),
        "These are the skins of animals with the hair removed. They have been tanned and will turned into various leather items for sale.\n");
    add_item(({"lamp"}),
        "The lamp hangs from the ceiling, casting a warm glow around the room. The lamp is large and and unusually bright.\n");
    add_item(({"floor", "ground"}),
        "The floor is swept clean. It is made of hard-packed dirt and is oddly warm.\n");
    add_item(({"table", "work table", "workbench"}),
        "The table is made of wood and sits against a wall. It's scratched and stained from many years of tanning leathers.\n");    

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
    add_item("sign", "It is large with something written on it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");

    set_room_tell_time(300);
    add_room_tell("The lamp swings overhead, casting shadows around the room.");
    add_room_tell("A cold breeze blows through a chink in the walls.");


    configure_shire_inn();

    add_exit(HR_DIR + "htr14", "west");

    reset_faerun_room();
}

string
pricelist_desc()
{
    return "\t+----------------------------------------------------+\n"+
        "\t|                                                    |\n"+
        "\t|                  Container Shop                    |\n"+
        "\t|                                                    |\n"+
        "\t|    The best bags and packs are made here by the    |\n"+
        "\t|    local tanner. Though he mostly in leather, he   |\n"+
        "\t|    also uses other materials to make his wares.    |\n"+
        "\t|                                                    |\n"+
        "\t|    A well-used leather tote . . . . 4 gc  6 sc     |\n"+
        "\t|    Used to carry body parts                        |\n"+ 
        "\t|                                                    |\n"+
        "\t|    A soft leather satchel . . . . . 3 gc  6 sc     |\n"+
        "\t|    Designed to hold spell components               |\n"+
        "\t|                                                    |\n"+
        "\t|    A soft leather pouch . . . . . . 3 gc  6 sc     |\n"+
        "\t|    Used to hold herbs                              |\n"+
        "\t|                                                    |\n"+
        "\t|    A travel-stained canvas pack . . 4 gc  8 sc     |\n"+
        "\t|    For holding storing everything you carry        |\n"+
        "\t|                                                    |\n"+
        "\t|    A black leather bag. . . . . . . 6 gc  6 sc     |\n"+
        "\t|    Will hold all your gems                         |\n"+
        "\t|                                                    |\n"+
        "\t|    A large leather purse. . . . . . 6 gc  6 sc     |\n"+
        "\t|    Used to hold all your coins                     |\n"+
        "\t|                                                    |\n"+
        "\t+----------------------------------------------------+\n\n";
}

void
reset_faerun_room()
{
    if (!hut_npc)
        hut_npc = clone_object(NPC_DIR + "hut_leather");
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

int
do_order(string str)
{

    if (!hut_npc || !present(hut_npc))
    {
        notify_fail("There is no one here to buy anything from.\n"+
          "She is gone for now.\n");
        return 0;
    }

    return ::do_order(str);
}

mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    switch (item_name)
    {
    case "tote":
    case "totes":
    case "leather tote":
    case "leather totes":
    case "well-used leather tote":
    case "well-used leather totes":
        order = clone_object("/d/Faerun/obj/tote");
        price = 648;
        break;
    case "satchel":
    case "satchels":
    case "leather satchel":
    case "leather satchels":
    case "soft leather satchel":
    case "soft leather satchelss":
        order = clone_object("/d/Faerun/obj/satchel");
        price = 504;
        break;
    case "pack":
    case "pack":
    case "canvas pack":
    case "canvas packs":
    case "travel-stained canvas pack":
    case "travel-stained canvas packs":
    case "backpack":
    case "backpack":
    case "canvas backpack":
    case "canvas backpacks":
    case "travel-stained canvas backpack":
    case "travel-stained canvas backpacks":
        order = clone_object("/d/Faerun/obj/backpack");
        price = 504;
        break;
    case "bag":
    case "bags":
    case "leather bag":
    case "leather bags":
    case "black leather bags":
    case "black leather bag":
        order = clone_object("/d/Faerun/obj/bag");
        price = 936;
        break;
    case "purse":
    case "purses":
    case "leather purse":
    case "leather purses":
    case "large leather purse":
    case "large leather purses":
        order = clone_object("/d/Faerun/obj/purse");
        price = 936;
        break;
    case "pouch":
    case "soft leather pouch":
    case "leather pouch":
    case "soft pouch":
        order = clone_object("/d/Faerun/obj/herb_pouch");
        price = 504;
        break;

    }
    return (({order}) + ({price}));
}

int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

        write("You cannot go there yet.\n");
    return 1;
}
