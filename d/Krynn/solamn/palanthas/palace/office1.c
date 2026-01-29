/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
    set_short("Information Office");
    set_long("This is the Information Office. Strange, there is "
         +   "no one here, and it doesn't look like anyone is working "
         +   "here. There is simply a big poster on the wall:\n"
         +   "\n"
         +   "Ground Floor:\n"
         +   "  01     Information Office\n"
         +   "  02     Supervisor\n"
         +   "  03     Waiting Room\n"
         +   "  06     Divorce Judge\n"
         +   "  07     Estate Agent\n"
         +   "  08     Personnel Department\n"
         +   "  09     Tax Collector\n"
         +   "  10     Computing Department\n"
         +   "Top Floor:\n"
         +   "  11     Archive\n"
         +   "  13     Treasury\n"
         +   "  15     City Guard\n"
         +   "  16     Form Office\n"
         +   "  17     Inquisitor\n"
         +   "  18     Office A-M\n"
         +   "  19     Office N-Z\n"
         +   "  20     Judge\n"
         +   "  21     Thaumaturgy\n");

    INSIDE;

    add_exit(PALACE + "hall1","east",0,0);
}

 
