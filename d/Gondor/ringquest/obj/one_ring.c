/*
 *	/d/Gondor/ringquest/obj/one_ring.
 *
 *	One Ring to rule them all, One Ring to find them,
 *	One Ring to bring them all and in the darkness bind them.
 *	Coded by Elessar, November 92.
 *
 *	Copyright (C) by Rolf Braun 1992.
 *
 *	Revision history:
 *	Olorin - 15-aug-95:	Moved to Gondor
 */
#pragma strict_types

inherit "/std/armour";

#include <cmdparse.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

// For the defintion of RACES:
#include "/d/Genesis/login/login.h"

#include "/d/Gondor/defs.h"

#define RING_SHADOW     (RINGQ_DIR + "obj/ring_shadow")

// Race resistance:	   Human, Elf, Dwarf, Hobbit, Gnome, Goblin
#define RING_RACE_RES	({    25,  40,    40,    100,     0,      0, })

// The basic (non-magical) weight of the One Ring.
#define RING_I_WEIGHT		100

// How much does the Ring change the INVIS properies when worn?
#define RING_I_INVIS		 99

// What is the factor for the delays between Ring effects?
#define SLOW_RATE		 10

/*
 *	Prototypes:
 */
public int     heat_ring(string str);
public int     read_ring(string str);
public int     test_will_remove(object pl);
public void    start_fast_count(object pl);
public void    start_slow_count(object pl);
public void    stop_counts(object pl);
public void    add_effect(object pl);
public void    will_contest(object pl);
public void    do_random_effect(object pl);

/*
 *	Global variables:
 */
static int     Is_Hot,
               Initialized,
               Count_Id,
               Contest_Id;
static object  Bearer,
               RQ_Master;
static string  Bearer_Name;

object  query_bearer() { return Bearer; }

varargs void set_initialized(int i = 1) { Initialized = i; }

void
create_armour()
{
    set_name("ring");
    // This name cannot be used in 'examine'. It is just a tag to be used
    // in code.
    add_name("Ash_Nazg");
    // alternative names of the One Ring:
    add_name(({"ash nazg", "one ring", }));
    set_adj(({"plain", "gold"}));
    set_short("plain gold ring");
    set_long("@@long_desc@@");
    set_at(A_ANY_FINGER);
    set_ac(1);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT,  "@@test_weight@@");
    add_prop(OBJ_I_VOLUME,   12);
    add_prop(OBJ_I_VALUE, 20736);
    add_prop(OBJ_I_NO_DROP, "@@test_drop@@");
    add_prop(OBJ_I_NO_GIVE, "@@test_give@@");

    add_prop(MAGIC_AM_MAGIC, ({100, "enchantment"}));

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "There seems to be something magical about the ring.\n",     1,
        "This seems to be a ring of invisibility.\n",               10,
        "There seems to be a powerful enchantment on this ring.\n", 25,
        "The ring seems to emanate power and evil.\n",              50,
        "This ring is one of the Rings of Power.\n",                75,
        BSN("This is the One Ring, the Greatest of the Rings of Power, the "
        + "Ruling Ring, forged by Sauron in Middle-earth.\n"),     100,
        }));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(OBJ_S_WIZINFO, "The One Ring, forged by Sauron.\n"
      + "It is the central object of the Ring Quest of the Middle Earth domains.\n");

    RQ_MASTER->load_me();
    RQ_Master = find_object(RQ_MASTER);
}

/*
 * Function name: long_desc
 * Description:   Long description as VBFC
 * Returns:       the logn description
 */
public string
long_desc()
{
    string  desc = "The ring looks to be made of pure and solid gold. It "
          + "looks quite plain";

    if (Is_Hot)
        desc += ". You see fine lines, finer than the finest penstrokes, "
          + "running along the ring, inside and outside: lines of fire that "
          + "seem to form the letters of a flowing script. They shine "
          + "piercingly bright, and yet remote, as if out of a great depth.";
    else
        desc += " and you cannot see any scratches or signs of wear.";

    return BSN(desc);
}

