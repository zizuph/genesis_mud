// file name:        /d/Avenir/rangorn/temp/camp_base.c
// creator(s):       Lilith, Oct '96  (Rangorn, Feb 97)
// revisions:
// purpose:
// note:             This file is to be inherited in all camp rooms.
//                   The more frequent add_items should be entered
//                   here.
// bug(s):
// to-do:

#pragma strict_types
#include "../holm.h";

inherit "/d/Avenir/inherit/room";
inherit "/d/Avenir/inherit/room_tell";

/*
 * Function name: create_camp_room
 * Description:   This function should be used for creating camp rooms.
 */
void
create_camp_room()
{
}

public void
create_domain_room()
{
    set_area("t_campp");
    set_tell_time(200);

   /* Tells made to player when a room is occupied */
    add_tell("You are suddenly overcome by the horrible " +
             "smell and feel a strong urge to puke.\n");
    add_tell("From somewhere nearby you can hear a scream.\n");
    add_tell("A brisk breeze makes the leaves on the thorn bushes "+
        "rustle like the rush of waves on a beach.\n");
    add_tell("There is an odd chattering coming from the bushes.\n");
    add_tell("A refreshing puff of wind taunts your nose with "+
             "the scent of sea-salt.\n");

    /* If an add_item will be in every room, add it here */
    add_cmd_item("air", "smell", "The air is hard to breathe. You "+
        "feel a bit sick when you inhale.\n");

    /* There is light in this area (see ~Avenir/common/common.h
     * for this define and the one following) */
    LIGHT;
    /* Though this is 'open' area, we are still in a big cavern,
     * so we are still 'inside' */
    IN; 

    add_item(({"tent"}), "There is a tent of sorts leaning against "+
        "the cliff wall.\n");
    add_item("smoke", "It hangs over the camp, an ominous shroud.\n");
    create_camp_room();
}
static void
add_bushes()
{
    add_item(({"bush", "bushes", "brush", "undergrowth", "vegetation"}),
        "The brush is composed almost entirely of thorny bushes that "+
        "appear to be as hostile as the rest of the environment.\n");
}

static void
add_ground()
{
    add_item(({"ground", "dirt", "gravel"}),
       "The ground is composed of a thin layer of dirt and gravel "+
       "on top of granite bedrock. It seems that "  +
       "vegetation is having a hard time growing here.\n");
    add_item(({"cliff", "cliff wall", "wall"}),
        "This cliff is part of a large wall of stone that curves "+
        "from southeast to the northeast.\n");
    add_item(({"hay"}), "It has been spread on the ground, probably "+
        "as a primitive sort of bedding.\n");
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}
