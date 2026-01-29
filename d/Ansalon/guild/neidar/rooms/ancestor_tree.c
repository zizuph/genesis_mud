/*
 *  This is the room based in the Tharkadan Mountain Ranges
 *  where Neidar dwarf members may choose to become a 
 *  Doomseeker.
 *
 *  WoHS can also retrieve the spell scroll for Stellar
 *  Alignment here.
 *
 *  Arman - April 2019
 */


#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"
#include <macros.h>
#include <time.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include "/d/Ansalon/guild/neidar/guild.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW
inherit "/lib/skill_raise";

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));

#define DOOMSEEKER_WARNING    "_has_been_given_doomseeker_warning"
#define OOTS_WARNING          "_has_been_given_oots_warning"
#define OOTS_MANAGER          "/d/Krynn/guilds/OotS/lib/oots_manager"
#define IS_OOTS(x)   ((x)->query_guild_name_lay() == "Holy Order of the Stars")

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_2H_COMBAT, "fight with two weapons", 0, 0, 90);

}

int
can_train_this_skill(object who, string skill, int step)
{
    return 1;
}

public int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;

    if (!sk || sscanf(sk, "%d", steps))
    {
        if (!ADMIN_MANAGER->query_is_doomseeker(TP))
        {
            write("What?\n");
            return 1;
        }
        return sk_list(steps);
    }

    tmp = explode(sk, " ");

    if(sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) -2], " ");
    else
    {
        skill = sk;
        steps = 1;
    }

    if(!ADMIN_MANAGER->query_is_doomseeker(TP))
    {
	write("Only dwarven Doomseekers can train here.\n");
	return 1;
    }

    if(can_train_this_skill(this_player(), skill, steps))
	return ::sk_improve(sk);
}

void
reset_tharkadan_room()
{
    return;
}

