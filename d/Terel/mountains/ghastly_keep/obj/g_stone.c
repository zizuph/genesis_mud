/*
 * /d/Terel/mountains/ghastly_keep/obj/g_stone.c
 *
 * Ghastly stone 
 *
 *  Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 */

inherit "/std/object";
#include "../defs.h";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("stone");
    add_name("_ghastly_keep_stone");
    set_adj("green");
    add_adj( ({ "green", "stone", "ghastly" }) );
    set_short("ghastly green stone");

    set_long("Moss is clinging to the stone like green snow. "
           + "A vibrant power seems to be stored inside this "
           + "small " + TO->short() + ".\n");

    add_prop(MAGIC_AM_MAGIC,( {20,"enchantment"} ));

    add_prop(MAGIC_AM_ID_INFO, ({
          "The presence of power is strong within this stone, you sense "
        + "if you collect enough of them, great things will happen.\n", 20 }) );

    add_prop(OBJ_S_WIZINFO, "This is one of the items used for the summoning "
                          + "ritual.\n");

    add_prop(OBJ_I_VALUE,   0);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);

    add_prop(OBJ_M_NO_SELL, "This " +TO->short()+ " is not worth anything.\n");
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If you have variables you want to recover yourself,
 *                you have to redefine this function, keeping at least
 *                the filename and the armour recovery variables, like
 *                they are queried below.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */

string
query_recover()
{
    return 0; // Don't want this item to recover.
}