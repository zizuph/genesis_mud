/*
 * A key, for the door in the tomb.
 *
 * 950501 by Rastlin
 */

#include "../local.h"

inherit "/std/key";
inherit "/lib/keep";

create_key() 
{
   ::create_key();
   set_name("key");
   set_short("bronze key");
   set_adj("bronze");
   set_long("It is a rather large bronze key.\n");
   set_keep(1);
   
   set_key(TOMB_KEY);
}
