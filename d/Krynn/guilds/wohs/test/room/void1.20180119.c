/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_BASE;

#define WOHS_TELL_ROOM(y, x)    tell_room(TO, x, 0, y)
#define COMPLETED_TEST    "_wohs_test_completed_test"

// Properties influencing alignment options
#define WOKE_GUARD                            "_wohs_test_woke_soldier"
#define KILLED_GUARD                          "_wohs_test_killed_soldier"
#define NO_INTRO                              "_wohs_test_did_not_intro_to_iriale"
#define NO_INTRO_2                            "_wohs_test_did_not_intro_to_iriale_second_time"
#define ENGAGED_ERGOTHIANS                    "_wohs_test_engaged_city_siegers"
#define DMG_TAKEN                             "_wohs_test_damage_taken"
#define KILLED_DUKE                           "_wohs_test_killed_duke"
#define STEAL_BOOK                            "_wohs_test_attempted_to_steal_grimoire"
#define MEMORISED_INVIS                       "_wohs_test_did_not_know_invis"
#define MEMORISED_SCRY                        "_wohs_test_did_not_know_scry"
#define SCRY_PROP                             "_wohs_test_successful_scry"
#define OBSERVE_PROP                          "_wohs_test_successful_observe"
#define WOHS_MIRROR_NUMBER_FAILED             "_wohs_test_mirror_number_failed_attempts"

int test_score = 100;
int total_hp;

void
reset_tower_room()
{
    return;
}

void
create_tower_room()
{
   set_short("a void of emptiness");
   set_long("You find yourself in a black void of emptiness. Are you standing? Or floating? " +
        "You don't know... your can see nothing, feel nothing, sense nothing. You realise " +
        "you are not even sure how long you have been within this void, as even your perception " +
        "of time has gone!\n");

   reset_tower_room();
}

void
align_evaluation(object player)
{
    if(player->query_prop(WOKE_GUARD))
    {
        WOHS_TELL_ROOM(player, "\n\nA strong, deep masculine voice booms through the void: " +
         C(player->query_real_name())+ " showed admirable traits in waking the " +
         "ensorcelled guard rather than slaying him in his sleep. It demonstrates a " +
         "principled, even noble, strength of character.\n");
        set_alarm(10.0,0.0, &WOHS_TELL_ROOM(player, "\n\nA dark, rasping voice whispers from " +
         "the void behind you: Noble strength of character? I would say foolish. " +
         C(HE(player))+ " potentially compromised the task given to " +HIM(player)+ 
         " with his soft principles.\n"));
        set_alarm(20.0,0.0, &WOHS_TELL_ROOM(player, "\n\nAn impassive, deadpan voice echoes " +
         "from the void around you: I would tend to agree. While idealistic and not the " +
         "most appropriate action, " +HE(player)+ " did ultimately retrieve the orders.\n"));
    }
    else if(player->query_prop(KILLED_GUARD))
    {
        WOHS_TELL_ROOM(player, "\n\nA strong, deep masculine voice booms through the void: " +
         C(player->query_real_name())+ " showed ignoble and opportunistic traits in slaying " +
         "the ensorcelled guard in his sleep which I found, quite frankly, disgusting. It " +
         "demonstrated a lack of principles, an inability to problem solve any better than " + 
         "your average goblin, and a weakness of character.\n");
        set_alarm(10.0,0.0, &WOHS_TELL_ROOM(player, "\n\nA dark, rasping voice whispers from " +
         "the void behind you: Hah! I would say any other action but the most efficient and " +
         "effective to be anything but foolish. " +C(HE(player))+ " deserves credit for not " +
         "compromising the task given to " +HIM(player)+ " through soft-hearted principles.\n"));
        set_alarm(20.0,0.0, &WOHS_TELL_ROOM(player, "\n\nAn impassive, deadpan voice echoes " +
         "from the void around you: I would tend to agree. In this case any other action " +
         "would be indulgent. Retrieving the orders was " +HIS(player)+ " primary objective, " +
         "which " +HE(player)+ " ultimately did achieve.\n"));
    }

    return;
}

