#include <macros.h>
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Marketplace in Nethosak");
    set_long("@@long_descr"); 

    add_item(({"wagon","wagons"}), "The "+
          "wagons are made out of heavy oak wood, and "+
          "a trader is standing next to it. Offering you "+
          "some of him merchantdise.\n");

    add_cmd_item(({"fountain","water","from fountain","water from fountain"}),
      "drink","@@drink_water");

    add_item(({"tent","tents"}), "The "+
          "tents are made out of thick heavy cloth and colored "+
          "in different dark tones. There's a large opening in "+
          "the side.\n");

    add_item(({"fountain"}), "This "+
          "is a large fountain, constructed out of pure white "+
          "marble. There's been placed a beautiful stone statue "+
          "besides it. A few dry leaves is floating on the "+
          "surface of the water.\n"+
          "The fountain is filled with water.\n");

    add_item(({"statue","stone statue"}), "The "+
          "statue is made of out grey stone, likes the ones used "+
          "to pave the streets. The statue has been carved in such "+
          "a way that it resembles a muscular minotaur, holding "+
          "his battleaxe triumphant into the air. Fresh water "+
          "pours out from his mouth, constantly filling the "+
          "fountain.\n");

    add_item(({"mouth"}), "As "+
          "you look closer at the mouth you seem to notice something "+
          "stuck in it.\n");

    add_exit(MROOM + "square3","north",0);    
    add_exit(MROOM + "square6","east",0);
    add_exit(MROOM + "square1","west",0);    
    add_exit(MROOM + "square8","south",0);             
   
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing in the center "+
          "of a big marketplace in the city of Nethosak. "+
          "Even though there are a lot of people here, the street "+
          "is still very clean and orderly. All around you large "+
          "tents and wagons have been placed in long rows, offering "+
          "different merchantdises to travellers and citizens. The "+
          "marketplace continues to the north and east. The marketsquare "+
          "continues to the north, east, south and west. "+
          season_descr()+ "\n"+
          "A large fountain has been build here.\n";

}

string
drink_water()
{
    if(TP->drink_soft(TP->drink_max() /16, 0))
    {
        write("You carefully remove the leaves from the surface of the water "+
              "and take a drink from the fountain.\n");
        say(QCTNAME(TP) + " carefully removes the leaves from the surface of the "+
              "water and takes a drink from the fountain.\n");
        return "";
    }
    else
        write("You are full of water, you can't drink anymore.\n");
    return "";
}

