#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>

#define MAP "/d/Ansalon/balifor/flotsam_forest/obj/map2"

inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}


create_flotsam_room()
{
    set_short("Within the mists on a narrow stone path");
    set_long("@@long_descr");

    add_item(({"path","stone path","narrow stone path"}),
      "Beneath you is a narrow stone path, although the direction " +
      "it goes you cannot tell because of the obscuring white " +
      "mist. You think it would be necessary to have a map to " +
      "be able to follow this path, confidence in your senses, " +
      "and a little bit of blind faith in the gods to follow this " +
      "path!\n");
    add_item(({"mist","strange white mist","white mist"}),
      "Strange white mist swirls around you, obscuring your " +
      "vision of the surroundings, and disorienting your sense " +
      "of direction.\n");

    add_exit(CROOM + "road16","out",0);
    add_invis_exit(CROOM + "mist2","east","@@path");
    add_invis_exit(CROOM + "death_room","north","@@die");
    add_invis_exit(CROOM + "death_room","south","@@die");
    add_invis_exit(CROOM + "death_room","west","@@die");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand upon a narrow stone path. Strange white " +
    "mist rises from below, swirling around you and obscuring " +
    "your view of the surroundings... including the path you " +
    "stand on. The sound of crashing waves rises up from far " +
    "below, indicating quite a drop for one who steps off " +
    "the path. " +
    "\n";
}

int
die()
{
    write("You foolishly step off the path and fall down " +
      "to your doom!\n");
    say(QCTNAME(TP) + " steps off the path and disappears " +
      "into the mist screaming...\n");
    TP->set_hp(0);
    TP->heal_hp(-10000);
    TP->move_living("M",CROOM + "death_room.c",1,0);
    TP->do_die(TO);
    return 1;
}

int
path()
{
    if (sizeof(filter(deep_inventory(this_player()), &->id("mist_map"))))
    {
        write("You edge your way along the path...\n");
        return 0;
    }
    
    write("Without a map, you become disoriented and " +
      "stumble from the path!\n");
    say(QCTNAME(TP) + " stumbles off the path and disappears " +
      "into the mist screaming...\n");
    TP->set_hp(0);
    TP->heal_hp(-10000);
    TP->move_living("M",CROOM + "death_room.c",1,0);
    TP->do_die(TO);
    return 1;
}

public void
warn_about_map(object player)
{
    player->catch_msg("You have no map over the area and would surely die "
    + "should you try to traverse it without one.\n");
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    if (!sizeof(filter(deep_inventory(ob), &->id("mist_map"))))
        set_alarm(1.0, 0.0, &warn_about_map(ob));
    
    ::enter_inv(ob, from);
}