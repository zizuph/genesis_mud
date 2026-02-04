/*  wrappernote.c */
/*  janus 921015 */

inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("wrappernote");
    set_short("wrap");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_VALUE,3);
    add_prop(OBJ_M_NO_DROP,1);
    set_no_show(); 
}


