/*
 * sack.c
 *
 * A simple rugged sack which makes you able to carry more.
 *
 
 ChangeLog
 
 May 21, 2005 Palmer -
   Removed all decay functions because herbs no longer decay
 
 */

#pragma save_binary

inherit "/std/receptacle";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include "/d/Shire/herald/herald.h"

/*
 *  Description: Constructor.
 */
public void
create_container()
{
    set_name("herbbag");
    add_name(({"bag","herb bag"}));
    set_pname("bags");
    set_adj( ({ "silk","small" }) );
    set_short("small silk bag");
    set_pshort("small silk bags");
    set_long("This is a finely woven small silk bag.\n");
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_WEIGHT,     600);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     300);           /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 3*1000);       /* 3.0 l          */
    add_prop(CONT_I_MAX_WEIGHT, 5*1000);      /* 5.0 kg        */
    add_prop(CONT_I_CLOSED,     1);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(OBJ_M_NO_SELL,     "@@check_sell@@");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
}

public int
do_default_open(string str)
{

    if(str == "bag" || str == "small silk bag" || str == "silk bag")
    ::do_default_open(str);

    return 1;
}

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
	return "There are things in the "+short()+"! Empty it first.\n";
    else
	return 0;
}

string
short(object for_obj)
{
    if (query_prop(CONT_I_CLOSED))
	return "closed " + ::real_short(for_obj);
    else
	return "open " + ::real_short(for_obj);
}

mixed enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);
    if(!obj->query_herb_name())
    {
	obj->move(TP);
	write("Seems silly to waste space in a herb bag like that, "+
	  "so you take it right back out.\n");
	return;
    }
}
