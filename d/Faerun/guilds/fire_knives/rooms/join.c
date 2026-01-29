/* /d/Faerun/guilds/fire_knives/rooms/join.c
 *
 * TEST JOINING ROOM. NOT PART OF THE GUILD HALL.
 *
 * Nerull, 2018
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

public int
into_shaft()
{
    write("\n\nYou climb up the improvised rope ladder "
    +"and enter the dark hole in the "
    +"soft ceiling.\n\n");
        
    return 0;
}


public int
into_guild()
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()))
    {
        write("\n\nWelcome, assassin!\n\n");
        
        return 0;
    }
    
    write("Only members of the Fire Knives may go further north.\n");
        
    return 1;
}


/*
 * Function name: do_join()
 * Description  : The function that adds a member of the guild.
 *
 */
int do_join(string str)
{
    object shadow_occ;
    
    object tokena;
        
    // Joining using the OCC slot
    if (str == "a fire knife")
    {   
        /*if (!this_player()->query_prop(I_CAN_JOIN_FIREKNIVES))
        {
            write("You have no permission to join the Fire Knives.\n");
                
            return 1;
        }*/
              
        if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()))
        {
            write("You are already a member of the Fire Knives.\n");
            return 1;
        }
        
        if (this_player()->query_average() < REQ_AVG)
        {
            write("You feel you are not quite yet to join this "
            +"outfit. Return later when you have grown some more.\n");
            
            return 1;        
        }
        
        if (this_player()->query_guild_name_occ())
        {
            write("Return when you have a vacant occupational slot.\n");
                
            return 1;
        }
       
        shadow_occ = clone_object(FIREKNIVES_GUILD_DIR 
        + "shadows/fireknives_sh_occ.c");

        if (shadow_occ->shadow_me(this_player(), "occupational", "rogue", 
        FIREKNIVES_GUILD_NAME) != 1)
        {
            write("You try to join the Fire Knives, but nothing happens.\n");
            return 1;
        }

        FIREKNIVES_MASTER->add_occ_fireknife(this_player()->query_name());
        FIREKNIVES_MAPPINGS->set_assassin_rank(this_player()->query_name(),1);
        FIREKNIVES_MAPPINGS->set_assassin_gauge(this_player()->query_name(),1);
            
        write("You join the Fire Knives.\n");

        tell_room(environment(this_player()), this_player()->query_name()
        + " joins the Fire Knives.\n", this_player());
        
        /*if (!present("nopatron_guild_object", this_player()))
        {
            clone_object(GUILD_ITEM4)->move(this_player(), 1);
        }*/

        this_player()->update_hooks();
            
        return 1;
    }
    
    write("What do you want to do here? Try to "
    +"<become a fire knife> if that is what you want to do.\n");
            
    return 1;
}


/*
 * Function name: do_leave()
 * Description  : The function that removes a member of the guild.
 *
 */
int
do_leave(string str)
{
    object emblem;

    if (str != "the outfit")
    {
        write("Do 'betray the outfit' if you want to "
        +"flee from the Fire Knives!\n");
        return 1;
    }

   // if (this_player()->query_guild_name_occ() == FIREKNIVES_GUILD_NAME)
    //{
        write("You decide to break the pact you once made with the Whispess "
        +"and her coven of Warlocks!\nA terrible, rasping voice of an elderly "
        +"lady echoes through your head, saying: ... Flee, weakling! Do not Dare "
        +"to return here again anytime soon!\nSuddenly, you feel as if being "
        +"cursed and unwanted in this place!\n\nYou leave the Warlocks of "
        +"Faerun!\nYour robe fades away!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        +" openly breaks the pact, and leaves the Warlocks of "
        +"Faerun!\n", this_player());
        
        // Removes patron 
        FIREKNIVES_MAPPINGS->clean_assassin_rank(this_player()->query_name());
        FIREKNIVES_MAPPINGS->clean_assassin_gauge(this_player()->query_name());
        FIREKNIVES_MASTER->remove_occ_fireknife(this_player()->query_name());
        
        FIREKNIVES_MASTER->remove_occ_boss_fireknife(this_player()->query_name());
        FIREKNIVES_MASTER->remove_occ_leadership_fireknife(this_player()->query_name());
        
        //WARLOCK_MAPPINGS->clean_desecration_power(this_player()->query_name());
        
        this_player()->remove_guild_occ();

        this_player()->clear_guild_stat(SS_OCCUP);

        this_player()->remove_cmdsoul("/d/Faerun/guilds/fire_knives/souls/fireknives_guild_soul");

        this_player()->set_default_start_location(this_player()->query_def_start());
        
        /* Remove any instances of the guild emblem on the player */    
        /*while (emblem = present(GUILD_ITEM_NAME, this_player()))
        {
            emblem->remove_object();
        }*/
        
        this_player()->update_hooks();
        
        return 1;
   // }

    write("You are not a member of the "+ FIREKNIVES_GUILD_NAME + ".\n");
 
    return 1;
}


