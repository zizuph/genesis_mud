/*
 *  /d/Gondor/guilds/rangers/ithilien/store_room.c
 *
 *  Store room for Ithilien Rangers Shop
 *  15-July-01, Alto: modified to fit CH theme.
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#define OIL_LAMP "/d/Gondor/common/obj/oil_lamp"
#define OILFLASK "/d/Gondor/common/obj/oilflask"

void    reset_room();

object *oil;
int nr;

void
create_room() 
{
   set_short("The store-room of Ithilien Rangers Hideout");
   set_long("This is the store-room for the Ithilien Rangers "
       + "Equipment Store.\n");

   add_exit(RANGERS_ITH_DIR + "shop", "east", 0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   nr = 3 + random(4);
   oil = allocate(nr);
   reset_room();
}

void
reset_room()
{
    int i;
    object quiver, arrows;
    
    if (!present("torch")) clone_object(OBJ_DIR + "torch")->move(TO);  
    if (!present("jar")) clone_object(RANGERS_OBJ + "travel_boots")->move(TO);
    if (!present("pouch")) clone_object(RANGERS_OBJ + "herbpouch")->move(TO);
    if (!present("backpack")) clone_object(RANGERS_OBJ + "backpack")->move(TO);
    if (!present("oil-lamp")) clone_object(OIL_LAMP)->move(TO);
    
    for(i = 0; i < nr; i++)
    {
        if(!oil[i] || !present(oil[i],TO))
        {
            oil[i] = clone_object(OILFLASK);
            oil[i]->move(TO);
        }
    }
    
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
    }
}

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj,from);
  store_update(obj);
}
