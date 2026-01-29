/*    Water2.c
 *    This is where the players end up after their fall
 *    from a great height, they are passed through the
 *    fallroom.c, through water1.c, and into this room
 *    via alarm.
 */

inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


int flush_id;
int num_players;

void flush_players();

void create_room()
{

    num_players = 0;
    
    set_long( "\n\n\nThe panic of certain death fades away as you "+
	"give in to the sweet nothings of unconsiousness, "+
	"unable to prevent yourself from floating onward, "+
	"to where, you are beyond knowing or caring...\n\n\n" ); 
    
}

void
enter_inv(object ob, object from)
{
    num_players++;
    if (num_players == 1)
	flush_id = set_alarm(20.0, 0.0, flush_players);
    ::enter_inv(ob, from);
}

void
leave_inv(object ob, object to)
{
    // I don't need to remove the alarm
    num_players--;
}

void
flush_players()
{
    int i;
    int sz;
    object *ppl;

    ppl = all_inventory(TO);
    sz = sizeof(ppl);

    for (i=0; i<sz; i++)
    {
	ppl[i]->catch_msg("D A R K N E S S...\n\nE M P T Y N E S S"+
	"...\n\nS I L E N C E...\n\n\n");
        ppl[i]->move_living("washed out to sea",
			    VAMP_AREA_DIR + "water3", 1, 0);
    }

}