/*
* the store for the Neraka General Store
*/

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#define ONE_OF(x)   (x)[random(sizeof(x))]
#define ARM     ONE_OF(({"vest","shirt","boots1","breeches"}))

#define ARMID   "_neraka_ashop_default_"

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}

create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");
   
   add_exit(NINNER + "ashop","out");
   
   INSIDE;  /* This is an inside room */
   reset_room();
}

reset_room()
{
    object ob;
    int i;
    seteuid(getuid(TO));
    if (!P(ARMID, TO))
    {
        for(i=0;i<5;i++)
        {
            ob = clone_object(NARM+ARM);
            ob->add_name(ARMID);
            ob->move(TO);
        }
    }
}
