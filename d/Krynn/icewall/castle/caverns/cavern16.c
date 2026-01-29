/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("A side cavern");
   set_long(
      "This is an extension of the main cavern from which you just "
      +"came. The land is dry as opposed to the lake just east of "
      +    "you. A small pile of furs here suggests a place to warm up. "
      + "\n");
   
   add_item("lake","The underground lake of Icewall is east of you.\n");
   add_item("pile","It is a pile of warm furs.\n");
   add_item(({"fur","furs"}),"They look warm and inviting.\n");
   add_cmd_item(({"fur","furs"}),"get","You cover yourself up with the furs and "
      + "warm yourself.\n");
   
   add_exit(CAVE + "cavern8.c", "east");
}
