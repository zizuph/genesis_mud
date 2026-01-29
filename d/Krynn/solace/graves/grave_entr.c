/* The graveyard enterance
 * grave_entr.c
 * 11-04-94
 * Nick & Dorak
 * Possible additions:
 *        a wagon as an object
 *        a real gate (door) w/ lock
 *        a climbable wall (difficult)
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h> /* QCTNAME */
inherit GRAVE_STD;

/*prototypes*/
string rd_sign();
string tk_sign();
string th_gate();
string up();
string down();
string north();
string northwest();
string southwest();
string northeast();
string southeast();
string east();
string south();
string swall();
string forest();
string west();



void
create_solace_room()
{
    set_short("Entrance of graveyard");
    set_long("You are standing at the entrance of the big graveyard he" +
      "re in Solace. In this graveyard are buried all brave her" +
      "oes and those not so brave, at least those who died in b" +
      "attle with the creatures of Krynn. To the east is a tall" +
      " stone wall with a small ornate gate in it.  To the sout" +
      "h you see the graveyard.\n");

    /* add_item without descriptives  - they are found below */

    add_item("dirt", "@@down");
    add_item(({"maple tree", "the maple tree", "maple trees",
	"the maple trees", "tree", "the tree", "trees",
	"the trees"}), "@@mpl_trees");
    add_item(({"the bushes", "bushes"}), "@@bush");
    add_item(({"the road", "road"}), "@@road");
    add_item(({"sign", "the sign"}), "@@sign");
    add_item(({"the path", "path"}), "@@path");
    add_item(({"the forest", "forest"}), "@@forest");
    add_item(({"the stone wall", "stone wall"}), "@@swall");
    add_item(({"the gate", "gate"}), "@@gate");
    add_item(({"the haze", "haze"}), "@@haze");

    /* add_item with descriptive included */

    add_item(({"wall", "the wall"}), "Do you mean the stone wall?.\n");
    add_item("entrance",
      "This is the entrance to the Solace graveyard.  The grave" +
      "s are to the south.  There is a well maintained road her" +
      "e. There is thick forest to the north and west. To the e" +
      "ast is a stone wall.\n");
    add_item("cottage",
      "East of the gate you see an old well kept cottage.\n");
    add_item(({"cobblestone", "cobblestones", "cobblestone path"}),
      "The cobble stone path is old and well worn, but in very good c" +
      "ondition.\n");
    add_item(({"ruts", "the ruts"}),
      "These are from a small wagon or cart. They go from north" +
      "west to south.  They are shallow and show signs of havin" +
      "g been filled from time to time.\n");

    ADD_GRAVEYARD;

    add_exit(C_SOLACE, "northwest", 0);
    add_exit(DOR_DIR + "studio", "east", "@@go_east");
    add_exit(TDIR + "grave0", "south", 0);

    OUTSIDE;

}

int
go_east()
{
    /*
	if(this_player()->query_wiz_level())
	  {
	      write("In a puff of purple haze a key appears in your ha" +
		    "nd.  You unlock the gate, fling it" +
		    " open and scurry through, slamming it locked " +
		    "behind you.  The key vanishes back to whereever i" +
		    "t came from.  You find you are not in the graveke" +
		    "epers yard, but instead a Wizard's studio.\n");
	      say("There is a puff of purple haze and a key appears in\n"
		  + QCTNAME(TP) + "'s hand.  With it the gate is quickly\n"
		  + "unlocked and " + QCTNAME(TP) + " opens it, rushes through\n"
		  + "and then slams it shut.  You hear a faint click.\n");
	      return 0;
	  }
	else 
    */
    {
	write("The gate is closed.\n");
	say(QCTNAME(TP) + " tries to go east but the gate is closed.\n");
	return 1;
    }
}

/* add action items */
void
init() 
{
    ::init();
    ADA("climb");
    ADA("unlock");
    ADA("pick");
    ADA("knock");
    ADA("open");
    ADA("read");
    ADA("take");
    ADA("look");

}

/* reaction to action included */
int
climb(string str) 
{
    NF("Climb what?\n");
    if ((str == "wall") || (str == "stone wall")
      || (str == "the wall") || (str == "the stone wall"))
    {
	write("You try to climb the wall but it is just too smooth.  Th" +
	  "ere are no cracks or rough spots on it anywhere.  It is " +
	  "truly a remarkable piece of masonry.\n");
	say(QCTNAME(TP) + " tries to climb the stone wall, but fails.\n");
	return 1;
    }
    if ((str == "tree") || (str == "maple") || (str == "maple tree")
      || (str == "the tree") || (str == "the maple tree")
      || (str == "the maple"))
    {
	write("You try to climb one of the near by maple tree, but all" +
	  " the limbs are too high for you to reach and the trunk " +
	  "is too big around to allow you to shimmy up it.\n");
	say(QCTNAME(TP) + " tries to climb a nearby maple tree, but is" +
	  " unable to do so.\n");
	return 1;
    }
    if((str == "gate") || (str == "the gate") || (str == "small gate")
      || (str == "ornate gate") || (str == "small ornate gate"))
    {
	write("You try to climb the gate, but ultimately find that " +
	  "there are a lack of climbable features.\n");
	say(QCTNAME(TP) + " tries to climb the ornate gate, but is " +
	  "unable to do so.\n");
	return 1;
    }
    return 0;
}

