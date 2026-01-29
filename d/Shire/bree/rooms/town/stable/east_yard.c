/*
 *  /d/Shire/bree/rooms/town/stable/east_yard.c
 *
 * Bree Stables Rental location
 * Palmer, December 2002
 *
 */

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Shire/sys/defs.h"
#include "bree_stables.h"

inherit "/d/Shire/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Shire/std/room/room_tell";

#define QUEST_NAME "horse"
#define CORRAL "corral"

/* Globals */
static object Stable_master;

/* Function prototypes */
public string corral_desc();
int yard_security();

string
text_on_sign =
    "\t --------------------------------------------------------------- \n" +
    "\t| o                                                           o |\n" +
    "\t|                 T H E   B R E E  S T A B L E S                |\n" +
    "\t|     -----------------------------------------------------     |\n" +
    "\t|                                                               |\n" +
    "\t|     Fine Rohan-bred steeds for rent. My steeds are            |\n" +
    "\t|     trained to stay calm during combat, and make              |\n" +
    "\t|     excellent pack animals. You must pay a fee first.         |\n" +
    "\t|     This fee will cover the care of your steeds in the        |\n" +
    "\t|     future.                                                   |\n" +
    "\t|                                                               |\n" +
    "\t|     Initial fee <pay fee> ........................... 50 pc   |\n" +
    "\t|     Rental fee <rent adj1 adj2 horse/pony> ..........  1 pc   |\n" +
    "\t|     Example: rent muscular brown horse                        |\n" +
    "\t|                                                               |\n" +
    "\t|     Once you pay the fee, you may rent a steed anytime        |\n" +
    "\t|     afterwards for a nominal fee.                             |\n" +
    "\t|                                                               |\n" +
    "\t|     Smaller races, like hobbits, dwarves, or gnomes, can      |\n" +
    "\t|     rent ponies. Other races, like humans or elves, can rent  |\n" +
    "\t|     horses. I do not rent horses to goblins. They eat them.   |\n" +
    "\t|                                                               |\n" +
    "\t|     You may see what horses and ponies are corraled by        |\n" +
    "\t|     looking at the room or by examining the corral. Some-     |\n" +
    "\t|     times all the horses are rented. When this happens,       |\n" +
    "\t|     please be patient until others are returned or more       |\n" +
    "\t|     are found.                                                |\n" +
    "\t|                                                               |\n" +
    "\t|     Don't forget to return your horse so it can be cared for  |\n" +
    "\t|     when you are done otherwise I won't rent another steed    |\n" +
    "\t|     to you until the world is renewed again.                  |\n" +
    "\t|                                                               |\n" +
    "\t|     <stable horse/pony> .............................  free   |\n" +
    "\t|                                                               |\n" +
    "\t|                                                               |\n" +
    "\t|     Don't forget to visit the tack shop next door for         |\n" +
    "\t|     food and riding supplies.                                 |\n" +
    "\t|                                                               |\n" +
    "\t|                                    Keleren, Stable Master     |\n" +
    "\t| o                                                           o |\n" +
    "\t --------------------------------------------------------------- \n";

