/*
 * /d/Shire/rivendell/room/river/river.c
 *
 * master room for the bruinen below the ford.
 * does lots of special msgs and damage.
 *
 */
 
#pragma strict_types
 
inherit "/d/Gondor/std/water/onwater";
 
#include <stdproperties.h>
#include "local.h"
 
#define	NO_GONDOR_DEFS
#include "/d/Gondor/std/water/onwater.h"
 
 
/* alarm for next msg */
#define ALARM_INTERVAL          3.0
 
/* prop to keep track of how long they've been in this room */
#define LIVE_I_STAYED_HERE      "_live_i_stayed_here"
 
 
/*
 * ok, here come the definitions that control how dangerous it is.
 * the larger MAX_STAY and WASH_CHANCE, and the smaller DAMAGE_DIVISOR,
 * the more dangerous the river
 *
 * in addition to what we do here, there is also the builtin chance of
 * hitting rocks in the normal river code.  you can tune that by
 * increasing or decreasing the value of ROCK_DENSITY.
 *
 * WASH_CHANCE          1 in WASH_CHANCE chance of washing downstream
 * MAX_STAY             max times they can stay in this room, if they
 *                      don't wash downstream because of WASH_CHANCE
 * DAMAGE_DIVISOR       each time they stay here, the river
 *                      does maxhp/DAMAGE_DIVISOR damage 
 * ROCK_DENSITY         how many rocks in the river.  ROCKY is define'd
 *                      in ~gondor/std/water/water_room.h
 */
 
#define MAX_STAY        3
#define WASH_CHANCE     5
#define DAMAGE_DIVISOR  10
#define ROCK_DENSITY    ROCKY
 
 
/* prototypes */
public void     create_river();
nomask void     create_onwater();
public int      block_exit();
public float    float_alarm(int str);
public void     float_downstream(object ob);
public void     msgs_before_move(string vb, string dir, int ashore);
public void     fatigue_message(object pl);
public int      check_hit_rock(object ob);
public void     break_armour(object ob);
 
 
/*
 * Function name:       create_river
 * Description  :       configure your river room here
 */
public void
create_river()
{
}
 
 
/*
 * Function name:       create_onwater
 * Description  :       set up the river
 */
nomask void
create_onwater()
{
    /* XXX these descs should be overridden by something more
     * interesting in create_river()
     */
    set_short("In the flooded River Bruinen");
    set_long("In the flooded River Bruinen.\n");
 
    /* defaults */
    set_depth(MAX_WADE_DEPTH * 4);
    set_currentstr(MAX_CURRENT - 1);
    set_rock_density(ROCK_DENSITY);
    set_watertype("river");
    set_waterrefs( ({ "water", "waters", "river",
        "bruinen", "river bruinen", "bruinen river", "loudwater",
        "river loudwater", "loudwater river",  }) );
 
    create_river();
 
} /* create_onwater */
 
 
/*
 * Function name:       block_exit
 * Description  :       prevent taking exits -- we want to
 *                      roll 'em about ourselves
 * Returns      :       1 -- always
 */
public int
block_exit()
{
    /* XXX more/better msgs */
    write(BSN(
        ({ "The current is too strong -- you cannot control "+
                "your movement.",
           "You splash desperately in the racing waters, "+
                "but are unable to make any progress.",
           "The river tosses you about like a straw -- "+
                "you are helpless in the torrents.",
        })[random(3)]));
    return 1;
} /* block_exit */
 
 
/*
 * Function name:       float_alarm
 * Description  :       mask parent to make the alarms happen very fast
 * Arguments    :       int str -- current strength (ignored)
 * Returns      :       float -- the alarm interval
 */
public float
float_alarm(int str)
{
    return ALARM_INTERVAL;
} /* float_alarm */
 
 
/*
 * Function name:       float_downstream
 * Description  :       mask parent to do interesting msgs.
 * Arguments    :       object ob -- the entering person
 */