int
unlock(string str) 
{
    NF("Unlock what?\n");
    if ((str == "gate") || (str == "small ornate gate")
      || (str == "small gate") || (str == "ornate gate")
      || (str == "gate with key") || (str == "small ornate gate with key")
      || (str == "small gate with key") || (str == "ornate gate with key"))
    {
	write("You can not unlock the gate.  You don't seem to have a k" +
	  "ey that fits.\n");
	say(QCTNAME(TP) + " is messing with the gate lock.\n");
	return 1;
    }
    return 0;
}

int
pick(string str) 
{
    NF("Pick what?\n");
    if ((str == "lock") || (str == "the lock") || (str == "gate lock"))
    {
	write("You try to pick the lock, but it is too complex for you.\n");
	say(QCTNAME(TP) + " is rattling the gate lock.\n");
	return 1;
    }
    return 0;
}

int
knock(string str) 
{
    NF("Knock where?\n");
    if ((str == "on the gate") || (str == "on the small ornate gate")
      || (str == "on the small gate") || (str == "ornate gate")
      || (str == "on gate"))
    {
	write(BS("You are about to knock when you notice a sign " +
	    "hanging on the gate.", 70));
	say(QCTNAME(TP) + " is looking at a sign.\n");
	return 1;
    }
    return 0;
}

int
open(string str) 
{
    NF("Open what?\n");
    if ((str == "gate") || (str == "small ornate gate")
      || (str == "small gate") || (str == "ornate gate")
      || (str == "the gate") || (str == "the small ornate gate")
      || (str == "the small gate") || (str == "the ornate gate"))
    {
	write(BS("The gate is locked.", 70));
	say(QCTNAME(TP) + " tries to open the gate but the gate seems stuck.\n");
	return 1;
    }
    return 0;
}

/* reaction descriptions not included - find these below */
int
read(string str) 
{
    NF("Read what?\n");
    if ((str == "sign") || (str == "common") || (str == "Common"))
    {
	rd_sign();
	return 1;
    }
    return 0;
}

int
take(string str)  /* in response to any attempts to take the sign */
{
    NF("Take what?\n");
    if ((str == "sign") || (str == "the sign"))
    {
	tk_sign();
	return 1;
    }
    return 0;
}

int
look(string str) 
{
    NF("Look through what? at what? or where?\n");
    if ((str == "through gate") || (str == "through the gate"))
    {
	th_gate();
	return 1;
    }
    if (str == "up")
    {
	up();
	return 1;
    }
    if (str == "down")
    {
	down();
	return 1;
    }
    if((str == "n") || (str == "north"))
    {
	north();
	return 1;
    }
    if ((str == "nw") || (str == "northwest"))
    {
	northwest();
	return 1;
    }
    if ((str == "ne") || (str == "northeast"))
    {
	northeast();
	return 1;
    }
    if ((str == "s") || (str == "south"))
    {
	south();
	return 1;
    }
    if ((str == "sw") || (str == "southwest"))
    {
	southwest();
	return 1;
    }
    if ((str == "se") || (str == "southeast"))
    {
	southeast();
	return 1;
    }
    if ((str == "e") || (str == "east"))
    {
	east();
	return 1;
    }
    if ((str == "w") || (str == "west"))
    {
	west();
	return 1;
    }
    return 0;
}

/* ADA details */
int
rd_sign() /* reading the sign on the gate */
{
    write(BS("This is my cottage.  I am very sick right now, so I'm " +
	"not entertaining any guests.  If I feel like entertain" +
	"ing when I'm well you will be able to visit.  Otherwis" +
	"e PLEASE stay out.  My regrets that the old graveyard " +
	"is in such disarray  I'll clean it up ASAP.           " +
	"                                                      " +
	"                                                    \n" +
	"    - The Graveyard Keeper", 70));
    say(QCTNAME(TP) + " reads the sign.\n");
    return 1;
}

