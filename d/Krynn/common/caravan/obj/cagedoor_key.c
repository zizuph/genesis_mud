/*
 *  Filename:       cagedoor_key.c
 *  Description:    This is a key for a door for a wagon.
 *
 *  Copyright (c) Aug. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 *
 * based on Door from corridor into cell, ground level. cell_door1a.c
 * done by Jeremiah.
 */
#include "../wagon/wagon.h"
inherit "/std/key";

void
create_key()
{
   ::create_key();
   set_name("steel key");
   set_short("fine steel key");
   set_pshort("fine steel keys");
   set_adj("steel");
   set_long("This is a fine steel key, used for unlocking someting.\n");

   set_key(CAGE_KEY);
}
