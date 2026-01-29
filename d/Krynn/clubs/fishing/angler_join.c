/* created by Arman March 2021 */

#include "/d/Krynn/common/defs.h"
#include "fishing.h"
#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>

inherit R_FILE

#define PALAN_EXIT   "/d/Krynn/solamn/palanthas/nobles/w05"

create_krynn_room()
{
    set_short("the Lodge of Distinguished Hunters and Anglers");
    set_long("You stand within the entry to an old noble estate " +
        "that is being used as the lodge for those of the Palanthas " +
        "chapter of the Distinguished Hunters and Anglers " + 
        "association. This lodge clearly is one of many fishing " +
        "enthusiasts, with the walls lined with the biggest of the " +
        "members' trophies.\nThe lodge is open to new members interested " +
        "in fishing. You can <become fishing hobbyist> " +
        "to take up fishing casually or <become an avid fisherman> " +
        "to make it your professional craft! If you lose your club " +
        "token you can <replace satchel> here as well.\nYou can also " +
        "<abandon my fishing obsession> to give it up.\n");

    add_item(({"trophies", "trophy", "members' trophies", 
        "members trophies"}),
        "Along the walls of the lodge are displayed the most exceptional " +
        "catches of members of the association. Of note are a gold-gilded " +
        "trophy board, a silver-gilded trophy board, and a bronze-gilded " +
        "trophy board. Members can 'hang fish on trophy board' if they " +
        "have caught a bigger fish for all to marvel over!\n");
    add_item(({"gold-gilded trophy board", "gold trophy board", 
        "gold board", "gold trophy"}),
        "@@gold_board");
    add_item(({"silver-gilded trophy board", "silver trophy board", 
        "silver board", "silver trophy"}),
        "@@silver_board");
    add_item(({"bronze-gilded trophy board", "bronze trophy board", 
        "bronze board", "bronze trophy"}),
        "@@bronze_board");

    clone_object(FISH_DIR + "angler_board")->move(TO, 1);
    add_exit(PALAN_EXIT, "east", "@@exit_lodge");

}

mixed 
check_fish(string board)
{
    mapping list = FISHING_MANAGER->query_club_trophy();
    mixed fish_type = ({ });
    int order;

    switch(board)
    {
        case "gold":
            order = 1;
            break;
        case "silver":
            order = 2;
            break;
        default:
            order = 3;
            break;
    }

    if (!m_sizeof(list))
    {
        fish_type = ({"", "The trophy board is currently empty. " +
            "An angler could <hang> a fish on to the trophy " +
            "board if they like.\n", 0 });
    }
/*
    else if (member_array(order, m_indexes(list)) == -1)
    {
        fish_type = ({"", "The trophy board is currently empty. " +
            "An angler could <hang> a fish on to the trophy " +
            "board if they like.\n", 0 });
    }
*/
    else if (m_sizeof(list) < 3)
    {
        if(m_sizeof(list) == 1)
        {
            if(board != "gold")
                fish_type = ({"", "The trophy board is currently empty. " +
                    "An angler could <hang> a fish on to the trophy " +
                    "board if they like.\n", 0 });
            else
            {
                mixed * first_fish = list["one"];
                fish_type = ({ first_fish[0], first_fish[1], first_fish[2] });
            }
        }
        else
        {
            if(board == "bronze")
                fish_type = ({"", "The trophy board is currently empty. " +
                    "An angler could <hang> a fish on to the trophy " +
                    "board if they like.\n", 0 });
            else
            {
                mixed * first_fish = list["one"];
                mixed * second_fish = list["two"];

                if(first_fish[2] >= second_fish[2])
                    if(board == "gold")
                        fish_type = ({ first_fish[0], first_fish[1], first_fish[2] });
                    else
                        fish_type = ({ second_fish[0], second_fish[1], second_fish[2] });
                else
                    if(board == "gold")
                        fish_type = ({ second_fish[0], second_fish[1], second_fish[2] });
                    else
                        fish_type = ({ first_fish[0], first_fish[1], first_fish[2] });
            }
        }
    }
    else
    {
        mixed * first_fish = list["one"];
        mixed * second_fish = list["two"];
        mixed * third_fish = list["three"];

        if((first_fish[2] >= second_fish[2]) &&
           (first_fish[2] >= third_fish[2]))
        {
            if(board == "gold")
            {
                fish_type = ({ first_fish[0], first_fish[1], first_fish[2] });
            }
            else if(board == "silver")
            {
                if(second_fish[2] >= third_fish[2])
                {
                    fish_type = ({ second_fish[0], second_fish[1], 
                        second_fish[2] });
                }
                else
                {
                    fish_type = ({ third_fish[0], third_fish[1], 
                        third_fish[2] });
                }
            }
            else
            {
                if(second_fish[2] >= third_fish[2])
                {
                    fish_type = ({ third_fish[0], third_fish[1], 
                        third_fish[2] });
                }
                else
                {
                    fish_type = ({ second_fish[0], second_fish[1], 
                        second_fish[2] });
                }
            }
        }
        else if((second_fish[2] >= first_fish[2]) &&
           (second_fish[2] >= third_fish[2]))
        {
            if(board == "gold")
            {
                fish_type = ({ second_fish[0], second_fish[1], second_fish[2] });
            }
            else if(board == "silver")
            {
                if(first_fish[2] >= third_fish[2])
                {
                    fish_type = ({ first_fish[0], first_fish[1], 
                        first_fish[2] });
                }
                else
                {
                    fish_type = ({ third_fish[0], third_fish[1], 
                        third_fish[2] });
                }
            }
            else
            {
                if(first_fish[2] >= third_fish[2])
                {
                    fish_type = ({ third_fish[0], third_fish[1], 
                        third_fish[2] });
                }
                else
                {
                    fish_type = ({ first_fish[0], first_fish[1], 
                        first_fish[2] });
                }
            }
        }
        else if((third_fish[2] >= first_fish[2]) &&
           (third_fish[2] >= second_fish[2]))
        {
            if(board == "gold")
            {
                fish_type = ({ third_fish[0], third_fish[1], third_fish[2] });
            }
            else if(board == "silver")
            {
                if(first_fish[2] >= second_fish[2])
                {
                    fish_type = ({ first_fish[0], first_fish[1], 
                        first_fish[2] });
                }
                else
                {
                    fish_type = ({ second_fish[0], second_fish[1], 
                        second_fish[2] });
                }
            }
            else
            {
                if(first_fish[2] >= second_fish[2])
                {
                    fish_type = ({ second_fish[0], second_fish[1], 
                        second_fish[2] });
                }
                else
                {
                    fish_type = ({ first_fish[0], first_fish[1], 
                        first_fish[2] });
                }
            }
        }
    }

    return fish_type;
}

