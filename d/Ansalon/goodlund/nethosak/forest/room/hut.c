#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
inherit MITHAS_IN;

object witch;
int no_go = 1;


void
reset_mithas_room()
{
   if(!objectp(witch))
   {
      witch = clone_object(MNPC + "laran");
      witch->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Wooden hut");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest24","out",0);

   add_item(({"wooden shelves","shelves"}),
     "The shelves are filled with jars containing "+
     "herbs. Some of then are quite fresh while "+
     "others look very old and dry.\n");

   add_item(({"jars"}),
     "The jars contain "+
     "herbs. Some of then are quite fresh while "+
     "others look very old and dry.\n");

   add_item(({"large bookshelf","bookshelf"}),
     "The bookshelf is made out of oak wood. It "+
     "has some strange old books place on it. "+
     "Perhaps some books about herbs and spellcraft.\n");

   add_item(({"strange books","books"}),
     "The books looks very old and well-used. "+
     "Perhaps these books contain strange "+
     "incantations and descriptions of "+
     "the different herbs in Krynn.\n");

   add_item(({"fire"}),
     "The fire burns brightly, giving a warm "+
     "glow to the entire hut.\n");

   add_item(({"cauldron"}),
     "The cauldron is made out of blackened iron, "+
     "and in it a strange brew is boiling.\n");

   add_item(({"brew"}),
     "This thick brown brew is boiling slightly in the cauldron. "+
     "You don't think it would be healthy to drink it!\n");

   add_cmd_item(({"brew"}),"drink","@@drink_brew");
 
   reset_mithas_room();
}

string
long_descr()
{ 
    return
    "You stand within a primitive wooden hut, in the "+
    "southern part of Mithas. This hut has been made out "+
    "of wooden boards and grass peat. Wooden shelves with "+
    "jars fill the east wall, and to the west a large "+
    "bookshelf stands, containing some strange old books. "+
    "In the middle of the hut a small fire burns, and a "+
    "huge cauldron has been placed above it.\n";
}

int
drink_brew(string str)
{
    object sh;
    mixed why;

    write("You carefully take a small swig from the brown brew.\n");
    say(QCTNAME(this_player()) + " takes a small swig from the brown brew.\n");
    set_alarm(4.0,0.0, &write("You have been poisoned!\n"));
    say(QCTNAME(this_player()) + " looks very ill!\n");
    return 1;   
}


