/*
 *	Master for tree in southern Ithilien
 */
inherit "/d/Gondor/common/room.c";

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#define HARD_TO_CLIMB  20  /* how hard is it to climb up the oak? - x + random(x) */
#define HARD_TO_EVADE  50  /* how hard is it to evade the arrows? - x + random(x) */

public int     do_climb(string str);
public void    climb_up();
public void    climb_down();
public void    fall_up(int hit);
public void    fall_down(int hit);

       int     num_arrow;
static string  up_room,
               down_room;
static string  description,
               extraline;

void   set_up_room(string s)   { if (stringp(s)) up_room = s; }
void   set_down_room(string s) { if (stringp(s)) down_room = s; }

string query_up_room()   { return up_room; }
string query_down_room() { return down_room; }

void   set_description(string s) { description = s; }
void   set_extraline(string s)   { extraline = s; }

void
reset_room()
{
    num_arrow = 60;
}

void
create_on_tree()
{
}

nomask void
create_room()
{
    set_long("@@long_desc@@");

    set_noshow_obvious(1);

    create_on_tree();

    reset_room();
}

void
init()
{
    ::init();
    add_action(do_climb, "climb");
}

string
long_desc()
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            long_descf = description;

    if (!clock->query_war()) 
    {
        switch(time)
        {
        case "night":
            long_descf += " Darkness rules the fields of Ithilien now in the nightime.";
            switch(clock->query_moon())
            {
                case "full":
                    long_descf += " A full moon gives some light though.";
                    break;
                case "dark":
                    long_descf += " The sky is covered with dark clouds, "
                      + "and not even the moon shines through.";
                    break;
                default:
                    long_descf += " The moon gives a little light though.";
                    break;
            }
            break;
        case "afternoon":
            long_descf += " The light of day shines across Ithilien. "
              + "It is afternoon.";
            break;
        case "morning":
            long_descf += " The sun is on its way up on the morning sky to the east.";
            break;
        case "noon":
            long_descf += " The sun is almost at its peak on its way "
              + "across the sky. It is the middle of the day in Middle-Earth.";
            break;
        case "evening":
            long_descf += " The sun is setting in the west, coloring the sky golden red.";
            break;
        case "early morning":
            long_descf += " The sun is rising in the east, casting long "
              + "shadows across Ithilien.";
            break;
        }
    }
    else
    {
        switch(time)
        {
        case "evening":
        case "night":
        case "early morning":
            long_descf += " Massive dark clouds cover the sky, making it "
              + "difficult to distinguish night and day. The clouds seem "
              + "to be coming from the east, where Mordor lies. You suspect "
              + "it is night now, as it is as dark as it can get.";
            break;
        case "morning":
            long_descf += " A thick cover of clouds prevent the sun from "
              + "shining on the lands of Ithilien, and it is almost as dark "
              + "as at night. However you gather that it is probably morning, "
              + "as it is getting a bit lighter than earlier.";
            break;
        case "noon":
            long_descf += " A dark mass of clouds seems to be rolling in from "
              + "the east, covering the sky above Ithilien. It is not much "
              + "lighter now than it usually is at night, but still you "
              + "suspect it is the middle of the day.";
            break;
        case "noon":
            long_descf += " A thick mass of clouds cover the sky, making it "
              + "difficult to see far. You suspect that it is afternoon, "
              + "as it is getting a bit darker than earlier.";
            break;
        }
    }
    if (strlen(extraline))
        long_descf += (" " + extraline);
    return (BSN(long_descf));
}

public int
do_climb(string str)
{
    int     risk,
            hurt,
            cap;
    object  tp = TP;

    if (!strlen(str))
    {
        NFN("Climb what?");
        return 0;
    }

    risk = HARD_TO_CLIMB + random(HARD_TO_CLIMB);
    cap = tp->query_skill(SS_CLIMB) + tp->query_stat(SS_DEX)/2;

    str = LOW(str);

    if (member_array(str, ({"oak", "branch", "bough", "tree", })) >= 0)
    {
        write("Climb up or down?\n");
        return 1;
    }

    if (str == "up")
    {
        if (!stringp(up_room))
        {
            write("You cannot climb any further up, since the branches "
              + "would not support you.\n");
            return 1;
        }

        if (cap > risk)
            climb_up();
        else
            fall_up(5*(risk-cap));
    }
    else if(str == "down")
    {
        risk += random(HARD_TO_CLIMB);
        if (cap > risk)
            climb_down();
        else
            fall_down(5*(risk-cap));
    }
    else
    {
        NFN("Climb what?");
        return 0;
    }
    return 1;
}

