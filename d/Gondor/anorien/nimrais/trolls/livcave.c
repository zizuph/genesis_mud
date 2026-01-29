/*
 * /d/Gondor/anorien/nimrais/trolls/livcave.c
 *
 * Coder: Unknown
 *
 * Modification log:
 * Gwyneth, 10/02/02: Updated and cleaned up. Changed inheritance.
 */ 
inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
 
int gFireLit;
object gEagle, gTroll, gTroll2, gTroll3;
 
string exa_fire();
int blocked();
string exa_floor();
string describe();
int test_fire();
void reset_room();

void
create_gondor()
{
    set_short("The living area of a hill-troll lair");
    set_long(&describe());
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(NIMRAIS_DIR + "trolls/prisoncave", "south", &blocked());
    add_exit(NIMRAIS_DIR + "trolls/entrcave", "north");
    add_exit(NIMRAIS_DIR + "trolls/armscave", "northwest", &blocked());
    add_exit(NIMRAIS_DIR + "trolls/cave1", "west");
    add_item(({ "ground","floor","cavefloor" }), &exa_floor());
    add_item("bottles", "There are empty and smashed bottles scattered about " +
        "in the cave. You manage to read the label of one of them: Dorwinion, " +
        "3012.\n");
    add_item("bones", "The bones are of varying size, some of them clearly " +
        "coming from small animals like rabbits, while others look like human " +
        "bones!\n");
    add_item(({ "pallet","pallets" }), "Just some dirty sacks filled with " +
        "smelly straw.\n");
    add_item("fire", &exa_fire());
    add_prop(ROOM_I_LIGHT, &test_fire());
    reset_room();
}
 
string
exa_fire()
{
    if (gFireLit)
        return "The campfire is very primitive, but provides good light in " +
            "the cave.\n";

    return "The campfire is very primitive, but when lit would provide good " +
        "light in the dark cave.\n";
}
 
int
blocked()
{
    object troll = present("troll", TO);

    if(troll && CAN_SEE(troll, TP)  && !TP->query_npc())
    {
        write("The " + troll->query_nonmet_name() + " blocks your way!\n");
        say(QCTNAME(TP) + " tries to leave south, but the " + 
            troll->query_unmet_name() + " stops " + TP->query_objective() + 
            ".\n", TP);
        return 1;
    }

    return 0;
}
 
string
exa_floor()
{
    string floorstr = "You find bones and broken bottles littered on the " +
        "floor of the cave. This is typically the living area of cave or " +
        "hill-trolls. ";

    if (gFireLit)
        floorstr += "A fire is burning in the center of the floor. ";
    else
        floorstr += "You see the remains of an old campfire on the floor. ";

    return (floorstr + "\n");
}
 
string
describe()
{
    string longstr = "You find yourself in a shadowy, smelly cave. This is " +
        "probably what the hill-trolls call home. There are a few rough " +
        "wooden pallets that the trolls must sleep on, and the floor is " +
        "littered with empty and smashed bottles and bones. In the centre of " +
        "the cave is a ";

    if (gFireLit)
        longstr += "primitive fire burning, providing some light. ";
    else
        longstr += "pile of ashes of an extinguished fire. ";

    longstr += "Tunnels lead off to the west, south and northwest, and "+
        "the main entrance seems to be to the north. ";
    return (longstr + "\n");
}
 
int
extinguish(string str)
{
    if (!strlen(str))
    {
        notify_fail("Extinguish what?\n");
        return 0;
    }

    if (str == "fire" || str == "primitive fire" || str == "campfire")
    {
        if (!gFireLit)
        {
            write("The fire is already extinguished.\n");
            return 1;
        }

        write("You extinguish the fire, and it gets darker in here.\n");
        say(QCTNAME(TP) + " extinguishes the fire on the floor, " +
            "and everything gets much darker.\n", TP);
        gFireLit = 0;
        return 1;
    }

    notify_fail("Extinguish what?\n");
    return 0;
}
 
int
test_fire()
{
    return gFireLit;
}
 
void
reset_room()
{
    gTroll = clone_npc(gTroll, NPC_DIR + "hilltroll");
    gTroll2 = clone_npc(gTroll2, NPC_DIR + "hilltroll2");
    gTroll3 = clone_npc(gTroll3, NPC_DIR + "hilltroll3");

    if (!present(gEagle))
    {
        gEagle = clone_object(NIMRAIS_DIR + "quest/obj/corpse");
        gEagle->move(TO);
    }

    gFireLit = 1;
}

int
do_get(string str)
{
    if(!strlen(str) || (str != "bottle" && str != "bottles"))
    {
        NF("Get what?\n");
        return 0;
    }

    write("When you try to pick up one of the bottles, it breaks, and " +
        "the shards scatter all over the floor.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(extinguish,"extinguish");
    add_action(do_get,"get");
}
 
