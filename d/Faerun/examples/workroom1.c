/*
 * This is a more detailed workroom
 * Finwe, November 2016
 */

// this is the standard workroom file
inherit "/std/workroom";
// this lets the room do random noises or actions
inherit "/d/Faerun/std/room_tell";

// always include /d/Faerun/defs.h in all files. Has basic defs
#include "/d/Faerun/defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#define MIRROR_ID   ("mirror")
#define TRASHCAN_ID ("trashcan")
#define MANTEL_ID   ("GH_mantel")

int check_exit();

void create_workroom()
{
    set_short("A large workroom");  // no period needed in short descriptions
    set_long("This large room is paneled in dark wood. The floor is covered " +
        "with a large carpet, which looks plush and luxuriant. A fireplace " +
        "is set against a far wall. It is large enough so that a human could " +
        "comfortablely stand in it. An ornate, brass grate surrounds it. " +
        "Above the fireplace is a large mantel. Knick knacks of all sorts " +
        "are scattered across the mantel. A mirror hangs above it.\n");

// describes parts of the room
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
        "fireplace and a mantel sits above it.\n");
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

    add_item(({"walls", "paneled walls"}),
        "The walls are maded from dark panels of wood. They are rich " +
        "looking and polished to a rich, brown color. The wood is rich " +
        "looking and has a fine grain. Light reflects from the walls, " +
        "casting a honey-colored glow.\n");
    add_item(({"floor", "ground"}),
        "The floor is covered by a plush carpet.\n");
    add_item(({"ceiling"}),
        "The ceiling is domed and rises above you. It has ribs that arch " +
        "inward to the center of the dome. Between the panels are arched " +
        "panes of glass.\n");
    add_item(({"dome"}),
        "The dome is round and dominates the ceiling. It is made of panes " +
        "of glass set between stone ribs. The glass is clear and floods " +
        "the room with soft light.\n");

// every 60 seonds, the room will do one of these actions.
    set_room_tell_time(60);
    add_room_tell("A loud pop erupts from the fireplace.");
    add_room_tell("The fire flares up briefly.");
    add_room_tell("A log breaks, sending a shower " +
        "of sparks flying up the chimney.");
    add_room_tell("The fire flares, filling the room with " +
        "a dim yellow glow.");
    add_room_tell("The wood burns, slumping further into the " +
        "fireplace.");
    add_room_tell("The fire slumps down slightly.");
    add_room_tell("Shadows from the flames dance across the " +
        "room.");

// sets the room to have 1 level of light
    add_prop(ROOM_I_LIGHT, 1);
// prevents attacks in the room
    add_prop(ROOM_M_NO_ATTACK, "No fighting allowed here.\n");
// prevents attacks by magic
    add_prop(ROOM_I_NO_MAGIC_ATTACK,"No magical attacks here.\n");
// this room has an object with fire in it
    add_prop(OBJ_I_HAS_FIRE,1);

// have the room reset itself periodically
    reset_workroom();

    add_exit("@@goto_start", "startloc", 0);
    add_exit("/d/Genesis/start/human/town/tower", "sparkle");
// This exit will be hidden and only wizards can enter it
    add_exit("/d/Genesis/wiz/green","island",check_exit(), 1, 1);
}


void
init()
{
    ::init();
    add_action("do_emote", "emote");
}

// This lets mortals do free emotes in this room.
int
do_emote(string arg)
{
    NF("Emote what?\n");
    if (!arg)
        return 0;
    else
    {
        say( QCTNAME(TP) + " " + arg + "\n");
        write("You emote: " + arg + "\n");
    }
    return 1;
}

// prevents mortals from using certain exits.
int 
check_exit()
{
        if(TP->query_wiz_level())
                return 0;
        write("The branches prevent you from going that way.\n");
        return 1;
}

public void
reset_workroom()
{
    object mirror;

// when room is reset, if mirror not in room, clone it
    if (!objectp(present(MIRROR_ID)))
    {
        // adds the object to the room
        room_add_object("/doc/examples/obj/mirror");
    }

    if (!objectp(present(TRASHCAN_ID)))
    {
        room_add_object("/d/Faerun/examples/obj/trashcan");
    }
 
    if (!objectp(present(MANTEL_ID)))
    {
        room_add_object("/d/Faerun/examples/obj/mantel");
    }

}

public void
enter_inv(object ob, object from)
{
    if (sizeof(query_room_tells()))
	start_room_tells();
    ::enter_inv(ob,from);
}
