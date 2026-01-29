inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(CIUBORI+"market/shop", "down");

    INSIDE;
    reset_room();
}

reset_room()
{
    object ob;
    int i;

    if (!present("marketherb", TO))
    {
      seteuid(getuid(TO));
      ob = clone_object(OBJ+ "herb_gizsha");
      ob->add_name("marketherb");
      ob->move(TO);
    }
   
}

enter_inv(ob, from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
