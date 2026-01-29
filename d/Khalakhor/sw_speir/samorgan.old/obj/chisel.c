/* Standard small Chisel
 * Created by Damaris 02/01
 */

inherit "/d/Khalakhor/std/weapon.c";
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
void
create_khalakhor_weapon()
{
    set_name("chisel");
    set_adj("small");
    add_adj("jeweled");
    set_short("small jeweled chisel");
    set_long("This is a small jeweled chisel. It is made from light weight steel and "+
      "it has a small jewel placed on the handle.\n");
    add_item(({"jewel", "small jewel"}),
      "A small delecate sapphire is embedded firmly in the handle. There is "+
      "an inscription below it.\n");
    add_item(({"inscription"}),
      "Property of Ariel of SaMorgan.\n");
    add_item(({"saphire", "small sapphire"}),
      "The sapphire is small and delecate and it sparkles when the light "+
      "catches it. It has been firmly embedded into the handle of the "+
      "chisel.\n");
    add_item(({"handle"}),
      "The handle is smooth with a small jewel embedded in it.\n");
       set_hit(10);
       set_pen(5);
    
       set_hands(W_NONE);
       set_wt(W_KNIFE);
       set_dt(W_IMPALE);
   
       add_prop(OBJ_I_WEIGHT,  800);
       add_prop(OBJ_I_VOLUME,  500);
   }
   
   
   /* Value must be lower than its sale price. 
      /d/Khalakhor/std/weapon won't let one change the value 
      property in create_khalakhor_weapon() at the time of writing */ 
   int
   query_value()
   {
       return 1;
}

public int
read_inscrip(string str)
{
    NF("Read what?\n");

    if (!str || !strlen(str))
	return 0;

    if (!parse_command(str, TP, "[the] 'inscription'"))
	return 0;

    write("Property of Ariel of SaMorgan.\n");
    return 1;
}
public void
init()
{
    ::init();
    add_action(read_inscrip, "read");
}
