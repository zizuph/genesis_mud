/*
 *  /d/Gondor/guilds/rangers/ithilien/pool.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * Based on Elessar's pool (thanks, Elessar!!)
 *
 * Modifications:
 * 20-Jul-2001, Alto: more tidy up, change inheritance for new
 *                   rangers.
 */
inherit "/d/Gondor/common/lib/area_room";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

#ifndef ROOM_I_NO_ALLOW_STEED
#include "/d/Gondor/std/steed/steed.h"
#endif /* ROOM_I_NO_ALLOW_STEED */

#define RANGER_ITHILIEN_VISITOR "ranger_ithilien_visitor"
#define MIN_CLIMB_SKILL         25
#define MIN_FATIGUE             50
#define ITHILIEN_POOL_INTRUDER  "_ithilien_pool_intruder"
#define ENTRANCE  (RANGERS_ITH_DIR + "entrance")
#define RANGER_WAS_STEALTHY "_ranger_was_stealthy"
#define RANGER_WAS_MASKED   "_ranger_was_masked"

public void   create_area_room();
public void   init();
public int    do_swim(string str);
public int    do_dive(string arg);
public int    do_climb(string arg);
public int    do_enter(string arg);
public int    do_listen(string arg);
public int    do_splash(string arg);
public int    do_duck(string arg);
public int    do_float(string arg);
public void   enter_inv(object ob, object from);
public void   leave_inv(object ob, object to);
public string query_swimmers();
public int    unq_no_move(string arg);
public void   wash_away(object pl);

public void
create_area_room()
{
    /* bad value so it doesn't do default config */
    set_areatype(999);
    set_areadesc("stone walled pool");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

    set_extraline("The waters of the pool form a beautiful veil as they "
        + "fall from a large rock to swirl and foam in the oval stone "
        + "basin. The steady splash of the waters masks the other sounds "
        + "of the forest. The walls of the basin are high and steep; the "
        + "only egress is a narrow cleft in the west wall, through which "
        + "the waters churn and flow away.");

    add_item( ({ "oval basin", "basin", "bowl", "pool" }), "The oval basin "
        + "is filled with foaming waters that plunge into the pool from "
        + "the top of the rock. The waters swirl around in the bowl before "
        + "flowing away, fuming and chattering, through a narrow cleft "
        + "into calmer and more level reaches to the west.\n");
    add_item( ({ "western wall", "west wall", "narrow cleft", "cleft" }),
        "The waters find their way out of the pool through a narrow "
        + "cleft to the west.\n");
    add_item( ({ "wall", "rocks", "rock wall", "rock walls", "walls",
        "cliff", "cliffs" }), "The walls of the basin are steep and "
        + "featureless, pierced only by a narrow cleft to the west end. "
        + "Over a flat even edge at the top of the north wall, a "
        + "waterfall plunges down into the pool.\n");
    add_item( ({ "edge", "flat edge", "even edge", "flat even edge",
        "northern wall", "north wall", "large rock", "rock", "veil",
        "fall", "falls", "waterfall", "waters", "water" }), "Water "
        + "plunges from a flat even edge at the top of the rock, shaping "
        + "the fall into a sparkling veil that pours into the pool.\n");
    add_item( ({ "tops", "tops of trees", "treetops", "tree tops",
        "forest", "tree", "trees" }), "Only the very tops of trees are "
        + "visible above the walls of the pool.\n");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    set_drink_from( ({ "pool", "basin", "bowl", "waterfall" }) );
}


/*
 * Function name: init
 * Description  : add player verbs
 */
public void
init()
{
    ::init();
    init_drink();
    add_action(do_swim,   "swim");
    add_action(do_dive,   "dive");
    add_action(do_climb,  "climb");
    add_action(do_enter,  "enter");
    add_action(do_listen, "listen");
    add_action(do_listen, "rhear");
    add_action(do_splash, "splash");
    add_action(do_duck,   "duck");
    add_action(do_duck,   "dunk");
    add_action(do_float,  "float");
}


