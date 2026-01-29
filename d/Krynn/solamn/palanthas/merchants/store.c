/*
 * the store for the Palanthas shop.
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include "/sys/stdproperties.h"

#define TORCH   "solace_shop_torch"

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

    add_exit(MERCH + "shop","south");

    INSIDE;  /* This is an inside room */
    reset_room();
}

reset_room()
{
    object ob;
    seteuid(getuid(TO));
    if (!P(TORCH, TO))
      {
      ob = clone_object("/d/Krynn/solace/village/obj/torch");
      ob->add_name(TORCH);
      ob->move(TO);
      ob = clone_object("/d/Krynn/solace/village/obj/torch");
      ob->add_name(TORCH);
      ob->move(TO);
      ob = clone_object("/d/Krynn/solace/village/obj/torch");
      ob->add_name(TORCH);
      ob->move(TO);
      }
/*    if (!P("dress",TO))
      clone_object(OBJ + "dress")->move(TO);
    if (!P("blouse",TO))
      {
      clone_object(OBJ + "cblouse")->move(TO);
      }
    if (!P("shirt",TO))
      {
      clone_object(OBJ + "cshirt")->move(TO);
      clone_object(OBJ + "lshirt")->move(TO);
      clone_object(OBJ + "wshirt")->move(TO);
      }
    if (!P("sweater",TO))
      clone_object(OBJ + "sweater")->move(TO);
    if (!P("pullover",TO))
      clone_object(OBJ + "pullover")->move(TO);
    if (!P("trousers",TO))
      clone_object(OBJ + "trousers")->move(TO);
    if (!P("leggings",TO))
      clone_object(OBJ + "leggings")->move(TO);
    if (!P("pants",TO))
      clone_object(OBJ + "pants")->move(TO);
    if (!P("skirt",TO))
      {
      clone_object(OBJ + "sskirt")->move(TO);
      clone_object(OBJ + "skirt")->move(TO);
      }
    if (!P("boots",TO))
      clone_object(OBJ + "boots")->move(TO);
    if (!P("shoes",TO))
      clone_object(OBJ + "shoes")->move(TO);
    if (!P("sandals",TO))
      clone_object(OBJ + "sandals")->move(TO);
    if (!P("shovel",TO))
      clone_object("/d/Emerald/obj/shovel")->move(TO);
    if (!P("shovel",TO))
      clone_object("/d/Emerald/obj/shovel")->move(TO);
    if (!P("_palan_map",TO))
      clone_object(OBJ + "palan_map")->move(TO);
    if (!P("_icewall_scroll",TO))
      clone_object(OBJ + "icewall_scroll")->move(TO);*/
}
