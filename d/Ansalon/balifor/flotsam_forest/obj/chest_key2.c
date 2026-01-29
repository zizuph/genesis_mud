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
    set_short("golden key");
    set_adj("golden");
    set_long("This is a relatively simple gold key.\n");

    set_key(CHEST_KEY2);
}
