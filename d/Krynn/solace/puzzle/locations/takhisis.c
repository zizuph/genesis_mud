/* The Takhisis room. ~solace/puzzle/locations/takhisis */

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

inherit ROOM_DEFS;

void reset_puzzle_room()
{
    room_add_object(OBJECTS + "control_panel");
}

void create_puzzle_room()
{
    set_short("The Takhisis room");
    set_long("You find yourself in a roughly-hewn cave-like chamber, round "+
        "in proportions. It's not too easy to see here, as the only light "+
        "comes from a solitary torch, flickering from inside a barred recess "+
        "of a nearby wall. You can see well enough to realize that there is "+
        "a small hole in the ceiling and an arched doorway leading west.\n");

    add_item(({"doorway", "arched doorway", "exit"}), "An exit from this "+
        "room to the room west of here. You see nothing more of interest.\n");

    add_item(({"room", "chamber", "roughly-hewn chamber", "cave-like chamber",
        "roughly-hewn cave-like chamber"}), "The room in which you are "+
        "standing. (Try typing 'look').\n");

    add_item(({"recess", "barred recess"}), "An area of the cave walls that "+
        "has been cut out so that a torch can be placed inside to light the "+
        "room somewhat. It is barred so that the aforementioned torch cannot "+
        "be reached.\n");

    add_item(({"wall", "walls"}), "The walls are of rough and irregular "+
        "stone, misshapen and without much attempt at form. This may just "+
        "be a natural underground cave. In one of the nearby walls is a "+
        "barred recess from which a faint glow emanates.\n");

    add_item(({"ceiling", "hole", "small hole"}), "The ceiling is made of "+
        "the same cold stone as the walls and is just as featureless, with "+
        "the exception of a small shadow-cast hole about as large as a "+
        "brandy cask. It is too small to squeeze through, but you may be "+
        "able to poke your head through and look into it.\n");

    add_item(({"torch", "solitary torch"}), "A softly glowing torch, "+
        "crackling and giving off a shifting red glow that barely lights "+
        "the room enough for you to be able to see properly. It has been "+
        "placed in a barred recessed niche in the wall so that nobody can "+
        "reach in and take it.\n");

    reset_puzzle_room();
}

void init()
{
    ::init();

    add_action("do_look", "look");
}

int do_look(string str)
{
    string pstr = "'in' / 'into' [the] [small] 'hole' [in] [the] [ceiling]";

    if(!strlen(str))
        return 0;

    if(!parse_command(str, TP, pstr))
        return 0;
    else
    {
        if(query_prop(OBJ_I_LIGHT) > 85)
            TP->catch_msg("\nYou poke your head through the hole in the "+
                "ceiling and can just see well enough to make out the dull "+
                "gleam of a metallic object.\n");
        else
            TP->catch_msg("\nYou poke your head through the hole in the "+
                "ceiling but can see nothing but shadows. It is too dark.\n");

        tell_room(TO, QCTNAME(TP)+" pokes "+POSSESSIVE(TP)+" head through "+
            "the hole in the ceiling.\n", TP);
    }
    return 1;
}
