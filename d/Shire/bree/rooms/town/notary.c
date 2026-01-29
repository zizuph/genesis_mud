/*
 * The Bree Notary office
 * by Finwe, June 2002
 */
#include "/sys/stdproperties.h"
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include "/d/Genesis/notary/notary_service.h"

inherit "/d/Genesis/notary/notary_service";
inherit "/d/Shire/std/room";

void create_room()
{

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    set_short("Archives of Genesis, Bree branch");
    set_long("This is a large, spacious room above the post office. The " +
        "atmosphere is quiet and relaxed. People come to have offical " +
        "documents certified that they are authentic or to view other " +
        "documents. A counter runs around the two sides of the room, " +
        "while the third is devoted to several lecterns. A sign and a " +
        "plaque are posted on the wall near the exit, and a large " +
        "poster is pasted opposite it.\n");
	
    add_item("bin",
        "A small wooden bin stands on the counter. It appears to contain " +
        "blank notarial forms that can be used for preparing documents.\n");
	add_item(({"counter"}),
	    "It is made of heavy wood and runs around three sides of the " +
        "room. It is stained a deep brown and polished.\n");
	add_item(({"lecturns", "lecturn"}),
	    "These are small desks that sit on one of the counters. Several " +
        "documents are spread across them.\n");
    add_item(({"documents", "papers"}),
        "They are made of parchments and spread across the lecturns. " +
        "You may read them if you 'list all' or 'exa index'.\n");
        
    add_cmd_item("sign",({ "exa", "read" }),N_SIGN_TEXT);
    add_cmd_item("plaque",({ "exa", "read" }),
        "\n" + 
        "You may see what documents may be read if you 'list all' or " +
        "'exa index'.\n");

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
    "in your inventory.\n\n");

    add_exit(TOWN_DIR + "post","down");

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

