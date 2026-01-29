/*
 * Common dagger for elf npcs
 * by Finwe, August 2004
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 15,
    pen = 20;

void
create_weapon()
{

    set_name("dagger");
    add_name("knife");
    set_adj("small");
    set_adj("silver");
    set_short("small silver dagger"); 
    set_long("This is a small silver dagger. It is longer than most " +
        "daggers and was forged by elves. Both sides of the blade, which " +
        "tapers to a point, are sharp. The weapon fits neatly in " +
        "your hand and is lightweight.\n");

    set_hit(hit);
    set_pen(pen);

    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH); 
}

