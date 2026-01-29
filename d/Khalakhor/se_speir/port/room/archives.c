/**********************************************************************
 * - archives.c                                                     - *
 * -                                                                - *
 * - Created by Damaris@Genesis 01/2005                             - *
 **********************************************************************/


#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/notary/notary_service.h"
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

inherit "/d/Genesis/notary/notary_service";

/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
    return ({5, 3});
}
public int *
query_global_coords()
{
    return VILLAGE_COORDS;

}



void create_khalakhor_room()
{
    set_short("Archives of Genesis, Port Macdunn branch");
    set_long("   A spacious room lit by several globes of soft white "+
      "light. The general atmosphere suggests quietness and unhurriedness. "+
      "A counter runs around the two sides of the room, while the third "+
      "is devoted to several lecterns. A sign is posted on the wall "+
      "near the exit, and a large poster is pasted opposite it.\n");
    add_item(({"room", "area"}), query_long);
    
    add_item("ceiling","The ceiling is domed and quite high, the "+
      "sound, nevertheless does not reverberate much. Some "+
      "light is provided by globes hanging from the ceiling.\n");
    add_item("floor","The floor is made of alternating grey and "+
      "erubescent granite slabs, creating a large checkerboard "+
      "pattern. A large blue rug covers the floor near the counter.\n");
    add_item(({ "rug","carpet" }),"The thick large rug is of dark blue hue, "+
      "supresses the sound of footsteps quite effectively.\n");
    add_item(({ "walls", "wall", "panel","panels" }), "Walls of the room "+
      "are panelled wood of warm yellowish-brown hue.\n");
    add_item("bin","A small wooden bin stands on the counter. Upon "+
      "examination it appears to contain blank notarial forms that "+
      "you can get and use for preparing documents.\n");
    add_item(({ "globe", "globes" }),"Several globes hang down on long chains "+
      "from the high ceiling, emitting soft white light.\n");
    add_item(({ "notary", "notaries", "clerk", "clerks" }),"Several people "+
      "bustle around behind the counter, some of them reading through "+
      "papers, some writing documents, and some waiting for clients to "+
      "conduct business.\n");
    add_item("counter", "The polished wood counter runs across the two "+
      "sides of the room, the clerks sitting behind it. There is a "+
      "bin with blank notarial forms on the counter.\n");
    add_item(({ "lectern", "lecterns" }),"There are several dark oak reading "+
      "desks stationed along the wall, to help people conduct their notarial "+
      "business.\n");
        
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
    " -  The notary will check the form, and if everything is\n"+
    "    filled out correctly, you will get a prepared document,\n"+
    "    which needs only to be signed.\n"+
    " 8. sign form [fully] [for <guild>]\n"+
    "     \"fully\" - will include your titles in signature,\n"+
    "     \"for <guild>\" will make you sign for one of the guilds\n"+
    "     you are a member of. See also \"help form access\"\n"+
    " 9. submit form *\n"+
    " -  The submitted documents have a starting storage duration\n"+
    "    of 15 minutes, and can be extended by: \n"+
    "10. extend <document_number> for <period> *\n\n"+
    "* - service fees apply!!\n\n"+
    " Steps 2-6 and 8 can be done anywhere in the world,\n"+
    " as long as you carry the form.\n\n"+
    " To view the documents that are already in archive, <examine index>.\n\n"
    );
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 2);
   add_exit("/d/Khalakhor/se_speir/port/room/road_9_7", "south");
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
