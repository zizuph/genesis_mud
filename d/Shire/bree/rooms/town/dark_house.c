/*
But as they drew near to the further gate, Frodo
saw a dark ill-kept house behind a thick hedge: the last house
in the village. In one of the windows he caught a glimpse of
a sallow face with sly, slanting eyes; but it vanished at once.
‘So that’s where that southerner is hiding!’ he thought. ‘He
looks more than half like a goblin.
’
Over the hedge another man was staring boldly. He had
heavy black brows, and dark scornful eyes; his large mouth
curled in a sneer. He was smoking a short black pipe. As they
approached he took it out of his mouth and spat.

squint-eyed southerner
*/
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bree/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>


/* Prototype */
void reset_shire_room();

void make_npcs();

object hob1, hob2, ranger, man, dwarf, spoon;

void
create_shire_room()
{
   set_short("A dark house");
   set_long("This is a dark house. Shadows fill the corners and the windows are covered with dark curtains. It is run down and smells horribly. Broken debris is scattered around the room, and shelves are full of random supplies. A table sits in one corner with a few candles and a bed in another corner.\n");
//      "This is the fabled common room of Bree's Prancing Pony, "+
//      "the most famous inn in the known world, according to Bree-"+
//      "folk, that is. A great fire burns in the fireplace, surrounded by many scattered "+
//      "tables, and even a few dark corners, nooks and crannies, for "+
//      "more private conversation. The small windows on the wall are "+
//      "always closed at night, for even in the summer the Shire gets "+
//      "a bit drafty for a hobbit's taste. Usually there are several "+
//      "people, elves, men, dwarves or hobbits discussing recent happenings "+
//      "from diverse areas like Staddle, Michel Delving, Hobbiton, and sometimes "+
//      "even Edoras is discussed. But this is a curious bunch, so "+
//      "don't expect your conversation to be private!\n");
    add_item(({"walls"}),
        "The walls are dark and bare, except for some shelves set against them\n");
    add_item(({"XXX"}),
        "XXX \n");
    add_item(({"XXX"}),
        "XXX \n");
    add_item(({"XXX"}),
        "XXX \n");
    add_item(({"XXX"}),
        "XXX \n");
    add_adj(({"Some rats scitter aross the floor."}));
    add_adj(({"A sneaky "}));

   add_prop(ROOM_I_INSIDE,1);

   add_exit(ROAD_DIR + "broad04","southwest",0);
   enable_reset();
   reset_shire_room();

}

void reset_shire_room()
{
//   make_npcs();
}

void
make_npcs()
{
   if(!hob1)
      {
      hob1 = clone_object(NPC_DIR + "ponyhobbit");
      hob1->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(hob1->query_nonmet_name()))+
         " comes strolling into the room.\n");
      hob1->command("sit in chair");
   }
   if(!hob2)
      {
      hob2 = clone_object(NPC_DIR + "ponyhobbit2");
      hob2->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(hob1->query_nonmet_name()))+
         " prances into the room.\n");
      hob2->command("sit in chair");
   }

   if(!ranger)
      {
      ranger = clone_object("/d/Gondor/common/guild/north/npc/wolfeater");
      ranger->arm_me(0);
      ranger->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(ranger->query_nonmet_name()))+
         " strides in warily..\n");
      ranger->command("sit in shadows");
   }

   if(!man)
      {
      man = clone_object(NPC_DIR + "ferny");
      man->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(man->query_nonmet_name()))+
         " paces in nervously, glancing about.\n");
      man->command("lean against wall");
   }

   if(!dwarf)
      {
      dwarf = clone_object(NPC_DIR + "dwarf");
      dwarf->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(dwarf->query_nonmet_name()))+
         " strolls in confidently, tugging his beard thoughtfully.\n");
      dwarf->command("sit by fire");
   }


}


init()
{
   ::init();
}
