/* A common ring
** Date      Coder      Action
** -------- ----------- -----------------------------------
** 12/10/94 Zima        Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define ENGS ({"leaves","daggers","hearts","skulls","birds","waves"})
void create_armour() {
    set_name("ring");
    set_adj("silver");
    set_short("silver ring");
    set_long(
       "It is a simple silver ring, engraved with tiny "+
       (ENGS[(random(sizeof(ENGS)))])+"\n");
    set_ac(0);
    set_at(A_FINGERS);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  50);
}
