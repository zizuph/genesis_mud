/**
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 */
    
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
inherit "/d/Krynn/std/room";

#define OBSOLETE_GUILD 0

void
reset_krynn_room()
{
}

void
create_krynn_room()
{
    set_long("You are at the entrance of a small wooden hut seated high up in the trees. "+
             "Here you can rest safely using one of the small bunks in here.\n");

    set_short("You are standing in the resting area in a small hut");


    add_item(({"hut", "wooden hut", "small hut", "small wooden hut"}),
               "This hut is used by the elite archers as a safe refuge.\n");
    add_item("trees", "The trees hide and carry the hut which you are standing in.\n");
    add_item(({"bunks", "bunk", "small bunk", "small bunks"}), "They do not look like the " +
               "most comfortable bed you have seen, but they should make do. You can " + 
               "use one of them by choosing to <start here>.\n");
    add_cmd_item("here", "start", "@@do_start");
    
    INSIDE;
    
    add_exit(ROOMS+"hut_board", "east", 0);
    add_exit(ROOMS+"entrance", "west", 0);
    reset_room();
}

int
do_start()
{
    if (TP->query_guild_name_occ() == "Ansalon Elvish Archers" ||
        TP->query_guild_name_lay() == "Ansalon Elvish Archers")
    {	
        TP->set_default_start_location(START_ROOM);
        write("You will start from here now any time you wake up.\n");
	return 1;
    }
    write("Only archers can start here.\n");
    return 1;
}

public status
update_player_guild(object player, int guild)
{
    object  shadow;
    int     result, stat;

    stat = player->stat_to_exp(player->query_stat(guild));
    
    write_file(MASTER_OB(this_object()), time() + " "
    + player->query_real_name() + " stat:" + guild + " exp:" + stat + "\n");
    
    if (file_name(environment(player)) == START_ROOM)
        player->move_living("M", "/d/Krynn/guilds/elven_archers/rooms/hut_entrance.c", 0, 0);
        
    if (player->query_default_start_location() == START_ROOM)
        player->set_default_start_location("/d/Krynn/guilds/elven_archers/rooms/hut_entrance.c");
    
    switch(guild)
    {
        case SS_OCCUP:
        player->remove_occ_member();
        shadow = clone_object("/d/Krynn/guilds/elven_archers/lib/occ_shadow.c");
        result = shadow->add_occ_shadow(player);
        "/d/Krynn/guilds/elven_archers/lib/options_manager"->set_option("LoreMasterTraining", player->query_real_name(), 90);
            break;
        case SS_LAYMAN:
        player->remove_lay_member();
        shadow = clone_object("/d/Krynn/guilds/elven_archers/lib/lay_shadow.c");
        result = shadow->add_lay_shadow(player);
            break;
    }
    
    if (result == 1)
    {
        player->set_guild_stat(guild, stat);
        return 1;
    }
    else
        write("An error has occured while moving you to the new guild, please "
        + "mail an error report with this number: " + result + " to Ansalon "
        + "and Krynn. Thank you!\n");
    
    return 0;
}