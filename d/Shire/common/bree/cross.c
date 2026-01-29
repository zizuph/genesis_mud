#include "defs.h"

inherit "/d/Shire/std/room";

object sign;
void lean_sign(string str);

void
create_shire_room()
{
   set_short("Crossroads");
   set_long("You are standing on a great crossroad west of the " +
        "town Bree. The Greenway, the Old North Road and the Great " +
        "East Road meet here. A huge sign has been posted here " +
        "for all to read.\n");

   sign = clone_object(STAND_OBJ + "sign");
   sign -> set_name("sign");
   sign -> set_adj("huge");
   sign -> set_short("huge sign");
   sign -> set_long(
      "\n\n"+
      "      __________________________________________________________\n"+
      "     |                                                          |\n"+
      "     |                    The Old North Road                    |\n"+
      "     |                            to                            |\n"+
      "     |                 Deadman's Dike (Fornost)                 |\n"+
      "     |                            /\\                            |\n"+
      "     |                            ||                            |\n"+
      "     |                            ||                            |\n"+
      "     |       The Shire    The Great Eastroad      Bree-hill     |\n"+
      "     |           and    <=====================>       and       |\n"+
      "     |      Greyhavens.           ||           Misty Mountains. |\n"+
      "     |                            ||                            |\n"+
      "     |                            \\/                            |\n"+
      "     |                       The Greenway                       |\n"+
      "     |                            to                            |\n"+
      "     |                          Gondor                          |\n"+
      "     |                                                          |\n"+
      "     |__________________________________________________________|\n"+
      "                                 |    |\n"+
      "                                 |    |\n"+
      "                                 |    |\n"+
      "                                 |    |\n"+
      "   ______________________________|____|______________________________\n");

   sign -> move(TO);
   add_item(({"bree","hill","wall"}),
      "To the east, you see Bree-Hill and the town of Bree beneath. "+
      "A large wall can be seen surrounding the town, and the only "+
      "entrance is through the West-Gate.\n");
   add_item(({"gate","west-gate"}),
      "The gate is not here, you'll have to go east first.\n");
   add_item(({"road","roads"}),
      "Which road do you mean?\n");
   add_item(({"eastroad","east road","west road", "great east road"}),
      "The Great East Road looks well trodden.\n");
   add_item(({"greenway","south road","south way"}),
      "The Greenway looks not so well trodden, in fact grass grow "+
      "on the road, hence the name...\n");
   add_item(({"north road","old north road"}),
      "It seems not to have been used so much.\n");

   add_exit(ER_DIR + "er29","west",0,1);
   add_exit(BREE_DIR + "wgate", "east", 0);
   add_exit(GWAY_DIR  + "gw1", "south", 0);
   add_exit(BREE_DIR + "ngreenway", "north", 0);
}


void
init()
{
    ::init();
    add_action("lean_sign", "lean");
}

void lean_sign(string str)
{
    return;
    if(str=="against sign" || str=="against huge sign" ||
       str=="up against sign" || str=="up against sign")
    {
        say (QCTNAME(TP) + " leans up against the sign wearily " +
            "and wipes the sweat from " + HIS_HER(TP) + "brow.\n");
        write("You wearily lean up against the sign and wipe the " +
            "sweat from your brow.\n");
    }
    NF("Lean against what?\n");
}
