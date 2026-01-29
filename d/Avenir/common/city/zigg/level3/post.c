// F.I.P.S. (/d/Avenir/common/city/zigg/level3/post.c)
// creator(s):   Zielia 2006
// purpose:      postal service            
// note:         
// bug(s):
// to-do:  
//
//  F.I.P.S. = Forbidden Isle Postal Service.
//
#include "zigg.h"

inherit ZIG_ROOM;
inherit "/d/Genesis/lib/post";

public void
create_room()
{
     set_short("Ziggurat Parcel Center");
     set_long("This is a branch of the Forbidden Isle Postal "+
	 "Service conveniently located within the Ziggurat. Silence "+
	 "is a revered quality in all those who visit, whether they "+
	 "wish to send or receive parcels. The floor, walls and ceiling "+
	 "are of the same black stone as the rest of the Ziggurat, though "+
	 "less glossy so as not to put a strain on your eyes for when "+
	 "you need to read those all-important missives. As such, the "+
	 "lighting is kept dim, with only a few black candelabrum along "+
	 "the walls. A single clerk can be seen behind a flat black "+
	 "counter sorting various bits of scrolls and sundry packages."+
	 "@@see_nearby@@\n");

     add_item(({"walls","wall","floor","ceiling","stone","black stone",
         "ground"}), "The floor, walls and ceiling are all crafted from "+
	 "the same flat black stone. One of the walls has a placard "+
	 "attached.\n");
     add_item(({"candelabra","candelabrum","black candelabrum",
	 "black candelabra"}),
	 "The few candelabrum along the walls are coated black to match "+
	 "the walls. The soft orange flames from the candles give off a "+
	 "warm but dim glow, just enough to read by.\n");
     add_item(({"counter","black counter","flat black counter"}),
	 "It is a 2-level counter made from kesoit wood that has been "+
	 "a flat black, although you can still make out faint veins of "+
	 "orange and red running through the grain. The portion of the "+
	 "counter facing you is more elevated than that which the clerk "+
	 "has access to and is devoid of any clutter, unlike the clerks "+
	 "portion which is covered in parcels and packages.\n");
     add_item(({"mail","mails","scrolls","parcels","package","packages"}),
	 "Those are the varied and sundry parcels and packages that "+
	 "the clerk is sorting through in preparation for delivery "+
	 "and/or pickup.\n");
     add_item(({"clerk"}),
	 "The clerk looks to be a "+ one_of_list(({"human","half-elf"})) +
	 " "+ one_of_list(({"male","female"})) +". They appear to be busily "+
	 "sorting through various parcels and packages.\n");
     add_item(({"placard","poster","board"}),
	 "The placard is actually a simple black poster board with "+
	 "white lettering informing you to check the mailreader for "+
	 "instructions.\n");

     add_exit("room3", "south");

     add_zigg();
}

private void
welcome(object who)
{
    if (!present(who, this_object()))
	return;

    who->catch_tell("The clerk looks up and notices you, after "+
	"a brief, calculating stare, they indicate a placard "+
	"on one of the walls.\n");
}

public void
init(void)
{
    ::init();
    post_init();

    if (query_interactive(TP))
    {
	int ran = random(2) + 1;
	set_alarm(itof(ran), 0.0, &welcome(TP));
    }
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