void
performance_evaluation(object player)
{
    if(player->query_prop(NO_INTRO))
         test_score -= 5;

    if(player->query_prop(NO_INTRO_2))
         test_score -= 10;

    WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: " +
         C(player->query_real_name())+ " defeated a comprehensive range of foes we sent " +
         "against " +HIM(player)+ "... both magical and mundane.\n");

    if(player->query_prop(ENGAGED_ERGOTHIANS))
    {
         set_alarm(3.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe strong, deep masculine voice " +
         "booms through the void: Yet "+ C(player->query_real_name())+ " was incautious at best, " +
         "leaving the Kadothan Grove without suitable enchantments to avoid being attacked " +
         "by the besieging armies.\n"));
         test_score -= 10;
    }

    if(player->query_prop(KILLED_DUKE))
    {
         set_alarm(5.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: " +
         C(player->query_real_name())+ " also managed to slay the Duke, which I thought " +
         "wasn't possible in the scenarios we set. Very impressive.\n"));
         test_score += 20;
    }

    total_hp = player->query_max_hp();

    if(player->query_prop(DMG_TAKEN) > (2 * total_hp))
    {
        set_alarm(7.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe dark, rasping voice sneers from " +
         "the void: " +C(HE(player))+ " was physically broken by the trials by combat. " +
         C(HIS(player))+ " body was practically shattered twice over by the ordeal! It is a wonder " +
         HE(player)+ " survived. A wonder indeed.\n"));
         test_score -= 20;
    }
    else if(player->query_prop(DMG_TAKEN) > total_hp)
    {
        set_alarm(7.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe dark, rasping voice whispers from " +
         "the void: " +C(HE(player))+ " sustained considerable physical damage in the trials by " +
         "combat. It was a close thing whether " +HIS(player)+ " body could survive the ordeal.\n"));
         test_score -= 10;
    }
    else if(player->query_prop(DMG_TAKEN) < (total_hp / 2))
    {
        set_alarm(7.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe dark, rasping voice whispers from " +
         "the void: " +C(HE(player))+ " managed to defeat the trials by combat comfortably. " +
         "This one is a capable battlemage!\n"));
         test_score += 10;
    }
    else
    {
        set_alarm(7.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe dark, rasping voice whispers from " +
         "the void: " +C(HE(player))+ " managed to defeat the trials by combat adequately. " +
         "While sustaining some physical punishment, it ultimately wasn't life threatening.\n"));
    }

    if(player->query_prop(MEMORISED_INVIS) && player->query_prop(MEMORISED_SCRY))
    {
         set_alarm(12.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: " +
         C(player->query_real_name())+ " came woefully unprepared for the Test, without the " +
         "knowledge of invisibility nor divination spells.\n"));
         test_score -= 40;
    }
    else if(player->query_prop(MEMORISED_INVIS) || player->query_prop(MEMORISED_SCRY))
    {
         set_alarm(12.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: " +
         C(player->query_real_name())+ " came unprepared for the Test, without knowledge of all the " +
         "spells potentially needed. " +C(HE(player))+ " was favoured with an element " +
         "of luck in being able to find out the plans of the Duke.\n"));
         test_score -= 10;
    }
    else if(player->query_prop(SCRY_PROP))
    {
         set_alarm(12.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: " +
         C(player->query_real_name())+ " demonstrated " +HIM(player)+ "self an adept diviner, " +
         "successfully scrying out the plans of the Duke.\n"));
    }
    else if(player->query_prop(OBSERVE_PROP))
    {
         set_alarm(12.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: " +
         C(player->query_real_name())+ " demonstrated " +HIM(player)+ "self an adept illusionist, " +
         "successfully cloaking " +HIM(player)+ "self in shadows and observing the plans of the Duke.\n"));
    }

    if(!player->query_prop(WOHS_MIRROR_NUMBER_FAILED))
    {
         set_alarm(18.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe strong, deep masculine voice " +
         "booms through the void: "+ C(player->query_real_name())+ " demonstrated excellent " +
         "understanding of the moon phases and navigated the Maze of Mirrors flawlessly.\n"));
         test_score += 10;
    }
    else if(player->query_prop(WOHS_MIRROR_NUMBER_FAILED) > 5)
    {
         set_alarm(18.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe strong, deep masculine voice " +
         "booms through the void: "+ C(player->query_real_name())+ " seemed to rely on guesswork " +
         "to navigate the Maze of Mirrors.\n"));
         test_score -= 10;
    }
    else
    {
         set_alarm(18.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe strong, deep masculine voice " +
         "booms through the void: "+ C(player->query_real_name())+ " navigated the Maze of " +
         "Mirrors successfully, with only a handful of false steps before unravelling the " +
         "moon phase sequences.\n"));
    }

    return;
}