public void
float_downstream(object ob)
{
    int         i, fatigue;
    object      savetp,
                *weps;
    string log_str;
 
    if (!objectp(ob) ||
        ENV(ob) != TO)
    {
        return;
    }
 
    if (!living(ob))
    {
        ::float_downstream(ob);
        return;
    }
 
    /* make 'em drop their weapons */
    i = sizeof(weps = ob->query_weapon(-1));
    while (i-- > 0)
    {
        ob->command("$drop "+OB_NAME(weps[i]));
        if (ENV(weps[i]) != TO)
        {
            write(BSN("The waters tear the "+weps[i]->short()+
                " from your grasp."));
            weps[i]->move(TO, 1);
        }
        sink(weps[i], 0);
    }
 
    /* some chance of staying here, with a suitable msg, up to
     * a max of MAX_STAY times.
     */
    if (!random(WASH_CHANCE) ||
        (i = ob->query_prop(LIVE_I_STAYED_HERE)) >= MAX_STAY)
    {
        ob->remove_prop(LIVE_I_STAYED_HERE);
        ::float_downstream(ob);
        return;
    }
 
    ob->remove_prop(OBJ_I_WATER_ALARM);
    ob->add_prop(LIVE_I_STAYED_HERE, (i + 1));
 
    /* called from alarm. must set this_player() to be ob, before
     * we can use say, write, etc.  remember to restore this_player()
     * before returning.
     */
    savetp = TP;
    set_this_player(ob);
 
    /* 5 chances each of 4 non-fatal events plus 1 chance
     * of fatal event.
     */
    switch(random(21))
    {
    case 0..4:
        write(BSN("The waters dash you painfully against a "+
            "half-submerged tree trunk."));
        SAY(" is dashed against a tree trunk.");
        break_armour(ob);
        ob->reduce_hit_point(ob->query_max_hp() / DAMAGE_DIVISOR);
        break;
    case 5..9:
        write(BSN("The raging waters toss you high into the air "+
            "for a moment. You fall back into the river and the "+
            "impact leaves you breathless."));
        SAY(" is tossed high into the air, then falls back into the water.");
        ob->reduce_hit_point(ob->query_max_hp() / DAMAGE_DIVISOR);
        break;
    case 10..14:
        write(BSN("The current rolls you against the riverbank, "+
            "leaving you bruised and gasping for breath."));
        SAY(" is rolled against the riverbank by the current.");
        ob->reduce_hit_point(ob->query_max_hp() / DAMAGE_DIVISOR);
        break;
    case 15..19:
        write(BSN("You tumble helplessly in the violent waters, "+
            "pummeled by submerged rocks and logs."));
        SAY(" tumbles helplessly in the violet waters.");
        ob->reduce_hit_point(ob->query_max_hp() / DAMAGE_DIVISOR);
        break;
    case 20:    /* the fatal one */
        /* XXX better msg */
        write(BSN("Swept along by the racing waters, you slam headfirst "+
            "into a rock."));
        SAY(" slams headfirst into a rock.");
        ob->reduce_hit_point(ob->query_max_hp());
        break;
    }
 
    if (ob->query_hp() <= 0)
    {
        write("You drown in the waters of the Bruinen.\n");
        SAY(" drowns in the waters of the Bruinen.");
        /* XXX should log this somewhere */
    log_str = ctime(time()) + " "+ capitalize(ob->query_real_name()) +
        " (" + ob->query_average_stat() + ") died in the ford.\n";
 
    log_file("ford_drowned",log_str);
 
        ob->do_die(TO);
        set_this_player(savetp);
        return;
    }
 
    /* borrow fatigue code from ~gondor/std/water/water_room.c */
    i = ob->query_skill(SS_SWIM);
    fatigue = swim_float_fatigue(i, Downstreamdir[0], WATER_MOVE_FLOAT, ob);
    if (fatigue > 0)
    {
        if (ob->query_fatigue() < fatigue)
        {
            if (take_damage(ob, Currentstr[0]))
            {
                /* player drowned */
                /* XXX should log this somewhere */
                set_this_player(savetp);
                return;
            }
        }
        ob->add_fatigue(-(fatigue));
    }
 
    ob->add_prop(OBJ_I_WATER_ALARM, 
        set_alarm(float_alarm(Currentstr[0]), 0.0, &float_downstream(ob)));
    set_this_player(savetp);
 
} /* float_downstream */
 
 
/*
 * Function name:       msgs_before_move
 * Description  :       mask parent to do more interesting msgs than
 *                      "The current washes you downstream."
 * Arguments    :       string vb -- "wash", "swim", "wade", "dive"
 *                      string dir -- the direction of movement
 *                      int ashore -- if nonzero, moving to shore
 */
