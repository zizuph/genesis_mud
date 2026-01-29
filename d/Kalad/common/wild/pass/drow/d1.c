inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/*
 * Undraeth repatriated wholly to Kalad.
 * Removed Avenir reference.
 * 	-Lucius, June 2017
 */
object ob1;
/* by Antharanos */
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_M_NO_TELEPORT,1);
    set_short("A narrow tunnel");
    set_long("An immense weight of rock hangs above you in this narrow "+
      "and cramped tunnel, adding to your sense of claustrophobia. The "+
      "featureless walls of the passage do nothing but add to the "+
      "seemingly endless expanse of rock.\n"+
      "Dark passages lead to the west and northeast.\n");
    add_item(({"rock"}),"Unusually dark stone that appears to exude "+
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
    add_exit(CPASS(underdark/u31), "west");
    add_exit(CPASS(drow/d2), "northeast");
    clone_object(CPASS(drow/door/c_e_gate1))->move(TO);

    set_noshow_obvious(1);

    enable_reset();
    add_npc(CPASS(drow/npc/c_e_guard), 2, &->equip_me());
}
