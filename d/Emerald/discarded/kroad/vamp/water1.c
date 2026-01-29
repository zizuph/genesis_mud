/*    Water1.c
 *    This is where the players end up after their fall
 *    from a great height, they are passed through the
 *    fallroom.c into this room via alarm.
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
    
    set_long( "\n\n\nThrough your fall-induced stupor, "+
           "you open your eyes to the sting of dark salt-"+
           "water, and you find your limbs unwilling to respond "+
           "to your attempts to find your way back to the "+
           "water surface.\n\n\n" ); 
    
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
	ppl[i]->catch_msg("You are powerless to resist the pull of "+
			  "the current while still stunned from the "+
                          "great fall. You get sucked under, quickly "+
                          "you float away...\n\n");
	tell_room(TO, 
		  QCTNAME(ppl[i])+" weakly struggles against the "+
		  "current as it draws XXX swiftly "+
                  "down and away.\n", ppl[i]);
	ppl[i]->move_living("pulled under by the current",
			    VAMP_AREA_DIR + "water2", 1, 0);
    }

}