/*
 * Kalad transition point into Cirath
 * By TAPAKAH, 10/2008
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route, edge of the waste");
   set_long("A mixed kind of land is around you, although not an encouraging "+
            "mix. The white and yellow of Great Kalad Waste is mending with "+
            "the reddish hue of the desert surrounding Tyr. To your " +
            "southeast you see a cliff of some sorts. The sand swirls around "+
            "you, but in a tolerable intensity. The sun continues to beat "+
            "down on you. The Caravan Route widens towards the northeast. "+
            "To your west the Great Kalad Waste begins.\n");
   add_item(({"caravan route","route"}),"A cobblestoned roadway that "+
      "shows the effects of heavy travel and the torturous environment.\n");
   add_item(({"great kalad waste","great waste","kalad waste","waste"}),
      "An apparently endless wasteland, the heat causes your vision to "+
      "blur, making the horizon shift and waver.\n");
   add_item(({"swirling sand","sand"}),"It swirls and billows all about "+
      "you, but it doesn't affect you too much here.\n");
   add_item(({"kaladian sun", "cirathian sun", "sun"}),
            "Its unrelenting rays have helped "+
            "turn this land into a harsh desert where little survives.\n");
   add_item(({"lands","land"}),"The land to the east seems more "+
            "reddish, white to the west it's white and yellow.\n");
   add_item(({"cliff","stone cliff","red cliff","red stone cliff"}),
         "It is an imposing cliff composed of the same reddish-brown "+
         "stone which makes up the Cirathian Ringing Mountains and the "+
         "bedrock "+
         "in those parts. At this point the cliff is over "+
         "40 metres in height, while no easy way up the cliff can be "+ 
         "found at this point. Since you have no reason to believe "+
         "that anything interesting can be found at the top, you "+
         "decide that it would not be worth the risk of climbing it, "+
         "at least at this point.\n");
   add_exit(CPASS(desert/d40),"northwest");
   add_exit("/d/Cirath/ridge/desert/d05","northeast","@@enter_cirath");
}

int enter_cirath()
{
   write("It is almost like you pass through a curtain, the intense "
      + "burn from the Cirathian sun hitting you like a mallet. "
      + "You can feel the harsh life-draining existence of being in "
      + "Cirath beginning.\n");
        return 0;
}
