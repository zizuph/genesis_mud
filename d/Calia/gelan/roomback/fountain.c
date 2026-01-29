
/* Code containing the description of the most of the items in the fountain
   in Gelan. Originally coded by Snarf. 
   Coin-related code (quest?) was not complete, so it was commented out 
   by Maniac, 7.94
   Code to remove headaches when drinking / washing has been commented out 
   for the time being, by Maniac 7.94
   Action for applicant task added Maniac 25/7/95
   Inherit from water room and made drinking have effect, Maniac, 2/8/96
   Added water vials to collect for Elemental Worshippers, Maniac, 6/11/96
   Made soaking more easy, Maniac, 17/12/96
   Stopped drinking if player is completely soaked, Maniac, 17/5/98
   Fixed typo, Maniac, 4/3/99
 */

#pragma save_binary

inherit "/d/Calia/std/water_room";

#include "snarfdefs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Calia/glykron/palace/specials/orange_task.h"

#define TP this_player()


void
make_fountain()
{
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_prop(ROOM_I_TYPE, ROOM_IN_WATER); 
  
  add_item(({"bottom","bottom of the fountain","bottom of fountain",
	     "bottom of pool","bottom of the pool"}),
    "The bottom of the fountain is made of some kind of magical " +
    "stone. You notice hundreds of tiny water vials scattered " +
    "down there. You could probably collect them if you wanted.\n");

  add_item(({ "objects", "tiny objects", "tiny vials", "tiny water vials", 
              "water vials", "vials"}), 
       "There are hundreds of tiny water vials resting at the bottom " +
       "of the fountain.. or perhaps they are just refractions of light " +
       "on the stone? You could always try collecting them.\n"); 

  add_item(({"Caliana", "caliana","golden heroine","heroine"}),
	   BS("@@statue|1"));
  add_item(({"dragon","black dragon"}),BS("@@statue|2"));
  add_item(({"statue","mighty statue","golden statue","mighty golden statue"}),
	   BS("@@statue|3"));
  add_item("fountain","The fountain is a large round pool, " +
	   "filled with deep blue water. There seem to be tiny objects " +
           "scattered on the bottom.\n");
  add_item(({"pool","large pool","round pool","large round pool"}),
	   "The pool is filled filled with deep blue water. There seem " +
           "to be tiny objects scattered on the bottom.\n");
  add_item(({"water","blue water","deep blue water"}),
	   "The water has a deep blue color and feels very smooth.\n");
}


string
statue(string flag)
{
  string text;
  
  text = "";
  if (flag == "2" || flag == "3") text = text + "The dragon is a hideous " +
    "creature and seems to be writhing with pain and malice. It has a " +
    "slimy body covered with black and grey scales, more than the usual " +
    "number of legs and heads and long, sharp fangs. Like any respected " +
    "dragon, it belches " +
    "dangerous, impressive flames. The creature's leathery wings are " +
    "equipped with sharp talons. ";
  if (flag == "1" || flag == "3") text = text + "Caliana, the golden " +
    "heroine, an athletic " +
    "figure, is holding a splendid, magic sword in her right hand and a " +
    "skilfully ornamented shield in the left hand. She is wearing a " +
    "golden helmet on her shining long mane and her legs are clad in " +
    "golden leggings. On her athletic chest she is carrying a golden " +
    "platemail " +
    "and over her shoulders she is wearing a fluttering cape.";
  return BS(text + "\n");
} 



int
shout(string str)
{
    object tp = this_player();
    object ticket, coin;

    if ((str != "Praise Caliana") && (str != "praise Caliana") &&
        (str != "praise caliana") && (str != "Praise caliana"))
        return 0;

   tp->catch_msg("You shout out loudly: Praise Caliana!\n");
   tell_room(this_object(), QCTNAME(tp) + " shouts out loudly: " +
                 "Praise Caliana!\n", tp);

   if (ticket = present(TICKET_NAME, tp)) {
       tp->catch_msg("Your ticket turns into a crystalline coin!\n");
       ticket->remove_object();
       coin = clone_object(COIN);
       coin->move(tp);
       return 1;
   }
   else  {
      tp->catch_msg("Nothing happens..\n"); 
      return 1;
   }
}


int
drink(string rest)
{
    object tp = this_player(); 
    string x,y,z;
    int c;
    
    notify_fail("Drink what from what?\n");

    if (!rest) 
      return 0;

    if ((sscanf(rest,"%sfrom %s",x,y)) != 2) return 0;
    if (!(x == "" || x == "water ")) return 0;
    if (sscanf(y,"the %s",z)) y = z;
    if (y != "fountain" && y != "pool") return 0;

    c = 0; 
    while (tp->drink_soft(50, 0) && c < 15)
        c++; 

    if (!c) {
        write("You have drunk all that you can.\n"); 
        return 1;
    } 

    say(QCTNAME(TP) + " drinks some water from the fountain.\n");
    write("You drink some water from the fountain.\n");
    return 1;
}


int
wash(string rest)
{
    string  x,*pron,*pron1,*pron2;
    int     i,face;

    pron1 = ({"his face","her face","its face","your face"});
    pron2 = ({"himself","herself","itself","yourself"});

    if (!rest) {
      write("Wash what?\n");
      return 1;
    }
    if (sscanf(rest,"%sface%s",x,x)) pron = pron1;
    else if (sscanf(rest,"%smyself%s",x,x)) pron = pron2;
    else return 0;
    if ((sscanf(rest,"%swater%s",x,x) != 2) &&
	(sscanf(rest,"%sfountain%s",x,x) != 2) &&
	(sscanf(rest,"%spool%s",x,x) != 2 )) return 0;
    

    say((QCTNAME(TP) + " washes " + pron[(TP->query_gender())] + 
        " in the fountain.\n"));
    write("You wash " + pron[3] + " in the fountain.\n");
    return 1;

}



int
bath(string rest)
{
  string x;

  if (!rest) return 0;
  if ((!(sscanf(rest,"%sfountain%s",x,x))) &&
      (!(sscanf(rest,"%swater%s",x,x))) &&
      (!(sscanf(rest,"%smyself%s",x,x))) &&
      (!(sscanf(rest,"%spool%s",x,x)))) return 0;
  return wash("myself fountain");
}


int
swim(string foo)
{
  write("The fountain isn't deep enough for you to swim in.\n");
  return 1;
}




int
collect(string str)
{
    object vial;
    int num;
    if (str != "vials")
    {
        notify_fail("Collect vials?\n");
        return 0;
    }
    vial=clone_object("/d/Calia/worshippers/objects/water_vial");
    num = 3 + random(6);
    vial->set_heap_size(num);
    if (!vial->move(this_player())) { 
        write("You collect "+num+" water vials from the fountain.\n");  
        say(QCTNAME(TP)+" collects some water vials from the fountain.\n"); 
        return 1;
    } 
    write("Hmm, you had trouble collecting the vials for some reason.\n"); 
    return 1;
}

void
init()
{
    ::init();
    add_action(drink,"drink",0);
    add_action(wash,"wash",0);
    add_action(bath,"bath",0);
    add_action(swim,"swim",0);
    add_action(shout, "shout");
    add_action(collect, "collect"); 
}

