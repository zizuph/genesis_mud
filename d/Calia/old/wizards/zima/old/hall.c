inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

#define BBOARD          GUILDOBJ+"board.c"
#define MORE_OBJ 	"/std/board/board_more"

/*
 * The Minstrel Guild Headquarters: Great Hall
 * Here players join the guild by selecting an instrument.
 * Cedric 1/93
 */

int
check_enter()
{
    if (MEMBER(TP()))
    {
	TP()->catch_msg("You pass through the great hall and enter the inner "
	+ "sanctum.\n");
	return 0;
    }
    else
	TP()->catch_msg(("That way lies the inner sanctum of the Minstrels; "
	+ "only the initiated may pass.\n"));
    return 1;
}

string
do_mread()
{
    seteuid(getuid(TO()));
    clone_object(MORE_OBJ)->more(read_file(GUILD+"text/welcome"));
    return "";
}

void
create_room()
{
    set_short("The Great Hall of the Minstrels");
    set_long(BS("You stand in a great hall, with stone pillars and stained glass "
    + "windows that rise to dizzying heights far above your head. The architecture "
    + "here emphasizes vertical lines and light; the sunlight pouring through the "
    + "countless colored bits of glass plays along the walls and floor in a "
    + "brilliant show of ever-changing irridescence. Several pedestals, "
    + "each supporting a musical instrument, line the hall.\n")+"Near the front entrance "
    + "stands a podium, supporting a large book.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(GUILD+"entrance", "north");
    add_exit(GUILD+"nice", "south", "@@check_enter");
    add_item(({"book", "podium"}), BS("Here on an elegant marble podium sits"
    + "a large text, bound in leather and handsomely engraved. Perhaps you "
    + "should read it?\n"));
    add_cmd_item(({"book", "book"}), ({"read","mread"}), ({read_file(GUILD+"text/welcome"),"@@do_mread"})); 
    reset_room();
}

void
reset_room()
{
    object ob;
    
    seteuid(getuid());
    if (!present("lute", TO()))
    {
	ob=clone_object(GUILDOBJ+"lute_pedestal");
	ob->move(TO());
    }    
    if (!present("recorder", TO()))
    {
	ob=clone_object(GUILDOBJ+"recorder_pedestal");
	ob->move(TO());
    }
    if (!present("dulcimer", TO()))
    {
	ob=clone_object(GUILDOBJ+"dulcimer_pedestal");
	ob->move(TO());
    }
    if (!present("shawm", TO()))
    {
	ob=clone_object(GUILDOBJ+"shawm_pedestal");
	ob->move(TO());
    }
    if (!present("viol", TO()))
    {
	ob=clone_object(GUILDOBJ+"viol_pedestal");
	ob->move(TO());
    }
    if (!present("trumpet", TO()))
    {
	ob=clone_object(GUILDOBJ+"trumpet_pedestal");
	ob->move(TO());
    }
    if (!present("harp", TO()))
    {
	ob=clone_object(GUILDOBJ+"harp_pedestal");
	ob->move(TO());
    }
    
}
