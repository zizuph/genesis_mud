/* Castle Gylar
 *
 *
 * Nerul 2021
 */
 
#include "../defs.h"
#include "../guild.h"
inherit STD_ROOM;


void
create_room()
{
	seteuid(getuid());
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
    
    set_long("Leaving the hallway behind, you step into a square, windowless "
	    +"room that looks like what used to be an armoury. Dimly lit by "
		+"a lantern on the south wall you are able to make out some shelves "
		+"and cupboards, and in the centre of the room a large wooden "
		+"apothecary desk littered with clutter. Behind the desk you "
		+"make out a hooded creature.\n");
		
    set_short("Inside a makeshift laboratory.");
    
    
   /* Object: lantern
An ordinary, dim lantern providing a minimum of illumination to the room.

Object: shelves
You see shelves containing books and laboratory equipment covering most 
of the walls in this room. There doesn’t seem to be any system to it, and hence 
you have a hard time gathering any useful intel by looking at them. Particularly 
in these lighting conditions.

Object: cupboards
You see a couple cupboards on the wall behind the desk. You get the distinct 
feeling that further investigation would require permission. 
 */
    
	add_exit(THEORDER_GUILD_DIR + "rooms/27", "west");
}


/*
 * Function name: do_join()
 * Description  : The function that adds a member of the guild.
 *
 */
int do_join(string str)
{
    object shadow_lay_cleric;
	object shadow_lay_melee;

    if (str == "cleric")
    {          
        if (this_player()->query_guild_name_lay())
        {
            write("Return when you have a vacant layman slot.\n");
                
            return 1;
        }
        
        if (THEORDER_MASTER->is_lay_theorder_melee(this_player()->query_name()))
        {
            write("You are already a member of The Order.\n");
            return 1;
        }
        
        if (THEORDER_MASTER->is_lay_theorder_cleric(this_player()->query_name()))
        {
            write("You are already a member of The Order.\n");
            return 1;
        }

        shadow_lay_cleric = clone_object(THEORDER_GUILD_DIR + "shadows/theorder_sh_lay_cleric.c");

        if (shadow_lay_cleric->shadow_me(this_player(), "layman", "cleric",
            THEORDER_GUILD_NAME_LAY_CLERIC) != 1)
        {
            write("Nothing happens.\n");
            return 1;
        }

        THEORDER_MASTER->add_lay_theorder_cleric(this_player()->query_name());
            
        write("Doubtfully, you still choose to make a pact with the unseen eldery lady "
        +"by accepting her offer to become a servant of her mysterious "
        +"coven!\n\nImmediately, you feel the doubts starts to build up, but "
        +"you are suddenly unable to move and flee from this cursed place! "
        +"Without warning, you feel for a brief moment a searing pain "
        +"in your heart as if a terrible curse has taken hold on "
        +"you!\n\nAn ebony-colored robe magically appear in your "
        +"inventory, reminding you that you are "
        +"now a new member and a fresh servant of a secret coven of Warlocks "
        +"in Faerun, run by the powerful Witch only known as the "
        +"Whispess!\n");

        write("\nThe tapestry that hangs on the north dirt wall suddenly "
        +"looks like a gate or a portal to you! Go north, servant!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        + " mumbles something, or "
        +"to someone here you can't see!\n", this_player());

        this_player()->update_hooks();

        return 1;
    }
	
	if (str == "melee")
    {          
        if (this_player()->query_guild_name_lay())
        {
            write("Return when you have a vacant layman slot.\n");
                
            return 1;
        }
        
        if (THEORDER_MASTER->is_lay_theorder_melee(this_player()->query_name()))
        {
            write("You are already a member of The Order.\n");
            return 1;
        }
        
        if (THEORDER_MASTER->is_lay_theorder_cleric(this_player()->query_name()))
        {
            write("You are already a member of The Order.\n");
            return 1;
        }

        shadow_lay_melee = clone_object(THEORDER_GUILD_DIR + "shadows/theorder_sh_lay_melee.c");

        if (shadow_lay_melee->shadow_me(this_player(), "layman", "figther",
            THEORDER_GUILD_NAME_LAY_MELEE) != 1)
        {
            write("Nothing happens.\n");
            return 1;
        }

        THEORDER_MASTER->add_lay_theorder_melee(this_player()->query_name());
            
        write("Doubtfully, you still choose to make a pact with the unseen eldery lady "
        +"by accepting her offer to become a servant of her mysterious "
        +"coven!\n\nImmediately, you feel the doubts starts to build up, but "
        +"you are suddenly unable to move and flee from this cursed place! "
        +"Without warning, you feel for a brief moment a searing pain "
        +"in your heart as if a terrible curse has taken hold on "
        +"you!\n\nAn ebony-colored robe magically appear in your "
        +"inventory, reminding you that you are "
        +"now a new member and a fresh servant of a secret coven of Warlocks "
        +"in Faerun, run by the powerful Witch only known as the "
        +"Whispess!\n");

        write("\nThe tapestry that hangs on the north dirt wall suddenly "
        +"looks like a gate or a portal to you! Go north, servant!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        + " mumbles something, or "
        +"to someone here you can't see!\n", this_player());

        this_player()->update_hooks();

        return 1;
    }
    
    write("What do you want to do here? Do you dare "
    +"to 'join <cleric | melee>' "
    +"with the unseen eldery lady in order to join her "
    +"mysterious coven?\n");
            
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

    if (str != "the order")
    {
        write("Do 'betray the order' if you want to "
        +"flee from the coven!\n");
        return 1;
    }

    if (this_player()->query_guild_name_lay() == THEORDER_GUILD_NAME_LAY_CLERIC)
    {
        write("You decide to break the pact you once made with the Whispess "
        +"and her coven of Warlocks!\nA terrible, rasping voice of an elderly "
        +"lady echoes through your head, saying: ... Flee, weakling! Do not Dare "
        +"to return here again anytime soon!\nSuddenly, you feel as if being "
        +"cursed and unwanted in this place!\n\nYou leave the Warlocks of "
        +"Faerun!\nYour robe fades away!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        +" openly breaks the pact, and leaves the Warlocks of "
        +"Faerun!\n", this_player());
        
        THEORDER_MASTER->remove_lay_theorder_cleric(this_player()->query_name());
		THEORDER_MASTER->remove_lay_theorder_melee(this_player()->query_name());
        
      
        this_player()->remove_guild_lay();

        this_player()->clear_guild_stat(SS_LAYMAN);

        this_player()->remove_cmdsoul("/d/Faerun/guilds/warlocks/souls/theorder_guild_soul_lay_melee");
		this_player()->remove_cmdsoul("/d/Faerun/guilds/warlocks/souls/theorder_guild_soul_lay_cleric");

        this_player()->set_default_start_location(this_player()->query_def_start());
        
        /* Remove any instances of the guild emblem on the player */    
        while (emblem = present("theorder_guild_object_lay_melee", this_player()))
        {
            emblem->remove_object();
        }
		
		while (emblem = present("theorder_guild_object_lay_cleric", this_player()))
        {
            emblem->remove_object();
        }
        
        this_player()->update_hooks();
        
        return 1;
    }

    write("You are not a member of The Order.\n");
 
    return 1;
}


void
init()
{
    ::init();

    add_action(do_join, "join");
    add_action(do_leave, "betray");
}
