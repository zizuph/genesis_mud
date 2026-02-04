/* birch.c */
/* janus 920822 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()


reset_room()
{
}
create_room()
{

  set_short("birch tree");
  set_long(break_string("You are standing in the crown of a "+
     "big birch tree. The leaves block the view but it would "+
     "have been great. \n",70));
   add_exit(JANUSDIR + "garden/garden4", "down",0);

  reset_room();
}
