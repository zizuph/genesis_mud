
/* 
   A fisherman's knife, for the fishermen on the surface of the 
   west Calia water area. 

   Coded by Maniac

   History:
       2/8/96          Created                 maniac 
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <language.h>
#include "defs.h"

#define KNIFE_TYPES ({ "long", "sharp", "simple", "serrated", "notched" })

void
create_weapon()
{
    string *kts; 
    string a; 

    kts = KNIFE_TYPES;  
    a = kts[random(sizeof(kts))]; 

    set_name("knife");
    set_adj(a);
    set_short(a + " knife"); 
    set_long(capitalize(LANG_ADDART(a)) + " fisherman's knife.\n"); 

    set_hit(9);
    set_pen(10);

    set_wt(W_KNIFE); 
    set_dt(W_IMPALE | W_SLASH); 

    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VILLAGER_ORIGIN, 1); 
}


string
query_recover()
{
    return 0;
}

