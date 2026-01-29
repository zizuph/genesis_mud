/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_BASE;

#define HEARTROOM_ACTIVATED  "_wohs_test_heartroom_activated"

object mirror;

void
reset_tower_room()
{
    if(!objectp(mirror))
    {
       mirror = clone_object("/d/Krynn/guilds/wohs/test/obj/magic_mirror1");
       mirror->move(TO);
       mirror->set_mirror_setting(random(3));
    }
}

void
create_tower_room()
{
   set_short("the Hall of Shadows within the crimson tower of High " +
       "Sorcery");
   set_long("You stand in the Hall of Shadows on the upper level of the " +
       "crimson tower of High Sorcery, a testing ground for " +
       "illusionists among other things.\n");
   add_item(({"hall","halls","hall of shadows","hall of shadow"}),
       "Dark and shapeless, the hall really is just a room of shifting " +
       "shadows.\n");
   add_item(({"shadows","shadow","shifting shadows"}), "As you look " +
       "around the hall the shadows shift, hiding nothing and " +
       "everything... with the exception of the mirror standing in the " +
       "middle of the room.\n");

   set_tell_time(15);
   add_tell("The framed, silver mirror rocks precariously as the walls " +
       "of the tower vibrate furiously!\n");
   add_tell("The tower rocks violently, as if it had been struck by a " +
       "wave of force!\n");
   add_tell("The stones of the tower begin to crack as spiderwebs of " +
       "energy spread across them.\n");
   add_tell("The tower begins to shake and rumble ominously!\n");
   add_tell("The walls of the tower groan, as if they were being " +
       "constricted by a powerful coil of force.\n");

   add_exit(WOHS_TEST + "room/daltigoth_tower7", "west", 0);

   reset_tower_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && TP->query_prop(HEARTROOM_ACTIVATED))
       start_room_tells();
}
