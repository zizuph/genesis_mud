#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_IN;
 
object priest;

void 
reset_mithas_room()
{
   if(!objectp(priest))
    {
        priest = clone_object(MNPC + "highPriest");
        priest -> move(this_object());
    }
}

void
create_mithas_room()
{
   set_short("Inner Sanctum");
   set_long("@@long_descr"); 

  add_item(({"walls", "blood-red"}),"As you examine the "+
              "walls closer you notice that it might not "+
              "be the stones that's red, perhaps "+
              "some liquid once colored it...\n");
 
  add_item(({"floor", "obsidian"}),"The floor is made "+
              "out of small square obsidian stones. The "+
              "stones has been polished making it very "+
              "smoothe and soft to walk on. The furrow's "+
              "between the stones are filled with a "+
              "hardened black substance.\n");

  add_item(({"substance", "blood"}),"The substance "+
              "has been dried, it looks like someone "+
              "was trying to remove it. As you study "+
              "it closer you get the feeling that this "+
              "might be blood.\n");

  add_item(({"altar", "warrior"}),"This beautiful "+
              "altar has been carved so that it looks "+
              "like a great minotaur warrior wielding "+
              "a huge golden axe. The eyes of the "+
              "minotaur is made out of red gemstones, "+
              "perhaps rubies. This must an altar "+
              "devoted to the God Sargonnas. He is "+
              "known as the god of vengeance, rage, "+
              "deserts, and volcanoes. Takhisis, his "+
              "greatest ally, but sometimes also his "+
              "greatest enemy, the only thing he cares "+
              "about is his own personally gain. "+
              "Suddenly an invisible "+
              "force throws you on the ground!\n"+
              "You fall to the ground in front of the "+
              "minotaur statue, groveling.\n");

   set_tell_time(100);
   add_tell(({
       "You breathe in the sweet smell of the incense.\n",
       "The glow from the walls covers everything in a "+
       "reddish color.\n",
       "You hear slow chanting from somewhere nearby.\n", }));  

   add_exit(MROOM + "temple4","southeast",0); 
   add_exit(MROOM + "temple3","southwest", 0); 
   reset_mithas_room();
}

string
long_descr()
{ 
   return "You are standing in the inner Sanctum in the "+
          "Temple of the Stars in Nethosak. You have never "+
          "seen anything more beautiful then this great "+
          "room. The walls are made out of some "+
          "unknown blood-red stone, casting a red glow "+
          "on everything here. The floor is made out of "+
          "small square blocks of black obsidian and the "+
          "great ceiling forms an arch high above you. "+
          "In the center of the room, a spledid altar "+
          "has been placed, it has the shape of a "+
          "minotaur warrior and it is made out of solid "+
          "gold. Four braziers have been put here, one "+
          "to represent each corner of the world. There's "+
          "a pleasent small of incense here.\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}

