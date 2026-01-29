/*
   Diamond. Street LINE.

   line.c
   -----------
   Coded ........: 08/24/93
   By ...........: Aridor

   Latest update : April 1997
   By ...........: Kentari

*/

#include "../local.h"

inherit STREET;

#include <macros.h>

int moves = 0;

public void
create_street()
{

    set_short("In Line for the Bathroom");
    set_long("@@my_long@@");

    AE(DIROOM + "se2","southwest","@@leave_line_first");
    AE(DIROOM + "e1","northeast","@@leave_line_first");
    AE(DIROOM + "bathrm","southeast","@@why_wait");

    AI("line", "You are definitely standing in a line. " +
	     "Unfortunately, as is usual when waiting for a bathroom, " +
	     "it is virtually impossible to know how much longer " +
	     "you'll have to wait.\n");
    AI(({"bathroom","se"}),
	"The bathroom lies to the southeast, and seems to be one of " +
	"the more popular attractions of the city, which is no " +
	"wonder with all of the drinks available.\n");
    AI("sign","The sign has a painting of three sick-looking people, " +
	"one with a green face and covering their mouth, one with a " +
	"tense face and holding their crotch, and one with a blue face " +
	"and holding their behind.\n");
}


void
init()
{
    int i;
    ::init();
    add_action("leave_line","exit");
    add_action("leave_line","leave");
    for(i = moves; i < 20; i++)
      set_alarm(itof(i * 20),0.0,"little_move",TP);
    moves = 20;
    set_alarm(200.0,0.0,"my_move", TP);
}


int
leave_line(string str)
{
    int i;
    if (str == "line")
    {
        write("You leave the line for the bathroom.\n");
        say(QCTNAME(TP) + " leaves the line for the bathroom.\n");

        TP->move_living(0,DIROOM + "se1");
        return 1;
    }
    else
    {
        NF("Exit what?\n");
        return 0;
    }


}


void 
little_move(object player)
{   
    seteuid(getuid(TO));
    if (player && E(player) == TO)
      player->catch_msg("The line moves a little closer to the bathroom " +
	"and your need to get there increases with the wait.\n");
    /*tell_room(TO,"The line moves a little further.\n");*/
    moves--;
}


void
my_move(object player)
{
    seteuid(getuid(TO));
    if (present(player, TO))
    {
        write("FINALLY you reach the bathroom. The line ends here.\n");
        player->move_living("southeast", DIROOM + "bathrm", 0);
    }
}

string
my_long()
{
    string desc = ("You are somewhere in the line for the bathroom of " +
	"Diamond City. There are many people here, a few just trying " +
	"to make their way through the crowd, and most waiting " +
	"impatiently for use of the bathroom.\n");
    return desc;
}

int
leave_line_first()
{
    write("You are still standing in line, remember? This means you " +
	  "have to exit the line first before wandering off!\n");
    return 1;
}

int
why_wait()
{
    write("What do you think you are waiting in line for? No " +
	"cutting after all.\n");
    return 1;
}
