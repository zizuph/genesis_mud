#pragma save_binary

inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
  set_short("a hidden set of stairs");
  set_long(BS("A set of stone steps lead up from here, towards the roof "+
    "of green leaves above. The hidden passage continues west between "+
    "narrow stone walls. You hear the sound of rushing water from the north.\n"));
  add_item(({"roof","leaves"}),BS("A roof of green leaves can be seen above. "+
    "You guess it is the bushes covering the entrance to this hidden path.\n"));
  add_item("passage","The hidden passage runs under a cover of leaves.\n");
  add_item("steps","The path runs up a set of stone steps cut into the rock.\n");
  add_exit(RANGER_ITH_DIR+"passage5","west",0);
  add_exit(RANGER_ITH_DIR+"entrance","up",0);
}