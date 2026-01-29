inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"

create_room() 
{
    set_short("The workroom of Councellor Olorin");
    set_long(BS("Heaps of papers lying around on a desk and on the floor "
        + "almost completely fill the room. Nevertheless, that's the place "
        + "where Olorin works. There is a single window here. On the "
        + "wall opposite the window hangs a painting.\n"));
  add_exit("/d/Genesis/wiz/entrance","entrance",0);
  add_exit("/d/Genesis/wiz/virtual","virtual",0);
  add_exit("/d/Genesis/wiz/domain","tower",0);
  add_exit("/d/Genesis/wiz/admin","admin",0);
  add_exit("/d/Genesis/start/human/town/tower","human",0);
  add_exit("/d/Genesis/start/hobbit/v/guild","hobbit",0);
  add_exit("/d/Genesis/start/elf/room/vill_board","elf",0);
  add_exit("/d/Gondor/workroom","meeting",0);
  add_exit("/d/Gondor/common/guild/startchamber","guild",0);
  add_exit("/d/Gondor/common/guild/post","post",0);
  add_exit("/d/Shire/common/guild/hguild2","shire",0);
  add_exit("/d/Krynn/solace/guild/hall1","krynn",0);
  add_exit("/d/Dville/glykron/palace/guild","dville",0);
  add_exit("/d/Terel/common/town/street/guild","terel",0);
  add_exit("/d/Gondor/rohan/edoras/guild","rohan",0);
  add_exit("/d/Gondor/olorin/Sorry_Im_idle","idle",0);
    add_item("papers",BS("The papers with numbers and letters in all "
      + "possible combinations. Only a real wiz might be able to "
      + "make anything out of them.\n"));
    add_item("painting",BS("Not what one would call a nice painting, but "
      + "very impressive. It's beauty stems from it's profund depth "
      + "and great clarity. It shows an artist's impression of the "
      + "death of Isildur at the beginning of the Third Age.\n"));
    add_item("window",BS("Looking out of the window you realize that "
      + "you must be somewhere in the White Tower of Minas Tirith. "
      + "Below, you can see the city with it's seven circles. Looking "
      + "farther, you can see the river Anduin and across the river you "
      + "see the lands of Ithilien lying under the Shadow of Mordor.\n"));

  clone_object("/d/Gondor/mercade/bagpipes")->move(this_object());
  clone_object("/d/Gondor/mercade/kilt")->move(this_object());
}

query_prevent_snoop() {
  return 1;
}


sunrise()
{
  tell_room(this_object(),"The sun rises in Gondor and Middle-earth.\n");
  return 1;
}

sunset()
{
  tell_room(this_object(),"The sun sets in Gondor and Middle-earth.\n");
  return 1;
}
