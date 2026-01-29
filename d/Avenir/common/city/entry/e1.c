// file name:        /d/Avenir/common/city/entry/e1.c
// creator(s):       Lilith, Sept 97
// revisions:	Lucius Oct 2008
// purpose:
// note:
// bug(s):
// to-do:   
#pragma strict_types

#include "entry.h"
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("practice arena");
    set_long("A small, circular practice arena situated "+
        "just east of the great First Gate. The arena "+
        "floor is covered in sand the colour of cream, "+
        "and around it a few benches have been placed. "+
        "At the end of each bench stands a tall urn "+
        "containing scented herbs and flowering plants. "+
        "The wall of the Inquisitors' enclave is directly "+
        "south, while west is a large stone building with "+
        "barred windows.\n");

    add_item(({"large building", "west building", "building",
        "stone building"}),
        "A stark and imposing building, made of the dark island stone excavated "+
        "during the building of the City walls. Its only embellishment is "+
        "the bars that have been installed over its few windows. It is "+
        "situated just beyond the arena, against a natural outcropping.\n");

    add_outside();
    add_bath();
    add_zig();
    add_urns();
    add_walls();

    add_exit(ENTRY +"courtyard", "east",  0);    
    add_exit(ENTRY +"e2", "west", 0);

    add_npc(MON + "dej-minha3", 1, &->equip_me());
    add_object(COM + "obj/bench", 3);
}
