/*
  
  by Udana, /2006
*/

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define RANDOM_COLOURS ({ \
    "white", \
    "black", \
    "red", \
    "blue", \
    "yellow" \
})

string colour;
public string query_colour();
public void set_colour(string s);


string
query_arm_recover()
{
    return ::query_arm_recover() + "^C^" + colour;
}

void
init_arm_recover(string arg)
{
	string s_arg;
	sscanf(arg, "%s^C^%s", s_arg, colour);
	::init_arm_recover(s_arg);
}

public string
query_colour()
{
    if (!colour) colour = one_of_list(RANDOM_COLOURS);
    return colour;
}

public void
set_colour(string s)
{
    colour = s;
    add_adj(colour);
}