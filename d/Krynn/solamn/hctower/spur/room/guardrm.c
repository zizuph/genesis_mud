// guardrm.c
// grace sept 1994

#include "../local.h"

inherit SPURRM;
object door1, door2, guard1, guard2, guard3, guard4;

reset_spur_room()
{
  if (!guard1)
    (guard1 = clone_object(KNIGHT))->move_living(0,this_object());
  if (!guard2)
    (guard2 = clone_object(KNIGHT))->move_living(0,this_object());
    guard2->set_leader(guard1);
    guard1->team_join(guard2);
  if (!guard3)
      (guard3 = clone_object(KNIGHT))->move_living(0,this_object());
  guard3->set_leader(guard1);
  guard1->team_join(guard3);

  if (!guard4) {
      (guard4 = clone_object(KNIGHT))->move_living(0,this_object());
      guard4->set_leader(guard1);
      clone_object("/d/Krynn/solamn/hctower/spur/obj/cell_key")->move(guard1, 1);
      guard1->team_join(guard4);
    }
}
         

create_spur_room()
{

   SHORT("Guardroom");
   LONG("You stand in a room deep inside the Knight's Spur.  "+
      "Despite the high ceilings, the unrelieved stone seems "+
      "to weigh upon you.  Though not quite a dungeon, this "+
      "is the place where knights keep a careful watch on those "+
      "imprisoned in the cell to the west.  "+ 
      "The only ornamentation is a lamp sitting on a square "+
      "table in the center of the room.\n");

   door1 = clone_object(SOBJ + "l1d2a");
   door1->move(TO);
   door2 = clone_object(SOBJ + "l1d3a");
   door2->move(TO);

   AI("table", "It is square, made of heavy wood, and sits in the " +
       "center of the room. There are benches underneath it.\n");
   AI("ceiling ", "It arches high above your head.\n");
   AI("walls", "The walls are smooth, dark, stone.\n");
   AI("lamp", "A simple oil-lamp.\n");
   AI(({"bench","benches"}), "They are narrow and made of hardwood. " +
      "The benches look uncomfortable for sitting.\n");
   ACI(({"bench","benches"}), ({"sit","sit on"}), "@@do_sit");
   AI("cell", "All you can see of the cell is a flat iron grill "+
      "set into the stone wall.\n");
   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   ACI("lamp", ({"get","take","remove"}),"@@do_get");

    reset_spur_room();     

}


init()
{
    ::init();
    ADA("do_get");
    ADD("do_sit", "sit");
    ADD("do_rise", "rise")
    ADD("do_rise", "stand");
    
}

int
do_get()
{
   write("As you try to remove the lamp from the table some "+
      "of the oil spills onto your skin, burning it.\n");
   say(QCTNAME(TP) + " tries to take the lamp and gets burned.\n");
      TP->add_fatigue(-10);
   return 1;
}

int
do_sit()
{
   write("You sit down on one of the hard benches.\n");
   say(QCTNAME(TP) + " sits on one of the benches.\n");
   return 1;
}    

int
do_rise(string arg) {
    NF("Rising...\n");
 
    if (!arg) {
           write("You rise from the hard bench.\n");
           say(QCTNAME(TP) + " rises slowly from the bench.\n");
        return 1;
        }
    if (arg == "up" || arg == "bench" || arg == "from bench" || arg == "off bench") {
           write("You rise up from the bench, stretching your cramped legs "+
              "and sore buttocks.\n");
           say(QCTNAME(TP) + " sighs with relief as "+ TP->query_pronoun() +
              " rises from the hard wooden bench.\n");
        return 1;
        }
}


lockup()
{

     if (door2->query_locked() == 0)
    {
      door2->auto_close_door();   
      tell_room("/d/Krynn/solamn/hctower/spur/room/guardrm",
	  "The flat iron grill swings "+
           "closed. You hear the lock click.\n");  
    }


}