string
gold_board()
{
    mixed fish_type = check_fish("gold");
    string player = fish_type[0];
    string fish_desc = fish_type[1];
    int weight = fish_type[2];
    string weight_desc;

    string str = "The gold-gilded trophy board holds the BIGGEST fish " +
         "caught and displayed by the association.\n";

    if(!weight)
    {
        str += fish_desc;
    }
    else
    {
        /* Display whole kilograms or grams. */
        if (weight > 1000)
            weight_desc = (weight / 1000) + " kilograms";
        else
            weight_desc = weight + " grams";

        str += "Hanging upon the board is " +LANG_ADDART(fish_desc)+
            " under which is a small plaque that reads:\n\n" +
            "            " +capitalize(LANG_ADDART(fish_desc))+ ", " +
            "weighing " +weight_desc+ ".\n\n" +
            "            Caught by " +capitalize(player)+ ".\n\n";
    }

    return str;
}

string
silver_board()
{
    mixed fish_type = check_fish("silver");
    string player = fish_type[0];
    string fish_desc = fish_type[1];
    int weight = fish_type[2];
    string weight_desc;

    string str = "The silver-gilded trophy board holds the second biggest " +
         "fish caught and displayed by the association.\n";

    if(!weight)
    {
        str += fish_desc;
    }
    else
    {
        /* Display whole kilograms or grams. */
        if (weight > 1000)
            weight_desc = (weight / 1000) + " kilograms";
        else
            weight_desc = weight + " grams";

        str += "Hanging upon the board is " +LANG_ADDART(fish_desc)+
            " under which is a small plaque that reads:\n\n" +
            "            " +capitalize(LANG_ADDART(fish_desc))+ ", " +
            "weighing " +weight_desc+ ".\n\n" +
            "            Caught by " +capitalize(player)+ ".\n\n";
    }

    return str;
}

string
bronze_board()
{
    mixed fish_type = check_fish("bronze");
    string player = fish_type[0];
    string fish_desc = fish_type[1];
    int weight = fish_type[2];
    string weight_desc;

    string str = "The bronze-gilded trophy board holds the third biggest " +
         "fish caught and displayed by the association.\n";

    if(!weight)
    {
        str += fish_desc;
    }
    else
    {
        /* Display whole kilograms or grams. */
        if (weight > 1000)
            weight_desc = (weight / 1000) + " kilograms";
        else
            weight_desc = weight + " grams";

        str += "Hanging upon the board is " +LANG_ADDART(fish_desc)+
            " under which is a small plaque that reads:\n\n" +
            "            " +capitalize(LANG_ADDART(fish_desc))+ ", " +
            "weighing " +weight_desc+ ".\n\n" +
            "            Caught by " +capitalize(player)+ ".\n\n";
    }

    return str;
}

int
exit_lodge()
{
    write("You depart through the doors of the Lodge of " +
        "Distinguished Hunters and Anglers.\n");
    return 0;
}

void
init()
{
    ::init();
    ADA("become");
    ADA("abandon");
    ADA("replace");
    ADA("hang");
    add_action("hang","tack");
}

