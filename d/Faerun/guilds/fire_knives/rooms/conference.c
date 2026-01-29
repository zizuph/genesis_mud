/* /d/Faerun/guilds/fire_knives/rooms/conference.c
 *
 * Conference Room for audiences with the council
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

#define CHALLENGE_WARNING "_i_challenged_elder"

public int
block_check()
{
    if (present("fireknives_visit_object_elder", this_player()))
    {
       write("The guard dogs raise their heads to look "
       +"at you suspiciously, but they "
       +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());
            
        return 0;
    }  
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()))
    {
        write("The guard dogs raise their heads to look at "
        +"you, then look down "
        +"and turn around in a submissive gesture.\n");
    
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a furtive glance from the dogs before they lower "
        +"their head and turn around in a submissive "
        +"gesture.\n", this_player());
        
        return 0;
    }
      
    write("The guard dogs slowly pace until they stand in front of you "
    +"while growling softly, their eyes focused on yours. You decide "
    +"to reconsider your option and take a few steps backwards.\n");

    tell_room(environment(this_player()), QCTNAME(this_player()) 
    +" steps backwards from the dogs as they move in front of "
    + this_player()->query_possessive()
    +", blocking the way.\n", this_player());
        
    return 1;
}


int
trainee_to_full_member_ceremony(string str)
{    
    if (!str)
    {
        write("What?\n");
        
        return 1;
    }
    
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) == MAX_PROSPECT_RANK)
    {
        if (this_player()->query_prop(FULL_MEMBER_CEREMONY) == 1)
        {          
	        object playa = find_player(str);
			
			if (!playa)
			{
				write("No such player in the game.\n");

				return 1;
			}
	
            if (str == this_player()->query_name())
            {
                write("Challenge yourself? No.\n");
                
                return 1;
            }
            
            if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(playa->query_name()) ||
                FIREKNIVES_MASTER->is_occ_thefist_fireknife(playa->query_name()) ||
                FIREKNIVES_MASTER->is_occ_boss_fireknife(playa->query_name()) ||
                playa->query_wiz_level())
            {
                if (!present(playa, this_object()))
                {
                    write("That person is not present here in the conference room.\n");

                    return 1;
                }
                
                if (!this_player()->query_prop(CHALLENGE_WARNING))
                {
                    write("By challenging and fighting a member of the council "
                    +"you risk almost certain death.. Do you really want to do that? If "
                    +"so, make the challenge again!\n");
					
					this_player()->add_prop(CHALLENGE_WARNING, 1);

                    return 1;
                }
                
                write("You attack "+playa->query_name()+"!\nYou "
                +"aggressively raise your hand against "
                +playa->query_name()+" but aren't able to land a blow before "
                +"you feel the ground give way under your feet and you "
                +"land flat on your back on the ground!\n"
				+playa->query_name()+" performs a hard stomp on your solar "
				+"plexus that completely dazes you, making you struggle to breathe.\n\n");
                
                tell_room(this_object(), QCTNAME(this_player())
                +" attacks "+playa->query_name()+"!\n"+QCTNAME(this_player())
                +" aggresively raises "
                +this_player()->query_possessive()+" hand against "+playa->query_name()
                +" but isn't able to land a blow before "
                +this_player()->query_pronoun()+"'s swept off "
                +this_player()->query_possessive()+" "
                +"feet, falling flat on "
                +this_player()->query_possessive()+" back on the ground! The "
				+playa->query_name()+" performs a hard stomp on "
				+QCTNAME(this_player())+"'s solar "
				+"plexus that completely dazes "
				+this_player()->query_objective()+", making "
				+this_player()->query_objective()+" struggle to "
				+"breathe.\n\n", this_player(), playa);

                playa->catch_tell(this_player()->query_name()+ " attacks you!\n"
                +this_player()->query_name()+ " aggressively raises "+
                this_player()->query_possessive()+" hand towards "
                +"you, but you send "+this_player()->query_objective()
                +" straight to the floor flat on "
                +this_player()->query_possessive()+" back with "
                +"a quick sweep of your right foot! You perform a hard "
				+"stomp on "+this_player()->query_possessive()+" solar "
				+"plexus that completely dazes "+
				this_player()->query_objective()+", making "
				+this_player()->query_objective()+" struggle to breathe.\n");                
                
                
                if (!present("fullmember_cutscene_paralyze", this_player()))
                {
                    clone_object(FULLMEMBER_CUTSCENE_PARALYZE)->move(this_player(), 1);
                }
                
                FIREKNIVES_MASTER->remove_guild_trainee(this_player()->query_name());
	        	FIREKNIVES_MASTER->add_guild_fullmember(this_player()->query_name());
                FIREKNIVES_MAPPINGS->set_assassin_rank(this_player()->query_name(), MIN_FULLMEMBER_RANK);
				
				this_player()->remove_prop(FULL_MEMBER_CEREMONY);
				this_player()->remove_prop(CHALLENGE_WARNING);
                
                FULLMEMBER_LOG("fullmember_log",
                "The Trainee " +this_player()->query_name() 
                +" challenged an Elder and passed the test, becoming a "
                +"full member of the Brotherhood.\n");
                
                return 1;               
            }
                       
            write("You sense a divine force preventing your attack.\n");
            
            return 1;
        }
    }
    
    write("You sense a divine force preventing your attack.\n");
    
    return 1;
}


int
assume_elder_role(string str)
{
    if (str == "elder role")
    {
        if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
        {
            write("You are not a member of the Fire Knives.\n");
            
            return 1;
        }
        
        if (FIREKNIVES_MAPPINGS->query_assassin_xcouncil_activity_cooldown(this_player()->query_name()) == 1)
        {
            write("You recently held a council position of the "
            +"brotherhood and failed. Therefore you are not eligible for "
            +"the position at this time.\n");
            return 1;
        }
               
        if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 1)
        {
            write("You already are the Elder of the Fire Knives.\n");
            
            return 1;
        }
              
        // Elder is gone. The Mentor/Inquisitor can assume Elder role.
        if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 1)
        {
            if (FIREKNIVES_MASTER->no_boss() == 1)
            {
                write("You assume the role as the new Elder of the Fire Knives.\n");
                
                FIREKNIVES_MAPPINGS->set_assassin_rank(this_player()->query_name(), FIREKNIVES_MAX_RANK_MEMBER);
                FIREKNIVES_MASTER->add_occ_boss_fireknife(this_player()->query_name());
                
                FIREKNIVES_MASTER->remove_occ_mentor_fireknife(this_player()->query_name());
                FIREKNIVES_MASTER->remove_occ_thefist_fireknife(this_player()->query_name());
                
                FIREKNIVES_MASTER->remove_guild_fullmember(this_player()->query_name());
                FIREKNIVES_MASTER->remove_guild_trainee(this_player()->query_name());
            
                return 1;
            }
            
            write("The brotherhood already has an active Elder.\n");
            
            return 1;
        }
        
        // Elder is gone. The Fist can assume Elder role.
        if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 1)
        {
            if (FIREKNIVES_MASTER->no_boss() == 1)
            {
                write("You assume the role as the new Elder of the Fire Knives.\n");
                
                FIREKNIVES_MAPPINGS->set_assassin_rank(this_player()->query_name(), FIREKNIVES_MAX_RANK_MEMBER);
                FIREKNIVES_MASTER->add_occ_boss_fireknife(this_player()->query_name());
                
                FIREKNIVES_MASTER->remove_occ_mentor_fireknife(this_player()->query_name());
                FIREKNIVES_MASTER->remove_occ_thefist_fireknife(this_player()->query_name());
                
                FIREKNIVES_MASTER->remove_guild_fullmember(this_player()->query_name());
                FIREKNIVES_MASTER->remove_guild_trainee(this_player()->query_name());
            
                return 1;
            }
            
            write("The brotherhood already has an active Elder.\n");
            
            return 1;
        }
        
        // Guild has no council, therefore the Elder position 
        // can be taken by the first qualified candidate.
        if (FIREKNIVES_MASTER->no_boss() == 0 
        && FIREKNIVES_MASTER->no_fist() == 0 
        && FIREKNIVES_MASTER->no_mentor() == 0)
        {
            write("Uhm..no. The role of the Elder is not "
            +"vacant. Furthermore, assuming this position is "
            +"only possible when there are no other council members left.\n");
            
            return 1;
        }  
        
        if (this_player()->query_stat(SS_OCCUP) > 99)
        {
            write("You lack the proper amount of guild experience to "
            +"assume this role. Try again later when you have gained sufficient "
            +"guild experience.\n");

            return 1;            
        }
        
        write("Since this Brotherhood of Assassins lack leadership, you "
        +"freely claim the role as the new Elder!\nYou are now the new head "
        +"of the guild! Run it wizely...\n");


        FIREKNIVES_MAPPINGS->set_assassin_rank(this_player()->query_name(), FIREKNIVES_MAX_RANK_MEMBER);
        FIREKNIVES_MASTER->add_occ_boss_fireknife(this_player()->query_name());
        FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(this_player()->query_name(), 1000);
        
        FIREKNIVES_MASTER->remove_occ_mentor_fireknife(this_player()->query_name());
        FIREKNIVES_MASTER->remove_occ_thefist_fireknife(this_player()->query_name());
        
        FIREKNIVES_MASTER->remove_guild_fullmember(this_player()->query_name());
        FIREKNIVES_MASTER->remove_guild_trainee(this_player()->query_name());

        return 1;
    }

    write("Assume what? the 'elder role'?\n");
    
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
    
    setuid();
    seteuid(getuid());
        
    if (str == "to brotherhood")
    {   
        if (!this_player()->query_prop(I_CAN_JOIN_FIREKNIVES))
        {
            // Guild has no council, therefore anyone can join
            if (FIREKNIVES_MASTER->no_boss() == 0 
            && FIREKNIVES_MASTER->no_fist() == 0 
            && FIREKNIVES_MASTER->no_mentor() == 0)
            {
                write("You have no permission to join the brotherhood.\n");
                
                return 1;
            }  
        }
              
        if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()))
        {
            write("You are already a member of the brotherhood.\n");
            return 1;
        }
        
        if (this_player()->query_average() < REQ_AVG)
        {
            write("You feel you are not quite yet to join the "
            +"brotherhood. Return later when you have grown some more.\n");
            
            return 1;        
        }
        
        if (this_player()->query_guild_name_occ())
        {
            write("Return when you have a vacant occupational slot.\n");
                
            return 1;
        }
        
        if (this_player()->query_alignment() > -300)
        {
            write("You are not sufficiently evil of heart to join the "
            +"Brotherhood.\n");
            
            return 1;
        }
       
        shadow_occ = clone_object(FIREKNIVES_GUILD_DIR 
        + "shadows/fireknives_sh_occ.c");

        if (shadow_occ->shadow_me(this_player(), "occupational", "thief", 
        FIREKNIVES_GUILD_NAME) != 1)
        {
            write("You try to join the brotherhood, but nothing happens.\n");
            return 1;
        }

        FIREKNIVES_MASTER->add_occ_fireknife(this_player()->query_name());
		FIREKNIVES_MASTER->add_guild_trainee(this_player()->query_name());
        FIREKNIVES_MAPPINGS->set_assassin_rank(this_player()->query_name(), 1);
        FIREKNIVES_MAPPINGS->set_assassin_gauge(this_player()->query_name(), 1);
            
        if (!present("join_cutscene_paralyze", this_player()))
        {
            clone_object(JOIN_CUTSCENE_PARALYZE)->move(this_player(), 1);
        }
        
        this_player()->remove_prop(I_CAN_JOIN_FIREKNIVES);

        this_player()->update_hooks();
        
        if (FIREKNIVES_MASTER->no_boss() == 1 
            && FIREKNIVES_MASTER->no_fist() == 1 
            && FIREKNIVES_MASTER->no_mentor() == 1)
        {
            JOIN_LOG("join_log",
            "The individual " +this_player()->query_name() 
            +" joined the Brotherhood as a new Postulant. No council "
            +"in guild, so join-at-will is possible.\n");
                
            return 1;
        }  
        
        JOIN_LOG("join_log",
        "The Applicant " +this_player()->query_name() 
        +" joined the Brotherhood as a new Postulant.\n");
            
        return 1;
    }
    
    write("What?\n");
            
    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Conference Chamber");
    
    set_long("A lustruous chamber carved deep within the ancient keep. "
    +"Unlike other rooms, the walls have not been tended as well as others, "
    +"and so retain the memories of old in its various shapes and cracks. "
    +"At the far end to the north, incrusted within the walls in a scraggly "
    +"hole leading up to a chimney is a fireplace, while in the center a "
    +"high throne prides the hollow enclosure in which you are in. At each "
    +"side are two lower, less imposing chairs. The rough floor is tamed "
    +"only by as many black diamonds as sand on a beach, whilst the "
    +"unreachable ceiling is crowned by an ancient candelabra dangling with "
    +"each gust of wind coming from the fireplace and casting a myriad of "
    +"sparkles around the gems strewn about the cave-like room. "
    +"A pair of guard dogs is resting near the north exit.\n");

    add_item(({"walls"}),
    "The walls are rough and varied in shape, each one of them has a black "
    +" sconce holding a torch. To the north there is a hidden door.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the north.\n");

    add_item(({"sconce"}),
    "The sconces are of a dark metal-like material, each one holds a torch "
    +" in every wall.\n");

    add_item(({"torch"}),
    "The torches are thick and seemingly strong, currently lit.\n");

    add_item(({"shapes"}),
    "Various shapes have appeared with the passage of time in each part of "
    +" the wall, someresembling wraith-like creatures screaming while others "
    +" appear to be sunk in sorrow.\n");

    add_item(({"creatures"}),
    "Various shapes have appeared with the passage of time in each part of "
    +" the wall, someresembling wraith-like creatures screaming while others "
    +" appear to be sunk in sorrow.\n");
    
    add_item(({"hole", "door"}),
    "The hole appears man made, carved within the far northern wall beside a "
    +"door. Next to a fireplace.\n");
    
    add_item(({"fireplace"}),
    "The fireplace is ever burning, the calm crackling sounds seem eerie, "
    +" although calming.\n");
    
    add_item(({"throne"}),
    "The high throne in the middle is decoared with "
    +"twisting snakes that entwine "
    +"into each other, swallowing their own tails and "
    +"evolving into two bigger "
    +" ones that meet at the center atop the chair, "
    +"holding a hold between them.\n");

    add_item(({"snakes"}),
    "The snakes are sometimes similar to a statue. They "
    +"twist and turn around "
    +" the high chair.\n");
    
    add_item(({"head"}),
    "The head appears frozen in an expression of pain. "
    +"Its eyes and mouth "
    +" have been sewn shut, with both its corners "
    +"draping downwards in anguish.\n");
   
    add_item(({"right chair"}),
    "A lower simple wooden chair with the symbol of a fist carved on it.\n");
    
    add_item(({"chair"}),
    "Which chair? The left chair, right chair or the throne?\n");
   
    add_item(({"chairs"}),
    "There are a less imposing chair on the left and the right side of the high throne.\n");
    
    add_item(({"left chair"}),
    "A lower simple wooden chair with the symbol of a pen carved on it.\n");
    
    add_item(({"floor"}),
    "The floor is rough, tamed only by the uncountable "
    +"amount of black diamonds "
    +"covering its surface.\n");
    
    add_item(({"diamonds","black diamonds"}),
    "The diamonds are strewn about the floor, covering every inch of it, "
    +"glistening in the rays of the light thrown by various sources.\n");
    
    add_item(({"ceiling"}),
    "The ceiling is so high up it is barely visible from here, but you can "
    +"tell there is one by the hanging candelabra "
    +"protruding from the shadows.\n");
    
    add_item(({"candelabra"}),
    "The candelabra seems heavy. Thick chains hold it "
    +"in place, but the gusts of " 
    +" wind coming from the hole still manage to make "
    +"it dangle in place once in a "
    +" while, making the room come alive.\n");
    
    add_item(({"wind"}),
    "The wind is felt as if coming from the hole where the fireplace is.\n");
    
    add_item(({"sparkles"}),
    " The sometimes faint and others bright sparkles are cast by the light "
    +" bouncing off the gems strewn about the floor.\n");
    
    add_exit(FIREKNIVES_ROOMS_DIR + "elder.c", "north", block_check);

    add_exit(FIREKNIVES_ROOMS_DIR + "reception.c", "south");

    reset_faerun_room();
}


/*
 * Function that allows the player to sit at a table or the bar
 */
