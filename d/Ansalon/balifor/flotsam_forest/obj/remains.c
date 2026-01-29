inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

int map_taken = 0;
#define SKEL_MAP FOBJ + "map1"

void
create_object()
{
    set_name(({"remains","skeletal remains"}));
    set_short("the skeletal remains of a human");
    set_long("This is the broken remains of a red-robed " +
      "human, someone who has obviously fallen off the cliff " +
      "to his or her death. " + "@@map_message@@" + "\n");
    add_prop(OBJ_I_VOLUME, 30000);
    add_prop(OBJ_I_WEIGHT,50000);

    add_cmd_item(({"map from skeletal remains",
	"map from remains","map from skeletal remains of a human"}),
      ({"get","take"}),"@@get_map");
    setuid; seteuid(getuid());
}

void
remove_remains()
{
    tell_room(E(TO),"The skeletal remains of a human suddenly "+
      "crumbles to dust, and is blown away by the wind.\n");
    TO->remove_object();
}

string
map_message()
{
    if(map_taken == 1)
    {
	return "";
    }
    else
	return "Clutched tightly in its left hand is a map " +
	"of some sorts.";
}

string
get_map()
{
    if(map_taken == 1)
    {
	write("There is no map to get from the remains.\n");
	return "";
    }
    else
	write("You pull a map from the left hand of the " +
	  "skeletal remains of a human.\n");
    say(QCTNAME(TP) + " pulls a map from the left hand " +
      "of the skeletal remains of a human.\n");
    clone_object(SKEL_MAP)->move(TP);
    map_taken = 1;
    set_alarm(30.0,0.0,&remove_remains());
    return "";
}
