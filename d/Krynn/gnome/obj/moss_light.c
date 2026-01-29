inherit "/std/object";
 
#include <stdproperties.h> 	/* All prop definitions */
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <wa_types.h>

void
create_object()
{
    set_name("moss_light");
    set_short("moss_light_object");
    set_long("Receive this object from the gnome-caves. It selfdestructs after "
    	+ "some time.\n");

    set_no_show();
    
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);

    set_alarm(1.0, -1.0, "fix_subloc");
    set_alarm(200.0, -1.0, "wither_away");
}

void
fix_subloc()
{
    E(TO)->add_subloc("shiny_moss", this_object());
}

void
wither_away()
{
    E(TO)->catch_msg("The moss covering your hands rapidly withers away.\n");
    E(TO)->remove_subloc("shiny_moss");
    TO->remove_object();
}


int
hand_full(object me)
{
   int i;
   
   if(me->query_armour(TS_LHAND))
    	i += 1;
   if(me->query_armour(TS_RHAND))
    	i += 1;
   return i;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    int i;

    if (subloc != "shiny_moss")
      return E(TO)->show_subloc(subloc, me, for_obj);
    
    i = hand_full(me);
    
    if( i > 1)
    	return "";    
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
    
    if (for_obj == me)
      if(!i)
   	return "Your hands shine greenish.\n"; 
      else
      	return "Your uncovered hand shines greenish.\n"; 
    else
      if(!i) 
      	return C(me->query_pronoun(me)) + " hands shine greenish.\n";
      else
      	return C(me->query_pronoun(me)) + " one uncovered hand shines "
      		+ "greenish.\n";
}

int
init()
{
   ADA("show");
}

int
show(string str)
{
   int i;
   object obj;
   
   NF("Show what?\n");
   if(str != "hands")
   	return 0;   

   if(obj = E(TO)->query_armour(TS_LHAND))
    	i += 1;
   if(E(TO)->query_armour(TS_RHAND))
    	i += 1;
   
   if( i > 1)
   {
   	write("You show around your " + C(obj->query_name()) + ".\n");    
   	return 1;
   }
   if(i == 1)
   {
   	write("You proudly show your one shining green hand.\n");
   	say(QCTNAME(TP) + " shows you that one of " + POSSESSIVE(TP)
   		+ "hands shine greenishly.\nAstonishing!\n");  	
   }
   else
   {
   	write("You proudly show your shining green hands.\n");
   	say(QCTNAME(TP) + " shows you " + POSSESSIVE(TP) + " greenishly shining "
   		+ "hands.\nAstonishing!\n");
   }
   return 1;
}
