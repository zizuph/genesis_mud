/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood2.c
 *
 *  The trees along the western hillsides surrounding Del Rimmon in
 *  the Blackwall Mountains of Emerald have drawn back some here, allowing
 *  a delicate lawn to carpet the forest floor in a clearing. There are
 *  very fascinating mushrooms here. *grin*
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";

#include <macros.h>  /* For QCTNAME */
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
public mixed       Portal;

/* prototypes */
public void        create_tree_room();
public int         mushroom_dance(string str);
public int        van_winkle(string arg);
public void        init();
public void        reset_room();
public void        leave_inv(object ob, object to);
public string      describe();
public string      maeltars_finger();


/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
public void
create_tree_room()
{
    add_name(CLEARING);
    set_loc(2);
    set_side("west");
    set_show_area_desc();

    set_extraline(describe);

    add_item( ({ "shadow", "large shadow", "point" }), maeltars_finger);
    add_item( ({"clearing"}), BSN(
        "A clearing opens out here between the trees where an arcing"
      + " lawn of grass runs for a ways upon the hillside."));
    add_item( ({"wooded hill", "wooded hills"}), BSN(
        "The tree clad hills are thinned of trunk and other growing"
      + " things here, where a bit of a clearing has opened up"
      + " along the hillside."));
    add_item( ({"lawn", "large lawn", "grass lawn",
                "lawn of grass", "large lawn of grass"}), BSN(
        "Between the trunks of trees, a lawn along the hillside here"
      + " marks a clearing in the woods. Grasses and thick moss make"
      + " for a peaceful glade beside the lakeshore."));
    add_item( ({"glade", "peaceful glade"}), BSN(
        "There is a calm serenety about this small clearing."));
    add_item( ({"grass", "grasses", "moss", "mosses", "thick moss",
                "thick mosses"}), BSN(
        "Thin mists pass over the turf of the lawn here, where thick"
      + " moss and grass comprise the bed of this peaceful clearing."
      + " Here and there small mushroom heads can be seen dotting"
      + " the soft ground."));
    add_item( ({ "mushroom", "mushrooms", "head", "heads",
                 "mushroom head", "mushroom heads" }),
    BSN("The mushrooms which dot the floor of the clearing have long"
      + " dark stems, and maple brown caps. Their tiny shapes form a"
      + " ring towards the center of the clearing."));
    add_item( ({"shapes", "shape", "tiny shape", "tiny shapes"}), BSN(
        "The mushrooms are delicate and delightful here in this"
      + " lovely clearing on the slopes of the lake."));
    add_item( ({"enclave", "peaceful enclave"}), BSN(
        "There is a serenity about this clearing, as if it offers"
      + " peace and sanctuary from the cares of the day."));
    add_item( ({"ring", "mushroom ring", "ring of mushrooms",
                "fairy ring", "fairae ring", "circle", "rings"}), BSN(
        "Mushrooms have grown in a circular pattern here in the"
      + " middle of the clearing. Where the circle is broken, a"
      + " faint brown hue completes the shape between various"
      + " shapes and sizes of mushrooms."));
    add_item( ({"hue", "brown hue", "faint hue",
                "faint brown hue"}), BSN(
        "The ring of mushrooms would be complete if that tiny"
      + " portion of ground would bear a few more blooms."));
    add_item( ({"ground", "soft ground", "floor",
                "floor of the clearing"}), BSN(
        "The long rows of trees fail here somewhat where a clearing"
      + " has opened up along the hillside."));
    add_item( ({"rows", "rows of trees", "long rows of trees"}), BSN(
        "The trees continue thickly to the south and north, and yet"
      + " here have fallen back somewhat to allow a lawn of grass"
      + " to cover the hillside uncrowded."));

    /* Begin Nasty Red Herring Code */
    add_cmd_item( ({"ring", "mushroom ring", "ring of mushrooms",
                    "fairy ring", "fairae ring", "faerie ring",
                    "circle", "rings" }),
                  ({"search"}), BSN(
        "You poke around the ring of mushrooms, but find nothing"
      + " special."));
    add_cmd_item( ({"mushroom", "mushrooms"}),
                  ({"search"}), BSN(
        "Lowering yourself to the ground, you crawl along the lawn,"
      + " pouring over each tiny mushroom. Aside from many interesting"
      + " flaws and variations in the shape of the individual growths,"
      + " you find nothing special."));
    add_cmd_item( ({"mushroom", "mushrooms"}),
                  ({"pick"}), BSN(
        "You pluck a few mushrooms from the grass, and peer carefully"
      + " at them. Noticing nothing special, you toss them away."));
    add_cmd_item( ({"hue", "brown hue", "faint hue",
                    "faint brown hue"}),
                  ({"search", "dig"}), BSN(
        "You dig around in the grass where there is a faint brown"
      + " hue nearly completing the ring of mushrooms. After a bit,"
      + " you notice that your fingers have turned a bit brown as"
      + " as well, yet nothing becomes any clearer."));
    /* End Nasty Red Herring Code */


    add_exit(DELRIMMON_DIR + "lakeside/w_wood3","north",check_sitting,1,1,);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore3", "northeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore2","east",check_sitting,1,1,);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore1", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1","south",check_sitting,1,1,);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1b", "southwest",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2b","west",check_sitting,1,1,);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b", "northwest",
             check_sitting,1,1);
} /* create_tree_room */

