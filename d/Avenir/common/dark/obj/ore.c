// /d/Avenir/common/dark/obj/ore.c
// Ore to find when mining in the underdark
// Modifications:
// Lilith Jun 18 2004 Added Smiths name.
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>

public void
create_object(void)
{
    set_name(({"ore", "chunk"}));
    add_name(({"smith_bar", "smiths_iron_bar", "iron_smith_bar"}));
    set_short("chunk of ore");
    set_pshort("chunks of ore");
    set_long("This is a chunk of iron ore. It must have been recently "+
       "mined, because it shows no signs of oxidation. It is a high-"+
       "quality iron ore, it shouldn't take much refining to turn "+
       "it into weapons-quality iron.\n");

    add_prop("smiths_iron_bar", 1);

    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, 150 + random(50));
}
