/*
 *  /d/Sparkle/guilds/new_merc/rooms/path4.c
 *
 *  Within the grounds of the Mercenary Guild just south of the
 *  sawmill, within which players may join the guild. This room is
 *  open to non-members.
 *
 *  Created April 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;


/* Prototypes */
public void        create_merc_room();


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("just south of an old sawmill within the grounds of the"
      + " Mercenary Guild");
    set_long("The path turns here, travelling west through a guarded"
      + " fence around the north side of the lodge or back south toward"
      + " the center of the camp. The old sawmill stands just north"
      + " of the path, a few guards standing warily at each side of"
      + " its entrance.\n\n");

    try_item( ({ "mill", "sawmill", "small building",
                 "smaller building", "saw mill", "old sawmill" }),
        "The sawmill is directly to the north. Derelict from its old"
      + " duties in the glory days of the sawmill, it acts now as a"
      + " recruitment office for the Mercenary Guild. A few able-looking"
      + " guards stand at the ready before the entrance, eyeing you"
      + " up and down with faces that tell you nothing of what they"
      + " might be thinking.\n");
    try_item( ({ "north" }),
        "The old sawmill is north of here. Within, you might be able"
      + " to join up as a Mercenary, if you wish.\n");
    try_item( ({ "west", "fence", "guarded fence" }),
        "A fence of criss-crossed sharpened poles has been placed along"
      + " the access route between the mill and the lodge where the"
      + " path turns to the west here. It doesn't look as if anyone"
      + " who is not welcome will be able to get past that blockade"
      + " very easily.\n");
    try_item( ({ "pole", "poles", "sharpened pole", "sharpened poles",
                 "criss-crossed poles", "criss-crossed sharpened poles",
                 "blockade", "route", "access route" }),
        "The fence clearly means business. No one is going through"
      + " that without first getting permission.\n");
    try_item( ({ "able-looking mercenary", "able-looking mercenaries",
                 "able-looking guard", "able-looking guards" }),
        "Able indeed! If you are not already a member of this fine"
      + " establishment, perhaps within the mill you might find a new"
      + " occupation to futher you on your path to glory.\n");
    try_item( ({ "south" }),
        "South, the path heads to the center of the camp, just beside"
      + " the lodge.\n");
    try_item( ({ "recruitment office", "office" }),
        "The life of a Mercenary offers so many opportunities, the"
      + " draw has made it necessary for an entire building to become"
      + " dedicated to prospective members, it seems. Perhaps there is"
      + " something here for you, too?\n");

    add_river_view();
    add_bridge_view();
    add_outdoor_view();
    add_lodge_view();
    add_mill_view();

    add_exit("wep_train", "west", &check_merc_access(), 1, 0);
    add_exit("join", "north");
    add_exit("path3", "south");

    set_no_exit_msg( ({ "northwest", "southwest" }),
        "The sharp poles of the fence prevent your movement.\n");
    set_no_exit_msg( ({ "northeast", "east" }),
        "You wander around the corner of the mill, but find nothing"
      + " of interest, and return to the path.\n");
} /* create_merc_room */
