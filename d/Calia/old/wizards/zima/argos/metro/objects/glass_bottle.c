/* A hand made glass bottle, bought in rooms/glasswrk. Needed to press */
/* grapes into wine in the wine press.                                 */
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
 
void create_object() {
    set_name("bottle");
    add_name(ARGOS_EMPTY_BOTTLE);
    set_adj("empty");
    set_adj("glass");
    set_short("empty glass bottle");
    set_long(
       "It is an empty glass bottle, a hand made item with the artist's "+
       "signature on the bottome: Gaulios.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 6);
}
