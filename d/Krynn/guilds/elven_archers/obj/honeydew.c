#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

/* Note: from wikipedia
In Norse mythology, dew falls from the ash tree Yggdrasil
to the earth, and according to the Prose Edda book Gylfaginning,
"this is what people call honeydew and from it bees feed."
*/

public void
create_food()
{
    set_name("honeydew");
    add_name(({"finger's measure"}));
    set_pname("honeydew");   
    set_adj(({"sticky", "sweet", "fresh"}));
    set_short("finger-measure of fresh honeydew");
    set_pshort("finger-measures of fresh honeydew");

    set_long("This is a finger's measure of fresh honeydew. "+
      "It is extremely sweet and sticky, bursting with "+
      "energy, and reminiscent of the forest in spring. "+
      "A delight on the tongue and in the belly.\n");

    set_amount(60);
    add_prop(HEAP_I_UNIT_VOLUME, 6);
    add_prop(HEAP_I_UNIT_VALUE, 2);
}
