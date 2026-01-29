/* 
 * /d/Gondor/clubs/storyteller/rooms/foyer.c
 * Copyright, Rolf Braun a.k.a. Elessar. Genesis, 1998.
 *
 * This is the first room of the clubhouse, connected to
 * /d/Gondor/pelargir/street/nroad2.c
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/open/room_chairs/room_chairs";
#include "/d/Gondor/defs.h"
#include "/d/Gondor/clubs/storyteller/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

static int fish_fed = 0;

string read_sign();
string read_plaque();
public nomask string sitting_look(string arg);
public nomask string long_func();

void
create_room()
{
    set_short("the foyer");
    set_long(long_func);
    add_item(({"lantern", "lanterns", "brass lantern", "brass lanterns"}),
        "You find six of them on the walls of the foyer, all of them " +
        "small and of brightly polished brass, providing ample lighting " +
        "for the entire room.\n");
    add_item(({"wall", "walls"}),
        "The walls are made of polished wood panels, and six lanterns " +
        "have been attached to them to provide light in the room.\n");
    add_item(({"panel", "panels", "wood panel", "wood panels"}),
        "The wood panels on the walls have all been polished down, " +
        "though they do look aged still.\n");
    add_chair("settee", "[down] [in] [the] [blue] 'settee'", 2);
    add_item(({"settee", "sofa", "blue settee"}), &sitting_look("settee"));
    add_item("sign", read_sign);
    add_item("plaque", read_plaque);
    add_item("table", "On top of the wooden table is a glass bowl " +
        "containing some colourful fish.\n");
    add_item(({"stairs","staircase","stair"}),
        "Over by the west wall is a stone staircase leading up to the " +
        "second floor.\n");
    add_item(({"bowl", "fish bowl", "fish", "colourful fish", "colorful fish",}),
        "A few fish in rather beautiful colours are swimming in a docile " +
        "manner back and forth in the glass bowl. The sight is " +
        "both fascinating and relaxing.\n");
    add_cmd_item("sign", "read", read_sign);
    add_cmd_item("plaque", "read", read_plaque);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
    add_exit(STORYT_DIR + "rooms/kitchen", "east", check_sitting, 0);
    add_exit(STORYT_DIR + "rooms/sittingroom", "north", check_sitting, 0);
    add_exit(STORYT_DIR + "rooms/2ndfloor", "up", check_sitting, 1);
    clone_object(STORYT_DIR + "obj/foyer_door_in")->move(TO);
}

string
read_sign()
{
    write(read_file(STORYT_DIR + "misc/sign2.txt"));
    return "";
}

string
read_plaque()
{
    write(read_file(STORYT_DIR + "misc/plaque.txt"));
    return "";
}

nomask public string
long_func()
{
    string  desc;
    desc = "You are in the foyer of this impressive, old building. " +
        "The detailed construction and fine furnishings reflect " +
        "conservative, good taste. The walls are made of polished, aged " +
        "wood panels, and small brass lanterns have been attached to them " +
        "to provide light. An inviting settee is against the east wall, and " +
        "directly across from it is a small table with a bowl of colourful " +
        "fish sitting on top of it. Above the fish bowl, a large golden "+
	"plaque has been fastened to the wall. There is a also a small "+
	"sign affixed to the opposing wall. " +
        "A staircase against the west wall leads to the upper floors. ";
    return desc + sitting_on_chair("settee", TP, 0);
}

nomask public string
sitting_look(string arg)
{
    string  occupants;
    if (arg == "settee")
    {
        return "The settee is covered with a brilliant blue fabric, and " +
            "has scrolled arms making it look very comfortable and soft.\n" +
            sitting_on_chair("settee", TP, 0);
    }
}

int
feed_fish(string str)
{
   if ((str != "fish") && (str != "the fish"))
       NFN0("Feed what? The fish perhaps?");
   if (fish_fed > 5)
   {
       write("You see some fishfood still floating in the surface, " +
           "and realize that they must have been fed recently.\n");
       return 1;
   }
   write("You stop to feed the fish, then gaze fondly into " +
       "the bowl for a while and watch the fish swim.\n");
   say(QCTNAME(TP) + " stops to feed the fish, then gazes fondly into " +
       "the bowl for a while and watches the fish swim.\n");
   fish_fed += 1;
   return 1;
}

int
goodbye_fish(string str)
{
   if ((str != "fish") && (str != "to fish") && (str != "to the fish"))
       NFN0("Goodbye to whom? The fish perhaps?");

   write("You wave goodbye to the fish in the bowl, your index finger " +
       "lightly brushing against the outside of the glass.\n");
   say(QCTNAME(TP) + " waves goodbye to the fish in the bowl, " +
       POSSESSIVE(TP)+" index finger lightly brushing against the " +
       "outside of the glass.\n");
   return 1;
}

public int
join_club(string str)
{
    int     result, total, required, age;

    if (!strlen(str) || str != "tales")
    {
        NF("What do you want to do? Try to 'spin tales with the " +
            "Storyteller Club?\n");
        return 0;
    }

    if (TELLERS->query_banned(this_player()->query_real_name()))
    {
        NF("You have been banished from this club, and are no longer "+
            "welcome here.\n");
        return 0;
    }

    if (this_player()->query_skill(SS_LANGUAGE) < 30)
    {
        NF("You do not seem to have mastered the basic skills of "+
            "reading and writing yet. These are prerequisites for "+
            "becoming a storyteller.\n");
        return 0;
    }

    total = this_player()->query_stat(SS_INT) + 
        this_player()->query_stat(SS_WIS) +
        this_player()->query_skill(SS_LANGUAGE);

    /* Require wanderer level intelligence and wisdom plus maxed
       Adventurer Guild language skill for non-goblins, require
       hero level intelligence and wisdom plus maxed Adventurer
       Guild language skill for goblins. */

    if (this_player()->query_race() == "goblin")
        required = 225;
    else
        required = 150;

    if (total < required)
    {
        NF("You do not feel mentally prepared for the task of writing "+
            "and telling stories yet, please try again later.\n");
        return 0;
    }

    FIX_EUID;

    /* Player's age in days */
    age = TP->query_age() * 2 / 86400;

    result = TELLERS->add_member(TP->query_real_name(), age);
    if (result == 0)
    {   
    /* Already a member */
        write("You are already a member!\n");
        return 1;
    }
    else if (result == -1)
    {
        write("Something went wrong, you could not join!\n");
        return 1;
    }
    else
    {
        TP->add_cmdsoul(TELLER_SOUL);
        TP->update_hooks();
        clone_object(STORYBOOK)->move(TP, 1);
        write("\t Welcome, New Spinner of Tales and Teller of Stories!\n\n");
        write("You receive your very own storybook.\n");
        say(QCTNAME(TP) + " decides to join the Storyteller Club.\n");

	log_file("story_club", this_player()->query_name()+
	    " joined the club on " + ctime(time())+".\n");

        return 1;
    }
}

