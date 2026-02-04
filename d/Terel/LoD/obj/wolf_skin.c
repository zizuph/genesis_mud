/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tooth.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <stdproperties.h>

#include "/d/Terel/LoD/dungeon/quest.h"


public void
create_object()
{
    set_name("skin");
    add_name("wolf skin");
    add_name(DQ_WOLF_SKIN);
    set_adj("grey");
    
    set_long("It's a bloody grey skin. From the size and shape you " +
             "realize it must have belonged to some big animal. " +
             "Most likely a wolf or bear.\n");
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2600);
    add_prop(OBJ_I_VALUE, 109);
}
