/*
    Crowbar for pickaxe quest.

    Made by: Maelstrom, 2016/05
*/

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

create_weapon()
{
    set_name(({"crowbar", "weapon", "tool", "crowbar_quest"}));
    set_short("crowbar");
    set_pshort("crowbars");
    set_long("A crowbar. Really, what did you expect?\n");

    set_default_weapon(9,8,W_CLUB,W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");
    add_prop(OBJ_M_NO_SELL, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");   
}