/*
 * Function name: mushroom_dance
 * Description  : allows mortals to dance in the fairy ring
 * Arguments    : str - what the player typed after 'dance'
 * Returns      : 1 - success, and dancing; 0 - no dance
 */
public int
mushroom_dance(string str)
{
    if (!strlen(str))
    {
        NFN0("Where do you want to dance, or with whom?");
    }

    if (!parse_command(str, ({}),
        "[in] [the] [mushroom] [fairy] [faerie]"
      + " 'mushrooms' / 'ring' [of] [mushrooms]"))
    {
        NFN0("Where do you want to dance, or with whom?");
    }

    WRITE("You dance and twirl in the ring of mushrooms until you"
        + " fall exhausted to the ground. Lights dance above your"
        + " dizzy eyelids.");
    SAY(" dances and twirls in the middle of the"
      + " clearing until " + TP->query_pronoun()
      + " falls to the ground, overcome with"
      + " dizziness.");

    return 1;
} /* mushroom_dance */

/*
 * Function name:        van_winkle
 * Description  :        i am bored ... this is funny
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
van_winkle(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(query_verb()) + " where?");
    }

    if (!parse_command(arg, ({}),
        "[down] [on] [in] [the] [fairy] [fairae] [mushroom]"
      + " 'ring' / 'circle' [of] [mushrooms]"))
    {
        return 0; /* bad syntax */
    }

    write("Hmmm ... so you're " + CAP(this_player()->query_name())
        + " van Winkle, now?\n");
    return 1;
} /* van_winkle */


/*
 * Function name: init
 * Description  : add actions to the room
 */
public void
init()
{
    ::init();

    add_action(mushroom_dance, "dance");
    add_action(van_winkle, "lie");
    add_action(van_winkle, "rest");
    add_action(van_winkle, "lay");
    add_action(van_winkle, "sleep");
} /* init */


/*
 * Function name:        reset_room
 * Description  :        clone the portal to the room
 */
public void
reset_room()
{
    if (!present("_del_rimmon_portal", this_object()))
    {
        Portal = clone_object(DELRIMMON_DIR + "obj/portal");
        Portal->move(this_object());
    }

    return;
} /* reset_room */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just leaved this inventory
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (Portal->query_standing() == ob)
    {
        Portal->remove_standing();
    }
} /* leave_inv */


/*
 * Function name:        describe
 * Description  :        provide a description for the room.
 * Returns      :        string - the room description
 */
public string
describe()
{
    string txt = "The trees and foliage have drawn back somewhat here,"
               + " forming a clearing along these wooded hills. A large"
               + " lawn of grass spreads itself in a peaceful enclave"
               + " between the trees.";

    if (!query_beacon())
    {
        return txt;
    }

    if (MANAGER->query_door_location(this_player()) == CLEARING)
    {
        txt += " A large shadow extends into the area here, its point"
             + " ending toward the middle of the clearing.";
    }

    return txt;
} /* describe */


/*
 * Function name:        maeltars_finger
 * Description  :        provide a description for the shadow
 * Returns      :        string - the description
 */
public string
maeltars_finger()
{
    if (!query_beacon())
    {
        return "You find no " + Exa_arg + "\n";
    }

    if (MANAGER->query_door_location(this_player()) != CLEARING)
    {
        return "The shadows which are cast by the brilliant illumination"
             + " all point west northwest, as if the source of the light"
             + " were coming from the southeastern end of the lake.\n";
    }

    return "The shadow extends into the area like a vast finger. It"
         + " is pointing directly at the clearing.\n";
} /* maeltars_finger */
