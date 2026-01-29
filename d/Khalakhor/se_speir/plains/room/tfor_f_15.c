/* File         : /d/Khalakhor/se_speir/plains/room/tfor_f_15.c
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

   add_exit(PLAINS + "tfor_f_14","west",0,1,1);
   add_exit(PLAINS + "tfor_e_14","northwest",0,1,1);
   add_exit(PLAINS + "tfor_e_15","north",0,1,1);
   add_exit(PLAINS + "tfor_e_16","northeast",0,1,1);
   add_exit(PLAINS + "tfor_f_16","east",0,1,1);
   add_exit(PLAINS + "tfor_g_16","southeast",0,1,1);
   add_exit(PLAINS + "tfor_g_15","south",0,1,1);
   add_exit(PLAINS + "tfor_g_14","southwest",0,1,1);

   set_long(query_long() + " It looks as if it is possible to travel "
                         + "in nearly every direction from here.\n");
}

