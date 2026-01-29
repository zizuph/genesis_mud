inherit "/d/Kalad/room_std";
inherit "/lib/store_support";
#include "/d/Kalad/defs.h"
#define POTION1   "/d/Kalad/common/market/obj/potions/dex_potion"
#define POTION2   "/d/Kalad/common/market/obj/potions/int_potion"
#define POTION3   "/d/Kalad/common/market/obj/potions/dragon_scum"
#define POTION4   "/d/Kalad/common/market/obj/potions/mind_blast"

void
set_up_potions()
{
    int i;
    for(i=0;i<5;i++)
    {
        clone_object(POTION1)->move(TO);
        clone_object(POTION2)->move(TO);
        clone_object(POTION3)->move(TO);
        clone_object(POTION4)->move(TO);
    }
}


void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 1;
   set_short("Store room");
   set_long("You are in the store room of Eron von Lotto's shop.\n");
   add_exit("/d/Kalad/common/market/shop/potion_shop", "shop",0,-1,-1);
   set_up_potions();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}
