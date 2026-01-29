/*  /d/Faerun/guilds/black_flame/obj/scarab.c
 *
 *  Scarab token.
 *
 *  Nerull, 2022
 *
 */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h";
//#include "../blacklist.h";

int nodenr = 0;


int
no_drop()
{
}


int
do_destroy(string str)
{
    if (str == "scarab")
    {
        write("You destroy your scarab!\n");

        remove_object();
        
        return 1;
    }
    
    return 0;
}


int
place_scarab(string str)
{
    setuid();
    seteuid(getuid());
    
    if (str == "scarab")
    {
        // We try to avoid parking coffins in instances.
        if (MASTER_OB(environment(this_player())) != file_name(environment(this_player())))
        {
            write("You sense that this location is not fit "
            +"for a scarab. Look elsewhere for a more suited location.\n");
            
            return 1;
        }
        
        /*if (member_array(MASTER_OB(environment(this_player())), blacklisted_locations) >= 0)
        {
            write("You sense that this location is not fit "
            +"for a scarab. Look elsewhere for a more suited location.\n");
            
            return 1;
        }*/
        
        if (environment(this_player())->query_prop(ROOM_I_TYPE) == 2)
        {
            if (member_array("down", environment(this_player())->query_exit_cmds() != -1))
            {
                write("The scarab requires solid ground or bedrock. You "
                +"can't place it here.\n");
            
                return 1;
            }
        }
        
        
        if (present("_bf_scarab", (environment(this_player()))))
        {
            write("A scarab is present here already.\n");
            
            return 1;
        }
		
		
		
		nodenr = BF_MAPPINGS->query_bf_nodes(this_player()->query_name());
		
		/*if (nodenr >= MAXNODES)
		{
			write("You can't have more than "+MAXNODES+" deployed at "
			+"any time!\n");
			
			return 1;
		}*/
        
        write("You activate and hide the scarab here in the room! "+nodenr+".\n");
        
        object scarab=clone_object(BF_GUILD_DIR +"obj/scarab_token");
			
        scarab->set_owner(this_player()->query_name()); 
        
        scarab->move(environment(this_player()), 1);
		
		
		nodenr = nodenr + 1;
		
		BF_MAPPINGS->set_bf_nodes(this_player()->query_name(), nodenr);
        
        
       
        /*SPYTOKENPLACEMENT_LOG("spytokenplacement_log",
        "The player " +this_player()->query_name() 
        +" placed a scarab at"+MASTER_OB(environment(scarab))+".\n");*/
        
        remove_object();
        
        return 1;
    }
    
    return 0;
}


void
create_object()
{
    set_name("_scarab_token");
    add_name("scarab");
    set_adj("tiny");
    add_adj("black");
    
    set_short("tiny black scarab");
    
    set_long("This is a tiny magical black figure of a "
    +"scarab.\nYou may "
    +"<destroy scarab> if you wish to rid yourself of this "
    +"object, or <place scarab> in a room you deem fit.\n");
    
    add_prop(OBJ_I_VALUE, 123);
    // Questitem no-drop properties.
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
}


init()
{
    ::init();
    add_action(do_destroy,"destroy");
    add_action(place_scarab,"place");
}


string
query_recover()
{
    return 0;
}
