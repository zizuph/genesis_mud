/**************************************************/
/*  Secret Passage in Oak  Room of Icewall Castle */
/*               Coded by Steve  */
/**************************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

create_icewall_room()
{
set_short("Secret Passage");
set_long(BS(
"\nYou are in a secret passage at the back of the fireplace"
+ " in the Oak Room. The passage continues east into another"
+ " room."
+ "",75));



add_exit(ICE_CAST1_R + "oak_room.c", "west");
add_exit(ICE_CAST1_R + "secret2.c", "east");
}
