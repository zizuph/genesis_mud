/*
 *  /d/Emerald/blackwall/delrimmon/obj/acorn.c
 *
 *  A basic acorn. Certain denizens of the Blackwall Mountains are rather
 *  fond of these.
 *
 *  Copyright (c) August 1997, Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/object.c";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_object();

/* global variables */
int     Acorn_Size = 1;

public int     query_acorn_size() { return Acorn_Size; }
public void    set_acorn_size(int i) { Acorn_Size = i; }

/*
 * function name:        create_object
 * description  :        set up the object
 */
public void
create_object()
{
    set_name("acorn");
    add_name( ({"nut","seed"}) );
    add_adj( ({"small","little","brown"}) );
    add_name("_del_rimmon_acorn");

    set_acorn_size(1 + random(3) );

    set_short("little brown acorn");
    set_long(BSN("This small nut is not much bigger than an average"
      + " human thumbnail. It most likely came from an oak tree in"
      + " the area."));

    add_prop(OBJ_I_WEIGHT, (10 + random(5) ) - 5);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) + 2);
} /* create_object */
