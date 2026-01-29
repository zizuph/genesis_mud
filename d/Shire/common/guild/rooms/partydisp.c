/*
 *   /d/Shire/common/guild/partydisp.c
 *   The party dispenser room of the Hin Warrior Guild.
 */
inherit "std/room";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

/* Prototypes */
void reset_room();

void
create_room()
{
   set_short("Party room");
   set_long(break_string(
     "This is a dusty back room where few people ever come. The only "
   + "interesting feature of the room must be that machine which is "
   + "standing in the middle. West you can wriggle through the "
   + "forcefield back into the the guildroom, east is another "
   + "exit protected by a forcefield.\n", 70));

   add_exit(HINROOM_DIR + "hguild2", "east", "@@try_east");
   add_exit(HINROOM_DIR + "hguild", "west",0,"@@try_west");

   add_prop(ROOM_I_NO_ATTACK, 1);
   add_prop(ROOM_I_NO_STEAL, 1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_I_INSIDE,1);

   reset_room();
}

void
reset_room()
{
   if (!present("partytool dispenser"))
      clone_object(OPEN_DIR + "party/party_dispenser")->move(this_object());
}

/*
 * Function name:   try_east
 * Description:     Low mortals may not go east, wizards and high Hins may.
 * Returns:	    1 if the way is to be blocked, 0 otherwise
 */
int
try_east()
{
   if (this_player()->query_wiz_level()) 
   {
      write("You wiggle yourself through the forcefield.\n");
      if(this_player()->short())
         say(QCTNAME(this_player()) + " wiggles through the forcefield.\n");
      return 0;
   }
   write("The forcefield bars your way.\n");
   return 1;
}

/*
 * Function name:   try_east
 * Description:     Everyone can go west
 * Returns:	    1 if the way is to be blocked, 0 otherwise
 */
int
try_west()
{
   write("You wiggle yourself through the forcefield.\n");
   if(this_player()->short())
      say(QCTNAME(this_player()) + " wiggles through the forcefield.\n");
   return 0;
}
