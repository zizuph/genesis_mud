/*                                   */
/*    Part of the Market in Kalad.   */
/*                                   */
/*              -Rico 20.12.94       */
/*                                   */

#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>

inherit MRKT_PATH(marketStd);

object ob1;
object ob2;

create_room()
{
   ::create_room();
   
   set_short("\n" + "In the Market");
   set_long("\n"+
      "    You are in the Market. The ground here "+
      "is incredibly muddy and your feet make sucking "+
      "noises as you walk. All around you there are "+
      "colorful tents and people caught up in the "+
      "excitement of the market atmosphere. "+
      "\n\n"+
      "    To the west is brightly colored tent. It has "+
      "words painted above the door which you can easilly "+
      "read from here. To the southwest you can see a "+
      "wagon. "+
      "\n\n");
   
   add_item(({ "brightly colored tent", "tent" }), "\n"+
      "This tent is made of brightly colored, almost "+
      "glowing material. There are many people of all "+
      "classes gathered around it and going in and out "+
      "of it. There are brightly colored words painted "+
      "over the doorway. "+
      "\n\n");
   add_item(({ "words", "painted words" }), "\n"+
      "You think you can easilly read what they say. "+
      "\n\n");
   add_item(({ "wagon", "southwest" }), "\n"+
      "You can't really get a very good look at it "+
      "from this angle. It does look like it might be "+
      "a good place to hide under, though. "+
      "\n\n");
   add_item(({ "tents", "colorful tents" }), "\n"+
      "These are very colorful tents. An unusual "+
      "contrast to the everyday dreary atmosphere "+
      "of the land. You are amazed that the the tents "+
      "aren't completely covered in mud. Their bright "+
      "us still obvious. It appears that most of the "+
      "tents are shops of some kind. "+
      "\n\n");
   add_item(({ "people", "crowd" }), "\n"+
      "The market place is packed with people of "+
      "all descriptions and races. There are so "+
      "many people constantly bumping into you "+
      "that you think you should probably keep "+
      "a firm grasp upon your purse... Unless "+
      "you don't mind losing it of course. "+
      "\n\n");
   
   set_time_desc("    The crowds are tightly packed right "+
      "now. You feel somewhat claustrophobic in these "+
      "tight confines.\n\n", "    Considering the time of "+
      "day, there are still a large number of "+
      "people milling about. Must have something "+
      "to do with the fact that the Market is the "+
      "center of activity around these parts. "+
      "\n\n");
   
   set_alarm(50.0, 0.0, "room_events");
   set_alarm(1.0, 0.0, "reset_room");
   
   add_exit(MRKT_PATH(casino01), "west");
   add_exit(MRKT_PATH(m14), "southeast");
   add_exit(MRKT_PATH(m15), "southwest");
   add_exit(MRKT_PATH(m21), "north");
}

