/*
 * Modification log:
 * Gwyneth:
 * Changed /d/Gondor/elessar/lib/time.c to /d/Gondor/common/lib/time.h
 */
#pragma save_binary

inherit "/std/room";
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/time.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room()
{
  set_short("A wide flat rock above the waterfall");
  set_long("@@long_func");
  add_item("rock","You are standing on a wide flat rock above the waterfall.\n"+
    "The rock is wet from the mist from the waterfall.\n");
  add_item(({"waterfall","fall","torrent","stream"}),
    BS("Eastwards is the waterfall, splashing over many terraces, "+
    "and then, pouring down a steep race, it fills a smooth-hewn "+
    "channel with a dark force of water flecked with foam, and curling "+
    "and rushing almost at your feet it plunges sheer over the edge "+
    "that yawns to the west.\n"));
  add_item("vale","It is a great vale, with a silvery spine running from "+
    "north to south - the River Anduin.\n");
  add_item(({"field", "fields"}), "The fields are green, with a silvery " +
    "spine  running from north to south - the River Anduin.\n");
  add_item(({"water", "river","anduin"}),
    BS("The river you can see in the west is "+
    "the mighty Anduin, on its way to the Sea. The torrent at your feet "+
    "seems to be one of its tributes.\n"));
  add_item(({"terrace", "terraces"}),
    BS("The terraces consist of large, flat rocks, smoothed by thousands of " +
    "years of water passing.\n"));
  add_item("cleft", "The cleft is a V-shaped fissure, filled with " +
    "foaming water.\n");
  add_exit(RANGER_ITH_DIR+"post","down",0);
  add_exit(RANGER_ITH_DIR+"landing2","west",0);
}

long_func()
{
  string long;
  long = "You are on a wide flat rock without rail or parapet. Just "+
    "to the east, the torrent stream falls, splashing over many terraces "+
    "and flowing west to "+
    "fill a smooth cleft with foaming water. The rock is wet from the "+
    "thin mist rising from the cleft. In the distance to the west "+
    "stretches an immense vale";
  if (tod()=="night") long = long+", filled with a silvery mist "+
    "lit by the moon.\n";
  else long = long+", its green fields lit by the sun. Its epic beauty "+
    "astounds you - Gondor, Oh Gondor!\n";
  return BS(long);
}
