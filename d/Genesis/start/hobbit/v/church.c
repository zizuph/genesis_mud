/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 *
 * The Hobbiton Church, starting location of the hobbits.
 *
 * Coded by Rastlin and Tricky.
 *
 * Revision history:
 * /Mercade, 09-02-1994: Added Styles book for newbies.
 * /Khail, 09-12-1996  : Updated 'pray' to conform with
 *                       current ghost routines.
 *
 * Added newbie poster
 * TAPAKAH, 25/05/2005
 *
 * Added newbie portal
 * TAPAKAH, 17/07/2005
 *
 * Lavellan, 2010/08/22 : Added "start" offer and confirm messages, copied from
 *                        elf start, fixed ghost destination.
 *
 * Finwe, Apr 25, 2011: Added map routine prop
 *  
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Genesis/login/login.h"

#define ALLOWED_RACES ({ "hobbit" })

/*
 * Prototype
 */
void reset_room();
void start_offer();

void
create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt"); 
   set_short("The Hobbiton church");
   set_long("You are standing in the middle of the Hobbiton church. "
   + "There are no windows at all in this church, but it is "
   + "lit by hundreds of candles attached to the walls or "
   + "hanging down from the roof. "
   + "On the north wall is a small opening that lets the "
   + "daylight in and is just big enough for a hobbit to pass through. "
   + "In the southern part of the church is a small crucifix. "
   + "On the west wall is a small painting with a golden frame. Beside "
   + "it is a small niche with an icon in it.\n");

   add_item("painting", 
     "The painting shows the powerful wizard "
   + "who helped the hobbits with their struggle "
   + "against some goblins that terrorised the village. "
   + "It is rumoured that the remaining goblins can "
   + "be found in the forest west from Hobbiton. "
   + "On a golden plaque under the painting you can read: "
   + "'Lord Rastlin -- A friend with power to help'.\n");

   add_item("crucifix",
     "It is a small golden crucifix, secured to the south wall. "
   + "On the crucifix you see an old man in a "
   + "long robe with a staff in his right hand. "
   + "Maybe you should pray to this man.\n");

   add_item(({"candles","candle"}),
     "There are hundreds of candles here in the church and "
   + "together they produce enough light to light up the entire "
   + "church. You wonder who has put all these candles in their "
   + "candlesticks, and who keeps them burning.\n");

   add_item("roof",
     "The roof looks solid and ancient. On it are burnmarks from candles "
   + "and dust from long ago.\n");

   add_item(({"niche","icon"}), 
      "The niche is a hole carved in the west wall. It is dusty and has "
    + "a small icon in it. On the icon you see a vague picture of a "
    + "bald and toothless sorceror. Someone wrote in the dust beside "
    + "the icon: 'Hail Tricky, Lord of the Shires'.\n");

   add_exit(STAND_DIR + "bw_road1","north","@@nblock");
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   room_add_object("/d/Genesis/start/newbie/poster");
   room_add_object("/d/Genesis/start/newbie/portal");
   reset_room();
}

void
reset_room()
{
    /* This book is very helpful for beginners. */
    
    if (!present("faq_book"))
    {
        seteuid(getuid());
    clone_object("/d/Genesis/start/FAQ/faq_book")->move(this_object());

    }
}

int
query_prevent_snoop()
{
   return 1; /* No snooping in the church */
}

void
init()
{
   ::init();
   add_action("pray","pray");
   add_action("pray","resurrect");
   add_action("do_start","start");
   set_alarm(1.0, 0.0, start_offer);

}

int
nblock()
{
   object tp;
   string race;

   tp = this_player();
   race = tp->query_race();

 /* Do not block wizards */
   if (tp->query_wiz_level() > 0)
      return 0;

 /* Block humans and elves */
   if ((race == "human") || (race == "elf"))
   {
      write("You are too big to go through the small opening.\n");
      say(QCTNAME(TP)+" attempts to go north, but fails.\n",TP);
      return 1;
   }
   return 0;
}

