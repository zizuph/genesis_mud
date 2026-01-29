/*
   Diamond. Street SE#1.

   se1.c
   -----------
   Coded ........: April 1997
   By ...........: Kentari
   
   Latest update : April 1997
   By .......... : Kentari

*/

#include "../local.h"
#include <macros.h>

inherit STREET;

public void
create_street()
{
    add_my_desc("A bathroom lies to the southeast, with a sign " +
	"hanging above it and a long line waiting to enter in " +
	"front of it. The street continues to the " +
	"southwest and to the northeast, where it leads to the " +
	"eastern corner of the city.\n");
    AI(({"bathroom","se"}),
	"The bathroom lies to the southeast, and seems to be one of " +
	"the more popular attractions of the city, which is no " +
	"wonder with all of the drinks available.\n");
    AI("sign","The sign has a painting of three sick-looking people, " +
	"one with a green face and covering their mouth, one with a " +
	"tense face and holding their crotch, and one with a blue face " +
	"and holding their behind.\n");
    AI(({"line","long line","patrons"}),
	"It is a fairly long line of people, all of which are waiting " +
	"to use the bathroom.\n");
     
    add_cmd_item(({"line","in"}),({"stand","wait"}),"@@wait_forever");
   
    AE(DIROOM + "e1", "northeast", 0);
    AE(DIROOM + "se2", "southwest", 0);
    AE(DIROOM + "bathrm","southeast","@@bathrm_closed",0);
}

int
bathrm_closed()
{
    if ((present("diamond_mem", TP)) || (TP->query_wiz_level()))
      {
	write("The bathroom attendant emerges with a smile, " +
		"saying: \"Welcome! Please pay no attention to " +
		"the line here, one such as you is above such " +
		"things. I hope our facilities serve you adequately.\" " +
		"The attendant bows humbly and clears your way through " +
		"the crowd.\n");
	return 0;
      } 
	write("The bathroom attendant emerges and blocks your way, " +
		"saying: \"Excuse me! There _is_ a line here. If you'd " +
		"like to use the facilities, please wait in line with " +
		"the other patrons. Thank you, and have a nice day.\" " +
		"The attendant bows curtly and frowning, goes back " +
		"to work.\n");
	return 1;
}

int
wait_forever()
{
    write("You enter the line. Despite the urgency of the situation, " +
	"this may take a while.\n");
    say(QCTNAME(TP) + " enters the line.\n");
    TP->move_living(0, DIROOM + "line");
    return 1;
}
