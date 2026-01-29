/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/east_overlook.c
 *
 *  An overlook rises above the pass to Del Rimmon here, where the
 *  troops of Formandil were able to monitor any movement in or out
 *  of the valley. Just behind this ledge is the entrance to the southern
 *  outpost which was constructed to guard the lake.
 *
 *  Copyright (c) February 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/west_overlook";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public void        reset_room();
public void        leave_inv(object ob, object to);
public int         door_exit();
public int         corporeal_flux(object player);
public void        end_flux(object player);
public int         say_password(string arg);
public void        init();


/*
 * Function name:       create_del_rimmon
 * Description :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    set_cliff_base(DELRIMMON_DIR + "lakeside/pathway2");
    set_short("on a landing, overlooking a path below");
    set_long(del_rimmon_long);

    set_extraline("Hugging the eastern walls of rock, a wide landing"
      + " serves as an overlook to a pathway far below. At one time,"
      + " it appears as if this was some kind of fortification by"
      + " which a watch was placed on the pass."
      + " A wall runs along the edge of the landing,"
      + " broken only by a small opening which joins a stairway"
      + " leading down to the pathway. To the east, a stone doorway"
      + " of some kind is set in the rock walls. A small pathway"
      + " leads further upwards to the southeast.");

    add_item( ({ "rock" }),
        "The rock has been carved to house a stone doorway.\n");
    add_item( ({ "wall", "walls" }),
        "Do you wish to examine the wall along the ledge, or the"
      + " cliff walls?\n");
    add_item( ({ "opening", "opening in the wall" }),
        "At the northern end of the wall, an opening leads on to a"
      + " stairway that descends below the ledge.\n");
    add_item( ({ "pass" }),
        "The pathway below this ledge appears to be the only way in"
      + " or out of the valley to the north.\n");
    add_item( ({ "valley", "valley to the north" }),
        "To the north, a valley stretches out, cradling the lake of"
      + " Del Rimmon in its deeps.\n");
    add_item( ({ "ledge", "landing", "wide landing", "wide ledge",
                 "overlook", "fortification", "here", "area" }),
        "This ledge forms an overlook to the pathway below. It extends"
      + " out from the eastern wall of rock perhaps five meters before"
      + " stopping abruptly at the foot of a stone wall which runs"
      + " the length of its western edge.\n");
    add_item( ({ "edge", "western edge", "stone wall",
                 "wall of stone", "wall along the ledge" }),
        "The wall of stone spans the eastern edge of this landing,"
      + " serving as both a railing and most likely at one time as"
      + " a defensive position. Arrow slots are visible at regular"
      + " intervals in its surface, and a massive pile of stones rests"
      + " in the southernmost corner along its length. An opening at"
      + " its northern end joins with a stairway leading downward.\n");
    add_item( ({ "stair", "stairs", "steps", "stairway", "stone stair",
                 "stone stairs", "stone steps", "stone stairway" }),
        "A stone stairway leads from an opening at the northern end"
      + " of the wall to the pathway far below this landing.\n");
    add_item( ({ "slot", "slots", "narrow slot", "narrow slots",
                 "arrow slot", "arrow slots" }),
        "Narrow slots are visible along the stone wall at regular"
      + " intervals. They run vertically from the base of the wall,"
      + " appearing to allow an archer to adjust his aim up or down.\n");
    add_item( ({ "pile", "massive pile", "stone", "stones", "stone pile",
                 "pile of stones", "massive pile of stones" }),
        "This pile of stones does not look like any natural phenomenon,"
      + " but rather more like a deliberate collection of ammunition to"
      + " be used in the defense of the pass.\n");
    add_item( ({ "stone", "stonework" }),
        "The stonework of this landing is not crude, and yet looks to"
      + " have been performed with haste, as if artistry was of far"
      + " less concern than utility. There is a military feel about"
      + " the place.\n");
    add_item( ({ "path below", "pathway below",
                 "path below the landing",
                 "pathway below the landing" }),
        &exa_cliff_base("The pathway rests at the base of the walls of"
          + " rock upon which this overlook stands, running north and"
          + " south through a narrow corridor which forms the pass to"
          + " the lake of Del Rimmon. "));
    add_item( ({ "door", "doorway", "stone door", "stone doorway",
                 "doors", "stone doors", "east" }),
        "A stone doorway is set in the wall of rock to the east of"
      + " this landing. It appears to have been carved from a single"
      + " stone slab. An emblem has been carved in its surface.\n");
    add_item( ({ "stone", "surface", "surface of the door",
                 "surface of the doors", "surface of the doorway",
                 "slab", "stone slab", "single stone slab" }),
        "The surface of the doorway is smooth, having been carved by"
      + " skilled hands. An emblem is carved upon it.\n");
    add_item( ({ "rock wall", "rock walls",
                 "eastern wall", "eastern walls",
                 "wall of rock", "walls of rock",
                 "eastern wall of rock", "eastern walls of rock",
                 "cliff", "cliffs", "cliff wall", "cliff walls" }),
        "To the east of this landing, rock walls rise high above,"
      + " forming cliffs which extend as far as the eye can see into"
      + " the sky. This is in fact the base of Melan Rath, the western"
      + " peak which rises at the south end of Del Rimmon. A doorway of"
      + " some kind has been carved in the rock here.\n");
    add_item( ({ "melan rath", "base", "base of melan rath",
                 "western peak" }),
        "Melan Rath rises immediately to the east here, rising up"
      + " high above. You must crane your neck to glimpse its hights,"
      + " and even then, from this perspective they are beyond view.\n");
    add_item( ({ "melan earl", "eastern peak" }),
        "Melan Earl is completely obscured here by the Melan Rath,"
      + " which rises immediately to the east.\n");
    add_item( ({ "path", "pathway" }),
        "Which pathway do you mean? There is a small pathway leading"
      + " to the southeast, and a path below the landing.\n");
    add_item( ({ "small path", "small pathway", "southeast",
                 "southeast path", "southeast pathway",
                 "path leading southeast", "pathway leading southeast"}),
        "The small pathway to the southeast winds its way around the"
      + " southern portion of the base of Melan Rath, disappearing from"
      + " view around a corner high above.\n");
    add_item( ({ "corner" }),
        "The path disappears from view once it rounds the corner.\n");

    add_cmd_item( ({ "door", "doorway", "doors",
                     "on door", "on doorway", "on doors",
                     "on the door", "on the doorway", "on the doors" }),
                  ({ "knock" }),
        "You knock on the doorway, and hurt your hand doing so. The"
      + " stone slab appears to be very thick, and you doubt anyone"
      + " could even hear such a feeble knock from the other side.\n");
    add_cmd_item( ({ "door", "doorway", "stone door", "doors",
                     "the door", "the doorway", "the stone door",
                     "the doors" }),
                  ({ "open" }),
        "You find no obvious way to accomplish that.\n");
    add_cmd_item( ({ "pile", "massive pile", "pile of stones",
                     "ammunition" }),
                  ({ "search", "dig" }),
        "You dig around in the ammunition, but don't find much of"
      + " anything out of the ordinary. You could probably take stones"
      + " from the pile if you wished.\n");

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost2a", "east",
             door_exit, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/e_stairway", "down");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/rath_ledge", "southeast");

    set_no_exit_msg( ({ "northeast" }),
        "You are halted by the eastern walls of rock in that"
      + " direction.\n");
    set_no_exit_msg( ({ "north", "northwest", "west", "southwest",
                        "south" }),
        "The stone wall which runs along the edge of the landing"
      + " prevents movement in that direction.\n");

    FIX_EUID

    add_lakeview();
    reset_room();
} /* create_del_rimmon */


