/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guard_room.c
 *
 * This is where the guards hang out.
 */

#include "/d/Terel/include/Terel.h"

inherit JAIL_DIR + "prison_room";

public void
create_room()
{
     ::create_room();
     set_short("Guard room");
     set_long("This is where the guards hang out.\n");
     
}
