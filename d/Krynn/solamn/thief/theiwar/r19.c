/* created by Aridor 05/19/94 */

#include "../local.h"

inherit LIGHTDARKROOM;

void
create_ld_room()
{
  set_short("In a cavern");
  set_long("@@my_long");
  
  add_exit(THEIWAR + "r18", "north");
  add_exit(THEIWAR + "r14", "south");
  add_exit(THEIWAR + "r21", "northeast");
  add_exit(THEIWAR + "r15", "southwest");
  add_exit(THEIWAR + "r16", "west");  
  add_exit(THEIWAR + "r17", "northwest");

}


string
my_long()
{
    return "A large cavern with exits in almost all directions. " +
      "You can hear loud clanking noises coming from somewhere " +
      "in the northeast." +
      "\n";
}

