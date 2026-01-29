/*
 *   The storage room of the armoury in Minas Morgul
 */
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

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
   set_short("the armoury's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(MORGUL_DIR + "city/rooms/armoury", "west",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   reset_room();
}

public void
reset_room() 
{
    if (!present("sword",TO))
    {
        clone_object(WEP_DIR + "orcsword")->move(TO);
        clone_object(WEP_DIR + "fssword")->move(TO);
    }
    if (!present("club",TO))
    {
        clone_object(WEP_DIR + "orcclub")->move(TO);
        clone_object(WEP_DIR + "stick")->move(TO);
    }
    if (!present("shovel",TO))
    {
        clone_object(OBJ_DIR + "shovel")->move(TO);
        clone_object(OBJ_DIR + "shovel")->move(TO);
    }
    if (!present("morning-star"))
    {
        clone_object(WEP_DIR + "orc_wep/morningstar")->move(TO);
        clone_object(WEP_DIR + "orc_wep/morningstar")->move(TO);
    }
    if (!present("battleaxe"))
    {
        clone_object(WEP_DIR + "orc_wep/battleaxe")->move(TO);
        clone_object(WEP_DIR + "orc_wep/battleaxe")->move(TO);
    }
    if (!present("scimitar"))
    {
        clone_object(WEP_DIR + "orc_wep/broad_scimitar")->move(TO);
        clone_object(WEP_DIR + "orc_wep/dull_scimitar")->move(TO);
    }
    if (!present("halberd"))
    {
        clone_object(WEP_DIR + "orc_wep/halberd")->move(TO);
        clone_object(WEP_DIR + "orc_wep/halberd")->move(TO);
    }
    if (!present("whip"))
    {
        clone_object(MORDOR_DIR + "obj/wep/whip")->move(TO);
    }
}

