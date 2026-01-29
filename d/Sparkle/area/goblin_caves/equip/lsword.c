/*
 * Longsword for goblin level 1
 * - Boreaulam, April 2012
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

/*
 * Function name:        create_weapon
 * Description  :        constructor for the object
 */
void
create_weapon()
{

    set_name("sword");
    add_name("longsword");
    set_adj("sharp");
    set_short("sharp longsword");
    set_long("This longsword, though crudely made, appears fairly sharp " +
             "and dangerous. The lack of any sophistication or artistry " +
             "in its design is typical of goblin-make and quite common " +
             "among such creatures.\n");

    set_hit(10 + random (5));
    set_pen(10 + random (5));
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH);
} /* create_weapon */