int action_sit(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()))
    {
        if(this_player()->query_prop("_sitting_at_elder_chair"))
        {
            write("But you are already sitting at the decorated throne!\n");
            return 1;
        }   
        
        if(str == "in the chair" | str == "in throne" 
        | str == "throne" | str == "chair" | str == "on throne"
        | str == "on the throne")
        {
            this_player()->catch_msg("You sit down at the "
            +"high decorated throne.\n");
            
            say(QCTNAME(this_player()) + " sits down at the high "
            +"decorated throne.\n");
            
            this_player()->add_prop("_sitting_at_elder_chair", 1);
            
            this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
            +"at the high decorated throne");
            return 1;
        }

        else
        {
            this_player()->catch_msg("Being the Elder, you should rather 'sit on throne'.\n");
            return 1;
        }

        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()))
    {
        if(this_player()->query_prop("_sitting_at_mentor_chair"))
        {
            write("But you are already sitting in your chair!\n");
            return 1;
        }   
        
        if(str == "in the chair" | str == "chair" | str == "in chair")
        {
            this_player()->catch_msg("You sit down in the simple "
            +"wooden chair with the symbol of a pen carved on it.\n");
            
            say(QCTNAME(this_player()) + " sits down in the simple "
            +"wooden chair with the symbol of a pen carved on it.\n");
            
            this_player()->add_prop("_sitting_at_mentor_chair", 1);
            
            this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
            +"in the simple wooden chair with the symbol of a pen carved on it");
            return 1;
        }

        else
        {
            this_player()->catch_msg("Being the Inquisitor, please 'sit in chair'.\n");
            return 1;
        }

        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()))
    {
        if(this_player()->query_prop("_sitting_at_thefist_chair"))
        {
            write("But you are already sitting in your chair!\n");
            return 1;
        }   
        
        if(str == "in the chair" | str == "chair" | str == "in chair")
        {
            this_player()->catch_msg("You sit down in the simple "
            +"wooden chair with the symbol of a fist carved on it.\n");
            
            say(QCTNAME(this_player()) + " sits down in the simple "
            +"wooden chair with the symbol of a fist carved on it.\n");
            
            this_player()->add_prop("_sitting_at_thefist_chair", 1);
            
            this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
            +"in the simple wooden chair with the symbol of a fist carved on it");
            return 1;
        }

        else
        {
            this_player()->catch_msg("Being the Fist, please 'sit in chair'.\n");
            return 1;
        }
    }
    
    write("Uhm...no! You don't want to risk your life by "
    +"being caught sitting on places belonging to the "
    +"Elders!\n");
    
    return 1;
}


