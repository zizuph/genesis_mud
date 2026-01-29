
/* Bottle of Cologne - by Antharanos 

   Mirandus - December 2018 - Fixed buggy code with respect to removal of 
   object when dropped 
*   07-01-2022 Meton - Capitalized NF of do_spray
*/

inherit "/std/object";
inherit "/lib/keep";
#include <macros.h>
#include "/d/Kalad/defs.h"
   
int uses=5;

create_object()
{
    set_name("cologne");
    add_name("bottle");
    set_adj("glass");
    add_name("glass bottle of cologne");
    set_short("glass bottle of cologne");
    set_long("@@my_long");
    add_prop(OBJ_I_VALUE,144);
    add_prop(OBJ_I_VOLUME,400);
    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_M_NO_SELL,1);
}
string
my_long()
{
    string empty_desc;

    if (uses < 1)
	empty_desc = "The bottle is empty.";
    else
	empty_desc = "There looks to be a little cologne left inside.";

    return (
      "It is a small container used for colognes. There is a small rubber "+
      "bulb at the top that can be used to spray the cologne. " + empty_desc + "\n");
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
	    if(str != "myself" && str != "cologne" && str != "cologne on myself")
	    return 0;
    }
    
    else
        
    if(str != "cologne" && str != "cologne on myself")
	return 0;

    NF("The cologne bottle makes a strange sucking noise but nothing comes "+
      "out except for a few drops.\n");
    if (uses < 1)
	return 0;

    write("You liberally spray some of the cologne around your neck, its "+
      "strong, musky odor reaching your nostrils.\n");
    say(QCTNAME(TP) + " liberally sprays some cologne around " + TP->query_possessive() + " neck.\n");
    say("A strong manly odor emanates from " + QCTNAME(TP) + ".\n");
    
    uses = uses - 1;
    remove_dirt();
    return 1;
}

void
remove_dirt()
{
    object *ob = deep_inventory(TP);
    filter(ob, &->id("dirty"))->remove_object();
}

void
dest_me()
{   
    if (!environment())
        return;

    tell_room(environment(), "The " + QSHORT(this_object()) + " shatters upon impact with the ground!\n");
    remove_object();
}

public void
enter_env(object dest, object from)
{
    ::enter_env(dest, from);
    
    if (!from || living(dest)) return;
    
    if (dest->query_wearable_item() == 1) return;
    
        
    set_alarm(1.0,0.0, &dest_me());
    return 0;
}
