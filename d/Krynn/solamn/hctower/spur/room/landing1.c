
//landing1.c
//grace aug 1994
#include "../local.h"

inherit SPURRM;

object guard1, guard2, guard3, guard4;

reset_spur_room()
{
    if (!guard1)
    {
        (guard1 = clone_object(KNIGHT))->move_living(0,this_object());
        clone_object("/d/Krynn/solamn/hctower/spur/obj/main_key")->move(guard1, 1);
    }
    if (!guard2)
    {
        (guard2 = clone_object(KNIGHT))->move_living(0,this_object());
        guard2->set_leader(guard1);
        guard1->team_join(guard2);
    }
    if (!guard3)
    {
        (guard3 = clone_object(KNIGHT))->move_living(0,this_object());
        guard3->set_leader(guard1);
        guard1->team_join(guard3);
    }
    if (!guard4)
    {
        (guard4 = clone_object(KNIGHT))->move_living(0,this_object());
        guard4->set_leader(guard1);
        guard1->team_join(guard4);
    }
}



create_spur_room()
{
   
   SHORT("Landing");
   LONG("You are standing at the top of a broad stair on "+
      "the second floor of the Knights' Spur.  This room is "+
      "rather large for a landing, and brightly lit.\n");  
   
   INSIDE;
   LIGHT;
   
   clone_object(SOBJ + "l2d1b")->move(TO); 
   AE(ROOM + "stairs", "down", 0);
   
   AI("torch", "It burns brightly.\n");
   AI("light", "The light is provided by a torch.\n");
   AI("stair", "It is wide and dimly lighted.\n");
   AI(({"shadow","shadows"}), 
      "The shadows seem to leap out at you.\n");
   
   reset_spur_room(); 
}
