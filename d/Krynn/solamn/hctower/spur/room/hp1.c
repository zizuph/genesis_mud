// hp1
// grace aug 1994
#include "../local.h"
inherit SPURRM;


object guard;
int key;

create_spur_room()
{

   SHORT("Hidden storage room");
   LONG("This room is half again as large as the Chapel.\n"+
      "It is as clean and well-kept as the rest of the "+
      "fortress, despite its hidden location. Numerous "+
      "crates line the bare stone walls, and a straw "+
      "pallet lies on the floor. A passageway leads south.\n");

   AE(ROOM + "alcove", "south", "@@walk_south@@");
   AE(ROOM + "hp2", "east", 0);
/*
clone_object(SOBJ + "arm_a")->move(TO);
*/

   AI(({"pallet","straw pallet"}),
      "It is a lumpy mattress made of straw.\n");
    AI(({"floor","stone floor"}),
      "The stones are polished to a mirror-like finish. "+
      "The floor so shiny you can see your reflection in it. "+
      "There is an odd, square-shape in the northwest corner.\n");
    AI(({"corner", "northwest corner", "square"}),
       "A large square with a unique pattern. Within the square "+
       "are two oblong shapes. The stones here are oddly worn, as "+
       "if this corner sees a lot of foot-traffic.\n");
    AI(({"oblong shapes", "oblong", "shapes", "footprints", "prints"}),
       "These oblong shapes are roughly the same size as the print "+
       "left by a booted foot. They are placed shoulder-width apart.\n");

   AI(({"crates","crate"}), "The wooden crates are all nailed " +
      "closed, and have words like 'Blankets', 'Candles', "+
      "'Torches', and 'Misc' printed on the front.\n");
   ACI(({"crate", "crates"}), ({"open", "smash", "break"}), "You "+
      "are unable to do that at this time.\n"); 
   AI(({"wall", "walls"}), "Smooth dark stone, bare and cool to "+
      "the touch.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   ACI(({"pallet","mattress"}), ({"lift","feel under", "search"}),
      "@@do_key");

   reset_spur_room();
}

nomask void
init()
{
   ::init();
/*
    ADD("do_stand", "stand");
*/
} 
                  
nomask static int
do_stand(string str)
{
   NF("You are already standing.\n");
   if(!str)
      return 0;   


   if (parse_command(str,environment(this_player()),
                        " [on] 'square'") ||
        parse_command(str,environment(this_player()),
                        " [in] 'square'")     ||
        parse_command(str,environment(this_player()),
                        " [within] 'square'"))
      {
                write("You stand within the square.\n");
                set_alarm(3.0, 0.0, "do_vkeep");
                return 1;
      }
   NF("You are already standing.\n");
      return 0;
}                                                                   

int
do_vkeep()
{
   write("You feel an odd tingling in your stomach.\n");
   write("Your sight blurs and your knees feel weak.\n");
   set_alarm(2.0, 0.0, "do_the_move");
   return 1;
}

int
do_the_move()
{
   write("Suddenly, you find yourself in a different place!\n");
   if (MEMBER(TP) || LAYMAN(TP))
     TP->move_living("suddenly", "/d/Krynn/solamn/vkeep/corridor", 0, 0); 
   else
     TP->move_living("suddenly", "/d/Krynn/solamn/vkeep/landing", 0, 0);
   TP->command("puke");
   return 1;
}     

int
do_key()
{
   object ob;

   seteuid(getuid(TO));

   if (key < 1)
      {
      key++;
      ob = clone_object(SOBJ + "main_key");
      if (ob->move(TP))
         {
         write("Your eyes pick out something metallic " +
            "under the pallet.\n");
         ob->move(TO);
       }
      else
         {
         write("You find a key under the pallet and " +
            "pick it up.\n");
	 say(QCTNAME(TP) + " picks something up off of " +
            "the floor.\n");
       }
      return 1;
   }
   write("You search beneath the entire pallet and find nothing.\n");
   say(QCTNAME(TP) + " looks disappointed.\n");
   return 1;
}

void
reset_spur_room()
{
   key = 0;
   if (!guard)
      (guard = clone_object(KNIGHT))->move_living(0,this_object());
}

int
walk_south()
{
    write("As you walk south along the passageway, suddenly the wall " +
	  "in front of you slides back, allowing you to pass.\n");
    return 0;
}



