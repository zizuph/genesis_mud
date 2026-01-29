inherit "/std/object";
 
#include <stdproperties.h> 	/* All prop definitions */
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_object()
{
    set_name("sponge");
    set_short("sponge");
    set_long("A soft sponge, about a handspan wide, two long, and " +
      	"one thick. A small label is stitched into it.\n");
    add_cmd_item(({"label","label on sponge","sponge label"}), "read",
	"The label reads: This product of Gnomish Industries can "
	+ "'wipe'.\n");
    add_item("label", "There is something written on it.\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 10);
}

void
init()
{
    ::init();
    ADA("wipe");
}

string
what(object obj)
{
   if(living(obj))
   	return QTNAME(obj);
   else
   	return "the "+ obj->query_short();
}

int
wipe(string str)
{
   object obj;

   NF("Wipe what?\n");
   if(P(str, E(TP)))
       obj = P(str, E(TP));
   if(P(str, TP))
       obj = P(str, TP);
    if(!obj)
			 return 0;

     TP->catch_msg("You wipe down " + what(obj) + " with "
	+ "your gnomish sponge.\n");
   say(QCTNAME(TP) + " wipes down " + what(obj)
	+ " with a gnomish sponge.\n");
   return 1;
}

