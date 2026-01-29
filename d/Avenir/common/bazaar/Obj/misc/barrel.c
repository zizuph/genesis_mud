// creator(s):     Lilith  8/28/97
// last update: 
// purpose:        Source of organs for mummers and spellcasters
// bug(s):
// to-do:

inherit "/std/receptacle";

#include "/d/Avenir/include/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define ORGAN "/d/Avenir/inherit/leftover"

void fill_barrel();

void
create_receptacle()
{
    if (!IS_CLONE)
        return;
 
    set_name("organ barrel");
    set_adj(({"organ", "large", "pristine", "clean", "polished"}));
    add_name(({"barrel", "container"}));
    set_short("pristine barrel"); 
    set_long("This is a large barrel. It is unusually clean and polished, "+
        "as though it is regularly scrubbed.\n");

    add_prop(OBJ_M_NO_GET, "The "+ short() +" is too heavy.\n");
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_WEIGHT, 15000);       // 15 kilos
    add_prop(CONT_I_VOLUME,  9000);       //  9 litres
    add_prop(CONT_I_MAX_VOLUME, 99000);   // 99 litres
    add_prop(CONT_I_MAX_WEIGHT, 99000);   // 99 kilos
    add_prop(CONT_I_RIGID, 1);

    seteuid(getuid(TO));
    fill_barrel();
}

void
fill_barrel()
{
    object organ;
    int i = random(5);

    organ = clone_object(ORGAN);
    organ->leftover_init("intestine", "animal");
    organ->move(this_object(), 1);
    organ->set_heap_size(10 + i);

    organ = clone_object(ORGAN);
    organ->leftover_init("eye", "deer");
    organ->move(this_object(), 1);
    organ->set_heap_size(8 + i);

    organ = clone_object(ORGAN);
    organ->leftover_init("heart", "bicorn");
    organ->move(this_object(), 1);
    organ->set_heap_size(5 + i);

    organ = clone_object(ORGAN);
    organ->leftover_init("rib", "phrynos");
    organ->move(this_object(), 1);
    organ->set_heap_size(10 + i);

}
