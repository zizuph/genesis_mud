/*
 *  /d/Genesis/login/new/death_chamber.c
 *
 *  This room is where mortals are sent after their conversation with
 *  death, and subsequent rescue by Lars.
 *
 *  Created August 2004, by Cooper Shery (Gorboth)
 */
#pragma strict_types

inherit "/std/room";

#include <files.h>
#include <login.h>
#include <ss_types.h>
#include <stdproperties.h>

/* definitions */
#define TRIED_PORTAL_PROP        "_death_i_tried_portal"

/* prototypes */
public void        create_room();
public int         gate_shut();
public int         door_shut();
public void        reset_room();
public int         do_enter(string arg);
public void        init();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_short("a small room with many exits");
    set_long("You stand in a large circular chamber with exits on all"
      + " sides. To the south a long corridor extends beyond"
      + " your vision. The east and west wall each have three identical"
      + " doorways leading to small rooms. At the center of the chamber"
      + " stands a shimmering blue portal, beside which a column of white"
      + " light rises from the ground. Between the two stands a"
      + " large sign which provides useful information.\n\n");

    add_item( ({ "chamber", "circular chamber", "large chamber",
                 "large circular chamber", "here", "area" }), long);
    add_item( ({ "south", "south wall", "corridor", "long corridor",
                 "hall", "hallway", "long hallway" }),
        "A long corridor travels from the south wall into the"
      + " distance.\n");
    add_item( ({ "east", "east wall", "eastern wall",
                 "west", "west wall", "western wall",
                 "door", "doorway", "doors", "doorways",
                 "three doors", "three doorways", "identical doors",
                 "identical doorways", "closed door", "closed doors",
                 "closed doorways", "three closed doorways",
                 "three closed doors" }),
        "There are three closed doorways in the walls to either side.\n");
    add_item( ({ "north", "north wall", "northern wall" }),
        "The northern wall is featureless.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is illuminated by the shimmering portal and white"
      + " shaft of light.\n");
    add_item( ({ "up", "ceiling", "roof" }),
        "The ceiling of this chamber is high above the floor.\n");
    add_item( ({ "portal", "shimmering portal", "blue portal",
                 "shimmering blue portal", "blue shimmering portal" }),
        "A blue shimmering portal rises from the floor of the chamber."
      + " If you wish to forsake your old body and choose a new one,"
      + " you may <enter portal>. Be warned, however, that doing this"
      + " will strip you of the vast majority of skills you have"
      + " trained. Examine the column of light for an alternative.\n");
    add_item( ({ "column", "light", "column of light", "white light",
                 "column of white light" }),
        "A column of light rises from the floor of the chamber. Within"
      + " the column, your old body floats in a state of suspended"
      + " animation. If you wish to continue inhabiting your previous"
      + " form, you may <enter light>.\n");
    add_item( ({ "body", "old body" }),
        "Seeing your body from the outside is an eerie experience"
      + " to say the least. Nonetheless, you can't help but notice"
      + " how peaceful the body seems to be, floating without"
      + " pain or suffering within the embrace of the column of"
      + " light.\n");

    add_cmd_item( ({ "door", "doorway", "doors" }),
                  ({ "open" }),
        "The doors cannot be opened.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("tutorial/hobbit_chamber", "northeast", door_shut, 1, 0);
    add_exit("tutorial/human_chamber", "east", door_shut, 1, 0);
    add_exit("tutorial/goblin_chamber", "southeast", door_shut, 1, 0);
    add_exit("tutorial/6", "south", gate_shut, 1, 0);
    add_exit("tutorial/gnome_chamber", "southwest", door_shut, 1, 0);
    add_exit("tutorial/elf_chamber", "west", door_shut, 1, 0);
    add_exit("tutorial/dwarf_chamber", "northwest", door_shut, 1, 0);

    reset_room();
} /* create_room */


/*
 * Function name:        gate_shut
 * Description  :        we want to prevent mortals from leaving
 *                       this room. this function provides an explanation
 *                       to the player.
 * Returns      :        int 1
 */
public int
gate_shut()
{
    write("You travel down the southern corridor. However, when you"
      + " get to the end, you find a gate that is shut tight. You"
      + " cannot go that way, so you return to the circular"
      + " chamber.\n");

    return 1;
} /* gate_shut */


/*
 * Function name:        door_shut
 * Description  :        we want to prevent mortals from leaving
 *                       this room. this function provides an explanation
 *                       to the player.
 * Returns      :        int 1
 */
public int
door_shut()
{
    write("The doorway is shut and cannot be opened.\n");

    return 1;
} /* gate_shut */


/*
 * Function name:        reset_room
 * Description  :        add a sign to the room
 */
public void
reset_room()
{
    object   sign;

    if (!present("_tutorial_sign"))
    {
        sign = clone_object("/d/Genesis/login/sign");
        sign->config_sign("sign");
        sign->add_adj( ({ "familiar", "useful", "large" }) );
        sign->add_name("information");
        sign->set_short("large sign");
        sign->move(this_object());
    }

    return;
} /* reset_room */


/*
 * Function name:        do_enter
 * Description  :        Allow players to begin the character creation
 *                       process
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    object ob;
    
    if (!strlen(arg))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[the] [blue] [shimmering] 'portal'"))
    {
        if (this_player()->query_prop(TRIED_PORTAL_PROP))
        {
            write("As you step into the portal, you glimpse your old"
              + " body melding with the column of light, returning to"
                + " the ether.\n");
	    
                        
            /* BEGIN CHARACTER CREATION SEQUENCE HERE */
            this_player()->set_ghost(GP_BODY);
            this_player()->ghost_ready();
            return 1;
        }

        write("Forsake your old body and lose most of your skills? If"
          + " you are sure you want to do this, <enter portal> one more"
          + " time.\n");
        this_player()->add_prop(TRIED_PORTAL_PROP, 1);
        return 1;
    }

    if (parse_command(arg, ({}),
        "[the] [column] [of] [white] 'light'"))
    {
        if (this_player()->query_ghost() & GP_BODY)
        {
            write("You attempt to step into the column of white light, " +
                "but it appears that path is not yet open for you.\n");
            return 1;
        }
        
        write("As you step into the column of light, you feel yourself"
          + " rising into your old body, slowly sending warmth back"
            + " into the cold dead limbs.\n");

        /* Return the player to his old body and into the real world */
        this_player()->set_ghost(0);
        this_player()->ghost_ready();
        return 1;
    }

    notify_fail("You may either <enter portal> or <enter light>."
      + " Examine each for more information.\n");
    return 0;
} /* do_enter */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_enter, "enter");
}

/*
 * Function name: prevent_enter
 * Description  : We don't people to drop anything here, but we do
 *                allow livings, and the board itself.
 * Arguments    : object ob - the object trying to enter.
 * Returns      : int 1/0 - reject if true.
 */
int
prevent_enter(object ob)
{
    if (living(ob) || IS_BOARD_OBJECT(ob) ||
        ob->id("_tutorial_sign"))
        return 0;

    return 1;
}

