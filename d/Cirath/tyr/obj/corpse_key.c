/*
* Created by: Luther
* Date: August 2001
*
* File: /d/Cirath/tyr/obj/corpse_key.c
* Comments: A simple object to pass to Dale as part of a quest
*/


#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <config.h>
#include <cmdparse.h>
#include <language.h>
#include "/d/Cirath/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#define _IS_KEY_ "_is_key_"

void
create_object()
{
    set_short("bone sliver");
    set_long("This is a small sliver from a bone "+
             "which might beable to open locks if you are skilled enough.\n");
    set_adj("bone");
    set_name("sliver");
    add_name("_jail_corpse_key_");
    add_prop(_IS_KEY_, 1);	
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 5);
}
