/*
    Pickhead for pickaxe quest.

    Made by: Maelstrom, 2016/05
*/


inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

create_weapon()
{
    set_name(({"pickhead", "pickhead_quest"}));
    set_short("pickhead");
    set_pshort("pickheads");
    set_long("It seems to be the head of a pickaxe.\n");

    set_default_weapon(1,1,W_CLUB,W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
    add_prop(OBJ_M_NO_SELL, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");   
}