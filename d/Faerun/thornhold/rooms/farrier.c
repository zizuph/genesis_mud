/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
//#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;

int ingot_found = 0;
object ingot;

object farrier_npc;

void
create_house()
{
	add_prop(ROOM_I_ALLOW_STEED, 1); // It's a stable so make an exception

    set_short("Farrier");
    set_long("Hay is scattered on the floor of this " +
    		 "stone room. A brass lantern is suspended by a chain from " +
             "the ceiling. The room is also illuminated by hot " +
             "orange light from a small forge, " +
             "adjacent to which sits a steel anvil and a " +
             "quenching barrel. The forge must be used for crafting " +
             "horseshoes and tack, for from the various " +
             "equestrian items on display here, you are clearly " +
             "in a farrier's workshop. While not a full " +
             "blacksmith operation, you suspect the farrier " +
             "may be able to <sharpen> your weapons for a fee.\n");

	add_item("hay",
            "Hay is scattered thinly over the stone floor of the " +
            "farrier's workshop.\n");

	add_item(({"steel anvil", "anvil" }),
            "It's a standard steel anvil, used for hammering metal " +
            "into shape.\n");
    
    add_item("forge",
            "This forge is built of solid, dwarf-hewn stone, with a " +
            "chimney that vents up through the ceiling. It is roaring " +        
            "red hot, and next to it rest bellows, tongs, and a pile " +
            "of raw materials.\n");
    
    add_item(({ "orange light", "hot orange light" }),
    		"This is one hot fire! Careful, don't get too close.\n");

    add_item("bellows",
            "Standard bellows, used by the farrier to keep the forge " +
            "fire burning hot.\n");
    
    add_item("tongs",
            "These tongs are used by the farrier to hold metal to the " +
            "fire.\n");
            
    add_item("chimney",
            "The chimney reaches up to the ceiling, venting heat. Seen " +
            "from the exterior, it is likely twin to the alehouse " +
            "chimney directly across the courtyard.\n");

    add_item("materials",
            "Next to the forge you see a pile of various raw materials " +
            "and discarded metal items for use by the farrier for " + 
            "crafting and repairs.\n");

    add_item(({ "farriers workshop", "workshop", "stone room", "room" }),
   			 "Hay is scattered on the floor of this " +
    		 "stone room. A brass lantern is suspended by a chain from " +
             "the ceiling. The room is also illuminated by hot " +
             "orange light from a small forge, " +
             "adjacent to which sits a steel anvil and a " +
             "quenching barrel. The forge must be used for crafting " +
             "horseshoes and tack, for from the various " +
             "equestrian items on display here, you are clearly " +
             "in a farrier's workshop. While not a full " +
             "blacksmith operation, you suspect the farrier " +
             "may be able to <sharpen> your weapons for a fee.\n");
             
    add_item("sharpen","Just type: sharpen <weapon>.\n");
            
// this sets up the search routine to find 
// something in the pile of materials

    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN,"my_search");
    
    add_exit(ROOM_DIR + "stables",  "south");

    reset_room();
}

void
reset_room()
{
   ::reset_room();
   ingot_found = 0;
   
   setuid(); 
   seteuid(getuid());
    
    if ((!farrier_npc))
    {
        farrier_npc = clone_object(NPC_DIR + "farrier");
        farrier_npc->move(this_object()); 
    }

}

mixed
my_search(object searcher , string str)
{
    int awareness;
    
    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < 13) 
    {
        return 0;
    }
    if(str=="pile" || str=="materials" || str=="metal")
    {
        if(ingot_found == 1)
        {
            return "You found nothing useful in the pile, though you " +         
            "note the diverse assortment of metals. The farrier must " +
            "cycle through different metals periodically.\n";
        }
        else
        {
            if(!QUEST_MASTER->check_ingot(searcher))
            {
                seteuid(getuid(TO));
                ingot = clone_object("/d/Faerun/thornhold/obj/ingot.c");
                ingot->move(searcher,1);
                say(QCTNAME(searcher)+ " finds something among the raw "+
                " materials.\n");
                ingot_found = 1;
                return "You fetch a " + ingot->short() + 
                " from the pile!\n";
            }
            else
            {
                say(QCTNAME(searcher)+ " searches among the raw "+
                " materials.\n");
                return "You decide not to take a second ingot " +
                "from the pile!\n";
            }
        }            
        
      return "You found nothing useful.\n";
    }
    else
    {
        return ;
    }
}