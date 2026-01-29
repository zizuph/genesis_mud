#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define HARD_TO_CLIMB 30
#define LAIR "/d/Ansalon/balifor/flotsam_forest/dark_forest/lair"

inherit FOREST_OUT;
object dragon;

void
reset_flotsam_room()
{
    if(!objectp(dragon))
    {
        setuid();
        seteuid(getuid());
        
	dragon = clone_object(FNPC + "g_dragon");
	dragon->move(TO);
	LAIR->load();
	LAIR->reset_treasure();
    }
}

void
create_flotsam_room()
{
    set_short("In the center of a clearing before a great oak tree");
    set_long("@@long_descr");

    add_item("clearing","@@long_descr");
    add_item(({"great oak tree","ancient oak tree","ancient tree",
	"great tree","oak tree","oak","tree","trunk"}),
      "In the center of the clearing is an ancient oak tree of " +
      "gigantic size. Its lowest branches, being as thick as a man " +
      "is tall, start five metres up the oaks trunk. At the base of " +
      "the trunk great roots extend out and burrow into the ground.\n");
    add_item(({"great roots","roots"}),"Great roots extend out " +
      "from the base of the tree's trunk. You notice a large " +
      "cavern-like tunnel has been burrowed at the base of " +
      "the tree between two large roots. Noxious gas belches out " +
      "from its depths.\n");
    add_item(({"cavern-like tunnel","tunnel"}),"A large cavern-like " +
      "tunnel disappears down under the tree. Noxious yellow gas rises " +
      "from it.\n");
    add_item(({"fog","yellowish fog"}),"The air is thick with a " +
      "yellowish fog that smells strongly of chlorine.\n");
    add_item(({"yellow gas","gas","noxious-smelling gas"}),
      "From out of the tunnel rises noxious-smelling gas, filling the " +
      "clearing with a yellowish fog.\n");
    add_item(({"branches","branch"}),"About five metres up the oak " +
      "tree great branches, as thick as a man is tall, protrude from " +
      "the trunk.\n");
    add_item(({"animal trail","trail"}),"To the southeast an almost " +
      "unnoticeable animal trail leads into the forest.\n");
    add_item(({"green grass","grass"}),"Deep green grass grows " +
      "throughout the clearing. Although green, it looks decidedly " +
      "unhealthy.\n");
    add_item(({"forest","twisted forest","dark and twisted forest"}),
      "Surrounding the clearing is a dark and twisted forest.\n");

    add_exit(FOREST_PATH + "/dark_forest/path5","southeast",0);

    add_cmd_item(({"tree","up tree","up oak tree","oak tree"}),"climb",
      "@@climb_tree");
    add_cmd_item(({"tunnel","cavern","cavern-like tunnel"}),"enter",
      "@@enter_tunnel");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in a clearing in the center of a dark and twisted " +
    "portion of the forest. Dominating the clearing is the largest oak " +
    "tree you have ever seen. The green grass growing here is damp all " +
    "through the clearing, and an almost unnoticeable animal trail leads " +
    "into the forest to the southeast. A yellowish fog seems to permeate " +
    "throughout the clearing.\n";
}


string
enter_tunnel()
{
    string who;

    if(objectp(dragon))
    {
	who = L(TP->query_name());

	if(dragon->query_attack())
	    return "The dragon is in the way! You cannot enter " +
	    "the tunnel.\n";
	write("The green dragon roars in fury as you try and enter " +
	  "its lair!\n");
	say("The green dragon roars in fury as " + QTNAME(TP) +
	  " tries to enter its lair!\n");

        dragon->command("kill " + OB_NAME(TP));
        return "";
    }
    else
	write("You travel down the tunnel under the great oak tree...\n");
    TP->move_living("down into the tunnel",
      FOREST_PATH + "/dark_forest/lair",1,0);
    return "";
}


string
climb_tree()
{
    if(TP->query_skill(SS_CLIMB) < HARD_TO_CLIMB)
    {
	write("You attempt to frantically climb up the gigantic " +
	  "tree, but you fail miserably.\n");
	say(QCTNAME(TP) + " tries to scamper up the great oak tree " +
	  "but fails miserably.\n");
	return "";
    }
    write("You quickly scamper up the side of the " +
      "great oak and onto one of the great branches.\n");
    TP->move_living("up the great oak tree and disappears " +
      "into its folliage",FOREST_PATH + "/dark_forest/tree",1,0);
    return "";
}
