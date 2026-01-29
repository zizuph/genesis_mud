/*  
    Lava tank for pickaxe quest

    Made by: Maelstrom, 2016/05

*/


inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>

create_object()
{
    set_name(({"tank", "lava tank","lava_tank_quest"}));
    set_short("lava tank");
    set_long("A glowing red tank that can hold lava.\n");

	add_prop(OBJ_I_VOLUME, 1);
	add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
    add_prop(OBJ_M_NO_SELL, "You'd better hang on to this. You think perhaps <show>ing it first. Just to be sure.\n");
}