int
pray()
{
   object tp;
   string race;

   tp = this_player();
   race = tp->query_race();

   write(
      "You kneel in front of the crucifix and start to pray. "
    + "After a few seconds the church is filled by a "
    + "mystical pale green light. "
    + "Your mind starts to clear and you are overcome by "
    + "a sensation of ease.\n");
   if (!(tp->query_invis()))
      say(QCTNAME(tp) + " kneels in front of the crucifix.\n"
       + "After a few seconds the church is filled with "
       + "a mystical pale green light.\n",tp);
   else
      say("A mystical pale green light starts to fill the church.\n");

  /*
   * First we see if the player has a ghost_player.c object.
   * If this is the fact, we'll make sure they've got a ghost
   * var set so the death mark will function, and then give
   * a new death mark to try to repeat the death sequence.
   */
    if (MASTER_OB(tp) == LOGIN_NEW_PLAYER)
    {
      /*
       * Player is a physical ghost. Make sure the ghost
       * var is 33 (GP_DEAD | GP_BODY) and send them to
       * the bodies room.
       */
        tp->set_ghost(GP_DEAD | GP_BODY);
        write("The green light swells and swirls around " +
            "you brightly, you feel yourself becoming one " +
            "with the light as it flashes off towards another "+
            "place!\n");
        say("The greenish light intensifies, swirling " +
            "brighter and faster around " + QTNAME(tp) + " " +
            "with each passing second. You have to close " +
            "your eyes...when you open them a second later, " +
            tp->query_pronoun() + " is gone.\n");       
//        tp->move_living("M", "/d/Genesis/login/bodies", 1, 0);
        tp->move_living("M", "/d/Genesis/login/creation", 1, 0);
        say(QCTNAME(tp) + " arrives in a flash of light.\n");
	return 1;
    }

  /*
   * Ok, the player isn't using a ghost_player.c object, but we
   * have to make sure it's not a normal player with a ghost
   * var set running around. That's an easy repair by just
   * removing the ghost variable.
   */
   if (tp->query_ghost())
   {
      tp->remove_ghost();
      write("The green light explodes in a bright flash!"
          + "You can feel yourself take a more natural form.\n");
      say("The green light explodes in a bright flash.\n",tp);
      say(QCNAME(tp)+" appears in a more solid form.\n",tp);
      say("The green light starts to fade away.\n");
    return 1;
   }
  /* Allow humans and elves to leave the church anyway */
   if ((race == "human") || (race == "elf"))
   {
    /* Noise inside the church */
      write("You feel yourself becoming weightless. For a moment you think\n"
          + "you are floating. When you open your eyes again, you are no\n"
          + "longer inside the church.\n");
      say("The green light turns into bright yellow, and you have to\n"
        + "close your eyes. When you open your eyes again after a short\n"
        + "while, " + QTNAME(tp) + " is gone.\n");
      tp->move(STAND_DIR + "bw_road1");
    /* Noise outside the church */
      say("Suddenly, a green light flashes brightly, and you have to\n"
        + "close your eyes. When you open your eyes again after a short\n"
        + "while, " + QNAME(tp) + " is standing in front of you.\n");
   }
   return 1;
}
    
string
wizinfo()
{
   return (
        "This is the starting location for the Hobbit race. "
      + "Some of the races are to large to enter and leave "
      + "the church. They can leave the church by praying. "
      + "Here the hobbits (and maybe some other race) come "
      + "to pray, to get back from ghosthood. "
      + "The name of this small village that the hobbits are "
      + "living in, is Hobbiton (Yes, it is the one from Middle Earth). "
      + "It is almost the same as it is in Tolkien's world. "
      + "Hobbiton was coded by Rastlin and Tricky in 1991.\n");
}

int
do_start(string str)
{
   if (str == "here")
   {
      /* Allow only the right races to start here */
      if (member_array(this_player()->query_race(),ALLOWED_RACES) >= 0)
      {
         this_player()->set_default_start_location(STAND_DIR + "church");
         write("The next time you return to this world, you will " + 
             "begin your journey here.\n");
         return 1;
      }
      notify_fail("You cannot start here.\n");
      return 0;
   }
}

void
start_offer()
{
  if ((member_array(this_player()->query_race(),ALLOWED_RACES) >= 0) &&
      this_player()->query_default_start_location()!=file_name(this_object()))
    write("\nTo start here, give the command 'start here'.\n");
}
