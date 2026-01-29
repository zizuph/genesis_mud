/* Chapel, Vingaard Keep, coded by Percy.           */
/*                     modified by Grace, 04/07/94  */

/**********************************************************************
 * - Added the following:                                           - *
 * -   #include "/d/Krynn/solamn/vin/std/no_scry_room.c"            - *
 * -   add_prop(ROOM_M_NO_SCRY, query_no_scry);                     - *
 * -                                                                - *
 * - Modified by Damaris@Genesis 03/2005                            - *
 **********************************************************************/   
inherit "/lib/guild_support";
#include "../local.h"
#include <macros.h>

inherit SPURRM;
inherit "/d/Krynn/solamn/guild/spells/chapel_base.c";
#define CANDLE  SOBJ + "pcandle"
#include "/d/Krynn/solamn/vin/std/no_scry_room.c"
void
create_spur_room()
{
    add_prop(ROOM_M_NO_SCRY, query_no_scry);
    set_short("The chapel");
    LONG("To all followers of Paladine, this is a holy place.\nA " +
      "small room with white-washed walls, it smells strongly " +
      "of the beeswax and tallow candles that have been used " +
      "to illuminate it for centuries.  Hollows have been worn " +
      "into the stone floor by the knees of countless knights " +
      "seeking communion with their gods during their daily " +
      "devotions.  There is an alcove built into the north " +
      "wall and a simple altar sits on a dais to the west.\n" +
      "A prayerbook lies on the altar.\n");
   
   add_item("prayerbook", "It is very small and bound with white leather.\n");
   
   AI(({"candles","candle"}), "Long white beeswax candles burn " +
      "upon the altar.\n");
   AI(({"hollow","hollows"}), "The hollows have been worn into " +
      "stones by kneeling knights.\n");
   AI("altar", "It is very modest in size, plain and " +
      "adorned with candles and a prayerbook.\n"); 
   AI("dias", "A stone platform about one-hand high and one "+
      "man-length. On it rests the altar.\n");
   add_item("alcove","Candles are piled upon the shelves built " +
      "into the alcove.\n");
   add_item("shelves", "They look like ordinary shelves. If you " +
      "entered the alcove you might be able to examine them " +
      " more closely.\n");
   
   AE(ROOM + "vestibule", "east", 0);
   create_guild_support();
}


int
remove_medi_props()
{
   TP->remove_prop(LIVE_I_MEDITATES);
   TP->remove_prop(LIVE_S_EXTRA_SHORT);
}

void
init()
{
   ::init();
   init_guild_support();
    init_chapel();
   ADD("gs_meditate", "kneel");
   ADD("do_enter", "enter");
   ADA("pray");
   ADA("read");
   ADD("do_candle", "set"); 
   ADD("do_candle", "place"); 
   ADD("do_candle", "put"); 
}

// This function rewards a knight for placing a candle on the altar

int
do_candle(string str) // set, place, put
{
   object ob;
   NF("Place candle where?\n");
   
   if ((str == "candle on altar") || (str == "candles on altar"))
      {
      if (ob = present("paladine_candle", TP))
         {
         ob->remove_object();
         if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 5000)
            TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 5000);
         
         write("You reverently place the candle upon the altar.\n");
         say(QCTNAME(TP) + " places " + TP->query_possessive() + 
            " candle upon the altar.\n");
         return 1;
       } 
      return 0;
   }             
}

/*
* This function allows a knight to <pray> and <pray patron>
*/

