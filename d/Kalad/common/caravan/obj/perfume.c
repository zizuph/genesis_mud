
/* Bottle of Perfume - by Antharanos 

   Mirandus - December 2018 - Fixed buggy code with respect to removal of 
   object when dropped 
*  Cotillion - January 2019 - Fixed object removal message when dropped.
*   07-01-2022 Meton - Capitalized NF of do_spray
*/

inherit "/std/object";
inherit "/lib/keep";
#include <macros.h>
#include "/d/Kalad/defs.h"
   
int uses=5;

create_object()
{
    set_name("perfume");
    add_name("bottle");
    set_adj("glass");
    add_name("glass bottle of perfume");
    set_short("glass bottle of perfume");
    set_long("@@my_long");
    add_prop(OBJ_I_VALUE,144);
    add_prop(OBJ_I_VOLUME,400);
    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_M_NO_SELL,1);
    set_keep();
}
string
my_long()
{
    string empty_desc;

    if (uses < 1)
	empty_desc = "The bottle is empty.";
    else
	empty_desc = "There looks to be a little perfume left inside.";

    return BS(
      "It is a small container used for perfumes. There is a small rubber "+
      "bulb at the top that can be used to spray the perfume. " + empty_desc + "\n");
}
init()
{
    ::init();
    AA(do_spray,spray);
    AA(do_spray,use);
}
do_spray(str)
{
    NF(capitalize(query_verb() + " what?\n"));
    
    if (!str)
	return 0;
    
    if (query_verb() == "spray")
    {
        if(str != "myself" && str != "perfume" && str != "perfume on myself")
	    return 0;
    }
    
    else
    
    if(str != "perfume" && str != "perfume on myself")
	return 0;
    
    NF(BS("The perfume bottle makes a strange sucking noise but nothing comes "+
	"out except for a few drops.\n"));
    
    if (uses < 1)
	return 0;
    
    write(BS("You gently spray some perfume around your neck, reveling "+
	"in the sweet fragrance.\n"));
    say(QCTNAME(TP) + " discreetly sprays some perfume around " 
    + TP->query_possessive() + " neck.\n");
    say("The pungent smell of perfume wafts from " + QCTNAME(TP) + ".\n");
    uses = uses - 1;
    remove_dirt();
    return 1;
}
remove_dirt()
{
    object *ob;
    int i;
    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->id("dirty"))
	    ob[i]->remove_object();
    return 1;
}

public void
enter_env(object dest, object from)
{
    ::enter_env(dest, from);
    
    if (!from || living(dest)) return;
    
    if (dest->query_wearable_item() == 1)   
        return;
    
        
    set_alarm(0.25, 0.0, "dest_me");
    return 0;
}

void
dest_me()
{   
    if (environment())
        tell_room(environment(), "The " + QSHORT(this_object()) + " shatters upon impact with the ground!\n");
    remove_object();
}
