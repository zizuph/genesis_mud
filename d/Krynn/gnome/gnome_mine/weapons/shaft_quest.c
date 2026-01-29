/*
    Shaft for pickaxe quest.

    Made by: Maelstrom, 2016/05
*/


inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

create_weapon()
{
    set_name(({"shaft", "shaft_quest"}));
    set_short("shaft");
    set_pshort("shafts");
    set_long("A shaft of sorts. Indentations on the top suggest it's missing something previously attached to it.\n");

    set_default_weapon(1,1,W_CLUB,W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
    add_prop(OBJ_M_NO_SELL, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");  
}