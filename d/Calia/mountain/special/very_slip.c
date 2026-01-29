#include <ss_types.h>
#include <macros.h>
#define TP this_player()

int
slip()
{
	if(random(3)==1)
    {
        object tp;
		int num;

		num = random(3);
        tp = TP;
        if (random(100) < tp->query_stat(SS_DEX))
        {
	if(num==0)
		{
		write("You pirouette around on one foot, nearly falling, "+
		"but deftly right yourself.\n");
		say(QCTNAME(tp)+" pirouettes around on one foot on the "+
			"slippery floor.\n");
            return 0;
		}
	if(num==1)
		{
		write("You sliiiiiiide for a long distance...it was fun!\n");
		say(QCTNAME(tp)+" slides down the hall.\n");
		return 0;
		}
	if(num==2)
		{
		write("You wildly wave your arms around to keep your "+
			"balance.\n");
		say(QCTNAME(tp)+" wildly waves "+tp->query_possessive()+
			" arms around, trying to keep balanced.\n");
		return 0;

		}
        }

		write("Your feet fly out from under you, "+
			"and you fall on your bum!\n");
		say(QCTNAME(tp)+" fell on the slippery floor of the "+
			"tunnel.\n");
        tp->add_hp(-1);
        return 1;
    }

    return 0;
}
