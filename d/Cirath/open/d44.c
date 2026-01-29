inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
    ::create_room();
    add_prop(ROOM_NO_TIME_DESC,1);
    set_short("A sandy syncline on the Caravan Route");
    set_long("You find yourself in the sandy pit within the Great Kalad "+
      "Waste. The unrelenting Kaladian sun beats down from above, "+
      "its harsh rays searing exposed flesh. Here, in the syncline it "+
      "seems to shine even stronger and much more deadly.\n"+
      "The air in the syncline is so hot that it burns your lungs "+
      "painfully. Moreover, the swirling sand enters your mouth and nose "+
      "what makes breathing a very uncomfortable activity.\n"+
      "The Caravan Route heads to the northwest and southeast.\n");
    add_item(({"caravan route","route"}),"A cobblestoned roadway that "+
      "shows the effects of heavy travel and the torturous environment, "+
      "here in many places covered by the sand what makes it very difficult "+
      "to follow. To the southeast it climbs up a bit and leaves the syncline.\n");
    add_item(({"swirling sand","sand"}),"It swirls and billows all about "+
      "you, limiting your vision and making your breath dangerously short.\n");
    add_item(({"kaladian sun","sun"}),"Its unrelenting rays have helped "+
      "turn this land into a harsh wasteland where little survives.\n");
    add_item(({"syncline","pit","sandy syncline"}),"A sandpit of proportions "+
      "adequate to the Great Kalad Waste. The heat causes your vision to "+
      "blur, making the everything you can see shift and waver.\n");
    add_exit(CPASS(desert/d43),"northwest","@@msg",3);
    add_exit(CPASS(desert/d45),"southeast","@@msg",3);
}
msg()
{
    write("The sand on the road makes your movements difficult.\n");
    return 0;
}

