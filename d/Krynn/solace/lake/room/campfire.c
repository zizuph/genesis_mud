/*
 * Feb-20-2001 Boron: Fixed a bug in load_drac
 * Mar 2007, updated by Cherek. Fixed descs to fit in with
 * the updated surroundings.
*/

#include "../local.h"
#include RND_MEET
inherit VILLAGE_BASE_OUT;

object *npc;
object other_room = ROOM + "tent";

void
reset_toron_room()
{
    int i;
  
    if (!npc)
    {
        npc = ({0,0,0,0,0,0});
    }
  
    for(i=0;i<6;i++)
    {
        if (sizeof(npc) <= i)
        {
             npc += ({0});
        }
        
        if (!npc[i])
        {
            set_alarm(itof(i*i/3),0.0,"load_drac",i);
        }
    }
}

void
create_toron_room()
{
    set_short("In a small camp");
    set_long("You are standing by a campfire set by the draconians " +
             "inhabiting this site. Some furs have been thrown on the " +
             "ground and a few logs have been placed in a circle around " +
             "the fire. A foreign aroma penetrates the area. You notice " +
             "large tent has been raised to your east. \n");

    add_item(({"fur","furs"}),
               "Brown furs cover the ground, it seems like most of the " +
               "inhabitants of the camp sleep under a bare sky.\n");

    add_item(({"log","logs","circle"}),
               "The logs seem to have been here for quite some time.\n");
               
    add_item("ground",
             "It is just dirt.");              
               
    add_item(({"fire","campfire"}),
               "The large fire appears to have some meat roasting on it.\n");

    add_item(({"meat","roast","something"}),
               "A slab of some unknown animal sizzles over the open flame.\n");

    add_item(({"flame","flames"}),
               "They are dancing around in a random pattern. \n");
               
    add_item("tent",
             "It is a large army tent made of some heavy cloth. It looks " +
             "possible to enter. \n");

    add_item(({"paths","north path","south path","path"}),
               "Looks like people walk these paths a lot, they are " +
               "quite wide by now.\n");

    add_cmd_parse("[the] 'tent' / 'Tent'", "enter", "@@enter_tent");

    add_exit("lake8.c","west",0);

    reset_room();
}

int
enter_tent()
{
      set_dircmd("tent");
      
      write("You enter the large tent.\n");
      
      say(QCTNAME(TP) + " enters the large tent.\n");
      
      other_room->someone_arrives(TP);
      
      TP->move_living("M", ROOM + "tent", 0);
      
      return 1;
}


void
load_drac(int i)
{
  // If the NPC is there, we don't do anything
  
  if (npc[i])
  {
      return;
  }

  npc[i] = RANDOM_MEET(CAMPTABLE);
  npc[i]->move_living("xxx", TO);
}
