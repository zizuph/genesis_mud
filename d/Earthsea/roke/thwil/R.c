/* Roke harbour.
* Copyright (C)  1995-02-04 by Jakob
*
*/

#include "defs.h"
inherit THWIL_BASE_ROOM;

#include <stdproperties.h>
#include <macros.h>

#pragma strict_types;

void
create_thwil_room()
{
   set_short("Bay of Thwil");
   set_long("The bay of Thwil. Over the harbour you "+
      "see not far off a high, round, green hill and beneath it "+
      "a town. You hear a bell ringing, and only far off the hiss "+
      "and roaring of the sea. Clouds hung dark to north and east "+
      "and south a mile off all about the island. But over Roke stars "+
      "are coming out one by one in a clear and quiet sky. "+
      "The boat you are on has a look of long, hard "+
      "use, though the dull red sail is patched with "+
      "great care and the boat is as clean and trim as "+
      "could be. You are ready to set sail for the Sea, "+
      "to the east, or to disembark. \n");
   
   
   add_item("boat", "On either side of its prow en eye is painted. "+
      "It feels like the boat is staring at you. \n");
   
   if (LOAD_ERR("/d/Earthsea/roke/inmost_sea/area_handler"))
      {
      write("Can't load map handler, please report immediately...\n");
      return;
   }
   
   add_exit("", "east", "@@enter_map:/d/Earthsea/roke/inmost_sea/"+
      "area_handler|R@@");
   set_no_npc(1);
   BAY;   
}

void
init()
{
   ::init();
   add_action("disembark", "disembark");
   add_action("sail", "sail");
   add_action("sail", "set", 1);
}

int
disembark()
{
   clone_object(THWIL + "obj/boat")->move(THWIL + "quay");
   TP->move_living("", THWIL + "quay");
   return 1;
}

void
sail()
{
   TP->move_living("east", "@@enter_map:/d/Earthsea/roke/inmost_sea/"+
      "area_handler|R@@");
}

public void 
sink(object ob) 
{
   tell_room(TO,"The "+ob->query_name()+" sinks to the " + 
      "bottom of the sea.\n"); ob->remove_object();
}

public void
enter_inv(object ob,object from)
{
   ::enter_inv(ob,from);
   if(living(ob))
      return;
   set_alarm(1.0, 0.0, &sink(ob));
}