void
create_room()
{
    ::create_room();

    set_short("Eastern part of the Bree stable yard");
    set_long("Eastern part of the stable yard. To the north are the stables. " +
             "A white fence encloses the corral to the east. At the base of the " +
             "fence is a water trough. @@corral_desc@@" +
             "A large sign has been planted in the ground.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit("stable_yard", "west");
    add_exit("stable", "north");
    add_exit("club/foyer", "south");
    add_exit("corral", "east", yard_security, 0,1);
    add_item(("sign"), text_on_sign);
    add_item("corral", "@@corral_desc@@");
    add_item(({"fence", "white fence", "wooden fence"}),
        "A sturdy white wooden fence enclosing the corral. A broom leans " +
        "against the fence.\n");
    add_item("ground",
        "Its dirt, littered with hay here and there.\n");
    add_item("hay",
        "Hay is for horses.\n");
    add_item("broom",
        "An old broom, used for sweeping up the stable area.\n");
    add_item(({"trough", "water trough"}),
        "A large rectangular wooden trough filled with fresh water.\n");
    add_item(({"building", "large building", "wooden building",
            "stables", "stable"}),
        "A large wooden building with huge gates. Above the open gates a " +
        "horseshoe is nailed to the wall.\n");
    add_item("horseshoe",
        "It is a rusty old horseshoe, nailed in the upward position, " +
        "so the luck doesn't fall out.\n");
    add_item(({"gate", "gates"}),
        "These wooden gates are wide enough for horses to get in and " +
        "out of the stable.\n");

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from( ({ "trough", "water"}) );
    set_room_tell_time(45 + random(37));
    add_room_tell("A stable boy walks by and pours a bucket of water " +
        "in the trough.");
    add_room_tell("Some raucous hammering noise echos from the northwest.");
    add_room_tell("Neighing sounds come from the corral to the east.");
    add_room_tell("A horse trots up to the corral fence.");
    add_room_tell("An irritable dwarf trots by on a pony.");
    add_room_tell("A curious pony pokes her head over the fence, munching " +
        "on some hay.");
    reset_room();
    add_prop(ROOM_I_LIGHT, 1);

}

int
read_sign(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
        "[large] 'sign' [in] [the] [ground]"))
    {
        notify_fail("Read what? Your mind?\n");
        return 0;
    }
    write(text_on_sign);
    return 1;
}

public string
corral_desc()
{
    object other_room;
    mixed opeople;

    if (!LOAD_ERR(BREE_STABLES_DIR + "corral"))
        other_room = find_object(BREE_STABLES_DIR + "corral");
    else
        return "ERROR: We have a problem in the corral view. Please bug " +
            "report this.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return "Behind the corral fence you see no horses.\n";
    else
        return "Behind the corral fence you see " + COMPOSITE_LIVE(opeople) + ".\n";

}


int
yard_security()
{
    // Let the stable master and tack shop keeper run to corral when attacked
    if (TP->query_wiz_level() || TP->query_name() == "Keleren" ||
        TP->query_name() == "Kalrin" || TP->query_race() == "horse")
        return 0;

    write("You can't seem to climb over the corral fence.\n");
    return 1;
}


void
unlead_horse(object horse, object leader)
{
    horse->do_unlead(leader, 1);
    horse->remove_object();
    write("Keleren shouts, 'You found my horse!'\n");
    write("Keleren takes the reigns and leads the horse into the corral.\n");
    write("Keleren arrives from the east.\n");

    leader->remove_prop("_horse_trust_");

    //The horse is back, so let someone else do the quest.
    Stable_master->reset_quest_timer();

    if (!REWARD_QUEST(leader, QUEST_NAME))
    {
        write("say Thanks again.\n");
        return;
    }
    else
    {
        leader->remove_prop("_horse_quest");
        tell_object(leader,"You feel more experienced!\n");
        say(QCTNAME(leader) + " looks more experienced.\n");
    }
}


void
enter_inv(object ob, object from)
{
    object quest_horse;
    object leader_obj;
    object leader;
    int test;

    ::enter_inv(ob, from);
    if (present("__leader_object", ob))
    {
        leader_obj = present("__leader_object", ob);
        quest_horse = leader_obj->query_steed();
        leader = leader_obj->query_leader();

        test = member_array("_quest_steed_", quest_horse->query_names());
        if (test != -1)
        {
            //   We need to add this delay because the horse
            //   is still in the other room at this point
            write ("A large black horse comes galloping in from the west.\n");
            set_alarm(2.0, 0.0, &unlead_horse(quest_horse, leader));
        }
    }
}


public void
init()
{
    ::init();
    init_drink();
    add_action(read_sign, "read");
}


public void
reset_room()
{
    if (!Stable_master)
        Stable_master = clone_object(BREE_STABLE_MASTER);

    if (!present(Stable_master, this_object()))
        Stable_master->move(this_object());
}
