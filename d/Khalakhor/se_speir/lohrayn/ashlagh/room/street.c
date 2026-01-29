// Base room for street and other outside rooms in the village
//
// Date    Coder       Action
// ------- ----------- ----------------------------------------
// 6/9/98  Zima        Created
//
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
string extra="";
object guard=allocate(2);
 
void make_guards()
{
   int i;
   seteuid(getuid());
   for (i=0; i<2; i++)
      if (!objectp(guard[i]))
         {
         guard[i] = clone_object(NPC+"guard");
         guard[i]->equip_me();
         guard[i]->set_monster_home(MASTER); // setup in case room wants it
         guard[i]->set_restrain_path(ROOM);  // guards do not auto-waner
         guard[i]->move(TO);
         tell_room(TO,QCNAME(guard[i])+" arrives and takes his post.\n");
         }
}
 
 
public void add_std_items()
{
   add_item(({"town","village"}),
      "The village consists of small houses and other buildings made "+
      "of wood and painted in pastel colors. Flowers lining the streets "+
      "add scent as well as decor to the quaint village. The town "+
      "is protected by a stone wall which encircles it.\n");
   add_item(({"cobbestone","street"}),
      "The street is paved with light brown cobblestones, "+
      "neatly placed and smooth, not one ajar or cracked. It is "+
      "lined with colorful flowers which are planted between the "+
      "street and the buildings. You believe the villagers must "+
      "spend alot of time and money on keeping the street in such "+
      "good shape.\n");
   add_item(({"houses","homes","buildings"}),
      "All the houses and buildings of the village are constructed "+
      "in the same style, so similar you can't tell a home from a "+
      "pub by the architecture. They are made of wood, their "+
      "walls covered in flat panels painted in pastel blues, pinks "+
      "and yellows. Long dark brown beams frame the walls, each with "+
      "two large beams crossing their front in an 'X' pattern, two on "+
      "either sides of their entrances. They have steep "+
      "roofs which are shingled with bright red wooden slats. Flowers "+
      "have been planted along the edges of the buildings to further "+
      "decorate them. They make the village look very neat and quaint.\n");
   add_item(({"flowers","flowerbed","flowerbeds"}),
      "Flowerbeds have been dug out along the base of the walls "+
      "of all the houses, bordering the street with color and "+
      "scent. You figure there are many talented gardeners in this "+
      "small place.\n");
   add_item("wall",
      "The high stone wall encircles the little village, made of "+
      "boulders and large rocks piled a little over head high. The "+
      "wall looks like it has withstood many onslaughts over many "+
      "years, as it looks much newer than the buildings of the village.\n");
   add_cmd_item(({"flowers","flower","blossom","blossoms"}),
      ({"take","get","pick","pluck"}),
      "You wouldn't dare do that! Around here you would get arrested!\n");
   add_cmd_item(({"flowers","flower"}),({"smell","sniff"}),
      "You sniff the flowers lining the street and your nostrils "+
      "are filled with their perfumed scent.\n");
}
 
public void create_court(string sdir)
{
   set_short("In a courtyard of a quaint village");
   set_long( "This is one of the quiet courtyards of the village "+
             "around which three buildings are situated. The yard "+
             "is covered in short green grass and bordered "+
             "like the street with flowerbeds. There are entrances "+
             "to the three homes or buildings here, while the "+
             "street is just to the "+sdir+". " + extra + "\n");
 
   add_item(({"courtyard","yard"}),
      "The courtyard serves as a quiet square around which the "+
      "three buildings are situated. It is covered with short "+
      "well-kept green grass and bordered by colorful flowerbeds.\n");
   add_item("grass",
      "It is just regular grass, but well groomed and watered. You "+
      "see no weeds or patches of bare ground anywhere.\n");
   add_std_items();
}
 
public void create_common()
{
   set_short("On the commons of a quaint village");
   set_long("You are on the central commons of the quaint little "+
            "village, where the street forms a large square in the "+
            "center of town, framing a grass covered greens area "+
            "in the middle. The pastel colored houses and other "+
            "buildings are situated neatly around the commons with "+
            "their flowerbeds blooming with color, though you notice "+
            "no buildings have an entrance leading directly onto "+
            "the street. The sun shines brightly on the town square, "+
            "with only a few thin gray clouds in the air. "+extra+"\n");
   add_item(({"commons","square"}),
      "The commons is just a grass-covered square in the center of "+
      "town, probably a gathering place for important events which "+
      "might occur in the little village.\n");
   add_std_items();
}
 
public void create_street()
{
   set_short("On a street in a quaint village");
   set_long("You are on a cobblestone street which runs through a "+
            "quaint little village. The small houses and other "+
            "buildings of the village which line the street are made "+
            "of wood painted in pastel colors. Flowerbeds brimming "+
            "with blossoms of various colors border the houses, "+
            "outlining the street with color and scent. "+extra+"\n");
   add_std_items();
}
 
 
public void create_khalakhor_room()
{
   create_street();
}