/*
 * Function name: do_swim
 * Description  : handle movement around the pool
 * Arguments    : string arg -- the direction to swim
 * Returns      : 1 if a good direction, 0 if not
 */
int
do_swim(string arg)
{
    object tp = TP;
    object mcloak = present("_mottled_cloak_", tp);

    if (tp->query_prop(ITHILIEN_POOL_INTRUDER))
    {
        notify_fail("Swim where?");
        return 0;
    }

    if (arg == "w" ||
      arg == "west" ||
      arg == "through cleft" ||
      arg == "cleft")
    {
        write("You swim through the cleft in the west wall of the basin.\n");
        SAYBB(" swims through the cleft in the west wall.");
        write("The waters grow calmer and you climb out of the stream.\n");
        tp->move_living("M", (ITH_DIR + "nforest/sstream9"));
        if (TP != tp)
        {
            set_this_player(tp);
        }
        tell_room(ENV(tp), QCNAME(tp)+" climbs out of the stream.\n", tp);
        if (tp->query_prop(RANGER_WAS_STEALTHY))
        {
            tp->remove_prop(RANGER_WAS_STEALTHY);
            if (!tp->query_autosneak())
                tp->set_autosneak(1);
            write("You prepare to move stealthily again as you were "
                + "when you entered Henneth Annun.\n");
        }


        if (objectp(mcloak->query_worn()) &&
            tp->query_prop(RANGER_WAS_MASKED))
        {
            if (!tp->query_prop("_rangers_incognito"))
                tp->command("$hood myself");
            tp->command("$mask myself");
            tp->command("$pin cloak");
         }
    }
    else if (arg == "beneath waterfall" ||
      arg == "beneath falls" ||
      arg == "beneath fall" ||
      arg == "beneath veil")
    {
        SAYBB(" disappears beneath the waterfall.");
        write("You swim beneath the plunging waterfall for a moment, then "
            + "are swept out into the pool.\n");
        SAYBB(" emerges from the waterfall.");
    }
    else
    {
        write("You swim in the foaming waters.\n");
        SAYBB(" swims about the pool.");
    }

    return 1;
}


/*
 * Function name: do_dive
 * Description  : respond to attempts to dive
 * Arguments    : string arg -- whatever the player typed (unused)
 * Returns      : 1  (always succeeds)
 */
public int
do_dive(string arg)
{
    string tmpstr;

    if (strlen(arg) && arg != "down" &&
      !parse_command(arg, ({ }),
      "'into' / 'in' / 'beneath' / 'under' / 'below' "+
      "%s 'water' / 'waters' / 'pool'", tmpstr))
    {
        notify_fail("Dive where?\n");
        return 0;
    }

    write(({ "You dive beneath the surface of the water for a moment, "
        + "and then return.\n", "You dive into the foaming waters, but "
        + "emerge rather quickly when you run out of air.\n", "You dive "
        + "towards the bottom of the pool, then bob to the surface "
        + "again.\n" })[random(3)]);
    SAYBB(" dives under the water and then surfaces again.");
    return 1;
}


/*
 * Function name: do_climb
 * Description  : respond to attempts to climb
 * Arguments    : string arg -- whatever the player typed (unused)
 * Returns      : 1  (always succeeds)
 */
