inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/*
 * Undraeth repatriated wholly to Kalad.
 * Removed Avenir reference.
 * 	-Lucius, June 2017
 */
/* by Antharanos */
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_M_NO_TELEPORT,1);
    set_short("A narrow tunnel");
    set_long("An immense weight of rock hangs above you in this narrow "+
      "and somewhat cramped tunnel, giving you an uneasy feeling as you "+
      "ponder just how much rock is above you. The passage is wider here "+
      "than in the west, and in the east it appears to widen even further. "+
      "The "+
      "featureless walls of the passage do nothing but add to the "+
      "seemingly endless expanse of rock.\n"+
      "The passage heads to the west and east.\n");
    add_item(({"rock"}),"Strangely dark stone that appears to exude "+
      "darkness as one would exude sweat on a searing day in summer.\n");
    add_item(({"narrow tunnel","cramped tunnel","tunnel"}),"The passage "+
      "is made out of a strangely dark rock.\n");
    add_item(({"passage"}),"The tunnel is made out of a strangely dark "+
      "rock.\n");
    add_item(({"featureless walls","walls","wall"}),"The rough uncut "+
      "stone of the passage lends you to believe it was crafted by nature, "+
      "as opposed to some intelligent force.\n");
    add_item(({"endless expanse","expanse"}),"Filling your sight in "+
      "every direction is the strangely darkened rock of the Dark Dominion.\n");
    add_exit(CPASS(drow/d2),"west");
    add_exit(CPASS(drow/d4),"east");
    set_noshow_obvious(1);
}
