#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>
#include <ss_types.h>

inherit FOREST_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("On top of a grassy topped cliff");
    set_long("@@long_descr");

    add_item(({"forboding forest","forest"}),
      "To your southwest stands a forboding forest as ancient " +
      "as the sea it overlooks.\n");
    add_item(({"edge of a grassy topped cliff","cliff",
	"grassy topped cliff"}),
      "The sound of the sea crashing against the side of the " +
      "cliff echoes up through the mists before you. Apart " +
      "from that, everything else is obscured from view.\n");
    add_item(({"mysterious wall of white mist","white mist",
	"mist","wall of white mist"}),
      "A wall of white mist rises from the edge of the cliff, " +
      "forming a visual barrier before you. It seems mysteriously " +
      "unaffected by the wind or temperature, and it seems to " +
      "hypnotically beckon to you. Tendrils of this mist curl " +
      "around your legs, as if trying to gently pull you into " +
      "its depths.\n");

    add_exit(CROOM + "road14","west",0);
    add_exit(CROOM + "road15","south",0);

    add_cmd_item("mist",({"enter","step into","jump into"}),
      "@@enter_mist");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"cliffs","grass","bluffs","coastline",
        "road","coast"}), 2);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand upon the edge of a grassy topped cliff, " +
    "although you would hardly know it, as much of its edge is " +
    "covered by a mysterious wall of white mist. To your " +
    "southwest stands the edge of a forboding forest.\n";
}

string
enter_mist()
{
    if(TP->query_stat(SS_WIS) < 30)
	return "The mists gently repel you from entering. " +
	"Perhaps one as small as yourself shound travel more " +
	"before attempting to step off a cliff into the mist?\n";
    write("Questioning your sanity, you step into the " +
      "mysterious white mist... and onto a narrow stone path!\n");
    TP->move_living("into the mist",
      CROOM + "mist1.c",1,0);
    return "";
}
