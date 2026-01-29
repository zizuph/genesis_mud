/* created by Aridor 06/19/93 */
/*Adapted by Macker for griffon quest 07/12/94*/

#include "../local.h"

inherit ROOM_BASE

#include "/sys/money.h"
#include <ss_types.h>
#include <macros.h>

#include RND_MEET

object* monster = ({});
int find_something = 1;

void
init()
{
    object mon;

    ::init();
    ADA("climb");
    if (random(50) > 1)
        return;
    mon = RANDOM_MEET(TABLE);
    mon->move_living("xx",TO);
    monster += ({ mon });
    ADA("push");
    ADD("push","move");
}

void
reset_vin_mount_room()
{
   if (random(2))
     find_something = 1;
   monster -= ({ 0 });
   if (monster && sizeof(monster))
   {
       monster->command("emote leaves.");
       monster->remove_object();
       monster = ({ });
   }
}

void
create_vin_mount_room()
{
    set_short("On a ridge");
    set_long("The road proceeds on top of a ridge downwards to the east " +
         "and upwards to the south. You see a heap of stones lying " +
         "beside the road and a big rock stands up to your north.\n");

    OUTSIDE;

    add_item(({"rock","big rock","block","stone","block of stone"}),
         "This big rock is leaning against the wall of the mountain " +
         "as if it were a child leaning on it's mother for support. " +
         "It is rough in texture, and you think you might be able to " +
         "climb it. In fact, you think you see something resting on a " +
         "cliff slightly higher than the top of the rock. It looks " +
         "like a nest of some kind!\n");

    add_exit(ROOM + "road6","east",0,15);
    add_exit(ROOM + "road8","south",0,15);

    add_item("ridge","It's a ridge sloping down to the north, east and west, " +
         "except for the big rock which is north of you also.\n");
    add_item("nest", "You can't see it well from here, but it does " +
         "appear to be a large nest resting on a cliff above you. " +
         "You could probably reach that cliff by climbing the rock in " +
         "front of you.\n");
    add_item(({"track","ground","road","gravel","mountain track"}),
         "The track itself is simply laid out with small stones and " +
         "gravel.\n");
    add_item(({"mountains","mountain","mountainside"}),
         "These are high mountains indeed, rocks and occasional " +
         "shrubs are scattered everywhere, it is definitely " +
         "a very hostile area.\n");
    add_item(({"shrubs","rocks"}),
         "The mountainsides are covered with rocks with a few " +
         "shrubs making their living in between.\n");
    add_item(({"stones","heap","heap of stones","pile"}),
         "It is a heap of stones, each about the size of a fist, " +
         "piled up to mark the track.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_heap");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    reset_room();
}

mixed
search_heap(object player, string str)
{
    int x;
    if ((str == "heap" || str == "heap of stones" || str == "stones" ||
     str == "pile") && find_something)
      {
      find_something--;
      x = random(30) + 2;
      MONEY_MAKE_CC(x)->move(player);
      return "You find " + x + " copper coins and pick them up.\n";
      }
    else
      return 0;
}

int
climb(string str)
{
    if(!(str == "rock" || str == "big rock" || str == "stone" ||
     str == "big stone"))
      {
      NF("Climb what?\n");
      return 0;
      }
    if((TP->query_skill(SS_CLIMB)) < 20)
      {
      say(QCTNAME(TP) + " tried to climb up the big rock but failed.\n");
      NF("You try to climb the big rock but almost break "
         + "your limbs when you fall back down.\n");
      return 0;
      }
    write("You skillfully climb up the big rock.\n");
    TP->move_living("climbing up the big rock",GRIFFON_LANDING);
    return 1;
}


int
push(string str)
{
    if (str != "rock")
      return 0;
    write("The rock is just too heavy to be moved.\n");
    say(QCTNAME(TP) + " tries to move the rock but fails.\n");
    return 1;
}
