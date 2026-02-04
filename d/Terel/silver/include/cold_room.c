/* Terel cold room,
  by Udana 03/2006
 */


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit STDROOM;

public void create_room()
{
  ::create_room();
  add_prop(ROOM_I_TEREL_COLD, 1);
}


public void init()
{
  ::init();
  if(this_player()->has_cold_shadow() || this_player()->query_wiz_level())
    return;
  FIX_EUID;
  this_player()->catch_msg("It's freezing out here!\n");
  object cold_shadow = clone_object(OBJ + "cold_shadow");
  cold_shadow->start_cold(this_player());
}