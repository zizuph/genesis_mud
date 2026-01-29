/*
 * Scarlett robe worn by the haradrim captains
 * -- Finwe, July 2005
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

create_armour()
{
    set_name("cloak");
    add_name("robe");
    set_pname("cloaks");
    add_pname("robes");
    set_short("fringed scarlet cloak");
    set_pshort("fringed scarlet cloaks");
    set_adj("fringed");
    set_adj("scarlett");
    set_long("This is an ornate scarlet robe. It is made of heavy scarlet " +
        "fabric and edged with a golden border. On the back is a large " +
        "motif of a sun. The robe hangs from the neck to the ground, and " +
        "is quite ornate. It appears to have belong to a wealthy Haradrim.\n");
    add_item(({"border"}),
        "It is a wide piece of golden fabric sewn onto the edge of the " +
        "cloak. It shimmers in the light and adds a look of elegance " +
        "to the robe.\n");
    add_item(({"motif", "large motif", "sun motif", "large motif of the sun"}),
        "It is a large, golden circle stitched onto the back of the " +
        "robe. The motif is a stylized version of the sun with many " +
        "rays radiating from the center out to the edges of the robe.\n");
    add_item(({"fabric", "fabrics"}),
        "There are two types of fabric. Do you want to examine the " +
        "scarlet fabric or the golden fabric?\n");
    add_item(({"scarlet fabric"}),
        "The fabric was woven from thick thick threads. It is a rich, " +
        "deep red colour and looks heavy. Sewn into the back of the " +
        "fabric is a large motif.\n");
    add_item(({"golden fabric"}),
        "The fabric is about the width of a finger. It was carefully " +
        "stitched around the outside of the robe. It is smooth and shimmers " +
        "in the light.\n");
    
    set_default_armour(3, A_ROBE, (({ 0, 0, 1})), 0);
    add_prop(OBJ_I_WEIGHT, 650);   /* 360 gram */
    add_prop(OBJ_I_VOLUME, 300);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+random(20));
}
