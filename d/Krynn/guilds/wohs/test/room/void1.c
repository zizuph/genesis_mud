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
#define WOKE_GUARD                  "_wohs_test_woke_soldier"
#define KILLED_GUARD                "_wohs_test_killed_soldier"
#define NO_INTRO                    "_wohs_test_did_not_intro_to_iriale"
#define NO_INTRO_2                  "_wohs_test_did_not_intro_to_iriale_second_time"
#define ENGAGED_ERGOTHIANS          "_wohs_test_engaged_city_siegers"
#define DMG_TAKEN                   "_wohs_test_damage_taken"
#define KILLED_DUKE                 "_wohs_test_killed_duke"
#define STEAL_BOOK                  "_wohs_test_attempted_to_steal_grimoire"
#define MEMORISED_INVIS             "_wohs_test_did_not_know_invis"
#define MEMORISED_SCRY              "_wohs_test_did_not_know_scry"
#define SCRY_PROP                   "_wohs_test_successful_scry"
#define OBSERVE_PROP                "_wohs_test_successful_observe"
#define WOHS_MIRROR_NUMBER_FAILED   "_wohs_test_mirror_number_failed_attempts"
#define HEARTROOM_ATTEMPTS          "_wohs_test_heartroom_activation_attempts"
#define WOHS_TEST_SCORE             "_wohs_test_final_score"
#define PREVIOUSLY_FAILED_TEST      "_previously_failed_wohs_test"

#define SWORE_OATH                  "_wohs_test_swore_oath"
#define DIALOG_PROP                 "_conclave_currently_dialoguing"

int test_score = 100;
int bonus_guild_xp = 0;
int total_hp;

public void        init();

static int dialog_alarm;
public object dialog_target;
static mapping speak;
string portal_desc = "";
int white_portal = 0;
int red_portal = 0;
int black_portal = 0;

public varargs int
handle_timed_messages(object player, mapping messages, int cycle)
{
    if (objectp(dialog_target))
    {
        if (!present(dialog_target, this_object()))
        {
           WOHS_TELL_ROOM(player, "The void falls silent. Empty.\n");
            // Rude to leave like that while someone is lecturing.
            remove_alarm(dialog_alarm);
            dialog_target = 0;
        }
        
        if (objectp(dialog_target) && !cycle)
        {
            // Conversation can't be interrupted
            return 0;
        }
        
        if (!objectp(dialog_target))
            return 1;
    }
        
    if (!mappingp(messages) || !m_sizeof(messages))
    {
        DEBUG("Void room no messages check called.");
        return 1;
    }
    
    // Deliver the message
    if (cycle)
        WOHS_TELL_ROOM(player, messages[cycle][1]);
    
    dialog_target = player;
    cycle++;
    
    if (member_array(cycle, m_indexes(messages)) < 0)
    {
        remove_alarm(dialog_alarm);
        dialog_target = 0;
        return 1;
    }
    
    dialog_alarm = set_alarm(messages[cycle][0], 0.0,
                     &handle_timed_messages(player, messages, cycle));
}


void
reset_tower_room()
{
    return;
}

void
set_white_portal(int on)
{
    white_portal = on;
}

void
set_red_portal(int on)
{
    red_portal = on;
}

void
set_black_portal(int on)
{
    black_portal = on;
}

int
query_white_portal()
{
    return white_portal;
}

int
query_red_portal()
{
    return red_portal;
}

int
query_black_portal()
{
    return black_portal;
}

string
portal_desc()
{
    if(query_white_portal() && query_red_portal())
       portal_desc = "\n\nBefore you has appeared an ivory portal " +
           "glowing a brilliant white, as well as a bloodstone portal " +
           "radiating a red light.";
    else if(query_black_portal() && query_red_portal())
       portal_desc = "\n\nBefore you has appeared an ebony portal that " +
           "is cloaked in dark shadows, as well as a bloodstone portal " +
           "radiating a red light.";
    else if(query_white_portal())
       portal_desc = "\n\nBefore you has appeared an ivory portal " +
           "glowing a brilliant white.";
    else if(query_black_portal())
       portal_desc = "\n\nBefore you has appeared an ebony portal that " +
           "is cloaked in dark shadows.";
    else if(query_red_portal())
       portal_desc = "\n\nBefore you has appeared a bloodstone portal " +
           "radiating a red light.";

    return portal_desc;
}

