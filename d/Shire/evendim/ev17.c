inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "ev13","west",0,1
#define EXIT2 EVENDIM_DIR + "hut","east",0,1

void
create_er_room()
{
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "quiet riverside";
    grass = "blue-green";
    extraline = "Upon this fair quiet riverside a hut has "+
    "been constructed, and part of a boat lies between "+
    "the hut and the bank of the river.";
    add_item("bank","The riverbank is a sharp, short one "+
      "separating the blue-green grass from the brown muddy "+
      "water by only a slim band of sand.\n");
    add_item("hut","It's a badly constructed hut made by orcs.\n"+
      "All the same, you enter it by going east.\n");
    add_item("river", "@@river_long");
    add_item("boat", "This is not yet a boat. Only the keel has been made.\n");
    add_exit(EXIT1);
    add_exit(EXIT2);
    reset_shire_room();
}

is_orc(obj) { return obj->id("_invading_orc_"); }

void
reset_shire_room()
{
    object *arr;
    int i,s;
    if (!(s = sizeof(arr = all_inventory(this_object()))) ||
      (s = sizeof(filter(arr, "is_orc", this_object()))) < 4)
    {
	for (i=0; i<(4-s); i++)
	    clone_object(EVENDIM_DIR + "npc/invading_orc")->move(TO);
    }
}

string river_long()
{
    if((this_player()->query_skill(SS_LOC_SENSE) > 15))
	return "This is the Brandywine making its way south.\n";
    return "A river on its way south.\n";
}
