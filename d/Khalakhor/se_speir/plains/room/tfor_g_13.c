/* File         : /d/Khalakhor/se_speir/plains/room/tfor_g_13.c
 * Creator      : Darragh@Genesis
 * Date         : 01-01-23   
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications:  
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "plains.h"

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

void
create_khalakhor_room()
{
   create_tforest();

   add_exit(PLAINS + "tfor_g_12","west",0,1,1);
   add_exit(PLAINS + "tfor_f_12","northwest",0,1,1);
   add_exit(PLAINS + "tfor_f_13","north",0,1,1);
   add_exit(PLAINS + "tfor_f_14","northeast",0,1,1);
   add_exit(PLAINS + "tfor_g_14","east",0,1,1);
   add_exit(PLAINS + "tfor_h_14","southeast",0,1,1);
   add_exit(PLAINS + "tfor_h_13","south",0,1,1);
   add_exit(PLAINS + "tfor_h_12","southwest",0,1,1);

   set_long(query_long() + " It looks as if it is possible to travel "
                         + "in nearly every direction from here.\n");
}