public void
msgs_before_move(string vb, string dir, int ashore)
{
    if (vb == "wash")
    {
        /* XXX more/better msgs */
        write(BSN( ({
            "You are flung about like a leaf as the foaming waters "+
                "dash you downstream.",
            "Frothing and hissing, the water sweeps you downstream.",
            "You barely keep your head above water as you are swept "+
                "downstream.",
            })[random(3)]));
    }
    else
    {
        ::msgs_before_move(vb, dir, ashore);
    }
} /* msgs_before_move */
 
/*
 * Function name:       msgs_after_move
 * Description  :       mask parent to handle msgs when we wash them
 *                      onto the landing
 * Arguments    :       object tp -- this_player
 *                      string vb -- "swim", "wade", "dive"
 *                      string pcpl -- participle phrase suitable for being
 *                              appended to "Foo arrives " (e.g., "swimming")
 *                              (no trailing period)
 *                      int change_state -- if nonzero, swimmer will
 *                              stand up or wader will swim
 */
public void
msgs_after_move(object tp, string vb, string pcpl, int change_state)
{
    int	type = ENV(tp)->query_prop(ROOM_I_TYPE);
 
    if (type == ROOM_IN_WATER ||
        type == ROOM_UNDER_WATER)
    {
        /* they're still in the river */
        ::msgs_after_move(tp, vb, pcpl, change_state);
    }
    else
    {
        /* they washed ashore */
        /* XXX more/better msgs */
        write(BSN( ({
            "Battered and gasping, you wash up on shore.",
            "The river spits you out onto the shore.",
            "The violent current flings you up onto dry land.",
            })[random(3)] ));
        tp->remove_prop(OBJ_I_WATER_MOVE);
        tp->remove_prop(LIVE_I_STAYED_HERE);
    }
} /* msgs_after_move */
 
 
 
 
/*
 * Function name:       fatigue_message
 * Description  :       mask parent so we don't do fatigue msgs
 *                      "You feel somewhat tired." looks silly when we're
 *                      writing all these dire msgs about slamming
 *                      into trees etc.
 * Arguments    :       object pl -- the player
 */
public void
fatigue_message(object pl)
{
}
 
 
/*
 * Function name:       check_hit_rock
 * Description  :       mask parent to have a chance
 *                      of breaking armour if hit
 * Arguments    :       object ob -- the player
 * Returns      :       1 if hits rock, 0 if not
 */
public int
check_hit_rock(object ob)
{
    int	rval;
 
    rval = ::check_hit_rock(ob);
    if (!rval ||
        !living(ob))
    {
        return rval;
    }
    break_armour(ob);
    return 1;
} /* check_hit_rock */
 
 
/*
 * Function name:       break_armour
 * Description  :       they hit something hard -- break their armour
 * Arguments    :       object ob -- the player
 */
public void
break_armour(object ob)
{
    object      *armours;
    int         s;
 
    /* filter out autoloading so don't break guild tokens */
    armours = filter(ob->query_armour(-1),
        &operator(==)(0) @ &->query_auto_load());
    s = sizeof(armours);
    if (!s)
    {
        return;
    }
    if (s > 1)
    {
        s = random(s);
    }
    else
    {
        s = 0;
    }
    armours[s]->set_condition(armours[s]->query_condition() + 2);
    return;
} /* break_armour */
