#include "local.h"
inherit TDIR+"plain_base";

#include <macros.h>

void
create_plains_room()
{
    set_short("On the plains");
    set_long("You are standing in the middle of the plains. The only " +
	     "difference here is that many people surround you looking " +
	     "at you with begging and pleading eyes. Obviously, these " +
	     "people are refugees.\n");
    
    add_std_exits();

    set_auto_reset("tblqueshu",7+random(7));
    reset();
}

void
make_teh_people()
{
    auto_reset_objs->set_village("Que Teh");
}

void
reset_plains_room()
{
    set_alarm(0.0,0.0,make_teh_people);
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 1;
}

