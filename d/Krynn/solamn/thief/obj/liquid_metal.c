/* created by Aridor, 08/13/94 */

inherit "/std/object";

#include "../local.h"
#include <macros.h>
#include <cmdparse.h>

int liq = 1;

void
create_object()
{
    set_name("metal");
    add_adj("liquid");
    set_long("This is metal that has been heated to the point "+
        "that is has become liquid.\n");
    set_alarm(itof(random(10) + 18),0.0,"cool_down");
    add_prop(OBJ_M_NO_GET,"@@too_hot");
}


void
set_volume(int i)
{
    add_prop(OBJ_I_VOLUME, i);
    add_prop(OBJ_I_WEIGHT, i*10);
    
}

void
cool_down()
{
    remove_adj("liquid");
    add_adj("hardened");
    set_short(0);
    remove_prop(OBJ_M_NO_GET);
    tell_room(E(TO),"The metal seems to have cooled down now.\n");
    liq = 0;
}

int
fill_something(string str)
{
    string what;
    object *obj;
    if (!liq)
      return 0;
    
    if (sscanf(str, "%s with metal", what) != 1)
      return 0;
    obj = FIND_STR_IN_OBJECT(what, TP);
    
    if (obj && sizeof(obj) && function_exists("create_container", obj[0]))
      {
	  write("You fill the liquid metal into the " + obj[0]->query_short() + ".\n");
	  say(QCTNAME(TP) + " fills the liquid metal into a " + obj[0]->query_short() + ".\n");
	  TO->move(obj[0],1);
	  return 1;
      }
    return 0;
}

int
too_hot()
{
    write("OUCH! The metal is so hot that you burnt yourself extremely badly from it.\n");
    TP->heal_hp(-300);
    return 1;
}
