inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


int flush_id;
int num_players;

void flush_players();

void create_room()
{

    num_players = 0;
    
    set_long( "\n\n\nYou find yourself plummetting "+
"very ungracefully into the chasm...\n\n\n"+
"The life that flashes by you is unpleasantly "+
"short...\n\n\nThe wave-swept rocks rise to "+
"meet you...\n" ); 

    
}

void
enter_inv(object ob, object from)
{
    num_players++;
    if (num_players == 1)
	flush_id = set_alarm(15.0, 0.0, flush_players);
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
	ppl[i]->catch_msg("\n\n\nS P L A S H !\n\n\nYou slam into the "+
                          "water surface at breakneck speed, luckily "+
                          "into a deep pool amongst the sharp rocks."+
                          "\n\n\nThe great force of the fall stuns "+
                          "you, and the shock of the cold water takes "+
                          "the breath from you.\n\n");
	tell_room(TO, 
		  QCTNAME(ppl[i])+" hits the water surface with a loud "+
                          "splash, that sounds too much like a thud for "+
                          "your liking, as you too hit the surface...\n", 
                          ppl[i]);
	ppl[i]->move_living("slamming into the water surface",
			    VAMP_AREA_DIR+"water1", 1, 0);
    }

}

