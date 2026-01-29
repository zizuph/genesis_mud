#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Before a quaint stone cottage");
    set_long("@@long_descr");

    add_item(({"cottage","stone cottage","quaint stone cottage"}),
      "@@long_descr");
    add_item(({"door","mahogany door","large mahogany door"}),
      "Before you stands a large mahogany door. It is closed.\n");
    add_item(({"white-brick wall","wall"}),
      "This is one of the four walls of the quaint cottage. " +
      "Vines on either side of the door crawl up the wall to " +
      "just below a window ledge on the second story.\n");
    add_item(({"vines","well-cultivated vines"}),
      "Well-cultivated vines crawl up the wall of the cottage " +
      "around the door and ending under a window ledge about a " +
      "meter above the door.\n");
    add_item(({"window","window ledge","ledge"}),
      "Above the door is a window with a small ledge below it.\n");
    add_item(({"trail","small trail"}),
      "A small trail leads away from the cottage to the " +
      "northeast.\n");

    add_exit(CROOM + "road12","northeast",0);

    add_cmd_item("door",({"enter","open"}),"@@enter_house");
    add_cmd_item(({"vines","vine"}),"climb","@@climb_vine");
    add_cmd_item("cottage","enter","@@enter_house");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand outside an old-fashioned stone cottage. " +
    "A large mahogany door graces the center of the white-" +
    "brick wall facing you, and well-cultivated vines crawl " +
    "up the wall on either side of it. A small trail " +
    "leads from the door to the northeast.\n";
}

string
enter_house()
{
    write("You open the large mahogany door and step into " +
      "the quaint stone cottage.\n");
    TP->move_living("into the quaint stone cottage",
      CROOM + "cottage1.c",1,0);
    return "";
}

string
climb_vine()
{
    if(this_player()->query_skill(SS_CLIMB) < 100)
    {
	write("You try and climb the vines that crawl up the " +
	  "side of the house, but slip and fall.\n");
	say(QCTNAME(TP)+ " tries to climb up the vines that crawl "+
	  "up the side of the cottage, but slips halfway up and " +
	  "falls back onto the small trail.\n");
	return "";
    }
    write("You nimbly climb up the vines...\n");
    TP->move_living("up the vines growing up the wall of the " +
      "cottage",CROOM + "cottage3.c",1,0);
    return "";

}
