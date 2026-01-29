/*
 * /d/Kalad/common/guilds/sh_walkers/obj/ladder.c
 * This is the ladder cloned into entrance.c and tunnel1.c
 * Created By : Rico 23.05.96
 * First Modif: 7.Feb.97
 */

#include "../defs.h"

inherit "/std/object.c";

void
create_object()
{
   set_short("old dusty ladder");
   add_name("ladder");
   add_adj(({ "old", "dusty" }));
   set_long("\nThis is an old, dusty ladder.  It looks extremely "+
      "old and worn.\nIt's rails are starting to splinter.\n"+
      "Perhaps you should test it before attempting to climb "+
      "down it...\n\n");

   add_item(({ "rail", "rails", "splintering rails" }),
      "\nYou had best be careful while climbing down this "+
      "ladder...\nYou're liable to find your palms full of "+
      "nasty splinters!\n\n");

   add_prop(OBJ_M_NO_GET, "\nThe ladder seems to be wedged into "+
      "place it's been here so long.\n\n" );
}

