#pragma save_binary

inherit "/d/Genesis/ship/cabin";
#include "/d/Shire/common/defs.h"


void
create_cabin()
{
    set_short("A warm and cosy cabin inside the magnificent ship");
    set_long("This long flat cabin, running the length of the ship "+
    "seems a great haven from any inclement weather.  There is a "+
    "bench in the corner, probably used for seasickness.\n");
    add_item("cabin","This cabin is underneath an ocean-going ship.\n");
    add_item("bench","It smells too bad to lie upon. You almost "+
    "become sick thinking of it.\n");

    add_exit("/d/Shire/common/ship/ship3/deck", "up", 0,1);


}