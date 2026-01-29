/*
 * cadu_b1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types
#include <macros.h>
#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/std/room";
inherit STDPIER;

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;


void
create_room()
{
  ::create_pier();
  set_short("Pier - Circle Line.");
  set_long("You are on the pier south of Cadu.\n" +
           "To the north is the shore and further north " +
           "you see the central parts of Cadu. " +
           "The pier continues to the south.\n" +
           "This is the place where the public galleon lands.\n");
  
  add_exit("cadu_s1", "north");
  add_exit("cadu_b4", "south");
  
  BEACH;
  sign = clone_object(SIGN);
  sign->move(TO);
  reset_room();
  add_pier_entry(MASTER_OB(TO), "Cadu", "Pan-Donut Circle");
  initialize_pier();

}

object
query_sign ()
{
  return sign;
}
