// Kirk of Port City - Abbey Upper Level - Chapel
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 7/20/98     Zima        Recoded
//
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
inherit "/d/Khalakhor/std/room";
inherit  SR_ROOM+"kneelrm";
 
/* room definition */
void create_khalakhor_room() {
   set_short("Chapel of the Abbey");
   set_long(
      "   This is the chapel of the abbey, where the faithful come to "+
      "meditate on the mysteries of the order. A life-size statue of an "+
      "angel stands on a pedestal along the western wall, his wings "+
      "folded down behind him and his head bowed in reverence. "+
      "Small niches in the north, south and west walls house small "+
      "sculpted figures which encircle those who come here as a "+
      "congregation of watchful guardians. Candelabras are set in the "+
      "four corners of the chamber, filling it with a somber light, "+
      "their calmly burning candles adding to the aura of peace and "+
      "harmony here.\n");
   INSIDE;
 
   add_item(({"candelabra","candelabrum","candelabras","candles"}),
      "The ornate candelabras stand in the four corners of the chapel, "+
      "made of gold and ornately crafted with elegant twists and curves "+
      "which branch out from a tall central staff. Dozens of thick white "+
      "candles burn calmly in the holders of each, filling the chapel "+
      "with light and an aura of meditation.\n");
 
   add_item(({"chapel","chamber"}),
      "It is a meditation chapel, ornately decorated with candelabras "+
      "and statues and candelabras.\n");
 
   add_item(({"niche","niches","statues","figures","sculpted figures"}),
      "There are nine niches in the walls of the chapel, three each "+
      "on the north, south and west walls. In each stands a small "+
      "statue or figurine, which looks out prayerfully over the chapel. "+
      "You could look at each one individually, the first through the "+
      "ninth.\n");
 
   add_item(({"angel","statue"}),
      "A life-size statue of an angel stands atop a pedestal which sits "+
      "along the western wall, his wings folded neatly behind him, his "+
      "head bowed and eyes closed reverently, his arms folded around a "+
      "large trumpet.\n");
 
   add_item(({"pedestal","inscription"}),
      "The angel stands on a pedestal, a simply sculpted cube of stone "+
      "with smooth sides. An inscription on the face of the pedestal "+
      "reads: MAIGHAL THE ARCHANGEL OF ARDAUGH.\n");
 
   add_item(({"first niche","first statue","first figure",
      "figure of seanchan tor","statue of seanchan tor"}),
      "The first niche is the left of three on the south wall. "+
      "It contains a small sculpted figure of tall thin elf in a long "+
      "robe and thick belt. He wears a tight cap with straps that hang "+
      "down from his ears, and has a long writhing mustache and goatee. "+
      "He stares pensively into a crystal he hold with both hands.\n");
 
   add_item(({"second niche","second statue","second figure",
      "figure of rhiannon","statue of rhiannon"}),
      "The second niche is the center of three on the south wall. "+
      "It contains a small sculpted figure of a female elf in a long "+
      "flowing dress and cape, wearing a tiara. Her hands are held "+
      "together prayerfully and a dove is perched on her shoulder.\n");
 
   add_item(({"third niche","third statue","third figure",
      "figure of irgalach","statue of irgalach"}),
      "The third niche is the right of three on the south wall. "+
      "It contains a small sculpted figure of a muscular elf in a short "+
      "tunic, leaning on the hilt of a down-pointed sword. His foot "+
      "stands atop a crushed helmet.\n");
 
   add_item(({"fourth niche","fourth statue","fourth figure",
      "figure of kesair","statue of kesair"}),
      "The fourth niche is the left of three on the west wall. "+
      "It contains a small sculpted figure of a female elf "+
      "with long curly locks, wearing an elegant gown, holding a mortar "+
      "in her hands. Her head is bowed and her eyes closed.\n");
 
   add_item(({"fifth niche","fifth statue","fifth figure",
      "figure of camulos","statue of camulos"}),
      "The fifth niche is the center of three on the west wall, directly "+
      "behind and slightly above the angel. "+
      "It contains a small sculpted figure of a male elf dressed as a "+
      "traveler with a long mantle. He holds an ornate staff in his "+
      "left hand, his right over his heart with his head bowed "+
      "prayerfully.\n");
 
   add_item(({"sixth niche","sixth statue","sixth figure",
      "figure of ambisargus","statue of ambisargus"}),
      "The sixth niche is the right of three on the west wall. "+
      "It contains a small sculpted figure of a male elf garbed in a loose "+
      "robe with his bowed head cowled. He holds a book over his heart "+
      "with one hand while the other is slightly upheld holding an orb.\n");
 
   add_item(({"seventh niche","seventh statue","seventh figure",
      "figure of argante","statue of argante"}),
      "The seventh niche is the left of three on the north wall. "+
      "It contains a small sculpted figure of a female elf "+
      "garbed in a loose belted robe with its cowl thrown back, a fial "+
      "liann on her forehead. Two grotesque sharp-nailed toes peep from "+
      "beneath her robe.\n");
 
   add_item(({"eighth niche","eighth statue","eighth figure",
      "figure of sechnasach","statue of sechnasach"}),
      "The eighth niche is the center of three on the north wall. "+
      "It contains a small sculpted figure of a male elf "+
      "dressed in a short belted tunic and holding an ornate hammer. "+
      "His head is bowed and his eyes closed.\n");
 
   add_item(({"ninth niche","ninth statue","ninth figure",
      "figure of ragallach","statue of ragallach"}),
      "The ninth niche is the right of three on the north wall. "+
      "It contains a small sculpted figure of a young male "+
      "elf in the dress of ancient nobility, holding a lamp with a large "+
      "flame in one hand. He seems to be kissing his other hand fisted "+
      "before his bowed face.\n");
 
 
   add_exit("ucorr5","east","@@check_kneeling");
   (clone_object(SR_OBJ+"covaltar"))->move(TO);
}
 
int do_meditate()
{
   if (kneeling(TP))
      {
      write("You meditate upon the mysteries of the universe.\n");
      tell_room(TO,QCTNAME(TP)+" meditates quietly.\n",TP);
      }
   else
      write("You should probably kneel first.\n");
   return 1;
}
 
public void init()
{
   ::init();
   add_action(&do_meditate(), "meditate");
}
