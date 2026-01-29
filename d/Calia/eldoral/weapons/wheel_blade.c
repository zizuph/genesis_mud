/*
 * wheel_blade.c
 * 
 * Basically just a sharpened disk, this isn't much of a weapon to wield,
 * but it's 'left over' after a player gets hit with it if they weight down
 * the wrong stone in ~Calia/eldoral/ruins/catacomb_hub.c trying to free
 * the sword in the stone, where it does a lot more damage than it can do
 * when wielded.
 *
 * Coded by Khail, Dec 23/96
 */
#pragma strict_types

#include "defs.h"

#define HIT 5
#define PEN 10

inherit "/std/weapon";

public void
create_weapon()
{
    set_name("disk");
    add_name("disc");
    add_name("blade");
    set_adj("thin");
    add_adj("steel");
    set_short("thin steel disk"); 
    set_pshort("thin steel disks"); 
    set_long("This small object is nothing more than a steel disk not " +
        "much bigger around than your fist, but the edges have been " +
        "sharpened to a razor's edge, making it a very interesting " +
        "weapon.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_KNIFE);
    set_hands(W_ANYH);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 10);
}
