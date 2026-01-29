/*
 * - The high effect effect was commented out. /Cotillion, AoB
 * Reduced effect from 50 to 2 per coffee, Ckrik 9/2005
 */
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
    set_name("coffee");
    set_adj(({"gontish", "Gontish"}));
    set_short("Gontish coffee");
    set_long("A steaming hot cup of coffee, laced with " +
        "a slug of whiskey for flavour.\n");
    set_soft_amount(100);
    set_alco_amount(50);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

public void
special_effect(int num)
{
    this_player()->add_fatigue(2 * num);
    write("The coffee burns as it goes down.\nYou feel more awake.\n");
}