/*
 * Function name: test_weight
 * Description:   calculate the weight of the ring
 * Returns:       the weight
 */
public int
test_weight()
{
    int     aff = TP->query_skill(SS_AFFECTED_BY_RING);

    if (TP != ENV(TO))
        return RING_I_WEIGHT;
    return RING_I_WEIGHT + (aff*aff/2);
}

/*
 * Function name: remove_object
 * Description:   Inform the master object of the destruction of this clone.
 */
void
remove_object()
{
    if (!objectp(RQ_Master))
        RQ_Master = find_object(RQ_MASTER);

    RQ_Master->ring_removed(TO, Bearer, Bearer_Name);

    ::remove_object();
}

/*
 * Function name: remove_ring
 * Description:   destruct the clone
 */
void
remove_ring()
{
    tell_object(ENV(TO), "DEBUG: Removing "+file_name(TO)+"!\n");
    TO->remove_object();
}

/*
 * Function name: init
 * Description:   initialize the ring
 */
void
init()
{
    object *clones;

    ::init();

    /*
     *	Test is there is another clone of the One Ring in the mud.
     */
    if (!Initialized)
    {
        dump_array(object_clones(find_object(MASTER)));
        clones = object_clones(find_object(MASTER));
        if (sizeof(clones) > 1)
            set_alarm(0.0, 0.0, remove_ring);

        FIX_EUID
        if (!RQ_MASTER->set_one_ring(TO))
            set_alarm(0.0, 0.0, remove_ring);

        set_initialized();
    }

    add_action(heat_ring, "heat");
    add_action(read_ring, "read");
}

/*
 * Function name: cool_down
 * Description:   reset ring after is was heated
 */
void
cool_down()
{
    Is_Hot = 0;
}

/*
 * Function name: heat_ring
 * Description:   the action of heating up the One Ring in a fire
 * Arguments:     str - the argument of the command verb
 * Returns:       0/1 for failure/success
 */
int
heat_ring(string str)
{
    object *arr,
            ring,
            fire;

    NFN("Heat what?");

    if (!strlen(str))
        return 0;

    str = LOW(str);
    if (!parse_command(str, TP, "[the] %i", arr))
        return 0;

    arr = NORMAL_ACCESS(arr, 0, 0);

    if (sizeof(arr) != 1)
        return 0;

    if (arr[0] != TO)
        return 0;

    if (objectp(query_worn()))
    {
        NFN("You cannot heat the "+short()+" while you are wearing it.");
        return 0;
    }

    arr = all_inventory(TP) + all_inventory(ENV(TP));
    arr = filter(arr, &->query_prop(OBJ_I_HAS_FIRE));

    NFN("You have nothing to warm the ring over!");
    if (!sizeof(arr))
        return 0;

    write(BSN("You hold the ring over the flames of the "
      + arr[0]->short()+" for a moment. Even though you burn your "
      + "fingertips, the ring does not get any warmer."));
    say(QCTNAME(TP)+" holds "+LANG_ADDART(short())+" over the flames of "
      + LANG_ADDART(arr[0]->short())+" for a moment.\n", TP);
    Is_Hot = 1;
    set_alarm(120.0 + 60.0 * itof(arr[0]->query_prop(OBJ_I_LIGHT)),
        0.0, cool_down);
    return 1;
}

/*
 * Function name: read_ring
 * Description:   the action of reading the letters on the One Ring
 * Arguments:     str - the argument of the command verb
 * Returns:       0/1 for failure/success
 */
