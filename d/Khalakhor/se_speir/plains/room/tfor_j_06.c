/* File         : /d/Khalakhor/se_speir/plains/room/tfor_j_06.c
 * Creator      : Darragh@Genesis
 * Date         : 01-01-23   
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications: 2004-08-24 Corrected a wrong link /Treacher
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

    add_exit(PLAINS + "tfor_j_05","west",0,1,1);
    add_exit(PLAINS + "tfor_i_05","northwest",0,1,1);
    add_exit(PLAINS + "tfor_i_06","north",0,1,1);
    add_exit(PLAINS + "tfor_i_07","northeast",0,1,1);
    add_exit(PLAINS + "tfor_j_07","east",0,1,1);
    add_exit(PLAINS + "tfor_k_07","southeast",0,1,1);
    add_exit(PLAINS + "tfor_k_06","south",0,1,1);
    add_exit(PLAINS + "tfor_k_05","southwest",0,1,1);

    set_long(query_long() + " It looks as if it is possible to travel "
      + "in nearly every direction from here.\n");
}

