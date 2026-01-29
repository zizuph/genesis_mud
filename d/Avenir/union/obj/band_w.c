//-*-C++-*-
// file name:    /d/Avenir/union/obj/band_w.c
// creator(s):   Cirion
// purpose:      To hold throwing knives
// revised:      Lilith June 2004: Split out from band.c and
//               fixed recovery bug.
#pragma strict_types

#include "../defs.h";
inherit (OBJ + "band");

private nomask void 
init_band(void)
{
    knives = 20;

    add_name(BAND_ID +"_war");
    set_short("black war bandeleria");
    set_adj(({"black", "war", "union"}));
    add_adj("unworn");

    set_long("It is a massive, wide belt that can "
      + "be worn over the shoulder and down to the "
      + "hips. Is is wide enough to fit two "
      + "pockets in each row.");
}