void
create_tower_room()
{
   set_short("a void of emptiness");
   set_long("You find yourself in a black void of emptiness. Are you " +
       "standing? Or floating? You don't know... you can see nothing, " +
       "feel nothing, sense nothing. You realise you are not even sure " +
       "how long you have been within this void, as even your " +
       "perception of time has gone! @@portal_desc@@\n");

   add_item(({"portals","portal"}), "@@exa_portals");
   add_item(({"ivory portal","white","brilliant white","glowing portal",
       "white portal"}), "@@exa_white_portal");
   add_item(({"red portal","bloodstone portal","red light","red",
       "radiating portal"}), "@@exa_red_portal");
   add_item(({"black portal","ebony portal","cloaked portal",
       "dark shadows","shadows"}), "@@exa_black_portal");

   reset_tower_room();
}

string
exa_portals()
{
    if(query_white_portal() && query_red_portal())
       return "Before you has appeared an ivory portal glowing a " +
           "brilliant white, as well as a bloodstone portal radiating " +
           "a red light.\n";
    else if(query_black_portal() && query_red_portal())
       return "Before you has appeared an ebony portal that is cloaked " +
           "in dark shadows, as well as a bloodstone portal radiating " +
           "a red light.\n";
    else if(query_white_portal())
       return "Before you has appeared an ivory portal glowing a " +
           "brilliant white.\n";
    else if(query_black_portal())
       return "Before you has appeared an ebony portal that is cloaked " +
           "in dark shadows.\n";
    else if(query_red_portal())
       return "Before you has appeared a bloodstone portal radiating " +
           "a red light.\n";

    return "The void is completely empty. You find nothing here to " +
        "examine!\n";    
}

string
exa_white_portal()
{
    if(query_white_portal())
       return "Before you has appeared an ivory portal glowing a " +
           "brilliant white. By entering this portal you accept the " +
           "sponsorship of the Order of the White Robes and become " +
           "a Wizard of High Sorcery.\n\nThe Order of the White Robes " +
           "draws its power from the white moon Solinari. Members of " +
           "this order follow the paths of knowledge and wisdom, and " +
           "are focused on the cause of Good. Often they will assist " +
           "the forces of Good to defend against the darkness.\n";

    return "You find nothing of such type to examine!\n";    
}

string
exa_red_portal()
{
    if(query_red_portal())
       return "Before you has appeared a bloodstone portal radiating a " +
           "red light. By entering this portal you accept the " +
           "sponsorship of the Order of the Red Robes and become " +
           "a Wizard of High Sorcery.\n\nThe Order of the Red Robes " +
           "draws its power from the moon Lunitari. The members of " +
           "this order follow the paths of knowledge, and are " +
           "said to have the ultimate loyalty to magic, with no " +
           "tendencies to lean either towards good or towards evil. " +
           "Red Robes seek to maintain the Balance.\n";

    return "You find nothing of such type to examine!\n";    
}

string
exa_black_portal()
{
    if(query_black_portal())
       return "Before you has appeared an ebony portal that is cloaked " +
           "in dark shadows. By entering this portal you accept the " +
           "sponsorship of the Order of the Black Robes and become " +
           "a Wizard of High Sorcery.\n\nThe Order of the Black Robes " +
           "draws its power from the moon Nuitari. While members of " +
           "this order are evil-aligned, they do not cause random " +
           "destruction for destruction's sake. To do so would raise " +
           "the ire of the masses and jeopardize the place of magic in " +
           "the realms. Black Robe wizards may be cruel, but they are " +
           "also cunning. They tend to avoid open acts of violence " +
           "if more subtle ways can be found. Black Robe wizards seek " +
           "the quickest route to power possible to satisfy their " +
           "hunger for magic.\n";

    return "You find nothing of such type to examine!\n";    
}

