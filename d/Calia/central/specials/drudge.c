// OBJECT:  drudge.c

    /* Calia Domain

    HISTORY

    [99-06-08] Created by Uhclem from [D:\CALIA\CENTRAL\SPECIALS\DRUDGE.DOC].

    PURPOSE

    This is an invisible object that can be cloned and moved around when
    needed.  It has no functions other than those in the standard object; it
    simply occupies a location which other objects can use as a reference
    point.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include "defs.h"

// OBJECT DEFINITION

void
create_object()

    {

    set_name("drudge");
    set_short("calian drudge");
    set_long("This object is invisible.\n");

    /*  PROPERTIES  */

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_INVIS, 100);

    add_prop(OBJ_S_WIZINFO,
        "This object performs important tasks in" +
        " Calia. It does not interact with mortals and" +
        " should never be detected by them.\n");

    }
