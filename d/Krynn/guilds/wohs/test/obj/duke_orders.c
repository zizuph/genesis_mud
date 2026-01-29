/* The orders from the Duke about to attack the Tower of Daltigoth
 * Part of the Test content
 */

inherit "/std/scroll";
inherit "/lib/keep";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

#define SCROLLFILE "/d/Krynn/guilds/wohs/test/obj/orders.txt"
#define SCROLL_I_FURLED "_scroll_i_furled"

int steal_attempt = 0;

void
check_if_in_test()
{
    set_alarm(60.0, 0.0, "do_i_dispel");
}

void
remove_illusionary_object()
{
   remove_object();
}

void
do_i_dispel()
{
    object room = TO;
    object person = TO;

    while(E(room))
      room = E(room);

    if(E(TO) != room)
      while(person && !(interactive(person)))
	person = E(person);

    if(room && file_name(room))
      if(file_name(room)[0..30] != "/d/Krynn/guilds/wohs/test/room/")
      {
         person->catch_msg("The " +TO->short()+ " dissipate! It was " +
           "nothing but an illusion!\n");
         set_alarm(0.3, 0.0, "remove_illusionary_object");
      }
      else
	set_alarm(120.0, 0.0, "do_i_dispel");

    return;
}

void
create_scroll()
{
    set_name("orders");
    add_name("scroll");
    add_name("_wohs_test_duke_orders");
    set_pname("orders");
    add_pname("scrolls");
    add_adj("military");
    set_short("furled military orders");
    add_adj("furled");
    set_long("These military orders are currently furled.\n");
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 50 + (random(50)));
    add_prop(SCROLL_I_FURLED, 1);
    add_prop(OBJ_M_NO_STEAL, "The orders are stuck underneath the scout. " +
         "You are unable to steal them from him.\n");

    set_file(SCROLLFILE);
    check_if_in_test();
}

init()
{
    ADA("furl");
    ADA("unfurl");
    ::init();
}

int furl(string str)
{
    if((str=="orders")||(str=="military orders")||
      (str=="scroll")||(str=="military scroll"))
    {
        if (TO->query_prop(SCROLL_I_FURLED))
        {
            write("The " + query_short() + " is already furled!\n");
            return 1;
        }
        write("You furl the " + query_short() + ".\n");
        say(QCTNAME(TP) + " furls the " + QSHORT(TO) + ".\n");
        TO->add_prop(SCROLL_I_FURLED, 1);
        TO->remove_adj("unfurled");
        TO->set_short("furled military orders");
        TO->add_adj("furled");
        TO->set_long("This military orders are currently furled.\n");
        return 1;
    }
    NF("Furl what?\n");
    return 0;
}

int unfurl(string str)
{
    if((str=="orders")||(str=="military orders")||
       (str=="scroll")||(str=="military scroll"))
    {
        if (!(TO->query_prop(SCROLL_I_FURLED)))
        {
            write("The " + query_short() + " is already unfurled!\n");
            return 1;
        }
        write("You unfurl the " + query_short() + ".\n");
        say(QCTNAME(TP) + " unfurls the " + QSHORT(TO) + ".\n");
        TO->remove_prop(SCROLL_I_FURLED);
        TO->remove_adj("furled");
        TO->set_short("unfurled military orders");
        TO->add_adj("unfurled");
        TO->set_long("These unfurled military orders describe " +
            "instructions provided by the Ergothian Praetor-General to " +
            "one of his scouts.\n");
        return 1;
    }
    NF("Unfurl what?\n");
    return 0;
}

public int
read_access(object ob)
{
    if (ob->query_prop(SCROLL_I_FURLED))
    {
        NF("You can only read unfurled orders!\n");
        return 0;
    }
    NF("You must be holding the orders to read it properly!\n");
    return ((E(ob) == TP) &&
      (function_exists("create_object", ob) == SCROLL_OBJECT));
}

/*
 * Function name: read_it
 * Description  : Perform the actual read. This function prints the text
 *                to the player and displays a message to the people in
 *                the room.
 * Arguments    : string - the command the player executed, only 'read'
 */
void
read_it(string str)
{
    int taskcheck;
    seteuid(getuid(TO));

    if (!scroll_file)
    {
        write("There was nothing to read on the " + QSHORT(TO) + ".\n");
        return;
    }

    if ((str == "read") &&
      (file_size(scroll_file) < 4000))
    {
        write("You read the " + query_short() + ".\n");
        say(QCTNAME(TP) + " reads the " + QSHORT(TO) + ".\n");
        cat(scroll_file);
    }
    else
    {
        if (file_size(scroll_file) >= 50000)
        {
            write("The scroll is too large to be read.\n");
            return;
        }
        TP->more(read_file(scroll_file));
    }
}
