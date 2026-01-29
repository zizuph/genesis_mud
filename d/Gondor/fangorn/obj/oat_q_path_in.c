/*
 *  /d/Gondor/fangorn/obj/oat_q_path_in.c
 *
 *  Pathway out of the quest area for oat quest
 *
 *
 *  Alto, 12 May 2001
 */

#pragma strict_types

inherit "/std/door";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"
#define FANGORN_DIR "/d/Gondor/fangorn"

public void
create_door()
{
  ::create_door();
  set_door_id("oat_q_path");
  set_pass_command(({"w","west"}));
  set_door_name(({"pathway through the roots", "pathway"}));
  set_other_room(FANGORN_DIR + "/marsh_oak_room");
  set_door_desc("A pathway through the roots.\n");
  set_open(1);
}

