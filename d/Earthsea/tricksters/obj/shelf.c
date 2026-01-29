/*
 *   Created by Ged 12/04/2002
 *   Autosaving rack for Stranglers of Kina
*/

inherit "/lib/guild_rack";

#include <stdproperties.h>

void create_rack()
{
 add_rack_guild_lay("Tricksters of Kina");
 set_rack_file("/d/Earthsea/tricksters/log/shelf_state");
 set_rack_log_file("/d/Earthsea/tricksters/log/shelf_log");

 set_adj("large");
 add_adj("black");
 set_name("shelf");

 set_short("large black shelf");

 set_long("This shelf has been granted to faithful followers by "+
   "Kina. It will help stranglers to gather equipment for Year of "+
   "Skulls to come.\n");

 add_prop(OBJ_I_VALUE, 2031);
 add_prop(CONT_I_VOLUME, 100000);
 add_prop(CONT_I_WEIGHT, 100000);
 add_prop(CONT_I_MAX_VOLUME, 14000000);
 add_prop(CONT_I_MAX_WEIGHT, 39000000);
 add_prop(CONT_I_RIGID, 1);
 add_prop(OBJ_M_NO_GET, "NONONO! Kina would get very mad!!!\n");
}