/*
 * Function name: create_guildhall_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_fireknives_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    set_short("In a murky water infested underground earth cavity");
    
    set_long("You are inside a murky water infested underground "
    +"earth cavity. Stinking swamp water constantly trickles in from "
    +"the rough root-infested dirt walls, forming a pool of muddy water "
    +"that cover your feet. The reek of decaying stagnant matter is "
    +"almost unbearable here, but the curious presence of a large tapestry "
    +"covering the north wall makes you almost forgetful about "
    +"it. An improvised rope ladder makes it possible to climb "
    +"back out of this dreadful underground swamp cavity.\n");
    
    add_item(({"sinew"}),
        "Strong sinews from animals maybe, keeping the large "
        +"tapestry from falling into the muddy pool "
        +"of swamp water.\n");
        
    add_item(({"finger imprints", "prints", "finger prints"}),
        "It looks like imprints from different humanoids. You "
        +"conclude that someone tried to touch the blood stain for "
        +"some obscure reason.\n");
        
    add_item(({"red blood stain", "blood stain", "stain", 
    "red stain"}),
        "At the left bottom corner of the large tapestry, there "
        +"is a red blood stain. Near and around it, you "
        +"see finger imprints, as if somebody has touched "
        +"it...\n");
        
    add_item(({"cave", "cavity"}),
        "This whole reeking place looks roughly excavated by manual "
        +"labour. Meshes of strong roots cover the moist "
        +"dirt walls and ceiling, preventing immediate "
        +"collapse.\n");
        
    add_item(({"patterns", "colour", "colour patterns", "circles",
    "random circles"}),
        "The large tapestry depicts a series of random circles "
        +"and shapes of read, blue, yellow and violet colours. "
        +"They are vague in appearance, but don't mean anything "
        +"to you.\n");
    
    add_item(({"up", "ceiling", "roof", "soft ceiling"}),
        "Clad with a mesh of strong roots, the soft earth ceiling is " 
        +"barely kept from caving in. It is saturated by stinking "
        +"swamp water from above.\n");
        
    add_item(({"root", "roots", "strong roots", "mesh", "mesh of roots"}),
        "While everything else in this underground cavity seems loose "
        +"and nearly to give in at any moment, the exception is the "
        +"myriad of roots that form a protective strong mesh that "
        +"keeps it all together. It's as if some strong ancient "
        +"magic is at work here.\n");
        
    add_item(({"walls", "wall", "soft walls", "dirt wall", "dirt walls"}),
        "The walls consist of soft soaked dirt. Swamp water trickles in "
        +"from nearly everywhere, but meshes of roots keeps them from "
        +"caving in.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "central", "north", into_guild);
    add_exit(FIREKNIVES_ROOMS_DIR + "shaft2", "up", into_shaft);
    
    reset_faerun_room();
}


void
reset_faerun_room()
{
}


void
init()
{
    ::init();

    add_action(do_join, "become");
    add_action(do_leave, "betray");
}

