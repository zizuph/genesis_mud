
inherit "/d/Krynn/std/dragon_base-no_fear";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>

string *friend_list = ({ "kentari", "teth", "morrigan", "karath"});


int	cloned; 

void
create_dragon_npc()
{
	set_colour("silver");
	set_age("ancient");
	set_short("platinum dragon hatchling");
	set_long("This little dragon is about as big as a large dog, " +
		"and compared to the rest of his kin, still a baby. " +
		"He looks quite comfortable warming himself by the " +
		"fire.  Not your average pet, but with Kentari's care " +
		"it has become quite loyal, and also guards his " +
		"master's home...if in the mood.\n");
	set_name("fizzy");
	add_name("hatchling");
	set_living_name("fizzy");
	set_gender(0);
	set_title("the Fireside Dragon, Companion to Kentari");
}

public void
attacked_by(object ob)
{
   ::attacked_by(ob);
   command("emote squeals in terror and searches frantically for aid");
   seteuid(getuid());
   if (cloned == 0)
clone_object("/d/Krynn/kentari/mnstrs/humaspirit")->move(environment());
   cloned = 1;
}
