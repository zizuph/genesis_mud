/**********************************************************************
 * - map.c                                                          - *
 * - Just a general map of the southern seas.                       - *
 * - Created by Damaris@Genesis 03/2001                             - *
 * - Updated by Damaris@Genesis 03/2005                             - * **********************************************************************/

#pragma strict_types

inherit "/std/object.c";
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

public string map_text();

void
create_object()
{
    set_name("map");
    set_adj("small");
    set_short("small map");
    set_long("@@map_text@@");
    add_cmd_item(({"map","small map"}), "read", map_text());
    add_prop(OBJ_I_WEIGHT,  30);
    add_prop(OBJ_I_VOLUME,  30);
}

public string map_text()
{
    return "You unroll the map and examine it closely.\n\n"+
"                              /\\\n"+                                      
"                           ..(<>)..\n"+                                   
"                          '  |\\/|  `\n"+                        
"       ,___________________./    \\.____________________.\n"+
"      /                                                 \\\n"+
"     |               Map of Southern Seas                |\n"+
"     |---------------------------------------------------|\n"+
"     |                               Port--x............ |\n"+
"     |                            MacDunn    ........... |\n"+
"     |                                       ........... |\n"+
"     |                                            .      |\n"+
"     |                                                   |\n"+
"     |..                                                 |\n"+
"     |..x--SaMorgan        Galaith                       |\n"+
"     |                      Isle            South Seas   |\n"+ 
"     | ,___________________.      .____________________. |\n"+
"     |//\\_/\\\\|              \\    /               |//\\_/\\\\|\n"+
"     ( \\___/ )               |/\\|                ( \\___/ )\n"+
"      \\_____/             `..(<>)..'              \\_____/\n"+
"                              \\/\n";
}
