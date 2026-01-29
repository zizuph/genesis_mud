

inherit "/std/object.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP              this_player
#define TO              this_object

int		dug_up_flag;

void
init()
{
    ::init();
    add_action("do_dig", "dig");
}

void
create_object()
{
    set_short("shallow grave");
    set_long("@@long_desc@@");
    set_name("grave");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_S_SEARCH_FUN,"do_search");
}

string
long_desc()
{
    if (dug_up_flag)
	return BS("This shallow grave would probably be easy to miss, except "
	+ "that someone has recently dug it up! From the worn, unreadable "
	+ "marker you suspect that the grave is quite old; you wonder why "
	+ "anybody should take an interest in this sad relic of times long "
	+ "past.\n");
    else
	return BS("Studying the ground closely, you notice the faint traces "
    + "of a shallow grave, dug long ago in the permantly frozen ground. The "
    + "grave must have been covered with snow until just recently; you wonder "
    + "why the snow should have receeded now.\n");
}

string
do_search()
{
    if (dug_up_flag) return BS("You search the grave, but whoever dug it up "
    + "was thorough; no trace remains of the late occupant.\n");
    else return BS("You study the grave carefully, but find nothing remarkable. "
    + "It appears to have been hewn crudely from the frozen and stony earth, "
    + "a great deal of effort in what must have been incredibly harsh circumstances. "
    + "More love and hardship must have gone into this shallow depression than into "
    + "a dozen of the beautiful stone mausoleums that decorate more traditional "
    + "cemeteries.\n");
}

int
do_dig(string str)
{
    object  ob1, ob2, corpse, journal;
    
  seteuid(getuid(TO()));  
  if (!str) return 0;
  else  
    if (dug_up_flag)
    {
	write("But somebody has already dug it up!\n");
	return 1;
    }
    else
 	if (parse_command(str, environment(TP()), "%o 'with' %o", ob1, ob2))
	    if (ob1==TO() && member_array("shovel", ob2->query_names()) >= 0)
	    {
		write(BS("Using the "+ob2->query_short()+" you begin the arduous "
		+ "task of digging up the frozen ground. Eventually, you turn over "
		+ "a stone to reveal a hand! Furthur excavation unearths the corpse "
		+ "of a tall elf, remarkably well preserved in the bitter cold of "
		+ "these icy wastes. Exposed again to the air, however, the "
		+ "corpse has already begun to decay.\n"));
		say(BS(QCTNAME(TP())+" digs up the grave, unearthing the frozen corpse "
		+" of an elf.\n"));
		corpse=clone_object("/d/Terel/cedric/thane/corpse.c");
		corpse->move(environment(TO()));
		journal = clone_object("/d/Terel/cedric/thane/journal.c");
		journal->move(corpse);
		dug_up_flag = 1;
		return 1;
	    }
	    else write("ob name match failed miserably\n");
	else write("parse_command failed miserably\n");
    notify_fail("Dig what with what?\n");
    return 0;
}

void
reset_object()
{
    dug_up_flag = 0;
}
