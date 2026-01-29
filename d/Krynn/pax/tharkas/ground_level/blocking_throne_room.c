/*
Pax Tharkas, Ground level, The Pax Tharkas throne room. Earlier
the hall of Thanes.


throne_room.c
-------------

Coded ........: 95/01/25
By ...........: Jeremiah

Latest update : 95/04/19
By ...........: Jeremiah

Modified on 10/11/96 by Morrigan.
The room was modified to prevent people from seperating Ember
and Verminaard through use of bombs or other means, now they
will fight together as a pair, as they were intended. It also
prevents players with higher than 160 stats from leaving the
room after attacking. Ember will position his body in between
the player attempting to flee and the exit. Players with less
that 160 stats may still flee...
*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

#define BALC \
({   \
      WALL_LEVEL + "balcony2", \
 })


object highlord, dragon;


reset_pax_room()
{
   if(P("verminaard",TO) || P("pyros", TO) || P("ember", TO))
      return;
   
   highlord = clone_object(PMONSTER + "verminaard");
   highlord->equip_me();
   
   dragon = clone_object(PMONSTER + "pyros");
   
   dragon->set_leader(highlord);
   highlord->team_join(dragon);
   
   highlord->move_living("arrives",TO,0,0);
   dragon->move_living("arrives",TO,0,0);
}


void
create_pax_room()
{
   reset_pax_room();
   
   set_short("Throne room");
   set_long("You are standing in a large room, furnished with every " +
      "possible luxury. You are sure that all that is beautiful, " +
      "graceful, delicate and valuable in the world, has been " +
      "brought here to decorate this room. A large ornate throne " +
      "stands, raised above the floor on a stone dais, in the " +
      "south end of the room. Rare and priceless silver mirrors " +
      "hang on the walls. High above you, just under the ceiling, " +
      "a balcony, most of it hidden in shadow, runs along the " +
      "north side of the room. A pair of huge open doors lead " +
      "west, into dimly lit room.\n");
   
   INSIDE;
   
   add_item("throne","A huge ornate throne, beautifully carved out of " +
      "a solid piece of bright rock. Gemstones in all colours " +
      "decorate the sides and the back of the throne. Large, and " +
      "smooth polished gems, decorate the end of each armrest. " +
      "A marvellous piece of stone masonry.\n");
   
   add_item(({"gem", "gems"}), "The gems are solidly planted into " +
      "the stone throne.\n");
   
   add_item("dais", "A semi circle shaped stone plateau rising in " +
      "the south end of the room. On the dais you see a large " +
      "ornate throne.\n");
   
   add_item(({"mirror", "mirrors", "silver mirror"}), "These are " +
      "beautiful silver mirrors. You can't remember ever to " +
      "have seen anything like them. Looking closer you " +
      "realize, that all the mirrors have been placed in a " +
      "way, so that no matter where you look, you would see " +
      "the person standing on the dais in front of the " +
      "throne.\n");
   
   add_item("balcony","@@balcony_descr");
   
   add_exit(GROUND_LEVEL + "corridor2", "north", "@@check_blocked");
   add_exit(GROUND_LEVEL + "dragons_lair", "west", "@@check_blocked");
}


int
check_blocked()
{
   object enemy;
   
   if (TP->query_wiz_level())
      {
      return 0;
   }
   
   if (TP->query_name() == "Verminaard" ||
         TP->query_name() == "Ember" ||
      TP->query_name() == "Pyros")
   {
      write("Oh no, you will stand and fight!\n");
      return 1;
   }
   
   enemy = TP->query_enemy();
   if (enemy->query_name() == "Verminaard" ||
         enemy->query_name() == "Ember")
   {
      
      if (TP->query_stat(0) > 160 || TP->query_stat(1) > 160 ||
            TP->query_stat(2) > 160)
      {
         if (present(highlord))
            {
            highlord->command("say You are brave... but you have crossed "+
               "the line between courage and stupidity.  Now you will "+
               "die!\n");
            return 1;
          }
         
         write("The massive red dragon moves to block the exits, "+
            "blocking your escape! Fear settles in as you realize "+
            "what you've gotten yourself into.\n");
         say(QCTNAME(TP)+" tries to flee, but the dragon blocks "+
            OBJECTIVE(TP)+" from escaping.\n");
         return 1;
       }
      
      if (present(highlord))
         {
         highlord->command("say Young fool... You are brave, but you "+
            "lack common sense...\n");
         highlord->command("say Perhaps that will come with age. My "+
            "Mistress has use for such courage; as such, I will let "+
            "you flee... killing one as pathetic as yourself is not "+
            "even worth the effort.\n");
         return 0;
       }
      
      write("The massive red dragon allows you to flee, finding you "+
         "pathetic and unworthy of his attention.\n");
      say("The dragon allows "+QTNAME(TP)+" to flee, apparently bored "+
         "with such a pathetic creature.\n");
      return 0;
   }
   return 0;
}

string
balcony_descr()
{
   string *roomfiles;
   string ret_str;
   object *inv, *live, room;
   int    i;
   
   roomfiles = BALC;
   ret_str = "Taking a closer look at the balcony above you, ";
   inv = ({});
   
   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }
   
   if (sizeof(inv) == 0)
      ret_str += "you see nothing.";
   
   if (sizeof(inv) == 1)
      ret_str += "you see a figure standing in the shadows. You " +
   "cannot see who or what it is.";
   
   if (sizeof(inv) > 1)
      ret_str += "you see some figures standing in the shadows. " +
   "You cannot see who or what they are.";
   
   ret_str += "\n";
   return ret_str;
}
