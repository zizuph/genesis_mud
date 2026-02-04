/*
 * ohead.c
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"

public void
create_object()
{
    set_name("head of an ogre");
    add_name("head");
    add_name(DQ_OGRE_HEAD);
    set_adj(({"large", "ugly"}));
    
    set_long("A large ugly head of an ogre. Disgusting!\n");
    
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 11);
}
