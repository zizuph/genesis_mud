/*
 *  /d/Emerald/blackwall/delrimmon/obj/hole.c
 *
 *  This object allows mortals to attempt to dig at the burial site of
 *  the torque wearers, producing a hole, and eventually touching the
 *  upper levels of the tomb itself.
 *
 *  Location cloned: /d/Emerald/blackwall/delrimmon/lakeside/sw_wood3b
 *
 *  Copyright (c) February 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* global variables */
public int         State = 0;    /*
                                  *  0 - no hole
                                  *  1 - small hole
                                  *  2 - large hole
                                  *  3 - deep hole
                                  *  4 - deep, wide hole
                                  *  5 - extremely deep and wide hole
                                  */


/* prototypes */
public void        create_object();
public string      state_short();
public string      state_long();
public int         do_dig(string arg);
public void        init();
public string      slab_description();
public string      tomb_desc();
public string      search_hole();
public string      search_slab();
public int         mess_with_slab(string arg);

public void        set_state(int i) { State = i; }
public int         query_state() { return State; }



/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("hole");
    add_adj( ({ "small", "large", "deep", "wide", "extremely" }) );

    set_short(state_short);
    set_long(state_long);

    add_item( ({ "bottom of the hole", "bottom", "hole bottom", "stone",
                 "slab", "stone slab", "blue stone", "blue stone slab",
                 "radiant slab", "radiant blue slab", "radiant stone slab",
                 "radiant blue stone slab", "glow", "unearthly glow" }),
        slab_description);
    add_item( ({ "grave", "tomb", "crypt", "casket", "coffin" }),
        tomb_desc);

    add_cmd_item( ({ "hole", "pit", "small hole", "large hole",
                     "deep hole", "deep, wide hole",
                     "extremely deep and wide hole" }),
                  ({ "search" }), search_hole);
    add_cmd_item( ({ "stone", "slab", "stone slab", "blue stone",
                     "blue stone slab", "radiant slab",
                     "radiant blue slab", "radiant stone slab",
                     "radiant blue stone slab", "grave", "tomb",
                     "crypt", "casket", "coffin" }),
                  ({ "search" }), search_slab);
    add_cmd_item( ({ "hole", "pit", "small hole", "large hole",
                     "deep hole", "deep, wide hole",
                     "extremely deep and wide hole" }),
                  ({ "step", "enter", "stand", }),
        "You step down into the hole and kick at its bottom"
      + " for a while. After a bit, you climb back out again.\n");

    add_prop(OBJ_M_NO_GET, "Get what?\n");
    set_no_show_composite(1);
} /* create_object */


/*
 * Function name:        state_short
 * Description  :        the short description must vary according to
 *                       the value of State
 * Returns      :        string - the current short description
 */
public string
state_short()
{
    string txt;

    switch (State)
    {
        default:
        case 0:
            return "";
            break;
        case 1:      
            txt = "small hole";
            break;
        case 2:
            txt = "large hole";
            break;
        case 3:
            txt = "deep hole";
            break;
        case 4:
            txt = "deep, wide hole";
            break;
        case 5:
            txt = "extremely deep and wide hole";
            break;
    }

    return txt + " in the ground";
} /* state_short */


/* 
 * Function name:        state_long
 * Description  :        the long description must vary according to the
 *                       value of State
 * Returns      :        string - the current long description
 */
public string
state_long()
{
    switch (State)
    {
        default:
        case 0:
            return "You find no such thing.\n";
            break;
        case 1:
            return "A small hole has been dug in the ground here. It"
                 + " measures only about a foot deep and two feet"
                 + " in diameter.\n";
            break;
        case 2:
            return "A large hole has been dug in the ground here. It"
                 + " measures about two feet deep and three feet"
                 + " in diameter.\n";
            break;
        case 3:
            return "A very deep hole has been dug in the ground here."
                 + " It is about three feet wide, and at least"
                 + " four feet deep.\n";
            break;
        case 4:
            return "A deep, wide hole has been dug in the ground here."
                 + " It is about four feet deep and roughly five feet"
                 + " in diameter.\n";
            break;
        case 5:
            return "Someone has dug an extremely deep and wide hole"
                 + " in the ground here. It is almost eight feet in"
                 + " diameter, and the bottom looks to be almost"
                 + " ten feet deep. At the bottom of the hole, a"
                 + " radiant blue stone slab has been uncovered,"
                 + " giving the surrounding dirt an unearthly glow.\n";
            break;
    }

    return ""; /* should never happen */
} /* state_long */


