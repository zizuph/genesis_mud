/* 
 * Armoire
 * (Grace aug 1994)
 *
 * 2008-04-01 Lunatari fixed a GUILD_NAME_CLERIC bug (uncommented)
 */
#include "../local.h"

inherit SPURRM;

int robe;

create_spur_room()
{

   SHORT("Inside the armoire");
   LONG("This is a fairly sizeable and well-made wardrobe.  "+
      "It smells strongly of the cedar panelling which lines "+
      "the interior.  A shelf has been built into the armoire "+
      "just above eye-level, and rod for hanging clothing is "+
      "below it.\n");

   INSIDE;
   LIGHT;

   clone_object(SOBJ + "arm_b")->move(TO);   

   AI("interior", "It is spacious and fragrant with the scent "+
     "of cedar.\n");
   AI("shelf", "It is dusty and bare.\n");
   ACI(({"air","fragrance", "scent"}), "smell", "It smells strongly "+
      "of cedar.\n");
   AI("rod", "@@rod");
   AI(({"panel", "panelling", "panels"}), "The panels have been "+
     "sanded and lightly rubbed with oil. Some of the panels are "+
     "perfect, while others have knots in them.\n");
   AI(({"knot", "knots"}), "The knots are dark reddish swirls in " +
       "the wood.\n@@knot_aware@@");
   AI("hole", "You can't tell much about the hole except that it "+
     "is just big enough to put your finger in.\n");

   reset_spur_room();
}

init()
{
    ::init();
    ADD("do_pass", "put");
    ADD("do_pass", "stick");
    ADA("get");
    ADD("get","take");
    ADD("feel_me_up", "feel");
    ADD("feel_me_up", "touch");
    ADD("feel_me_up", "search");
}

string rod()
{
     if (robe == 4)
      {
          write("There is nothing hanging from the rod at this time.\n");
          return "";
      }

    write("There is a robe of some sort hanging from the rod.\n");
    return "";
}

string knot_aware()
{
    if (TP->query_skill(SS_AWARENESS) > 18)
            return("One of the knots seems to have fallen from "+
               "a panel in the back of the armoire, leaving a "+
               "small circular hole.\n");     

        return "";
}  
        


int
get(string str)
{
    NF("Get what?\n");
    if ((str == "robe") || (str == "robe from rod") ||
        (str == "robes") || (str == "robe off rod"))
      {

          if (robe == 4)
            {
                write("There doesn't seem to be anything "+
                   "hanging from the rod.\n");
                return 1;
            }
          /* GUILD_NAME_CLERIC is not defined, I dont know what
           * it should be. Lunatari 2008-04-01
	  if (TP->query_guild_name_lay() == GUILD_NAME_CLERIC)
	    clone_object(SOBJ + "clericrobe")->move(TP);
	  else
          */

          clone_object(SOBJ + "burnoose")->move(TP);

          write("You get a robe from the rod.\n");
          SAY(" gets robe from the rod.\n");
          robe++;
          return 1;
      }
    return 0;
} 

int
do_pass(string str)
{
    NF("put what?\n");
    if ((str == "finger in hole") || (str == "finger into hole") ||
        (str == "finger in knot") || (str == "finger in knot hole") ||
        (str == "my finger in hole") || (str == "my finger into hole") ||
        (str == "my finger in knot") || (str == "my finger in knot hole"))
       {   
          write("You put your finger into the knot hole, releasing "+
             "the latch holding the back wall in place. The panel "+
             "swings back, opening into another room.\n");
          TP->move_living("suddenly", ROOM + "arm", 1);
       return 1;
       }
   return 0;
}

int
feel_me_up(string str)
{
    NF("Feel what?\n");
    if ((str == "knot") || (str == "hole") || (str == "wall") || (str == "walls") || (str == "panel"))
       {  
           write("It feels very smooth and hard. Your fingers run across "+
                   "a place in a panel where a knot has fallen out, leaving "+
                   "a finger-sized hole.\n");
           return 1;
        }
     if ((str == "me") || (str == "myself"))
        {
            write("Wow! That feels g-o-o-o-o-d!\n");
            say(QCTNAME(TP) + " seems to be playing with " 
                  + TP->query_objective() + "self.\n");
            return 1;
       }
   return 0;
}

reset_spur_room()
{
   robe = 0;
}

