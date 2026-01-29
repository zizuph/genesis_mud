/*
*   /d/Faerun/phlan/rooms/phlanbank.c
*
*   modified by Tharizdun, 2021
 * Nov hut for bank
 * -- Finwe, November 2007
 */
 
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_PHLAN_INDOOR;
inherit "/lib/bank";

/*
*   Check to see if player is on quest
*/

int
check_quest()
{
    if(this_player()->query_prop("_phlan_tour1_start"))
    {
        this_player()->remove_prop("_phlan_tour1_start");
        this_player()->catch_msg("You are ready to return to Daari for your reward.\n");
        this_player()->add_prop("_phlan_tour1_prop", 1);        
        return 0;
    }
}  

public void
create_phlan_room()
{

    set_short("The bank of Phlan");
    set_long("This bank is strongly built and secure. Two barred windows"
    +" face the street to the west. The walls are unadorned except for a plaque"
    +" explaining how to use the bank. An oil lamp suspended from the ceiling"
    +" supplements the light coming through the windows. The floor is plain"
    +" stone and swept clean. A gnomish teller sits behind a counter greedily"
    +" processing transations. The doorway back to the street is in the western"
    +" wall.");

    add_item(({"wall", "walls"}),
        "They are thick oak planks, secured to beams of the same material by"
        +" square headed iron nails. The western wall has two barred windows"
        +" and the doorway leading back to the street.\n");
        
    add_item(({"plank", "planks"}),
        "They are six inches wide and probably at least half that thick."
        +" Stout oak, it would take a company of axemen or an angry giant"
        +" to breach them. They are securely attached to a framework of"
        +" oak beams by iron nails.\n");     

    add_item(({"nail", "nails", "iron nail", "iron nails", "square headed iron nails"}),
        "The square heads of these nails measure a full inch across. No common"
        +" carpentry hammer drove these spikes home and no mere crowbar"
        +" will pull them out.\n");         
        
    add_item(({"doorway"}),
        "The doorway to the west leads back to the street.\n");
        
    add_item(({"window", "windows"}),
        "There are two windows facing the street in the western wall. They"
        +" both are secured with iron bars.\n");     

    add_item(({"bar", "bars", "barred window", "barred windows"}),
        "The black iron bars are firmly mounted to the window frames"
        +" preventing any unwarranted entrance. The bars are an inch"
        +" thick with only three inches between them.\n");          
        
    add_item(({"ceiling"}),
        "The ceiling is peaked and supported by strong beams. A silver oil lamp"
        +" hangs from one of the cross beams.\n");
        
    add_item(({"beam", "beams"}),
        "These oak beams are six inches square and provide the framework to which"
        +" the planks are secured by square headed iron nails.\n");
        
    add_item(({"lamp"}),
        "The lamp is of gleaming silver, indicating that this bank makes"
        +" a decent profit. It hangs motionlessly, dispelling any shadows.\n");

    add_item(({"floor", "ground", "slate"}),
        "The floor is of smooth grey slate. It is swept spotless as only a"
        +" meticulous gnome could accomplish.\n");
        
    add_item(({"counter"}),
        "A sturdy teak counter chased in silver. The rich brown of the wood"
        +" offset by the brilliance of the metal. It seems to glow with a"
        +" protective magical force. You would not think of trying to commit"
        +" an unlawful act on its surface.\n");
        
    add_item(({"gnome"}),
    "A short, fat, greedy gnome stands behind the counter. You notice a ledge or step"
    +" that he is standing on to be able to see over top of it. His hair is elaborately"
    +" styled and powdwered and he sports an impeccably waxed mustache of the same"
    +" powdered white.\n");
    
    add_item(({"ledge", "step"}),
    "A wooden riser fourteen inches tall that allows the gnome to see over the counter.\n");  
    
    object deposit = clone_object("/d/Genesis/obj/deposit");

    deposit->set_bank_id(5202, "Bank of Phlan");
    deposit->move(this_object(), 1);

    add_prop(ROOM_S_MAP_FILE, "phlan_map.txt");

    config_default_trade();
    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");    

/* Set the exchange fee (% of changed amount)
*
* IMPORTANT
* This needs to be called *before* config_trade_data() is called
* or else the fee will not be taken out.
*/
     
    set_bank_fee(14);
    
/*
*  Initialize bank
*/

    config_trade_data();    

/*
*   Room protections
*/

   add_prop(ROOM_I_NO_ALLOW_STEED, 1);
   add_prop(ROOM_I_NO_TELEPORT, 1);
   add_prop(ROOM_M_NO_TELEPORT_TO, 1);
   add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
   add_prop(ROOM_I_NO_SCRY, "You focus on finding your "
   +"target but are suddenly overcome by a vision of black nothingness.\n");
   
/*
*   Sound effects
*
*/   

    set_room_tell_time(200);
    add_room_tell("The gnome rubs his chubby fingers lovingly over the counter.");
    add_room_tell("A customer walks in, makes a quick transaction and walks back out.");
    add_room_tell("The gnome steps off his ledge, momentarily disappearing"
        +" behind the counter.");
    add_room_tell("A city guard looks in the door and then continues her patrol.");
    add_room_tell("A loud group of pedestrians walk past the door.");

    add_exit(ROOM_DIR + "road14", "west");

    reset_faerun_room();
}

void
reset_faerun_room()
{
}

void
init()
{
 /* 
 *  Add the bank commands 
 */   
    ::init();

    bank_init();
}

