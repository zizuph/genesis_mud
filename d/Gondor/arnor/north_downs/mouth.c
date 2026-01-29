inherit "/d/Gondor/arnor/arnor_room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/arnor/north_downs/nd_defs.h"

string set_arnor_long();

void
create_gondor()
{
    set_short("The mouth of a large stream in the North Downs");
    set_long("@@set_arnor_long@@");

    add_item(({ "", "" }), "");
    add_item("", "");

    add_exit(NORTH_DOWNS_DIR + "stream4", "west", 0, 3);
    add_exit(NORTH_DOWNS_DIR + "broad_valley6", "south", 0, 3);
}

string
set_arnor_long()
{
   string desc;

   desc = "The mouth of a large stream in the North Downs. "+
   "The stream is very wide and shallow here, it divides into several "+
   "smaller streamlets before reaching the lake. The water noisely flows "+
   "over many shining pebbles. South is the valley floor itself, upstream "+
   "is west. ";
   desc += query_arnor_time();

   return BSN(desc);
}
