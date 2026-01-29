#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

object dwarf;
string *herbs = HERB_MASTER->query_herbs( ({ "beach","intertide", }) );


void
reset_flotsam_room()
{
    if(!objectp(dwarf))
    {
	dwarf = clone_object(FNPC + "g_dwarf");
	dwarf->arm_me();
	dwarf->move(TO);
    }
}

create_flotsam_room()
{
    set_short("Under the pier on the rocky shore of the Blood Bay.\nA wooden sign");
    set_long("@@long_descr");
    add_item(({"sea","bloodsea","blood sea","waves"}),
      "Turbulent seas crash against the rocks around you. " +
      "To your west you can " +
      "just make out the wreck of an old fishing vessel " +
      "that has been thrown against one of the larger " +
      "rocks in the Bay. \n");
    add_item("path","A natural path that winds through the rockpools " +
      "to the east. It looks quite safe. \n");
    add_item(({"rock pools","pools","rockpools"}),"These rockpools " +
      "are full of sea life, most being trapped in " +
      "these pools after great storms when the tide rises " +
      "to great heights.\n");
    add_item(({"wreck","fishing vessel","vessel","old fishing vessel"}),
      "An old fishing vessel that has been dashed against " +
      "the rocks during some great storm. \n");
    add_item(({"wooden sign","sign"}),"This wooden sign has been posted up " +
      "here recently. On it is some writing in thick black paint. \n");
    add_item("ladder","A rickety ladder... looks unsafe.\n");
    add_item(({"rocky shore","shore"}),"You stand upon the rocky shore of Blood Bay " +
      "under the docks of Flotsam. To the east and at your feet " +
      "are many rockpools. To your west is the dangerous " +
      "waters of the Blood Bay. You think only a skilled or stupid " +
      "person would attempt to swim in that.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED,1);

    add_cmd_item(({"water","into water","in water",
	"sea","into sea","in sea","bloodsea","into bloodsea",
	"in bloodsea","waves","into waves","in waves"}),
      ({"enter","dive","jump","step","go"}),
      "@@into_sea");

    add_cmd_item("sign","read","@@read_sign");


    add_exit(FROOM + "rock_pool2","east",0);
    add_invis_exit(FROOM + "street04","up","@@up_ladder",0);

    set_tell_time(95);
    add_tell("You are sprayed with cool salty water as a wave crashes " +
        "against the rocks. \n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"rocks","rock pools","pools","shore",
        "coastline","sea","water"}), 2);

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + "You stand upon the rocky shore of " +
    "Blood Bay under one of the piers in the town of Flotsam. " +
    "To your north and west the Bloodsea crashes upon jagged rocks " +
    "sending salty spray periodically high up into the air. " +
    "Deep rockpools lie undisturbed before the rocks. A natural " +
    "path winds through these pools to the east. A ladder " +
    "has been attached to the side of one of the piers " +
    "supports, allowing you to return to the pier. \n" +
    "A wooden sign has been stuck here, facing the ladder. \n";
}

string
into_sea()
{
    write("You take a deep breath and dive into the " +
      "turbulent waters of the Blood Bay...\n");
    TP->move_living("into the waters of the Blood Bay",
      FROOM + "bay1.c", 1, 0);
    return "";
}

int
up_ladder()
{
    write("You nimbly climb up the rickety ladder... \n");
    return 0;
}

int
read_sign()
{
    write("   _________________________\n" +
      "  |                         |\n" +
      "  |   Warning!!!            |\n" +
      "  |   All swimmers beware!  |\n" +
      "  |   The Blood Bay is      | \n" +
      "  |   extremely dangerous   | \n" +
      "  |   all year round. Swim  |\n" +
      "  |   at your own peril!    |\n" +
      "  |                         |\n" +
      "  |                         |\n" +
      "  |_________________________|\n" +
      "           |    | \n" +
      "           | @  | \n" +
      "           |    |\n \n");

    return 1;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}
