/*
 *  Shire cowpie
 *  Adapted so it can be thrown. Based on teh party cake piece
 *  Finwe, September 2017
 */
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

//#include "party.h"

object thrown_by, thrown_at, thrown_in;
int hit_alarm = 0;

/* Prototypes */
object get_new_victim();
string get_body_part_hit();
void hit_victim();

void do_smell();
void remove_smell();

void
create_object()
{
   set_name("cowpie");
   add_name(({"dung","waste","pile","heap"}));
   set_short("large cowpie");
   add_adj(({"pile","smelly"}));
   
   set_long("This is a huge smelly cowpie. It smells horribly! If you dared, " +
        "you can pick it up and throw it at someone.\n");
   
   add_prop(OBJ_I_WEIGHT, 1400);
   add_prop(OBJ_I_VOLUME, 14000);
   add_prop(OBJ_I_VALUE, 0);
   
   set_alarm(15.0,25.0,"do_smell");
   set_alarm(600.0,0.0,&remove_smell());

}


void
do_smell()
{
   tell_room(ENV(TO), "A strong stench from the cowpie wafts " +
       "up to your nose. It smells awful!\n");
   
}

void
remove_smell()
{
   TO->remove_object();
}


void
init()
{
    ::init();

    add_action("do_throw", "throw");
    add_action("do_duck", "duck");
}

int
do_duck(string str)
{
    object victim;
    string body_part_hit, msg;

    if (str)
	return 0;

    if (!random(4))
    {
        write("You try to evade a flying " + query_short() + " but fail miserably...\n");
        say(QCTNAME(this_player()) + " tries in vain to evade a flying " + 
            query_short() + ".\n");
        return 1;
    }

    remove_alarm(hit_alarm);
    msg = "The " + query_short() + " hits ";
    victim = get_new_victim();

    if (victim)
    {
        body_part_hit = get_body_part_hit();
        msg += QTNAME(victim) + " " + body_part_hit;
        this_player()->catch_msg("You duck.\n" + msg + "!\n");
        say(QCTNAME(this_player()) + " ducks.\n" + msg + "!\n",
            ({this_player(), victim}));
        victim->catch_msg(QCTNAME(this_player())
            + " ducks and you are hit by a flying " + query_short() + ".\n"
            + "Eww!!!\n");
    }
    else
    {
        msg += "the wall";
        this_player()->catch_msg("You duck.\n" + msg + ".\n");
        say(QCTNAME(this_player()) + " ducks.\n" + msg + ".\n");
    }
    remove_object();
    return 1;
}

int
do_throw(string str)
{
    object *obs;
    string cowpie, victim;
    int i;

    notify_fail("Throw what at who?\n");

    if (!str)
	return 0;

    if (sscanf(str, "%s at %s", cowpie, victim) != 2)
	return 0;

    obs = FIND_STR_IN_OBJECT(cowpie, this_player());

    if (!obs || !sizeof(obs) || obs[0] != this_object())
	return 0;

    notify_fail("Throw " + cowpie + " at who?\n");
    obs = FIND_STR_IN_OBJECT(victim, environment(this_player()));

    if (!obs || !sizeof(obs))
	return 0;

    if (sizeof(obs) > 1)
    {
	notify_fail("Throw just one " + cowpie + " at several players???\n");
	return 0;
    }

    if (obs[0] == this_player())
    {
	notify_fail("You must be kidding.\n");
	return 0;
    }

    this_player()->catch_msg("You throw a " + query_short() + " at " + QTNAME(obs[0])
	+ ".\n");
    say(QCTNAME(this_player()) + " throws a " + query_short() + " at " + 
        QTNAME(obs[0])
	+ "!\n", ({ this_player(), obs[0] }));
    obs[0]->catch_msg("A " + query_short() + " comes flying at you!!!\n");
    thrown_by = this_player();
    thrown_at = obs[0];
    thrown_in = environment(thrown_by);
    hit_alarm = set_alarm(itof(random(8) + 2), 0.0, &hit_victim());
    move(obs[0]);
    return 1;
}

int get_new_victim_filter(object obj);

object
get_new_victim()
{
    object *obs;

    obs = all_inventory(environment(this_player()));
    obs = filter(obs, &get_new_victim_filter(), this_object());

    if (!obs || !sizeof(obs))
	return 0;

    return obs[random(sizeof(obs))];
}

int
get_new_victim_filter(object obj)
{
    if (obj != thrown_at && obj != thrown_by && living(obj))
	return 1;
    return 0;
}

string
get_body_part_hit()
{
    switch (random(8))
    {
    case 0:
	return "right in the face";
    case 1:
	return "on the head";
    case 2:
	return "on the cheeks";
    case 3:
	return "on the arms";
    case 4:
	return "in the stomach";
    case 5:
	return "on the side";
    case 6:
    return "on the back of the head";
    case 7:
    return "on the side of the face";
    }
}

void
hit_victim()
{
    string body_part_hit;

    if (!thrown_in)
    {
	remove_object();
	return;
    }

    if (!thrown_at || !present(thrown_at, thrown_in))
    {
	tell_room(thrown_in, "The " + query_short() + " hits the wall.\n");
	remove_object();
	return;
    }

    body_part_hit = get_body_part_hit();
    set_this_player(thrown_at);
    write("A flying " + query_short() + " hits you " + body_part_hit + "!\n"
	+ "Yuck!!!\n");
    say(QCTNAME(thrown_at) + " is hit " + body_part_hit + " by a flying " + 
        query_short() + "");
    remove_object();
}
