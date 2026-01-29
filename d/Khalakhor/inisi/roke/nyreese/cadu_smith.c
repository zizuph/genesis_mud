/*
 * cadu_smith.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Changed 'fix' to 'sharpen' and added repair and polish.
 * Tapakah, 07/2021
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

object smith;

string sign_text = "The sign reads:\n" +
  "We <sharpen> edged weapons, <repair> blunt and <polish> corroded ones.\n";

void
reset_room ()
{
  if (!smith) {
    tell_room(TO, "The weaponsmith arrives.\n");
    smith = clone_object(ROKEDIR + "npc/weaponsmith");
    smith->equip_me();
    smith->move(this_object());
  }
}

void
create_room ()
{
  set_short("The weaponsmith's forge");
  set_long("You are in the forge where the weaponsmith of Cadu works.\n"+
           "It's very hot in here and you feel a little uncomfortable.\n"+
           "There is a sign here.\n");

  add_item("sign", sign_text);

  add_cmd_item("sign", "read", sign_text);

  INSIDE;
  add_prop(OBJ_I_HAS_FIRE, 1);
  
  add_exit("cadu_q3", "west");

  reset_room();
}

void
leave_inv (object obj, object to)
{
  ::leave_inv(obj,to);
  if (!living(obj))
    return;
  if (smith)
    smith->someone_left(obj, to);
}
