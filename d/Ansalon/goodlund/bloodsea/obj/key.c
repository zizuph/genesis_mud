#include "/d/Ansalon/balifor/flotsam_forest/local.h"
inherit "/std/key";

void
create_key() 
{
    ::create_key();
    set_name("key");
    set_short("iron key");
    set_adj("iron");
    set_long("This is a large iron key.\n");

    set_key(7171717);
}
