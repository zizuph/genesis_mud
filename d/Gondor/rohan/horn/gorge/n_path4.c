inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

string	find_tracks();
string footprint_func();

void create_helmsdeep_room()
{
    object door;

    set_short_desc("A narrow path");
    set_extra_long("A narrow path outside the Hornburg. The path winds "+
    "between the wall to the south and the sheer brink of the Rock to the "+
    "north. To the south is the postern-door of the keep. ");

    set_track_dir1("east");

    KEEP;
    BRINK;
    WALL;
    GORGE;
    CLIFFS;
    MOUNTAINS;

    add_item("path", "The rocky path winds close to the brink.\n");
    add_item("rock","The keep is built on the Rock.\n");

    remove_item("ground");
    remove_item("track");
    remove_item("tracks");
    remove_item("footprints");

    add_item(({ "ground", "track", "tracks" }), find_tracks);
    add_item("footprints", footprint_func);

    add_exit(ROH_DIR+"horn/gorge/n_path3","east",0);

    door = clone_object(ROH_DIR + "horn/doors/postern_door_in");
    door->move(TO);
}

string find_tracks()
{
    string track_desc;
    int skill;

    skill = TP->query_skill(SS_TRACKING);
    switch(skill)
    {
        case 0..TRACK_LOW :
            track_desc = "You find nothing special. ";
            break;
        case TRACK_LOW + 1..100 :
            if(TP->query_prop(FOUND_ORC))
                track_desc = "You find some orc tracks leading from the "+
                "wall to the "+ track_dir1 +". ";
            else
                track_desc = "You find nothing special. ";
            break;
        default :
            break;
    }
    return BSN(track_desc);
}

string footprint_func()
{
    string str;

    if(TP->query_prop(FOUND_ORC) && TP->query_skill(SS_TRACKING) > TRACK_LOW) 
    {
        str = "There are two deep footprints in the ground, as if someone "+
        "has jumped down from a height. A track of footprints leads to "+
        "the east. ";
        TP->add_prop(FOUND_TRACK, 1);
    }
    else
        str = "You find no footprints. ";
    return BSN(str);
}
