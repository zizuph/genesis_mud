/*
 *
 * Dunlending weapon
 * Coded by Hordak@Genesis
 */
#pragma strict_types

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_weapon()
{
    seteuid(getuid());


    set_name("mace");
    add_name("club");
    set_short("steel spiked mace");
    set_long("The head of the mace consists of two steel rings " +
      "through eachother, and on the edges of the rings " +
      "are small spikes. The rings are attached to a " +
      "wooden pole, that has been wrapped with leather " +
      "to make the grip more comfortable. It is a simple " +
      "weapon, deadly nevertheless.\n");

    set_adj(({"steel", "spiked"}));

    set_hit(33);
    set_pen(35);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(33, 35) + random(100));
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 1500);
}
