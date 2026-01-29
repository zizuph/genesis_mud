/*
 * Made by Korat
 * may 1996
 *
*/
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object prisoner;
object rat1;
object rat2;
object rat3;

create_room()
{
   ::create_room();
   set_short("dwarven Citadel");
   set_long("You are inside an ancient citadel, long abandoned "+
      "by their masters and makers, the deep dwarves. "+
      "Even though the citadel has clear marks of decay from "+
      "the centuries of abandonment, the masonry is of such "+
      "quality that you still have problems finding the "+
      "cracks inbetween the stoneblocks. This room looks to "+
      "be a desolated place. You wonder why, since everywhere "+
      "else you have met those brigands roaming around. "+
      "You see two exits, one to the east and one northeast into "+
      "what looks like two more rooms hidden "+
      "in a veil of darkness.\n");

   add_item(({"cobweb","web","silky network","silky web"}),
      "They are woven, silky networks spun by spiders through "+
      "time. All of them look to be abandoned by their creators, "+
      "much like the citadel itself; left alone to slowly be "+
      "grinned down by the sand carried along with the wind.\n");
   add_item(({"ceiling","roof"}),
      "The ceiling looks to be made by "+
      "brilliant craftsmen. This citadel was made to last ... "+
      "for thousands of years.\n");
   add_item("floor","The floor is covered with fine-grained, white "+
      "sand that must have been carried in here with the wind from the "+
      "great Kaladian waste.\n");
   add_item("citadel","The citadel you are inside is a masterpiece "+
      "of construction. Time has managed to mark it with signs of age, "+
      "but that only mystifies it more than its centuries of abandonment "+
      "manages to do alone.\n");
   add_item(({"wall","walls"}),"The walls are of a darker shade than "+
      "you have seen before. Along one of them you see a stone-block "+
      "that must have been here since the creation of this citadel.\n");
   add_item(({"block","stoneblock","stone-block","altar"}),
      "One of the stone-blocks looks almost like an altar. You see some fading runes "+
      "inscribed on it.\n");
   add_item("runes","The runes are ancient. You only manage to dechiper "+
      "one word that has not faded through time as the other runes: "+
      "RHOXVAN.\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description");
   add_prop(ROOM_I_LIGHT,0);
   INSIDE;

   add_exit(CPASS(citadel/level2/b1),"northeast","@@arch",-1);
   add_exit(CPASS(citadel/level2/b5),"east","@@arch",-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!objectp(prisoner))
   {
      prisoner=clone_object("/d/Kalad/common/wild/pass/citadel/npc/girlprisoner");
      prisoner->move_living("M",TO);
      prisoner->command("emote stares at you in utter fright, and "+
         "crawls closer to a larger stone-block in the corner.");
   }
   if (!objectp(rat1))
   {
      rat1=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat1->move_living("M",TO);
   }
   if (!objectp(rat2))
   {
      rat2=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat2->move_living("M",TO);
   }
   if (!objectp(rat3))
   {
      rat3=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat3->move_living("M",TO);
      rat1->team_join(rat2);
      rat1->team_join(rat3);
   }
}

void
init()
{
   ::init();
   add_action("touch","touch");
   add_action("push","push");
   add_action("meditate","meditate");
}

void
touch(string str)
{
   if (str == "altar" || str == "stone")
   {
      TP->catch_msg("The altar feels cold to your hands. Nothing happens.\n");
      tell_room(TO,QCTNAME(TP)+" touches the altar.\n",TP);
      return;
   }
   if (str = "runes")
   {
      TP->catch_msg("The runes all feel just like engravings on a stone. "+
        "Except one word that stings your fingers with a strong heat.\n");
      tell_room(TO,QCTNAME(TP)+" touches the runes.\n",TP);
      return;
   }
   TP->catch_msg("Touch what?\n");
}

void
push(string str)
{
   if (str == "altar" || str == "stone")
   {
      TP->catch_msg("The altar does not move an inch. Nothing happens.\n");
      tell_room(TO,QCTNAME(TP)+" pushes the altar.\n",TP);
      return;
   }
   if (str = "runes")
   {
      TP->catch_msg("You push at the different runes. Nothing happens.\n");
      tell_room(TO,QCTNAME(TP)+" pushes on the runes.\n",TP);
      return;
   }
   TP->catch_msg("Push what?\n");
}

void
meditate(string str)
{
   if (str != "to rhoxvan" || str != "to Rhoxvan")
   {
      TP->catch_msg("Pray to whom?\n");
      return;
   }
   if (TP->query_alignment() < 0)
   {
      TP->catch_msg("You pray to Rhoxvan, but nothing happens.\n");
      tell_room(TO,QCTNAME(TP)+" starts to pray.\n",TP);
      return;
   }
   TP->catch_msg("You pray to Rhoxvan.\n");
   tell_room(TO,QCTNAME(TP)+" starts to pray.\n",TP);
   set_alarm(2.0,0.0,"return_pray",TP);
}

return_pray(object player)
{
   if (!present(TP,TO))
      return;

   TP->catch_msg("Suddenly you feel your prayers answered. "+
      "A warmth embraces your body and suddenly you realize "+
      "what the runes on the altar means:\n\n"+
      "   The statue of praise that demanded a curse.\n"+
      "   Thought of himself as master when he an apprentice was."+
      "   He formed me in stone but ruined my eye.\n"+
      "   His life shall be long until his deeds are redone.\n"+
      "   By a true master in heart.\n\n"+
      "   Only then will I come to salvage my kin.\n"+
      "   Go with my blessing and claim my return.\n\n"+
      "You feel a heat envelope your very soul.\n");
   TP->catch_msg("You also realize it still is to early for you to "+
      "claim Rhaxvans return. Come back later.\n");

/*      TP->add_prop("GOT_BLESSED_BY_RHAXVAN",1);  */

   return;
}

/* give a feeling of passing through an arc */
void
arch()
{
   TP->catch_msg("You walk through a low passage that arches around you.\n");
   return 0;
}

/* returns a random darkroom description */
dark_description()
{
   string desc;
   switch (random(5))
   {
      case 0:
         desc = "You find yourself inside utter darkness.\n";
         break;
      case 1:
         desc = "A weak and chilling wind is all breaks the darkness.\n";
         break;
      case 2:
         desc = "You think you hear some sounds in front of you, but "+
                "without vision you cannot know what it comes from.\n";
         break;
      case 3:
         desc = "A dark room that envelopes you like a cloak of death.\n";
         break;
      case 4:
         desc = "You touch the wall to make sure you walk in the right "+
                "direction.\n";
         break;
      default: break;
   }
   
   return desc;
}
