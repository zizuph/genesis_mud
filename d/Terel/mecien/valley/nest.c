inherit "/std/container.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP              this_player
#define TO              this_object

void
create_container()
{
	object ob;
	
	seteuid(getuid(TO()));
	set_name("nest");
	set_adj("small");
	add_adj("bird's");
	set_long("The happy home of a bird family.\n");
	add_prop(OBJ_M_NO_GET,"But if you take the nest, where will the birds live?\n");
	ob = clone_object("/d/Terel/mecien/valley/guild/quest/feather.c");
	ob->move(TO());
}

void
reset_room()
{
	object ob;

 	seteuid(getuid(this_object()));
	if (present("mystic_quest_feather")) return;
	ob = clone_object("/d/Terel/mecien/valley/guild/quest/feather.c");
	ob->move(TO());
}

