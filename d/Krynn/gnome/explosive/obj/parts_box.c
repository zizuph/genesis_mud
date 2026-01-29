/**
* Coded by Louie 2004
* 
* Box of Parts.
* This object is a required quest piece received from the parts shop
* of the gnomish explosive center (expl5.c) and used to construct a 
* prototype explosive device in the manufacturing room (expl9.c).
*
*/
#pragma strict_types

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

/** prototypes **/
public int get_size();
public void set_size(int i);
string longDesc();
int size;
void remove_me();

/*
* Create
*/
void
create_object()
{
	
    set_name("box");
    set_short("@@longDesc@@" +
    	" gnomish box of parts");
    set_adj("parts");
    add_name(({"parts","components"}));
    add_name("_gnome_parts_box");
    add_adj(({"gnomish","parts"}));
    set_long("This is a " + 
    	"@@longDesc@@" + 
    	" box of gnomish parts.  " +
		"The components are used to construct an explosive device.\n");
    size = 0;
	
	add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);

}

string
longDesc()
{
	string desc;
	
	desc = "humongous";
	
	if (size < 25) {
		desc = "very large";
	}

	if (size < 15) {
		desc = "large";
	}

	if (size < 10) {
		desc = "small";
	}
	
	if (size < 5) {
		desc = "tiny";
	}
	
	
	return desc;
}

public void
set_size(int i)
{
	size = i;
}

public int
get_size()
{
	return size;
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
	tell_room(environment(TO),"The box cracks open and all the parts " +
		"scatter, becoming immediately lost.\n",0);
	remove_object();
}