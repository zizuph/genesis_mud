// Tomato mush (after dropping a tomato)
// creator(s):   Kazz
// last update:  Lilith: Feb 1999 made into a leftover so it decays.
// purpose:      Used to replace a tomato that is dropped.
// note:	 
// bug(s):
// to-do:        


#include <macros.h>
#include <stdproperties.h>

inherit "/std/leftover";

void
create_leftover()
{
    set_name ("splattered tomato");
    set_pname("splattered tomatoes");
    add_name( "tomato" );
    add_name( "tomatoes" );
    set_short ("splattered tomato");
    set_pshort ("splattered tomatoes");
    set_long ("This mess seems to be a splattered ripe tomato.\n" );
    add_prop (OBJ_I_VALUE, 0);
    add_prop (OBJ_M_NO_GET, "You try to get the splattered tomato, "+
        "but it all slips through your fingers.\n");
}