public int
read_ring(string str)
{
    int     skill;
    string  desc;

    NFN("Read what?");
    if (!strlen(str))
        return 0;

    str = LOW(str);

    if (!parse_command(str, ({}),
        "'script' / 'letters' / 'writing' [on] [the] [ring]"))
        return 0;

    if (!Is_Hot)
    {
        write(BSN("You cannot see any marks of writing on the ring, nor "
          + "any scratches or signs of wear. It looks like an ordinary "
          + "gold ring."));
        return 1;
    }

    desc = "The letters are in an ancient language.";
    skill = TP->query_skill(SS_LANGUAGE);

    switch (skill)
    {
    default:
    case  0..25:
        desc += " You cannot understand it.";
        desc = BSN(desc);
        break;
    case 26..50:
        desc += " You recognize the letters as Feanorian, but you are "
             +  "unable to read them.";
        desc = BSN(desc);
        break;
    case 51..75:
        desc += " You recognize the letters as Feanorian, but the words "
             +  "are in an unknown language. This is what you read:";
        desc = BSN(desc);
        desc += "\n\t    Ash nazg durbatuluk, ash nazg gimbatul,\n"
             +    "\tash nazg thrakatuluk agh burzum-ishi krimpatul.\n\n";
        break;
    case 76..100:
        desc += " You recognize the letters as Feanorian, but the words "
             +  "are in the Black Speech, the language created by Sauron. "
             +  "You read:";
        desc = BSN(desc);
        desc += "\n\t    Ash nazg durbatuluk, ash nazg gimbatul,\n"
             +    "\tash nazg thrakatuluk agh burzum-ishi krimpatul.\n";
        desc += "\nTranslated, this means:\n"
             +  "\n\tOne Ring to rule them all, One Ring to find them,\n"
             +    "\tOne Ring to bring them all and in the darkness bind them.\n\n";
        break;
    }
    write(desc);
    return 1;
}

/*
 * Function name: wear
 * Description:   make the wearer invisible when the One Ring is worn
 * Arguments:     obj - object to be worn
 * Returns:       -1     - failure to wear the One Ring, standard fail msg
 *                 0     - success, standard msg
 *                 1     - success, wear() defines the wear msg
 *                string - failure to wear the One Ring, fail msg
 */
mixed
wear(object obj)
{
    int     worn_on_part;

    if (obj != TO)
        return -1;
    start_fast_count(TP);

    if (TP->query_armour(A_L_FINGER) == TO)
        worn_on_part = A_L_FINGER;
    else if (TP->query_armour(A_R_FINGER) == TO)
        worn_on_part = A_R_FINGER;

    tell_room(ENV(TP),QCTNAME(TP)+" suddenly disappears from view!\n",TP);
    write("You wear the "+short()+wear_how(worn_on_part)+".\n");

    TP->add_prop(OBJ_I_INVIS, TP->query_prop(OBJ_I_INVIS) + RING_I_INVIS);
    TP->add_prop(LIVE_I_SEE_INVIS, TP->query_prop(LIVE_I_SEE_INVIS) + RING_I_INVIS);
    return 1;
}

/*
 * Function name: test_will_remove
 * Description:   A check to see if the ring wants to stay on the finger.
 * Arguments:     pl - the wearer
 * Returns:       0/1 for failure/success
 */
public int
test_will_remove(object pl)
{
    return ( random(pl->query_stat(SS_DIS)) >
             random(pl->query_skill(SS_AFFECTED_BY_RING)) );
}

/*
 * Function name: remove
 * Description:   make the wearer visible when the One Ring is removed
 * Arguments:     obj - object to be removed
 * Returns:       -1     - failure to remove the One Ring, standard fail msg
 *                 0     - success, standard msg
 *                 1     - success, remove() defines the remove msg
 *                string - failure to remove the One Ring, fail msg
 */
mixed
remove(object obj)
{
    int     invis;

    /* Does the ring want to be taken off? */
    if (!test_will_remove(TP))
    {
        write(BSN("Your finger must have grown bigger, or maybe the ring has "
          + "become smaller, because it seems impossible to take it off."));
        return -1;
    }

    start_slow_count(TP);
    TP->r(OBJ_I_INVIS,0);

    invis = TP->query_prop(OBJ_I_INVIS) - RING_I_INVIS;
    if (invis)
        TP->add_prop(OBJ_I_INVIS, invis);
    else
        TP->remove_prop(OBJ_I_INVIS);
    invis = TP->query_prop(LIVE_I_SEE_INVIS) - RING_I_INVIS;
    if (invis)
        TP->add_prop(LIVE_I_SEE_INVIS, invis);
    else
        TP->remove_prop(LIVE_I_SEE_INVIS);

    tell_room(ENV(TP), QCNAME(TP)+" suddenly appears out of nowhere!\n",TP);
    write("You take the "+short()+" off your finger, and the world looks "
      + "normal again.\n");
    return 1;
}

