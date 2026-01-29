#include "/d/Shire/common/defs.h"

#pragma save_binary

inherit "std/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/common/lib/time.h"

create_room() {
   set_short("trolls cave");
   set_long("A long abandoned trolls' cave in great disarray. "+
      "Scatterings of dried bones litter the floor and the odor "+
      "of must and decay permeate the area. There seems to be a "+
      "freshly dug hole in the earthen floor.\n");
   add_item("hole", "The hole looks like it's been recently dug "+
      "and is now empty.\n");
   add_item(({"bones","dry bones"}), "The bones have been here "+
      "for a long time and are probably the remains of meals, eaten "+
      "by the long ago inhabitants of this cave.\n");
   add_exit(ERE_DIR + "err21","east");
   reset_room();
}

reset_room(){
   object dude;
   dude = present("grunge");
   if (dude && dude->query_name()!="ghost")
      return 0;
   else
      dude = clone_object("/d/Shire/eastroad/npc/ertroll.c");
   dude->move_living("into a room",this_object());
}

