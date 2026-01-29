/* A pair of stout leggings - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("leggings");
    set_pname("leggings");
    add_pname("armours");
    set_short("pair of leggings");
    set_pshort("pairs of leggings");
    set_long(
        "It is a pair of goblin made stout leggings. " +
        "These leggings look like quite good armour. They are made of " +
        "leather and metal, and tie around your legs.\n");

    set_adj("stout");

    set_ac(20); /* Based on splint mail, but is goblin made. */ 

    /* Set slash,impale & bludgeon modifiers */
    set_am(({ 1, 1, -2}));
    set_at(A_LEGS);

    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 4000);
}