public int
do_climb(string arg)
{
    if (TP->query_prop(ITHILIEN_POOL_INTRUDER))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (arg == "waterfall" ||
      arg == "falls" ||
      arg == "fall" ||
      arg == "veil")
    {
        return do_enter("waterfall");
    }

    if (arg == "up")
    {
        arg = "wall";
    }

    /* singular arg */
    if (arg == "wall" ||
      arg == "cliff" ||
      arg == "rock" ||
      arg == "north wall" ||
      arg == "northern wall" ||
      arg == "west wall" ||
      arg == "western wall" ||
      arg == "south wall" ||
      arg == "southern wall" ||
      arg == "east wall" ||
      arg == "eastern wall")
    {
        write("You swim to the edge of the pool and try to climb the "
            + arg + ", but it is much too steep. You fall back into "
            + "the water with a loud splash.\n");
        SAY(" tries to climb the wall of the basin, but falls back "
            + "into the water with a loud splash.");
        return 1;
    }

    /* plural arg */
    if (arg == "walls" ||
      arg == "cliffs" ||
      arg == "rocks")
    {
        write("You swim to the edge of the pool and try to climb the "
            + arg + ", but they are much too steep. You fall back into "
            + "the water with a loud splash.\n");
        SAY(" tries to climb the wall of the basin, but falls back "
            + "into the water with a loud splash.");
        return 1;
    }

    notify_fail("Climb what?\n");
    return 0;

}


/*
 * Function name: do_enter
 * Description  : respond to attempts to enter waterfall
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 if we understand the arg, 0 if not
 */
public int
do_enter(string arg)
{
    object tp = TP;

    if (tp->query_prop(ITHILIEN_POOL_INTRUDER) ||
      (arg != "waterfall" &&
       arg != "falls" &&
       arg != "fall" &&
       arg != "veil"))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    write("You swim beneath the waterfall and attempt to climb "
        + "the wet, slippery rocks.\n");
    SAYBB(" disappears beneath the waterfall.");

    if (tp->query_skill(SS_CLIMB) >= MIN_CLIMB_SKILL &&
        tp->query_fatigue() >= MIN_FATIGUE && 
        tp->query_encumberance_weight() <= 80)
    {
        write("With some difficulty, you scramble up the rocks "
            + "beneath the plunging water and emerge on solid ground.\n");
        tp->move_living("M", (RANGERS_ITH_DIR + "window"));
        tell_room(ENV(tp), QCNAME(tp)+" emerges from the waterfall.\n", tp);
        if (tp->query_autosneak())
        {
            tp->set_autosneak(0);
            write("You stop being stealthy as you enter the halls "
                + "of Henneth Annun.\n");
            tp->add_prop(RANGER_WAS_STEALTHY, 1);
        }

        // remove hood in ranger hideout
    if (tp->query_prop("_rangers_mask_closed"))
    {
        tp->add_prop(RANGER_WAS_MASKED, 1);
        tp->command("$unpin cloak");
        tp->command("$unmask me");
    }
    }
    else
    {
        write("You fall from the rocks and are swept out into the pool.\n");
        SAYBB(" emerges from the waterfall.");
    }
    return 1;
}


/*
 * Function name: do_listen
 * Description  : respond to attempts to listen
 * Arguments    : string arg -- whatever the player typed (unused)
 * Returns      : 1 (always)
 *
 * All you can hear in the pool is the water.
 */
public int
do_listen(string arg)
{
    write("The rhythmic plash of falling waters masks all other sounds.\n");
    return 1;
}


