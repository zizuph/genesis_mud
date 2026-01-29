#pragma save_binary

inherit "/std/shadow";

#include "../guild.h"
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>

#define SW	shadow_who

private object uniform;

void
set_uniform(object uni)
{
    uniform = uni;
}

public object
query_worn_uniform()
{
    if (uniform->query_worn() == SW)
	return uniform;
    return 0;
}

public string
show_worn(object for_obj)
{
    object *worn, *underuni = ({ });
    int i, j, slots;
    string show, name, *tmp, *names = ({ });

    if (!objectp(uniform) || uniform->query_worn() != SW)
    {
	set_alarm(0.0, 0.0, remove_shadow);
	return SW->show_worn(for_obj);
    }

    worn = SW->query_clothing(-1);
    for(i = sizeof(worn)-1; i >= 0; i--)
    {
	if (worn[i] != uniform)
	{
	    slots = worn[i]->query_slots_setting();
	    if (slots != A_SHIELD && 
		(slots & (A_BODY | A_TORSO | A_CHEST | A_ARMS | A_LEGS)))
		underuni += ({ worn[i] });
	}
    }
    worn -= underuni;
    show = ((for_obj == SW) ? "You are" : C(HE(SW)) + " is") +
	    " wearing " + COMPOSITE_FILE->fo_desc_dead(worn, for_obj, 1);
    if (sizeof(underuni))
    {
    	for (i=0; i<sizeof(underuni); i++)
    	{
    	    name = "something";
    	    tmp = underuni[i]->query_names();
    	    for (j=0; j<sizeof(tmp); j++)
    		if (!wildmatch("*_*",tmp[j]))
    		{
		    name = tmp[j];
		    j = sizeof(tmp);
    		}
    	    names += ({ name });
    	}
	show += ". Under the uniform you " +
		((for_obj == SW) ? "wear " : "notice ") +
		COMPOSITE_WORDS(names);
    }
    return show + ".\n";
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (!objectp(uniform) || uniform->query_worn() != SW)
    {
	set_alarm(0.0, 0.0, remove_shadow);
	return SW->show_subloc(subloc, on, for_obj);
    }
    if (subloc == SUBLOC_WORNA)
    {
	return show_worn(for_obj);
    }
    return SW->show_subloc(subloc, on, for_obj);
}
