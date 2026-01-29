/* /d/Faerun/guilds/vampires/obj/vamp_painting7.c
 * 
 *
 */

inherit "/std/object.c";

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "../guild.h"


string contours()
{
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {
		string box_str = "This "
            +"captivating painting seems to illustrate a dark "
			+"chamber, or maybe a dark crypt. The shadows within "
            +"covers most if not all the features, but it looks "
			+"like it's a place of solitude. As strange as it "
			+"sounds, you think you can <enter painting>.\n";
		
        return box_str;
    }        
    
    return "You look at the painting, but all you see is some "
    +"abstract colourful art that you don't understand.\n";
}


void
create_object()
{  
    setuid();
    seteuid(getuid());
    
    set_name("painting");
    add_name("old dusty painting");
    
    set_adj("old");
    add_adj("dusty");
    
    set_short("old dusty painting");
    set_pshort("old dusty paintings");
    
    set_long(contours);
    
    add_item(({"frame", "wooden frame"}), "There is a "
    +"carefully carved 'V' into the black wooden "
    +"frame containing the painting.\n");
    
    set_no_show_composite(1);
    
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GET, 1);
}


int
do_enter_painting(string str)
{
	if (str == "painting")
	{
		if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
        {
            // Knights have local exceptioncode that prevents
            // them from becoming vampire spawns. Therefore we 
            // add this check.
            if (present("vampthrall_amp_obj", this_player()))   
            {
                write("Strange. There must be something that "
                +"blocks you from entering. You have an eerie "
                +"feeling that it may have something to do about you "
                +"being affected by the curse of a vampire.\n");
                
                return 1;
            }
            
            if (this_player()->query_guild_name_occ() == "Solamnian Knights")
            {
                write("Strange. There must be something that "
                +"blocks you from entering. You have an eerie "
                +"feeling that it may have something to do about your "
                +"affiliation to the Knights of Solamnia.\n");
                
                return 1;
            }
            
            if (this_player()->query_guild_name_lay() != 0)
            {
                write("Strange. There must be something that "
                +"blocks you from entering. You have an eerie "
                +"feeling that it may have something to do about your "
                +"layman occupation.\n");
                
                return 1;
            }
            
            if (this_player()->query_guild_name_race() != 0)
            {
                write("Strange. There must be something that "
                +"blocks you from entering. You have an eerie "
                +"feeling that it may have something to do about your "
                +"racial occupation.\n");
                
                return 1;
            }
            
            if (this_player()->query_race() != "human")
            {
                write("Strange. There must be something that "
                +"blocks you from entering. You have an eerie "
                +"feeling that it may have something about your "
                +"race.\n");
                
                return 1;
            }
            
            if (this_player()->query_average() < 160)
            {
                write("Strange. There must be something that "
                +"blocks you from entering. You have an eerie "
                +"feeling that it may have something with your "
                +"size. You need to grow some more.\n");
                
                return 1;
            }
            
			tell_room(environment(this_player()), QCTNAME(this_player())
                + " fades away into the shadows!\n", this_player());
			
			this_player()->move_living("M", "/d/Faerun/guilds/vampires/rooms/crypt");
 
			return 1;
		}
		
		write("What?\n");
		
		return 1;
	}
	
	return 0;
}


void
init()
{
    ::init();

    add_action(do_enter_painting, "enter");
}
