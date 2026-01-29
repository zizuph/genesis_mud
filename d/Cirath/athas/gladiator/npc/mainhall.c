/* mainhall.c: Hallway guarded by Brutus. Serpine, 4-24-95 */
#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

object ob1;
object ob2;
object ob3;
object ob4;

void
jalla_func();

void
reset_room()
{
   bring_room_mob("brutus",GLAD_NPC+"brutus",1,1);
}

void
create_room()
{
    set_short("barren hallway");
    set_long("This hallway is cold and bare, with nothing to break the "+
             "monotony of angular stone. Unless of course you count the "+
             "dried blood of those who have dared face the Guardian of "+
             "the Gladiators. The sounds of combat echo through this "+
             "hallway from the west to the south, and the screams of "+
             "the arena audience echo from a tunnel running under the "+
             "stands to the north.\n");

    add_item(({"blood", "dried blood"}), "Unremarkable save in amount.\n");

    INSIDE

    add_exit(GLAD_ROOM+"stairwy1.c", "west", "@@west_block@@", 1);
    add_exit(GLAD_ROOM+"entrance.c", "south", 0, 1);
    add_exit(TYR+"stadium/stadium.c", "north", "@@stadium_block@@", 1); 
    reset_room();
}

void
jalla_func()
{
     say("A pair of hidden doors opens and a group of guards "
	+"emerge ready for battle.\n");
   	if (!ob1)
	{
        ob1 = clone_object("/d/Cirath/athas/gladiator/npc/bdefend.c");
		ob1 -> move(TO);
    	ob1 -> arm_me();
	}
    ob1 ->command("assist brutus");
	if (!ob2)
	{
        ob2 = clone_object("/d/Cirath/athas/gladiator/npc/bdefend.c");
        ob2 -> move(TO);
        ob2 -> arm_me();
	}
	ob2 ->command("assist brutus");
    if (!ob3)
	{	
		ob3 = clone_object("/d/Cirath/athas/gladiator/npc/bdefend.c");
        ob3 -> move(TO);
        ob3 -> arm_me();
	}
    ob3 ->command("assist brutus");
	if (!ob4)
	{
        ob4 = clone_object("/d/Cirath/athas/gladiator/npc/bdefend.c");
        ob4 -> move(TO);
        ob4 -> arm_me();
	}
    ob4 ->command("assist brutus");
}


int
west_block()
{
  object guard = present ("brutus", TO);
  if(objectp(guard))
  {
    if((!IS_MEMBER(TP))&&(!IS_WIZ(TP)))
    {
      TP->catch_msg(QCTNAME(guard)+" shoves you back.\n");
      return 1;
    }    
    TP->catch_msg(QCTNAME(guard)+" salutes with his axe as you pass.\n");
  }
  return 0;
}

int
stadium_block()
{  
    /*
    if (present("poison",TP))
    {
        TP->catch_msg("A voice inside your head screams 'No poison "+
            "may pass this way. Begone!' You feel compelled to obey.\n");
        return 1;
    }
    */
    
    if (present("_no_stadium_",TP))
    {
        TP->catch_msg("A voice inside your head screams 'You carry a "+
            "forbidden item. Begone!' You feel compelled to obey.\n");
        return 1;
    }
    return 0;
}

