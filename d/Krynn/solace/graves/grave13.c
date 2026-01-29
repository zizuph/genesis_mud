/* The graveyard
 *
 * Nick & Dorak
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit GRAVE_STD;

void
create_solace_room()
{
    set_short("Graveyard");
    set_long(BS(
	"You are in the Solace graveyard. Graves are all around you. " +
	"The graves look well kept here and the path going north looks " +
	"rather well used." +
	"", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave8", "north", 0);
    add_exit(TDIR + "grave12", "west", );
    add_exit(TDIR + "grave18", "south", );
}

void
init()
{
    ::init();
    ADA("bless");
}

int
bless(string str)
{
    object obt;

    NF("Bless what?\n");
    str = lower_case(str);
    if ((str == "grave") || (str == "drakmar_dragonbane") ||
	str == "drakmar" || str == "drakmar dragonbane" ||
	str == "grave of drakmar" || str == "grave of drakmar dragonbane" ||
	str == "grave of drakmar_dragonbane")
    {
   	if (obt = present("tour3", TP))
	    obt->set_arr("bless");

	write(BS("You bless the grave and it makes you feel good.", 70));
	say(BS(QCTNAME(TP) + " blesses a grave.", 70));
	return 1;
    }
    return 0;
}

/* Redefine this function so that Drakmar's grave appears here */
string
graves()
{
    string filename, *names, str;
    int j;
    
    seteuid(getuid(this_object()));
    filename = GRAVE_LOG + "rooms/room" + TO->query_grave_room();
    if (file_size(filename) > 0)
      {
	  str = read_file(filename);
	  names = explode(str, " ") - ({ "" });
	  names = ({"Drakmar Dragonbane"}) + names;
	  j = sizeof(names);
	  if (j < 1)
            return "The graves are all empty, yet to be filled.\n";
	  if (j == 1)
            str = names[0];
	  else
            str = implode(names[0 .. j - 2], ", ") + " and " + names[j - 1];
	  write("You look at the graves and read the names on them:\n");
	  write(break_string(str + ".\n", 70));
	  write("There is text written on each grave which you can read.\n");
	  return "";
      }
    return "You can't make out anything about the graves.\n";
}

mixed
grave_look()
{
    string str;
    
    str = query_item_rest_command();
    if (!str)
      return "You must tell me what grave you want to read on.\n";
    if (L(str) == "grave of drakmar" || 
	L(str) == "grave of drakmar dragonbane" ||
	L(str) == "of drakmar" || 
	L(str) == "of drakmar dragonbane")
    {
	write("You read:\n" +
	      "  Killed by a huge red dragon in defence\n" +
	      "  of our home, the village of Solace, when\n" +
	      "  dealing the final blow to the beast.\n" +
	      "                R.I.P.\n");
	return 1;
    }
    return ::grave_look();
}

int
query_grave_room() { return 13; }
