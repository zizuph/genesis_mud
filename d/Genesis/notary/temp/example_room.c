/***
 * Notarial room.
 * Rooms as this is what people can use to put in their own domains
 * or they can inherit "notary/room" and write their own custom rooms.
 *   2003-08-06 by Dargoth
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/notary/notary_service.h"

inherit "/std/room";
inherit "/d/Genesis/notary/notary_service";

void create_room()
{
    set_short("Archives of Genesis, Sparkle branch");
	set_long("A spacious room lit by several globes of soft white light. "+
        "The general atmosphere suggests quietness and unhurriedness. "+
        "A counter runs around the two sides of the room, while the third "+
        "is devoted to several lecterns. A sign is posted on the wall "+
        "near the exit, and a large poster is pasted opposite it.\n");

    add_exit("/d/Genesis/start/human/town/road1","east");

	
    add_item("bin","A small wooden bin stands on the counter. Upon "+
		"examination it appears to contain blank notarial forms that "+
		"you can get and use for preparing documents.\n");
	
        
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
    "     you are a member of. See also \"help notary access\"\n"+
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

