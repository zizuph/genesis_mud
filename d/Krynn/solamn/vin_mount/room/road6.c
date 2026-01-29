/* created by Aridor 06/19/93 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include RND_MEET

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

object* monster = ({});

void
init()
{
    object mon;

    ::init();
    ADA("push");
    ADD("push","move");
    ADA("swim");
    ADD("swim","enter");
    ADD("swim","jump");
    ADA("drink");
    if (random(50) > 1)
    return;
    mon = RANDOM_MEET(TABLE);
    mon->move_living("xx",TO);
    monster += ({ mon });
}

void
reset_vin_mount_room()
{
    monster -= ({ 0 });
    if (monster &&sizeof(monster))
    {
    monster->command("emote leaves.");
    monster->remove_object();
    monster = ({});
    }
}

void
create_vin_mount_room()
{
    set_short("At the lake.\nThere are two obvious exits: northwest, west");
    set_special_short("At the lake");
    set_long("You are on a road winding through the mountains. There is a " +
      "small lake here with clear and fresh mountain water. To your " +
      "east, an enormous rock blocks your way.\n" +
      "There are two obvious exits: northwest, west.\n");
    set_alarm(0.0,0.0,"add_prop",ROOM_I_TYPE,ROOM_BEACH);
    add_item("lake",
      "A small clear lake where you can see all the way to the " +
      "bottom. It does look inviting, too.\n");

    add_exit(ROOM + "road5","northwest",0,10);
    add_exit(ROOM + "road7","west",0,25);
    /*add_exit(CAVE + "cave1","squeeze","@@cannot_do_yet",3);*/
    set_noshow_obvious(1);

    add_item(({"darkness","opening"}),
      "You can only see black there. You probably have to squeeze " +
      "through the opening to get a closer look.\n");
    add_item("rock",
      "The rock is very big and stands up against the mountainside.\n");
    add_item(({"track","ground","road","gravel","mountain track"}),
      "The track itself is simply laid out with small stones and " +
      "gravel.\n");
    add_item(({"mountains","mountain","mountainside"}),
      "These are high mountains indeed, rocks and occasional shrubs " +
      "are scattered everywhere, it is definitely a very hostile area.\n");
    add_item(({"shrubs","rocks"}),
      "The mountainsides are covered with rocks with a few shrubs " +
      "making their living in between.\n");
    add_cmd_item(({"into opening","","under rock","into the opening","under the rock",
    "through opening","through the opening"}),
      "squeeze","@@squeeze_in");

    add_prop(OBJ_S_SEARCH_FUN, "search_rock");
    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop(LIVE_I_CAN_FISH, "alpine_lake"); 


}

int
swim(string str)
{
    if (str == "in lake" || str == "lake" || str == "in water" ||
      str == "water")
    {
    say(QCTNAME(TP) + " swims out into the lake but returns quickly to " +
      "the shore.\n");
    write("You swim out into the lake but since the water is freezing " +
      "cold you decide to return to the shore.\n");
    return 1;
    }
    return 0;
}

int
drink(string str)
{
    if (str == "from water" || str == "water" || str == "from lake")
    {
    if (TP->drink_soft(TP->drink_max() / 16,0))
    {
        say(QCTNAME(TP) + " drinks some water.\n");
        write("You drink some ice cold water and feel very refreshed.\n");
    }
    else
        write("Hmm, you are not thirsty at all at the moment.\n");
    return 1;
    }
    return 0;
}

int
push(string str)
{
    if (str == "rock")
    {
    say(QCTNAME(TP) + " tries in vain to move the rock aside.\n");
    write("You try as hard as you can, but you don't succeed in pushing " +
      "the rock aside. It looks like the rock is just too big and " +
      "heavy.\n");
    return 1;
    }
    return 0;
}

mixed
search_rock(object player, string str)
{
    if (str == "rock")
    return "You find an opening under the rock that leads somewhere into " +
    "darkness beyond.\n";
    return 0;
}

int
squeeze_in()
{
    write("You lie flat on the ground and squeeze yourself through the " +
      "opening.\n");
    SAY(" crawls under the rock.");
    TP->move_living("M",CAVE + "cave1",1,0);
    say(QCTNAME(TP) + " arrives crawling through the opening.\n");
    find_player("aridor")->catch_msg(TP->query_name() + " enters cave in THIEFAREA.\n");
    return 1;

    write("Hmm, wierd, you cannot squeeze through. You have the feeling " +
      "that there is enough room, though. Maybe you should attempt " +
      "this again later, after a Krynn wizard has gotten around to " +
      "digging into the mountain.\n");
    return 1;
}
