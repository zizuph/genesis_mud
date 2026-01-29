inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On a ladder");
  
  set_long(break_string(
           "You're standing on a ladder leading downwards into the darkness. "+
           "Uwards, you can see some light.\n"
           ,60));  
  add_item("ladder","It's a wooden ladder leading down.\n");

  INSIDE;

  add_exit(CIUBORI+"homes/home3","up");
  add_exit(CIUBORI+"homes/sneakroom","down");
}