/*
 * Function name:        do_dig
 * Description  :        the code for digging the hole, or making it
 *                       bigger
 * Arguments    :        what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_dig(string arg)
{
    mixed   fail;
    object  obj;

    if (!strlen(arg))
        NFN0("Where do you wish to " + query_verb() + "?");

    if (!(parse_command(arg, all_inventory(TP),
        "[in] [up] [out] [the] [a] 'here' / 'ground' /"
      + " 'earth' / 'hole' 'with' [the] %o", obj)))
    {
        if (parse_command(arg, ({}),
            "[in] [up] [out] [the] [a] 'here' / 'ground' /"
          + " 'earth' / 'hole'"))
        {
            write("With your hands? You'd need some kind of tool.\n");
            return 1;
        }

        // parse_command() failed
        NFN0("Where do you want to " + query_verb() + " with what?");
    }

    if (!(obj->id("shovel")))
    {
        WRITE("Your " + obj->short() + " doesn't seem to do much good"
          + " at all. What you need is a shovel.");
        return 1;
    }


    if (query_verb() == "fill")
    {
        write("This hole does seem a bit out of place. Using your"
          + " shovel, you make quick work of the piles of dirt"
          + " which surround the hole, pouring them back into the"
          + " hole. After a time, all the dirt is gone, and, it"
          + " would seem, so is the hole.\n");
        State = 0; /* hide the hole, don't remove it */
        set_no_show_composite(1);
        return 1;
    }

    if (this_player()->query_fatigue() < 40)
    {
        write("You are too tired to dig right now.\n");
        return 1;
    }

    if (State == 5)
    {
        write("As your shovel draws near to the stone slab, a powerful"
            + " magic force hits you, and your muscles seize in place."
            + " After a moment, you are released, and draw back from"
            + " the hole, startled.\n");
        return 1;
    }
    else
    {
        switch (State)
        {
            default:
            case 0:
                write("You take your shovel, and begin digging into"
                     + " the soft earth of the forest floor. Soon, you"
                     + " grow tired, and stop for a bit.\n");
                this_player()->add_fatigue(-40);
                break;
            case 1:
                write("Taking the shovel, you work to increase the size"
                    + " of the hole, digging away dirt from the sides,"
                    + " and scooping out the rubble that falls down"
                    + " into its basin as you work. Growing tired, you"
                    + " stop to rest for a bit.\n");
                this_player()->add_fatigue(-60);
                break;
            case 2:
                write("You take the shovel, intent on digging deeper"
                    + " into the ground, and begin scooping out the"
                    + " bottom of the hole. Soon, you are forced to"
                    + " lean lower and lower over the narrow depth, and"
                    + " your back begins to ache. You decide to pause"
                    + " for a bit.\n");
                this_player()->add_fatigue(-100);
                break;
            case 3:
                write("You take the shovel, and work to widen the"
                    + " narrow pit. As you carve away more and more"
                    + " of the sides of the hole, you are able to"
                    + " eventually step down inside to scoop the"
                    + " dirt away which constantly falls to fill the"
                    + " base of the hole as you work. After a truly"
                    + " gruelling labor, you stick your spade into"
                    + " the ground and lean on the handle, catching"
                    + " your breath.\n");
                this_player()->add_fatigue(-500);
                break;
            case 4:
                write("Determined to dig yet deeper, you mount an"
                    + " all out digging assault on the hole, attacking"
                    + " its sides and basin relentlessly with your"
                    + " shovel. Heaving dirt up and over your head"
                    + " so that it lands far beyond the lip of the"
                    + " hole, you hear calls of dismay and scurrying"
                    + " feet as the local wildlife scrambles for"
                    + " cover. Having dug nearly to the point of"
                    + " exhaustion, and deeper than you thought was"
                    + " possible, your shovel suddenly strikes against"
                    + " something beneath the dirt, and a shiver of"
                    + " magic runs through your entire body, causing"
                    + " you to drop the shovel. Quickly picking it up"
                    + " again, you excitedly work to uncover whatever"
                    + " it was you struck, taking care not to dig"
                    + " carelessly. Slowly, a slab of stone is revealed"
                    + " at the base of the pit, which glows with an"
                    + " intense blue radiance. You step out of the"
                    + " hole, and gaze at it.\n");
                this_player()->add_fatigue(-1000);
                break;
        }
        say(QCTNAME(TP) + " digs a bit in the ground.\n");

        State += 1;
        set_no_show_composite(0);
    }

    return 1;
} /* do_dig */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_dig, "dig");
    add_action(mess_with_slab, "hit");
    add_action(mess_with_slab, "open");
    add_action(mess_with_slab, "push");
    add_action(mess_with_slab, "pull");
    add_action(mess_with_slab, "lift");
    add_action(mess_with_slab, "break");
    add_action(mess_with_slab, "move");
    add_action(mess_with_slab, "touch");
    add_action(do_dig, "fill");
} /* init */


