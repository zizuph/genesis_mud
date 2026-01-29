/*
 * BASE_SPHERE.c
 * This is the base inheritable file for the spheres which
 * contain the lost souls of the elven clerics for the Graveyard quest.
 * - Alaron October 2, 1996
 */

#include "../default.h"
#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/graveyard/gquest.h"

inherit "/std/object";

int snum;

void set_sphere_num(int i);
int query_sphere_num();

void
create_sphere()
{
  /* Define this function in the individual sphere objects. */

  set_sphere_num(1);
}

void
set_sphere_num(int i)
{
  snum = i;
}

int
query_sphere_num()
{
    return snum;
}

void
create_object()
{
    create_sphere();
  
    set_name("sphere");
    set_adj("blue");
    add_adj("glowing");
    add_adj(SHAPE_DESCS[snum]);    // so players can distinguish spheres.
    set_short("glowing blue sphere");

    add_name(SPHERE_UNIQUE_NAME);   // For identification by present() fun 

    set_long("This object is remarkable. The sphere is perfectly smooth "+
	     "and absolutely perfect in its shaping. Holding the object "+
	     "in your hands, you notice that the sphere seems to be "+
	     "radiating a dim blue glow. Examining it further, you notice "+
	     "that hidden within the reflection of the light around you is "+
	     "a strange shape.\n");

    add_item(({"shape", "strange shape", SHAPE_DESCS[snum]+" shape"}),
	     VBFC_ME("examine_shape"));

    add_item(({"glow", "dim blue glow", "blue glow"}),
	     "The glow radiating from the sphere mystifies you. You know "+
	     "that it is coming from within the sphere, yet you can find "+
	     "no latches, handles, openings or cracks through which you "+
	     "might discover the source of the light. The sphere feels "+
	     "slightly warm to the touch.\n");
}

string
examine_shape()
{
  return "Remarkably well concealed within the reflection of the light "+
    "of your surroundings, you can see a shape that appears to be floating "+
     "in the center of the blue sphere. The shape is a "+SHAPE_DESCS[snum]+
    ".\n";
}

init()
{
  ::init();

  // Add a couple of commands here to make it interesting, but
  // nothing terribly useful.
  // The fact that this item has such functions may lead players
  // to think that this item is important. 

  add_action("rub_sphere", "rub");
  add_action("polish_sphere", "polish");
  add_action("kiss_sphere", "kiss");    // to dissapoint the gem users <g>
}

int
rub_sphere(string str)
{
     notify_fail("Rub what?\n");
     
     if (!str) return 0;
     if( (str != "sphere") && (str != "blue sphere") )
       return 0;
     
     write("You rub the sphere. Nothing happens.\n");
     return 1;
}

int
kiss_sphere(string str)
{
    notify_fail("Kiss what?\n");

    if (!str) return 0;
    if ( (str!="sphere") && (str!="blue sphere") ) 
      return 0;

    write("You kiss the the sphere. When nothing happens, you feel quite "+
	  "silly for having kissed a blue ball.\n");

    say(QCTNAME(TP)+ " kisses the blue sphere. When nothing happens, "+
	TP->query_possessive()+ " face turns quite red in embarrassment.\n");

    return 1;
}

int
polish_sphere(string str)
{
    notify_fail("Polish what?\n");
    
    if (!str) return 0;
    if( (str!="sphere") && (str!="blue sphere") ) 
      return 0;

    write("You polish the glowing blue sphere. Nothing happens.\n");
    say(QCTNAME(TP)+" polishes the glowing blue sphere. Nothing happens.\n");

    return 1;
}




