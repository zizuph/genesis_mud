inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
void reset_room();
void create_killers();
int summoned;
void
create_room()
{
   ::create_room();
   INSIDE;
   set_short("The chamber of the Matron Mother of House Claddath");
   set_long("This is the private chamber of the Matron Mother of "+
      "House Claddath. An almost palpable emotion of terror hangs in the air "+
      "here, like the specter of death gazing down upon a man on the brink "+
      "of death, yet still vainly clutching to life. Midnight-black onyx "+
      "braziers line the sides of this pentagon-shaped chamber, filling its "+
      "darkened recesses with its intoxicating incense. A huge chest lies "+
      "off to one corner along with a single bed of black spider silk. At the "+
      "center of the room lies a single, blood-red column of light.\n");
   add_item(({"chamber","private chamber"}),
      "A decidedly unpleasant place to be in, an atmosphere of total "+
      "dread pervades this chamber like maggots in a rotting corpse.\n");
   add_item(({"midnight-black onyx braziers","midnight-black braziers","onyx braziers","braziers","brazier"}),
      "The black stone containers are continously spewing forth the "+
      "aromatic and intoxicating odor of incense.\n");
   add_item(({"huge chest","chest"}),
      "A large rectangular-shaped container fashioned from pure adamantine. "+
      "It reflects the scarlet light coming from the center of the chamber "+
      "in a somehow menacing and terrible manner.\n");
   add_item(({"single bed","bed"}),
      "A spider-shaped bed wrapped in black spider silk that appears to "+
      "hover from the floor.\n");
   add_item(({"black spider silk","black silk","spider silk","silk"}),
      "Soft and velvety, the ebony material glistens slightly in the red light "+
      "that fills the room.\n");
   add_item(({"single column","single light","blood-red column","blood-red light","column","light"}),
      "A five foot wide beam of scarlet energy that descends through the floor "+
      "of this chamber.\n");
   add_item(({"floor"}),
      "The featureless black surface is punctuated only by the single, "+
      "blood-red column of light that stabs through it.\n");
   add_item(({"ceiling","walls","wall"}),
      "The strange and unusually featureless black surface seems to absorb "+
      "what little light is given off by the blood-red column at the center "+
      "of this chamber.\n");
   add_item("thesummoningspellforthedrowkillers","@@drow_killers");
   add_exit(CPASS(drow/house7/priest_chamber),"down","@@msg",-1,-1);
   set_noshow_obvious(1);
   reset_room();
}
void
reset_room()
{
   summoned = 0;
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h7_matron));
      ob1 -> move_living("xxx",TO);
   }
}
string
drow_killers()
{
   if(summoned)
      return("The killers have already been summoned.\n");
   set_alarm(6.0,0.0,"create_killers");
   return("The killers have not yet been summoned.\n");
}
void
create_killers()
{
   int i;
   summoned = 1;
   for(i = 0; i < 5; i++)
   {
      clone_object(CPASS(drow/npc/killer))
      ->move(TO);
      tell_room(TO,"A drow killer steps out of the red column of light!\n");
   }
}
msg()
{
   write("You step into the red light, and feel yourself grow lighter as "+
      "you are transported by the column.\n");
   say(QCTNAME(TP) + " steps into the red light, and seems to grow lighter "+
      "as " + TP->query_pronoun() + " is transported by the column.\n");
   return 0;
}
