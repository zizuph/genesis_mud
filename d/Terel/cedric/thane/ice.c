inherit "/std/object.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP              this_player
#define TO              this_object

void
init()
{
	::init();
	add_action("do_say","say");
	add_action("do_say","intone");
}

void
create_object()
{
    	seteuid(getuid(TO()));
	set_name("ice");
	add_name(({"block","block of ice"}));
	set_adj("frozen");
	set_short("tremendous block of ice");
	set_long(BS("This enormous block of ice is remarkably clear; "
	+ "embedded deep within it you see a sword the likes of which you "
	+ "have never seen before. The ice seems unlikely to yield up "
	+ "its treasure, however, for it is as cold as death and as hard "
  	+ "as battle-tempered steel.\n"));
	add_prop(OBJ_I_WEIGHT,500000);
	add_prop(OBJ_I_VOLUME,500000); 
	add_prop(OBJ_S_WIZINFO, "The secret word that will destroy this "
	+ "block of ice\n   and place the sword in the player's hands is 'cael-lin'.\n");
}

do_say(string str)
{
	object ob;

	if (str=="Cael-lin"||str=="cael-lin")
	{
		write(BS("You stand over the block of ice, and pronounce the "
		+ "ancient syllables. A great power, long dormant, seems to "
		+ "rise up within you. The air around fills with the power of "
		+ "the invocation, and the ice begins to vibrate. Suddenly, "
		+ "the block of ice shatters, and you find yourself holding "
		+ "the ancient sword!\n"));
		ob = clone_object(CEDRICDIR+"thane/tsword");
		if (ob->move(this_player()))
		{
		    ob->move(environment(this_player()));
		    say(QCTNAME(TP())+" drops the sword.\n");
		    TP()->catch_msg("The ancient sword is too heavy; you drop it.\n");
		}
		ob->add_prop(OBJ_M_NO_GIVE, ob->sword_catch_give());
		say(BS(QCTNAME(TP())+" intones a name, and the air begins to "
		+ "crackle. Suddenly, the mighty block of ice shatters, and "
		+ "the ancient blade is glowing in "+TP()->query_possessive()+
		  " hand!\n"));
		remove_object();
		return 1;
	}
	else
		return 0;
}
