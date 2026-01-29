#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit FLOTSAM_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define PLAYER_I_FOUND_KEY  "_player_i_found_flotsam_key"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "beach","intertide", }) );
object quest_npc_octopus;
int octopus_found = 0;

void
reset_flotsam_room()
{
    if(objectp(quest_npc_octopus))
	return;

    octopus_found = 0;
}

void
create_flotsam_room()
{
    set_short("Amongst the rockpools under the pier");
    set_long("@@long_descr");
    add_item(({"sea","bloodsea","blood sea","waves"}),
      "Turbulent seas crash against the rocks around you. " +
      "\n");
    add_item("path","A natural path that winds through the rockpools " +
      "to the west. It looks quite safe. \n");
    add_item(({"rock","rocks"}),
      "All around you are the rocks that make up the rockpools.\n");
    add_item(({"rock pool", "rock pools", "rockpool", "rockpools",
	"pool", "pools"}), "These rockpools are full of life, most "
      + "being trapped in these pools after great storms when the "
      + "tide rises to great heights. A flash of light, such as "
      + "would reflect off a metallic substance, attracts your "
      + "attention. It seemed to come from one of the larger "
      + "rockpools.\n");
    add_item(({"large rockpool", "large rockpools", 
	"larger rockpool", "larger rockpools"}), "Taking a closer "
      + "look at the larger rockpools your eye catches the flash "
      + "of light, such as would reflect off a metallic "
      + "substance. It seems to have come from a niche deep down "
      + "in one of them.\n");

    add_item("niche", "@@octopus_descr");
    add_item("corpse","@@corpse_descr");
    add_item("key","@@key_descr");

    add_exit(FROOM + "rock_pool1","west",0);

    set_tell_time(95);
    add_tell("You are sprayed with cool salty water as a wave crashes " +
        "against the rocks. \n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"rocks","rock pools","pools","shore",
        "coastline","sea","water"}), 2);

    reset_flotsam_room();
}


void
init()
{
    ::init();
    add_action("fish_key", "fish");
}


string
long_descr()
{
    return tod_descr1() + "You stand upon the rocky shore of " +
    "Blood Bay under one of the piers in the town of Flotsam. " +
    "To your north and east the Bloodsea crashes upon jagged rocks " +
    "periodically sending salty spray high up into the air. " +
    "Deep rockpools lie undisturbed before the rocks. A natural " +
    "path winds through these pools to the west. \n";
}


string
octopus_descr()
{
    write("You look in the niche...\n");

    if (!octopus_found)
    {
        write("A giant octopus rises from the waters.\n");
        say("A giant octopus rises from the waters.\n");
	quest_npc_octopus = clone_object(FNPC + "octopus");
	quest_npc_octopus->move(TO);
	octopus_found = 1;
	return "";
    }

    if (present("octopus", TO))
    {
	write("The giant octopus prevents you from reaching "
	  + "the niche.\n");
	quest_npc_octopus->command("kill " + TP->query_real_name());

	return "";
    }

    if (octopus_found == 1)
    {
	write("You notice the bloated remains of a sailor's corpse " +
	  "far down in the niche.\n");
	say(QCTNAME(TP) + " finds something in the large rockpool.\n");

	return "";
    }

    write("You find nothing.\n");

    return "";
}

string
corpse_descr()
{
    if(octopus_found == 1)
    {
	write("You look upon the bloated remains of a sailor " +
	  "who has obviously been thrown from his ship in a storm " +
	  "and didn't quite make it back to land, and whose remains " +
	  "are little more than fishfood far down the bottom of a deep " +
	  "niche in these rockpools. A key hangs around his neck.\n");

	return "";
    }

    if(octopus_found ==2)
    {
	write("You look upon the bloated remains of a sailor " +
	  "who has obviously been thrown from his ship in a storm " +
	  "and didn't quite make it back to land, and whose remains " +
	  "are little more than fishfood far down the bottom of a " +
	  "deep niche in these rockpools.\n");

	return "";
    }

    write("You see no corpse.\n");
    return "";

}

string
key_descr()
{
    if(octopus_found == 1)
    {
	write("A key hangs around the neck of the bloated remains " +
	  "of a sailor. You wonder if you can get it?\n");

	return "";
    }
    write("You see no key.\n");
    return "";
}


int
wielding_f_rod(object who)
{
    object *wielded_weapons;

    wielded_weapons = who->query_weapon(-1);

    if (!sizeof(wielded_weapons))
    {
	return 0;
    }

    if (wielded_weapons[0]->id("_flotsam_f_rod_"))
    {
	return 1;
    }

    return 0;
}

int
fish_key(string what)
{
    if (!strlen(what))
    {
	NF("Fish for what?\n");
	return 0;
    }

    if (!wielding_f_rod(TP))
    {
	NF("You have nothing to fish with!\n");
	return 0;
    }

    if ((what == "for key") || (what == "after key"))
    {
	if (octopus_found == 1)
	{
	    write("You begin fishing for the key...\n");
	    say(QCTNAME(TP) + " starts fishing in the rockpool.\n");
	    write("You manage to hook the key from the corpses "
	      + "neck, and quickly pocket it!\n");
	    clone_object(FOBJ + "chest_key")->move(TP);
	    TP->add_prop(PLAYER_I_FOUND_KEY, 1);
	    say(QCTNAME(TP) + " catches something!\n");

	    octopus_found = 2;

	    return 1;
	}

	write("You fish for a while but do not catch "
	  + "anything.\n");
	say(QCTNAME(TP) + " fishes for a while but does "
	  + "not catch anything.\n");

	return 1;
    }

    NF("That will not accomplish anything.\n");
    return 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}
