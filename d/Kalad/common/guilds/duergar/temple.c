inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/drow/guild/default.h"
create_room()
{ 
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A grand temple devoted to the Spider Queen, Lolth");
   set_long("A grand temple to the Spider Queen of the Drow, Lolth.\n"+
      "Myriad decorations of faerie fire dimly illuminate this nearly "+
      "cavernous enclosure within the giant stalactite. Obsidian braziers "+
      "line the walls of this circular chamber, their incense-filled smoke "+
      "filling the air with their intoxicating fragrance. A hideously-decorated "+
      "altar lies in the west, while a rune-encrusted obsidian table is in "+
      "the east. At the center of the room is a single, blood-red column of "+
      "light, which pierces the perfectly-sculptured floor and ceiling.\n"+
      "A plaque, writhed with red faerie fire is before you.\n");
   add_item(({"myriad decorations","decorations","decoration","faerie fire","fire"}),
      "Dozens of portraits depicting Lolth and the fanatical drow priestesses "+
      "that are extensions of her will here on the mortal plane.\n");
   add_item(({"obsidian braziers","braziers","brazier"}),
      "Tall stone structures used by the priestesses of Lolth to help "+
      "in the summoning of powerful creatures from the nether regions of "+
      "the immortal planes.\n");
   add_item(({"hideously-decorated altar","altar"}),
      "A massive altar of blackest obsidian that is completely covered in "+
      "blood so red, it appears as if it were some type of black slime "+
      "or ooze.\n");
   add_item(({"blood"}),
      "It seems fresh, for upon nearing the altar, the distinct odor "+
      "of blood, fresh blood is evident.\n");
   add_item(({"rune-encrusted obsidian table","rune-encrusted table","obsidian table","table"}),
      "A huge and relatively simply-constructed table that nevertheless "+
      "is covered with all manner of runes.\n");
   add_item(({"runes","rune"}),
      "They are unfamiliar to you.\n");
   add_item(({"blood-red column of light","blood-red light","light","column"}),
      "A five-foot wide beam of ruby-red light that lies at the center of "+
      "this room.\n");
   add_item(({"perfectly-sculptured floor","floor","perfectly-sculptured ceiling"}),
      "It is of such great quality that its surface appears like nothing "+
      "more than a still pool of blackened water.\n");
   add_item(({"red faerie fire"}),
      "Magical fire the color of blood.\n");
   add_item("plaque","Several glowing words have been written on it.\n");
   add_cmd_item("plaque","read",
      "Here you may worship Lolth and through her limitless power, be "+
      "transported into the depths of the Dark Dominion. Beware however, "+
      "for Lolth's will is whimsical, and you may find yourself in dire "+
      "straits.\n");
   add_prop(ROOM_M_NO_ATTACK,"Lolth forbids violence in her temple!\n");
   add_exit(CPASS(drow/guild/start),"up","@@msg",-1,-1);
   add_exit(CPASS(drow/guild/train),"down","@@msg",-1,-1);
   set_noshow_obvious(1);
}
msg()
{
   write("You step into the red light, and feel yourself grow lighter as "+
      "you are transported by the column.\n");
   say(QCTNAME(TP) + " steps into the red light, and seems to grow lighter "+
      "as " + TP->query_pronoun() + " is transported by the column.\n");
   return 0;
}
void
init()
{
   ::init();
   AA(worship,worship);
}
int
worship(string str)
{
   if(!str || str != "Lolth")
      {
      NF("What ?\n");
      return 0;
   }
   write("You collapse onto your knees and worship Lolth.\n");
   say(QCTNAME(TP) + " collapses onto " + TP->query_possessive() + " knees and worships Lolth.\n");
   set_alarm(3.0,0.0,"vision");
   return 1;
}
void
vision()
{
   int i;
   i = random(5);
   if(i < 1)
      {
      TP->catch_msg("You feel the power of Lolth transport you...\n");
      TP->move_living("X","/d/Kalad/common/wild/pass/underdark/falling");
      return;
   }
   else
      if(i < 2)
      {
      TP->catch_msg("You feel Lolth's power surge into you as you are whisked "+
         "away...\n");
      TP->move_living("X","/d/Kalad/common/wild/pass/underdark/u3");
      return;
   }
   else
      if(i < 3)
      {
      TP->catch_msg("All turns black as you feel the will of Lolth crash into you...\n");
      TP->move_living("X","/d/Kalad/common/wild/pass/underdark/u28");
      return;
   }
   else
      if(i < 4)
      {
      TP->catch_msg("You are momentarily blinded by the sudden power of Lolth...\n");
      TP->move_living("X","/d/Kalad/common/wild/pass/underdark/u43");
      return;
   }
   else
      TP->catch_msg("The sudden and complete power of Lolth almost overwhelms you...\n");
   TP->move_living("X","/d/Kalad/common/wild/pass/underdark/u19c");
   return;
}
