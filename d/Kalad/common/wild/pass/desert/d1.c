inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
    ::create_room();
    add_prop(ROOM_NO_TIME_DESC,1);
    set_short("The Caravan Route, edge of the waste");
    set_long("The low foothills end here, and the vastness of the Great "+
      "Kalad Waste stretches in all its glorious bleakness to the "+
      "southeast. Only to the northwest is there the promise of water, and "+
      "life. The Caravan Route heads to the northwest and to the southeast.\n");
    add_item(({"caravan route","route"}),"A cobblestoned roadway that "+
      "shows the effects of heavy travel and the torturous environment.\n");
    add_item(({"great kalad waste","great waste","kalad waste","waste"}),
      "An apparently endless wasteland, the heat causes your vision to "+
      "blur, making the horizon shift and waver.\n");
    add_item(({"horizon"}),"A thin line in the distance.\n");
    add_item(({"foothills","foothill"}),"Small rises visible far to the "+
      "northwest.\n");
    add_exit(CPASS(goblin/g4),"northwest","@@msg",3);
    add_exit(CPASS(desert/d2),"southeast",0,3);
}
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (query_verb() == "nw" || query_verb() == "northwest")
	write("Shaking the sand from your clothes, you leave the waste behind you.\n");
}
block()
{
    write("To the southeast a towering, raging dust storm whirls furiously "+
      "about, destroying all within its path. You, yourself, are nearly "+
      "caught up in its terrible embrace, but thankfully, you manage to "+
      "escape.\n");
    return 1;
}
