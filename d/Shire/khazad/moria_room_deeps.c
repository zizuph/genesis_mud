/* The standard Field-of-Gondor-file, made by Elessar for Genesis
 *  February 1992. No copyrights, but would like to have my name
 *  mentioned if anyone modifies this file for own use.
 *  Totally changed to make it into a hobbit hole builder, by Elix 2-95       
 *  
 *  Used and modified for the deep tunnels in Khazad-dum. My thanks to the 
 *  previously mentioned people.
 *  Glaurung 1-27-96
 *
 *  Updated by Igneous.
 */ 

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

inherit "/d/Shire/khazad/moria_room";

// Global Vars
int roomtype, deep;
string extraline;

// Prototypes
string short_description();

void
set_extraline(string str)
{
    extraline = str; 
}

void
set_roomtype(int i)
{
    roomtype = i;
}

void
set_deep(int i)
{
    deep = i;
}

string
query_deep()
{
    switch (deep)
    {
    case 0:
	return "";
    case 1:
	return "first deep";
    case 2:
	return " second deep";
    case 3:
	return " third deep";
    case 4:
	return " fourth deep";
    case 5:
	return " fifth deep";
    case 6:
	return " sixth deep";
    case 7:
	return " seventh deep";
    default:
	return "underdeeps";
    }
}

// This is here so (hopefully) it is backwards compatable
void make_the_room() { this_object()->create_moria_room(); }

void create_deeps_room() {}

nomask void
create_moria_room()
{
    create_deeps_room();  

    set_short(short_description());
    set_long("@@long_description@@");

    // Place all common add_items that all the deeps should have here.

}

string
short_description()
{
    switch (roomtype)
    {
    case 0:
	add_item("tunnel",
	  "Dug out of the hard rock ages ago by the Dwarves of "+
	  "Khazad-dum.\n");
	add_item(({ "ground", "floor", "walls" }),
	  "Dull grey rock shaped by Dwarven hands long ago.\n");
	add_item(({ "beam", "beams" , "wooden beams" }),
	  "Thick logs wedged into place along the walls and ceiling. "+
	  "Most of them show some sign of decay.\n");
	add_item("riches",
	  "You search in vain for a while looking for long lost "+
	  "treasure. You find nothing.\n");
	return "A dark mining tunnel in the "+query_deep()+" of Khazad-dum";
    case 1:
	add_item(({ "room", "storeroom" }),
	  "Dug out og the hard rock ages ago by the Dwarves of "+
	  "Khazad-dum.\n");
	return "A dark room in the "+query_deep()+" of Khazad-dum";
    case 2:
	add_item("tunnel",
	  "Dug out of the hard rock ages ago by the Dwarves of "+
	  "Khazad-dum.\n");
	add_item(({ "ground", "floor", "walls" }),
	  "Dull grey rock shaped by Dwarven hands long ago.\n"); 
	add_item("riches",
	  "You search in vain for a while looking for long lost "+
	  "treasure. You find nothing.\n");
	add_item("darkness",
	  "Thousands of feet below the surface the darkness seems to "+
	  "exudes a malevolent aura.\n");
	return "A gloomy passage in the "+query_deep()+" of Khazad-dum";
    case 3:
	add_item("tunnel",
	  "Dug out of the hard rock ages ago by the dwarves of "+
	  "Khazad-dum.\n");
	return "A narrow passage in the "+query_deep()+" of Khazad-dum";
    case 4:
	add_item("tunnel",
	  "Dug out of the hard rock ages ago by "+
	  "the Dwarves of Khazad-dum.\n");
	add_item(({ "ground", "floor", "walls" }),
	  "Dull grey rock shaped by Dwarven hands long ago.\n");
	return "A shallow slope in the "+query_deep()+" of Khazad-dum";
    case 5:
	add_item("tunnel",
	  "Dug out of the hard rock ages ago by the Dwarves of "+
	  "Khazad-dum.\n");
	return "A sharp descent in the "+query_deep()+" of Khazad-dum";
    case 6:
	add_item("chasm",
	  "Black and seemingly endless.\n");
	return "A slender ledge in the "+query_deep()+" of Khazad-dum";
    case 7:
	add_item("tunnel",
	  "Dug out of the hard rock ages ago by "+
	  "the Dwarves of Khazad-dum.\n");
	add_item(({ "ground", "floor", "walls" }),
	  "Dull grey rock shaped by Dwarven hands long ago.\n");
	return "A junction deep within the "+query_deep()+" of Khazad-dum";
    case 8:
	add_item("tunnel",
	  "Dug out of the hard rock ages ago by "+
	  "the Dwarves of Khazad-dum.\n");
	add_item(({ "ground", "floor", "walls" }),
	  "Dull grey rock shaped by Dwarven hands long ago.\n");
	return "A straight tunnel in the "+query_deep()+" of Khazad-dum";
    }
}

string
long_description()
{
    string long = CAP(short()) + ".  ";

    switch (roomtype)
    {
    case 0:
	long += "This long abandoned mining tunnel is barren and shows no "+
	"sign of the riches it once held. Like a frame large wooden "+
	"beams run across the ceiling and up the walls here lending "+
	"support to what might otherwise be an unstable tunnel.";

	break;
    case 1:
	long += "This ancient storeroom is empty.";
	break;
    case 2:
	long += "The tunnel widens a great deal here and you briefly feel "+
	"a twinge of fear as you are engulfed by the oppresive, "+
	"silent darkness. From what you can see this tunnel, long "+
	"abandoned by Dwarves, is barren of the riches it once "+
	"held.";

	break;      
    case 3:
	long += "The tunnel narrows considerably here.";
	break;
    case 5:
	long += "A distinct warmth can be felt coming from "+
	"the descending tunnel.";
	break;
    case 6:
	long += "You stand at the edge of a vast chasm.";
	break;
    case 4:
    case 7:
    case 8:
	long += "This long abandoned mining tunnel is barren "+
	"and shows no sign of the riches it once held.";
	break;
    default:
	long += "This should never happen.";
    }
    if (extraline)
    {
	long += "  " + this_object()->check_call(extraline);
    }
    return long + "\n";
}

void
enter_inv(object ob, object from)
{
    int PANIC = 0;
    int MY_DIS = ob->query_stat(SS_DIS);
    ::enter_inv(ob, from);

    if (!living(ob))
	return;

    else
    {
	PANIC = 160 - MY_DIS;
	if (PANIC <= 0)
	    return;

	else
	    ob->add_panic(PANIC);
    }
}