public int
leave_club(string str)
{
    int     result;
    object  tmp;

    if (!strlen(str) || str != "tales")
    {
        NF("What do you want to forget? The tales?\n");
        return 0;
    }

    FIX_EUID;
    result = TELLERS->remove_member(TP->query_real_name());
    if (result == 0)
    {
        write("But you are no Storyteller, you have no tales to forget!\n");
        return 1;
    }
    else if (result == -1)
    {
        write("Something went wrong, and you could not leave!\n");
        return 1;
    }
    else
    {
        if (objectp(tmp = present("Storyteller_Book", TP)))
            tmp->remove_object();
        if (objectp(tmp = present("Storyteller_Spectacles", TP)))
            tmp->remove_object();
        if (objectp(tmp = present(KEY_ID, TP)))
            tmp->remove_object();

        if (TP->query_default_start_location() ==
          (STORYT_DIR + "rooms/start_room"))
            TP->set_default_start_location(TP->query_def_start());

        write("You hand in your storybook, as your mind is set " +
            "on leaving the Storyteller Club and " +
            "forgetting all the tales.\n");
        say(QCTNAME(TP) + " just left the Storyteller Club.\n");

        if (IS_LIBRARIAN(TP))
            TELLERS->remove_librarian(TP->query_name());

	log_file("story_club", this_player()->query_name()+
	    " left the club on " + ctime(time())+".\n");

        rm(STORYT_DIR + "tellers/" + capitalize(TP->query_real_name()) + ".o");
        return 1;
    }
}

public int
ban_club(string str)
{
    int     result;
    object  tmp, tmp2;

    if (!this_player()->query_wiz_level())
        return 0;

    if (!strlen(str))
    {
        NF("Whom do you want to ban from the Storytellers Club?\n");
        return 0;
    }

    FIX_EUID;
    result = TELLERS->ban_player(str);
    if (result == 0)
    {
        write("Something failed with the ban.\n");
        return 1;
    }
    else
    {
        write("You ban "+str+" from the Storyteller Club.\n");

        log_file("story_club", this_player()->query_name()+
	    " banned "+ str+" from the club on " + ctime(time())+".\n");

        rm(STORYT_DIR + "tellers/" + capitalize(str) + ".o");

        if (tmp = find_living(str))
        {
            tmp->catch_tell("You have been banished "+
                "from the Storyteller Club.\n");
            if (objectp(tmp2 = present("Storyteller_Book", tmp)))
                tmp2->remove_object();
            if (objectp(tmp2 = present("Storyteller_Spectacles", tmp)))
                tmp2->remove_object();
            if (objectp(tmp2 = present(KEY_ID, tmp)))
                tmp2->remove_object();

            if (tmp->query_default_start_location() == 
              (STORYT_DIR + "rooms/start_room"))
                tmp->set_default_start_location(tmp->query_def_start());
        }
        return 1;
    }
}

public int
pardon_club(string str)
{
    int     result;
    object  tmp;

    if (!this_player()->query_wiz_level())
        return 0;

    if (!strlen(str))
    {
        NF("Whom do you want to pardon from the banned list?\n");
        return 0;
    }

    FIX_EUID;
    result = TELLERS->pardon_player(str);
    if (result == 0)
    {
        write("Something failed with the pardon.\n");
        return 1;
    }
    else
    {
        write("You pardon "+str+" from the banned list.\n");

	log_file("story_club", this_player()->query_name()+
	    " pardoned "+str+" on " + ctime(time())+".\n");

        return 1;
    }
}

void
init()
{
    ::init();
    init_room_chairs();
    add_action(goodbye_fish, "goodbye");
    add_action(feed_fish, "feed");
    add_action(join_club, "spin");
    add_action(leave_club, "forget");
    add_action(ban_club, "ban");
    add_action(pardon_club, "pardon");
}

void
leave_inv(object obj, object to)
{
    leave_inv_room_chairs(obj, to);
    ::leave_inv(obj, to);
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (IS_STORYTELLER(obj) && !present("Storyteller's Book", obj))
    {
        obj->catch_msg("You notice that you no longer have your storybook, "+
	    "and pick up another.\n");
        clone_object(STORYT_DIR + "obj/storybook")->move(obj);
    }
}

void
reset_room()
{
    fish_fed = 0;
}
