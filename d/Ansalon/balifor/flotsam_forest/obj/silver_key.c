/*
*/
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
inherit "/std/key";

void
create_key() 
{
    ::create_key();
    set_name("key");
    set_short("silver key");
    set_adj("silver");
    set_long("This is a beautiful key made of silver. Its " +
      "size gives you the impression that this key would " +
      "be used to unlock a thick gate of some kind.\n");

    set_key(SILVER_KEY);
}