void
parsalian_evaluation(object player)
{
   // DEBUG("Parsalian eval function called");

    string align_str1, align_str2, align_str3, engaged_ergothians, 
        killed_duke, damage_taken, spy_message, maze_message, test_text, 
        sponsor1, sponsor2, sponsor3, sponsor4, sponsor5, sponsor6;
    total_hp = player->query_max_hp();

    if(!player->query_wiz_level())
         WOHS_MANAGER->set_passed_wohs_test(player);

    // Test score influencers not mentioned by Conclave
    if(player->query_prop(NO_INTRO))
         test_score -= 5;
    if(player->query_prop(NO_INTRO_2))
         test_score -= 10;
    if(player->query_prop(HEARTROOM_ATTEMPTS) > 3)
         test_score -= 30;
    if(player->query_prop(HEARTROOM_ATTEMPTS) > 1)
         test_score -= 10;

    // If previously failed Test you get penalised
    if(WOHS_MANAGER->query_wohs_test_prop(player, PREVIOUSLY_FAILED_TEST)) 
         test_score -= 20;

    WOHS_TELL_ROOM(player, "\n\nA voice sounds out from the void, " +
        "neither near nor far, yet clearly the familiar voice of the " +
        "Archmage Par-Salian.\n\n\n Par-Salian says to you: What you " +
         "have participated in Aspirant is an event from before the " +
         "Cataclysm, where the great powers that existed in the realm " +
         "rose up against magic. All magic. It was a dark time for " +
         "practitioners of the arcane, with many lessons learnt " +
         "that came at great cost and should not be forgotten.\n\n");

    if(player->query_prop(WOKE_GUARD))
    {
        align_str1 = "\n\nA strong, deep masculine voice booms through " +
            "the void: " +C(player->query_real_name())+ " showed " +
            "admirable traits in waking the ensorcelled guard rather " +
            "than slaying him in his sleep. It demonstrates a " +
            "principled, even noble, strength of character.\n\n";
        align_str2 = "\n\nA dark, rasping voice whispers from " +
            "the void behind you: Noble strength of character? I would " +
            "say foolish. " +C(HE(player))+ " potentially compromised " +
            "the task given to " +HIM(player)+ " with his soft " +
            "principles.\n\n";
        align_str3 = "\n\nAn impassive, deadpan voice echoes " +
            "from the void around you: I would tend to agree. While " +
            "idealistic and not the most appropriate action, " +
            HE(player)+ " did ultimately retrieve the orders.\n\n";
    }
    else if(player->query_prop(KILLED_GUARD))
    {
        align_str1 = "\n\nA strong, deep masculine voice booms through " +
            "the void: " +C(player->query_real_name())+ " showed " +
            "ignoble and opportunistic traits in slaying the " +
            "ensorcelled guard in his sleep which I found, quite " +
            "frankly, disgusting. It demonstrated a lack of " +
            "principles, an inability to problem solve any better than " + 
            "your average goblin, and a weakness of character.\n\n";
        align_str2 = "\n\nA dark, rasping voice whispers from " +
            "the void behind you: Hah! I would say any other action " +
            "but the most efficient and effective to be anything but " +
            "foolish. " +C(HE(player))+ " deserves credit for not " +
            "compromising the task given to " +HIM(player)+ " through " +
            "soft-hearted principles.\n\n";
        align_str3 = "\n\nAn impassive, deadpan voice echoes " +
            "from the void around you: I would tend to agree. In this " +
            "case any other action would be indulgent. Retrieving the " +
            "orders was " +HIS(player)+ " primary objective, " +
            "which " +HE(player)+ " ultimately did achieve.\n\n";
    }

    if(player->query_prop(ENGAGED_ERGOTHIANS))
    {
        engaged_ergothians = "\n\nThe strong, deep masculine voice " +
            "booms through the void: Yet "+ C(player->query_real_name())+ 
            " was incautious at best, leaving the Kadothan Grove " +
            "without suitable enchantments to avoid being attacked " +
            "by the besieging armies.\n\n";
        test_score -= 10;
    }
    else
        engaged_ergothians = "";

    if(player->query_prop(KILLED_DUKE))
    {
        killed_duke = "\n\nThe impassive, deadpan voice echoes: " +
            C(player->query_real_name())+ " also managed to slay the " +
            "Duke, which I thought wasn't possible in the scenarios " +
            "we set. Very impressive.\n\n";

        if(!WOHS_MANAGER->query_wohs_test_marking(player))
        {
            killed_duke += "The dark, rasping voice hisses from the " +
                "void: Impressive, but indicates an obsessive mind. " +
                "The Test has marked " +HIM(player)+ " as such, as a " +
                "warning to be mindful of the destructive nature of " +
                "fixations and obsessions.\n\n";
            WOHS_MANAGER->set_wohs_test_marking(player, "mark_of_andras");
            WOHS_MANAGER->set_wohs_test_marking_status(player, 1);
        }

        test_score += 20;
         
    }
    else
        killed_duke = "";

    if(player->query_prop(DMG_TAKEN) > (2 * total_hp))
    {
        damage_taken = "\n\nThe dark, rasping voice sneers from " +
             "the void: " +C(HE(player))+ " was physically broken by " +
             "the trials by combat. " +C(HIS(player))+ " body was " +
             "practically shattered twice over by the ordeal! It is a " +
             "wonder " +HE(player)+ " survived. A wonder indeed.\n\n";

        if(!WOHS_MANAGER->query_wohs_test_marking(player))
        {
            damage_taken += "The strong, deep masculine voice booms " +
                "through the void: Aye. The Test has marked " +
                HIM(player)+ " with the scars of " +HIS(player)+ 
                " ordeal as a permanent reminder that as a mage " +
                HE(player)+ " must always be prepared to defend " +
                HIM(player)+ "self.\n\n";
            WOHS_MANAGER->set_wohs_test_marking(player, "mark_of_scarring");
            WOHS_MANAGER->set_wohs_test_marking_status(player, 1);
        }

        test_score -= 20;
    }
    else if(player->query_prop(DMG_TAKEN) > total_hp)
    {
        damage_taken = "\n\nThe dark, rasping voice whispers from " +
            "the void: " +C(HE(player))+ " sustained considerable " +
            "physical damage in the trials by combat. It was a close " +
            "thing whether " +HIS(player)+ " body could survive the " +
            "ordeal.\n\n";
         test_score -= 10;

        if(!WOHS_MANAGER->query_wohs_test_marking(player))
        {
            damage_taken += "The strong, deep masculine voice booms " +
                "through the void: Aye. The Test has marked " +
                HIM(player)+ ". " +C(HIS(player))+ " skin has been " +
                "bronzed by the holy flames of the presbyter. A " +
                "permanent reminder that as a mage " +HE(player)+ 
                " must always be prepared for battle against all types " +
                "of enemies.\n\n";
            WOHS_MANAGER->set_wohs_test_marking(player, "mark_of_bronzing");
            WOHS_MANAGER->set_wohs_test_marking_status(player, 1);
        }
    }
    else if(player->query_prop(DMG_TAKEN) < (total_hp / 2))
    {
        damage_taken = "\n\nThe dark, rasping voice whispers from " +
            "the void: " +C(HE(player))+ " managed to defeat the trials " +
            "by combat comfortably. This one is a capable battlemage!\n\n";
         test_score += 10;
    }
    else
    {
        damage_taken = "\n\nThe dark, rasping voice whispers from " +
            "the void: " +C(HE(player))+ " managed to defeat the trials " +
            "by combat adequately. While sustaining some physical " +
            "punishment, it ultimately wasn't life threatening.\n\n";
    }

    if(player->query_prop(MEMORISED_INVIS) && 
       player->query_prop(MEMORISED_SCRY))
    {
        spy_message = "\n\nThe impassive, deadpan voice echoes: " +
            C(player->query_real_name())+ " came woefully unprepared " +
            "for the Test, without the knowledge of invisibility nor " +
            "divination spells.\n\n";
         test_score -= 40;
    }
    else if(player->query_prop(MEMORISED_INVIS) || 
            player->query_prop(MEMORISED_SCRY))
    {
        spy_message = "\n\nThe impassive, deadpan voice echoes: " +
            C(player->query_real_name())+ " came unprepared for the " +
            "Test, without knowledge of all the spells potentially " +
            "needed. " +C(HE(player))+ " was favoured with an element " +
            "of luck in being able to find out the plans of the " +
            "Duke.\n\n";
        test_score -= 10;
    }
    else if(player->query_prop(SCRY_PROP))
    {
        spy_message = "\n\nThe impassive, deadpan voice echoes: " +
            C(player->query_real_name())+ " demonstrated " +HIM(player)+ 
            "self an adept diviner, successfully scrying out the plans " +
            "of the Duke.\n\n";
    }
    else if(player->query_prop(OBSERVE_PROP))
    {
        spy_message = "\n\nThe impassive, deadpan voice echoes: " +
            C(player->query_real_name())+ " demonstrated " +HIM(player)+ 
            "self an adept illusionist, successfully cloaking " +
            HIM(player)+ "self in shadows and observing the plans of " +
            "the Duke.\n\n";
    }
    else
        spy_message = "";

    if(!player->query_prop(WOHS_MIRROR_NUMBER_FAILED))
    {
        maze_message = "\n\nThe strong, deep masculine voice " +
            "booms through the void: "+ C(player->query_real_name())+ 
            " demonstrated excellent understanding of the moon phases " +
            "and navigated the Maze of Mirrors flawlessly.\n\n";
        test_score += 10;
    }
    else if(player->query_prop(WOHS_MIRROR_NUMBER_FAILED) > 5)
    {
        maze_message = "\n\nThe strong, deep masculine voice " +
            "booms through the void: "+ C(player->query_real_name())+ 
            " seemed to rely on guesswork to navigate the Maze of " +
            "Mirrors.\n\n";
        test_score -= 10;
    }
    else
    {
        maze_message = "\n\nThe strong, deep masculine voice " +
            "booms through the void: "+ C(player->query_real_name())+ 
            " navigated the Maze of Mirrors successfully, with only " +
            "a handful of false steps before unravelling the " +
            "moon phase sequences.\n\n";
    }

    WOHS_MANAGER->add_wohs_test_props(player, WOHS_MIRROR_NUMBER_FAILED, 
        player->query_prop(WOHS_MIRROR_NUMBER_FAILED));
    WOHS_MANAGER->add_wohs_test_props(player, WOHS_TEST_SCORE, test_score);

    if(test_score > 90)
    {
       test_text = "\n\nThe impassive, deadpan voice echoes: Yes. " +
           C(player->query_real_name())+ " has passed with distinction " +
           "the Test of High Sorcery. Worthy of entering as a Wizard " +
           "of the Ninth Circle.\n\n";
       bonus_guild_xp = 5000;

    }
    else if(test_score > 70)
    {
       test_text = "\n\nThe impassive, deadpan voice echoes: Yes. " +
           C(player->query_real_name())+ " has meritoriously passed the " +
           "Test of High Sorcery.\n\n";
       bonus_guild_xp = 2500;
    }
    else if(test_score > 40)
    {
       test_text = "\n\nThe impassive, deadpan voice echoes: Yes. " +
           C(player->query_real_name())+ " has passed the Test of High " +
           "Sorcery.\n\n";
    }
    else
    {
       test_text = "\n\nThe impassive, deadpan voice echoes: Yes. " +
           C(player->query_real_name())+ " has passed the Test of High " +
           "Sorcery. Barely.\n\n";
    }

    // Those that do well get some bonus guild xp.
    player->set_skill(WOHS_GUILD_STAT, bonus_guild_xp);

    if(player->query_prop(WOKE_GUARD))
    {
         sponsor1 = "\n\nThe strong, deep masculine voice " +
             "booms through the void: "+ C(player->query_real_name())+ 
             " is welcome within the Order of the White Robes.\n\n";

         sponsor2 = "\n\nThe impassive, deadpan voice echoes: " +
             "The Order of the Red Robes is willing to sponsor " +
             C(player->query_real_name())+ ".\n\n";

         sponsor3 = "\n\nThe dark, rasping voice whispers from the " +
             "void: The Order of the Black Robes declines to sponsor " +
             C(player->query_real_name())+ ".\n\n";

         sponsor4 = "\n\nThe voice of the Archmage Par-Salian sounds " +
             "out from the void: Aspirant " +C(player->query_real_name())+ 
             ", you have a choice before you now.\n\n";

         sponsor5 = "\n\nThe voice of the Archmage Par-Salian sounds " +
             "out: Do you choose to walk the path of the Order of the " +
             "White Robes as a wizard aligned toward good, and use " +
             "your magic to further the predominance of good in the " +
             "world?\n\n";

         sponsor6 = "\n\nThe voice of the Archmage Par-Salian sounds " +
             "out: Or do you choose to walk the path of the Order of " +
             "the Red Robes as a wizard aligned to neutrality, working " +
             "to balance good and evil and leaving your ultimate " +
             "loyalty to magic?\n\n";

         set_alarm(188.0,0.0, &WOHS_TELL_ROOM(player, "\n\nAn ivory " +
             "portal glowing a brilliant white and a bloodstone portal " +
             "radiating with a red light appear before you.\n\n"));
         set_alarm(188.0,0.0, &set_white_portal(1));
         set_alarm(188.0,0.0, &set_red_portal(1));
    }
    else
    {
         sponsor1 = "\n\nThe strong, deep masculine voice " +
             "booms through the void: The Order of the White Robes " +
             "declines to sponsor " +C(player->query_real_name())+ ".\n\n";

         sponsor2 = "\n\nThe impassive, deadpan voice echoes: " +
             "The Order of the Red Robes is willing to sponsor " +
             C(player->query_real_name())+ ".\n\n";

         sponsor3 = "\n\nThe dark, rasping voice whispers from the " +
             "void: The Order of the Black Robes is also willing to " +
             "sponsor " +C(player->query_real_name())+ ".\n\n";

         sponsor4 = "\n\nThe voice of the Archmage Par-Salian sounds " +
             "out from the void: Aspirant " +C(player->query_real_name())+
             ", you have a choice before you now.\n\n";

         sponsor5 = "\n\nThe voice of the Archmage Par-Salian sounds " +
             "out: Do you choose to walk the path of the Order of the " +
             "Black Robes embracing the cause of evil, and following " +
             "an ethos where magic should be pursued without ethical " +
             "or moral restraint?\n\n";

         sponsor6 = "\n\nThe voice of the Archmage Par-Salian sounds " +
             "out: Or do you choose to walk the path of the Order of " +
             "the Red Robes as a wizard aligned to neutrality, working " +
             "to balance good and evil and leaving your ultimate " +
             "loyalty to magic?\n\n";

         set_alarm(188.0,0.0, &WOHS_TELL_ROOM(player, "\n\nAn ebony " +
             "portal cloaked in shadows and a bloodstone portal " +
             "radiating with a red light appear before you.\n\n"));
         set_alarm(188.0,0.0, &set_black_portal(1));
         set_alarm(188.0,0.0, &set_red_portal(1));
    }

    speak = ([
        1 : ({ 22.0, "\n\nThe voice of the Archmage Par-Salian sounds " +
                     "out from the void again, " +
                     "however you feel it not directed at you: So. " +
                     C(player->query_real_name())+ " has completed " +
                     "the Test of High Sorcery. " +
                     "How do you feel " +HE(player)+ " performed?\n\n" }),
        2 : ({ 12.0, align_str1 }),
        3 : ({ 12.0, align_str2 }),
        4 : ({ 12.0, align_str3 }),
        5 : ({ 10.0, "\n\nThe impassive, deadpan voice echoes: " +
                    C(player->query_real_name())+ " defeated a " +
                    "comprehensive range of foes we sent against " +
                    HIM(player)+ "... both magical and mundane.\n" }),
        6 : ({ 4.0, engaged_ergothians }),
        7 : ({ 4.0, killed_duke }),
        8 : ({ 7.0, damage_taken }),
        9 : ({ 7.0, spy_message }),
       10 : ({ 7.0, maze_message }),
       11 : ({ 12.0, "\n\nThe voice of the Archmage Par-Salian sounds " +
                    "out from the void: So, a decision has been made.\n\n" }),
       12 : ({ 9.0, test_text }),
       13 : ({ 10.0, "\n\nThe voice of the Archmage Par-Salian sounds " +
                    "out from the void: Very well. Which of the Orders " +
                    "are prepared to sponsor " +
                    C(player->query_real_name())+ "?\n\n" }),
       14 : ({ 7.0, sponsor1 }),
       15 : ({ 7.0, sponsor2 }),
       16 : ({ 7.0, sponsor3 }),
       17 : ({ 10.0, sponsor4 }),
       18 : ({ 6.0, sponsor5 }),
       19 : ({ 6.0, sponsor6 }),
       20 : ({ 10.0, "\n\nThe voice of the Archmage Par-Salian sounds " +
                    "out from the void: It is your choice to make. " +
                    "Swear an oath to magic, and then enter the portal " +
                    "that aligns with your Order of choice, " +
                    C(player->query_real_name())+ ".\n\n" }),
    ]);
    
    handle_timed_messages(player, speak);

    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (ob->query_prop(COMPLETED_TEST))
    {
       set_alarm(5.0,0.0, &parsalian_evaluation(ob));
    }
}

