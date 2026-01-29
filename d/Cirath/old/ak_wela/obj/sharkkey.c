/* sharkkey.c: Key to the rooms in the Smiling Shark Inn */

inherit "/std/object";
#include "/d/Cirath/common/defs.h"


void
create_object()
{
    set_short("bone key");
    set_long("This key is made of bone. Don't loose it, or you will "+
             "not be sleeping at the Smiling Shark tonight.\n");
    set_adj("bone");
    set_name("key");
    add_name("_smiling_shark_key");
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 5);
    add_prop(OBJ_M_NO_DROP,"No way. You paid dearly for this key.\n");
}