/*
 * Function that allows the player to stand from a table or the bar
 */
int
action_stand(string str)
{
    if(str == "up")
    {
        if(this_player()->query_prop("_sitting_at_elder_chair"))
        {
            this_player()->catch_msg("You stand up and leave the "
            +"high decorated throne.\n");
            
            say(QCTNAME(this_player())+" stands up from the "
            +"high decorated throne.\n");
            
            this_player()->remove_prop("_sitting_at_elder_chair");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }
        
        if(this_player()->query_prop("_sitting_at_mentor_chair"))
        {
            this_player()->catch_msg("You stand up and leave simple "
            +"wooden chair with the symbol of a pen carved on it.\n");
            
            say(QCTNAME(this_player())+" stands up from the simple "
            +"wooden chair with the symbol of a pen carved on it.\n");
            
            this_player()->remove_prop("_sitting_at_mentor_chair");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }
        
        if(this_player()->query_prop("_sitting_at_thefist_chair"))
        {
            this_player()->catch_msg("You stand up and leave simple "
            +"wooden chair with the symbol of a fist carved on it.\n");
            
            say(QCTNAME(this_player())+" stands up from the simple "
            +"wooden chair with the symbol of a fist carved on it.\n");
            
            this_player()->remove_prop("_sitting_at_thefist_chair");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }
    }

    else
    {
        this_player()->catch_msg("Stand? Stand up?\n");
        return 1;
    }

    return 1;
}


