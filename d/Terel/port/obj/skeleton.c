/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * skeleton.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <language.h>

object rope = 0;

public void
create_object()
{
    set_name("skeleton");
    set_adj("old");
    
    set_long("It is an old skeleton. Only the bones are left.\n");
    
    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, 0);

    add_prop(OBJ_M_NO_GET, 1);
    
    add_item("bones", "They are pure whitish.\n");
}
