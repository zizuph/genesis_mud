/*
 *  /d/Gondor/minas/shades/obj/poisoned_dagger.c
 */
#pragma strict_types
inherit "/d/Gondor/common/wep/poison_dagger";

void
create_poison_dagger()
{
    configure_dagger("black");
    set_doses(4);
}
