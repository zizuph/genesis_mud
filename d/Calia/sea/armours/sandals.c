
/*      
    Sandals that come in various colours and materials, 
    for fishermen and villagers.

    Coded by Maniac 2/8/96
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define SANDAL_COLOURS ({ "beige", "grey", "brown", "white", \
                          "blue", "red", "mauve", "cream" }) 

#define SANDAL_MATERIALS ({ "leather", "cloth", "canvas" }) 

void
create_armour()
{
    string *scs, *sms; 
    string a1, a2; 

    scs = SANDAL_COLOURS; 
    sms = SANDAL_MATERIALS;

    a1 = scs[random(sizeof(scs))]; 
    a2 = sms[random(sizeof(sms))]; 

    set_name("sandals");
    set_short("pair of " + a1 + " " + a2 + " sandals"); 
    set_pshort("pairs of " + a1 + " " + a2 + " sandals"); 
    add_adj( ({ a1, a2 }) );
    
    set_long("A pair of " + a1 + " " + a2 + " sandals.\n"); 
    set_ac(10);
    set_at(A_FEET);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VILLAGER_ORIGIN, 1); 
}


string
query_recover()
{
    return 0;
}

