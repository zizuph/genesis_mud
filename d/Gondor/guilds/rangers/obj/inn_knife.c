/* 
 * /d/Gondor/guilds/rangers/obj/inn_knife.c
 *
 * Weapon coded by Arren, September 93
 */
inherit "/std/weapon";
#include <wa_types.h>

void
create_weapon()
{
    set_name("knife");
    set_adj("cooking");
    set_short("cooking knife"); 
    set_long("This knife has a sharp steel blade, perfect for " +
        "chopping vegetables, meat and other foods.\n");

    set_default_weapon(8, 8, W_KNIFE, W_IMPALE, W_ANYH, 0);
}