string
enter_portal(string str)
{
    if(!str)
    {
        write("Enter what?\n");
        return ""; 
    }

    if(!query_white_portal() && !query_red_portal() && 
       !query_black_portal())
    {
        write("What?\n");
        return "";
    } 

    if((str == "portal") || (str == "portals")) 
    {
        write("Which portal do you wish to enter?\n");
        return "";
    }

    string name = TP->query_real_name();

    if((str == "ivory portal") || (str == "white portal") || 
       (str == "glowing portal")) 
    {
        if(!query_white_portal())
        {
            write("There is no " +str+ " to enter.\n");
            return "";
        }

        if(!TP->query_prop(SWORE_OATH))  
        {
            WOHS_TELL_ROOM(TP, "\nThe voice of the Archmage Par-Salian " +
               "sounds out from the void: Before you can become a " +
               "Wizard of High Sorcery you must swear on oath to " +
               "magic. Loyalty to the Art must take precedent to " +
               "your allegiance to your Order.\n\n");        
            return "";
        }      

        write("You step through the ivory portal, and find yourself " +
            "back in the Tower of High Sorcery in Wayreth...\n\n\n");
        say(QCTNAME(TP)+ " steps through the ivory portal and " +
            "disappears.\n");

        if(TP->query_alignment() < 900)   
          TP->set_alignment(900); 
	WOHS_MANAGER->set_wohs_order_colour(TP, "white");
        WOHS_MANAGER->add_wohs_members_list(name, "white");

        TP->move_living("M", "/d/Krynn/guilds/wohs/room/joinroom", 1, 0);
        return "";
   }

   if((str == "bloodstone portal") || (str == "red portal") || 
      (str == "radiating portal")) 
   {
        if(!query_red_portal())
        {
            write("There is no " +str+ " to enter.\n");
            return "";
        }

        if(!TP->query_prop(SWORE_OATH))  
        {
            WOHS_TELL_ROOM(TP, "\nThe voice of the Archmage Par-Salian " +
                "sounds out from the void: Before you can become a " +
                "Wizard of High Sorcery you must swear on oath to " +
                "magic. Loyalty to the Art must take precedent to " +
                "your allegiance to your Order.\n\n");        
            return "";
        }      

        write("You step through the bloodstone portal, and find " +
            "yourself back in the Tower of High Sorcery in " +
            "Wayreth...\n\n\n");
        say(QCTNAME(TP)+ " steps through the bloodstone portal and " +
            "disappears.\n");

        TP->set_alignment(0);
	WOHS_MANAGER->set_wohs_order_colour(TP, "red");
        WOHS_MANAGER->add_wohs_members_list(name, "red");

        TP->move_living("M", "/d/Krynn/guilds/wohs/room/joinroom", 1, 0);
        return "";
   }

   if((str == "ebony portal") || (str == "black portal") || 
      (str == "cloaked portal")) 
   {
        if(!query_black_portal())
        {
            write("There is no " +str+ " to enter.\n");
            return "";
        }

        if(!TP->query_prop(SWORE_OATH))  
        {
            WOHS_TELL_ROOM(TP, "\nThe voice of the Archmage Par-Salian " +
                "sounds out from the void: Before you can become a " +
                "Wizard of High Sorcery you must swear on oath to " +
                "magic. Loyalty to the Art must take precedent to " +
                "your allegiance to your Order.\n\n");        
            return "";
        }      

        write("You step through the ebony portal, and find yourself " +
            "back in the Tower of High Sorcery in Wayreth...\n\n\n");
        say(QCTNAME(TP)+ " steps through the ebony portal and " +
            "disappears.\n");

        if(TP->query_alignment() > -900)   
          TP->set_alignment(-900);     
	WOHS_MANAGER->set_wohs_order_colour(TP, "black");
        WOHS_MANAGER->add_wohs_members_list(name, "black");

        TP->move_living("M", "/d/Krynn/guilds/wohs/room/joinroom", 1, 0);
        return "";
   }

   write("Enter what?\n");
   return "";
}

string
swear_oath(string str)
{
    if(!str)
    {
      write("Swear what?\n");
      return "";
    }

    if((str != "an oath of loyalty to magic")) 
    {
      write("Swear what? An oath of loyalty to magic?\n");
      return "";
    }

    if(TP->query_prop(SWORE_OATH))
    {
      write("You have already sworn an oath of loyalty to magic.\n");
      return "";
    }

   write("You swear an oath of commitment and loyalty to magic, and " +
       "to follow the Laws of the Order and the principle of " +
       "brotherhood between all wizards.\n");
   say(QCTNAME(TP)+ " swears an oath of commitment and loyalty to " +
       "magic, and to follow the Laws of the Order and the principle " +
       "of brotherhood between all wizards.\n");
   TP->add_prop(SWORE_OATH, 1);
   return "";
}

/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(enter_portal, "enter");
    add_action(swear_oath, "swear");

} /* init */
