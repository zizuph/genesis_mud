/* 
   Example room to demonstrate a messaging example, 
   in this case for splashing water.
*/ 

#include <stdproperties.h>
#include <macros.h>

inherit "/d/Calia/maniac/splash_room"; 

void
create_splash_room()
{
   add_exit("/d/Calia/maniac/sr2", "east"); 
}
