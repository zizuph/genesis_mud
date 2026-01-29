/*
 * The key for the elder's chest
 * Tapakah, 10/2005
 */

#pragma STRICT_TYPES
#include "../../village/village.h"

inherit "/std/key";

void
create_key()
{
  set_name(V_OBJID + "_key");
  add_name("key");
  set_adj("bone");
  set_short("bone key");
  set_long("A small strange bone, split at the end.\n");
  set_key(VKEY_VALUE);
  
}
