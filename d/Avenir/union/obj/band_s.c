//-*-C++-*-
// file name:    /d/Avenir/union/obj/band_s.
// creator(s):   Cirion
// purpose:      To hold throwing knives
#pragma strict_types

#include "../defs.h";
inherit (OBJ + "band");

private nomask void 
init_band(void)
{
    knives = 5;

    add_name(BAND_ID +"_simple");
    set_short("simple bandeleria");
    set_adj("simple");
    add_adj(({"unworn", "union"}));
    set_long("It is a long leather belt, designed to "
      + "be worn over the right shoulder, and running "
      + "down to the hip.");
}
