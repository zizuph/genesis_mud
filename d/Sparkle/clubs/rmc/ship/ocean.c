/* Conan -Apr 95 */
 
#include "/d/Immortal/std/domain.h"
#include <stdproperties.h>
 
#pragma save_binary

inherit "/std/room";
 
void
create_room() 
{
  set_short("On the sea");
  set_long("This is an ocean. Water's everywhere!\n");
 
  WATER;
}