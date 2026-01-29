/*
 *  /d/Gondor/minas/obj/fenhollenin.c
 *
 *  Door of the Fen Hollen from the Rath Dinen
 *
 *  Original code by Elessar (1992)
 *
 *  Last modified by Alto, 08 April 2001
 *       Updated inherits, brushed up format.
 *
 */

#pragma strict_types

inherit "/std/door";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_door()
{
  ::create_door();
  set_door_id("fenhollen");
  set_pass_command(({"e","east"}));
  set_door_name(({"stone door","door","fen hollen"}));
  set_other_room(INNER_MINAS + "/houses/fen_hollen");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_door_desc("Engraved in the large stone door you read:\n"
    + "             Houses of the Dead\n"
    + "This door is called Fen Hollen, the Closed Door, because it is only\n"
    + "opened for the funerals of Kings or Stewards of Gondor.\n");
  set_open(0);
  set_locked(1);
  set_key("Key_To_Fen_Hollen");
}
