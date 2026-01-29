inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    set_short_desc("A ramp to the keep");
    set_extra_long("On a steep ramp leading up to the gates of the "+
    "Hornburg. Below the ramp a road goes across the stream to the Dike. ");

    set_track_dir1("east");
    set_track_dir2("southwest");

    add_item(({"keep","hornburg"}),"The Hornburg has high walls and a "+
    "lofty tower within.\n");
    add_item("gates","The gates can't be seen clearly at this distance.\n");
    add_item("ramp",BSN("The ramp is too steep for riding; horses would have "+
    "to be led to the gates."));

    add_item(({ "ground", "track", "tracks", "footprints" }),
    	find_tracks);
    ROAD;
    STREAM;
    GULLY;
    DIKE;
    GORGE;
    CLIFFS;
    MOUNTAINS;

    add_exit(ROH_DIR+"horn/gorge/out_gate","southwest",0,4);
    add_exit(ROH_DIR+"horn/gorge/causeway","east",0);
}

