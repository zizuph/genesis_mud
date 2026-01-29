/* dragonadmin.c
 * Carridin, 27 Nov 97
 * This is the bugger-o admin thingy for random dragonattacks in Neraka
 * Updated 18 Jan 97, Ashlar
 * Added min stat to be attacked, and young dragons, and colour distribution.
 *
 * Navarre December 30th 2007: After incident with ancient dragons killing smaller players.
 *                             I added a check to make sure no ancient dragons will appear
 *                             to attack players below 165 average.
 *                             At the same time I changed it so if the player is above 130
 *                             average he never gets a young dragon, but at minimum an adult.
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

object dragon;
int dragon_cloned = 0;
int idleness;

/* Prototypes */
void dragon_attack(object *list);
void dragon_flyby();
void check_for_dragonattack();

void
create_room()
{
	set_short("Dragonattack admin");
	set_long("This is the administration object for dragonattacks in " +
		"Neraka.\n");

	set_alarm(60.0, 60.0, check_for_dragonattack);
}

/*
 * Function name: check_for_dragonattack
 * Description: checks for mortals in Neraka that can be attacked
 */
void
check_for_dragonattack()
{
	object *obs;
	object *list = ({ });
	int i;
	string s;

	if (objectp(dragon))
	{
    	if (dragon->query_attack())
    	    idleness = 0;
    	else if (++idleness > 1)
    	{
        	tell_room(E(dragon), "The dragon takes to the skies!\n");
        	dragon->remove_object();
        	dragon_cloned = 0;
			idleness = 0;
    	}
	    return;
	}

    obs = users();
    for(i=0;i<sizeof(obs);i++)
    {
        if(E(obs[i]) && !E(obs[i])->query_prop(ROOM_I_INSIDE) &&
			(obs[i]->query_prop(NERAKA_I_ATTACKED_TEMPLE) ||
			ATTACKERS_ADMIN->query_know_person(0, obs[i])) &&
			(obs[i]->query_average_stat() > 70))
        {
	    if(wildmatch("*/taman_busuk/neraka/*", file_name(E(obs[i]))) ||
	       wildmatch("*/taman_busuk/sanction/room/*", file_name(E(obs[i]))))
            {
                list += ({ obs[i] });
            }
        }
    }
	
	if (sizeof(list) == 0)
    	return;

	switch (random(100))
	{
		case 0..4:	dragon_attack(list);	/* Attack a player */
		break;
		case 70..99:	dragon_flyby();		/* Send a text message to all of neraka */
		break;
	}
}

/*
 * Function name: dragon_attack
 * Description:   Starts an attack on a randomly chosen player
 * Arguments:     object *list - list of players in Neraka
 */
void
dragon_attack(object *list)
{
    int player_avg_stat;
    
    object player = list[random(sizeof(list))];
    string *age = ({"young","young","young","adult", "adult", "adult", "aged", "ancient"});
    string *col = ({"red","red","red","blue","blue","blue","green","black","white"});
    string setage = age[random(sizeof(age))];
    string setcol = col[random(sizeof(col))];

    player_avg_stat = player->query_average_stat();
    
    if((player_avg_stat < 165 && dragon->query_age() == "ancient") ||
       (player_avg_stat > 130 && dragon->query_age() == "young"))
    {
        dragon->remove_object();
    }
        
    if (!objectp(dragon) && !dragon_cloned)
    {
        dragon = clone_object(NNPC + "attackdragon.c");
        dragon->set_colour(setcol);
        
        if(player_avg_stat < 165 && setage == "ancient")
        {
            setage = "aged";
        }
        else if(player_avg_stat > 130 && setage == "young")
        {
            setage = "adult";
        }

        dragon->set_age(setage);
        dragon->heal_hp(dragon->query_max_hp());
        dragon->move_living("M", E(player));
        dragon_cloned = 1;
        
        if (player->query_average_stat() > 130)
            dragon->set_hunting(player);
        
        if (dragon)
        {
            tell_room(E(player), "\nWith an blood-chilling shriek, a great " + dragon->query_colour() +
                      " dragon swoops down on you from the skies above.\n\n");
            dragon->command("kill " + player->query_real_name());
            
        }
    }
}

/*
 * Function name: dragon_flyby
 * Description: Sends a message to Neraka
 */
void
dragon_flyby()
{
	switch (random(5))
	{
		case 0: NERAKA_ADMIN->tell_neraka("","A great shadow sweeps past " +
			"you on the ground.\n",1);
                NERAKA_ADMIN->tell_sanction("","A great shadow sweeps past you on the ground.\n",1);
		break;
		case 1: NERAKA_ADMIN->tell_neraka("","Something in the sky far above you " +
			"catches your eye, but when you look again, it's gone.\n",1);
                NERAKA_ADMIN->tell_sanction("","Something in the sky far above you catches your eye, but when you look again, it's gone.\n",1);
		break;
		case 2: NERAKA_ADMIN->tell_neraka("","Above you, a great dragon swoops by. " +
			"As the beast flies away, you give a sigh of relief.\n",1);
                NERAKA_ADMIN->tell_sanction("","Above you, a great dragon swoops by. As the beast flies away, you give a sigh of relief,\n",1);
		break;
		case 3: NERAKA_ADMIN->tell_neraka("","A flight of dragons glides through the " +
			"skies.\n",1);
                NERAKA_ADMIN->tell_sanction("","A flight of dragons glides through the skies.\n", 1);
		break;
		case 4: NERAKA_ADMIN->tell_neraka("","A lone dragon flies through the skies " +
			"above Neraka.\n",1);
                NERAKA_ADMIN->tell_sanction("","A lone dragon flies just below the clouds covering the skies of Sanction.\n",1);
		break;
	}
}

void
reset_room()
{
    if (!objectp(dragon))
         dragon_cloned = 0;
}