/*
 * Function to cleanup props if a player leaves before standing
 */
void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
      return;
                
    if(ob->query_prop("_sitting_at_elder_chair"))
    {
        ob->catch_msg("You stand up and leave the "
        +"high decorated throne before leaving the room.\n");
        
        say(QCTNAME(ob)+" stands up from the "
        +"high decorated throne before leaving the room.\n");
        
        ob->remove_prop("_sitting_at_elder_chair");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        return;
    }
    
    if(ob->query_prop("_sitting_at_mentor_chair"))
    {
        ob->catch_msg("You stand up and leave simple "
        +"wooden chair with the symbol of a pen "
        +"carved on it before leaving the room.\n");
        
        say(QCTNAME(ob)+" stands up from the simple "
        +"wooden chair with the symbol of a pen "
        +"carved on it before leaving the room.\n");
        
        ob->remove_prop("_sitting_at_mentor_chair");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        return;
    }
    
    if(ob->query_prop("_sitting_at_thefist_chair"))
    {
        ob->catch_msg("You stand up and leave simple "
        +"wooden chair with the symbol of a fist carved on "
        +"it before leaving the room.\n");
        
        say(QCTNAME(ob)+" stands up from the simple "
        +"wooden chair with the symbol of a fist "
        +"carved on it before leaving the room.\n");
        
        ob->remove_prop("_sitting_at_thefist_chair");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        return;
    }
}


