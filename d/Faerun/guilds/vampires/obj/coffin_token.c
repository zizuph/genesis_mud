/* /d/Faerun/guilds/vampires/obj/coffin_token.c
 *
 * Coffintoken. Rooms with this token can spawn coffins for vampires.
 *
 * Nerull, 2020
 *
 */

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h";

#define COFFIN_MANAGER   "/d/Faerun/guilds/vampires/master/coffin_manager.c"
#define TP this_player()

//#define WATCHERS(obj)   (filter(filter(all_inventory(environment((obj))), \
  //                          &->can_see_in_room()), &(obj)->check_seen()) \
    //                        - ({ (obj) }))
                            
#define MATERIALS ({ "stone", "marble", "wood", "copper", "silver", \
                    "gold", "platinum", "steel", "adamantine", "brass", \
                    "bone", })
                    
string *coffin_material = ({"wood",
                            "stone",
                            "marble"});
							
int cooldown_timer;
int reset_cooldown;
//int find_no_coffin;
//int do_coffinsearch;


void
remove_me()
{
	remove_object();
	
	return;
}


create_object()
{
    set_name("coffin_token");
    add_name("_coffin_token");
    set_adj("invisible");
    set_short("coffin token");
    set_long("This is some weird anomality.\n");

    add_prop(OBJ_I_VALUE, 80000);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_M_NO_SELL, 1);
	add_prop(OBJ_I_INVIS, 100);
    add_prop(OBJ_I_NO_STEAL, "Emh..no.\n");
    add_prop(OBJ_M_NO_GET, "Ehm..no.\n");
    
    set_no_show();
	
	cooldown_timer = 0;
	
	set_alarm(10790.0, 0.0, &remove_me());
    //set_alarm(590.0, 0.0, &remove_me());
}


int
find_no_coffin()
{
	write("Your search reveals nothing special.\n");
	
	return 1;
}


int
reset_coold()
{
	cooldown_timer = 0;
	
	return 1;
}


int
do_coffinsearch(string str)
{
    if (str == "here for coffin" || str == "here for coffins")
    {
		setuid();
		seteuid(getuid());
		
		if (VAMPIRES_MASTER->is_lay_vampires(this_player()->query_name()))
        {
			string *coffins;

			coffins = COFFIN_MANAGER->query_all_coffins();
			
			for (int i = 0; sizeof(coffins) > i; i++)
			{
				// We wont find coffins when we already have one.
				if (coffins[i] == TP->query_real_name())
				{
					return 0;
				}
			}


            object coffin;

			int i;
            
            i = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
            
            switch(i)
            {   
                case 0..3000:
                int randdice1 = random(3);
                
                if (randdice1 == 0)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_1_1");
                }
                
                if (randdice1 == 1)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_1_2");
                }
                
                if (randdice1 == 2)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_1_3");
                }                             
                break;            
          
                case 3001..11000:
                int randdice2 = random(3);
                
                if (randdice2 == 0)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_2_1");
                }
                
                if (randdice2 == 1)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_2_2");
                }
                
                if (randdice2 == 2)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_2_3");
                }                             
                break;
                             
                case 11001..99999:
                int randdice3 = random(3);
                
                if (randdice3 == 0)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_3_1");
                }
                
                if (randdice3 == 1)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_3_2");
                }
                
                if (randdice3 == 2)
                {
                    coffin=clone_object(VAMPIRES_GUILD_DIR +"obj/coffin_owner_token_3_3");
                }                             
                break;
            }
            
			coffin->move(TP, 1);

			TP->catch_msg("Your keen senses locates some coffin "
			+"buried in the ground here! With unnatural strength, you "
			+"pull up a "+coffin->short()+".\n");

			WATCHERS(TP)->catch_msg(QCTNAME(TP)+ " digs into the ground "
			+"and finds a "+coffin->short()+".\n");
            
            COFFINFIND_LOG("coffinfind_log",
            "The player " +this_player()->query_name() 
            +" found a new coffin.\n");
			
			return 1;
        }
    }
    
    return 0;
}


void
init()
{
    ::init();
	
    add_action(do_coffinsearch, "search");
}
