inherit "/std/object";
#include <stdproperties.h>

#define PIG "/d/Terel/dust/pig"


do_check()
{
    int i,j,found;
    object *us,*in,pig;

    us = users();
    for (i=0; i<sizeof(us); i++)
    {
	if (interactive(us[i]))
	{
	    in = deep_inventory(us[i]);
	    found = 0;
	    for (j=0; j < sizeof(in) && !found; j++)
		found = (in[j]->query_name() == "pig");
	    if (!found)
	    {
		pig = clone_object(PIG);
		pig->move(us[i]);
		tell_object(us[i],break_string(
			"A marchpand pig magically appeared in " +
			"your hands - a gift from the wizards of " +
			"Dville and Terel!\n",70));
	    }
	}
    }
    call_out("do_check",30);
}

create_object()
{
    set_name("pigger");
    add_prop(OBJ_I_NO_GET,1);
    add_prop(OBJ_I_INVIS,1);
    do_check();
}
