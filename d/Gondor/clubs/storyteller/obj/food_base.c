/*
 * /d/Gondor/clubs/storytellers/obj/food_base.c
 *
 * The storyteller drink base file, by Morrigan 10/2002
 *    allows a drink to be sipped to completion or drank
 *    normally
 */

inherit "/d/Gondor/clubs/storyteller/obj/std_food";

#include "/sys/stdproperties.h"
#include <cmdparse.h>
#include <macros.h>

public void	set_nibble_max_amount(int i);
public void	set_nibble_amount(int i);
public void	add_nibble();
public int	query_nibble_max_amount();
public int	query_nibble_amount();
public void	create_st_food();
public void	setup_food();
public int	nibble_food(string str);
public string	long_desc();

int Nibble_max = 1, Nibble_amount, Food_max, Food_amount;

string Old_long;

void
create_st_food()
{
}

void
create_food()
{
    set_amount(100);
    set_name("bread");
    set_adj("light");
    set_short("light bread");
    set_pshort("light breads");
    set_long("An ordinary light bread.\n");
 
    create_st_food();
    setup_food();
}

public void
setup_food()
{
    Food_max = query_amount();
    Food_amount = Food_max / Nibble_max;

    Old_long = query_long();

    if (Nibble_max > 1)
        set_long(&long_desc());
}

public void
set_nibble_max_amount(int i)
{
    Nibble_max = i;
}

public void
set_nibble_amount(int i)
{
    Nibble_amount = i;
}

public void
add_nibble()
{
    int perc;

    Nibble_amount = Nibble_amount + 1;

    perc = 100 - (Nibble_amount * 100 / Nibble_max);

    /* Update the actual contents of the drink */
    set_amount(Food_max * perc / 100);
}

public int
query_nibble_max_amount()
{
    return Nibble_max;
}

public int
query_nibble_amount()
{
    return Nibble_amount;
}

init()
{
    ::init();

    add_action(nibble_food, "nibble");
}

public string
long_desc()
{
    int perc = Nibble_amount * 100 / Nibble_max;

    if (perc == 0)
        return Old_long + "The "+short()+" has not been eaten yet.\n";
    else if (perc < 20)
        return Old_long + "The "+short()+" has been nibbled on just a bit.\n";
    else if (perc < 40)
	return Old_long + "The "+short()+" has been nibbled on a little bit.\n";
    else if (perc < 60)
	return Old_long + "The "+short()+" has been nibbled on.\n";
    else if (perc < 80)
	return Old_long + "The "+short()+" has been nibbled on quite a bit.\n";
    else if (perc < 100)
	return Old_long + "The "+short()+" has been almost totally eaten.\n";
    else 
	return Old_long + "The "+short()+" has been eaten entirely.\n";
}

int
nibble_food(string str)
{
    object food;

    notify_fail("Nibble what?\n");
    if (!str)
	return 0;

    if (Nibble_max <= 1)
        return 0;

    if (!parse_command(str, environment(this_object()), "[on] [the] %o",
	food))
	return 0;

    if (food != this_object())
	return 0;

    if (Nibble_amount >= Nibble_max)
    {
        write("Somehow you did not realize that your "+short()+" was already "+
	    "eaten!\n");
	remove_food();
	return 1;
    }

    if (!this_player()->eat_food(Food_amount, 1))
    {
	write("Even a nibble of the "+short()+" is too much for you.\n");
	return 1;
    }


    if (Nibble_amount + 1 == Nibble_max)
    {
	write("You finish off the "+short()+".\n");
	say(QCTNAME(this_player()) + " finishes off the "+short()+".\n");

        this_player()->eat_food(Food_amount);

	remove_food();
	return 1;
    }

    write("You nibble on the "+short()+", enjoying the taste.\n");
    say(QCTNAME(this_player())+" nibbles on the "+short()+", enjoying "+
	"the taste.\n");

    this_player()->eat_food(Food_amount);

    add_nibble();
    return 1;
}
