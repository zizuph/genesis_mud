inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On Gateway Street");
    set_long("You now travel along the northern most street of Kabal: "+
    "Gateway street. This street heads east all the way into the "+
    "Caravan district, crossing the two gates to outside of the city; "+
    "High gate and Caravan gate. The street here in the noble district "+
    "are clean. The hot Kaladian sun burns down on you.\n");
    add_exit(NOBLE(gateway/s2),"west",0,0,-1);
    add_exit(NOBLE(gateway/s4),"east",0,0,-1);
/*
    add_exit(NOBLE(lingerie_shop/shop),"south",0);
*/
}


int
closed()
{
// the shop is temporarely closed, Toby.

    write("When you try to enter the shop you notice the door is closed. " +
	  "There is a small sign on the inside stating that the shop is closed " +
	  "due to death within the family.\n");

    return 1;
}

int
no_men()
{
   if (TP->query_gender() != 1)
   {
      write("A nice lady gently pushes you out her shop while "+
      "soothing you with some words: 'Send your servants, darling.'\n");
      return 1;
   }
   return 0;
}
