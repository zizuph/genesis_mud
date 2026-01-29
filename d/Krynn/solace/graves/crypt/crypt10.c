/* The crypt by percy */

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
inherit INSIDE_BASE;

int altar = 0;
/*          0 = white light,
 *          1 = no light,
 *          2 = black light
 */

object ob;

void
create_solace_room()
{
    set_short("Altar room");
    set_long("@@slong");
    
    add_exit(TDIR + "crypt8", "east", 0);
    add_exit(TDIR + "crypt9", "west", 0);
    
    add_item(({"floor", "ground"}), "@@floor");
    add_item(({"altar", "black altar"}), "@@altar");
    add_item(({"light", "column", "cylinder", "cylindrical column"}),
	     "@@whichlight");
    add_item("white light", "@@wlight");
    add_item("black light", "@@blight");
    add_item(({"wall", "walls", "earthen wall", "earthen walls",
		 "ceiling", "roof"}), "@@wall");
    add_item(({"chrome plaque","chrome amulet"}), "@@plaque");
    add_item(({"platinum amulet"}), "@@gplaque");
    add_item(({"plaque","amulet","symbol"}),"@@whichplaque");
    add_item(({"hole", "hole in altar"}), "@@ahole");
    
    INSIDE;
    LIGHT;
}

void
reset_solace_room()
{
    altar = 0;
}

string
slong()
{
    string str = "This is a well lit cavern." + 
      " In the centre of the cavern is a black altar.\n";
    if (altar != 2)
      {
	  str += "Streaming up from the altar is a cylindrical" +
	    " column of black light that reaches to the ceiling.\n";
      }
    else
      {
	  str += "Streaming up from the altar is a cylindrical" +
	    " column of white light that reaches to the ceiling.\n";
      }
    
    return str;
}

void
init()
{
    ::init();
    ADA("pull");
    ADA("put");
    ADA("pray");
	
}

int
query_altar()
{
    return altar;
}

int
pull(string str)
{
    if (altar == 0)
      {
	  NF("Pull what?\n");
	  if ((str == "plaque") || (str == "plaque from altar") ||
	      (str == "amulet") || (str == "amulet from altar"))
	    {
		write("You pluck the plaque from the altar and"
		      + " discover that it is in fact an amulet!\n");
		say(QCTNAME(TP) + " takes something from the altar!\n");
		seteuid(getuid());
		clone_object(OBJ + "evil_amulet")->move(TP);
		altar = 1;
		return 1;
	    }
	  return 0;
      }
    return 0;
    
}

int
pray()
{
    write("You kneel and pray to this evil altar."
	  + " You feel your soul shrivel up inside of you.\n");
    say(QCTNAME(TP) + " prays to the altar.\n");
    return 1;
}

int
put(string str)
{
    NF("Put what?\n");
    if (altar == 1)
      {
	  if ((str == "platinum amulet in altar") || (str == "amulet in altar")
	      || (str == "amulet in hole") || (str == "platinum amulet in hole"))
	    {
		if (P("platinum_amulet", TP))
		  {
		      write("You put the platinum amulet in the altar,"
			    + " the light streaming upwards changes to a glowing white!\n");
		      say(QCTNAME(TP) + " puts something in the altar.\n");
		      altar = 2;
		      if (ob = present("platinum_amulet", TP)); ob->remove_object();
		      if (ob = present("chrome_amulet", TP)); ob->remove_object();
		      return 1;
		  }
		return 0;
	    }
	  return 0;
      }
    return 0;
}

string
plaque()
{
    if (altar == 0)
      {
	  write("The plaque bears a symbol of a multicolour"
		+ " 5 headed dragon. Now that you look at it you think"
		+ " that it might come loose from the altar if you pulled"
		+ " it out.\n");
	  say(QCTNAME(TP) + " studies the plaque carefully.\n");
	  return "";
      }
    return "Examine what?\n";
}

string
ahole()
{
    if (altar == 1)
      {
	  write("The hole is quite small. You think that maybe"
		+ " something used to be in it, but has since been"
		+ " removed.\n");
	  say(QCTNAME(TP) + " studies the hole carefully.\n");
	  return "";
      }
    return "Examine what?\n";
}

string
gplaque()
{
    if (altar == 2)
      {
	  write("The amulet bears the symbol of paladine.\n");
	  say(QCTNAME(TP) + " studies the amulet carefully.\n");
	  return "";
      }
    return "Examine what?\n";
}

string
whichplaque()
{
    if (altar == 0)
      return plaque();
    if (altar == 2)
      return gplaque();
    return "Examine what?\n";
}

string
altar()
{
    write("The altar is obviously dedicated to the"
	  + " evil goddess Takhisis. Evil radiates from it"
	  + " filling your soul with dread. ");
    say(QCTNAME(TP) + " studies the altar carefully.\n");
    if (altar == 0)
      {
	  write("The altar has a small round chrome plated plaque "
		+ "type symbol imbedded in it.\n");
	  return "";
      }
    if (altar == 2)
      {
	  write("The altar has a small round platinum plated "
		+ "symbol imbeded in it.\n");
	  return "";
      }
    if (altar == 1)
      {
	  write("The altar has a small round hole in its front.\n");
	  return "";
      }
    return "";
}

string
blight()
{
    if (altar != 2)
      {
	  write("The black light streams upward from the centre"
		+ " of the altar, it appears to have no source and reaches right"
		+ " up to the cavern roof. It appears to have a diameter"
		+ " of about 1 foot.\n");
	  say(QCTNAME(TP) + " studies the black light carefully.\n");
	  return "";
      }
    return "Examine what?\n";
}

string
wlight()
{
    if (altar == 2)
      {
	  write("The white light streams upward from the centre"
		+ " of the altar, it appears to have no source and reaches right"
		+ " up to the cavern roof. It appears to have a diameter"
		+ " of about 1 foot.\n");
	  say(QCTNAME(TP) + " studies the white light carefully.\n");
	  return "";
      }
    return "Examine what?\n";
}

string
whichlight()
{
    if (altar == 0)
      return blight();
    if (altar == 2)
      return wlight();
    return "Examine what?\n";
}

string
floor()
{
    write("The floor is just normal earth, it is a bit muddy.\n");
    say(QCTNAME(TP) + " studies the floor carefully.\n");
    return "";
}

string
wall()
{
    write("The walls and the ceiling of the room are earthen though" +
	  " they appear to be sturdy enough.\n");
    say(QCTNAME(TP) + " studies the room carefully.\n");
    return "";
}


