/*
 * The buffet ticket that allows you to eat as much as you can ;-)
 * coded by Nick, May 30 1992
 * modified by Teth, Dec 6 1996
 */

inherit "/std/object";
#include "../local.h"
#include <macros.h>

#define MAX_FOOD 250
#define MAX_ALC	 30
#define MAX_SOFT 600 /* 10% drink */

int write_food_message(int food);
int write_drink_message(int soft, int alco);

int foodalarm = 0;
int no_alco = 0;

public void
create_buffet()
{
}

public void
create_object()
{
    set_name("buffet");
    add_name("ticket");
    set_adj("buffet");
    set_short("ticket for the buffet at the Bronze Dragon Inn");
    set_long("The ticket allows you to eat from the buffet, " +
        "otherwise there is nothing remarkable about it.\n");
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_NO_DROP, 1);
    create_buffet();
}

public void
set_no_alco()
{
  no_alco = 1;
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (living(dest))
      foodalarm = set_alarm(3.0,0.0,"eat_something");
}

public void
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
	if (!no_alco)
	  ob->drink_alco(alc, 0);
    }
}

public void
write_food_message(int food)
{
    string drink;
    object ob;

    ob = environment();

    if (food < 2)
        drink = ({ "a Verkhus peanut", "an Ergothian candy" })[random(2)];
    else if (food < 20)
        drink = ({ "some blueberries", "a Hylo apple",
                   "a piece of Solamnic hardtack" })[random(3)];
    else if (food < 50)
        drink = ({ "a slice of a Palanthian melon",
                   "a hearty okate of wild greens",
                   "some Nordmaar sausages, spiced with herbs"})
                   [random(3)];
    else if (food < 80)
        drink = ({ "a Vingaard River bass with lemon pepper",
                   "some Solanthian scrapple fried in slices"})
                   [random(2)];
    else if (food < 140)
        drink = ({ "a grilled chicken, cooked Flotsamite style",
                   "a strip of venison meat, fried with onions"})
                   [random(2)];
    else drink = ({ "a platter of roasted meat",
                    "a Throtl fowl, basted in its own juices",
                    "a sirloin steak from a Palanthian-bred cow",
                    "a breast of Kalamanian turkey"})
                    [random(4)];

    tell_object(ob, "You eat " + drink + ".\n");
    say(QCTNAME(ob) + " eats " + drink + ".\n", ob);
}

public void
write_drink_message(int soft, int alc)
{
    string drink;
    object ob;

    ob = environment();

    if (alc < 2 || no_alco)
    drink = ({ "a tumbler of orange juice", "Vingaard Mountain water"})
               [random(2)];
    else if (soft < alc)
    drink = ({ "a shot of Thelgaard whiskey",
               "a snifter of Palanthian brandy" })[random(2)];
    else if (alc < 10)
    drink = ({ "a glass of Lemishite beer", "some Solanthian wine" })
               [random(2)];
    else 
    drink = "a bottle of Caergothian vodka";
    tell_object(ob, "You drink " + drink + ".\n");
    say(QCTNAME(ob) + " drinks " + drink + ".\n", ob);
}

