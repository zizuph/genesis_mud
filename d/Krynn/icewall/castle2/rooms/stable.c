#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object minotaur1, minotaur2, minotaur3, minotaur4, minotaur5, minotaur6;
object grif, freed_griffon;

int    griffon_imprisoned = 1;
int    griffon_free = 0;
int    griffon_secured = 0;
int    xp_base = 750;

public void
reset_icewall_room()
{
    if (!grif)
    {
	grif = clone_object(NPCK + "young_griffon.c");
	grif->move_living("xx", TO);
    }      

    griffon_imprisoned = 1;
    griffon_free = 0;
    griffon_secured = 0;
    xp_base = 750;

    if (!minotaur1)
    {
	minotaur1 = clone_object(NPCK + "stable_mino.c");
	minotaur1->move_living("xx", TO);
    }
    if (!minotaur2)
    {
	minotaur2 = clone_object(NPCK + "stable_mino.c");
	minotaur2->move_living("xx", TO);
    }
    if (!minotaur3)
    {
	minotaur3 = clone_object(NPCK + "stable_mino.c");
	minotaur3->move_living("xx", TO);
    }
    if (!minotaur4)
    {
	minotaur4 = clone_object(NPCK + "stable_mino.c");
	minotaur4->move_living("xx", TO);
    }
    if (!minotaur5)
    {
	minotaur5 = clone_object(NPCK + "stable_mino.c");
	minotaur5->move_living("xx", TO);
    }
    if (!minotaur6)
    {
	minotaur6 = clone_object(NPCK + "stable_mino.c");
	minotaur6->move_living("xx", TO);
    }

}

void
create_icewall_room()
{

    set_short("Castle stables");
    set_long("@@long_descr");


    add_exit("inner_courtyard","east");
    add_exit("north_stable","north","@@stairs");
    add_exit("south_stable","south","@@stairs");

    add_item(({"bolts","bolt"}),"Long bolts have been driven into " +
     "the stone walls. They end with an iron loop to which the " +
     "chains are linked.\n");
    add_item(({"chains","manacles"}),"@@chains_desc");
    add_item(({"passageway","passageways"}),"Wide passageways " +
     "leading north and south towards symmetrical spiral staircases. " +
     "You see nothing special about them.\n");
    add_item(({"set","set of chain","set of chains"}),"Which set of chains " +
     "do you wish to examine? There are four of them.\n");
    add_item(({"first set","first set of chains"}),"@@set_desc");
    add_item(({"second set","second set of chains"}),"The second set of " +
     "chains is bolted securely to the wall, but holds no creature.\n");
    add_item(({"third set","third set of chains"}),"The third set of " +
     "chains is bolted securely to the wall, but holds no creature.\n");
    add_item(({"fourth set","fourth set of chains"}),"The fourth set of " +
     "chains is bolted securely to the wall, but holds no creature.\n");

    set_tell_time(900);

    add_tell("Somewhere on the floor above you, heavy footsteps " +
     "resound.\n");

    reset_room();
}

string
set_desc()
{
     if(griffon_imprisoned)
      {
        return "The first set of chains holds down a young, battered " +
        "griffon. You notice, however, that the beast has managed to " +
        "loosen its manacles, and one might try to loosen them even " +
        "further, before one of the minotaurs notices it and " +
        "clamp them tight again.\n";
      }
  
      if(griffon_free)
      {
        return "The first set of " +
        "chains is bolted securely to the wall, but holds no creature.\n";
      }

      if(griffon_secured)
      {
        return "The first set of chains holds down a young, battered " +
        "griffon. You notice, that the manacles holding the beast " +
        "have been clamped tight, and the griffon has no chance of " +
        "escaping on its own. Its legs are bleeding.\n";
      }

}