/*
 * Function name: enter_env
 * Description:   start the effect on the Ringbearer
 * Arguments:     to   - The destination
 *                from - From what object
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
        return;

    start_slow_count(to);
    Bearer = to;
    Bearer_Name = Bearer->query_real_name();
}

/*
 * Function name: leave_env
 * Description:   The armour is moved from the inventory
 *                Stop the effect on the Ringbearer
 * Arguments:     from - where from
 *                to   - where to
 */
void
leave_env(object from, object to)
{
    ::leave_env(from,to);

    if (!objectp(from) || !living(from))
        return;

    stop_counts(from);
    Bearer = 0;
    Bearer_Name = 0;
}

/*
 * Function name: race_no
 * Description:   return index in RACES array for race name of player
 * Arguments:     pl - the object for which to return the index
 * Returns:       the index
 */
int
race_no(object pl)
{
    return member_array(pl->query_race(), RACES);
}

/*
 * Function name: start_fast_count
 * Description:   start the alarm for the effects of the One Ring on the
 *                Ringbearer when it is worn
 * Arguments:     pl - the Ringbearer
 */
public void
start_fast_count(object pl)
{
    float   contest_interval;
    int     dis = pl->query_stat(SS_DIS),
            affected = pl->query_skill(SS_AFFECTED_BY_RING),
            interval;

    if (Count_Id)
        remove_alarm(Count_Id);

    if (ENV(TO) != pl)
        return;

    if (dis > 200)
        dis = 200;

    // If the discipline is too high, the bearer is very susceptible to
    // the power of the One Ring.
    dis = (dis > 100 ? 200 - dis : dis);

    interval = (dis + RING_RACE_RES[race_no(pl)]);

    Count_Id = set_alarm(0.0, itof(interval), &add_effect(pl));

    contest_interval = -log(rnd()) * 600.0;
    Contest_Id = set_alarm(contest_interval, 0.0, &will_contest(pl));

    if (pl->query_wiz_level())
        pl->catch_msg("Fast count started, interval: "+interval+".\n");
}

/*
 * Function name: start_slow_count
 * Description:   start the alarm for the effects of the One Ring on the
 *                Ringbearer when it is not worn
 * Arguments:     pl - the Ringbearer
 */
public void
start_slow_count(object pl)
{
    int     dis = pl->query_stat(SS_DIS),
            interval;

    if (Count_Id)
        remove_alarm(Count_Id);

    if (ENV(TO) != pl)
        return;

    if (dis > 200)
        dis = 200;

    // If the discipline is too high, the bearer is very susceptible to
    // the power of the One Ring.
    dis = (dis > 100 ? 200 - dis : dis);

    interval = (dis + RING_RACE_RES[race_no(pl)]) * SLOW_RATE;

    Count_Id = set_alarm(itof(interval), itof(interval), &add_effect(pl));

    if (pl->query_wiz_level())
        pl->catch_msg("Slow count started, interval: "+interval+".\n");
}

/*
 * Function name: stop_counts
 * Description:   stop all alarms
 * Arguments:     pl - the Ringbearer
 */
void
stop_counts(object pl)
{
    if (Count_Id)
        remove_alarm(Count_Id);
    Count_Id = 0;

    if (Contest_Id)
        remove_alarm(Contest_Id);
    Contest_Id = 0;

    if (pl->query_wiz_level())
        pl->catch_msg("All counts stopped.\n");
}

/*
 * Function name: add_effect
 * Description:   The power of the Ring has its influence on the Ringbearer
 * Arguments:     pl - the Ringbearer
 */
