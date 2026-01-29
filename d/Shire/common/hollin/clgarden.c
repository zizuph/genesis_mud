#include "valley.h"

int has_tiara;

create_valley() {
    has_tiara = 1;
    set_short("Beautiful, closed garden");
    set_long("You are in a beautiful, closed garden, surrounded by dense "+
	     "undergrowth. Gladiols, bougainvillea, lilies, and other "+
	     "exotic plants you cannot recognize, frame a small statue "+
	     "which emits a glowing light. ");
    add_item("statue", 
	  "It represents an elven princess, and is nicely hewn out of the "+
	     "best marble. The princess is beautiful, and looks almost "+
	     "alive! But of course, it is too heavy to carry.\n");
    NORTH("winding");

/*
    add_exit("players/rogon/avd1/basin_s","north");
    add_exit("players/rogon/avd1/winding","south");
    add_exit("players/rogon/avd1/crevice","west");
*/

}

reset_valey() {
    has_tiara = 1;
}

init() {
    ::init();
    add_action("my_touch","touch");
    add_action("my_kiss","kiss");
    add_action("my_move","move");
}

int
she(string str)
{
    return member_array(str, ({"princess","statue","marble"}))!=-1;
}

string
message(int n)
{
    string str =
	"The princess whispers to you:\n"+
	"   I am Arwen Undomiel of the High Elven race.\n"+
	"   If you seek the precious dwarven ring hidden\n"+
	"   deep in the Mines of Moria, you will need this\n"+
	"   tiara. I will inform the elves that a good\n"+
	"   creature wears this item, so keep it well.\n"+
	"   I will also advice you this:\n";

    if(n==0)
	str +=
	    "       There is a magical staff hidden in this\n"+
	    "       valley. Find it, and you shall be gifted\n"+
	    "       with light in thy path.\n";
    else if(n==1)
	str +=
	    "       It is said that Dain Ironfoot's Waraxe\n"+
	    "       is kept by the trolls in their treasures.\n"+
	    "       They keep it there because of its powers\n"+
	    "       against the foul creatures of Morgoth.\n";
    else if(n==2)
	str +=
	    "       Durin's Axe is said to be hidden in Durin's\n"+
	    "       treasure chamber beneath his throne. Do not\n"+
	    "       take it, unless you wear the dwarwen ring of\n"+
	    "       power on your hand. Thus is the commandment\n"+
	    "       upon the Naugrim, that noone should wield the\n"+
	    "       mighty axe without the wearer of Durin's Ring.\n";
    return str;
}

int
my_touch(string str)
{
    object tiara;
    if(!str) {
	notify_fail("Touch what?\n");
	return 0;
    }
    write("You touch the statue.\n");
    say(QCTNAME(TP)+" touches the statue.\n");
    if(!she(str))
	return 0;
    if(!has_tiara) {
	write("Nothing happens.\n");
	return 1;
    }
    write(message(random(3)));
    write("The princess suddenly melts back into her statue.\n");
    say("The statue seems to be alive for a second!!\n");
    say("The princess seems to whisper something to "+
	 QTNAME(TP)+".\n");
    say("But then the princess melts back into her statue.\n");
/*
    tiara->clone_object(STAND_ARMOUR+"tiara");
    tiara->move(TO);
    tiara->move(TP);
*/
    has_tiara = 0;
    return 1;
}

my_kiss(string arg) {
  if(!arg) {
    notify_fail("Kiss what?\n");
    return 0;
  }
  if(arg == "princess" || arg == "statue" || arg == "marble") {
    write("Nothing happens.\n");
    return 1;
  }
}

my_move(string arg) {
  if(!arg) {
    notify_fail("Move what?\n");
    return 0;
  }
  if(arg == "princess" || arg == "statue" || arg == "marble") {
    write("Nothing happens.\n");
    return 1;
  }
}
