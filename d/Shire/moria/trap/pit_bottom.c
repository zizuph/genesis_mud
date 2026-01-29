#include "defs.h"
#include <language.h>

inherit MINES_FILE;

#define SPIKES    7
#define SPIKE_WC 30

CreateMines()
{
    set_short("bottom of a plate trap");
    set_long("Bottom of a plate trap.\n");
}

recieve_victim(object who, int depth)
{
    int wc = 80;
    int speed;          
    int num_spikes;
    int i;
    mixed ret;

    if (!living(who))
	return;

    speed = ftoi(sqrt(2.0*9.8*itof(depth))); // v = sqrt(2gs). 
					     // Gives a value in m/s.
					     // 10 m/s = 36 km/s.
    wc += speed*20;				   
    num_spikes = 4 + random(4);

    who->catch_msg("WC = " + wc + "\n");
    TellRoom(who, 0, "$You $land on " + LANG_WNUM(num_spikes) +
	     " nasty spikes!!\n");

    for (i=0;i<num_spikes;i++)
    {
	ret = who->hit_me(wc, DT_IMPALE, TO, -1);
	produce_message(who, 0, ret[0], ({
	    "$You miraculously $avoid the &first spike!",
	    "$You $are fortunate with the &first spike, it didn't hurt!",
	    "$You $feel a bit of pain as the &first spike impales $your &body!",
	    "The &first spike pierces into $n's &body! Ouch!",
	    "The &first spike stings badly as it impales $n's &body!!",
	    "The &first spike impales deeply into $n's &body!!",
	    "The &first spike gores deeply into $n's &body!!!",
	    "The &first spike penetrates $n's &body, leaving a nasty hole!",
	    "$You $land heavily upon the &first spike!! It makes an ugly hole through $his &body!!!"
	    }), ([ "&first": LANG_WORD(i+1), "&body": ret[1] ]));
    }

    if (HP(who) <= 0)
    {
	TellRoom(who, 0, 
		 "$You $sigh deeply, as $your last breath dies out.\n");
	who->do_die(TO);
    }
}