/*
 * function name:    reset_room
 * description  :    clone and set up the emblem
 */
public void
reset_room()
{
    object  emblem;

    if (!present("kot_emblem"))
    {
        emblem = clone_object(DELRIMMON_DIR + "obj/normal_emblem");
        emblem->move(this_object());
    }
} /* reset_room */


/*
 * Function name:        leave_inv
 * Description  :        Called when objects leave this container or
 *                       when an object is about to change its weight,
 *                       volume, or light status.
 * Arguments    :        ob: The object that just left this inventory
 *                       to: where it went
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->query_prop(TOUCH_PROP))
    {
        ob->catch_tell("You remove your hands from the stone doorway.\n");
        ob->remove_prop(TOUCH_PROP);
    }

    return;
} /* leave_inv */


/*
 * Function name:        door_exit
 * Description  :        check to see if the player is in corporeal
 *                       flux. If not, they cannot pass this way.
 * Returns      :        1 - cannot pass, 0 - may pass
 */
public int
door_exit()
{
    if (this_player()->query_prop(FLUX_PROP))
    {
        write("You walk through the stone door.\n");
        return 0;
    }

    write("The stone door blocks your path.\n");
    return 1;
} /* door_exit */


/*
 * Function name:        corporeal_flux
 * Description  :        if not already in this state, the player is
 *                       rendered non-corporeal, allowing him to pass
 *                       through the stone doorway into the room
 *                       beyond.
 * Arguments    :        object player - the player object
 * Returns      :        1 - do it, 0 - already done, so don't do it
 */
