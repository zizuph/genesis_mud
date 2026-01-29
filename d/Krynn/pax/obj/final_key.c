/*
 * A key, for the south door in the Chainroom.
 *
 * 950501 by Rastlin
 */

#include "../local.h"

inherit "/std/key";

create_key() 
{
   ::create_key();
   set_name("key");
   set_short("silver key");
   set_adj("silver");
   set_long("It is a small silver key.\n");
   
   set_key(FINAL_KEY);
}
