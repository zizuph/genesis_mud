/*
 *  /d/Gondor/guilds/rangers/hq/hq_store.c
 *
 *  Store room for Ranger Central Headquarters Shop
 *  9-July-01, Alto: modified to fit CH theme.
 *
 *  Modification log:
 *    Gwyneth, 3 May 2004 - Cleaned up
 */
inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <stdproperties.h>

#define OIL_LAMP "/d/Gondor/common/obj/oil_lamp"
#define OILFLASK "/d/Gondor/common/obj/oilflask"

void reset_room();

object *oil;
int nr;

void
create_room() 
{
   set_short("the store-room of Central Headquarters Equipment Store");
   set_long("This is the store-room for the Central Headquarters "
       + "Equipment Store.\n");

   add_exit(RANGERS_HQ_DIR + "hq_shop", "south", 0);

   add_prop(ROOM_I_INSIDE, 1);
   nr = 3 + random(4);
   oil = allocate(nr);
   reset_room();
}

void
reset_room()
{
    int i;
    if (!present("torch"))
        clone_object(OBJ_DIR + "torch")->move(TO);

    for(i = 0; i < nr; i++)
    {
        if(!oil[i] || !present(oil[i],TO))
        {
            oil[i] = clone_object(OILFLASK);
            oil[i]->move(TO);
        }
    }

    if (!present("jar"))
        clone_object(RANGERS_OBJ + "herbjar")->move(TO);
    if (!present("pouch"))
        clone_object(RANGERS_OBJ + "herbpouch")->move(TO);
    if (!present("backpack"))
        clone_object(RANGERS_OBJ + "backpack")->move(TO);
    if (!present("shortsword"))
        clone_object(WEP_DIR + "ssword")->move(TO);
    if (!present("armour"))
        clone_object(ARM_DIR + "studl")->move(TO);
    if (!present("oil-lamp"))
        clone_object(OIL_LAMP)->move(TO);
}

/*
 * Function name: enter_inv
 * Description  : Masks the parent to update the storeroom when a new
 *                item arrives.
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);

    store_update(obj);
}
