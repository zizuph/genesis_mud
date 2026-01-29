// file name: d/Avenir/common/outpost/tower_middle3.c
// creator(s):  Kazz    March '95
// note:   second floor in europe/third floor in us.
// last update: April 1995
//              Lilith, Apri 2022: updated for fort makeover
//                 This room looks like it  
//                 should be tower_middle2 but due to all of the 
//                 quest-related code, keeping the file-names.

# pragma strict_types
# include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Genesis/notary/notary_service.h" 
inherit "/d/Genesis/notary/notary_service";
inherit "/d/Avenir/common/outpost/fort_base";

void create_fort_room()
{
	add_exit("tower_middle2","up",0);
    add_exit("tower_middle1","down",0);
	add_exit("shop", "south", 0);
	
    add_fort_room();   
    add_exit_views();

    set_short("the second floor with Notary and Shop");
    set_long("Here, on the second floor of the fort's main tower, "+
	  "steep stone stairs lead up and down to the other floors. "+
      "Some crystal and copper wall lamps gently illuminate the room. "+
	  "Something that looks like a shop appears to be through "+
	  "a doorway to the south, while flames can be seen "+
	  "flickering through the narrow windows to the west. "+
      "A banner on the north wall indicates that you "+
      "are in one of the Sybarus branches of the Notary of Genesis. "+
      "A desk sits in the middle of the room, and it sports both a "+
      "sign on top and a poster affixed to its front.\n");
       
    add_item(({"desk", "stone desk" }), 
        "It is a desk made of stone. It provides ample space for "+
        "writing.\n");
    add_item(({"stone", "black stone"}), 
        "It is what it appears to be, nothing more, and nothing less.\n");
    add_item(({"north wall", "banner"}), 
        "It is a simple banner, which states in plain common:\n"+
        "  Welcome to the Sybarus branch of the Notary of Genesis\n");
    add_cmd_item(({"banner"}),"read", 
        "It is a simple banner, which states in plain common:\n"+
        "  Welcome to the Sybarus branch of the Notary of Genesis\n");
    add_cmd_item("sign",({ "exa", "read" }),N_SIGN_TEXT);
    add_cmd_item("poster",({ "exa", "read" }),
        "\n"+
        "Ten quick steps to Notarial Service usage:\n"+
        " 1. Get form\n"+
        " 2. Fill form title <document title>\n"+
        " 3. Fill form type <contract|order|agreement|etc.>\n"+
        " 4. Fill form access <private|guild|guildleader|public>\n"+        
        " 5. Fill form signers <signer name, ...>\n"+
        " 6. Fill form contents\n"+
        " 7. submit form *\n"+
        " - The notary will check the form, and if everything is "+
        "   filled out correctly,\nyou will get a prepared document, "+
        "   which needs only to be signed.\n"+
        " 8. Sign form [fully] [for <guild>]\n"+
        "     \"fully\" - will include your titles in signature,\n"+
        "     \"for <guild>\" will make you sign for one of the guilds\n"+
        "     you are a member of. See also \"help notary access\"\n"+
        " 9. Submit form *\n"+
        " - The submitted documents have a starting storage duration\n"+
        "   of 15 minutes, and can be extended by: \n"+
        "10. Extend <document_number> for <period> *\n\n"+
        "* - service fees apply!!\n\n"+
        " Steps 2-6 and 8 can be done anywhere in the world,\n"+
        " as long as you carry the form.\n\n"+
        " See also: \"help notary\", \"help form\" and examine the index "+
        "in your inventory.\n\n");

    add_item(({"stairs", "stair"}), 
      "Stairs made of basalt stone hug the walls. "+
      "One set rises up and the other, goes down.\n" );	
	add_item( ({ "west windows", "west facing windows", "west window"}), 
      "@@exa_window|You look through the window.\n|" + OUTPOST +"cave2@@");
	add_item( ({ "east windows", "east facing windows", "east window"}), 
      "@@exa_window|You look through the window.\n|" + OUTPOST +"fort2@@");
    add_item(({"windows", "window"}), "There are west windows "+
      "and east windows.\n");
    add_item(({"light", "firelight", "flames"}), 
      "The light in the room flickers a bit, likely coming from the huge "+
      "pools of flame by the outpost gate.\n" );
    add_item(({"tower", "black tower"}), 
      "The tower is made of the same black stone as much of the "+
      "fort. You are inside the south tower at "+
      "Fort Sybarus.\n");
	  
}


/*
 * Function name: exa_window
 * Description  : This lets people see the adjacent outside room.
 */
#define FILTER_SHOWN_COMPOSITE(x) \
    filter((x), &not() @ &->query_no_show_composite())
public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_LIVE(all_inventory(room))),
      this_player());
    in_room_o = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_DEAD(all_inventory(room))),
      this_player());

    write((room_file)->long());

    if (sizeof(in_room_p))
        this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p)) + 
          ".\n");

    if (sizeof(in_room_o))   
        this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ 
          ".\n");

    tell_room(ENV(TP), QCTNAME(TP) + " gazes through the window.\n", TP);

    return "";
} 
/* Notary-related */
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