void
final_evaluation(object player)
{
    WOHS_TELL_ROOM(player, "\n\nThe voice of the Archmage Par-Salian sounds out from the void, " +
         "neither near nor far: So, a decision has been made.\n\n");

    if(test_score > 90)
    {
      set_alarm(7.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: Yes. " +
         C(player->query_real_name())+ " has passed with distinction the Test of High Sorcery. " +
         "Worthy of entering as a Wizard of the Ninth Circle.\n"));
    }
    else if(test_score > 70)
    {
      set_alarm(7.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: Yes. " +
         C(player->query_real_name())+ " has meritoriously passed the Test of High Sorcery.\n"));
    }
    else if(test_score > 40)
    {
      set_alarm(7.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: Yes. " +
         C(player->query_real_name())+ " has passed the Test of High Sorcery.\n"));
    }
    else
    {
      set_alarm(7.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: Yes. " +
         C(player->query_real_name())+ " has passed the Test of High Sorcery. Barely.\n"));
    }

    set_alarm(14.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe voice of the Archmage Par-Salian sounds " +
         "out from the void, neither near nor far: Very well. Which of the Orders are prepared to " +
         "sponsor " +C(player->query_real_name())+ "?\n\n"));

    if(player->query_prop(WOKE_GUARD))
    {
         set_alarm(18.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe strong, deep masculine voice " +
         "booms through the void: "+ C(player->query_real_name())+ " is welcome within the " +
         "Order of the White Robes.\n"));

         set_alarm(22.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: " +
         "The Order of the Red Robes is willing to sponsor " +C(player->query_real_name())+ ".\n"));

         set_alarm(26.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe dark, rasping voice whispers from " +
         "the void: The Order of the Black Robes declines to sponsor " +
         C(player->query_real_name())+ ".\n"));

         set_alarm(30.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe voice of the Archmage Par-Salian sounds " +
         "out from the void: Aspirant " +C(player->query_real_name())+ ", you have a choice before " +
         "you now.\n\n"));

         set_alarm(35.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe voice of the Archmage Par-Salian sounds " +
         "out: Do you choose to walk the path of the Order of the White Robes as a wizard " +
         "aligned toward good, and use your magic to further the predominance of good in the world?\n\n"));

         set_alarm(38.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe voice of the Archmage Par-Salian sounds " +
         "out: Or do you choose to walk the path of the Order of the Red Robes as a wizard aligned " +
         "to neutrality, working to balance good and evil and leaving your ultimate loyalty " +
         "to magic?\n\n"));

         set_alarm(40.0,0.0, &WOHS_TELL_ROOM(player, "\n\nA glowing white portal and a glowing " +
         "red portal appear before you.\n\n"));
         set_alarm(40.0,0.0, &add_exit("/d/Krynn/guilds/wohs/room/joinroom","white",
                   "@@white_portal"));
         set_alarm(40.0,0.0, &add_exit("/d/Krynn/guilds/wohs/room/joinroom","red",
                   "@@red_portal"));
    }
    else
    {
         set_alarm(18.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe strong, deep masculine voice " +
         "booms through the void: The Order of the White Robes declines to sponsor "+ 
         C(player->query_real_name())+ ".\n"));

         set_alarm(22.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe impassive, deadpan voice echoes: " +
         "The Order of the Red Robes is willing to sponsor " +C(player->query_real_name())+ ".\n"));

         set_alarm(26.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe dark, rasping voice whispers from " +
         "the void: The Order of the Black Robes is also willing to sponsor " +
         C(player->query_real_name())+ ".\n"));

         set_alarm(30.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe voice of the Archmage Par-Salian sounds " +
         "out from the void: Aspirant " +C(player->query_real_name())+ ", you have a choice before " +
         "you now.\n\n"));

         set_alarm(35.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe voice of the Archmage Par-Salian sounds " +
         "out: Do you choose to walk the path of the Order of the Black Robes embracing the cause of " +
         "evil, and following an ethos where magic should be pursued without ethical or moral " +
         "restraint?\n\n"));

         set_alarm(38.5,0.0, &WOHS_TELL_ROOM(player, "\n\nThe voice of the Archmage Par-Salian sounds " +
         "out: Or do you choose to walk the path of the Order of the Red Robes as a wizard aligned " +
         "to neutrality, working to balance good and evil and leaving your ultimate loyalty " +
         "to magic?\n\n"));

         set_alarm(40.0,0.0, &WOHS_TELL_ROOM(player, "\n\nA glowing white portal and a glowing " +
         "red portal appear before you.\n\n"));
         set_alarm(40.0,0.0, &add_exit("/d/Krynn/guilds/wohs/room/joinroom","black",
                   "@@black_portal"));
         set_alarm(40.0,0.0, &add_exit("/d/Krynn/guilds/wohs/room/joinroom","red",
                   "@@red_portal"));
    }

    return;
}

void
parsalian_evaluation(object player)
{
    WOHS_TELL_ROOM(player, "\n\nA voice sounds out from the void, neither near nor far, " +
         "yet clearly the familiar voice of the Archmage Par-Salian: So. " +
         C(player->query_real_name())+ " has completed the Test of High Sorcery. " +
         "How do you feel " +HE(player)+ " performed?\n\n");

    set_alarm(20.0,0.0, &align_evaluation(player));
    set_alarm(50.0,0.0, &performance_evaluation(player));
    set_alarm(80.0,0.0, &final_evaluation(player));

    return;
}

int
white_portal()
{
    return 0;
}

int
red_portal()
{
    return 0;
}

int
black_portal()
{
    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && ob->query_prop(COMPLETED_TEST))
       set_alarm(10.0,0.0, &parsalian_evaluation(ob));
}
