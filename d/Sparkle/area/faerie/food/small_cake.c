
inherit "/std/food";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

object thrown_by, thrown_at, thrown_in;
int hit_alarm = 0;

/* Prototypes */
object get_new_victim();
string get_body_part_hit();
void hit_victim();

void
create_food()
{
    setuid();
    seteuid(getuid());

    set_name(({"cake", "faerie_cake_"}));
    set_pname(({"cakes", "small cakes"}));
    set_short("small cake");
    set_pshort("small cakes");
    set_long("This is a small cake, baked by the best bakers of Green Oaks. " +
        "It round and looks light. However, it looks like it is filling. " +
        "Holding it, you get a sudden urge to throw it at someone.\n");

    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
  
}


string
my_short_desc()
{
    if (!hit_alarm)
	return "small cake";
    return "";
}

string
my_pshort_desc()
{
    if (!hit_alarm)
	return "small cakes";
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
	write("You try to evade the small cake but fail miserably...\n");
	say(QCTNAME(this_player()) + " tries in vain to evade the flying small cake.\n");
	return 1;
    }

    remove_alarm(hit_alarm);
    msg = "The small cake hits ";
    victim = get_new_victim();

    if (victim)
    {
	body_part_hit = get_body_part_hit();
	msg += QTNAME(victim) + " " + body_part_hit;
	this_player()->catch_msg("You duck.\n" + msg + "!\n");
	say(QCTNAME(this_player()) + " ducks.\n" + msg + "!\n",
	    ({this_player(), victim}));
	victim->catch_msg(QCTNAME(this_player())
	    + " ducks and you are hit by a small cake.\n"
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

    write("You eat the small cake. It tastes good.\n");
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
	notify_fail("Throw just one " + cake + " at several players???\n");
	return 0;
    }

    if (obs[0] == this_player())
    {
	notify_fail("You must be kidding.\n");
	return 0;
    }

    this_player()->catch_msg("You throw your small cake at " + QTNAME(obs[0])
	+ ".\n");
    say(QCTNAME(this_player()) + " throws a small cake at " + QTNAME(obs[0])
	+ "!\n", ({ this_player(), obs[0] }));
    obs[0]->catch_msg("A small cake comes flying towards you!!!\n");
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
	tell_room(thrown_in, "The small cake hits the wall.\n");
	remove_object();
	return;
    }

    body_part_hit = get_body_part_hit();
    set_this_player(thrown_at);
    write("The small cake hits you " + body_part_hit + "!\n"
	+ "Mmmm... it is delicious.\n");
    say(QCTNAME(thrown_at) + " is hit " + body_part_hit + " by a small cake!\n");
    remove_object();
}
