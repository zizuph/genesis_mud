
#include "../local.h"
#include <ss_types.h>


inherit "/std/object";

void
create_object()
{
    set_name("statue");
    add_name("draconian");
    add_name("draconian_statue");
    set_adj("small");
    add_adj("draconian");
    set_long("@@statue_desc@@");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 0);
}

string
statue_desc()
{
    string str = "";

    if (TP->query_stat(SS_INT) > 30 && !TP->test_bit("Krynn",2,6))
    {
	TP->add_prop("_player_m_pal_lib_audition",
		     ({"say Oh! You are here to see Astinus?", "ponder",
		       "say Ah yes, Astinus seems to be expecting you.",
		       "draconians"}));
	str = "You feel it might be a good idea to learn more about " +
	  "draconians from Astinus.\n";
    }
    return "This is a wooden statue of a draconian.\n" + str;
}

