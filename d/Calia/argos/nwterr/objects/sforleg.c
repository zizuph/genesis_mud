/* The marble leg of a statue of a satyr, a newbie quest object
** found in rooms/sfor12.c
**/
inherit "std/object";
#include <stdproperties.h>
 
void
create_object()
{
    set_name(({"leg","_satyr_quest_leg"}));
    add_adj("marble");
    add_adj("goat");
    set_short("marble goat leg");
    set_long(
       "It is the marble leg of a goat. It looks to have been broken "+
       "off from a statue.\n");
 
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  0);
}