string
chains_desc()
{
     if(griffon_imprisoned)
      {
        return "Those heavy chains appear " +
        "strong enough to hold up a drawbridge, and are definitely " +
        "too big to imprison any normal humanoid being, minotaurs " +
        "included. Each pair of chains ends with a set of four " +
        "manacles, leading you to believe that whatever was meant to " +
        "be kept here, has four appendages. And in fact, a four legged " +
        "beast is chained here - the first set of chains holds a young griffon.\n";
      }
  
      if(griffon_free)
      {
        return "Those heavy chains appear " +
        "strong enough to hold up a drawbridge, and are definitely " +
        "too big to imprison any normal humanoid being, minotaurs " +
        "included. Each pair of chains ends with a set of four " +
        "manacles, leading you to believe that whatever was meant to " +
        "be kept here, has four appendices.\n";
      }

      if(griffon_secured)
      {
        return "Those heavy chains appear " +
        "strong enough to hold up a drawbridge, and are definitely " +
        "too big to imprison any normal humanoid being, minotaurs " +
        "included. Each pair of chains ends with a set of four " +
        "manacles, leading you to believe that whatever was meant to " +
        "be kept here, has four appendices. And in fact, a four legged " +
        "beast is chained here - the first set of chains holds a young griffon. " +
        "The manacles have been clamped very tight on its legs, to the point " +
        "of bleeding.\n";
      }

      return "Room buggy! Notify the wizards!\n";
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string

long_descr()

{ return ("" +
     "Long ago, this was the castle's stable. Though the stronghold " +
     "itself did not possess any mounted garrison, couriers, guests, " +
     "and the lord of the castle " +
     "had their horses well cared for. Today, in the age of ice, this " +
     "chamber must have found a different use, for on the floor you " +
     "spot many thick as a bugbear's arm chains with heavy manacles " +
     "attached. To the north and south wide passageways open. At " +
     "both their ends you can see staircases leading upward.\n");

}

int
stairs()
{ 
  write("Stepping through the narrow passageway, you exit the " +
    "stable.\n");
  say(QCTNAME(TP) + " steps through the narrow passageway.\n");
  return 0;
}
  
int
clamp(string str)
{
   if(str != "manacles")
       {
         notify_fail("Clamp what? The manacles?\n");
         return 0;
       }

   if(griffon_imprisoned)
    {
     write("You manage to distract the griffon and lean down to clamp its " +
        "manacles tight again! As you step back, the griffon lunges with " +
        "his sharp beak, but you manage to avoid the desperate attack.\n");
     say(QCTNAME(TP) + " manages to distract the griffon and leans down " +
        "to clamp its manacles tight! The griffon tries to attack with its " +
        "beak, but " + QTNAME(TP) + " manages to leap back just in time to " +
        "avoid the desperate lunge.\n");
     griffon_imprisoned = 0;
     griffon_secured = 1;

     if(TP->test_bit("krynn", 3, 11))
     {
        TP->catch_msg("\nYou feel strange... as if you repeated " +
                     "your own footsteps.\n");
        return 1;
     }

     TP->catch_msg("\nYou feel more experienced.\nIt was an evil deed to " +
       "keep the freedom-loving creature imprisoned.\n");
     tell_room(E(TP), QCTNAME(TP) + " smiles evily and looks more experienced.\n", TP);

     TP->add_exp(xp_base, 0);
     TP->set_bit(3, 11);
     TP->set_alignment(TP->query_alignment() - 300);
     TP->change_prestige(-1);

     K_QUEST_LOG("quest", "Imprisoned Griffon (evil)", TP, xp_base);       

     return 1;
    } 

   if(griffon_secured)
    {
     write("There is no point in doing that. The manacles are already clamped " +
       "tight, and the griffon isn't going anywhere soon.\n");
     return 1;
    }

   if(griffon_free)
    {
    write("What's the point in clamping a set of empty manacles? Trying to " +
       "capture the very air, aren't you?!\n");
    return 1;
    }
}

int
loosen(string str)
{
   if(str != "manacles")
       {
         notify_fail("Loosen what? The manacles?\n");
         return 0;
       }

   if(griffon_imprisoned)
    {
     write("You manage to distract the griffon and lean down to loosen its " +
        "manacles! As you step back, the griffon lounges with " +
        "his sharp beak, but you manage to avoid the desperate attack.\n\n" +
        "Suddenly, the griffon realizes it is free, and moves for the " +
        "stable's doorway, using every ounce of its remaining strength to leap " +
        "into the air and fly away towards the high mountain.\n\n" +
        "The young battered griffon screeches happily as it beats his " +
        "wings on the crisp icy air.\n");
     say(QCTNAME(TP) + " manages to distract the griffon and leans down " +
        "to loosen its manacles! The griffon tries to attack with its " +
        "beak, but " + QTNAME(TP) + " manages to leap back just in time to " +
        "avoid the desperate lounge.\n\nSuddenly, the griffon realizes " +
        "it is free, and leaps for the stable's " +
        "doorway, using every ounce of its remaining strength to leap " +
        "into the air and fly away towards the high mountain.\n\n" +
        "The young battered griffon screeches happily as it beats his " +
        "wings on the crisp icy air.\n");

     griffon_imprisoned = 0;
     griffon_free = 1;

    if (present("_stable_mino", TO))
      {  
        say("A minotaur yells: It has gotten away! Notify Hrun!\n");
        write("A minotaur yells: It has gotten away! Notify Hrun!\n");   
      }

    freed_griffon = present("griffon", this_object());

    if (objectp(freed_griffon))
        freed_griffon->remove_object();

     if(TP->test_bit("krynn", 3, 11))
     {
        TP->catch_msg("\nYou feel strange... as if you repeated " +
                     "your own footsteps.\n");
        return 1;
     }

     TP->catch_msg("\nYou feel more experienced.\nIt was an good deed to " +
       "set the wild creature free.\n");
     tell_room(E(TP), QCTNAME(TP) + " smiles happily and looks more experienced.\n", TP);

     TP->add_exp(xp_base, 0);
     TP->set_bit(3, 11);
     TP->set_alignment(TP->query_alignment() + 300);
     TP->change_prestige(300);

     K_QUEST_LOG("quest", "Imprisoned Griffon (good)", TP, xp_base);       

     return 1;
    } 

   if(griffon_secured)
    {
     write("The griffon appears tense. Perhaps the pain from manacles clamped " +
       "very tight over its legs makes it especially wary against anyone " +
       "approaching. If you tried to free the griffon now, it would most " +
       "likely attempt to tear you to pieces.\n");
     return 1;
    }

   if(griffon_free)
    {
    write("What's the point in loosening a set of empty manacles?\n");
    return 1;
    }
}


void
init()
{
    ::init();

    add_action(clamp, "clamp");
    add_action(loosen, "loosen");
}        
    
