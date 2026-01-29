/* created by Aridor 08/24/93 */

#include "../local.h"

inherit STREET_BASE

#include <macros.h>

int moves = 0;

void
create_palan_room()
{

    set_short("In Line on the Central Plaza");
    set_long("@@my_long@@");

    add_exit(ROOM + "street17","northwest","@@leave_line_first");
    add_exit(ROOM + "street20","west","@@leave_line_first");
    add_exit(ROOM + "street10","southwest","@@leave_line_first");
    add_exit(ROOM + "street3","south","@@leave_line_first");
    add_exit(ROOM + "street4","southeast","@@leave_line_first");
    add_exit(ROOM + "street6","east","@@leave_line_first");
    add_exit(ROOM + "street12","northeast","@@leave_line_first");
    add_exit(PALACE + "palace1","north","@@why_wait");

    add_item("line", "You are definitely standing in a long line. " +
	     "Unfortunately the line twists and turns so you cannot " +
	     "make out how long it will take for you to get to the palace.\n");
    add_item(({"palace","tower","white tower","building"}),
	     "It's truly a magnificent palace which is topped by the white " +
	     "tower. The palace makes up the entire north side of the plaza, " +
	     "it's front is also painted white and many windows look out " +
	     "onto the plaza.\n");
    add_item(({"window","windows","front"}),
	     "The windows on the palace front are painted in different but " +
	     "still decent colors, giving the building a friendly and " +
	     "peaceful appearance.\n");
    add_item(({"fountain"}),
	     "From your point in the line, you cannot make out much, but " +
	     "the fountain is really a statue.\n");
    add_item(({"statue","man"}),
	     "All you can make out is that the statue resembles a man with " +
	     "water sprouting from his hands.\n");
    add_item(({"hand","hands","head","water"}),
	     "You cannot make out any details.\n");
    add_item(({"plaza"}),
	     "It's a large plaza on which you are standing. Crowds of people " +
	     "are in front of and behind you, pushing and shoving you. In " +
	     "the middle of the plaza is a fountain.\n");
    add_item(({"people","crowd","crowds"}),
	     "All these people here! You are in a very long line of people, " +
	     "but everywhere on the plaza you can see people strolling " +
	     "around, minding their business.\n");

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
    set_alarm(220.0,0.0,"my_move", TP);
}


int
leave_line(string str)
{
    int i;
    if (str == "line")
    {
        write("You leave the line.\n");
        say(QCTNAME(TP) + " leaves the line.\n");

        TP->move_living(0,ROOM + "plaza");
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
      player->catch_msg("The line moves a little further.\n");
    /*tell_room(TO,"The line moves a little further.\n");*/
    moves--;
}


void
my_move(object player)
{
    seteuid(getuid(TO));
    if (present(player, TO))
    {
        write("Finally you reach the palace. The line ends here.\n");
        player->move_living("north", PALACE + "palace1", 0);
    }
}


string
my_long()
{
    string desc = ("You are somewhere in the line on the Central Plaza. " +
		   "It is unmistakably the center of the city there are " +
		   "crowds of people pushing and shoving you. You " +
		   "just hope all your money is safe. Actually you wonder " +
		   "about these people since there is nothing on the plaza " +
		   "except a fountain, water glistening golden in the sun. " +
		   "Towering the plaza to the north is the Palace with its " +
		   "magnificent white tower glistening in the sun and " +
		   "radiating warmth.\n");
    return desc;
}


int
leave_line_first()
{
    write("You still stand in line, remember? This means you " +
	  "have to exit the line first before wandering off!\n");
    return 1;
}

int
why_wait()
{
    write("What do you think you are waiting in line for?\n");
    return 1;
}


