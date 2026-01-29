/*
* Created by: Luther
* Date: SEPT 2001
*
* File: /d/Cirath/ridge/obj/rope.c
* Comments: The rope you get for completing valley_body_quest
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
#define THE_ROPE "the_rope"

void
create_object()
{
    	set_name("rope");
    	add_name("_rope_");
    	set_long("A ancient rope.\n");
    	add_prop(THE_ROPE, 1);	
    	add_prop(OBJ_I_WEIGHT, 1000); /* 1 kg */
    	add_prop(OBJ_I_VOLUME, 1000); /* 1 l */
    	add_prop(OBJ_I_VALUE, 0); /* 0 copper */
}
