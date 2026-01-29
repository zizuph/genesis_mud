// file name:   /d/Emerald/docks/pav_pub.c
// creator(s):  Casca 02/21/00
// last update: 
// purpose:     
// note:        
// bug(s):      
// to-do:       

inherit "/d/Emerald/std/room";
inherit "/lib/pub";
inherit "/lib/trade";

#include "defs.h";
#include "/sys/money.h"
#include <subloc.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <cmdparse.h>

static object waitress;

public void sit_down(string str);

#define MY_PRICES ({11,13,71,189})

create_emerald_room() {
    set_short("The Travellers Retreat");
    set_em_long(
        "You are standing in a large open air pub. "+
        "The thatched roof is supported by roughly carved "+
        "oak trucks and the floor is a fine white sand. "+
        "Several plain tables and chairs are under the the "+
        "cover of the roof, while a few are out in the elements. "+
        "To the north of the area is the bar and behind it is "+
        "an open kitchen where the meals are cooked. "+
        "A raised platform to the west hold a small band "+
        "playing light upbeat melodies. "+
        "Two sandy paths lead back to the center of the pavilion "+
        "towards the east and south.\n");


    add_prop(ROOM_I_INSIDE, 1);
    add_prop("_room_i_sunlight", 1);

    add_exit("pav6","east");
    add_exit("pav5", "south");

    config_default_trade();
    set_money_give_out(({10000,700,1,3}));
    set_money_give_reduce(({0,4,0,6}));

    add_drink("water","water","fresh", 90, 0, MY_PRICES[0],
             "glass of water", "glasses of water",
             "It is simply water, sparkling fresh and clear.\n",0);

    add_drink(({"pint","ale"}),({"pint","ale"}),"strong",110,33,MY_PRICES[1],
             "pint of strong ale", "pints of strong ale",
             "The strong ale is of prime quality. It was brewed "+
             "in and imported from Telbarin.\n", 0);

    add_drink("wine", "wine", "white", 70, 40, MY_PRICES[2],
             "glass of white wine", "glasses of white wine",
             "This light white wine is pressed from "+
             "the ripened grapes that were harvested in the "+
             "famous vineyards west of Telbarin.\n", 0);

    add_drink("whiskey", "whiskey", "dark",10, 60, MY_PRICES[3],
             "glass of whiskey", "glasses of whiskey",
             "The dark whiskey is a caramel brown and has a strong "+
             "smell to it.\n",0);

     reset_room();
}

init() {
   ::init();
   init_pub();
   add_action("do_read","read",0);
}


do_read(str) {
   if (!str || str == "")
      return 0;
   if (str == "pricelist" || str == "list" || str == "menu")
   {
      write(price_long());
      return 1;
   }
   return 0;
}

price_long() 
{
   return (
      "The pricelist reads:\n\n"
    + "   Fresh Water         -   " + MY_PRICES[0] + " copper coins\n"
    + "   Strong Ale          -   " + MY_PRICES[1] + " copper coins\n"
    + "   Light White Wine    -   " + MY_PRICES[2] + " copper coins\n"
    + "   Whiskey             -   " + MY_PRICES[3] + " copper coins\n");
}
/*
reset_room()
{
  if (!waitress)
   {
      waitress = clone_object(NPC + "waitress");
      waitress->arm_me();
      waitress->move_living("M", this_object());
    }
}
*/

public int
sit(string str)
{
    mixed *oblist;

    if (!parse_command(str, all_inventory(), "[down] [at] [the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        if (!parse_command(str, ({}), "[down] [at] 'table' %w", str) ||
            (member_array(str, query_sublocs()) < 0))
	{
            notify_fail("Sit where?\n");
	    return 0;
	}
    }
    else if (sizeof(oblist) > 1)
    {
        notify_fail("You can only sit at one table at a time.\n");
        return 0;
    }
    else
    {
        str = oblist[0]->query_subloc();
    }

    sit_down(str);
    return 1;
}

public int
stand(string str)
{
    string subloc;

    if (subloc = this_player()->query_subloc())
    {
        write("You stand up from " + (this_player()->query_subloc()) + ".\n");
        say(QCTNAME(this_player()) + " stands up from " +
            (this_player()->query_subloc()) + ".\n");

        this_player()->move(this_object());
	query_table(subloc)->remove_diner(this_player());
	return 1;
    }

    notify_fail("You are not sitting!\n");
    return 0;
}


void
sit_down(string str)
{
    if ((this_player()->query_subloc()) == str)
    {
        write("You are already sitting at "+ str +".\n");
    }
    else
    {
        if (this_player()->query_subloc())
        {
            write("You stand up from " + (this_player()->query_subloc()) +
                " and walk over to " + str + ".\n");
            say(QCTNAME(this_player())+ " stands up from "+
            (this_player()->query_subloc()) +" and walks over to "+str+" .\n");

            this_player()->move(this_object());
        }

	if (query_table(str)->add_diner(this_player()))
	{
            this_player()->move(this_object(), str);
            write("You sit down at " +str+".\n");
            say(QCTNAME(this_player()) +" sits down at " +str+ ".\n");
        }
        else
        {
            write("All the seats around this table are occupied.\n");
	}
    }
}

public string
show_subloc(string subloc, object ob, object for_obj)
{
    object *livings = FILTER_LIVE(subinventory(subloc));

    if (sizeof(livings))
    {
        return capitalize(COMPOSITE_LIVE(livings)) +
            ((sizeof(livings) == 1) ? " is " : " are ") + "sitting " +
            "at "+subloc+".\n";
    }

    return "";
}


public int
subloc_access(string sloc, object ob, string acs, object for_obj)
{
    return 0;
}

int
table_talk(string str)
{
    if (this_player()->query_subloc())
    {
    	int i;
        string subloc = this_player()->query_subloc();
        object *others = subinventory(subloc) - ({ this_player() });

        for(i = 0; i < sizeof(others); i++)
        {
           others[i]->catch_tell((this_player()->query_The_name(others[i])) +
               " quietly says: " + str + "\n");
        }

        write("You quietly say: " + str + "\n");
    }
    else
    {
        write("You are not sitting at a table.\n");
    }

    return 1;
}

void
init()
{
    ::init();
    add_action(sit, "sit");
    add_action(stand, "stand");
    add_action(table_talk, "tsay");
}
