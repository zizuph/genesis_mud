inherit "/std/leftover";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <poison_types.h>

void
create_leftover()
{
    set_name("leg");
    add_name("mirkwood_spider_leg");
    set_pname("legs");
    set_adj("spider");
    set_short("spider leg");
    set_pshort("spider legs");
    set_long("This leg was chopped from enormous black spider.\n");

    add_prop(HEAP_S_UNIQUE_ID, "_mirkwood_spider_leg_");
    add_prop(OBJ_I_VALUE,100);  /* 100 cc */
    add_prop(OBJ_I_WEIGHT,(250+random(50)));  
    add_prop(OBJ_I_VOLUME,(250+random(50))); 
}


/*
void
consume_text(object *arr, string vb)
{
    string str;
    int i;

    for(i=0; i<sizeof(arr); i++)
      if(MASTER == MASTER_OB(arr[i])) write("*** Leg! ***\n");

    write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + ".\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str + ".\n");
}
*/
