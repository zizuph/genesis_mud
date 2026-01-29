/*
 *   The storage room of the general store in Minas Morgul
 */
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object *oil,
       *packs;
int     nr;

public void reset_room();

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
   set_short("the shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(MORGUL_DIR + "city/rooms/shop", "east",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   nr = 3 + random(8);
   oil = allocate(nr);
   nr = 3 + random(4);
   packs = allocate(nr);
   enable_reset(200);
   reset_room();
}

public void
reset_room() 
{
    int     i, s;

    for (i = 0, s = sizeof(packs); i < s; i++)
    {
        if (!objectp(packs[i]) || !present(packs[i], TO))
            (packs[i] = clone_object(MORGUL_DIR + "obj/backpack"))->move(TO);
    }

    if (!present("sack", TO))
    {
        clone_object(MORGUL_DIR + "obj/sack")->move(TO);
        clone_object(MORGUL_DIR + "obj/sack")->move(TO);
        clone_object(MORGUL_DIR + "obj/sack")->move(TO);
    }

    if (!present("torch",TO))
    {
        clone_object(OBJ_DIR + "torch")->move(TO);
        clone_object(OBJ_DIR + "torch")->move(TO);
        clone_object(OBJ_DIR + "torch")->move(TO);
    }

    for(i = 0, s = sizeof(oil); i < s; i++)
    {
        if (!objectp(oil[i]) || !present(oil[i],TO))
            (oil[i] = clone_object(OBJ_DIR + "oilflask"))->move(TO);
    }

    if (!present("lamp",TO))
    {
        clone_object(OBJ_DIR + "oil_lamp")->move(TO);
        clone_object(OBJ_DIR + "oil_lamp")->move(TO);
        clone_object(OBJ_DIR + "oil_lamp")->move(TO);
    }
}