/*
 * Function name: do_splash
 * Description  : respond to attempts to splash people
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
do_splash(string arg)
{
    object *target, *inv, tp = TP;
    int s;

    arg = LOW(arg);
    if (!strlen(arg) || arg == "water")
    {
        write("You splash water high into the air -- wheee!\n");
        say(QCTNAME(tp) + " splashes water high into the air.\n");
        return 1;
    }

    if (arg != "me" && arg != "myself" && arg != tp->query_real_name())
    {
        inv = all_inventory(TO);
        if (!parse_command(arg, inv, "[water] [on] / [at] %l", target))
        {
            notify_fail("Splash whom?\n");
            return 0;
        }

        target = NORMAL_ACCESS(target, 0, 0);
    }
    else
    {
        target = ({ tp }); 
    }

    if (!(s = sizeof(target)))
    {
        notify_fail("Splash whom?\n");
        return 0;
    }

    while (s-- > 0)
    {
        if (target[s] != tp)
        {
            write("You splash water at " + target[s]->query_the_name(tp)
                + ".\n");
            target[s]->catch_tell(tp->query_The_name(target[s])
                + " splashes water at you.\n");
            say(QCTNAME(tp) + " splashes water at " + QTNAME(target[s])
                + ".\n", ({ tp, target[s] }) );
        }
        else
        {
            write("You splash water on your face. Ahhh, that's refreshing.\n");
            say(QCTNAME(tp) + " splashes water on " + tp->query_possessive()
                + " face.\n");
        }
    }

    return 1;
}


/*
 * Function name: do_duck
 * Description  : respond to attempts to duck people
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
do_duck(string arg)
{
    object *target, *inv, tp = TP;
    int s;

    if (!strlen(arg))
    {
        write("You duck beneath the water for a moment.\n");
        say(QCTNAME(tp) + " ducks beneath the water for a moment.\n");
        return 1;
    }

    inv = all_inventory(TO);
    arg = LOW(arg);
    if (!parse_command(arg, inv,
      "%l [under] / [beneath] / [in] [the] [pool] / [water]", target))
    {
        notify_fail("Duck whom?\n");
        return 0;
    }

    target = NORMAL_ACCESS(target, 0, 0);
    if (!(s = sizeof(target)))
    {
        notify_fail("Duck whom?\n");
        return 0;
    }
    if (s > 1)
    {
        notify_fail("You can't duck that many people at once!\n");
        return 0;
    }

    write("You dive towards the bottom of the pool and, grabbing "
        + target[0]->query_the_possessive_name(tp) + " ankles, pull "
        + target[0]->query_objective() + " beneath the water!\n"
        + "You release your grip on " + target[0]->query_the_name(tp) + ".\n"
        + "You return to the surface.\n");
    say(QCTNAME(tp) + " dives into the water.\n", tp);
    tell_object(target[0], "Something grabs your ankles and pulls you "
        + "beneath the water!\nYou bob back to the surface as the grip on "
        + "your ankles is released.\n");
    say("Suddenly, " + QTNAME(target[0]) + " is pulled beneath the water!\n"
        + QCTNAME(target[0]) + " bobs to the surface.\n", ({ tp, target[0] }) );
    say(QCTNAME(tp) + " rises to the surface.\n", tp );
    return 1;
}


/*
 * Function name: do_float
 * Description  : respond to attempts to float
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
do_float(string arg)
{
    string adv, poss = TP->query_possessive();

    if (!strlen(arg))
        arg = "here";
    else if (strlen(adv = FULL_ADVERB(arg)))
        arg = adv;

    switch (arg)
    {
    case "here":
    case "lazily":
    case "in pool":
    case "in water":
        write("You float lazily in the pool, eyes closed and mind "
            + "deliciously empty.\n");
        say(QCTNAME(TP) + " floats lazily in the pool. " + capitalize(poss)
            + " eyes are closed and there's a blissful smile on " + poss
            + " face.\n");
        break;

    case "happily":
        write("You float happily in the pool, making little splashes "
            + "with your toes.\n");
        say(QCTNAME(TP) + " floats happily in the pool, making little "
            + "splashes with " + poss + " toes.\n");
        break;

    case "idly":
    case "n":
    case "s":
    case "e":
    case "w":
    case "ne":
    case "nw":
    case "se":
    case "sw":
    case "north":
    case "south":
    case "east":
    case "west":
    case "northeast":
    case "northwest":
    case "southeast":
    case "southwest":
        write("You float idly in the pool, unable to control your "
            + "direction of movement.\n");
        say(QCTNAME(TP) + " floats idly in the pool.\n");
        break;
    default:
        notify_fail("Float how?\n");
        return 0;
    }
    return 1;
}

/*
 * Function name: enter_inv
 * Description  : check if ob is allowed to enter
 * Arguments    : object ob -- the entering object
 *                object from -- where they came from
 *
 * XXX was using LIVE_S_EXTRA_SHORT, but gorboth said it
 * gave weird results with some of the Morgul Mages souls.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
        if (present("_kalad_dirty_object", ob))
        {
            present("_kalad_dirty_object", ob)->remove_object();
        }
        if (ob->query_dirty_shadow() == 666)
        {
            ob->remove_shire_filthy_shadow();
        }

        if (!objectp(find_object(ENTRANCE)))
            ENTRANCE->teleledningsanka();
        if (!ITHILIEN_MEMBER(ob) && !ob->query_wiz_level() &&
          !MANAGER->query_voted_in(ob->query_real_name(), "ithilien") &&
          !ENTRANCE->query_allowed(ob->query_real_name()) &&
          !ob->query_prop(RANGER_ITHILIEN_VISITOR) &&
          MASTER_OB(ob) != (RANGERS_OBJ + "pigeon") &&
          MASTER_OB(ob) != (RANGERS_OBJ + "ferret"))
        {
            set_alarm(0.1, 0.0, &wash_away(ob));
            ob->add_prop(ITHILIEN_POOL_INTRUDER, 1);
        }
    }
    else
    {
        set_alarm(1.0, 0.0, &wash_away(ob));
    }
}

/*
 * Function name: leave_inv
 * Description  : remove props from objects when they leave
 * Arguments    : object ob -- the entering object
 *                object to -- where they're going
 */
