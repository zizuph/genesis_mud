/* created by Aridor 09/14/93 */
/* modified by Vitwitch 08/08/21 */

#include <macros.h>
#include "../local.h"

inherit CITY_ROOMBASE;


query_to_jail()
{
  return "down";
}

void
create_palan_room()
{
    set_short("On the Marble Stairs");
    set_long("You have reached the middle of the Marble Stairs. "
         +   "The light of an illuminated room, still far above you, "
         +   "is reflected on the white marble of the stairs. "
         +   "In the direction whence you came, you can see the "
         +   "safety of the entrance hall, far below.\n"
         +   "The oppressive bureaucratic presence of the palace "
         +   "dogs your every step. "
         +   "Even though no one has said it to you -- indeed "
         +   "no one even seems to be about -- you know in your "
         +   "bones that one such as you is not permitted to go up.\n");

    add_exit(PALACE + "palace1","down",0,0);
    add_exit(PALACE + "palace9","up","@@is_protected",0);
}


is_protected()
{
    write("Striking the tiniest of blows for freedom, you summon "
        + "your resolve and venture upwards.\n\n");

    say(QCTNAME(TP) + " ascends with determination towards the light above.\n");
    return 0;
}
