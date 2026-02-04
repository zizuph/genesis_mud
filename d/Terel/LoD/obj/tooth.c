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
    set_name("tooth");
    add_name(DQ_WOLF_TOOTH);
    set_pname("teeth");
    set_adj("yellowish");
    
    set_long("It's a yellowish tooth. From the size and shape you " +
             "realize it must have belonged to some big animal. " +
             "Most likely a wolf or bear.\n");
    
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 26);
    add_prop(OBJ_I_VALUE, 10);
}
