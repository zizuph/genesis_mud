#include "plains.h"
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit PLAINBASE;
#define MAX_SHEEP 3

object *sheep=allocate(MAX_SHEEP);
object shepherd;

public void
reset_room()
{
   int i,num=random(MAX_SHEEP);
   set_searched(0);
   if (!objectp(shepherd))
      {
      shepherd=clone_object(NPC2+"shepherd");
      shepherd->arm_me();
      shepherd->move(TO);
      tell_room(TO,QCNAME(shepherd)+" walks up amongst the sheep.\n");
      }

   for (i=0; i<num; i++)
      if (!objectp(sheep[i]))
         {
         sheep[i]=clone_object(NPC2+"sheep");
         (sheep[i])->move(TO);
         tell_room(TO,"A "+(sheep[i]->query_short())+" scampers up to you.\n");
         }
}


public void
create_khalakhor_room()
{
    create_plain();
    set_short("In a pasture on a grassy plain");
    set_long("   You in a pasture situated on the "+
             "grassy rolling hills of the plain. The smell of "+
             "livestock is strong here, the scent mixing with that of "+
             "the salt air brought in by a cool breeze. A crude fence "+
             "encloses the pasture on all sides.\n");

    add_item(({"area","fenced-in area","pasture"}),
       "The pasture is situated on the grassy hills of the plain, "+
       "obviously made to enclose livestock. A crude wooden fence "+
       "surrounds the pasture on all sides.\n");
    add_item("fence",
       "The fence is crudely made of twisted, sun and rain warped "+
       "wooden beams, posts set fairly evenly around the pasture, "+
       "with two rails strapped horizontally between each.\n");

    add_exit(PLAINS + "plains_29_7", "north");
    add_exit(PLAINS + "plains_30_7", "northeast");
    add_exit(PLAINS + "plains_30_8", "east");
    add_exit(PLAINS + "plains_30_9", "southeast");
    add_exit(PLAINS + "plains_29_9", "south");
    add_exit(PLAINS + "plains_28_9", "southwest");
    add_exit(PLAINS + "plains_28_8", "west");
    add_exit(PLAINS + "plains_28_7", "northwest");
}

public int *
query_global_coords()
{
    return ({3, 0});
}
