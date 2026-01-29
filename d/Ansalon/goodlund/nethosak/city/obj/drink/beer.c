inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(250);
    set_alco_amount(75);
    set_name("beer");
    set_adj("roke");
    set_short("imported roke beer");
    set_pshort("imported roke beers");
    set_long("This is one of the famous roke beers from "+
             "the lost land of Re Albi. These beers are "+
             "notorious for their high level of alcohol.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    seteuid(getuid());
    clone_object("/d/Ansalon/goodlund/nethosak/city/obj/booze_object")->move(this_player());
}

