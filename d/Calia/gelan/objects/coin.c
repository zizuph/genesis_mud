/* 
   Coin for use in the applicants task when they want to join 
   the Calian guild.
*/


inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/domain.h"

void
create_object()
{
    set_name("coin");
    set_adj("crystalline");
    set_long("It is a small crystalline coin.\n");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_NO_STEAL,1);
    add_prop(OBJ_M_NO_SELL,1);
}


int
do_swallow(string str)
{
    if ((!str) || (str != "coin"))
        return 0;
    write("You swallow the coin.  Mmmmmm...chocolate!\n");
    set_alarm(1.0, 0.0, "remove_object");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_swallow,"swallow");
    add_action(do_swallow,"eat"); 
}

