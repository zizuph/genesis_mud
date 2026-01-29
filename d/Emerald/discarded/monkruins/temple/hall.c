inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
int talk=0;
int i=0;
void talker1();
 
object par,thp;
 
string *talk1 = ({"You feel yourself beginning to drift off into sleep...\n",
      "A strange shape appears inside your mind...\n",
      "The shape transforms into image of God...\n",
      "God sits down at the air and smiles at you.\n",
      "God says: Hello!\n",
      "God says: I'm God, God of the Doomed!\n",
      "God says: It's nice to see a new monk in my temple...\n",
      "God suddenly stops speaking, and looks at you.\n",
      "God asks: Hey, you don't want to be a monk, " +
      "do you?\n",
      "God goes hmmmm.\n",
      "God looks at you suspiciously.\n",
      "God asks: Then why did you call me?!\n",
      "God stretches his tired body.\n",
      "God says: I'm a very busy person, you know.\n",
      "God looks at you again, his eyes glow briefly.\n",
      "God goes ahhh.\n",
      "God says: You are looking for abbot's ring?\n",
      "God smiles happily.\n",
      "God says: Ok, I'll help you. I like him.\n",
      "God closes his eyes and concentrates for a " +
      "moment.\n",
      "God opens his eyes and says: Oops, wrong ring.\n",
      "God blushes profusely.\n",
      "God ponders the situation.\n",
      "God closes his eyes and concentrates for a moment.\n",
      "God says: Ahh, a thief took that ring.\n",
      "God says: Are you happy now?\n",
      "God smiles hopefully.\n",
      "You shake your head in disagreement.\n",
      "You say: Where is that ring now then?\n",
      "God scratches his head.\n",
      "God closes his eyes and concentrates for a moment.\n",
      "God open his eyes and says: I have no more mana, I'm sorry.\n",
      "God sighs deeply.\n",
      "God looks at you with a greedy glint in his eyes.\n",
      "God says: You don't mind if I use your mana, do you?\n",
      "God closes his eyes and concentrates for a moment.\n",
      "You feel yourself being mentally drained.\n",
      "God opens his eyes and smiles confusedly.\n",
      "God says: I'm afraid I cannot tell you much.\n",
      "God says: All I could see was a symbol of Earth.\n",
      "God says: I cannot help you anymore with it, sorry.\n",
      "God begs your pardon.\n",
      "You say: No problem.\n",
      "God smiles happily.\n",
      "God thanks you gratefully.\n",
      "God thinks hard about how he can help more.\n",
      "God thinks about it, then it dawns on him...\n " +
      "His face brightens.\n",
      "God says: Maybe you want to know where is something " +
      "that can help you to retrieve that ring?\n",
      "God says: I can make it too.\n",
      "God smiles proudly.\n",
      "God closes his eyes and concentrates for a moment.\n",
      "You feel yourself mentally drained.\n",
      "You growl menacingly.\n",
      "God opens his eyes and looks at you for a long time.\n" +
      "He seems surprised.\n",
      "God says: I said that I would need your mana, didn't I?\n",
      "You make some menacing movements at him.\n",
      "God chirps: Calm down, calm down.\n",
      "God chirps: I can tell you something about that thing.\n",
      "You ask: What thing?\n",
      "God says: The one which can help you to retrieve that ring.\n",
      "God says: It's somehow linked to the water...\n",
      "You say: And?\n",
      "God sighs sadly.\n",
      "God says: That's all. To tell the truth, I'm not very " +
      "powerful god.\n",
      "God sighs wistfully.\n",
      "God says: Wait a few thousand centuries, you'll see that " +
      "I become the God of Gods, The One, The ...\n"});
 
void create_room()
{
   object altar;
 
   add_prop(ROOM_I_INSIDE, 1);
   set_short("Temple of the Doomed");
   set_long("   You have entered the Temple of the Doomed. "+
            "You find yourself standing in the wonderous altar room. "+
            "Never before have you been filled with such a feeling of "+
            "anxiety and anticipation. You can hear a constant drone "+
            "coming from somewhere around. You assume it is the humming " +
            "of the monks, but you really don't see any here.\n\n");
 
   add_exit(TEMPLE_DIR + "entrance", "west", 0);
   add_exit(TEMPLE_DIR + "hallway_n", "north", 0);
   add_exit(TEMPLE_DIR + "hallway_s", "south", 0);
   altar=clone_object(TEMPLE_DIR + "doors/trapdoor_a");
   altar->move(this_object());
}
 
void
init()
{
   ::init();
   add_action("do_pray","pray");
}
 
int
do_pray(string str)
{
   notify_fail("Pray where?\n");
   if(!str) return 0;
   if(!parse_command(str, TP, "'at' 'altar'"))
      {
      return 0;
   }
   if ((TP->query_prop("_ring_quest_")==1) &&
         (TP->query_prop("_met_with_god_")!=1) &&
      (TP->query_mana()>TP->query_max_mana()/3) && (talk==0))
   {
      talk=1;
      par=clone_object("/std/paralyze");
      par->set_stop_verb();
      par->set_fail_message("You cannot do something now, you are " +
         "sleeping.\n");
      par->move(TP);
      write("You kneel down and begin to pray.\n");
      say(QCTNAME(TP) + " kneels down and begins to pray.\n");
      write("You feel the powerful touch of someone's mind.\n");
      TP->add_mana(-TP->query_max_mana()/3);
      write("You feel yourself mentally drained.\n");
      i=0;
      thp=TP;
      set_alarm(1.0, 0.0, talker1);
      return 1;
   }
   else {
      write("You kneel down for a while to pray, you feel much better.\n");
      tell_room(TO, QCTNAME(this_player())+" kneels down and "+
         "prays.\n", TP);
      return 1; }
}
 
void
talker1()
{
  object player;
 
   player=thp;
   player->catch_msg(talk1[i]);
   i++;
   if ((i==33) || (i==45) || (i==66))
      {
      if ((player->query_mana()<player->query_max_mana()/3) || (i==66))
         {
         write("God says: I have to go, another monk " +
            "prays for my help.\n");
         write("God sighs tiredly and waves to you.\n");
         write("You feel you awaken from the dream.\n");
         write("You end your praying and stand up.\n");
         say(QCTNAME(TP) + " stands up.\n");
         talk=0;
         TP->add_prop("_met_with_god_",1);
         par->remove_object();
         return;
       }
      player->add_mana(-player->query_max_mana()/3);
   }
   thp=player;
   set_alarm(2.0,0.0,talker1);
}
