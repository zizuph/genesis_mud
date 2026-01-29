/*
 * follower.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

inherit "/std/monster";

#include "defs.h"

static string followee;
static int follow_on_ships;

void fly();
void telep_fun(string who);

void
create_follower()
{
}

nomask void
create_monster()
{
    trig_new("%s 'is' 'slowly' %s", "telep_func");
    trig_new("%w 'leaves' 'the' %s", "leave_ship");
    trig_new("%w 'leaves' 'boarding' %s", "board_ship");
    trig_new("%w 'leaves' %s", "leave_fun");
    trig_new("%w 'arrives.\n'", "arrive_fun");
    trig_new("%w 'disappears' 'in' 'a' 'puff' 'of' 'smoke.\n'", "telep_fun");

    follow_on_ships = 0;

    create_follower();
}

void
set_follow_on_ships(int i)
{
    follow_on_ships = i;
}

void
board_ship(string s, string ss)
{
    command("say hiho! hihi! a-sailing we go!");
    if (follow_on_ships)
        telep_fun(s);
}

void
leave_ship(string s, string ss)
{
    command("puke");
    command("say Why do I always get seasick?");
    if (capitalize(s) == followee)
        command("disembark");
}

void
follow(string s)
{
    followee = capitalize(s);
}

void
telep_fun(string who)
{
    if (capitalize(who) == followee)
        set_alarm(1.0, 0.0, fly);

    command("say Why do you leave me?");
}

void
telep_func(string who)
{
    if (capitalize(who) == followee)
        this_object()->move(NYREESEDIR + "cas_a11");
}

/* substitute these functions with your own if you want something
   special when leaving/arriving when following */

void
teleport_leave_hook()
{
}

void
teleport_arrive_hook()
{
}

void
leave_hook()
{
}

void
arrive_hook()
{
}

void
fly()
{
    teleport_leave_hook();
    move_living("X", environment(find_player(lower_case(followee))));
    teleport_arrive_hook();
}

void
leave_fun(string who, string where)
{
    string wh;

    wh = explode(where, ".")[0];

    if (capitalize(who) == followee)
    {
        leave_hook();
        command(wh);
        arrive_hook();
    }
}

void
arrive_fun(string s)
{
}