public void
add_effect(object pl)
{
    int     affected = pl->query_skill(SS_AFFECTED_BY_RING);
    object  shadow;

    if (!living(ENV(TO)) || (pl != ENV(TO)))
    {
        stop_counts(pl);
        return; 
    }

    if (!pl->query_ring_shadow())
    {
        shadow = clone_object(RING_SHADOW);
        if (!shadow->shadow_me(pl))
        {
            SECURITY->do_debug("destroy", shadow);
            log_file("ring_quest", "ERROR: Could not load the Ring shadow.\n");
        }
    }

    pl->set_skill(SS_AFFECTED_BY_RING, ++affected);
    if (pl->query_wiz_level())
        pl->catch_msg("You are now affected "+affected+" % by the ring.\n");
}

int
test_give()
{
  if (TP != environment(TO)) return 0;
  if (random(TP->query_skill(SS_AFFECTED_BY_RING)) > random(TP->query_stat(SS_DIS)/2)) {
    write("You immediately start to think - why part with this ring, which\n"+
      "has become so precious to you? You decide not to give it away.\n");
    return 1;
    }
  if (random(TP->query_skill(SS_AFFECTED_BY_RING)) > random(TP->query_stat(SS_DIS)/5)) {
    write("You are about to give the precious ring away, but find it quite\n"+
      "hard. Why should you? But you shake off the feeling and give it away.\n");
    return 0;
    }
  if (!random(4))
    write("You feel a bit insecure when you give the ring away.\n");
  return 0;
}

int
test_drop()
{
  if (random(TP->query_skill(SS_AFFECTED_BY_RING)) < TP->query_stat(SS_DIS))
    return 0;
  write("Drop your precious?? You decide not to.\n");
  return 1;
}



/*
 * Function name: will_contest
 * Description:   check if a random effect of the One Ring will take place
 * Arguments:     pl - the Ringbearer
 */
public void
will_contest(object pl)
{
    float   contest_interval;
    int     affected,
            dis;

    if (pl != ENV(TO))
    {
        stop_counts(pl);
        return; 
    }

    affected = pl->query_skill(SS_AFFECTED_BY_RING);
    dis = MIN(100, pl->query_stat(SS_DIS));
    dis /= 2;

    if (random(dis*dis) <= (affected*affected))
    {
        do_random_effect(pl);
    }

    contest_interval = -log(rnd()) * 600.0;
    Contest_Id = set_alarm(contest_interval, 0.0, &will_contest(pl));
}

/*
 * Function name: do_random_effect
 * Description:   random actions for the Ringbearer
 * Arguments:     pl - the Ringbearer
 */
public void
do_random_effect(object pl)
{
    int     affected;

    if (pl != ENV(TO))
    {
        stop_counts(pl);
        return; 
    }

    affected = random(pl->query_skill(SS_AFFECTED_BY_RING));

    switch(affected)
    {
    case 0:
        pl->catch_msg("You think fondly of the precious gold ring you are carrying.\n");
        tell_room(ENV(pl), QCTNAME(pl)+" smiles dreamily, lost in thoughts.\n", pl);
        break;
    case 1..4:
        pl->catch_msg("You wonder if anyone else might be interested in your precious ring.\n");
        tell_room(ENV(pl),QCTNAME(pl)+" peers suspiciously around.\n", pl);
        break;
    case 5..10:
        pl->catch_msg("You have a feeling someone is watching your back.....\n"
                    + "But when you turn around, there is no one there.\n");
        tell_room(ENV(pl), QCTNAME(pl)+" looks anxiously back.\n", pl);
        break;
    case 11..20:
        if (TO->query_worn())
            pl->catch_msg("You feel as if a great lidless eye is turning its gaze towards you!\n");
        else
            pl->catch_msg("You feel it would be a good idea to put your "+short()+" on now.\n");
        break;
    default:
        pl->command("$yawn");
        pl->command("$say I think I'm losing control.....");
        break;
    }
    return;
}

string query_recover() { return 0; }

