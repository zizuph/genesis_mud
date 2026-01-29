#pragma strict_types
#pragma save_binary

inherit "/std/act/attack";
inherit "/std/monster";
#include "/d/Gondor/defs.h"
#include "defs.h"
inherit  "/d/Gondor/rohan/farm/farm/camp/lib/base_dunlending";	
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>


/*
 * Defines for guard_type();
 */
#define CLONE_SCOUT 	0
#define CLONE_GUARD 	1
#define CLONE_CAPTAIN	2
#define CLONE_ARCHER	3
#define CLONE_RANDOM	(random(4))


void
create_camp_guard() 
{
	set_guard(CLONE_GUARD);
	
	
}