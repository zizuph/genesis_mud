/* created by Aridor 06/19/93 */

/* Navarre Nov 4th 2008, adding missing \n on add_items */

#include "../local.h"

inherit ROOM_BASE

#include RND_MEET

object* monster = ({});

void
reward_tour(object who)
{
    int exp = 40;
    int group = 4;
    int bit = 1;
    string ei_name = "Vingaard Mountain Top EI";

    if (who->test_bit("Krynn",group,bit))
      return;
    setuid();
    seteuid(getuid());
    STD_QUEST_LOG(ei_name, who, exp);
    who->set_bit(group,bit);
    who->add_exp_quest(exp);
    write("What an incredible view! You feel slightly more experienced!\n");
}


void
init()
{
    object mon;

    ::init();
    set_alarm(0.1,0.0,&reward_tour(TP));
    
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
    if (monster && sizeof(monster))
    {
	monster->command("emote leaves.");
	monster->remove_object();
	monster = ({});
    }
}

void
create_vin_mount_room()
{
    set_short("On Top");
    set_long("You have reached the top of the mountain. You can see "
         +   "in all directions. The Vingaard Mountains extend to the "
         +   "northeast and southwest. Very far away to the north you "
         +   "even catch a glimpse of sparkling water, this must be the "
         +   "ocean. To your southeast you can make out the Plains of "
         +   "Solamnia. There is a river bounding the plains to the east, "
         +   "and you can make out a small dark dot which could be "
         +   "Vingaard Keep. Strangely though, you can make out scattered "
         +   "black dots on the plains as well and wonder what this could "
         +   "portend.\n");

    OUTSIDE;

    add_exit(ROOM + "road11","down");

    add_item("top","There is no way up, only down in all directions.\n");
    add_item(({"dots","dot","water","keep","vingaard keep","plains"}),
	     "You cannot see any details, you are just too far away.\n");
    add_item(({"mountains","mountain"}),
	     "These are high mountains indeed, rocks and occasional " +
		"shrubs are scattered everywhere, it is definitely " +
		"a very hostile area.\n");
    add_item(({"shrubs","rocks"}),
	     "The mountainsides are covered with rocks with a few " +
		"shrubs making their living in between.\n");
}






