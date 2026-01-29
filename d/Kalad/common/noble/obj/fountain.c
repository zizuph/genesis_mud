inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Kalad/defs.h"
/* Sarr */
/* updated water prop Damaris - 08/2002 */

void
create_object()
{
    set_name("fountain");
    set_adj("beautiful");
    add_adj("water");
    set_short("beautiful water fountain");
    set_long("This is a beautiful water fountain made of shiny white "+
      "stone. It is a half-circle with a pool at the center. A statue "+
      "of nude, well-muscled man stands in the center, holding up a "+
      "flower. Out of the flower, clear blue water spouts out, and runs "+
      "down his body and into the pool. You see little fishes swimming "+
      "around in there too.\n");
    add_prop(OBJ_M_NO_GET,"Are you mad?\n");
    add_prop(OBJ_I_CONTAIN_WATER, 1);
}


int
drink_it(string str)
{
    string what, where;
    int i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    /* See if syntax is "drink <something> from <something>" */
    if (sscanf(str, "%s from %s", what, where) != 2)
    {
        /* See if syntax is "drink from <something>" */
        if (!sscanf(str, "from %s", where))
        {
            /* Syntax must simply be "drink <something>" */
            what = str;
        }
    }

    if (what && !parse_command(what, ({}), "[the] / [some] 'water'"))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (where && !parse_command(where, ({}), "[the] 'fountain' "))
    {
        /* Technically, this isn't going to show because of the standard
         * 'drink' command.  Really, there's not much choice, though,
         * since we don't want to return 1.
         */
        notify_fail("Drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("You take a gulp of water from the fountain. Having " +
            "drunk your fill, you feel refreshed. Ahh!\n");
    }
    else
    {
        write("You take a drink of the cool water.\n");
    }

    say(QCTNAME(this_player()) +" drinks some water from the "+
       "fountain.\n");
    return 1;
}

void
init()
{
    ::init();
    
    set_alarm(10.0,0.0,"bubble",TP);
    add_action(drink_it, "drink");
}

void
bubble(object ob)
{
    if(present(ob,E(TO)))
    {
	set_alarm(50.0,0.0,"bubble",ob);
	ob->catch_msg("The water makes little bubbling noises as it "+
	  "spouts out of the flower.\n");
    }
}

