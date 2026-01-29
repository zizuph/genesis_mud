inherit "/std/container";
#include "/d/Emerald/defs.h"

create_container()
{
    set_short("bowl-shaped altar");
    set_name("altar");
    set_long("The altar seems to reek of death and decay. "+
       "It stands at the western wall of the cavern and "+
       "wraps around part of the side of the wall. There "+
       "are some strange inscriptions on the front of it "+
       "and some sort of rack for ceremonial weapons covers "+
       "the top of it. It could contain something.\n");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 10000000000);
    add_prop(CONT_I_WEIGHT, 10000000);
}

void
enter_inv(object ob, object from)
{
    write("The "+ob->short()+" suddenly melts into the altar.\n");
    ob->remove_object();
}

leave_inventory()
{
}
