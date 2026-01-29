/**
* Coded by Louie 2004
* 
* Request Form / Waiver
* A player receives this after signing a request form at the main desk
* of the gnomish explosive center (expl1.c).  It's the first piece
* of paperwork that a player has to manage to do the "build a bomb"
* quest.  
*
* If the player has the form approved by the designer gnome (design_gnome.c)
* they increase their chances of successfully building a bomb, and may
* also receive some bonus xp for going through the red tape.
*
*/
#pragma strict_types

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

/* prototypes*/
void set_owner(string str);
public string query_owner();
public void approve();
void remove_me();
public int is_approved();

string longDesc = "This form details a request to design and " +
"build an explosive device.  " +
"It also serves as a " +
"waiver, freeing the Explosives Development Center of " +
"Gnomish Industries from any liability in the event " +
"all of your body parts spontaneous move away from each " +
"other at a very high rate of speed.  ";
string signedDesc;

int approved;
string owner;

void
create_object()
{
	owner = "";
    set_name("form");
    add_name("waiver");
    add_name("_gnome_request_form");
    set_short("gnomish explosives request form");
    set_adj("request");
    add_adj(({"gnomish","explosives"}));
    set_long(longDesc +"\n");
    approved = 0;

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);

}

void
set_owner(string str)
{
	owner = str;
    signedDesc = "It has been signed by " +
    str + ".  ";
    set_long(longDesc + signedDesc + "\n");

}

public string
query_owner()
{
	return owner;
}

public void
approve()
{

    set_long(longDesc + signedDesc + 
      "It has been stamped with the official seal of " +
      "approval of the Explosives Development Center " +
      "of Gnomish Industries.\n");
    approved = 1;
}

public int
is_approved()
{
	return approved;
}

void
leave_env(object old, object dest)
{
	::leave_env(old, dest);
	set_alarm(0.5,0.0,"remove_me");
}

void
remove_me()
{
	if (!living(environment(TO)))
	{
		tell_room(environment(TO),"The " + query_short() +
			" gets caught by the wind and is lost.\n",0);
		remove_object();
	}
}
