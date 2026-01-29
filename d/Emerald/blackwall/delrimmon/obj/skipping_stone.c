/*
 *  /d/Emerald/blackwall/delrimmon/obj/skipping_stone.c
 *
 *  Stones like this can be found along the shores of Del Rimmon
 *  in the Blackwall Mountains. They seem to work quite well for skipping
 *  purposes.
 *
 *  Copyright (c) October, 1997 by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_object();
public string  stone_characteristics();
public int     skipping_routine(object actor);
public int     skip_stone(string str);
public void    init();

/* global variables */
int     Skip_Number;      // How many times does the stone skip?

/*
 * function name:        create_object
 * description  :        set up the stone
 */
public void
create_object()
{
    set_name("stone");
    add_name( ({ "rock" }) );
    add_name("_del_rimmon_skipping_stone");
    add_adj( ({ "flat", "grey", "round", "smooth", "small",
                "skipping" }) );

    set_short(stone_characteristics() + " stone");
    set_long(BSN("This " + short() + " is about the size of the palm"
           + " of your hand. Its size and shape look perfect for"
           + " skipping on the surface of a lake or pond."));

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
} /* create_object */

/*
 * function name:        stone_characteristics
 * description  :        provides a random description for the
 *                       skipping stone
 * returns      :        str -- the short description for the stone
 */
public string
stone_characteristics()
{
    return ONE_OF_LIST(
        ({"flat grey", "flat round", "smooth grey",
          "smooth round", "small flat", "small grey"}) );
} /* stone_characteristics */

/*
 * function name:        skipping_routine
 * description  :        shows the player (and any audience assembled)
 *                       how well they skipped the stone. we also
 *                       deliver a message to anyone in the water
 *                       where the stone is thrown to.
 * arguments    :        actor -- the player who threw the stone
 * returns      :        1 -- the throw always works ! :-)
 */
public int
skipping_routine(object actor)
{
    string  skip_txt;

    switch(random(11))
    {
        default:
        case 0:
            skip_txt = "The " + short() + " tumbles sloppily through"
                     + " the air and lands with an unsatisfying"
                     + " plop a short distance from shore.";
            break;
        case 1:
            skip_txt = "The " + short() + " sails fast and strong"
                     + " towards the water, skips once on the surface,"
                     + " and then arcs widely off to the left where"
                     + " it sinks into the water with a splash.";
            break;
        case 2:
            skip_txt = "The " + short() + " flies quickly over the"
                     + " water, skipping off the surface jaggedly,"
                     + " but not enough to prevent it from skipping"
                     + " a second time before sinking below the"
                     + " calm waves with a splash.";
            break;
        case 3:
            skip_txt = "The " + short() + " sails directly at"
                     + " the surface of the water with a sharp angle."
                     + " It skips once, twice, three times and then"
                     + " hits the water with a firm splash.";
            break;
        case 4:
            skip_txt = "The " + short() + " rebounds off the water"
                     + " quite close to shore, then makes three more"
                     + " full skips before eventually dipping below"
                     + " the surface with a thunk.";
            break;
        case 5:
            skip_txt = "The " + short() + " sails far before hitting"
                     + " the surface. Its first contact sends it"
                     + " arcing widely off to the right, where it"
                     + " makes four swift hops on the water and"
                     + " finishes with a splash.";
            break;
        case 6:
            skip_txt = "The " + short() + " makes three wide skips"
                     + " in a straight line along the water, and then"
                     + " curves slightly right for three more.";
            break;
        case 7:
            skip_txt = "The " + short() + " flies straight and"
                     + " level out over the surface of the water,"
                     + " skipping perfectly for five counts, and"
                     + " then dips off slightly for a final two."
                     + " A solid throw!";
            break;
        case 8:
            skip_txt = "The " + short() + " skips deftly off the"
                     + " surface of the water. One, two, three, four,"
                     + " five, six, seven.... eight times!";
            break;
        case 9:
            skip_txt = "The " + short() + " makes a long curve as"
                     + " it skips perfectly along the water, in the"
                     + " end making an impressive nine hops in all!";
            break;
        case 10:
            skip_txt = "Flying almost completely parallel to the"
                     + " water, the " + short() + " skips on and on,"
                     + " each skip a continuing testimony to the"
                     + " near perfection of the throw. It finally"
                     + " dips below the water with an almost inaudible"
                     + " quip, but not before you have counted ten"
                     + " perfect skips. A masterful throw!";
            break;
    }

    tell_room(ENV(actor), BSN(skip_txt) );
    remove_object();

    return 1;
} /* skipping_routine */

/*
 * function name:        skip_stone
 * description  :        process the attempt to skip the stone
 * arguments    :        str -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
skip_stone(string str)
{
    object  obj;

    if (!strlen(str))
        NFN0(CAP(query_verb()) + " what?");

    if (ENV(TO) != TP)
        NFN0("Pick up the stone first!");

    if (!(parse_command(str, all_inventory(TP),
        "%o 'in' / 'on' / 'over' / 'across' [the] [nen] "
      + "'lake' / 'water' / 'hithoel'", obj) ) )
    {
        // parse_command() failed
        NFN0("What do you wish to " + query_verb() + " where?");
    }

    if (!ENV(TP)->id("emerald_lakeshore"))
    {
        write("There does not seem to be any water here which is"
            + " suitable for skipping stones.\n");

        return 1;
    }

    write("With a careful stroke, you cast the stone out over the"
        + " surface of the lake.\n");
    say(QCTNAME(TP) + " casts a " + short() + " out over the"
        + " surface of the lake.\n");

    set_alarm(2.0, 0.0, &skipping_routine(TP) );
    return 1;
} /* skip_stone */

/*
 * function name:        init
 * description  :        add the 'skip' verb to the player
 */
public void
init()
{
    ::init();

    add_action(skip_stone, "skip");
} /* init */
