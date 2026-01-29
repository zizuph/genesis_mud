#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define HARD_TO_SWIM 19

inherit FLOTSAM_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define H1 "/d/Krynn/common/herbs/bull_kelp"
#define H2 "/d/Krynn/common/herbs/sargassum"

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Choppy waters of the Blood Bay");
    set_long("@@long_descr");

    add_item(({"water","sea","vessel","waters",
	"rocks"}),"To the west towards the ruins of a vessel " +
      "trapped on the rocks the waters get very rough. " +
      "Those not careful, or weak at swimming could easily " +
      "get dashed against the rocks. \n");

    add_invis_exit(FROOM + "nowhere","north","@@no_go");
    add_invis_exit(FROOM + "rock_pool1","east","@@return_to_shore");
    add_invis_exit(FROOM + "nowhere","south","@@no_go");
    add_invis_exit(FROOM + "bay2","west","@@swim_check");


    set_tell_time(45);
    add_tell("Icy waves crash over you.\n");

    seteuid(getuid(TO));
    set_search_places(({"sea","water","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + "You are swimming in the choppy waters " +
    "of the Blood Bay, just west of the rockpools. To your " +
    "west are very rough and dangerous waters, " +
    "where many a fool has probably drowned, but past that you can make out the ruins of a vessel that " +
    "has been thrown against the rocks. \n";
}

int
no_go()
{
    write("You try and swim in that direction, but wind and waves " +
      "push you back. \n");
    return 1;
}

int
return_to_shore()
{
    write("You swim back to the rockpools. \n");
    return 0;
}

int
swim_check()
{
    if (this_player()->query_skill(SS_SWIM) < random(HARD_TO_SWIM)
      + random(11))
    {
	if(TP->query_prop(MAGIC_I_BREATH_WATER) > 0)
	{
	    write("You foolishly swim towards the ruins of the vessel, "+
	      "but the waves are too strong!\n\n\n\n" +
	      "You get caught in a tidal rip and get pulled down "+
	      "into the turbulent waters...\n\n\n\n "+
	      "Fortunately, you can breath water, so manage to "+
	      "make it to the surface after an exhausting swim.\n");
	    TP->add_fatigue(-200);
	    return 1;
	}
	write("You foolishly swim towards the ruins of the vessel, " +
	  "but the waves are too strong! \n \n \n \n " +
	  "You get caught in a tidal rip and get pulled down into " +
	  "the dark, turbulent waters... \n \n \n \n " +
	  "Your lungs feel as if they are about to explode! \n \n");
	say(QCTNAME(this_player()) + " is pulled down into the depths by a tidal rip! \n");

	TP->set_hp(0);
	TP->heal_hp(-200);
	TP->do_die(TO);

	return 1;
    }
    write("Fortunately, you are a good swimmer and are unaffected " +
      "by the rough waters. \n");
    return 0;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob))
    {
	if (!ob->id("corpse"));
	{
	    tell_room(TO, "The " + ob->short() + " slowly sinks "
	      + "into the deep darkness of the Blood bay waters, "
	      + "and is lost forever.\n", ({TO, ob}));
	}

	ob->move("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");
    }
    
    if (interactive(ob))
        start_room_tells();
}

