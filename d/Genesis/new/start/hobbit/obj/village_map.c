/*
 * File         : /d/Genesis/start/hobbit/obj/village_map.c
 * Creator      : Seaweed - Site
 * Copyright    : Copyright (C) 1999, Joakim Larsson
 * Date         : 3/14/1999
 * Related Files: 
 *     - ../mobiles/informer.c - hand out this map in the hobbit startloc
 *     
 * Purpose      : 
 *     This is a simple pergament map showing the hobbit startlocation. 
 * Todo         : 
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types
/* inherits */
inherit "/std/scroll";

/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include "../hobbit.h"
/* defines */
#define SCROLLFILE      EX_ROOM + "villagemap.txt"
/* prototypes */

/* globals */

/*
 * Function name: create_scroll
 * Description  : setup the map
 */
void
create_scroll()
{
    set_long("This is a small pergament map.\n");
    set_name("map");
    set_pname("maps");
    set_short("map");
    set_pshort("maps");
    set_file(SCROLLFILE);
    set_adj(({"small", "practical"}));
}

/*
 * Function name: hook_smelled
 * Description  : describe the smell of the map
 */
void
hook_smelled()
{
    write("The map smells freshly of pergament and ink.\n");
}
/* EOF */