public int
corporeal_flux(object player)
{
    if (player->query_prop(FLUX_PROP))
    {
        player->catch_tell("You are already in flux!\n");
        return 0;
    }

    player->add_prop(FLUX_PROP, 1);
    player->catch_tell(
        "You say: " + CAP(MANAGER->query_password(player)) + "!\n"
      + "The door pulses briefly with a bright blue light, which travels"
      + " up your arm and over your whole body. You suddenly notice that"
      + " the breeze is no longer blowing against you, and that you do"
      + " not feel your weight upon the ground. Your hand moves forward"
      + " into the rock, disappearing beyond the surface of the door.\n");
    player->remove_prop(TOUCH_PROP);
    player->set_no_show_composite(1);
    player->set_invis(1);

    set_alarm(5.0, 0.0, &end_flux(player));

    return 1;
} /* corporeal_flux */


/*
 * Function name:        end_flux
 * Description  :        end the corporeal flux effect on the player
 * Arguments    :        object player - the player object
 */
public void
end_flux(object player)
{
    player->set_no_show_composite(0);
    player->set_invis(0);
    player->catch_tell("You feel the floor solidly against"
                     + " your feet once more as your corporeal form"
                     + " returns.\n");
    player->remove_prop(FLUX_PROP);
} /* end_flux */


/*
 * Function name:        say_password
 * Description  :        catch it if the player happens to speak the
 *                       password which he has been assigned for the
 *                       outpost doors
 * Arguments    :        string arg - what the player typed after 'say'
 * Returns      :        1 - success, 0 - failure
 */
public int
say_password(string arg)
{
    string  txt = LOW(arg);

    if (!strlen(arg))
    {
        notify_fail("What do you wish to incant?\n");
        return 0;
    }

    if (txt == MANAGER->query_password(this_player()) ||
        txt == MANAGER->query_password(this_player()) + "." ||
        txt == MANAGER->query_password(this_player()) + "!")
    {
        if (this_player()->query_prop(TOUCH_PROP))
        {
            corporeal_flux(this_player());
            return 1;
        }

        write("You incant: "
          + CAP(MANAGER->query_password(this_player())) + "!\n"
          + "The stone door in the east wall of rock pulses briefly"
          + " with a bright blue light.\n");
        return 1;
    }

    return 0; /* let the mudlib take it from here */
} /* say_password */


/*
 * Function name:        do_touch
 * Description  :        allow the player to touch the door/emblem
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
do_touch(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, ({}),
        "[the] [east] [eastern] [stone] 'door' / 'doors' / 'doorway'"
      + " / 'emblem'"))
    {
        return 0; /* we don't like the syntax, send it to the mudlib */
    }

    if (QVB == "pry")
    {
        write("The door does not offer any opportunity for you"
          + " to pry it open.\n");
        return 1;
    }

    if (this_player()->query_prop(TOUCH_PROP))
    {
        write("You are already touching the door.\n");
        return 1;
    }

    if (this_player()->query_prop(FLUX_PROP))
    {
        write("Your hand passes through the stone of the door as"
            + " you reach out to touch it.\n");
        return 1;
    }

    this_player()->add_prop(TOUCH_PROP, 1);
    write("You reach out, and touch the doorway.\n");

    return 1;
} /* do_touch */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(say_password, "incant");
    add_action(do_touch, "touch");
    add_action(do_touch, "pry");
} /* init */
