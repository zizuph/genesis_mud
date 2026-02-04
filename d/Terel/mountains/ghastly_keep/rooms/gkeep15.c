/* /d/Terel/mountains/ghastly_keep/ghastly_keep/rooms/gkeep15.c
 *
 * One of the rooms in the Ghastly Keep.
 *
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */

#include "defs.h";

inherit GKEEP_STD_ROOM;

int dust = 0;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    update_longdesc();

    set_short("End of the path");
    set_long("The path comes to an abrupt halt at the end of a corridor. "
            + "The only exits are either the way you came or through an "
            + "ominous open door on the west wall. On the other side of "
            + "the door there is a staircase leading down into the depths "
            + "of the ruins. There are various symbols on the door that seem "
            + "to shift in the light.\n");

    add_item( ({"door", "wooden", "wooden door"}), "The door is open leading "
               + "into the depths of the ruins. @@check_dust@@.\n");

    add_item( ({"magical", "disturbance"}), "@@see_door@@.\n");

    add_item( ({"symbols", "symbol", "writing"}), "The symbols on the "
               + "door seems to be ever changing, making them impossible "
               + "to decipher.\n");

    add_item( ({"staircase"}), "The staircase leads down into the depths "
               + "of the ruins.\n");

    add_item( ({"wall", "west wall"}), "An open wooden door decorates "
               + "the west wall.\n");

    add_item( ({"dust", "dusts"}), "@@check_dust@@.\n");

    add_cmd_item(({"door", "doors", "wooden door"}), 
                 ({"open", "close", "inspect"}), "@@see_door@@.\n");

    set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast", 
                        "east", "west", "south", "southwest" }),
                        "A wall stops you from walking in that direction.\n");

    set_no_exit_msg( ({ "up", "down" }),
                        "After struggling for a while you find out that is "
                      + "not possible.\n");

    add_exit(GKEEP + "gkeep16",  "east");
    add_exit(GKEEP + "gkeep18",  "down", "@@block_exit@@", 1, 0);

    add_npc(GKEEP_NPC + "g_sentry",   4);
    add_npc(GKEEP_NPC + "g_guardian", 2);

    add_prop(ROOM_I_INSIDE,          1);
    add_prop(ROOM_I_LIGHT,          -1);

    reset_room();
}


/*
 * Function name: set_dust()
 * Description  : Adjusting the dust.
 */
int
set_dust(int i)
{
    dust = i;
}

/*
 * Function name: check_dust()
 * Description  : Change the dust in the room
 */
public string
check_dust()
{

    if (dust)
    {
        return "Fresh footprints made in the dust "
              + "indicates someone has passed through quite recently";
    }

    return "The undisturbed dust on the floor shows that none have passed "
          + "through it in quite some time";
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    update_longdesc();
    set_dust(0);
}

int
can_access_level2(object player) {
    object tracker = present(GKEEP_KILL_TRACKER, player);

    if (!objectp(tracker))
        return 0;

    return tracker->query_level2_access();
}

/*
 * Function name: block_exit()
 * Description  : Block the exit for players without the right prop
 */
int
block_exit(string room)
{

    string race_name;

    if (TP->query_wiz_level())
    {
        TP->catch_msg("\nSpeak, friend, and enter, Mr. Wizard.\n\n");
        set_dust(1);
        return 0;
    }

    if (!can_access_level2(TP))
    {
        tell_room(ENV(TP), QCTNAME(TP)+ " tries to pass the magical "
                 + "disturbance, but fails.\n", TP);
        TP->catch_msg("You do not dare to pass the magical disturbance.\n");
        return 1;  
    }
    else
    {
        tell_room(ENV(TP), QCTNAME(TP)  + " pass through the magical "
                 + "disturbance, with ease.\n", TP);
        TP->catch_msg("You pass through the magical disturbance with ease.\n");
        set_dust(1);
        return 0;
    }
    return 1;
}

/*
 * Function name: see_door()
 * Description  : Change the appearance for players with the right prop
 */
public string
see_door()
{

    if (can_access_level2(TP))
    {
        return "The door is shrouded with a magical disturbance, but you "
              + "could easily open it";
    }

    return "The door is shrouded with a magical disturbance, making you "
          + "unable to open it";
}
