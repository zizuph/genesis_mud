// file name:    /d/Avenir/union/obj/band_c.
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
    knives = 10;

    add_name(BAND_ID +"_gold");
    set_short("gold-embroidered bandeleria");
    set_adj(({"gold","embroidered","gold-embroidered", "samite", "union"}));
    add_adj("unworn");
    set_long("Long and light, this belt can be worn "
      + "over the shoulder and across the chest. It is "
      + "made from soft webcloth interwoven with glimmering "
      + "threads of gold. Designed specifically to be worn "
      + "by Tornu as a reward for their service, it is both "
      + "utilitarian and decorative.");
}
