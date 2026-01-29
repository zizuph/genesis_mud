#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

#define BOMB_DIR "/d/Shire/bombadil/npc/"
static object pheasant;

//int do_enter(string str);

void
create_er_room()
{

   area = "not far";
   areaname = "Greenholm";
   land = "the Shire";
   areatype = 10;
   areadesc = "hamlet";
   grass = "green";

   extraline = "Just east of The Bounds, the Shire is not greatly "+
   "different than the Eriador it replaced.  A hobbit hole is dug "+
   "into the hill here and some others are east.";

   add_item(({"hobbit hole","smial","burrow","hill"}),
   "A medium-sized hobbit hole, also known as a smial or burrow "+
   "is dug into the side of the hill.  The door seems open, and it "+
   "is possible to enter the burrow.\n");

   add_item(({"the bounds","bounds","bound"}),
   "The border of the Shire is a bit west of here, you will cross it "+
   "if you go in that direction.\n");

   add_item(({"greenholm","village"}),
   "Greenholm, a tiny hamlet of the Shire, is under your feet.\n");
   reset_shire_room();

   add_exit(EAST_R_DIR + "er6","south");
   add_exit(EAST_R_DIR + "er7n","east",0,1,1);
   add_exit(EAST_R_DIR + "er5n","west",0,1,1);
   add_exit("/d/Shire/eastroad/village/greenholm/5", "enter", 0, 1, 1);
}
/*
void
init()
{
   ::init();
   add_action("do_enter","enter");
}

int
do_enter(string str)
{

   if (!str)
     return 0;
 
   if ((str == "burrow") || (str == "smial") || (str == "hobbit hole") || (str == "hole"))
   {
     write("You enter the open burrow.\n");
     say(QCTNAME(TP)+ " leaves into the open burrow.\n");
     TP->move_living("M",VILLAGE_DIR + "greenholm/5");
     say(QCTNAME(TP)+" arrives.\n");
     return 1;
    }

   write("Enter what ? A "+str+" ? You must be kidding!\n");
   return 1;
}
*/

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(pheasant))
    {
        pheasant = clone_object(BOMB_DIR + "pheasant");
        pheasant->set_restrain_path("/d/Shire/eastroad/western");
        pheasant->set_random_move(2);
        pheasant->move(TO);
    }
}
