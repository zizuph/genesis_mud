// file name:		~Avenir/common/dark/l3/l3_so.c
// creator(s):		Denis
// revision history:	Apr 96: Added logging event to statserv.
//			    -=Denis
//
// purpose:		Inheritable file for all roms that may contain
//			piece of source for Imps quest of Unterdark
// note:
// bug(s):
// to-do:

# include "/d/Avenir/common/dark/dark.h"
# include "l3_defs.h"
# include "/d/Avenir/smis/sys/statserv.h"

int can_contain_source;
object source_p;

int find_source(object player, int where)
{
    if(SOURCE_PLACER->query_has_source(where)&&can_contain_source)
    {
	can_contain_source=0;
	(source_p=clone_object(OBJ+"psource"))->move(player);
        source_p->set_destroy();

	STATSERV_LOG_EVENT("impquest", "Crystals gathered");

        return 1;
    }
    return 0;
}

reset_source()
{
    can_contain_source = 1;
}
