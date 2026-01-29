inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("necklace");
    set_adj("intricate");
    set_short("intricate silver necklace");
    set_long("This is a beautiful necklace made of small, intricately "+
    "carved links. There are many small pictures of fish, bears, and cats "+
    "carved on the links, as well as other intresting geometric symbols"+
    " and designs. Placed evenly along the chain are tiny diamond studs "+
    "that make the whole necklace sparkle brightly in the light.\n");
    set_at(A_NECK);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
    add_prop(OBJ_I_VALUE,500);
}

