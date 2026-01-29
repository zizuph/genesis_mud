#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

object merchant;

void
reset_kalaman_room()
{
    if(!objectp(merchant))
    {
        merchant = clone_object(KNPC + "bow_seller");
        merchant->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("A cobbled street in the city of Kalaman");

    add_item(({"market place","market"}),
      "To the north the road opens into a busy market place.\n");

    add_exit(CITY + "m1","north",0);
    add_exit(CITY + "r21","south",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand upon a street in the center of Kalaman. " +
    tod_descr1() + season_road() + "To your north the road opens into a busy " +
    "market place.\n";
}
