// this will be the star the ring of the ancients makes
// -- Lilith

inherit "/std/object";
#include <stdproperties.h>
#define TO this_object()

int twinkle_id = 0;

void
create_object()
{
    set_name("star");
    add_name("_terel_ring_star");
    set_adj("golden");
    set_short("golden star");
    set_long("All that glitters isn't gold, but in this case, it is. "+
      "A golden star sparkles overhead. You wonder what it's purpose "+
      "is.\n");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_M_NO_DROP, 1);

}

void
do_fade()
{
    TO->remove_object();
}	

void	 
do_twinkle(int count)
{
    string str;

    if (!environment(TO))
    {
	TO->do_fade();
	return;
    }

    if (count > 4)
    {
	tell_room(environment(TO), "The star twinkles one last time and "+
	  "then fades from view.\n");
	twinkle_id = set_alarm(0.5, 0.0, do_fade);
	return;
    }

    switch (count)
    {
    case 0: str = "A golden star pulses overhead.\n";
	break;
    case 1: str = "The golden star starts spinning.\n";
	break;
    case 2: str = "The golden star rises higher!\n";
	break;
    case 3: str = "The golden star twinkles far above.\n";
	break;
    case 4: str = "The golden star hovers just out of reach.\n";
	break;
    }

    tell_room(environment(TO), str + "\n");

    twinkle_id = set_alarm(3.0, 0.0, &do_twinkle(++count));	
}
