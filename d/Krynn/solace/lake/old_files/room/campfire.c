// Fab-20-2001 Boron: Fixed a bug in load_drac
#include "../local.h"

inherit SOLACE_ROOM_BASE;

#include RND_MEET

object *npc;
object other_room = ROOM + "tent";

void
reset_solace_room()
{
  int i;
  if (!npc)
    npc = ({0,0,0,0,0,0});
  for(i=0;i<6;i++)
    {
      if (sizeof(npc) <= i)
    npc += ({0});
      if (!npc[i])
    set_alarm(itof(i*i/3),0.0,"load_drac",i);
    }
}

void
create_solace_room()
{
    set_short("By a Draconian campfire");
    set_long("You are standing by a campfire, set by the draconians " +
         "inhabiting this site. There is a large tent to your east, " +
         "and well defined paths leading north and south. You think " +
         "you ought to be leaving here very soon. A foreign aroma " +
         "penetrates the area.\n");
    add_item(({"fire","campfire"}),
         "The large fire appears to have some meat roasting on it.\n");
    add_item(({"meat","roast","something"}),
         "A slab of well-basted newbie sizzles over the open flame.\n");
    add_item(({"tent"}),
         "It is a large army tent made of some heavy cloth. Maybe " +
             "it is possible to enter the tent?\n");
    add_item(({"paths","north path","south path","path"}),
         "Looks like people walk these paths a lot, they are quite wide " +
         "by now.\n");

    add_cmd_parse("[the] 'tent' / 'Tent'", "enter", "@@enter_tent");


    add_exit(ROOM + "camp_ent.c","west",0);
    add_exit(ROOM + "woods_n.c","north",0);
    add_exit(ROOM + "woods_s.c","south",0);

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
    return;

  npc[i] = RANDOM_MEET(CAMPTABLE);
  npc[i]->move_living("xxx", TO);
}
