/* Rags for the gully dwarves
 * Created by Arcturus
 * Latest update 06-05-2005
 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

string *gAdj1 = ({"brown","torn","ripped",
  "shredded","smelly","messy","dirty","spotted","disgusting"});

string *gName = ({"dress", "gown", "shirt", "rag", "garment", "cloth"});

create_armour()
{
    set_name(one_of_list(gName));
    set_adj(one_of_list(gAdj1));
    set_short(query_adj() + " " + query_name());
    set_long("This is a simple " +short() +
      ", typical worn by gully dwarves. This " + 
      short() + " looks like it has lead a rich " +
      "and exiting life in the past\n");
    
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
}
