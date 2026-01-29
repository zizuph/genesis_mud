/*
   Pax Tharkas, Ground level, Hollow wall, gate to the outside.

   hollow_wall2.c
   --------------

   Coded ........: 95/02/08
   By ...........: Jeremiah

   Latest update : 95/07/27
   By ...........: Jeremiah

   Modified by Blizzard.
   Added enter_inv() for quest purpose.
*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

#define EWALL \
   ({   \
      GROUND_LEVEL + "hollow_wall1", \
   })

#define WWALL \
   ({   \
      GROUND_LEVEL + "hollow_wall3", \
   })

#define I_RELEASED_ELF     "_i_released_elf"

int    gate_is_open = 0;    /* 0 : Gate is NOT open */
object other_room = VALLEY + "main_gate";
object guard1, guard2, guard3;

void   we_are_close();

void
reset_pax_room()
{
   if (!present("bozak",TO) && !present("sivak",TO))
   {
      guard1 = clone_object(PMONSTER + "sivak");
      guard2 = clone_object(PMONSTER + "bozak");
      guard3 = clone_object(PMONSTER + "bozak");

      guard2->set_leader(guard1);
      guard3->set_leader(guard1);

      guard1->team_join(guard2);
      guard1->team_join(guard3);

      guard1->add_act("push gates");
      
      guard1->move_living("arrives",TO);
      guard2->move_living("arrives",TO);
      guard3->move_living("arrives",TO);
   }

   if(guard1)
      guard1->command("push gates");
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("Large gate");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"hinge", "hinges"}), "Large metal hinges mounted solidly " +
            "in the stone roof. Apparently it is possible for the " +
            "ceiling to swing down. You are not sure you want to be in " +
            "here to see what happens if it does.\n");

   add_item(({"gate", "gates", "double gate"}), "These are huge iron " +
            "reinforced gates. They stand 6 times as tall as a grown man, " +
            "and 8 horses could easily ride next to each other through " +
            "them. The gates look extremely sturdy, and could probably " +
            "withstand serious and persistent ramming attempts. The gates " +
            "seem to open inwards.\n"); 
   
   add_exit(GROUND_LEVEL + "hollow_wall3", "west", 0);
   add_exit(GROUND_LEVEL + "hollow_wall1", "east", 0);
   add_exit(COURT_YARD + "court_yard1", "south", 0);
}


void
init()
{
   add_action("open_gate", "pull");
   add_action("close_gate", "push");
   ::init();
}

void
enter_inv(object dest, object old)
{
    ::enter_inv(dest, old);
    
    if ( dest->query_prop(I_RELEASED_ELF) )
        set_alarm(2.0, 0.0, &we_are_close());

}

void
we_are_close()
{
    object elf, drac;
    
    if ( elf = present("sarist", TO) )
    {
        elf->command("say The gate! We almost made it!");
        
        if ( drac = present("draconian", TO) )
        {
            drac->command("shout Kill that elf! Close the gate!");
            drac->command("kill sarist");
            elf->command("say Let's leave this place! Quick!");
            drac->command("push gate");
            
            if ( guard1 )
                guard1->command("kill sarist");
        }
    }

}
         
int
open_gate(string what)
{
   if (what != "gate" && what != "gates" && what != "Gate" && what != "Gates")
   {
      NF("Pull what ?\n");
      return 0;
   }

   if (gate_is_open)
   {
      write("The gates are already open!\n");
      return 1;
   }

   if (TP->query_stat(0) < 60)
   {
      write("You try with all your strength to pull the mighty gates. " +
            "open. They don't move an inch.\n");
      say(QCTNAME(TP) + "tries to pull the mighty gates open, but " +
            "fails.\n");
      return 1;
   }

   write("With all your strength you try to pull the gates " +
         "open. Slowly, with a rumbling sound, the mighty gates swing " +
         "inward. Through the open gates you see the curtain walls in " +
         "front of the fortress and beyond them, the narrow valley " +
         "leading up to here.\n");
   say(QCTNAME(TP) + " tries to pull the gates open. With a rumbling " +
       "sound the mighty gates swings inward. Through the open gates you " +
       "see the curtain walls, and the valley below the fortress.\n");

   other_room->gate_opens();
   add_exit(VALLEY + "main_gate", "north", 0);
   gate_is_open = 1;
   return 1;
}


int
close_gate(string what)
{
   if (what != "gate" && what != "gates" && what != "Gate" && what != "Gates")
   {
      NF("Push what ?\n");
      return 0;
   }

   if (!gate_is_open)
   {
      write("You push at the closed gates. Nothing happens.\n");
      say(QCTNAME(TP) + " pushes at the closed gate. Nothing happens.\n");
      return 1;
   }

   if (TP->query_stat(0) < 60)
   {
      write("You try with all your strength to push the mighty gates. " +
            "shut. They don't move an inch.");
      say(QCTNAME(TP) + " tries to push the mighty gates shut, but fails.");
      return 1;
   }

   write("With all your strength you try to push the gates " +
         "shut. Slowly, with a rumbling sound, the mighty gates swings " +
         "back in place, closing the entrance to the fortress.\n");
   say(QCTNAME(TP) + " tries to push the gates shut. With a rumbling " +
       "sound the mighty gates swings back in place, closing the entrance " +
       "to the fortress.\n");

   other_room->gate_closes();
   remove_exit("north");
   gate_is_open = 0;
   return 1;
}


string
ewall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = EWALL;
   inv = ({});

   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }

   if (inv && sizeof(inv) > 0)
   {
     live = FILTER_LIVE(inv);
     if (sizeof(live) > 0)
        return ("To the east you see " + COMPOSITE_LIVE(live) + ". ");
   }
   return ("The east part of the hollow wall looks empty. ");
}


wwall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = WWALL;
   inv = ({});

   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }

   if (inv && sizeof(inv) > 0)
   {
     live = FILTER_LIVE(inv);
     if (sizeof(live) > 0)
        return ("Looking west you see " + COMPOSITE_LIVE(live) + ". ");
   }
   return ("The west part of the hollow wall is empty. ");
}


string
room_descr()
{
   string ret_str;

   ret_str =  "You are standing inside the hollow wall, known as the great " +
              "Tharkadan wall. This wall links the two towers of Pax " +
              "Tharkas. The hollow wall stretches, like a long corridor, " +
              "to both sides of you. " + ewall_descr() + wwall_descr() + 
              "Above you, along the south ceiling, you see large hinges " +
              "mounted in the stone roof. In the north wall you see a " +
              "mighty double gate.";

   if (!gate_is_open)
      ret_str += " Right now the gates are closed.\n";
   else
      ret_str += " The mighty gates are open. Looking through the opening " +
                 "you see the curtain walls, and the narrow valley below " +
                 "the fortress.\n";

   return ret_str;

}

