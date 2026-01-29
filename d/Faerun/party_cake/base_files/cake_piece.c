/*
 *  cake_piece.c
 *  Cloned by the party_room.c when someone gets a piece of cake.
 *  It is not really food, so it does not disturb the game balance.
 *  Adapted by Finwe, November 2001
 */
inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
//#include "party.h"
#include "/d/Faerun/defs.h"

object thrown_by, thrown_at, thrown_in;
int hit_alarm = 0;

/* Prototypes */
object get_new_victim();
string get_body_part_hit();
void hit_victim();

void create_cake_piece()
{}


void
create_food()
{

    seteuid(getuid(this_object()));

    set_name("cake");
    add_name(({"piece of cake","_cake_piece","pieces of cake"}));
//    set_pname(({"cakes", "pieces", "pieces of cake"}));
    set_short("@@my_short_desc@@");
    set_pshort("@@my_pshort_desc@@");
    set_long("This is a piece of a large round cake. It is orange colored and looks delicious to eat. If you get bored, you could probably throw the piece of cake at someone.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 400);
    set_amount(100);

}

string
my_short_desc()
{
    if (!hit_alarm)
	    return "piece of cake";
    return "";
}

string
my_pshort_desc()
{
    if (!hit_alarm)
	    return "pieces of cake";
    return "";
}

void
init()
{
    ::init();

    if (!hit_alarm)
    {
        add_action("do_eat", "eat");
        add_action("do_throw", "throw");
    }
    else
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
        write("You try to evade the cake but fail miserably...\n");
        say(QCTNAME(this_player()) + " tries in vain to evade the cake.\n");
        return 1;
    }

    remove_alarm(hit_alarm);
    msg = "The cake hits ";
    victim = get_new_victim();

    if (victim)
    {
        body_part_hit = get_body_part_hit();
        msg += QTNAME(victim) + " " + body_part_hit;
        this_player()->catch_msg("You duck.\n" + msg + "!\n");
        say(QCTNAME(this_player()) + " ducks.\n" + msg + "!\n",
            ({this_player(), victim}));
        victim->catch_msg(QCTNAME(this_player())
            + " ducks and you are hit by the cake.\n"
            + "Mmmm... it is delicious!\n");
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
do_eat(string str)
{
    object *obs;

    notify_fail("Eat what?\n");

    if (!str)
	    return 0;

    obs = FIND_STR_IN_OBJECT(str, this_player());

    if (!obs || !sizeof(obs) || obs[0] != this_object())
	    return 0;

    write("You eat the piece of cake. It tastes good.\n");
    say(QCTNAME(this_player()) + " eats " + this_player()->query_possessive()
      + " piece of cake.\n");
    remove_object();
    return 1;
}

int
do_throw(string str)
{
    object *obs;
    string cake, victim;
    int i;

    notify_fail("Throw what at who?\n");

    if (!str)
	    return 0;

    if (sscanf(str, "%s at %s", cake, victim) != 2)
	    return 0;

    obs = FIND_STR_IN_OBJECT(cake, this_player());

    if (!obs || !sizeof(obs) || obs[0] != this_object())
	    return 0;

    notify_fail("Throw " + cake + " at who?\n");
    obs = FIND_STR_IN_OBJECT(victim, environment(this_player()));

    if (!obs || !sizeof(obs))
	return 0;

    if (sizeof(obs) > 1)
    {
        notify_fail("You can only throw the piece of cake at one person.\n");
        return 0;
    }

    if (obs[0] == this_player())
    {
        notify_fail("You must be kidding.\n");
        return 0;
    }

    this_player()->catch_msg("You throw your piece of cake at " + QTNAME(obs[0]) + ".\n");
    say(QCTNAME(this_player()) + " throws a piece of cake at " + QTNAME(obs[0]) +
        "!\n", ({ this_player(), obs[0] }));
    obs[0]->catch_msg("A piece of cake comes flying towards you!!!\n");
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
    return one_of_list(({"right in the face", "on the head", "on the cheeks", 
        "on the left arm", "on the right arm", "in the stomach", "on the side", 
        "on the back of the head", "on the side of the face", "on the left leg", 
        "on the right leg"}));
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
        tell_room(thrown_in, "The piece of cake hits the wall.\n");
        remove_object();
        return;
    }

    body_part_hit = get_body_part_hit();
    set_this_player(thrown_at);
    write("The cake hits you " + body_part_hit + "!\n"
	    + "Mmmm... it is delicious.\n");
    say(QCTNAME(thrown_at) + " is hit " + body_part_hit + " by the piece of cake!\n");
    remove_object();
}