reset_room()
{
   if(!present("wagon", TO))
      {
      clone_object(MRKT_PATH(obj/wagon))->move(TO);
   }
   if(!ob1)
      {
      ob1 = clone_object(MRKT_PATH(npc/mguard1));
      ob1 -> move_living("xxx", TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(MRKT_PATH(npc/mguard2));
      ob2 -> move_living("xxx", TO);
      ob2 -> team_join(ob1);
   }
}

void
init()
{
   ::init();
   
   add_action("read", "read");
   return;
}

int
read(string str)
{
   if((str=="wording")||(str=="painted words"))
      {
      write("The wording says:\n\n"+
         "         'Lucky Key Casino'\n\n");
      say(QCTNAME(this_player()) + " studies the "+
         "wording on the brightly colored tent to "+
         "the west.\n");
      return 1;
   }
   write("Read what? The wording?\n");
   return 1;
}

room_events()
{
   switch(random(28))
   {
      case 0:
      tell_room(TO, "A dirt-laden stranger brushes up against "+
         "you, leaving a smudge on your armour. "+
         "\n");
      break;
      
      case 1:
      tell_room(TO, "A cloaked group of wanderers arrives, shuffles "+
         "past you. You get an errie feeling from them. "+
         "\n");
      break;
      
      case 2:
      tell_room(TO, "The sound of the bell is muffled as a female "+
         "hobbit screams out in terror from somewhere nearby. "+
         "\n");
      break;
      
      case 3: 
      tell_room(TO, "A small thief arrives and quickly departs, "+
         "giving furtive glances behind him. "+
         "\n");
      break;
      
      case 4:
      tell_room(TO, "A burly warrior arrives and studies the "+
         "nearest tent, obviously searching for something. "+
         "After a few moments he leaves to search elsewhere. "+
         "\n");
      break;
      
      case 5:
      tell_room(TO, "A small thief arrives and quickly scampers "+
         "around the side of a tent, obviously hiding from someone. "+
         "\n");
      break;
      
      case 6:
      tell_room(TO, "A burly warrior pauses as he passes by you "+
         "and gives you an intense stare. You feel as though he "+
         "looking right into your very soul. "+
         ".\n");
      break;
      
      case 7:
      tell_room(TO, "A fat jolly man waddles in, glances at you "+
         "knowingly and carries on with his errand. "+
         "\n");
      break;
      
      case 8:
      tell_room(TO, "A mysterious robed figure appears, glances at "+
         "a nearby posting and leaves south. "+
         "\n");
      break;
      
      case 9:
      tell_room(TO, "The murmur of a crowd reaches your ears. "+
         "\n");
      break;
      
      case 10:
      tell_room(TO, "A youthful dwarf arrives peering around in "+
         "search of a companion. "+
         "\n");
      break;
      
      case 11:
      tell_room(TO, "A shiftless gnome sidles past you. "+
         "\n");
      break;
      
      case 12:
      tell_room(TO, "A hooded stranger bumps into you on his way "+
         "to one of the colorful tents. "+
         "\n");
      break;
      
      case 13:
      tell_room(TO, "A small brown rat starts chewing on your foot, "+
         "then hurriedly departs. "+
         "\n");
      break;
      
      case 14:
      tell_room(TO, "An elegantly dressed woman passes you on her "+
         "way to the gem shop. "+
         "\n");
      break;
      
      case 15:
      tell_room(TO, "A road-weary merchant arrives and leans upon "+
         "his staff for a moment before leaving. "+
         "\n");
      break;
      
      case 16:
      tell_room(TO, "A scream sounds from the south. "+
         "\n");
      break;
      
      case 17:
      tell_room(TO, "A dirty-looking dog arrives and begins sniffing "+
         "you. It leaves before you can get a look at it. "+
         "\n");
      break;
      
      case 18: 
      tell_room(TO, "A thief whisks past you with a small mob in close "+
         "pursuit! "+
         "\n");
      break;
      
      case 19:
      tell_room(TO, "A dark-skinned figure brushes past you. "+
         "\n");
      break;
      
      case 20:
      tell_room(TO, "A drunken guard arrives and stumbles into a "+
         "beautiful maiden. He is rewarded with a slap on the face! "+
         "\n");
      break;
      
      case 21:
      tell_room(TO, "The constant murmer of the crowd is beginning "+
         "to give you a headache. "+
         "\n");
      break;
      
      case 22:
      tell_room(TO, "You get jostled by a sudden surge in the crowd "+
         "and almost lose your balance. As you glare at the crowd "+
         "you can see that the cause is a trussed up barbarian being "+
         "dragged away by the market guards. "+
         "\n");
      break;
      
      case 23:
      tell_room(TO, "You begin to get thirsty trudging your way "+
         "through the mud and slime which is sucking at your feet. "+
         "\n");
      break;
      
      case 24:
      tell_room(TO, "As you pass by a dark alleyway you can hear "+
         "a muffled sob. You are unable to penetrate the darkness "+
         "of the alley to see the cause, though. You decide not "+
         "investigater further as it is probably an ambush set "+
         "by some foul hearted cut throats seeking easy prey. "+
         "\n");
      break;
      
      case 25:
      tell_room(TO, "A mud caked ruffian crawls out from under the "+
         "wagon and quickly vanishes into the crowd to the north. "+
         "\n");
      break;
      
      case 26:
      tell_room(TO, "A young boy in a colorful costume calls to you "+
         "from in front of the casino, inviting inside to try your "+
         "luck. "+
         "\n");
      break;
      
      case 27:
      tell_room(TO, "A wealthy looking man storms out of the casino "+
         "cursing loudly at anyone who happens to glance his way. "+
         "He has obviously hit a streak of poor luck. "+
         "\n");
      break;
   }
   set_alarm(50.0, 0.0, "room_events");
}

