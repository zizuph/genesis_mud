/*
 * The buffet ticket that allows you to eat as much as you can ;-)
 * coded by Nick, May 30 1992
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define MAX_FOOD 250
#define MAX_ALC	 30
#define MAX_SOFT 600 /* 10% drink */

int write_food_message(int food);
int write_drink_message(int soft, int alco);

int foodalarm = 0;
int no_alco = 0;

void
create_buffet()
{
}

void
create_object()
{
    set_name("buffet");
    add_name("ticket");
    set_adj("buffet");
    set_short("ticket for the buffet at the Smiling Knight");
    set_long("It's just another of those tickets.\n");
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_NO_DROP, 1);
    create_buffet();
}

void
set_no_alco()
{
  no_alco = 1;
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (living(dest))
      foodalarm = set_alarm(3.0,0.0,"eat_something");
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    if(foodalarm)
      remove_alarm(foodalarm);
    foodalarm = 0;
}

void
eat_something()
{
    int food, soft, alc, max_food, max_soft, max_alc;
    object ob;

    ob = environment();
    if (!ob || !living(ob))
	return;

    set_alarm(itof(random(4) + 4),0.0,"eat_something",);

    if (random(3))
    {
	max_food = ob->query_prop(LIVE_I_MAX_EAT);
	food = ob->query_stuffed();
	food = (max_food - food) < max_food / 20 ? max_food - food :
			max_food / 20;
	if (food > MAX_FOOD)
	    food = MAX_FOOD;
	write_food_message(food);
	ob->eat_food(food, 0);
    } else {
	max_soft = ob->query_prop(LIVE_I_MAX_DRINK);
	max_alc = ob->query_prop(LIVE_I_MAX_INTOX);
	soft = ob->query_soaked();
	alc = ob->query_intoxicated();
	soft = (max_soft - soft) < max_soft / 15 ? max_soft - soft :
			max_soft / 15;
	if (soft > MAX_SOFT)
	    soft = MAX_SOFT;
	alc = (max_alc - alc) < max_alc / 8 ? max_alc - alc :
			max_alc / 8;
	if (alc > MAX_ALC)
	    alc = MAX_ALC;
	write_drink_message(soft, alc);
	ob->drink_soft(soft, 0);
	ob->drink_alco(alc, 0);
    }
}

void
write_food_message(int food)
{
    string drink;
    object ob;

    ob = environment();

    if (food < 2)
        drink = ({ "a small peanut", "a tiny candy bar" })[random(2)];
    else if (food < 20)
        drink = ({ "some blue berries", "a small apple",
			"a piece of brown bread" })[random(3)];
    else if (food < 50)
        drink = ({ "a big slice of a melon", "a hearty okate of wild greens",
			"some sausages, spiced with herbs and pepper"})[random(3)];
    else if (food < 80)
	drink = ({ "some fish with potatoes", "some scrapple fried in slices" })[random(2)];
    else if (food < 140)
        drink = ({ "a grilled chicken", "a slab of steaming venison " +
		"fresh from the hunt"})[random(2)];
    else drink = ({ "a big plate of meat", "some gently roasted game fowl, basted " +
           "in its own juices", "a chunk of roast beef",
		"a thick steak from the flank of some big animal" })[random(4)];

    tell_object(ob, "You eat " + drink + ".\n");
    say(QCTNAME(ob) + " eats " + drink + ".\n", ob);
}

void
write_drink_message(int soft, int alc)
{
    string drink;
    object ob;

    ob = environment();

    if (alc < 2 || no_alco)
	drink = ({ "a glass of orange juice", "some water" })[random(2)];
    else if (soft < alc)
	drink = ({ "a small but strong hell burner (100 proof)", 
		"a glass of some strange yellow liquid" })[random(2)];
    else if (alc < 10)
	drink = ({ "a glass of strong beer", "some light and sweet wine" })[random(2)];
    else 
	drink = "some fresh wine";
    tell_object(ob, "You drink " + drink + ".\n");
    say(QCTNAME(ob) + " drinks " + drink + ".\n", ob);
}

