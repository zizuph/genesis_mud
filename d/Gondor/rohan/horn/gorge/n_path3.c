inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    set_short_desc("A narrow path");
    set_extra_long("A narrow path outside the Hornburg. The path winds "+
    "between the wall to the south and the sheer brink of the Rock to the "+
    "north. Far to the east are the gates to the keep. ");

    set_track_dir1("east");
    set_track_dir2("west");

    KEEP;
    BRINK;
    WALL;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item("path","The rocky path winds close to the brink.\n");
    add_item("gate","The gates can't be clearly seen from here.\n");
    add_item(({ "ground", "track", "tracks", "footprints" }),
    	find_tracks);

    add_exit(ROH_DIR+"horn/gorge/n_path2","east",0);
    add_exit(ROH_DIR+"horn/gorge/n_path4","west",0);
}
