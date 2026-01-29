inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Shire/open/randomize.h"
#include "party.h"

string color;

void
create_armour()
{
    color = random_color();

    set_name(({ "party hat", "hat", PARTY_HAT_ID }));
    set_pname(({ "party hats", "hats" }));
    set_adj(color);
    set_short("party hat");

    set_pshort("party hats");
    set_long(break_string("Not only is this hat is the opportunity of "
	+ "distinguishing yourself from others you have always been waiting for, "
	+ "but it also serves to determine if you're a funny guy or gal. "
	+ "'Now why would I wanna be that?' I hear you say... Well: funny guys and "
	+ "funny gals are almost always invited to parties! Excellent!\n", 70));

    set_ac(0);
    set_at(A_HEAD);
}
