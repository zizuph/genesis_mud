/*  Drac Bar */
/*  Theobald  */
/*   950907  */	

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tarsis/local.h"
#include <money.h>
#include <language.h>


inherit "/lib/pub";
inherit "/std/room";

#define LIV_PATH "/d/Krynn/tarsis/monster/"

void clone_tharok();

void
create_room()
{
 	set_short("This is the Drac Bar.\n");
   	set_long("You have now entered the Drac Bar. This bar is pretty " +
		"dirty, and you begin to wonder if your stomach and nose " +
		"can handle to eat in here. There is big counter in here " +
		"made of pure granit. You understand that if it were made " +
		"of something else it should hold for more than a few minutes. " +
		"Behind the counter stands a human and serves all the guests. " +
		"On the wall behind the counter there are a note.\n");
 	add_item("menu","This is the list of everything served in here. " +
		"Maybe you should read it !\n");
    	add_drink(({"drink","1","white drink"}),({"drink","white drink"})," ",20,10,24,"white drink",
		"white drinks","This is a Very cold drink, it is said that it is " +
		"cooled with the breath of a White dragon.\n",0);	
	add_drink(({"blue minth","2","minth"}),({"minth","blue minth"}),"refreshing",20,40,96,"blue minth","blue minths",
		"This is a very popular day after drink, both refreshing and a " +
		"way to get your hangover away.\n",0); 
	add_drink(({"black acid","3","acid"}),({"black acid","acid"})," ",20,50,144,"acid","acids"
		,"This schnaps is a real throath cleaner.\n",0);
	add_drink(({"red flame","4","flame"}),({"red flame","flame"}),"small",10,60,168,"schnaps off read flame",
		"schnapses of red flame","This is a burning drink, You have to be quick when you shall drink "+
		"it so you dont get burned.\n",0);
        add_drink(({"multicoulored death","5","death"}),({"multicoulored death","death"}),"tiny",10,80,300,"schnaps of death",
		"schnapses of death","Are you sure that you want to drink THIS !\n",0);	
	add_exit(TOWN + "tarsis4", "west");
	clone_tharok();
	reset();
}	
void
init()
{
	
	add_cmd_item(({"menu","note" }), ({"read","exa" }),
	"\nThese are the drinks we have in stock:\n\n" +
	"1. Ordinary white drink        24 cc\n" +
	"2. Blue minth                  96 cc\n" +
	"3. Black acid                  144 cc\n" +
	"4. Red flame                   168 cc\n" +
	"5. Multicolored death !       300 cc\n");
	::init_pub();
	::init();
}

void
clone_tharok()
{
object bartender;

bartender = clone_object(LIV_PATH + "tharok");
bartender->move(TO);
}