#pragma strict types
// file name:	/d/Avenir/common/bazaar/museum/obj/coffee.c
// creator(s): 
// last update:	Denis, May'00: There were some funs copied from /std/drink
//                             and causing errors. Why? Deleted them.
//			       The file shrunk 5k.
//
//	Lucius May 2009: Some cleanups, added sobriety enhancement.
//
inherit "/std/drink";
inherit "/d/Avenir/common/lib/sober";

#include <macros.h>
#include <stdproperties.h>

public void
create_drink(void)
{
    set_name("kahve");
    add_name(({"coffee", "hkahve"}));
    set_adj(({"sybarun", "hot"}));
    set_short("hot sybarun kahve");
    set_pshort("hot sybarun kahves");
    set_long("Dark and aromatic, topped with thick cream, "
        +"this hot sybarun kahve is more than a beverage. "
        +"It is an experience.\n");

    set_soft_amount(500);
    set_alco_amount(0);
    set_drink_msg("Mmmm... The delightfully intense flavour "
        +"floods your senses.\n");

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop("_drink_created", time());
}

public int
drink_it(string str)
{
    mixed res;

    if (str != "coffee" && str != "kahve") {
	return notify_fail(capitalize(query_verb()) + " what?\n");
    }

    if (!(res = command_drink())) {
	return notify_fail(capitalize(query_verb()) + " what?\n");
    }

    if (stringp(res))
    {
	write(res);
	return 1;
    }

    write("You " + query_verb() + " " + short() + ".\n");
    say(QCTNAME(this_player()) + " " + query_verb()  + "s" +
	" " + short() + ".\n");

    /* Remove the drinks after we are through */
    set_alarm(0.1, 0.0, remove_drink);
    return 1;
}

public int
drink_test(string str)
{
    if (!strlen(str))
        return 0;       

    if (str == "all")
    {
        write("You try to drink "+ short() +" too quickly, "
            + "and burn your tongue! Ouch.\n");
        say(QCTNAME(this_player()) + " burns "
                + this_player()->query_possessive() +" tongue on "
                + this_player()->query_possessive() +" "+ short() +".\n");
        return 1;
    }

    if (str == "coffee" || str == "kahve") 
    {
        if ((query_prop("_drink_created") + 600) > time())
        {
            write(capitalize(short()) +" is still too hot to drink. "
                +"Perhaps you should just sip it a while longer.\n");
            return 1;
        }
        else
        {
            drink_it(str);
            return 1;
        }
    }
    return 0;
}

public int 
do_sip(string str)
{
    if (str != "kahve" && str != "coffee") {
        return notify_fail("Sip what?\n");
    }

    write("You take a sip of the sybarun kahve with cream.\n"+
	"You close your eyes as an intensely delightful "+
	"flavour passes your lips to tantalize "+
	"your tongue, then inhale deeply of the strong, "+
	"roasted-bean aroma.\n");
    say(QCTNAME(this_player())+ "'s eyes close and a pleased "+
	"expression crosses "+ this_player()->query_possessive() +
	" face as "+ this_player()->query_pronoun() +
	" takes a sip of a hot sybarun kahve.\n");

    return 1;
}

public void
special_effect(int num)
{
    set_alarm(0.0, 0.0, &make_sober(this_player(), 0));
}

void
init()
{
    ::init();
    add_action(do_sip,     "sip");
    add_action(drink_test, "drink");
    add_action(drink_it,   "guzzle");
}
