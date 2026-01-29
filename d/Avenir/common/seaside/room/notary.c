// file name: d/Avenir/common/outpost/fort8.c
// creator(s): Lilith June 2004
// last update:
// purpose:    Notary for the fort area
// note:	
// bug(s):
// to-do:       

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Genesis/notary/notary_service.h" 

inherit "/d/Genesis/notary/notary_service";
inherit "/std/room";

void
create_room()
{
    set_short("Notary of Genesis, Sybarus Fort branch");
    set_long("This building has been carefully constructed from the "+
        "black stone so abundant in the area. Many sconces have "+
        "lighted torches in them, creating more than enough illumination "+
        "to write by. A banner on the east wall indicates that you "+
        "are in one of the Sybarus branches of the Notary of Genesis. "+
        "A long counter cuts the room in half, and it sports both a "+
        "sign on top and a poster affixed to its front. Through the "+
        "open doorway you can see west into the center of the fort.\n");
       
    add_exit(OUTPOST + "fort5","west",0);

    add_item(({"counter", "long counter" }), 
        "It is a long counter, also made of stone, which cuts the "+
        "room in half and provides ample space for writing.\n");
    add_item(({"stone", "black stone"}), 
        "It is what it appears to be, northing more, and nothing less.\n");
    add_item(({"banner"}), 
        "It is a simple banner, which states in plain common:\n"+
        "  Welcome to the Sybarus branch of the Notary of Genesis\n");
    add_cmd_item(({"banner"}),"read", 
        "It is a simple banner, which states in plain common:\n"+
        "  Welcome to the Sybarus branch of the Notary of Genesis\n");
    add_item(({"tower", "black tower"}), 
        "The black tower rises high above you to the southeast.\n");
    add_item(({"archway", "doorway"}),
        "It provides entrance and exit to the fort.\n" );
    add_item(({"wall", "walls", "ceiling"}),
        "These nice, regular walls are made of stone quarried from "+
        "the walls of the cavern as the fort here was made.\n" );
    add_item(({"light", "torches", "sconces", "torch", "sconce"}),
        "It is very bright in here due to the large number of "+
        "lighted torches seated in sconces high up on the walls.\n" );
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
        "in your inventory.\n\n");

        LIGHT
        IN

} // create_room()

void 
init()
{
    ::init();
    init_notary_service();
}

void 
leave_inv(object who,object to)
{
    ::leave_inv(who,to);
    leave_inv_notary(who,to);
}

