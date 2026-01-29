/*
     The tanner room for the smiths guild
     smiths can pay to make leather from skins and hides here
*/

#pragma save_binary;

inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_room() {
   set_short("Tannery of the Smiths Guild");

    set_long("This is the old workshop of the tanner, Bigerin " +
        "Smallburrow. He had worked tirelessly for many years and " +
        "decided it was time to take a vacation. Someday, he said, " +
        "he might return, but he has returned to his relatives in " +
        "Hardbottle for a badly needed rest. When he left, he " +
        "also took all his tools so nothing remains but an empty room.\n");

/*   set_long("This room is filled with hides from various animals and jars"+
      " with foul smelling liquids used in the process of making leather."+
      " The hides that are currently being worked on seems to be skins"+
      " from oxen, which is said to give a fine quality leather."+
      " In one corner of the room leather pieces are placed."+
      " Usually this is where Bigerin Smallburrow can be found, the person"+
      " to go to if you want leather for items. It is impossible to"+
      " understand how anyone can stand this smell for more than a few"+
      " minutes.\n");

   add_item("jars","They are filled with bad-smelling liquids.\n");
   add_item("hides","There are all kinds of hides ranging from rabbit"+
      " hides to ox hides.\n");
   add_item("liquid","It seems to be the liquid that makes the bad"+
      " smell.\n");
*/
   add_exit(SMITHSDIR_ROOMS+"discus","north",0);

   add_prop(ROOM_I_INSIDE,1);
   /* following props used until better solution is coded */
   add_prop(ROOM_I_NO_ATTACK,1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK,1);

   //if (!objectp("bigerin")) room_add_object
   //   ("/d/Shire/guild/smiths/npc/bigerin", 1, QCTNAME(TO)+" arives.\n");
   if (!objectp("recorder"))
      room_add_object("/d/Shire/guild/smiths/obj/skin_recorder");
}
