/*
 *  /d/Gondor/guilds/rangers/north/store_room.c
 *
 *  Store room for Northern Rangers Shop
 *  15-July-01, Alto: modified to fit CH theme.
 */
inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include "check_exit.c"

#define OIL_LAMP "/d/Gondor/common/obj/oil_lamp"
#define OILFLASK "/d/Gondor/common/obj/oilflask"

void    reset_room();

object *gOil;
int gNum;

void
create_room() 
{
   set_short("the store-room of Northern Rangers Hideout");
   set_long("This is the store-room for the Northern Rangers "
       + "Equipment Store.\n");

   add_exit(RANGERS_NOR_DIR + "shop", "east", &check_ranger());

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   gNum = 3 + random(4);
   gOil = allocate(gNum);

   reset_room();
}

void
reset_room()
{
    int i;
    object quiver, arrows;

    if (!present("torch")) clone_object(OBJ_DIR + "torch")->move(TO);
    for(i = 0; i < gNum; i++)
    {
        if(!gOil[i] || !present(gOil[i],TO))
        {
            gOil[i] = clone_object(OILFLASK);
            gOil[i]->move(TO);
        }
    }

    if (!present("jar"))
        clone_object(RANGERS_OBJ + "travel_boots")->move(TO);
    if (!present("pouch"))
        clone_object(RANGERS_OBJ + "herbpouch")->move(TO);
    if (!present("backpack"))
        clone_object(RANGERS_OBJ + "backpack")->move(TO);
    if (!present("oil-lamp"))
        clone_object(OIL_LAMP)->move(TO);

    if (!present("quiver"))
    {
        arrows = clone_object(RANGERS_OBJ + "arrows");
        quiver = clone_object(RANGERS_OBJ + "quiver");
        arrows->move(quiver, 1);
        quiver->move(TO, 1);
        
        arrows = clone_object(RANGERS_OBJ + "arrows");
        quiver = clone_object(RANGERS_OBJ + "quiver");
        arrows->move(quiver, 1);
        quiver->move(TO, 1);
    }

    if (!present("arrows"))
    {
        arrows = clone_object(RANGERS_OBJ + "arrows");
        arrows->set_heap_size(500);
        arrows->move(TO, 1);
    }

    if (!present("shortbow"))
    {
        clone_object(RANGERS_OBJ + "shortbow")->move(TO, 1);
        clone_object(RANGERS_OBJ + "shortbow")->move(TO, 1);
        clone_object(RANGERS_OBJ + "shortbow")->move(TO, 1);
        clone_object(RANGERS_OBJ + "shortbow")->move(TO, 1);
    }
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);

    store_update(obj);
}
