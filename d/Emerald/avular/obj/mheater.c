/*
 * MHEATER.c
 * A glowing blue orb sitting on a pedestal, about 4 feet
 * tall. Provides a small amount of heat, otherwise players
 * will eventually have to figure out what the purpose of
 * these things is.
 * - Alaron JAN 2000
 */

#include "../defs.h"
#include <stdproperties.h>

inherit "/std/object";

void
create_object()
{
    set_name("orb");
    set_adj("glowing");
    add_adj("blue");

    set_long("It is a glowing blue perfect sphere, probably about "+
        "a meter in diameter. The dim, diffuse glow coming from the "+
        "orb seems to pulse slowly, gradually going from almost black "+
        "to a soft blue glow. A small amount of heat seems to be "+
        "radiating from the orb. Despite the glow of the orb, it casts "+
        "no additional light into the suffocating darkness surrounding "+
        "it. It rests on a simple, square stone pedestal.\n");

    add_item( ({"pedestal", "stone pedestal", "square pedestal",
        "square stone pedestal"}),
        "It is a cube carved of smooth, cold stone. There are "+
        "no decorations or markings of any kind on it.\n");

    add_prop(OBJ_M_NO_GET, "You can't seem to lift it from the ground.\n");
    add_prop(OBJ_M_NO_BUY, "You can't sell this!\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 45000);
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(MAGIC_AM_MAGIC, ({ 65, "divination" }) );
    add_prop(MAGIC_AM_ID_INFO,
             ({ 5, "You are certain there is magic at work within "+
                   "the orb, but you cannot discern more detail than "+
                   "that.\n",
               85, "You sense that something extremely powerful is at "+
                   "work within the orb. You have no idea what it is, "+
                   "but you do get the feeling that the orb is not "+
                   "of this world somehow.\n" }) );
}