int
pray(string str)
{
   NF("What?\n");
   
   if (!str) 
      {
      if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 1000)
         TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 1000);
      
      write("You kneel at the altar and pray to Paladine. It gives you a feeling of well-being.\n");
      say(QCTNAME(TP) + " does " + TP->query_possessive() + " daily devotions at the altar.\n");
      return 1;
   }
   
   if (str == "patron" || str == "to patron")
      {
      if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 3000)
         TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 3000);
      
      if (TP->query_knight_level() == 2)
         {
         write("You kneel at the altar and pray to Paladine for guidance.\n");
         write("As you make your devotions, a sense of serenity envelops you.\n");
         write(BS("You feel wonder at the certainty that the loving, accepting presence " + 
               "in the room is that of Paladine himself.", 70));
         write("Your resolve to be a dedicated, courageous, and honest Squire has firmed.\n");
         write(BS("You rise from your daily devotions, prepared for yet another day of " + 
               "fighting the forces of evil, and confident of Paladine's blessing.", 70)); 
         say(QCTNAME(TP) + " prays to " + TP->query_possessive() + " patron for guidance.\n");      
         return 1; 
       }             
      if (TP->query_knight_level() == 3)
         {
         write("You kneel at the altar and pray to Habbakuk for guidance.\n");
         write("As you make your devotions, a sense of harmony envelops you.\n");
         write(BS("You feel wonder at the certainty that the creative, stimulating presence " + 
               "in the room is that of Habbakuk, Patron of the Order of the Crown.", 70));
         write(BS("Your resolve to be a courageous, obedient, and passionate" +
               " Knight of the Crown has firmed.", 70));
         write(BS("You rise from your daily devotions, prepared for yet another day of " + 
               "fighting the forces of evil, and confident of Habbakuk's blessing.", 70)); 
         say(QCTNAME(TP) + " prays to " + TP->query_possessive() + " patron for guidance.\n");      
         return 1; 
       }
      if (TP->query_knight_level() == 4)
         {
         write("You kneel at the altar and pray to Kiri-Jolith for guidance.\n");
         write("As you make your devotions, a sense of righteousness envelops you.\n");
         write(BS("You feel wonder at the certainty that the magnanimous, disciplined presence " + 
               "in the room is that of Kiri-Jolith, Patron of the Order of the Sword.", 70));
         write("Your resolve to be a heroic, honourable, and generous Knight has firmed.\n");
         write(BS("You rise from your daily devotions, prepared for yet another day of " + 
               "fighting the forces of evil, and confident of Kiri-Jolith's blessing.", 70)); 
         say(QCTNAME(TP) + " prays to " + TP->query_possessive() + " patron for guidance.\n");      
         return 1; 
       }
      if (TP->query_knight_level() == 5)
         {
         write("You kneel at the altar and pray to Lord Paladine for guidance.\n");
         write("As you make your devotions, a sense of hope envelops you.\n");
         write(BS("You feel awed by the certainty that the wise and just presence " + 
               "in the room is that of Paladine, Patron of the Order of the Rose.", 70));
         write("Your resolve to be a just, honourable, and disciplined Knight has firmed.\n");
         write(BS("You rise from your daily devotions, prepared for yet another day of " + 
               "fighting the forces of evil, and confident of Paladine's blessing.", 70)); 
         say(QCTNAME(TP) + " prays to " + TP->query_possessive() + " patron for guidance.\n");      
         return 1; 
       }
   }
   return 0;
}


read(str)
{
   NF("Read what?\n");
   if ((str == "book") || (str =="prayerbook"))
      {
      write("This is the Prayerbook of the Knights of Solamnia.\n"
         + " You can <pray> at the altar as part of your daily\n"
         + " devotions to Paladine. All good Knights pay homage\n"
         + " to him on a regular basis.                        \n"
         + "                                                   \n"
         + " In addition, you can <pray patron>. This allows you\n"
         + " to seek the counsel of the Patron of your Order.\n\n");
      return 1;
   }   
   return 0;
}

int
do_enter(string str) 
{
   if (str!="alcove") return 0;
    if (MEMBER(TP))
      {
      write("There is just room enough for you to enter the alcove.\n");
      TP->move_living("into the alcove", ROOM + "alcove", 0);      
      return 1;
   }
   write("Only devoted knights may enter the alcove.\n");
   say(QCTNAME(TP) + " is unable to enter the alcove.\n");
   return 1;
}



int
check_member(object ob)
{
   NF("I don't think Paladine would let you meditate at his altar since\n" +
      "you are not a Knight.\n");
   return (MEMBER(ob) || LAYMAN(ob));
}

int
gs_meditate(string str)
{
   if (!check_member(TP))
      return 0;
   return ::gs_meditate(str);
}

void
gs_hook_start_meditating()
{
   write("" +
      "You kneel before the altar of Paladine and close your eyes.\n" +
      "A feeling of great ease and self control falls upon you.\n" +
      "You block of your senses and concentrate solely upon your\n" +
      "own mind. You feel Paladine with you and he gives you the\n" +
      "power to <estimate> your different stats and <set> the\n" +
      "learning preferences at your own desire. Just <rise> when\n" +
      "you are done meditating.\n");
}

int
gs_hook_rise()
{
   write("As if ascending from a great depth, you rise to the surface\n" +
      "of your consciousness. You exhale and feel very relaxed as\n" +
      "you get up and leave the altar.\n");
   say(QCTNAME(TP) + " rises from the altar.\n");
}



