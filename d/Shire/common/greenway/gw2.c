inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "/sys/stdproperties.h"
#include <tasks.h>
#include "/sys/macros.h"

object shadow;

#define STAND_PARENT	"/d/Shire/common/"
#define STAND_DIR     STAND_PARENT + "greenway/"

#define SHADOW STAND_DIR + "dirty_shadow"
#define MIN_AWARE 10



//   Prototypes
void give(object ob);

int give_id;

void
create_shire_room()
{
    set_short("The Greenway");
    set_long("@@long_desc");

    add_item(({ "field", "fields" }), "The crops in the fields are bending in "
      + "the wind\n");
    add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
      + "and mules. There are also a few that indicate horses.\n");
    add_item(({ "bird", "birds" }), "They are only small black specks in the "
      + "sky.\n");
    add_item("puddle", "You wouldn't want to fall into that.\n");

    add_exit(STAND_DIR + "gw1", "north", "@@north");
    add_exit(STAND_PARENT + "hollin/f0000", "east");
    add_exit(STAND_PARENT + "gondorlink", "south", "@@south");
    add_exit("/d/Shire/common/obj/club/tree","west",0,1);

    reset_shire_room();

}

string long_desc() {

    string str;

    str = "You are travelling on an old road winding its way through "
    + "the fields surounding it. The tracks on the road are "
    + "quite fresh and implies that the road is in constant use. "
    + "You can hear the birds sing in the distance. In the "
    + "middle of the road is a big puddle. A new path leads "
    + "west into a clearing.\n";

    return str;

}

int south()
{
    if(!this_player()->query_dirty_shadow())
    {
	    if (TP->resolve_task(TASK_ROUTINE, ({TS_DEX,SS_AWARENESS})) <= 0)
	    {
            write("As you tread your way south you stumble and fall into the "
              + "puddle.\n");
            say(QCTNAME(this_player()) + " goes south but stumbles and falls into the "
              + "puddle.\n");
            tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) + 
                "Someone heads south on the Greenway. They stumble and " +
                "fall in the puddle.\n");
            give_id = set_alarm(0.1, 0.0, &give(this_player()));
            return 1;
	    }
    }

    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) + 
        " went south on the Greenway and disappears.\n");
    return 0;

}

int north() {

    if(!this_player()->query_dirty_shadow()) 
    {

        if (TP->resolve_task(TASK_ROUTINE, ({TS_DEX,SS_AWARENESS})) <= 0)
        {

            write("As you tread your way north, you stumble and fall into the "
              + "puddle.\n");
            say(QCTNAME(this_player()) + " goes north but stumbles and fall "
              + "into the puddle.\n");

            tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) + 
                "Someone comes north on the Greenway. They stumble and " +
                "fall in the puddle.\n");

            give_id = set_alarm(0.1, 0.0, &give(this_player()));
            return 1;
        }
    }
    
    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) + 
        " goes north up the Greenway.\n");
    return 0;
}

void
give(object ob) {

    remove_alarm(give_id);
    shadow = clone_object(SHADOW);
    shadow->shadow_me(ob);
    shadow->destruct_dirty_shadow();
}


public void reset_shire_room()
{
    ::reset_shire_room();
}
