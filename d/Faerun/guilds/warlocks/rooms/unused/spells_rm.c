/* /d/Faerun/guilds/warlocks/rooms/spell_rm.c
 *
 * Spells room where players learn spells
 * Finwe, May 2017
 *
 */

#include "/d/Faerun/defs.h"
#include "defs.h";
#include "../guild.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>

inherit WARLOCK_STD_ROOM;

/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A room of learning");
    set_long("This dark room is lit by a large candle set on a workbench " +
        "and a fireplace against a wall. The room is bare except for " +
        "a bookshelf against a wall, and a workbench in the center " +
        "of the room. A cauldron sits on the workbench next to a weathered " +
        "book. A large arch leads south to the library.\n");

    add_domed_ceiling();
    add_ground_plain();
    add_indoor_tells();

// fireplace
    add_prop(OBJ_I_HAS_FIRE,1);
    add_item("fire",
        "Red and yellow flames dance across logs, filling the " +
        "room with a yellow light and a gentle warmth.\n");
    add_item(({"log", "logs"}),
        "Large logs of maple, oak, and cedar burn brightly " +
        "in the fire.\n");
    add_item("fireplace",
        "The large fireplace sits against a wall and is made from large " +
        "blocks of stone. It is as tall as an elf and burns continuously. " +
        "The fire light fills the room with a gentle yellow glow. The " +
        "fireplace has a large brass screen in front of it to prevent " +
        "logs from rolling out and to keep sparks inside. A large stone " +
        "hearth sits in front of the fireplace.\n");
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
        "the length of a human.\n");
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
    add_room_tell("The flames in the fireplace dance, casting shadows " +
        "around the room.");
    add_room_tell("A loud pop erupts from the fireplace.");
    add_room_tell("The fire flares up briefly.");
    add_room_tell("A log breaks, and a shower of sparks flies up the chimney.");
    add_room_tell("The fire flares, filling the room with a dim yellow glow.");
    add_room_tell("The wood burns, slumping further into the fireplace.");
    add_room_tell("The fire slumps down slightly.");
    add_room_tell("Shadows from the flames dance across the room.");

    add_item(({"walls"}),
        "The walls are empty and bare. A bookshelf sits against one wall, " +
        "and a fireplace against another.\n");
    add_item(({"shelf", "bookshelf"}),
        "The bookshelf is large and sturdy looking. It sits against " +
        "a wall and hold many things used for spellcasting such as " +
        "candles, bowls, cauldrons, and some bones.\n");
    add_item(({"candles"}),
        "They sit on a pile on the bookshelf. The candles look well " +
        "used and many colors. A large candle sits on the workbench, " +
        "casting shadows around the room.\n");
    add_item(({"bowls", "bowl"}),
        "The bowls are stacked on the bookshelf and are all sizes. " +
        "They look dirty and well used, and are used to mix components " +
        "for spells.\n");
    add_item(({"cauldron", "cauldrons"}),
        "They are kettles used for brewing potions. The large ones " +
        "sit on the bottom shelf, and the smaller ones sit on the " +
        "upper shelves. A battered cauldron sits on the workbench.\n");
    add_item(({"workbench", "table"}),
        "It is long and heavy looking. The workbench sits in the center " +
        "of the room. It is made of wood, and stained from constant use. " +
        "A large candle sits on the workbench, next to a weathered " +
        "book an a cauldron.\n");
    add_item(({"battered cauldron"}),
        "It is a medium sized kettle and sits on the workbench. It is " +
        "well used and looks a little battered from constant use.\n");
    add_item(({"bones", "skull", "skulls", "femurs", "femur"}),
        "They look weathered and look human. They sit on the shelf and " +
        "are probably used for incantations. \n");
    add_item(({"large candle"}),
        "It is a tall candle and made of beeswax. It burns and casts an " +
        "eerie glow acrossed the workbench.\n");
    add_item(({"arch"}),
        "It is large and graceful looking. The arch is set in the " +
        "south wall and leads out to the library.\n");

    add_exit(WARLOCK_ROOMS_DIR + "library", "south");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}