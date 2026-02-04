/*
 * thand.c
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"

public void
create_object()
{
    set_name("hand");
    add_name(DQ_THIEF_HAND);
    set_adj(({"bloody", "dirty"}));
    
    set_long("A bloody and dirty hand. Disgusting!\n");
    
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 0);
}