int
th_gate() /* looking through the gate in the wall */
{
    write(BS("The wall is very thick.  Beyond the gate is a small cott" +
	"age with a well kept stone path leading up to it.", 70));
    say(QCTNAME(TP) + " looks through the gate.\n");
    return 1;
}

/*
* these are the details for looking in ALL directions
* some direcitons have a default description that is
* listed lower down in this code 
*/
int
up()
{
    write(BS("You see the sky.  There are no clouds right here, though you" +
	" think you might see a little low lying haze ... ... or is t" +
	"hat the spirit of an unfortunate adventurer???", 70));
    say(QCTNAME(TP) + " looks into the sky and shudders.\n");
    return 1;
}

int
down()
{
    write(BS("The ground here is well packed by many years of moderate us" +
	"e.  This is the road to and from the graveyard.", 70));
    say(QCTNAME(TP) + " looks down.\n");
    return 1;
}

int
north()
{
    forest();
    return 1;
}

int
northwest()
{
    write(BS("The road going to and from the graveyard goes in this " +
	"direction through the otherwise dense forest.", 70));
    say(QCTNAME(TP) + " looks in the northwesterly direction.\n");
    return 1;
}

int
northeast()
{
    forest();
    return 1;
}

int
south()
{
    write(BS("To the south the graveyard begins.  You can see some of" +
	" the gravestones there.", 70));
    say(QCTNAME(TP) + " gazes to the south.\n");
    return 1;
}

int
southwest()
{
    forest();
    return 1;
}

int
southeast()
{
    write(BS("Through some trees and bushes you see part of the graveyard." +
	"  Far to the southeast you see a giant Vallenwood tree tower" +
	"ing above all else.  You think there might be a structure of" +
	" some sort in it, but from this distance it is hard to tell." +
	"", 70));
    say(QCTNAME(TP) + " gazes to the southeast.\n");
    return 1;
}

int
east()
{
    swall();
    return 1;
}

int
west()
{
    forest();
    return 1;
}

int
tk_sign() /* what happens when someone tries to take the sign */
{
    write(BS("The sign is fastened to the gate with a very sturdy piec" +
	"e of chain.  You can't take it.  The chain can't be brok" +
	"en, it is too well made.", 70));
    say(QCTNAME(TP) + " tugs on the sigh.  You hear a clanking sound.\n");
    return 1;
}

/* default descriptives for looking in directions */
string
forest()
{
    write(BS("There is a dark and unpassable forest here.", 70));
    say(QCTNAME(TP) + " gazes into the forest.\n");
    return "";
}

string
swall()
{
    write(BS("This is a very well kept sturdy tall smooth stone wall.  It" +
	" is old and of such incredible workmanship it must have bee" +
	"n made by a dwarf.  There is a small ornate gate leading th" +
	"rough it.", 70));
    say(QCTNAME(TP) + " looks at the stone wall that is to the east.\n");
    return "";
}

/* add_item descriptions */
string
mpl_trees()
{
    write(BS("These are large majestic maple trees that seperate the" +
	" graveyard from the graveyard keepers estate.", 70));
    say(QCTNAME(TP) + " looks at some trees near by.\n");
    return "";
}

string
bush()
{
    write(BS("The bushes here are common harmless undergrowth to Krynn.  A" +
	"lthough harmless, they usually grow in thick patches that ma" +
	"ke movement through them difficult or impossible.", 70));
    say(QCTNAME(TP) + " looks at the bushes.\n");
    return "";
}

string
road()
{
    write(BS("This is a hard packed dirt road.  It has very shallow wagon " +
	"ruts in it.  It is otherwise in very good shape.  It is obvi" +
	"ously well traversed, though the hard packed surface leaves " +
	"no traces of tracks.", 70));
    say(QCTNAME(TP) + " looks at the road.\n");
    return "";
}


string
sign()
{
    write(BS("This is a new sign written in the common tounge so you can r" +
	"ead it.", 70));
    say(QCTNAME(TP) + " looks at a sign.\n");
    return "";
}

string
path()
{
    write(BS("This is a little cobblestone path that leads from the " +
	"gate to the cottage.  It is well maintained and clean." +
	"", 70));
    say(QCTNAME(TP) + " looks through the gate at something.\n");
    return "";
}

string
gate()
{
    write(BS("This is a small wrought iron gate that leads through t" +
	"he fence.  It is very ornate.  There is a new sign han" +
	"ging on it.  The gate is closed.", 70));
    say(QCTNAME(TP) + " takes a closer look at the wall.\n");
    return "";
}

string
haze()
{
    write(BS("Now that you look carefully, it looks a little humanoid shap" +
	"ed and seems to hover above the graveyard.", 70));
    say(QCTNAME(TP) + " stares intently into the sky and shivers.\n");
    return "";
}
