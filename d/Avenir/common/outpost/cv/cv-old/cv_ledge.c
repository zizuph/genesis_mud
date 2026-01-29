/* cv_ledge
 * Lilith Oct 2021
 * A coven entrance for the Faerun Vampires.
 *
 */
#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/vampires/guild.h";
inherit VAMPIRES_STD_ROOM;

#define CONNECTION "/d/Avenir/common/outpost/secret/stair_top"

/*
 * When you look into the abyss, the abyss may look back
 * into you ;)
 */
string
see_abyss()
{
    TP->add_panic(40);
    say(QCTNAME(TP) + " stares into the abyss.\n");
    return "";
}


public int
block_check()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
	{          
        if (VAMPIRES_MASTER->is_coven2_member(this_player()->query_name()) == 1)
        { 
            return 0;
        }
        
        if (VAMPIRES_MASTER->no_coven2_master() == 1)
        {
            if (VAMPIRES_MAPPINGS->query_vampires_rank(this_player()->query_name()) >= 2)
            {
                return 0;
            }
        }
    }        
    
    write("There is no obvious exit north.\n");   
    return 1;
}

/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    add_prop(ROOM_I_INSIDE, 1);
	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.
    set_short("beneath the bridge");
    set_long("You are under the bridge that crosses the abyss, "+
        "clinging to the massive footings that carry its weight "+
        "into the chasm wall. It looks like there is nowhere else "+
        "to go but back to the east, where the ledge widens.\n");
    add_item(({"bridge", "underside", "footing", "footings", "base"}),
        "The bridge appears to be sound, and the immense footings "+
        "do not appear to be in any danger of being dislodged.\n");
    add_item(({"abyss", "down", "lava", "lava flow"}), 
        "You stare down into the fiery abyss. The abyss looks "+
        "back into you.\n"+ VBFC_ME("see_abyss"));
    add_item(({"ledge", "east"}), "The ledge rapidly widens as "+
        "as it leads east, out from under the bridge. The ledge "+
		"supports the massive footings which angle into the wall "+
		"of the abyss.\n");
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

	add_exit(CONNECTION, "east", 0);
	// non-obvious
    add_exit("room1", "north", block_check, 0, 1); 
 
    reset_faerun_room();
	
}



void
do_whispers()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
	{          
        if (VAMPIRES_MASTER->no_coven2_master() == 1)
        {
            if (VAMPIRES_MAPPINGS->query_vampires_rank(this_player()->query_name()) >= 2)
            {
                this_player()->catch_tell(">>\nYou sense that a vampire "
                +"coven is located near here, and that if you will it, you "
                +"can pass through the wall to the north.<<\n");
                
                return;
            }
        }
    }        
 
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        set_alarm(0.2, 0.0, &do_whispers());
    }
}


public void
init()
{
    ::init();
}

