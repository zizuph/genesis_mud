/*
 * Mortis 02.2006 
 *
 * Laethorian pool towel.
 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>

inherit "/std/object";

#define WET				"i_am_wet"
#define TOWEL			"_i_have_not_returned_towel"
#define PTOWEL			"_laethorian_pool_towel"
#define WET_SUBLOC		"wet_subloc"

int	wet;
string give_it_prop();

public void
create_object()
{
    set_name("towel");
	add_name("_laethorian_pool_towel");
    add_adj(({"white", "pool"}));
	set_short("@@my_short");
	set_pshort("@@my_pshort");
    set_long("@@my_long");
    add_prop(OBJ_I_WEIGHT, 100 + random(20));
    add_prop(OBJ_I_VOLUME, 100 + random(20));
    add_prop(OBJ_I_VALUE, 0);
	set_alarm(1.0, 0.0, give_it_prop);
}

string
my_short()
{
    if (wet)
	return "wet white pool towel";

	return "white pool towel";
}

string
my_pshort()
{
    if (wet)
	return "wet white pool towel";

	return "white pool towels";
}

string
my_long()
{
    if (wet)
	return "This short white towel is sopping wet.  It has a black \"L\""
	+ "embroidered in its corner.";

	return "This short white towel is not very thick but could be used to "
	+ "<dry> yourself off.  It has a black \"L\" embroidered in its corner.";
}

string give_it_prop()
{
	add_prop(PTOWEL, 1);
	return "";
}

int
get_wet()
{
	wet = 1;
	write("Your towel is rather wet now.\n");
	return 1;
}

public void
init()
{
    ::init();
    ADD("do_dry", "dry");
}

int
do_dry(string str)
{
	NF("Dry yourself off?\n");

    if (!str)
		return 0;

	if (!parse_command(str, ({}), "'me' / 'myself' [off]"))
		return 0;

    if (!TP->query_prop(WET))
    {
        write("You are already dry.  Congratulations.\n");
        return 1;
    }

	NF("Your " + short() + " is too wet to dry yourself off with.\n");
    if (wet)
		return 0;

    TP->remove_prop(WET);
	TP->remove_prop(WET_SUBLOC);

    write("You dry yourself off with your " + short() + ".\n");
    say(QCTNAME(TP) + " dries " + HIMSELF(TP) + " off with " + HIS(TP)
	+ " " + short() + ".\n");

    get_wet();

    return 1;
}
