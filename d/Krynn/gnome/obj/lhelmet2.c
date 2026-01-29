/** Navarre July 22nd 2007, fixed runtime, and increase duration. */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

/* Prototypes */
void outout(object player);

void
create_armour()
{
    seteuid(getuid());
    set_name("helmet");
    set_short("gnomish mining helmet");
    set_adj("gnomish");
    set_long(BS(""+
      	"A sturdy helmet made mostly of metal.  A curious polished bowl "+
      	"shape is perched on the front with a wax candle and a little "+
      	"spring-loaded contraption holding a piece of flint.  A label "+
      	"is stamped into the rim."+
      	"", 70));
    add_item(({"label","label on helmet","helmet label"}), "@@read");
    set_ac(12);
    set_am(({1, 1, -2})); /* impale, slash, bludgeon armor mods */
    set_at(A_HEAD);
}

void
init()
{
    ::init();
    add_action("do_read", "read");
    add_action("flick", "flick");
}

void
candle()
{
    write("The candle on your helmet sheds a dim illumination.\n");
    say("A candle on " + QTNAME(TP) + "'s helmet begins to burn.\n");
    add_prop(OBJ_I_LIGHT, 1);
    set_alarm(itof(300 + random(10)), 0.0, &outout(TP));
}

int
flick()
{
    if (!query_worn())
    {
    	write("You have to wear the helmet to safely use the light!\n");
    	return 1;
    }
    write("You flick the switch on the side of your helmet." +
	"  A little spark strikes the\nwick of the candle!\n");
    say(QCTNAME(TP) + " does something to " + TP->query_possessive() +
	" helmet.\n");
    candle();
    return 1;
}


void
outout(object player)
{
    if(player)
    {
        write("The candle flickers out.\n");
	say("The candle on " + QTNAME(player) + "'s helmet flickers and goes out.\n");
    }
    add_prop(OBJ_I_LIGHT, 0);
}

string
read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
           "This product can: 'flick'" +
    	   "\n";
}

int
do_read(string str)
{
    if (str == "label" || str == "label on helmet")
    {
        write(read());
        return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