string
check_neidar()
{
    if(IS_MEMBER(TP))
        return " If you wish to walk the path of the Doomseeker, " +
        "you can <carve> your name upon the Tree of Ancestors.";
    else
        return "";
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_prop(LIVE_I_CAN_FISH, "alpine_lake");

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_snow");
    add_item(({"path","trail","pass","valley pass"}),
      "You stand on a trail running through the Tharkadan Mountain " +
      "Range. Here the trail heads north down to a to a narrow " +
      "valley filled with pines.\n");
    add_item(({"lake","crystal clear lake","clear lake","mountain lake"}),
      "A clear mountain lake to your south created from glacial melt " +
      "reflects the peaks of the Tharkadan Mountain Ranges.\n");
    add_item(({"pines","pine trees","trees","lodgepole pine trees"}),
      "In the valley down to your west lodgepole pines grow crowded " +
      "together, with the cabins made from these very pines the " +
      "only thing breaking the sea of deep green below.\n"); 
    add_item(({"ancient alpine oak", "ancient oak", "alpine oak", "oak",
      "tree of ancestors", "tree", "ancestors tree"}),
      "Before you stands a great alpine oak, known by the hill dwarves " +
      "of Krynn as the Tree of Ancestors. Its dark and weather-worn " +
      "bark is scarred with the carvings of the names of dwarves who " +
      "have taken a death-oath - a solemn vow to their ancestors " +
      "that they seek a glorious death to expunge some form of " +
      "dishonour that has befallen them.@@check_neidar@@\n");
    add_item(({"carvings","names","carving","name","carvings of " +
      "the names","carvings of names"}),
      "@@describe_carvings");

    add_exit("/d/Krynn/tharkadan/room/dwarf/village1","north",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    /* configure the trainer */
    set_up_skills();
    reset_tharkadan_room();
}

string
short_descr()
{
    return "on the edge of a crystal clear lake before the Tree of " +
        "Ancestors";
}

string
long_descr()
{
    return "You stand before an ancient " +
       "alpine oak with a broad crown stretching out above you like " +
       "gnarled and tortured limbs. Behind the oak to your south is " +
       "a crystal clear mountain lake, while behind you a path leads " +
       "to a narrow valley filled with pines.\n";
}

int
closed_village()
{
   write("You head down the trail to your north, but quickly return " +
     "after being gruffly rebuffed by the local hill dwarf residents.\n");
   say(QCTNAME(TP)+ " heads down the trail to your north into the " +
     "village, but quickly returns after being rebuffed by the local " +
     "hill dwarf residents.\n");
   return 1;
}

string
describe_carvings()
{
    mapping list = ADMIN_MANAGER->query_doomseeker_tree();
    string name_list = "";
    int size;

    if(!m_sizeof(list))
    {
    write("Upon the ancient alpine oak are carved the names of dwarves " +
        "who have taken the death-oath and become Doomseekers. Time " +
        "has worn the names and deeds of those you can see to the " +
        "point where they are no longer legible.\n");
       return "";
    }

    foreach(string name, mixed * var: list)
    {
        size++;
        name_list += capitalize(name);
        if (m_sizeof(list) - size == 1)
            name_list += ", and ";
        else if (m_sizeof(list) - size > 1)
            name_list += ", ";
    }

    write("Upon the ancient alpine oak are carved the names of dwarves " +
        "who have taken the death-oath and become Doomseekers. You can " +
        "make out the following names you could probably read more " +
        "about: " +name_list+ ".\n\n");

    return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(present("_stick_of_ancestors", ob))
    {
        set_alarm(1.5, 0.0, &ob->catch_tell("The petrified stick in your " +
            "possession creaks, as if twisting towards the ancient alpine " +
            "oak growing here. You get a strong urge to bury the stick " +
            "here.\n"));
    }

}

void
init()
{
    ::init();
    ADA("carve");
    ADA("read");
    ADA("bury");

    /* add the trainer's commands */
    init_skill_raise();
}

void
clone_spell_scroll()
{

    object scroll;
    seteuid(getuid(TO));

    tell_room(TO, "From being stuck between two high branches of the " +
        "ancient alpine oak, a furled piece of parchment is dislodged and " +
        "floats gently down to land before you.\n");

    scroll = clone_object("/d/Krynn/common/scrolls/stellar_alignment_scroll");
    scroll->move(TO, 1);
}

int
bury(string str)
{
    object stick;

    if(!objectp(stick = present("_stick_of_ancestors", TP)))
        return 0;

    if(str == "stick" || str == "petrified stick")
    {
        write("You dig a shallow hole in the hard frozen ground, place " +
            "the petrified stick in the ground, and cover it.\n");
        say(QCTNAME(TP)+ " digs a shallow hole in the hard frozen ground, " +
            "places an object in the hole and then covers it.\n");

        stick->remove_object();

        set_alarm(3.5, 0.0, &tell_room(TO, "The branches of the ancient " +
            "alpine oak start to sway, although not a breath of wind " +
            "blows through them.\n"));

        if(this_player()->query_advanced_spells_max())
        {
            if(!WOHS_MANAGER->query_scribed_spell(this_player(),"welunyoweth"))
            {
                set_alarm(7.0, 0.0, &clone_spell_scroll());
            }
        }
        return 1;
    }

    notify_fail("Bury what?\n");
        return 0;
}

int
carve(string str)
{
    string tree, name, death_details;

    NF("Carve what? Your name into the tree?\n");
    if (!str)
	return 0;

    str = lower_case(str);

    parse_command(str, TO, "[my] 'name' [in] / [upon] / [into] / [on] [the] %s", 
        tree);

    NF("Carve what? Your name into the Tree of Ancestors?\n");
    if(tree != "tree" && tree != "tree of ancestors")    
	return 0;

    if(!IS_MEMBER(TP))
    {
        say("As " +QTNAME(TP)+ " approaches the ancient alpine oak it " +
            "suddenly groans alarmingly, as if about to collapse. " +
            QCTNAME(TP)+ " steps away from it quickly!\n");
        notify_fail("You approach the ancient alpine oak to carve " +
            "your name into it when it suddenly groans alarmingly, " +
            "as if about to topple! You step away from it quickly.\n");
	return 0;
    }

    if(ADMIN_MANAGER->query_is_doomseeker(TP))
    {
        notify_fail("You have already carved your name into the Tree " +
            "of Ancestors and taken the death-oath of the Doomseekers!\n");
	return 0;
    }

    if(!TP->query_prop(DOOMSEEKER_WARNING))
    {
        write("\n" +
              "     By carving your name into the Tree of Ancestors\n" +
              "     understand that you are taking a death-oath before\n" +
              "     your past and present kin and family!\n\n" +
              "     You are publicly claiming ownership of an act of \n" +
              "     cowardice or dishonour that can only be redeemed\n" +
              "     through forsaking all and seeking nothing more than\n" +
              "     an honourable and glorious death.\n\n" +
              "     You will dedicate your entire fibre of your being to\n" +
              "     the hardest and most destructive life of battle that\n" +
              "     you can find. You will travel into treacherous \n" +
              "     wilderness and deliberately seek out mighty battles,\n" +
              "     fearsome foes, and overwhelming odds.\n\n" +
              "     You will forsake all armours and defensive abilities,\n" +
              "     leaving only your frenzy of battlerage between you\n" +
              "     and your enemies.\n\n" +
              "     In understanding this, carve your name into the Tree\n" +
              "     of Ancestors and begin your path of redemption as a\n" +
              "     Doomseeker of the Hill Dwarves.\n\n");

        TP->add_prop(DOOMSEEKER_WARNING, 1);
	return 1;
    }  

    if(IS_ELDER(TP) || IS_THANE(TP))
    {
        notify_fail("You need to forsake your claim as a leader of the " +
            "Neidar Clan to become a Doomseeker!\n");
	return 0;
    }

    if(IS_OOTS(TP))
    {
        if(OOTS_MANAGER->query_oots_god(TP) != "Kiri-Jolith")
        {
            string god_name = OOTS_MANAGER->query_oots_god(TP);
            mapping revelations = OOTS_MANAGER->query_oots_revelations(TP);

            if(member_array(lower_case("kirijolith"), m_indexes(revelations)) < 0)
            {
                write("Taking a death-oath goes against the teachings of " +
                    god_name+ ". You will need to seek out further " +
                    "revelations on the God of War, teachings which may " +
                    "resolve this conflict with the Holy Order of the " +
                    "Stars.\n");
                return 1; 
            }
            else if(!TP->query_prop(OOTS_WARNING))
            {
                write("Taking a death-oath goes against the teachings of " +
                    god_name+ ", however through the Revelation of Kiri-" +
                    "Jolith you realise the holy God of War will accept " +
                    "your oath. Know that by carving your name into the " +
                    "Tree of Ancestors, he that is known as Kijo the " +
                    "Blade will become your new patron with the Holy " +
                    "Order of the Stars.\n");
                TP->add_prop(OOTS_WARNING, 1);
                return 1; 
            }

            write("In taking a death-oath, Kijo the Blade, the god of " +
                "righteous warfare, becomes your new patron with the Holy " +
                "Order of the Stars.\n");
            tell_room(E(TP), QCTNAME(TP) + " has taken a new divine " +
                "patron within the Holy Order of the Stars!\n", TP);
            OOTS_MANAGER->set_oots_god(TP, "Kiri-Jolith");
        }
    }

    /* Add as Doomseeker and record player's current guild stat */
    ADMIN_MANAGER->add_doomseeker(TP);

    /* Clear the player's guild stat */
    TP->clear_guild_stat(SS_OCCUP);
    TP->remove_neidar_objs();
    TP->init_guild_member();

    tell_room(E(TP), QCTNAME(TP) + " carves " +HIS(TP)+ " name into the " +
        "ancient alpine oak alongside the names of other dwarven " +
        "Doomseekers that have taken the oath of seeking an honourable " +
        "death in battle!\n", TP);
    tell_object(TP,"You carve your name into Tree of Ancestors, accepting " +
        "the death-oath that forsakes all but an honourable death in " +
        "battle as a Doomseeker!\n");
 
    name = lower_case(TP->query_real_name());
    int join_time = time();

    mapping list = ADMIN_MANAGER->query_doomseeker_tree();

    if(!m_sizeof(list))
    {
        death_details = "";
    }
    else if(!IN_ARRAY(name, m_indexes(list)))
    {
        death_details = "";
    }
    else
    {
        mixed * carving_details = list[name];
        death_details = carving_details[1];
    }

    ADMIN_MANAGER->add_doomseeker_tree(name, join_time, death_details);
    return 1;
}

int
read(string str)
{    
    if(!str)
    {
       notify_fail("Read what? The carvings of one of the Doomseekers?\n");
       return 0;
    }

    str = lower_case(str);

    mapping list = ADMIN_MANAGER->query_doomseeker_tree();

    if(!m_sizeof(list))
    {
       notify_fail("There are no names carved on the ancient oak tree " +
           "that are legible.\n");
       return 0;
    }

    if(!IN_ARRAY(str, m_indexes(list)))
    {
       notify_fail("That name '" +str+ "' is not carved on the ancient " +
           "oak tree.\n");
       return 0;
    }

    mixed * carving_details = list[str];
    int time = carving_details[0];
    string death_details = carving_details[1];

    if(!strlen(death_details))
    {
        death_details = "A death-oath was taken on " +
            TIME2FORMAT(time, "d mmm yyyy")+ ". ";

        if(ADMIN_MANAGER->query_is_doomseeker(str))
        {
            death_details += "Redemption in battle is still being sought.";
        }
    }
    else
    {
        if(ADMIN_MANAGER->query_is_doomseeker(str))
        {
            death_details += "A death-oath was once again taken on " +
            TIME2FORMAT(time, "d mmm yyyy")+ ". Redemption in " +
            "battle is still being sought.";
        }
    }

     write("You read the carving made by the hill dwarf " +capitalize(str)+ 
         ".\n" +death_details+ "\n");

     say(QCTNAME(TP) + " examines a carving on the ancient oak tree.\n");

    return 1;
}