void
do_whispers()
{  
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        return;
    }
          
    // Elder is gone. The Mentor/Inquisitor can assume Elder role.
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 1)
    {
        if (FIREKNIVES_MASTER->no_boss() == 1)
        {
            this_player()->catch_tell("\n\nYou hear a whisper from the "
            +"shadows, saying: The Elder is gone! You may 'assume elder role' "
            +"if you want it, Inquisitor!\n\n");    
        
            return;   
        }
        
        return;
    }
    
    // Elder is gone. The Fist can assume Elder role.
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 1)
    {
        if (FIREKNIVES_MASTER->no_boss() == 1)
        {
            this_player()->catch_tell("\n\nYou hear a whisper from the "
            +"shadows, saying: The Elder is gone! You may 'assume elder role' "
            +"if you want it, Fist!\n\n");    
        
            return;   
        }
        
        return;
    }
    
    if (this_player()->query_stat(SS_OCCUP) > 99)
    {
        return;
    }
    
    if (FIREKNIVES_MASTER->no_boss() == 1 
        && FIREKNIVES_MASTER->no_fist() == 1 
        && FIREKNIVES_MASTER->no_mentor() == 1)
    {
        this_player()->catch_tell("\n\nYou hear a whisper from the "
        +"shadows, saying: The Elder and the rest of the Council is "
        +"gone! You may 'assume elder role' "
        +"if you want it!\n\n");    
    
        return;   
    }
    
    return;
}


