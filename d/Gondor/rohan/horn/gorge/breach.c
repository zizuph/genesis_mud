inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

static object sentinel1, sentinel2;

/* Prototypes */
void reset_room();
int  greet_them();
int  warn_them();

void
create_helmsdeep_room()
{
    set_short_desc("Breach in the Dike");
    set_extra_long("At the breach in Helm's Dike, where a stream "+
    "from above flows out. The road runs beside the stream here "+
    "through the breach. A rampart rises steeply on either side; "+
    "a ditch has been dug in front of the rampart. ");

    DIKE;
    ROAD;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item("breach", "The breach is wide and cannot easily be defended.\n");
    add_item("stream","The Deeping-stream flows gently through the breach.\n");
    add_item("rampart",BSN("The rampart looks to be a mile long. "+
    "It spans the entire opening of the gorge in a half circle."));
    add_item("ditch",BS("The ditch is deep, making an attempt to "+
    "force passage over the rampart very hard.\n"));
    add_item("tower", "The tower rises high upon the rock; no "+
    "details can be seen from here.\n");

    add_exit(ROH_DIR + "horn/gorge/road1"  ,"southwest", greet_them);
    add_exit(ROH_DIR + "horn/coomb/s_coomb","north"    , warn_them);

    FIX_EUID
    "/d/Gondor/rohan/horn/hide_out"->load_me();
    "/d/Gondor/rohan/horn/burg/tow_entr"->load_me();

    reset_room();
}
 
void
reset_room()
{
    sentinel1 = clone_npc(sentinel1, (ROH_DIR + "horn/npc/b_sentinel"));
    sentinel2 = clone_npc(sentinel2, (ROH_DIR + "horn/npc/b_sentinel"));
    sentinel1->team_join(sentinel2);
}

int
greet_them()
{
    object stopper, me = TP;

    if (stopper = present("_stopping_npc",TO)) 
    {
        if (!CAN_SEE(stopper,TP) || !CAN_SEE_IN_ROOM(stopper)) return 0;
        if (IS_EVIL(me))
        {
            stopper->command("say You are not allowed to enter!");
            write("The guard stops you from entering.\n");
            say("The guard stops " + QCTNAME(me) + " from entering.\n");
            return 1;
         }
         stopper->command("say Welcome to Helm's Deep. Help with guard "+
             "duty is always appreciated.");
         return 0;
    }
    return 0;
}

int
warn_them()
{
    object stopper, me = TP;

    if (stopper = present("_stopping_npc", TO))
    {
        if (!CAN_SEE(stopper,me) || !CAN_SEE_IN_ROOM(stopper))
            return 0;
        if (IS_EVIL(me))
            stopper->command("say Begone with you!");
         else
             stopper->command("say Watch out for orcs. They have become "+
                 "much bolder lately.");
    }
    return 0;
}
