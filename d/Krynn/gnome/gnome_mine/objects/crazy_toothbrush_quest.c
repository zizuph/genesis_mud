/*  
    Gizmo to get clockwork from for pickaxe quest

    Made by: Maelstrom, 2016/05

*/


inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include "common.c"

create_object()
{
    set_name(({"toothbrush","crazy_toothbrush_quest"}));
    set_short("toothbrush");
    set_pshort("toothbrushes");
    set_adj("crazy");
    set_long("A toothbrush made of small clockwork. A small switch activates it.\n");

	add_prop(OBJ_I_VOLUME, 1);
	add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");
    add_prop(OBJ_M_NO_SELL, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");   
}