int
become(string str)
{
    NF("Become what? Fishing hobbyist or avid fisherman?\n");
    if (!str)
	return 0;

    // Club join
    if(str == "fishing hobbyist")
    {
        if(IS_ANGLER(TP))
        {
            notify_fail("You are already an angler!\n");
            return 0;
        }

        tell_room(E(TP), QCTNAME(TP) + " has become a fishing " +
             "hobbyist and joined the anglers club!\n", TP);
        tell_object(TP,"You have become a fishing hobbyist and " +
             "joined the anglers club!\nYou are provided a bait " +
             "satchel.\n");
        FISHING_MANAGER->add_member(TP);

        setuid();
        seteuid(getuid());
        object club_obj = clone_object(CLUB_OBJ);
        club_obj->move(TP, 1);
        return 1;
    }
    // Craft guild
    if(str == "avid fisherman")
    {
        tell_object(TP,"The craftsman branch of the anglers " +
             "is not open to new members yet. Come back again " +
             "when it is!\n");
        return 1;
    }

    return 0;

}

int
abandon(string str)
{
    string army;
    object club_object = present("_angler_club_object_", TP);

    NF("Abandon your fishing obsession?\n");
    if (!str)
	return 0;

    NF("Abandon what? Your fishing obsession?\n");
    if (str != "my fishing obsession")
	return 0;    

    NF("You are not currently an angler!\n");
    if(!IS_ANGLER(TP))
        return 0;

    tell_object(TP, "You abandon your fishing obsession.\n");
    FISHING_MANAGER->remove_member(TP);
    if (objectp(club_object))
        club_object->remove_object();

    return 1;
}

int
replace(string str)
{
    object club_object = present("_angler_club_object_", TP);
    object bait_obj = clone_object(CLUB_OBJ);

    NF("Replace what? Your bait satchel?\n");
    if (!str)
	return 0;

    NF("Replace your bait satchel?\n");
    if ((str != "bait satchel") && (str != "satchel") && 
        (str != "my bait satchel"))
        return 0;

    NF("You aren't an angler! You can't get a bait satchel until " +
        "you have joined the club!\n");
    if(!IS_ANGLER(TP))
        return 0;

    NF("You haven't lost bait satchel! No need to replace it.\n");
    if (objectp(club_object))
        return 0;
  
    tell_room(E(TP), QCTNAME(TP) + " gets a replacement bait satchel.\n", TP);
    tell_object(TP, "You get yourself a replacement bait satchel.\n");

    setuid();
    seteuid(getuid());
    bait_obj->move(TP, 1);

    return 1;

}

int
hang(string str)
{
    object fish;
    string fish_name, bait_str;
    object *fbait;
    object *oblist;

    if(!strlen(str))
    {
        FISHING_DEBUG("No strlen: " +str);
        notify_fail("Hang what?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[the] %s 'on' [the] %s", fish_name, bait_str))
    {
        notify_fail("Hang what fish on what?\n");
        return 0;
    }

    if (!sizeof(oblist = FIND_STR_IN_ARR(fish_name, all_inventory(this_player()))))
    {
        notify_fail("You possess no " + fish_name + " to hang.\n");
        return 0;
    }
      
    fbait = filter(oblist, &->id("global_fish_obj"));

    if(!sizeof(fbait))
    {
        notify_fail("You have no fish that the association will " +
            "accept to be hung here.\n");
        return 0;
    }

    fish = fbait[0];

    NF("Hang what fish on the trophy boards?\n");
    if ((bait_str != "trophy board") && 
        (bait_str != "board") && 
        (bait_str != "the trophy boards") && 
        (bait_str != "trophy boards"))
        return 0;

    NF("You aren't an angler! You can't hang fish here if you aren't " +
        "a member of the association!\n");
    if(!IS_ANGLER(TP))
        return 0;

    mixed * first_fish = check_fish("gold");
    mixed * second_fish = check_fish("silver");
    mixed * third_fish = check_fish("bronze");

    int new_fish_weight = fish->query_prop(OBJ_I_WEIGHT);
    string new_fish = fish->query_short();
    string angler = this_player()->query_real_name();

    if((first_fish[2] >= new_fish_weight) &&
       (second_fish[2] >= new_fish_weight) &&
       (third_fish[2] >= new_fish_weight))
    {
        write(capitalize(LANG_ADDART(new_fish))+
            " isn't bigger than what is currently hanging on any of the " +
            "trophy boards!\n");
            return 1;
    }

    FISHING_MANAGER->add_club_trophy(angler, new_fish, new_fish_weight);

    tell_room(E(TP), QCTNAME(TP) + " hangs " +LANG_ADDART(fish->query_fish_short())+
        " up on the trophy boards!\n", TP);
    tell_object(TP, "You hang " +LANG_ADDART(fish->query_fish_short())+ 
        " up on the association's trophy boards, as one of the biggest " +
        "fish caught!\n");

    fish->remove_object();

    return 1;

}