public void
fall_up(int hit)
{
    write("You try to climb higher.\n"
        + "Suddenly you slip ...\n"
        + "You lose your last hold on the branch you were trying to climb.\n"
        + "You fall down again, but you manage to stop your fall on a lower branch of the tree.\n");
    tell_room(TO,QCTNAME(TP) + " tries to climb higher into the tree, but slips.\n"
        + CAP(TP->query_pronoun()) + " loses his hold and falls down again.\n", TP);
    TP->reduce_hit_point(hit);
    if (TP->query_hp() <= 0)
        TP->do_die(TO);
}

public void
climb_up()
{
    write("Stepping from branch to branch, you manage to climb higher.\n");
    tell_room(TO, "Stepping from branch to branch, "+QTNAME(TP)
      + " manages to climb higher.\n",TP);
    TP->move_living("M", up_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing up from below.\n",TP);
}

public void
climb_down()
{
    write("You climb down to lower branch of the tree.\n");
    tell_room(TO, QCTNAME(TP) + " climbs down from the branch.\n",TP);
    TP->move_living("M", down_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing down from above.\n",TP);
}

public void
fall_down(int hit)
{
    write("You try to climb down from the branch.\n"
        + "Suddenly you slip ...\n"
        + "You fall down from the branch, but you manage to stop your "
        + "fall on a branch somewhere in the tree.\n");
    tell_room(TO, QCTNAME(TP) + " tries to climb down from the branch, but slips.\n"
        + CAP(TP->query_pronoun()) + " falls down from the branch, but manages to stop"
        + TP->query_possessive() + " fall on a lower branch of the tree.\n", TP);

    TP->move_living("M", down_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives falling down from above.\n",TP);
    TP->reduce_hit_point(hit);
    if (TP->query_hp() <= 0)
        TP->do_die(TO);
}

void
arrow_hit(object tp)
{
    int     dex_stat,
            risk,
            hurt;

    if (!objectp(tp) || !present(tp))
        return;

    if (IS_EVIL(tp))
        return;

    if (!present("haradrim", find_object(ITH_DIR + "sforest/lookout")))
    {
        set_alarm(30.0, 0.0, &arrow_hit(tp));
        return;
    }

    if (!num_arrow)
        return;

    dex_stat = tp->query_stat(SS_DEX);
    risk = HARD_TO_EVADE + random(HARD_TO_EVADE) + random(HARD_TO_EVADE);
    if (dex_stat > risk)
    {
        write("An arrow narrowly misses you.\n");
        tell_room(TO, "An arrow narrowly misses " + QTNAME(tp) + ".\n", tp);
    }
    else
    {
        write("You are hit by an arrow fired from above.\n");
        tell_room(TO, QCTNAME(tp) + " is hit by an arrow fired from above.\n", tp);
        tp->reduce_hit_point(50);
        if (tp->query_hp() <= 0)
            tp->do_die(TO);
    }
    num_arrow--;
    set_alarm(150.0 - 2.0 * itof(num_arrow), 0.0, &arrow_hit(tp));
}

void
drop_item(object ob)
{
    if (!objectp(ob) || !present(ob))
        return;

    tell_room(TO, "The " + ob->query_name() + " falls down.\n");
    ob->move(down_room);
    tell_room(down_room, CAP(LANG_ADDART(ob->query_name())) + " falls down from above.\n");
    down_room->drop_item(ob);
}

void
make_smoke(object fire)
{
    tell_room(TO, "Smoke from "+LANG_ADDART(fire->short())
      + " is rising from below into the sky.\n");
    return;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob))
        return;
    if (!living(ob))
        set_alarm(1.0, 0.0, &drop_item(ob));
    else if ( !IS_EVIL(TP) )
        set_alarm(10.0 * rnd(), 0.0, &arrow_hit(ob));
}

