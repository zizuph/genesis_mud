
/*      
    Trousers that come in various colours and states, 
    for fishermen.

    Coded by Maniac 2/8/96
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define TROUSERS_COLOURS ({ "beige", "grey", "brown", "white", \
                         "blue", "red", "mauve", "cream" }) 

#define TROUSERS_STATES ({ "grimy", "tatty", "ragged", "old" }) 

void
create_armour()
{
    string *vcs, *vst; 
    string a1, a2; 

    vcs = TROUSERS_COLOURS; 
    vst = TROUSERS_STATES;

    a1 = vst[random(sizeof(vst))]; 
    a2 = vcs[random(sizeof(vcs))]; 

    set_name("trousers");
    set_short("pair of " + a1 + " " + a2 + " trousers"); 
    set_pshort("pairs of " + a1 + " " + a2 + " trousers"); 

    set_long("A pair of " + a1 + " " + a2 + " trousers. They are made " +
              "of coarse cloth and are cut fairly short.\n"); 
    set_ac(10);
    set_at(A_LEGS);
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

