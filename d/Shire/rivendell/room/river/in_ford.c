/*
 * /d/Shire/rivendell/room/river/in_ford.c
 *
 * evils will have a very bad time here.
 *
 */
 
#pragma strict_types
 
inherit "/d/Gondor/std/water/onwater";
#include <composite.h>
#include <macros.h>
#include "local.h"
 
/* set NO_GONDOR_DEFS so onwater won't try to include ~gondor/defs.h */
#define NO_GONDOR_DEFS
#include "/d/Gondor/std/water/onwater.h"
 
#define MIN_ALIGN       -160
 
public void     create_onwater();
public void     enter_inv(object ob, object from);
public int      check_alignment();
public int      block_exit();
public void     float_downstream(object pl);
 
 
/*
 * Function name:       create_onwater
 * Description  :       set up the ford
 */
public void
create_onwater()
{
    set_short("In the ford of the River Bruinen");
    set_long("This ford in the River Bruinen, though not as " +
        "deep as other areas of the river, allows safe " +
        "crossing. It flows swiftly from the north to the " +
        "southwest in this part of the forest. The water is " +
        "cold and clear with an occasional branch or leaf " +
        "floating on it.\n");
 
    add_item(({"river", "river bruinen", "bruinen", "fords", 
            "water", "ford", "ford of bruinen", 
            "Ford of Bruinen", "river of rivendell", 
            "rivendell river", "loudwater", "river loudwater", 
            "loudwater river",}),
        "The river, cool and clear, rushes south out of the " +
        "mountains. The river is often quite deep in many " +
        "places, but this ford usually allows for safe " +
        "crossing.\n");
 
    set_depth(MAX_WADE_DEPTH);
    set_currentstr(MODERATE_CURRENT);
    set_upstreamdir("north");
    set_downstreamdir("southwest");
    set_watertype("ford");
    set_waterrefs( ({ "water", "waters", "ford", "river",
        "bruinen", "river bruinen", "bruinen river", "loudwater",
        "river loudwater", "loudwater river",  }) );
 
    add_exit(FOREST_DIR + "forest52", "east", "@@check_alignment@@", 1);  
    add_exit(RIVER_DIR  + "riverbank", "west", 0, 3);
 
    /* river00 does not exist. we add the exit so that the
     * messages will look right, though.
     */
    add_exit("river00", "north", block_exit);
    add_exit("river01", "southwest", block_exit);
 
} /* create_onwater */
 
 
/*
 * Function name:       enter_inv
 * Description  :       mask parent to hasten alarms for washing
 *                      evils downstream
 * Arguments    :       object ob -- the entering object
 *                      object from -- its source
 */
public void
enter_inv(object ob, object from)
{
// if _no_cross prop NOT set, let them cross river
    if (!ob->query_prop("_no_cross_"))
    {
        ::enter_inv(ob, from);
        return;
    }
 
    /* we want to wash them downstream *fast* */
    ::enter_inv(ob, from);
    ob->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_SWIM);
    ob->add_prop(OBJ_I_WATER_ALARM,
        set_alarm(0.5, 0.0, &float_downstream(ob)));
} /* enter_inv */
 
 
 
/*
 * Function name:       check_alignment
 * Description  :       prevent evils from taking shore exits
 * Returns      :       0 if exit allowed, 1 if not
 */
public int
check_alignment()
{
    if (!TP->query_prop("_no_cross_"))
    {
        return 0;       /* exit allowed */
    }
    /* XXX what msg? */
    write(BSN("The cold waters crash over you, forcing you "+
        "back from the shore."));
    return 1;
}


 
/*
 * Function name:       block_exit
 * Description  :       block up- and downstream exits, so they
 *                      can't swim away. we will move evils downstream
 *                      by hand.
 * Returns      :       1 -- exit never allowed
 */
public int
block_exit()
{
    write(BSN("The waters are swift and icy cold, and appear dangerous. "+
        "You decide not to risk it."));
    return 1;   /* exit not allowed */
} /* block_exit */
 
 
/*
 * Function name:       float_downstream
 * Description  :       wash evils downstream, just do msgs for
 *                      everyone else :-)
 * Arguments    :       object ob -- the entering person
 */
public void
float_downstream(object ob)
{
 
    if (!objectp(ob) ||
        ENV(ob) != TO)
    {
        return;
    }
 
    ob->remove_prop(OBJ_I_WATER_ALARM);
// if _no_cross_ prop NOT set, let them cross.
    if (!ob->query_prop("_no_cross_"))
    {
        /* the default enter-water set up an alarm, but
         * we don't want to wash them downstream
         */
        return;
    }
// remove _no_cross_ prop so players can do this again
    ob->remove_prop("_no_cross_");
 
    /* XXX better msgs? */
    write(BSN("The river rises up, violently churning, and drags you "+
        "off your feet. You are pulled under and swept away."));
    say("The river suddenly rises up violently against "+
        QTNAME(ob)+". "+CAP(HE_SHE(ob))+" disappears beneath "+
        "the water and is swept downstream.\n");
    ob->move_living("M", "/d/Shire/rivendell/room/river/river01",1);
    tell_room(ENV(ob),
        QNAME(ob)+" is swept in by the foaming current.\n",
        ob);
 
} /* float_downstream */

/*
 * Allows players to drink from the river
 */
   
 
void init()
{   
    ::init();
    add_action("drink_it",      "drink");
}
 
int drink_it(string s)
{
 
int amount;
 
   if(s=="water" || s=="water from river")
       {
           amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
           if (TP->drink_soft(amount))
           {
           TP->catch_msg("You bend over in the river, dipping " +
                "your cupped hands into the river and get a " +
                "drink of the clear icy water. Its taste " +
                "refreshes your mind and body.\n");
 
           say(QCTNAME(TP)+" bends over in the river and gets a " +
                "drink.\n");
           
           }
           else
           {
           write("You cannot drink more water.\n");
           }
 
            return 1;
        }
    else
            NF("Drink what?\n");
}
