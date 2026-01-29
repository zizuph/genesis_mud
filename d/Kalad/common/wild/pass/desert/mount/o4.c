inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
int pres,i;
object *ob;
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Hollowed-out chamber");
   set_long("A hollowed-out chamber of rock lies before you, hardly the work "+
      "of nature considering its roughly square shape. The ground here is "+
      "considerably smoother than in the passage to the east, though still "+
      "crude by any civilized standards. A strong, rather putrid smell "+
      "clings to everything in this room, though it seems to originate in "+
      "a large depression in the northwestern corner of the chamber. To "+
      "the south lies a crudely carved archway.\n");
   add_item(({"hollowed-out chamber","chamber","room"}),
      "It is where you, unluckily, are currently inside of.\n");
   add_item(({"ground"}),
      "A roughly smooth surface, though pitted here and there it is an "+
      "improvement over the surface of the tunnel in the east.\n");
   add_item(({"large depression","depression"}),
      "A shallow two foot hole nearly six feet across. Within it are the "+
      "partially eaten corpses of at least three humans.\n");
   add_item(({"corpses","corpse"}),
      "Various body parts have been torn and even chewed off, especially "+
      "in the softer parts, such as the face, stomach and buttocks. The "+
      "smell is nearly overpowering in its putridness.\n");
   add_item(({"crudely carved archway","carved archway","archway","arch"}),
      "Nothing more than a harshly carved rectangular opening in the "+
      "wall of the chamber's southern side.\n");
   add_item(({"wall"}),
      "Which wall?\n");
   add_item(({"side"}),
      "Which side?\n");
   add_item(({"walls","sides"}),
      "Be more specific, you can't examine them all at the same time.\n");
   add_item(({"southern wall","southern side"}),
      "There is an archway in it leading south.\n");
   add_item(({"western wall","western side","northern wall","northern side"}),
      "A very solid wall of dark grey stone. It is riddled with numerous "+
      "chisel marks, indicative of unnatural origins.\n");
   add_exit(CPASS(desert/mount/o3),"east");
   add_exit(CPASS(desert/mount/o5),"south","@@check_move");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/mo_leader));
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"An ogre emerges from the darkness.\n");
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/mo_leader));
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      tell_room(TO,"An ogre steps into view, emerging from the darkness.\n");
   }
}
check_move()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for (i = 0; i < sizeof(ob); i++)
   {
      if (ob[i]->query_name() == "Leader")
         {
         pres = 1;
        }
   }
   if(pres == 1)
      {
      ob1->command("say You no can go there!");
      ob1->command("kill " + TP->query_real_name());
      ob2->command("say Me kill you!");
      ob2->command("kill " + TP->query_real_name());
   }
   return pres;
}
