/*
*  The Balrog's room
*
*  Created by Znagsnuf.
*
*
*  Date:                      What is done:                            By whom:            
*  ----------------------------------------------------------------------------
*  01/05-17                   Started remaking it                      Znagsnuf
*
*/

inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

/* Prototypes */
void add_balrog();
void reset_room();

// Balrog spawn
int b_spawn = 0;
int max_spawn = 0;
int timer = 0;

string drums();

#define drum_timer 60.0
#define MAX_ORCS 5
#define MAX_TROLLS 6

object balrog;

void reset_room()
{
    add_balrog();
}

void
create_room()
{
    set_short("A hot steamy place, deep in the mines");
    set_long("The air is relatively cool and calm, "+
	    "though the steam does not go away entirely. "+
	    "Loud rumbling sounds nearly knock you off balance, "+
	    "and the steam becomes red briefly.\n");

    add_item(({"steam","ground","air"}),
    "The steam rises from the ground, heating the air in this place. "+
    "The ground here is pocked with small depressions, covered with a "+
    "thin film of water.\n");

    add_item(({"red glow","glow","sounds","sound"}),
    "The glow brightens and fades out of time with the low rumbling "+
    "sounds that echo from within the darkness.\n");

    add_item(({"water","film","depressions","depression","pock"}),
    "The water covering the pocked depressions is covered by a thick "+
    "red film that is only partly translucent. "+
    "The depressions are a bit bigger here, and too big to be footprints.\n");

    add_prop(ROOM_I_INSIDE, 1);

    //add_exit("/d/Shire/moria/mines/lair/lair4","southeast",0,1);
    //add_exit("/d/Shire/moria/mines/lair/lair5", "southwest",0,1);

    reset_room();
}

/*
 * Function name: filter_in_moria()
 * Description  : Filter if a player is in Moria.
 */
static int
filter_in_moria(object who)
{
    object env = environment(who);

    if (!env || !objectp(env))
        return 0;
    /*
    if(who->query_wiz_level())
        return 0;
    */
    if(!wildmatch("/d/Shire/moria/*", file_name(env)))
        return 0;

    return 1;
}

/*
 * Function name: set_balrog_spawn()
 * Description  : Sets the Balrog spawn.
 */
int
set_balrog_spawn(int i)
{
    b_spawn = i;
}

/*
 * Function name: query_balrog_spawn()
 * Description  : Return the Balrog spawn.
 */
int
query_balrog_spawn(int i)
{
    return b_spawn;
}

/*
 * Function name: drums()
 * Description  : Doom - doom - doom.
 */
string
drums()
{
    object *is_in_moria;
    string print;
    int i;

    is_in_moria = filter(users(), &filter_in_moria());

    if(!sizeof(is_in_moria))
    {
        return "";
    }

    if(!balrog)
    {
        if (timer)
            remove_alarm(timer);
        return "";
    }

    for (i=0; i<sizeof(is_in_moria); i++) 
    {
        is_in_moria[i]->catch_msg("A drumming can be heard from a "
              + "distance.\n Doom - doom - doom roll the drum-beats.\n" 
              + "The drumming echoes from deep inside the mountain.\n");
    }

    timer = set_alarm(drum_timer, 0.0, &drums());

    return "";
}

/*
 * Function name: add_balrog()
 * Description  : Behold! This is the Mighty Balrog of Moria.
 */
void
add_balrog()
{
    if(!balrog && b_spawn > 10 && !max_spawn)
    {
        balrog = clone_object("/d/Shire/moria/wep/new/balrog_new");
        balrog->move(TO);
        tell_room((TO), "\nSomething arrives from behind, what it was could "
                      + "not be seen, it was like a great shadow, in the "
                      + "middle of which was a dark form, of man-shape maybe "
                      + "yet greater, and a power and terror seemed to be in "
                      + "and to go before it. It came to the edge of the fire "
                      + "and the light faded as if a cloud had bent over it. "
                      + "Then with a rush it leaped across the fissure. The "
                      + "flames roared up to greet it, and wreathed about it, "
                      + "and a black smoke swirled in the air. Its streaming "
                      + "mane kindled, and blazed behind it.\nA "
                      + balrog->query_race_name() + " has arrived!.\n\n");
        max_spawn = 1;
        drums();
    }
}
