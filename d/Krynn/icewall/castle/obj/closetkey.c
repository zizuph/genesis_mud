/* Created By Stevenson (part of Lance Quest) */

#include "/d/Krynn/icewall/local.h"

inherit "/std/key";

void
create_key() 
{
   ::create_key();
   set_name("bone");
   set_short("bone");
   set_adj("small");
   set_long("It is shaped very much like a key...\n");
   
   set_key(CLOSKEY);
}
