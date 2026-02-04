inherit "/std/container";
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"


/*
 * contains a precious gem, but main purpose is the hint
 */
void
create_container() {

    seteuid(getuid());
    set_name("box");
    set_short("box");
    set_adj("old");
    set_long("@@long_desc");
    add_prop(CONT_I_WEIGHT,500);
    add_prop(CONT_I_MAX_WEIGHT,600);
    add_prop(CONT_I_VOLUME,0);
    add_prop(CONT_I_MAX_VOLUME,100);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_CLOSED,0);
    add_prop(OBJ_I_NO_GET,1);
    add_prop(OBJ_I_NO_DROP,1);
}


string
long_desc()
{
    return(break_string("This is a very old box shimmering in all " +
	"rainbow colors.\n",70));
}

