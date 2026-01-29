inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

string painting();
string soot();
string stains();
void reset_room();
int do_rub(string str);

static int rubbed = 0;

void
create_room()
{

  set_short("The Antechamber");
  set_long("The eastern and western walls widen out as the "+
  "ceiling rises even farther into the air, making this room "+
  "feel very grand.  Pillars rise on either side of the central lane. "+
  " This room seems to have seen little destruction or decay over "+
  "the years.  North the room widens out into a great hall, and south "+
  "it narrows to an entrance hall.\n");

  add_item(({"central lane","lane"}),"The lane is divided from the "+
  "rest of the room by the crumbling pillars.\n");
  add_item(({"pillar","pillars"}),
  "Of all the pillars, only one reaches to the ceiling.\n");
  add_item(({"ceiling"}),"The ceiling is mostly gone here, at the "+
  "reach of vision, you pick out the decayed green of what was a copper "+
  "roof.\n");
  add_item("roof","The roof, though green and decayed, seems whole.\n");
  add_item(({"wall","walls"}),"Which wall, the eastern or western?\n");
  add_item("eastern wall","The eastern wall is bare, perhaps "+
   "a tapestry once adorned it.\n");
  add_item(({"western wall"}),
  "The western wall has a faint painting on it, mostly "+
  "covered with soot and dark stains.\n");

  add_item(({"painting"}), "@@painting");
  add_item(({"soot"}),"@@soot");
  add_item(({"stains","dark stains","stain"}),"@@stains");
  add_exit(CASTLE_DIR + "c1", "south", 0);
  add_exit(CASTLE_DIR + "c4","north",0,3);
  add_prop(ROOM_I_INSIDE,1);

}

string
painting()
{
   if(!rubbed)
   {
    return "The painting is mostly obscured by the stains and soot "+
   "covering it.\n";
   }

     else return "The painting is of a now ancient scene, a seafarer "+
     "with a sparkling jewel on his forehead disembarks a tall ship, "+
     "two younger men, appearing almost as twins, follow him.\n";

}

string
stains()
{
    if(!rubbed)
    {
      return "They are splattered on the painting on the western wall.\n";
    }

    else return "You find no stains.\n";

}

string
soot()
{
    if(!rubbed)
    {
      return "It covers the painting on the western wall.\n";
    }

    else return "You find no soot.\n";

}

void
reset_room()
{
    rubbed = 0;
}

void
init()
{
    ::init();
    add_action("do_rub","clean");
    add_action("do_rub","rub");
    add_action("do_rub","wipe");
}

int
do_rub(string str)
{
   if(!str)
   {
     write(capitalize(query_verb())+ " what?\n");
     return 1;
    }
    if((str != "painting"))
   {
     write(capitalize(query_verb())+ " what?\n");
     return 1;
    }
    write("You carefully brush the soot and stains from the painting.\n");
   say(QCTNAME(TP)+" does something to the western wall.\n");
   rubbed = 1;
   return 1;
}
