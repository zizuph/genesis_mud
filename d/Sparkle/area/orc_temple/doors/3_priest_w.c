/*
 *  /d/Sparkle/area/orc_temple/doors/3_priest_w.c
 *
 *  This is the west side of the door to the High Priest's chamber
 *  on the 3rd Level of the Sparkle Dungeons.
 *
 *  Created August 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit DOORS_DIR + "dungeon_door";

/* Prototypes */
public void        create_dungeon_door();


/*
 * Function name:        create_dungeon_door
 * Description  :        constructor for the door object
 */
public void
create_dungeon_door()
{
    ::create_dungeon_door();

    set_door_id("3_priest");
    set_pass_command( ({ "e" ,"east" }) );
    set_door_name( ({ "door", "polished door", "cedar door",
                      "polished cedar door",
                      "doorway", "polished doorway", "cedar doorway",
                      "polished cedar doorway",
                      "east door", "eastern door",
                      "east doorway", "eastern doorway",
                      "door to the east", "doorway to the east" }) );

    set_open_desc("There is an open polished cedar door leading east.\n");
    set_closed_desc("There is a closed polished cedar door leading east.\n");

    set_fail_pass("The polished cedar door is closed.\n");
    set_open_mess( ({ "opens the polished cedar door.\n",
                      "The polished cedar door opens.\n" }) );
    set_close_mess( ({ "closes the polished cedar door.\n",
                       "The polished cedar door closes.\n" }) );

    set_door_desc("A polished cedar door is set within an alcove"
      + " in the eastern wall of the tunnel here. The door is of"
      + " distinctly finer craftsmanship than just about anything"
      + " else you have seen in the dungeons. An ornamented door"
      + " handle can be used to open or close it.\n");

    add_item( ({ "door handle", "handle", "ornamented handle",
                 "ornamented door handle" }),
        "Arcane symbols are etched into the door handle.\n");
    add_item( ({ "symbols", "arcane symbols", "symbol",
                 "arcane symbol" }),
        "The symbols are not very clear. A great deal of grease and"
      + " filth has coated them.\n");
    add_item( ({ "grease", "filth" }),
        "Orcs must not wash their hands very often.\n");
    add_cmd_item( ({ "symbol", "symbols", "arcane symbol",
                     "arcane symbols", "handle", "ornamented handle",
                     "door handle", "ornamented door handle",
                     "grease", "filth" }),
                  ({ "clean", "wash", "polish" }),
        "The grime is embedded. No amount of cleaning will help.\n");
    add_item( ({ "keyhole", "thin keyhole", "lock", }),
        "This door appears to have neither lock or key.\n");

    set_other_room(ROOMS_DIR + "3_chambers");

    set_open(0);
    set_locked(0);
} /* create_dungeon_door */