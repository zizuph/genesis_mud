/* Created by Dajala
 * Baking is easy with the MasterBakerFritter!
 */

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

int baking_time;
string type;

void
create_food()
{
	set_name("fritter");
	add_name("@@fruit");
	set_adj("delicious");
	add_adj("@@colour");
	set_short("@@short_desc");
	set_long("@@long_desc");
	add_prop(OBJ_I_VALUE, 10);
}

void
set_fruit(string str)
{
	type = str;
}

string
colour()
{
	if(baking_time < 5)
		return "nearly white";
	if(baking_time > 7)
		return "blackened";
	else
		return "light brown";
}
				
void
set_durch(int time)
{
	baking_time = time;
}

string
short_desc()
{
	return colour() + " " + type + "-fritter";
}

string
long_desc()
{
	string str;
	
	str = "Made with a " + type + " this fritter smells delicious. ";
	if(baking_time < 5)
		str += "Unfortunately, it is been baked too short.\n";
	else if(baking_time > 7)
		str += "Unfortunately, it is slightly burned.\n";
	else
		str += "It is perfectly cooked.\n";
	return str;
}

string
fruit()
{
	return type + "-fritter";
}

void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + ".\n");
    if(baking_time < 5)
    	write("It tastes worse than it smelled.\n");
    else if(baking_time > 7)
    	write("You have a hard time chewing this piece of coal.\n");
    else
    	write("It tastes wonderful!\n");
    say(QCTNAME(TP) + " " + vb + "s " + str + ".\n");
}
