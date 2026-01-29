/* Small ball of bird doo (waste) - can be boiled to extract saltpeter,
** a combustible powder and ingredient of incense.
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 2/12/98     Zima        Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include "birdoo.h"
int boiled=0;
 
int query_boiled() { return boiled; }
void set_boiled() {
    add_adj("boiled");
    set_short("ball of boiled bird droppings");
    set_pshort("balls of boiled bird droppings");
    set_long(
       "It is a small soft ball of boiled bird droppings, probably "+
       "not a very healthy thing to handle.\n");
    boiled=1;
}
 
void create_object() {
    set_name("droppings");
    add_name(({"waste","doo","excrement","ball"}));
    add_name(BIRD_DOO);
    set_adj(({"small","smelly","bird"}));
    set_short("ball of bird droppings");
    set_pshort("balls of bird droppings");
    set_long(
       "It is a small smelly ball of bird droppings, probably "+
       "not a very healthy thing to handle.\n");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_VALUE,0);
}
