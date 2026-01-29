#include <ss_types.h>
#include <macros.h>
#define TP this_player()

int
slip()
{
	if(random(5)==1)
    {
        object tp;

        tp = TP;
        if (random(100) < tp->query_stat(SS_DEX))
        {
		write("You nearly fell on the slippery floor of "+
		"the tunnel, but regained your balance just in time.\n");
            return 0;
        }

		write("You fell on the slippery floor of the tunnel.\n");
		say(QCTNAME(tp)+" fell on the slippery floor of the "+
			"tunnel.\n");
        tp->add_hp(-1);
        return 1;
    }

    return 0;
}
