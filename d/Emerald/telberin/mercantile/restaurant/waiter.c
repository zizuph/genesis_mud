#pragma strict_types

inherit "/d/Emerald/std/elf";
inherit "/d/Genesis/lib/intro";


#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <money.h>
#include <const.h>

#define TITLE(ob) ((ob->query_gender() == G_FEMALE) ? "M'lady" : "Sir")
#define WAITER_I_BUSY "_waiter_i_busy"

static mapping order_map = ([]);
static object *menu_list = ({});
static int return_alarm = 0;

void deliver_order(object food,object customer);
string description(); 

public void
load_food(string file)
{
    object food;

    setuid();
    seteuid(getuid());
   
    LOAD_ERR(file);
    if (!(food = find_object(file)))
    {
        return;
    }

    menu_list += ({ food });
}


public void
create_elf()
{
    set_short("calm haughty male elf");
    set_long(description);
    add_adj("calm");
    add_adj("haughty");
    config_elf(70);

    map(({ TELBERIN_RESTAURANT_DIR + "steak" }), load_food);
}

string
description()
{
    string desc = 
        "This elf is wearing a formal black and white uniform that clearly " +
        "marks him as the waiter of this establishment. He bears an erect " +
        "posture and he has a calm but friendly expression on his face. ";

    if (query_subloc())
    {    
        desc += "He is presently occupied with " + query_subloc() + " .\n";
    }
    else
    {    
    	desc += "He is standing by the large window and it looks like " +
            "he is deep in thought as his stares out towards the lake.\n";
    }
    
    return desc;
}        

void
return_to_post()
{
    if (query_prop(WAITER_I_BUSY))
    {
	return;
    }

    remove_alarm(return_alarm);

    if (query_subloc())
    {
        command("tsay Pardon me.  I will give you more time....");
        command("emote moves back to his position by the window.");
        move(environment());
    }
}	


public void
approach_table(string subloc)
{
    move(environment(), subloc);
    return_alarm = set_alarm(15.0, 15.0, return_to_post);
}          

public void
leave_table()
{
    if (query_subloc())
    {
	move(environment());
    }

    remove_alarm(return_alarm);
    return_alarm = 0;
}
    
void
order(object food,object customer)
{
    object *orders;

    orders = order_map[customer->query_subloc()];
    orders = (pointerp(orders) ? orders + ({ food }) : ({ food }));
    order_map[customer->query_subloc()] = orders;

    tell_room(environment(),"The waiter nods slightly at " + 
        QTNAME(customer) + " and walks into the kitchen.\n");

    set_alarm(10.0,0.0, &deliver_order(food, customer));

    // Do the move last, since it's most likely to encounter unexpected
    // runtime errors.
    move(TELBERIN_RESTAURANT_DIR + "kitchen");
}


void
deliver_order(object food,object customer)
{
    move(TELBERIN_RESTAURANT_DIR + "restaurant");

    if (present(customer, environment()) && customer->query_subloc())
    {              
        string path;
        object c_food;
	object table;

        path=MASTER_OB(food);
        c_food=clone_object(path);
        tell_room(environment(),
            "The waiter comes out from the kitchen and " +
            "delivers " +LANG_ASHORT(food)+ " to " +           
            QTNAME(customer) +".\n");

	table = environment()->query_table(customer->query_subloc());
        c_food->move(table, customer->query_real_name());
    }
    else   
    {     
    	tell_room(environment(),"The waiter comes out of the kitchen.\n"); 
    
    }

}


int
call_waiter(string str)
{
    string subloc = this_player()->query_subloc();

    if(str == "waiter")
    {    
    	if (subloc)
        {
            if (query_subloc() == subloc)
            {
                write("The waiter is already standing by your table.\n");
	        return 1;
            }
	    
            write("You snap your fingers to attract the waiters " +
               "attention.\n");
            
            if (!query_subloc())
            {
                write("The waiter glances in your general direction and " +
                    "graciously moves towards your table.\n");
                say("The waiter glances in the direction of "+subloc+
                    " and graciously moves towards it.\n");

		approach_table(subloc);

                command("tsay How may I serve you, " + TITLE(this_player()) +
			"?\n");
            }
            else
            {
                write("The waiter is occupied at another table.\n");
            }
        }
        else
        {
            write("You must sit at a table to call a waiter.\n");
	}
    }
    else
    {
    	notify_fail("Call whom?\n");
	return 0;
    }	
    
    return 1;
}


object
verify_order(string str)
{
    mixed *obs;

    if (!parse_command(str, menu_list, "[the] [a] %i", obs))
    {
        return 0;
    }
    
    if (sizeof(obs) > 2)
    {
        return 0;
    }
     
    return obs[1];
}


int
place_order(string str)
{
    string subloc;
    object item;

    if (!(subloc = this_player()->query_subloc()))
    {
        write("You will need to take a seat at a table first.\n");
        return 1;
    }

    if (!query_subloc())
    {
        write("You will need to call the waiter to your table first.\n");
        return 1;
    }

    if (subloc != query_subloc())
    {
        write("The waiter appears to be busy at the moment.\n");
        return 1;
    }

    item = verify_order(str);	

    if (item)
    {
        order(item, this_player());
        return 1;
    }
    
    notify_fail("Order what?\n");
    return 0;
}

public int
give_bill(object player)
{
    int i;	
    object bill, table, *orders;
    string subloc = this_player()->query_subloc();

    if (!subloc)
    {
	return 0;
    }

    orders = order_map[subloc];

    if (!sizeof(orders))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());
    bill = clone_object(TELBERIN_RESTAURANT_DIR + "bill");
    bill->set_order(orders);

    table = environment()->query_table(subloc);
    if (!table)
    {
	command("give " + OB_NAME(bill) + " to " + OB_NAME(player));
    }
    else
    {
        command("emote places the bill on the table.");
        bill->move(environment()->query_table(subloc), 1);
    }

    return 1;
}

int
bill(string str)
{
    string subloc = this_player()->query_subloc();

    if (subloc && (subloc == query_subloc()))
    {
        give_bill(this_player());
    }

    return 1;
}


int
pay_bill(string str)
{
    object *orders;
    int i, total;

    if (str == "bill")
    {
        string subloc = this_player()->query_subloc();
        if (subloc && (subloc == query_subloc()))
        {
            int amount = 0;

            orders = order_map[subloc];

	    if (!sizeof(orders))
	    {
    	        move(environment(), subloc);
		command("tsay But you don't owe anything, " +
                    TITLE(this_player()) + "....");
		move(environment());
		return 1;
	    }

	    for (i = 0; i < sizeof(orders); i++)
	    {
		total += orders->query_prop(HEAP_I_UNIT_VALUE);
	    }
	    
            if (!MONEY_ADD(this_player(), -total))
            {
                command("tsay I am sorry, " + TITLE(this_player()) +
                    ", but you don't seem to have enough.");
            }    
            else
            {
            	write("You count up the correct amount and give the money " +
              	    "to the waiter.\n");
		order_map = m_delete(order_map, subloc);
	    }

	    return 1;
    	}
    }
    else
    {
        notify_fail("Pay what?\n");
        return 0;
    }
}        

public void
init_living()
{
    ::init_living(); 
    add_action(call_waiter, "call");
    add_action(place_order, "order");
    /*add_action(absent, "complain");*/
    add_action(bill, "check");
    add_action(pay_bill, "pay");
}
