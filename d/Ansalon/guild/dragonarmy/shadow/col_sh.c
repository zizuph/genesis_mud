#pragma save_binary

inherit "/std/shadow";

#include "../guild.h"
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include <living_desc.h>
#include <const.h>

#define SW	shadow_who

private object uniform;
private string colour;

void
set_uniform(object uni)
{
    uniform = uni;
}


/* Function: query_nonmet_name
 * Desc: poor mask of normal function from std/living/description
 * 	since only two adj were displayed
 */
query_nonmet_name()
{
    string *adj, str;
    string gender;
    int	size_arr;

    if (SW->query_short())
	    return SW->query_nonmet_name();

    /* Get the gender description only if needed. */
    if (SW->query_humanoid() &&
        !SW->query_prop(LIVE_I_NO_GENDER_DESC) &&
        (SW->query_gender() != G_NEUTER))
    {
        gender =SW->query_gender_string() + " ";

    }
    else
    {
        gender = "";
    }

   if (sizeof((adj = query_adj(1))) > 0)
    {
       // str = implode(adj[..1], " ") + " " + gender +
        str = implode(adj[..2], " ") + " " + gender +
            SW->query_race_name() +
            (SW->query_wiz_level() ? (" " + LD_WIZARD) : "");
    }
    else
    {
        str = gender + SW->query_race_name() +
            (SW->query_wiz_level() ? (" " + LD_WIZARD) : "");
    }

    if (SW->query_ghost())
    {
        str += " " + LD_GHOST;
    }

    return str;
}

void
set_shadow_colour(string col)
{
	if (!col)
	colour = uniform->query_colour();
	else
		switch (col)
		{
		   case "red":
			colour = col;
			break;
		   case "blue":
			colour = col;
			break;
		   default:
			colour = "blue";
		}
}

query_adjs()
{
	return query_adj(1);
}

query_adj(int arg)
{
	string *adjs;

	if (!arg) 
	{
	    return (colour +"-uniformed");
	}
	else 
	{
	    adjs = SW->query_adj(-1);
	    if (!pointerp(adjs))
	    {
		    adjs = ({ });
	    }
	    return ({ colour +"-uniformed"}) + adjs;
	}
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
