/* cv/underwater.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */
 
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/vampires/guild.h";
#include <stdproperties.h>


public object *diving = ({ });
/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, -10);
 	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.
	set_short("underwater river");
    set_long("Diving in darkness down a pool filled with water and shadows.\n");
    add_prop(ROOM_S_DARK_LONG, "Diving in darkness down a pool filled "+
      "with water and shadows.\n");
}

private void
diving_down(object ob, int count)
{
    string str;

    if (!ob)
	return;

    if (environment(ob) != this_object())
    {
	    diving -= ({ ob });
	    return;
    }

    if (count > 4)
    {
	    write("You finally break the surface, washing up in a "
            +"different grotto.\n");
	    ob->move_living("M", "/d/Avenir/common/dark/l1/grotto");
	    say(QCTNAME(ob) +" arrives dripping water.\n");
	    diving -= ({ ob });
	    return;
    }

    switch (count)
    {
        case 0: str = "You feel embraced by the warm water.\n";
	      break;
        case 1: str = "As you dive deeper, you feel the water tugging "
            +"at you.\n";
	      break;
        case 2: str = "You feel yourself tumbling in the water!\n";
		  break;
        case 3: str = "You are being tugged along in a rapid current.\n";
	      break;
        case 4: str = "Without a visual cue, you have become completely "
            +"disoriented.\n";
	      break;
    }

    if (query_interactive(ob))
	ob->catch_msg(str + "\n\n");

    set_alarm(3.0, 0.0, &diving_down(ob, ++count));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    diving = filter(diving, objectp);
    if (member_array(ob, diving) == -1)
    {
	    diving += ({ ob });
	    set_alarm(1.5, 0.0, &diving_down(ob, 0));
    }
}
