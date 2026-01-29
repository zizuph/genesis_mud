/* hats for the gully dwarves
 * Created by Arcturus
 * Latest update 06-05-2005
 */


inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

string *gAdj1 = ({"torn","old",
  "smelly","ripped","dirty", "black","blue","white","red"});

string *gName = ({"hat", "cap", "cloth"});

create_armour()
{

    set_name(one_of_list(gName));
    set_adj(one_of_list(gAdj1));
    set_short(query_adj() + " " +query_name());
    set_long("This is a simple " + short() +
      ". The " + short() + " practically dissolves just by looking " +
      "at it. These rags are common for the gully dwarves.\n");
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
}
