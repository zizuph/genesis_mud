/* /d/Faerun/guilds/vampires/rooms/anomality_room.c
 *
 * Nerull 2022
 *
 */

inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

int fountain_red;

void
dest_me()
{
    remove_object();
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("In the realm of blood");
    
    set_long("you are floating in what is best described as a void "
    +"with no features at all, except for the overwhelmingly strong "
    +"blood-red light that seems to emanate from everywhere. Before "
    +"you and within reach, you see a "
    +"floating fountain of metal that is pouring out "
    +"torrents of fresh Blood!\nYou may 'leave' at anytime to "
    +"return to your coffin or at the graveyard.\n");
    
    fountain_red = 1;
    
    set_alarm(50001.0, 0.0, &dest_me());

    reset_faerun_room();
}


void
do_whispers()
{  
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) > 0)
    {
        if (fountain_red == 1)
        {  
            this_player()->catch_tell("A commanding female voice echoes in "
            +"your head: Welcome to this sanctuary, Vampire! Please drink "
            +"from the fountain of Life, and increase in the power of the "
            +"Immortals! You may drink only once.\n");            
            
            return;
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
        set_alarm(2.0, 0.0, &do_whispers());
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


int
drink_fountain(string str)
{
    if (str == "from fountain" || str == "fountain"
    || str == "blood" || str == "blood from fountain")
    {
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) > 0)
        {
            if (fountain_red == 1)
            {
                int currentrep;
                int newrep;
                
                int imm_points;
                
                
                imm_points = VAMPIRES_MAPPINGS->query_vampires_resilience(this_player()->query_name());
                
                imm_points = imm_points + 1;
                VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), imm_points);
                
                
                
                write("You drink fresh blood greedily from the large "
                +"fountain!\nYou feel stronger and completely "
                +"saturated!\n\nYou gain a point of Immortality!\n\nYour reputation "
                +"among vampires rises slightly!\n\n");

                currentrep = VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name());
                
                newrep = currentrep + 5;
                
                if (newrep > 100)
                {
                    newrep = 100;
                }
                
                VAMPIRES_MAPPINGS->set_vampire_reputation(this_player()->query_name(), newrep);
                
                REP_INCREASE_LOG("rep_increase_log",
                this_player()->query_name()+" increased 1 point in reputation.\n");
                
                ANOMALITY_REWARD_LOG("anomality_reward_log",
                "The Vampire " +this_player()->query_name()+" received "
                +"1 imm point and 5 rep points.\n");
                
                fountain_red = 0;
                               
                return 1;
            }
            
            write("A commanding female voice echoes in "
            +"your head: Greedy, aren't we? You have had your fill, "
            +"vampire! Leave, or risk destruction!\n");
            
            return 1;
        }

        write("A commanding female voice echoes in "
        +"your head: You are not worthy yet of drinking from the "
        +"Fountain of Life. Leave this sanctuary or risk destruction!\n");

        return 1;            
    }
    
    return 0;
}


int
leave_haze()
{
    this_player()->move_living("M", VAMPIRES_GUILD_DIR + "rooms/coffin", 1);
    
    return 1;
}


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void init()
{
    ::init();

    add_action(drink_fountain, "drink");
    add_action(leave_haze, "leave");
}


