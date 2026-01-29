/***
 * Notarial room.
 * Rooms as this is what people can use to put in their own domains
 * or they can inherit "notary/room" and write their own custom rooms.
 *   2003-10-18 by Dargoth
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/notary/notary_service.h"

inherit "/std/room";
inherit "/d/Genesis/notary/notary_service";

void create_room()
{
	set_short("Archives of Genesis, Tyr branch");
	set_long("A long and narrow room, its cool marble floor and white walls "+
	"provide some relief from the Athasian weather outside. Several narrow windows "+
	"are set in the eastern wall, draped with curtains, they do not let in the "+
	"oppressive heat of the sun. A counter runs along the wall, and some people "+
	"are sitting behind it.\n");
    
    add_item(({"wall", "walls" }),"The walls are thick stone and whitewashed, "+
    	"providing excellent heat protection and making them actually cool to "+
    	"touch, despite the heat outside.\n");
   
   add_item("ceiling", "The bare whitewashed ceiling hangs rather low, "+
   	   "yet high enough so that even tallest of customers do not "+
   	   "have to bend their heads.\n");
   
   add_item("floor","The floor has been made of large polished marble slabs, "+
   	   "white veins running through various shades of green background. It reflects "+
   	   "such light as passes through windows.\n");
   
   add_item(({ "window","windows" }),"The narrow windows of this room are like "+
   	   "slits of light, the heat and shine of the Athasian sun passing through "+
   	   "them in dazzling beams. Curtains hang in front of the windows, softening "+
   	   "the light to a great degree.\n");
   	   
   	add_item(({"curtain", "curtains"}), "Light yet thick they hang in front "+
   		"of the windows, absorbing and reflecting most of the light passing "+
   		"through them.\n");
   	      	
    add_item("bin","A small wooden bin stands on the counter. Upon "+
		"examination it appears to contain blank notarial forms that "+
		"you can get and use for preparing documents.\n");
	
    add_item(({ "globe", "globes" }),"Several globes hang down on long chains "+
        "from the high ceiling, emitting soft white light.\n");
        
    add_item(({ "notary", "notaries", "clerk", "clerks", "people" }),"Several people "+
		"bustle around behind the counter, some of them reading through "+
		"papers, some writing documents, and some waiting for clients to "+
		"conduct business.\n");
		
	add_item("counter", "The polished wood counter runs along the long "+
		"side of the room, dividing it in the eastern and western part. "+
		"There are some clerks sitting behind it. There is a "+
        "bin with blank notarial forms on the counter.\n");

    add_cmd_item("sign",({ "exa", "read" }),N_SIGN_TEXT);
    
    add_cmd_item("poster",({ "exa", "read" }),
    "\n"+
    "Ten quick steps to Notarial Service usage:\n"+
    " 1. get form\n"+
    " 2. fill form title <document title>\n"+
    " 3. fill form type <contract|order|agreement|etc.>\n"+
    " 4. fill form access <private|guild|guildleader|public>\n"+        
    " 5. fill form signers <signer name, ...>\n"+
    " 6. fill form contents\n"+
    " 7. submit form *\n"+
    " - The notary will check the form, and if everything is "+
    "   filled out correctly,\nyou will get a prepared document, "+
    "   which needs only to be signed.\n"+
    " 8. sign form [fully] [for <guild>]\n"+
    "     \"fully\" - will include your titles in signature,\n"+
    "     \"for <guild>\" will make you sign for one of the guilds\n"+
    "     you are a member of. See also \"help form access\"\n"+
    " 9. submit form *\n"+
    " - The submitted documents have a starting storage duration\n"+
    "   of 15 minutes, and can be extended by: \n"+
    "10. extend <document_number> for <period> *\n\n"+
    "* - service fees apply!!\n\n"+
    " Steps 2-6 and 8 can be done anywhere in the world,\n"+
    " as long as you carry the form.\n\n"+
    " See also: \"help notary\", \"help form\" and examine the index "+
    "in your inventory.\n\n"
    );
    add_exit("/d/Cirath/tyr/noble/rd_hr_02", "east");
}


void init()
{
    ::init();
    init_notary_service();
}

void leave_inv(object who,object to)
{
	::leave_inv(who,to);
	leave_inv_notary(who,to);
}