public void
leave_inv(object ob, object to)
{
    if (living(ob))
        ob->remove_prop(ITHILIEN_POOL_INTRUDER);

    ::leave_inv(ob, to);
}

/*
 * Function name: query_swimmers
 * Description  : describe who's in the pool
 * Returns      : string -- the description
 */
public string
query_swimmers() 
{
    object *swimmers;
    int s;

    swimmers = FILTER_LIVE(all_inventory(TO));
    if (!(s = sizeof(swimmers)))
    {
        return "";
    }
    if (s == 1)
    {
        return swimmers[0]->query_Art_name(TP) + " is swimming in "
            + "the foaming waters of the pool. ";
    }
    return capitalize( COMPOSITE_WORDS(
        FILTER_LIVE(all_inventory(TO))->query_art_name(TP)))
        + " are swimming in the foaming waters of the pool. ";
}

/*
 * Function name: unq_no_move
 * Description  : mask parent so players can swim around the pool
 *                in all directions, even tho no exits have
 *                been added
 * Arguments    : string arg - the command line argument.
 * Returns      : 1 (always)
 */
public int
unq_no_move(string arg)
{
    string vb = query_verb();

    if (vb == "up")
    {
        return do_climb("walls");
    }
    if (vb == "down")
    {
        return do_dive("");
    }
    return do_swim(query_verb());
}

/*
 * Function name: wash_away
 * Description  : float intruders and nonlivings downstream
 * Arguments    : object ob -- the intruding object
 */
public void
wash_away(object ob)
{
    string desc1, desc2, vb;
    if (!objectp(ob))
        return;

    if (living(ob))
    {
        tell_object(ob, "The foaming waters sweep you downstream.\nThe "
            + "waters grow calmer and you climb out of the stream.\n");
        tell_room(TO, QCTNAME(ob) + " is swept downstream by the "
            + "foaming waters.\n", ob);
        ob->move_living("M", (ITH_DIR+"nforest/sstream9"));
        tell_room(ENV(ob), QCTNAME(ob) + " climbs out of the stream.\n", ob);
    }
    else
    {
        desc1 = ob->short();
        switch( ob->num_heap() )
        {
        case 0:
            desc2 = CAP(LANG_ADDART(desc1));
            desc1 = "The " + desc1;
            vb = "washes";
            break;
        case 1:
            desc2 = CAP(LANG_ADDART(desc1));
            desc1 = desc2;
            vb = "washes";
            break;
        default:
            desc2 = CAP(desc1);
            desc1 = desc2;
            vb = "wash";
            break;
        }

        tell_room(TO, desc1 + " " + vb + " downstream.\n");
        ob->move((ITH_DIR + "nforest/sstream9"), 1);
        tell_room(ENV(ob), desc2 + " " + vb + " ashore from the stream.\n");
    }
}
