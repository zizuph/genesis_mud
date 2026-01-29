/*
*    Key for treasure chest in quest in Flotsam
*/
#include "/d/Ansalon/estwilde/local.h"
inherit "/std/key";

void
create_key() 
{
    ::create_key();
    set_name("key");
    set_short("iron key");
    set_adj("iron");
    set_long("This is a key made of plain iron. An " +
      "imprint of two peaks, the mark of Iron Delving, " +
      "has been engraved on it.\n");

    set_key(CHEST_KEY);
    add_prop("_key_i_no_keyring",1);
}
