// base room for kirk sanctuary
#include "defs.h"
inherit  "/d/Khalakhor/std/room";
inherit  SR_ROOM+"kneelrm";
 
#include "/d/Khalakhor/guilds/sean-rhian/lib/kwin.h";
 
#define  MAX_MANACHS 3
 
public  object  *manach=allocate(MAX_MANACHS);
public  int     num_manachs=0;
public  string  extra="";
public  string  *wd=WINDESC;
 
void make_manach(int i)
{
   if ((i>=MAX_MANACHS)||(manach[i])) return;
   manach[i]=clone_object(SR_NPC+"kmonk");
   manach[i]->equip_me();
   manach[i]->move(TO);
   manach[i]->set_wander(ROOM, MASTER_OB(TO), 60);
   tell_room(TO,QCNAME(manach[i])+" arrives.\n");
}
 
void reset_room()
{
   int i;
   for (i=0; i<num_manachs; i++)
      make_manach(i);
}
 
void create_ksanct()
{
   set_short("in the village kirk");
   set_long(
      "You are in the small kirk of the village. Made of tall wood "+
      "planks which reach vertically from the floor to the ceiling, "+
      "the sanctuary is in the shape of an arch with its base along "+
      "the south side. Nine stained glass windows adorn the arching "+
      "wall along the west, north and south sides, filling the "+
      "kirk with vibrant colors, while a statue stands atop a perch "+
      "on the north end above the central window. Two tapestries hang "+
      "on either side of the entrance to the south, while a large "+
      "candelier hangs from the ceiling filled with candles adding "+
      "their somber light. "+extra+"\n");
 
   // architectural descriptions
   add_item("floor",
      "The floor of the kirk is made of the same stained wood planks "+
      "as the walls and ceiling, so well waxed they gleam with the "+
      "light from the windows and the chandelier.\n");
   add_item(({"room","kirk","sanctuary"}),
      "The sanctuary of the kirk is constructed in the form of an "+
      "arch, with a flat base wall along the south and an arching "+
      "wall curving from the west to the north to the east. It is "+
      "constructed of wood planks like the other buildings of the "+
      "village, except they are stained a natural color instead of "+
      "being painted in pastel. Nine stained glass windows adorn "+
      "the arching wall of the kirk.\n");
   add_item("ceiling",
      "The ceiling of the kirk is in the form of a semi-dome which "+
      "fits over the arch-shaped sanctuary. Made of long wood planks "+
      "which are expertly water-bent and cut to points to form the "+
      "dome, they converge to a center point above the altar. A "+
      "chandelier hangs from the point.\n");
   add_item(({"wall","walls"}),
      "The kirk really has only two walls, one flat to the south and "+
      "another which curves in an arch from the west to the east "+
      "along the north side. Unlike the other buildings of the village, "+
      "the wooden walls are unpainted, and instead are stained leaving "+
      "the natural wood color. Nine stained glass windows adorn the "+
      "arching wall.\n");
 
   // misc. object descriptions
   add_item(({"chandelier","candles"}),
      "There is a large multi-branched chandelier hanging from "+
      "the ceiling over the altar, its branches filled with dozens "+
      "of white candles. Their flames burn quietly adding their "+
      "somber light to the sanctuary.\n");
   add_item("altar",
      "You could get a better look by walking over to it.\n");
 
   // south wall (tapestry) descriptions
   add_item("tapestries",
      "There are two tapestries hanging on the south wall, one on "+
      "either side of the entrance.\n");
   add_item("entrance",
      "Marked by thick beams, the entrance is in the center of the "+
      "south wall, flanked by two large tapestries.\n");
 
   // window descriptions
   add_item("windows",
      "There are nine stained glass windows set in the arching wall "+
      "lining the sanctuary from the east to the west. The fifth "+
      "window is directly north, flanked by four on each side. You "+
      "may look specifically at each, the first through the ninth.\n");
   add_item(({"first window","second window","third window",
      "second tapestry","right tapestry"}),
      "You could get a better look if you were closer, in the "+
      "southwest corner of the sanctuary.\n");
   add_item(({"fourth window","fifth window","sixth window","statue"}),
      "You could get a better look if you were closer, in the "+
      "north apex of the sanctuary.\n");
   add_item(({"seventh window","eighth window","ninth window",
      "first tapestry","left tapestry"}),
      "You could get a better look if you were closer, in the "+
      "southeast corner of the sanctuary.\n");
}
 
void create_khalakhor_room()
{
   create_ksanct();
}
