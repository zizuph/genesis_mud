/*    Water3.c
 *    This is where the players end up after their fall
 *    from a great height, they are passed through the
 *    fallroom.c, through water1.c and 2, and into this room
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
    
    set_long( "\n\n\n\n\n\n" ); 
    
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
	ppl[i]->catch_msg("Something nags the farthest reaches of your "+
"conciousness, rousing you from the black depths.\n\nYour senses "+
"start to return to you, and the itching in your chest suddenly "+
"becomes a violent relex as your body rejects the salt water "+
"in your lungs.\n\nYou awkwardly crawl your way up onto the beach.\n\n");
        ppl[i]->move_living("up onto the beach",
			    VAMP_AREA_DIR + "beach1", 1, 0);
    }

}