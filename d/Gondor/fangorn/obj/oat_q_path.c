/*
 *  /d/Gondor/fangorn/obj/oat_q_path.c
 *
 *  Pathway into the quest area for oat quest
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

public int  remove_pathway();

public void
create_door()
{
  ::create_door();
  set_door_id("oat_q_path");
  set_pass_command(({"e","east"}));
  set_door_name(({"pathway through the roots", "pathway"}));
  set_other_room(FANGORN_DIR + "/marsh_oak_room");
  set_door_desc("A pathway through the roots.\n");
  set_open(1);
  set_alarm(60.0, 0.0, &remove_pathway());
  add_name("_oat_q_path_");
}

public int
remove_pathway()
{
    tell_room(ENV(TO), "The roots close over the pathway and "
        + "it is gone.\n", 0, TO);
    TO->remove_object();
    return 1;
}
