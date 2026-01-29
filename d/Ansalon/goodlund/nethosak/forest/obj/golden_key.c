/*
*    Key for the cellar door.
*/

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
inherit "/std/key";

void
create_key() 
{
   ::create_key();
   set_name("key");
   set_short("small golden key");
   set_adj("golden");
   add_adj("small");
   set_long("This is a small golden key. You wonder what "+
            "lock it might fit.\n");
   
   set_key(MITHAS_FOREST_CELLAR);
}

