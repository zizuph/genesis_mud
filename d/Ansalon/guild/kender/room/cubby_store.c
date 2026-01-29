inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"

#define TORCH "solace_shop_torch"
#define PICKS "/d/Ansalon/taman_busuk/sanction/obj/picks"

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

    add_exit(KROOM + "cubby","north");

    INSIDE;  /* This is an inside room */
    reset_room();
}

reset_room()
{
    object ob;
    seteuid(getuid(TO));
    if (!P(TORCH, TO))
    {
	ob = clone_object(KEN_OBJ + "kender_pouches");
	ob->add_name(TORCH);
	ob->move(TO);
	clone_object(PICKS)->move(TO);
	clone_object(PICKS)->move(TO);
	clone_object(PICKS)->move(TO);
	clone_object(KEN_OBJ + "kender_pouches")->move(TO);
	clone_object(KEN_OBJ + "kender_pouches")->move(TO);
	clone_object(KEN_OBJ + "kender_pouches")->move(TO);
	clone_object(KEN_OBJ + "kender_pouches")->move(TO);
	clone_object(KEN_OBJ + "hoopak")->move(TO);
	clone_object(KEN_OBJ + "hoopak")->move(TO);
	clone_object(KEN_OBJ + "hoopak")->move(TO);
	CLONE_HOOPAK;
	CLONE_HOOPAK;
	CLONE_HOOPAK;
    }
}
