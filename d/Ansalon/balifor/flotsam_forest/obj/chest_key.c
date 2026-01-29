/*
*    Key for treasure chest in quest in Flotsam
*/
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
inherit "/std/key";

void
create_key() 
{
    ::create_key();
    set_name("key");
	add_name("_gdragon_lair_key");
    set_short("elaborate key");
    set_adj("elaborate");
    set_long("This is a key of elaborate make. Made of " +
      "steel, it has a great number of teeth of different " +
      "shapes and sizes, giving you the impression " +
      "that it was made to open an almost fool-proof lock.\n");

    set_key(CHEST_KEY);
/*  add_prop("_key_i_no_keyring",1);  Since this key only works once
                                      now anyway, there's no reason to
									  keep this from keyrings.
									  -Mortis, 11.2005
*/
}
