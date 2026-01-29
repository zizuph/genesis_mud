/* 
 * /d/Kalad/common/market/blower.c
 * Purpose    : A glass blower.
 * Located    : /d/Kalad/common/market
 * Created By : Rico  27.Feb.97
 * Modified By: 
 * First Modif: 
 */ 
inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside Glass Blower's Shop");
   set_long("Inside Glass Blower's Shop.\n");
   
   add_exit(MRKT_PATH(m26), "east");
}
