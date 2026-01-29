//-*-C++-*-
// file name:    /d/Avenir/union/obj/band_e.
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
    knives = 15;

    add_name(BAND_ID +"_black");
    set_short("elegant black bandeleria");
    set_adj(({"elegant","black", "union"}));
    add_adj("unworn");
    set_long("It is a long belt, elegant in its simplicity, "
      + "made from a sturdy black silken-material. It can "
      + "be worn across the shoulders and chest.");
}
