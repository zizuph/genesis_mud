/* Secret stairs down from dining room. Mortricia 921101 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()
#define DINING         (MANSION + "rooms/dining")

public void
reset_room()
{
    object rammer;

    if (!present("prisoner")) {
        seteuid(getuid());
        rammer = clone_object(MANSION + "mon/rammer");
        rammer->move(TO);
    }
}

public void
create_room()
{
    set_short("Secret staircase");
    set_long("You are standing in a secret staircase. " +
             "It's lit up by a torch.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"stair", "stairs"}),
      "The stairs are made of stone and carved long ago.\n");
    add_item(({"torch"}),
      "It's a simple looking torch, firmly attached to the wall.\n");
    add_item(({"wall", "walls"}),
      "The walls are made out of large stones. The stones must have " +
      "been cut by an expert, since there are almost no gaps between " +
      "them.\n");
    add_item(({"gap", "gaps"}),
      "Small amount of dirty water emerges from the gaps.\n");
    add_item(({"water", "amounts of water"}),
      "You better not drink the water.\n");

    add_exit(MANSION + "rooms/s_stair2", "down", 0);

    reset_room();
}

public void
do_puke(object who)
{
    if (!who) return;
    
    who->catch_msg("You puke up the dirty water and the rest of " +
                   "your stomach content.\n");
    tell_room(environment(who), QCTNAME(who) + " sudddenly throws up!\n");
    tell_room(environment(who), "Yuck! What a smell!\n");
    who->add_fatigue(-20);
}

public void
feel_strange(object who)
{
    if (!who) return;
    tell_object(who, "You feel that drinking that water wasn't " +
                     "good for you.\n");
    set_alarm(10.0, -1.0, &do_puke(who));
}

public int
do_drink(string what)
{
    if (!what) return 0;
    
    write("You lick up some dirty water on the wall.\n");
    say(QCTNAME(TP) + " licks up some dirty water on the wall.\n");
    
    set_alarm(10.0, -1.0, &feel_strange(TP));
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_drink, "drink");
    add_action(do_drink, "lick");
}
