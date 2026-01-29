/* 
*  A Table for the Kitchen
*	Raymundo, Jan 2020
*/
#include "/d/Shire/defs.h"
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>




inherit "/std/object";
//keeps track of whether or not the pie has been eaten.
int the_pie = 1;


public void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("table");
    set_adj("kitchen");
    set_adj("wooden");
    set_adj("dinner");
    set_short("wooden kitchen table");
    set_long("This is a simple wooden table. It's the right size of three "
		+ "or four hobbits to sit around it and have breakfast, or second-"
		+ "breakfast, or elevenses, or any of the other numerous meals "
		+ "they eat throughout the day. " + "@@is_pie@@" + "\n");
    
	add_item( ({"top", "table top"}), "The table top is made of wood and "
		+ "looks well-used. " + "@@is_pie@@" + "\n.");
	add_item("pie", "@@exa_pie@@");
    
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 0);
 
    add_prop(OBJ_M_NO_SELL, 1);
}

void
init()
{
    ::init();
    add_action("table_top", "touch");
	add_action("get_pie", "get");
	add_action("get_pie", "take");
	add_action("get_pie", "snatch");
	add_action("get_pie", "appropriate");
	add_action("get_pie", "steal");
}

int
table_top(string str)
{
    if(str == "top" || str == "table top" || str == "table")
    {
        write("You touch the table top. It feels like wood.\n");
        tell_room(environment(TO), QCTNAME(TP) + " touches the top of "
            + "the table.\n", TP);
        return(1);
    }
    else
    {
        notify_fail("Huh?\n");
        return(0);
    }
}
  
//Returns the description of the pie, if it's there.  
string
is_pie()
{
	if(the_pie == 1)
	{
		return("A beautful fresh-made apple pie sits cooling on the table-top.");
	}
	else
	{
		return("");
	}
}
  
//let's you examine the pie
string
exa_pie()
{
	if(the_pie == 1)
	{
		return("The pie looks fresh-made. And it's an apple pie on top of "
			+ "that! You could probably take it from the table if you "
			+ "wanted.\n");
	}
	else
	{
		return("You find no pie.\n");
	}
}

//reset the pie
void
reset_pie()
{
	the_pie = 1;
	tell_room((EO), "You smell fresh-baked pie. Mmmmmm.\n");
}
//Get some pie!
int
get_pie(string str)
{
	if(!strlen(str))
	{

		return 0;
	}
	if(the_pie == 1)
	{
		if(str == "pie" | str == "the pie" | str == "apple pie" | str == "the apple pie" | str == "pie from table")
		{
			object apple_pie;
			apple_pie = clone_object(WAYM_FOOD_DIR + "apple_pie.c");
			apple_pie->move(TP);
			write("You get an apple pie from the table!\n");
			say(QCTNAME(TP) + " gets an apple pie from the table!\n");
			the_pie = 0;
			set_alarm(1800.0,0.0,"reset_pie");
			return 1;
		}
		else
		{
			notify_fail("Get what? The pie?\n");
			return 0;
		}
	}
	else
	{
		if(str == "pie" | str == "the pie" | str == "apple pie" | str == "the apple pie")
		{
		write("There is no pie to get!\n");
		return 1;
		}
		else
		{
			return 0;
		}
	}
}