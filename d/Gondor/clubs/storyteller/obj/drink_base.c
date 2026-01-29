/*
 * /d/Gondor/clubs/storytellers/obj/drink_base.c
 *
 * The storyteller drink base file, by Morrigan 10/2002
 *    allows a drink to be sipped to completion or drank
 *    normally
 */

inherit "/d/Gondor/clubs/storyteller/obj/std_drink";

#include "/sys/stdproperties.h"
#include <cmdparse.h>
#include <macros.h>

public void	set_sip_max_amount(int i);
public void	set_sip_amount(int i);
public void	add_sip();
public int	query_sip_max_amount();
public int	query_sip_amount();
public void	create_st_drink();
public void	setup_drink();
public int	sip_drink(string str);
public string	long_desc();

int Sip_max = 1, Sip_amount, Soft_max, Alco_max, Soft_amount, Alco_amount;
string Old_long;

void
create_st_drink()
{
}

void
create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("ale");
    set_adj("light");
    set_short("light ale");
    set_pshort("light ales");
    set_long("An ordinary light ale.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
 
    create_st_drink();
    setup_drink();
}

public void
setup_drink()
{
    Soft_max = query_soft_amount();
    Alco_max = query_alco_amount();
    Soft_amount = Soft_max / Sip_max;
    Alco_amount = Alco_max / Sip_max;
    Old_long = query_long();

    if (Sip_max > 1)
        set_long(&long_desc());
}

public void
set_sip_max_amount(int i)
{
    Sip_max = i;
}

public void
set_sip_amount(int i)
{
    Sip_amount = i;
}

public void
add_sip()
{
    int perc;

    Sip_amount = Sip_amount + 1;

    perc = 100 - (Sip_amount * 100 / Sip_max);

    /* Update the actual contents of the drink */
    set_soft_amount(Soft_max * perc / 100);
    set_alco_amount(Alco_max * perc / 100);
}

public int
query_sip_max_amount()
{
    return Sip_max;
}

public int
query_sip_amount()
{
    return Sip_amount;
}

init()
{
    ::init();

    add_action(sip_drink, "sip");
}

public string
long_desc()
{
    int perc = Sip_amount * 100 / Sip_max;

    if (perc == 0)
        return Old_long + "The "+short()+" is full.\n";
    else if (perc < 20)
        return Old_long + "The "+short()+" is almost full.\n";
    else if (perc < 40)
	return Old_long + "The "+short()+" is mostly full.\n";
    else if (perc < 60)
	return Old_long + "The "+short()+" is half full.\n";
    else if (perc < 80)
	return Old_long + "The "+short()+" is less than half full.\n";
    else if (perc < 100)
	return Old_long + "The "+short()+" is almost empty.\n";
    else 
	return Old_long + "The "+short()+" is empty.\n";
}

int
sip_drink(string str)
{
    object drink;

    notify_fail("Sip what?\n");
    if (!str)
	return 0;

    if (Sip_max <= 1)
        return 0;

    if (!parse_command(str, environment(this_object()), "[on] [from] [the] %o",
	drink))
	return 0;

    if (drink != this_object())
	return 0;

    if (Sip_amount >= Sip_max)
    {
        write("Somehow you did not realize that your "+short()+" was already "+
	    "empty!\n");
	remove_drink();
	return 1;
    }

    if (!this_player()->drink_soft(Soft_amount, 1))
    {
	write("Even a sip of the "+short()+" is too much for you.\n");
	return 1;
    }

    if (Alco_amount && !this_player()->drink_alco(Alco_amount, 1))
    {
	write("Even a sip of the "+short()+" is too strong for you.\n");
	return 1;
    }

    if (Sip_amount + 1 == Sip_max)
    {
	write("You sip on the "+short()+" until it is totally empty.\n");
	say(QCTNAME(this_player()) + " sips on the "+short()+" until it is "+
	    "totally empty.\n");

        this_player()->drink_soft(Soft_amount);
	if (Alco_max)
	    this_player()->drink_alco(Alco_amount);

	add_sip();
	remove_drink();
	return 1;
    }

    write("You sip on the "+short()+" slowly, savoring its flavour.\n");
    say(QCTNAME(this_player())+" sips on the "+short()+" slowly, savoring "+
	"its flavour.\n");

    this_player()->drink_soft(Soft_amount);
    if (Alco_max)
	this_player()->drink_alco(Alco_amount);

    add_sip();
    return 1;
}
