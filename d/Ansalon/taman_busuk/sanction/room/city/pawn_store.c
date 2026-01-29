inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

#define THIEF "/d/Krynn/solamn/thief/obj/"

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

    add_exit(SCITY + "pawn","south");

    INSIDE;  /* This is an inside room */
    reset_room();
}

reset_room()
{
    object ob;
    seteuid(getuid(TO));
    clone_object(THIEF + "bag")->move(TO);
    clone_object(THIEF + "bag")->move(TO);
    clone_object(THIEF + "torch")->move(TO);
    clone_object(THIEF + "torch")->move(TO);
    clone_object(THIEF + "torch")->move(TO);
    clone_object(SOBJ + "picks")->move(TO);
    clone_object(SOBJ + "picks")->move(TO);
    clone_object(SOBJ + "picks")->move(TO);
    clone_object(THIEF + "dudgeon")->move(TO);
    clone_object(THIEF + "dudgeon")->move(TO);
}
