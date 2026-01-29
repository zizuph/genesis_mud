/*
 * /d/Emerald/telberin/arts/cmasters_door.c
 *
 * This is the door to the Choir Master's chambers in the Arts Quarter
 * of Telberin off of Cantor's Plaza. It is never locked.
 *
 *     Rooms:  /d/Emerald/telberin/arts/cantors_plaza.c
 *             /d/Emerald/telberin/arts/cmasters_chambers.c
 *
 * Copyright (c) May 2000, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/std/door";


/*
 * Function name:        create_emerald_door
 * Description  :        set up the door
 */
public void
create_emerald_door()
{
    set_name("door");
    set_adj( ({ "small", "wooden" }) );
    add_adj( ({ "wood" }) );

    set_short("small wooden door");
    set_long("Though small, the door is made of thick and sturdy wood."
      + " An keyhole is set just below an elegant round knob.\n");

    add_item( ({ "wood", "thick wood", "sturdy wood", "oak" }),
        "The door appears to have been made of oak.\n");
    add_item( ({ "hole", "keyhole", "lock" }),
        "The keyhole is tall and narrow, suggesting the shape of the"
      + " key which operates within it.\n");
    add_item( ({ "knob", "round knob", "elegant knob", "door knob",
                 "doorknob" }),
        "The doorknob has been fashioned from metal and then painted"
      + " black. It seems somewhat smaller than what might be normal.\n");

    add_cmd_item( ({ "door", "wooden door", "small door",
                     "small wooden door", "lock", "keyhole",
                     "hole" }),
                  ({ "unlock", "lock" }),
        "You do not have the proper key.\n");

    set_open(0);
} /* create_emerald_door */


/*
 * Function name: do_pass_door
 * Description:   Move the living through the door,
 *                I redefine it to prevent the idiotic
 *                "Gorboth leaves enter" message.
 */
public void
do_pass_door()
{
    this_player()->move_living("through the door",
        query_other_room());
}