/*
 * Function name:        slab_description
 * Description  :        provide a description for the slab if it has
 *                       been uncovered
 * Returns      :        string - the description of the slab
 */
public string
slab_description()
{
    if (State < 5)
    {
        return "You find no such thing.\n";
    }

    return "At the bottom of the deep hole, a stone slab has been"
         + " uncovered. It pulses with a blue radiance which appears"
         + " to be magical in nature. The stone is extremely smooth,"
         + " and bears no ornamentation or markings of any kind.\n";
} /* slab_description */


/*
 * Function name:        tomb_desc
 * Description  :        provide the player with the opportunity to
 *                       speculate on the nature of the uncovered
 *                       slab
 * Returns      :        string - the description
 */
public string
tomb_desc()
{
    if (State < 5)
    {
        return "You find no such thing.\n";
    }

    return "As you gaze at the stone slab, pondering its origins, the"
         + " idea of a tomb or grave of some kind does not seem out"
         + " of the question. Whatever it is, it appears to be"
         + " protected by a powerful magical enchantment.\n";
} /* tomb_desc */


/*
 * Function name:        search_hole
 * Description  :        allow the player to search the hole
 * Returns      :        string - the text to print to the cmd_item
 */
public string
search_hole()
{
    if (State < 5)
    {
        return "You poke around the hole, checking to see if there is"
             + " anything in the dirt, but find nothing.\n";
    }

    return "You carefully examine the hole, clearing away a bit more"
         + " dirt from the stone slab which rests at its bottom. Aside"
         + " from the slab itself, you find nothing else of interest"
         + " in the dirt.\n";
} /* search_hole */


/*
 * Function name:        search_slab
 * Description  :        allow the player to search the slab
 * Returns      :        string - the text to print to the cmd_item
 */
public string
search_slab()
{
    if (State < 5)
    {
        return "You don't find any such thing to search.\n";
    }

    return "You carefully examine the stone slab, going over every"
         + " inch of its surface. The stone appears perfectly smooth,"
         + " and yet you can only guess at this, since every time your"
         + " fingers get close enough to touch it, a powerful magic"
         + " grips your entire body, and you are forced to draw back."
         + " Other than its radiant blue glow, you can determine"
         + " nothing further about the stone.\n";
} /* search_slab */


/*
 * Function name:        mess_with_slab
 * Description  :        allow players to try to mess with the slab
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
mess_with_slab(string arg)
{
    if (State < 5)
    {
        return 0; /* slab has not yet been exhumed */
    }

    if (!strlen(arg))
    {
        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [glowing] [radiant] [blue] [stone] 'slab'"))
    {
        return 0; /* cant parse the syntax */
    }

    write("As you move to " + query_verb() + " the stone slab,"
        + " a powerful magic grips your body, and causes your"
        + " every muscle to seize and hold. After a brief, and"
        + " somewhat painful wait, you are released, and collapse"
        + " to your knees, breathing hard.\n");

    return 1;
} /* mess_with_slab */