void move_eliminate_bleed(object executee)
{
    setuid();
    seteuid(getuid());
    
    clone_object(FIREKNIVES_GUILD_DIR + "obj/execute_obj")->move(executee, 1);
    
    return;
}


// Execution as punishment.
int
do_eliminate(string str)
{
    setuid();
    seteuid(getuid());
    
    object execute_obj = 0;
    
    if (!str)
    {
        return 0;
    }
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }
    
    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't execute the Elder!\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't execute the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't execute the Fist.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 1)
    {
        write("This function is not ment for members of the "
        +"brotherhood, but visitors.\n");
        return 1;
    }

    object executee = find_player(str);
    
    if (executee == 0)
    {
        write("That person is not in the realms!\n");
        
        return 1;
    }
    
    if (!present(executee, this_object()))
    {
        write("That person is not present here in the conference room.\n");

        return 1;
    }

    write("You silently order " + executee->query_name() 
    + " to be executed immediately!\n\n");
    
    tell_room(environment(executee), "You see a bald muscular male "
        +"human walk up to "
        +executee->query_name()+", placing a hand on "
        +executee->query_possessive()+" shoulder. There is a flash "
        +"of steel between "+executee->query_name()+" legs and a pool " 
        +"of blood starts forming quickly. The bald muscular human leans in "
        +"and whispers something to "+executee->query_name()
        +" before turning "
        +"around and walking away.\n", executee);
        
        executee->catch_tell("You feel a hand on your shoulder followed "
        +"by a sharp pain on the inside of your thigh. Warm liquid starts "
        +"to pour down your thigh as you hear the gravelly voice of "
        +"Richard D. Ruddock whispering in your ear 'Die swiftly.' and "
        +"you turn around to face him as he backs "
        +"off and walks away. Your arms start to feel heavy and your vision "
        +"starts to blur as you fall to your knees from the loss of "
        +"blood.\n");
        
    set_alarm(1.0, 0.0, &move_eliminate_bleed(executee));
    
    EXECUTE_LOG("execute_log",
    "The member " +str
    +" was Eliminated in the conference room "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_CONFERENCE_LOG("wizard_entry_conference_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives conference room.\n");
            
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
        
        set_alarm(1.0, 0.0, &do_whispers());
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    ::init();

    add_action(do_join, "pledge");
    add_action(do_eliminate, "eliminate");
	add_action(trainee_to_full_member_ceremony, "challenge");
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
    add_action(assume_elder_role, "assume");
}

