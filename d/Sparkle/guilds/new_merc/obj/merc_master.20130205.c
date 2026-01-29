/*
 *  /d/Sparkle/guild/new_merc/obj/merc_master.c
 *
 *  Data controller object for the Free Mercenary Guild of Sparkle.
 *
 *  Created January 2009, by Cooper Sherry (Gorboth)
 */
#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

inherit "/d/Emerald/lib/data_manager";
inherit "/lib/skill_raise";

#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <time.h>
#include "../merc_defs.h"

/* Definitions */
#define    SKILL_NAME(x)   (SS_SKILL_DESC[x][0])
#define    ADAPTING_PROP   ("_merc_guild_adapting_prop")
#define    ATTITUDE_KIND    1
#define    ATTITUDE_NORMAL  2
#define    ATTITUDE_CRUEL   3

#ifndef SS_BLOCK
#define SS_BLOCK 26 
#endif

/* Global Variables */
public mapping Adapt_Log = ([]);
public mapping SkMap = SS_SKILL_DESC;
public mapping Adapt_Map = ([
    "sword" :
      ({ SS_WEP_SWORD,
         "viridian",
         "on the path from Flotsam to Balifor in the lands of Krynn",
         "handle a sword",
         ATTITUDE_KIND,
       }),
    "axe" : 
      ({ SS_WEP_AXE,
         "brutus",
         "at the entrance to the Gladiator Guild in the lands of Tyr",
         "handle an axe",
          ATTITUDE_NORMAL, }),
    "polearm" : 
      ({ SS_WEP_POLEARM,
         "atlas",
         "within the Royal Palace in the Underwater City of Thalassia"
       + " in the lands of Calia",
         "handle a polearm",
          ATTITUDE_NORMAL, }),
    "knife" : 
      ({ SS_WEP_KNIFE,
         "gakhan",
         "somewhere within Flotsam in the lands of Krynn",
         "handle a knife",
          ATTITUDE_CRUEL, }),
    "club" : 
      ({ SS_WEP_CLUB,
         "dougan",
         "in Flotsam (probably in one of the pubs) in the lands of"
       + " Krynn",
         "handle a club",
          ATTITUDE_NORMAL, }),
    "missiles" : 
      ({ SS_WEP_MISSILE,
         "qualthas",
         "in the Qualinost Archer's Camp in the lands of Krynn",
         "use missile weapons",
          ATTITUDE_NORMAL, }),
    "javelin" : 
      ({ SS_WEP_JAVELIN,
         "elfhelm",
         "in the city of Edoras in Rohan in the lands of Middle Earth",
         "handle a javelin",
          ATTITUDE_NORMAL, }),
    "two handed combat" : 
      ({ SS_2H_COMBAT,
         "arlenn",
         "in the city of Calathin in the lands of Terel",
         "handle two weapons in combat",
          ATTITUDE_NORMAL, }),
    "unarmed combat" : 
      ({ SS_UNARM_COMBAT,
         "drelkhorn",
         "within the ancient Kahedan monastery in the lands of Cadu",
         "fight without weapons",
          ATTITUDE_KIND, }),
    "blindfighting" : 
      ({ SS_BLIND_COMBAT,
         "regliak",
         "outside the Dragon Order Monastery west of Sparkle",
         "fight without seeing",
          ATTITUDE_NORMAL, }),
    "parry" : 
      ({ SS_PARRY,
         "verminaard",
         "in the stronghold of Pax Tharkas in the lands of Krynn",
         "parry incoming hits in combat",
          ATTITUDE_CRUEL, }),
    "defence" : 
      ({ SS_DEFENCE,
         "jaine",
         "somewhere in Kendermore in the lands of Krynn",
         "defend yourself in combat",
          ATTITUDE_NORMAL, }),
    "mounted combat" : 
      ({ SS_MOUNTED_COMBAT,
         "brutakis",
         "in the Red Fang guild northeast of Kabal in the lands of"
       + " Kalad",
         "fight effectively while mounted",
          ATTITUDE_CRUEL, }),
    "block" : 
      ({ SS_BLOCK,
         "darryn",
         "in the lands of Krynn, hiding out somewhere near Flotsam",
         "prevent enemies from escaping",
          ATTITUDE_NORMAL, }),
    "spellcraft" : 
      ({ SS_SPELLCRAFT,
         "gamalus",
         "near the southern entrance to Gelan in the lands of Calia",
         "cast spells",
          ATTITUDE_KIND, }),
    "herbalism" : 
      ({ SS_HERBALISM,
         "johanna",
         "in a park in the southwest region of Gont Port in the lands"
       + " of Earthsea",
         "find and identify herbs",
          ATTITUDE_KIND, }),
    "alchemy" : 
      ({ SS_ALCHEMY,
         "raspatoon",
         "in the city of Gelan in the lands of Calia",
         "mix and use potions",
          ATTITUDE_NORMAL, }),
    "transmutation spells" : 
      ({ SS_FORM_TRANSMUTATION,
         "sharaburz",
         "within the Orc racial guild near the Shire in the lands of"
       + " Middle Earth",
         "use transmutation spells",
          ATTITUDE_CRUEL, }),
    "illusion spells" : 
      ({ SS_FORM_ILLUSION,
         "ry'nal",
         "within the Ziggurat Pleasure Palace in the Forbidden City"
       + " in the lands of Avenir",
         "use illusion spells",
          ATTITUDE_NORMAL, }),
    "divination spells" : 
      ({ SS_FORM_DIVINATION,
         "hylar",
         "somewhere in the Moorlands of Calia",
         "use divination spells",
          ATTITUDE_NORMAL, }),
    "enchantment spells" : 
      ({ SS_FORM_ENCHANTMENT,
         "aunty",
         "in the Adventurer's Guild of Ten Alders in Gont in the"
       + " lands of Earthsea",
         "use enchantment spells",
          ATTITUDE_KIND, }),
    "conjuration spells" : 
      ({ SS_FORM_CONJURATION,
         "erinys",
         "in the southern sections of the Holm in the lands of Avenir",
         "use conjuration spells",
          ATTITUDE_NORMAL, }),
    "abjuration spells" : 
      ({ SS_FORM_ABJURATION,
         "nemur",
         "somewhere on the Holm in the lands of Avenir",
         "use abjuration spells",
          ATTITUDE_NORMAL, }),
    "fire spells" : 
      ({ SS_ELEMENT_FIRE,
         "thorr-kan",
         "within the troll camp in Mithas in the lands of Krynn",
         "use fire-based magic",
          ATTITUDE_CRUEL, }),
    "air spells" : 
      ({ SS_ELEMENT_AIR,
         "laran",
         "somewhere in the forests around Mithas in the lands of"
       + " Krynn",
         "use air-based magic",
          ATTITUDE_KIND, }),
    "earth spells" : 
      ({ SS_ELEMENT_EARTH,
         "thimah",
         "in Solace in the lands of Krynn",
         "use earth-based magic",
          ATTITUDE_KIND, }),
    "water spells" : 
      ({ SS_ELEMENT_WATER,
         "maiden",
         "at the entrance to the Ziggurat beyond the First Gate of"
       + " Sybarus in the lands of Avenir",
         "use water-based magic",
          ATTITUDE_NORMAL, }),
    "life spells" : 
      ({ SS_ELEMENT_LIFE,
         "xania",
         "within the Academy of Elemental Arts in Gelan in the lands of"
       + " Calia",
         "use life-based magic",
          ATTITUDE_KIND, }),
    "death spells" : 
      ({ SS_ELEMENT_DEATH,
         "athir",
         "somewhere around the township of Thornlin in Gondor",
         "use death-based magic",
          ATTITUDE_CRUEL, }),
    "open lock" : 
      ({ SS_OPEN_LOCK,
         "jasmine",
         "somewhere in Kendermore in the lands of Krynn",
         "pick locks effectively",
          ATTITUDE_KIND, }),
    "pick pocket" : 
      ({ SS_PICK_POCKET,
         "merldon",
         "at the Secret Society guild in Kendermore in the lands of"
       + " Krynn",
         "steal things from people",
          ATTITUDE_KIND, }),
    "acrobat" : 
      ({ SS_ACROBAT,
         "ashel",
         "in a cottage located somewhere between Gont Port and Ten"
       + " Alders in the lands of Earthsea",
         "use your body in motion",
          ATTITUDE_KIND, }),
    "find and remove traps" : 
      ({ SS_FR_TRAP,
         "fredor",
         "south of Minas Tirith in the lands of Gondor in Middle Earth",
         "find and remove traps",
          ATTITUDE_NORMAL, }),
    "sneak" : 
      ({ SS_SNEAK,
         "aradan",
         "in the Prancing Pony inn in Bree near the Shire in the"
       + " lands of Middle Earth",
         "move around unnoticed",
          ATTITUDE_NORMAL, }),
    "hide" : 
      ({ SS_HIDE,
         "quillean",
         "in the Qualinost Elf Camp in the lands of Krynn",
         "conceal yourself from view",
          ATTITUDE_NORMAL, }),
    "backstab" : 
      ({ SS_BACKSTAB,
         "penance",
         "somewhere near the basket-lift in Kabal in the lands of"
       + " Kalad",
         "backstab effectively",
          ATTITUDE_NORMAL, }),
    "language" : 
      ({ SS_LANGUAGE,
         "deggart",
         "within the Great Library of Palanthas in the lands of Krynn",
         "speak and understand other languages",
          ATTITUDE_NORMAL, }),
    "appraise enemy" : 
      ({ SS_APPR_MON,
         "mergula",
         "in the Legion of Darkness headquarters somewhere in the"
       + " lands of Terel",
         "evaluate the attributes of others",
          ATTITUDE_NORMAL, }),
    "appraise object" : 
      ({ SS_APPR_OBJ,
         "pelle",
         "in the Blacksmith's Shop in Ten Alders in the lands of"
       + " Earthsea",
         "evaluate the attributes of objects",
          ATTITUDE_KIND, }),
    "appraise value" : 
      ({ SS_APPR_VAL,
         "rommik",
         "in the Auction Tent in Sparkle",
         "estimate the value of things",
          ATTITUDE_NORMAL, }),
    "swim" : 
      ({ SS_SWIM,
         "george",
         "somewhere in Cadu where he works as a lifeguard",
         "handle yourself in the water",
          ATTITUDE_KIND, }),
    "climb" : 
      ({ SS_CLIMB,
         "mimo",
         "beneath a huge rock in the foothills of the Misty Mountains"
       + " in the lands of Middle Earth",
         "climb steep objects or terrain",
          ATTITUDE_KIND, }),
    "animal handling" : 
      ({ SS_ANI_HANDL,
         "cerion",
         "somewhere in the village of Thornlin southwest of Minas Tirith"
       + " in the lands of Gondor",
         "handle animals correctly",
          ATTITUDE_NORMAL, }),
    "location sense" : 
      ({ SS_LOC_SENSE,
         "azealia",
         "at the Amazon camp in the Silent Forest in the lands of"
       + " Calia",
         "know where you are",
          ATTITUDE_NORMAL, }),
    "tracking" : 
      ({ SS_TRACKING,
         "noigo",
         "within a mazelike forest somewhere in Cadu",
         "find and follow tracks",
          ATTITUDE_NORMAL, }),
    "hunting" : 
      ({ SS_HUNTING,
         "rommenus",
         "somewhere in the Silver Forest of Terel",
         "follow quarry effectively",
          ATTITUDE_NORMAL, }),
    "awareness" : 
      ({ SS_AWARENESS,
         "tarshir",
         "in the village of Solace in the lands of Krynn",
         "notice things in your surroundings",
          ATTITUDE_NORMAL, }),
    "trading" : 
      ({ SS_TRADING,
         "hendi",
         "in the city of Telberin in the lands of Emerald",
         "deal with merchants",
          ATTITUDE_NORMAL, }),
    "riding" : 
      ({ SS_RIDING,
         "keleren",
         "in the stables of Bree east of the Shire in the lands of"
       + " Middle Earth",
         "handle animals correctly",
          ATTITUDE_NORMAL, }),
                          ]);

/* Prototypes */
public void    create_data_manager();
public void    adapt_script1(string skill, object who, object npc);
public void    adapt_cost(string skill, object who, object npc);
public void    adapt_train1(string skill, object who, object npc);
public int     trainer_busy(object who, object npc);
public void    merc_pay1(string skill, object who, object npc);
public void    check_new_adapt_msg(object who, string skill);
public void    adapt_increase(string skill, object who, object npc, int adapt_alarm);
public void    adapt_cleanup(object who, object npc, string skill, string ended = "");
public int     skill_extra_total(object who);
public int     skill_num(string skill);
public int    *query_skillnum_index();
public void    display_skill_enhance(mixed who);
public int     set_skill_enhance(object who, string skill, int amount);
public void    check_enhance_map(mixed who);
public void    clear_adapt(object who, string skill = 0, int leaving = 0);
public void    adapt_display(object who);
public void    print_columns(string *skill_names, object who, mapping enhance_map);
public void    print_columns2(string *skill_names, object who);
public mapping query_open_guilds();
public int     guild_is_open(string name);
public void    print_guild_list(object who);
public int     check_guild_membership(object who, string gname);
public int     parse_affiliation(string arg, object who);
public int     check_affiliation_valid(object who, string aff);
public string  format_the_the(string name);
public int     compute_guildstat_title(object who);
public int     compute_adapt_title(object who);

public mapping query_skmap() { return SkMap; }
public mapping query_adapt_map() { return Adapt_Map; }


/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    set_save_dir(DATA_DIR + "member_save/");
    set_garbage_dir(DATA_DIR + "member_save/old/");

    setuid();
    seteuid(getuid());
} /* create_data_manager */


/*
 * Function name:        adapt_script1
 * Description  :        Each trainer will have a different way of
 *                       talking to the player. This script controls the
 *                       interaction.
 * Arguments    :        string skill - the name of the skill to adapt,
 *                       object who - the player in question,
 *                       object npc - the npc who is the trainer
 */
public void
adapt_script1(string skill, object who, object npc)
{
    string  t_name = capitalize(Adapt_Map[skill][MERC_ADAPT_TRAINER]);
    int     remem,
            s_num = skill_num(skill);
    mapping enhance_map = get_info(who, "skill_enhance");

    if (trainer_busy(who, npc))
    {
        return;
    }

    remem = who->query_introduced(lower_case(t_name));

    who->catch_tell("You identify yourself as a Free Mercenary to "
      + ((remem > 0) ? capitalize(t_name) :
        "the " + npc->query_nonmet_name(who))
      + ", and ask for some adaptive training.\n");

    npc->add_prop(ADAPTING_PROP, who->query_real_name());

    if (member_array(s_num, m_indices(enhance_map)) > -1)
    {
        set_alarm(2.0, 0.0, &adapt_train1(skill, who, npc));
        return;
    }

    set_alarm(2.0, 0.0, &adapt_cost(skill, who, npc));
} /* adapt_script1 */


/*
 * Function name:        adapt_cost
 * Description  :        The trainer informs the player of the cost
 *                       to train with them.
 * Arguments    :        string skill - the name of the skill to adapt,
 *                       object who - the player in question,
 *                       object npc - the npc who is the trainer
 */
public void
adapt_cost(string skill, object who, object npc)
{
    int     attitude = Adapt_Map[skill][MERC_ADAPT_ATTITUDE];
    string  a_desc = Adapt_Map[skill][MERC_ADAPT_DESC];

    if (who->query_prop(MERC_COST_PROP) == npc->query_real_name())
    {
        switch (attitude)
        {
            case ATTITUDE_KIND:
                npc->command("say Perhaps you didn't hear me before?"
                  + " Oh, that's alright, I don't mind explaining"
                  + " again. You can <mercpay> me to get started - "
                  + " I charge " + ADAPT_BEGIN_COST + " platinum"
                  + " coins for my services.");
                break;
            case ATTITUDE_NORMAL:
                npc->command("say As I have said, the training can begin"
                  + " as soon as I receive " + ADAPT_BEGIN_COST
                  + " platinum coins. You can <mercpay> me"
                  + " presuming you are sufficiently funded.");
                break;
            case ATTITUDE_CRUEL:
                npc->command("say Do not try my patience, fool! I have"
                  + " already given you my terms. When I have received"
                  + " the " + ADAPT_BEGIN_COST + " platinum coins, then"
                  + " will I consider you worth my time. Now, stop all"
                  + " this drivel and <mercpay> me so we can begin.");
                break;
        }

        if (npc->query_real_name() == "sehis")
        {
            npc->command("emote telepathically says to you: Did I not"
              + " speak clearly before, perhaps? No matter. You can"
              + " <mercpay> me to get started - I charge "
              + ADAPT_BEGIN_COST + " platinum coins for this"
              + " service.");
        }

        npc->remove_prop(ADAPTING_PROP);
        return;
    }

    switch (attitude)
    {
        case ATTITUDE_KIND:
            npc->command("say Oh, how delightful! I always enjoy "
              + MERC_SCHOLAR + " sending me his hopefuls come to train.");
            who->catch_tell(npc->query_The_name(who) + " looks you up"
              + " and down appreciatively.\n");
            tell_room(environment(who), QCTNAME(npc) + " looks "
              + QCTNAME(who) + " up and down appreciatively.\n", who);
            npc->command("say Lets begin! I do ask that you first"
              + " <mercpay> me my initial learner's fee. To get things"
              + " off the ground, I ask a simple payment of "
              + ADAPT_BEGIN_COST + " platinum coins.");

            if (npc->query_real_name() == "sehis")
            {
                npc->command("emote telepathically says to you:"
                  + " Let us begin. I do ask that you first"
                  + " <mercpay> me my initial learner's fee."
                  + " I ask a simple payment of "
                  + ADAPT_BEGIN_COST + " platinum coins to begin.");
            }
            break;
        case ATTITUDE_NORMAL:
            npc->command("say Another one of " + MERC_SCHOLAR
              + "'s hopefuls come to learn how to " + a_desc
              + ", eh?");
            who->catch_tell(npc->query_The_name(who) + " looks you up"
              + " and down appraisingly.\n");
            tell_room(environment(who), QCTNAME(npc) + " looks "
              + QCTNAME(who) + " up and down appraisingly.\n", who);
            npc->command("say Very well. You can <mercpay> me my price"
              + " and we'll begin. To learn to adapt the " + skill
              + " skill I require an initial payment of "
              + ADAPT_BEGIN_COST + " platinum coins.");
            break;
        case ATTITUDE_CRUEL:
            npc->command("say Oh, how pathetic. Another one of "
              + MERC_SCHOLAR + "'s 'trainees' come to waste my"
              + " time?");
            who->catch_tell(npc->query_The_name(who) + " looks you up"
              + " and down scornfully.\n");
            tell_room(environment(who), QCTNAME(npc) + " looks "
              + QCTNAME(who) + " up and down scornfully.\n", who);
            npc->command("say As much as I can tell I won't enjoy"
              + " it, I'll consider helping you once you <mercpay>"
              + " me my price. Learning to adapt the " + skill
              + " skill is going to cost you an initial payment of "
              + ADAPT_BEGIN_COST + " platinum coins.");
            break;
    }

    npc->remove_prop(ADAPTING_PROP);
    who->add_prop(MERC_COST_PROP, npc->query_real_name());
} /* adapt_cost */


/*
 * Function name:        adapt_train1
 * Description  :        The trainer informs the player of the cost
 *                       to help them adapt an already trained skill.
 * Arguments    :        string skill - the name of the skill to adapt,
 *                       object who - the player in question,
 *                       object npc - the npc who is the trainer
 */
public void
adapt_train1(string skill, object who, object npc)
{
    int     attitude = Adapt_Map[skill][MERC_ADAPT_ATTITUDE];
    string  a_desc = Adapt_Map[skill][MERC_ADAPT_DESC];

    if (who->query_prop(MERC_COST_PROP) == npc->query_real_name())
    {
        switch (attitude)
        {
            case ATTITUDE_KIND:
                npc->command("say Perhaps you didn't hear me before?"
                  + " Oh, that's alright, I don't mind explaining"
                  + " again. You can <mercpay> me to get started - "
                  + " I charge " + ADAPT_RETURN_COST + " platinum"
                  + " coins for my services.");
            if (npc->query_real_name() == "sehis")
            {
                npc->command("emote telepathically says to you:"
                  + " Perhaps you didn't hear me before?"
                  + " Oh, that's alright, I don't mind explaining"
                  + " again. You can <mercpay> me to get started - "
                  + " I charge " + ADAPT_RETURN_COST + " platinum"
                  + " coins for my services.");
            }
                break;
            case ATTITUDE_NORMAL:
                npc->command("say As I have said, we can begin as soon"
                  + " as I receive " + ADAPT_RETURN_COST
                  + " platinum coins. You can <mercpay>"
                  + " me presuming you are sufficiently funded.");
                break;
            case ATTITUDE_CRUEL:
                npc->command("say Do not try my patience, fool! I have"
                  + " already given you my terms. When I have received"
                  + " the " + ADAPT_RETURN_COST + " platinum coins, then"
                  + " and ONLY then will I consider you worth my time."
                  + " Now, stop all this drivel and <mercpay> me so we"
                  + " can get this over with.");
                break;
        }

        npc->remove_prop(ADAPTING_PROP);
        return;
    }

    switch (attitude)
    {
        case ATTITUDE_KIND:
            npc->command("say Oh, delightful! You've returned for a bit"
              + " of a refresher on how to " + a_desc + "?");
            npc->command("say It will be my pleasure to assist. Let's"
              + " see now, you can go ahead and <mercpay> me the"
              + " cost of " + ADAPT_RETURN_COST + " platinum coins"
              + " and we will get started. Since you've already"
              + " done most of the hard work, we'll keep the price"
              + " nice and low from here on out.");
            if (npc->query_real_name() == "sehis")
            {
                npc->command("emote telepathically says to you:"
                   + " Ah, most delightful. You've returned for a bit"
                   + " of a refresher on how to " + a_desc + "?");
                npc->command("emote telepathically says to you:" 
                   + " It will be my pleasure to assist. Let's"
                   + " see now, you can go ahead and <mercpay> me the"
                   + " cost of " + ADAPT_RETURN_COST + " platinum coins"
                   + " and we will get started. Since you've already"
                   + " done most of the hard work, we'll keep the price"
                   + " nice and low from here on out.");
            }
            break;
        case ATTITUDE_NORMAL:
            npc->command("say Ah, back for a refresher course on how to "
              + a_desc + ", are we?");
            npc->command("say Sure, sure. You can <mercpay> me my price"
              + " and we'll begin. To help you adapt your " + skill
              + " to where you want it, I'll need to get "
              + ADAPT_RETURN_COST + " platinum coins.");
            break;
        case ATTITUDE_CRUEL:
            npc->command("say So, you've dragged your pathetic carcass"
              + " back to learn how to " + a_desc + " again, have you?");
            npc->command("say Very well, but make it quick! I"
              + " have more important things to do. Once you <mercpay>"
              + " me my price of " + ADAPT_RETURN_COST + " platinum"
              + " coins, we'll get your " + skill + " adapted to"
              + " where you want it.");
            break;
    }

    npc->remove_prop(ADAPTING_PROP);
    who->add_prop(MERC_COST_PROP, npc->query_real_name());
} /* adapt_train1 */


/*
 * Function name:        trainer_busy
 * Description  :        If the trainer is fighting someone, or is
 *                       already training someone else, then we
 *                       won't allow training to proceed.
 * Arguments    :        object who - the player
 *                       object npc - the trainer
 */
public int
trainer_busy(object who, object npc)
{
    if (npc->query_prop(ADAPTING_PROP))
    {
        if (npc->query_prop(ADAPTING_PROP) == who->query_real_name())
        {
            who->catch_tell("You are already training with "
              + npc->query_the_name(who) + "!\n");
        }
        else
        {
            who->catch_tell(npc->query_The_name(who) + " is currently"
              + " busy training someone else. You'll have to wait.\n");
        }
        return 1;
    }

    if (npc->query_attack())
    {
        if (npc->query_attack() == who)
        {
            who->catch_tell("Looks like you'll need to settle your"
              + " differences before any training will be taking place"
              + " with " + npc->query_the_name(who) + "!\n");
        }
        else
        {
            who->catch_tell(npc->query_The_name(who) + " is too busy"
              + " fighting to train you!\n");
        }

        return 1;
    }

    return 0;
} /* trainer_busy */


/*
 * Function name:        merc_pay1
 * Description  :        Allow the player to pay the appropriate cost
 *                       to the master trainer.
 * Arguments    :        string skill - the name of the skill to adapt,
 *                       object who - the player in question,
 *                       object npc - the npc who is the trainer
 */
public void
merc_pay1(string skill, object who, object npc)
{
    object  *inv_items = all_inventory(who);
    object  coin;
    object  temp_location;
    int     which_cost;
    int     attitude = Adapt_Map[skill][MERC_ADAPT_ATTITUDE];
    int    *freebie_skills;

    if (trainer_busy(who, npc))
    {
        return;
    }

    /* There are certain skills in the game that are not available in
     * adventurer guilds, and require guild membership to have. The
     * magic forms are all in this category. Therefore, we will allow
     * the training of these even if Mercenaries do not have the skill
     * learned otherwise. They will, however, only be able to adapt
     * it 30 levels rather than 100. We want to reserve true mastery
     * of these skills for people in layman guilds which support
     * them. (Gorboth)
     */
    freebie_skills = ({ SS_FORM_TRANSMUTATION,
                        SS_FORM_ILLUSION,
                        SS_FORM_DIVINATION,
                        SS_FORM_ENCHANTMENT,
                        SS_FORM_CONJURATION,
                        SS_FORM_ABJURATION,
                        SS_MOUNTED_COMBAT,
                        SS_BACKSTAB,
                     });

    if (!who->query_skill(skill_num(skill)))
    {
        if (member_array(skill_num(skill), freebie_skills) == -1)
        {
            who->catch_tell("You must have at least trained to novice"
              + " student in " + skill + " before you can adapt it from"
              + " this master!\n");
            return;
        }

        /* As a Mercenary, they actually learn the skill from the
         * Master trainer at this point, but only to level 0!
         */
        who->set_skill(skill_num(skill), 0);
    }

    if (who->query_skill(SS_MERC_ADAPT_SKILL)
         - skill_extra_total(who) < 1)
    {
        who->catch_tell("You do not have any adaptability points"
          + " to spend toward adapting a new skill. You either need"
          + " to clear one of your adaptations or train your"
          + " adaptability skill higher.\n");
        return;
    }

    foreach (object inv_item: inv_items)
    {
        if (inv_item->query_coin_type() == "platinum" &&
           (MASTER_OB(inv_item)) == "/std/coins")
        {
            coin = inv_item;
        }
    }

    if (!coin)
    {
        if (attitude == ATTITUDE_CRUEL)
        {
            npc->command("glare " + who->query_real_name());
            npc->command("say Wretch! Is this some form of joke?"
              + " I ask for platinum coins, not your pathetic"
              + " pocket lint! I will not trouble with lesser"
              + " coins than platinum. REMEMBER that next time.");
            return;
        }

        npc->command("frown");
        npc->command("say Perhaps you should return when you have"
          + " some platinum coins. I do not like to trouble with"
          + " lesser coins.");
        if (npc->query_real_name() == "sehis")
        {
            npc->command("emote telepathically says to you:"
               + " You will need to return when you have platinum"
               + " coins. I do not trouble with lesser monies.");
        }
        return;
    }

    which_cost = ( (member_array(skill_num(skill),
                    m_indices(get_info(who, "skill_enhance"))) == -1)
                     ? ADAPT_BEGIN_COST : ADAPT_RETURN_COST);

    if (coin->num_heap() < which_cost)
    {
        if (attitude == ATTITUDE_CRUEL)
        {
            npc->command("glare " + who->query_real_name());
            npc->command("say Oh, are we learning to count from Ogres?"
              + " I should kill you immediately for wasting my time"
              + " like this! Did you not hear me? I said "
              + which_cost + " platinum coins. Would it help if"
              + " I carved it into your skull?");
            return;
        }

        npc->command("frown");
        npc->command("say As I've said, the cost for my help will be "
          + which_cost + " platinum coins. Do not trouble me with lesser"
          + " coins than platinum.");
        if (npc->query_real_name() == "sehis")
        {
            npc->command("emote telepathically says to you:"
               + " As I have said, you will need to return when you"
               + " have " + which_cost + " platinum"
               + " coins. I do not trouble with lesser monies.");
        }
        return;
    }

    who->catch_tell("You pay " + which_cost + " platinum coins to "
      + npc->query_the_name(who) + ".\n");
    tell_room(environment(who), QCTNAME(who) + " pays some platinum"
      + " coins to " + QTNAME(npc) + ".\n", who);
    npc->command("emote smiles slowly.");
    npc->command("say Very well. Now ... pay attention.");

    if (npc->query_real_name() == "sehis")
    {
        npc->command("emote telepathically says to you:"
          + " Focus your mind. Pay attention now ...");
    }

    temp_location = clone_object("/std/room");
    coin->split_heap(which_cost);
    coin->move(temp_location);
    /* Clean up afterward. */
    temp_location->remove_object();

    npc->add_prop(ADAPTING_PROP, who->query_real_name());
    set_alarm(2.0, 0.0, &who->catch_tell(
        "You begin adaptive training with " + npc->query_the_name(who)
      + ". When you have reached your desired adaptation level, you"
      + " may <stop training>.\n"));
    set_alarm(2.0, 0.0, &tell_room(environment(who), QCTNAME(who)
      + " begins training how to " + Adapt_Map[skill][MERC_ADAPT_DESC]
      + " properly.\n", who));
    who->add_prop(TRAINING_PROP, 1);
    who->remove_prop(MERC_COST_PROP);

    if (!IN_ARRAY(skill_num(skill),
         m_indices(get_info(who, "skill_enhance"))))
    {
        who->add_prop(MERC_NEW_SKILL_FLAG, 1);
    }

    TELL_G(capitalize(who->query_real_name()) + " begins adaptive"
      + " training of " + skill + " skill!");

    set_alarm(3.0, 0.0, &adapt_increase(skill, who, npc));

    return;
} /* merc_pay1 */


/*
 * Function name:        check_new_adapt_msg
 * Description  :        If the player has just finished training
 *                       a skill they had not previously adapted,
 *                       we want to print a message to them telling
 *                       them that they can now train higher in
 *                       their adaptability skill.
 * Arguments    :        object who   - the player
 *                       string skill - the skill they adapted
 */
public void
check_new_adapt_msg(object who, string skill)
{
    int     a_lvl;
    string  a_txt;

    if (!who->query_prop(MERC_NEW_SKILL_FLAG))
    {
        return;
    }

    a_lvl = GUILD_A_TRAIN->sk_query_max(SS_MERC_ADAPT_SKILL);
    a_txt = SKILL_LIBRARY->sk_rank(a_lvl);

    set_alarm(2.0, 0.0, &who->catch_tell(
        "Your knowledge of adaptability has increased!\n"));
    set_alarm(2.0, 0.0, &who->catch_tell(
        "You can now train adaptability to " + a_txt
     + " in the Mercenary guildhalls.\n"));

    who->remove_prop(MERC_NEW_SKILL_FLAG);
} /* check_new_adapt_msg */


/*
 * Function name:        adapt_increase
 * Description  :        Allow the player to actually increase their
 *                       adaptation via a trainer.
 * Arguments    :        string skill - the name of the skill to adapt,
 *                       object who - the player in question,
 *                       object npc - the npc who is the trainer
 *                       int adapt_alarm - the repeating alarm to
 *                                         cancel when finished.
 */
public void
adapt_increase(string skill, object who, object npc, int adapt_alarm)
{
    mapping en_mapping = get_info(who, "skill_enhance");
    int    *freebie_skills;
    int     skillnum = Adapt_Map[skill][0];
    int     amount = en_mapping[skillnum];

    if (npc->query_attack())
    {
        if (npc->query_attack() == who)
        {
            npc->command("say The training session is over, fool! Now,"
              + " let us get to the REAL training!");
            if (npc->query_real_name() == "sehis")
            {
                npc->command("emote telepathically says to you:"
                  + " Insolent fool! Now you shall receive REAL"
                  + " training!");
            }
        }
        else
        {
            who->catch_tell(npc->query_The_name(who) + " is too busy"
              + " fighting to train you!\n");
        }

        adapt_cleanup(who, npc, skill, "(combat)");
        return;
    }

    if (environment(who) != environment(npc))
    {
        who->catch_tell("You have left your training session!\n");

        adapt_cleanup(who, npc, skill, "(left room)");
        return;
    }

    if (stringp(who->query_prop(TRAINING_PROP)) &&
        who->query_prop(TRAINING_PROP) == "stop")
    {
        who->catch_tell("You step back from your training and thank "
          + npc->query_the_name(who) + ", who nods silently.\n");
        tell_room(environment(who), QCTNAME(who) + " has finished"
          + " training, and steps back to rest.\n", who);

        adapt_cleanup(who, npc, skill, "(typed 'stop')");
        return;
    }

    freebie_skills = ({ SS_FORM_TRANSMUTATION,
                        SS_FORM_ILLUSION,
                        SS_FORM_DIVINATION,
                        SS_FORM_ENCHANTMENT,
                        SS_FORM_CONJURATION,
                        SS_FORM_ABJURATION,
                        SS_MOUNTED_COMBAT,
                        SS_BACKSTAB,
                     });

    /* This is where we cap the so-called freebie skills at 30 points
     * of adapted skill. The way we do this is to see if they have the
     * skill trained beyond 0 normally. If so, we allow them to exceed
     * the cap. If not, it is capped at 30.
     */
    if (member_array(skillnum, freebie_skills) > -1)
    {
        if (!who->query_base_skill(skillnum))
        {
            if (amount > 29)
            {
                who->catch_tell("You seem to have hit a brick wall with"
                  + " this skill. Evidently having no real learning"
                  + " outside of adaptability has its limits - and"
                  + " you've reached them! You step back from your"
                  + " training and smile sadly at "
                  + npc->query_the_name(who) + " who nods in"
                  + " silent understanding.\n");
                tell_room(environment(who), QCTNAME(who) + " shakes "
                  + who->query_possessive() + " head in frustration"
                  + " and steps back from the training, apparently"
                  + " finished.\n", who);

                adapt_cleanup(who, npc, skill, "(freebie skill capped)");
                return;
            }
        }
    }

    /* Knights are slated to be the masters of blocking technique
     * in the game. As such, Mercs are only allowed to learn it
     * to 50, not 100. We cap it at 20 adaptation, since it is
     * taught in AGs to 30.
     */
    if (skillnum == SS_BLOCK)
    {
        if (amount > 19)
        {
            npc->command("say I shall train you no further. Mastery of this"
              + " skill is reserved for the Knighthood alone.");
            who->catch_tell("The training session having (apparently)"
              + " ended, you step back and nod solemnly.\n");
            tell_room(environment(who), QCTNAME(who) + " steps back"
              + " and nods solemnly.\n", who);

            adapt_cleanup(who, npc, skill, "(reached block cap)");
            return;
        }
    }
        
    who->catch_tell(" ... your training progresses ...\n");
    tell_room(environment(who), QCTNAME(who) + " continues to"
      + " train.\n", who);

    if (set_skill_enhance(who, skill, 1))
    {
        adapt_cleanup(who, npc, skill);
    }
    else
    {
        set_alarm(3.0, 0.0, &adapt_increase(skill, who, npc));
    }

    /* This tells the cmdsoul that the player has actually trained
     * one level in the adaptation of this skill. We check this in the
     * stop_training() function in the cmdsoul to prevent players from
     * stopping what they have not yet even started.
     */
    who->add_prop(TRAINING_PROP, 2);
        
} /* adapt_increase */


/*
 * Function name:        adapt_cleanup
 * Description  :        Perform a few clean up functions once a player
 *                       finishes adapting a skill
 * Arguments    :        object who - the player who was training
 *                       object npc - the npc they were training with
 *                       string skill - the name of the skill
 *                       string ended - the reason training ended
 */
public void
adapt_cleanup(object who, object npc, string skill, string ended = "")
{
    who->remove_prop(TRAINING_PROP);
    npc->remove_prop(ADAPTING_PROP);
    check_new_adapt_msg(who, skill);

    write_file(LOG_DIR + "adapt_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(who->query_real_name()) 
      + " raised " + upper_case(skill) + " by "
      + Adapt_Log[who->query_real_name()] + ". "
      + ended + "\n");

    m_delkey(Adapt_Log, who->query_real_name());
} /* adapt_cleanup */


/*
 * Function name:        skill_extra_total
 * Description  :        Checks all of the skill enhancements listed in
 *                       the skillmap of the player's merc data file.
 *                       The sum of all enhancements is returned.
 * Arguments    :        object who - the player
 * Returns      :        int - the sum of all enhancements
 */
public int
skill_extra_total(object who)
{
    int     *v_skills = query_skillnum_index(),
             total = 0;
    mapping  enhance_map;

    set_this_player(who);

    check_enhance_map(who);
    enhance_map = get_info(who, "skill_enhance");

    foreach (int skillnum: v_skills)
    {
        if (enhance_map[skillnum])
        {
            total += enhance_map[skillnum];
        }
    }

    return total;
} /* skill_extra_total */


/*
 * Function name:        skill_num
 * Description  :        determine the mudlib defined (from <ss_types.h>
 *                       number for a given skill name.
 * Arguments    :        string - the name of the skill
 * Returns      :        int - the skill number
 */
public int
skill_num(string skill)
{
    return Adapt_Map[skill][MERC_ADAPT_SKILLNUM];
} /* skill_num */


/*
 * Function name:        query_skillnum_index
 * Description  :        takes a look at all the indicies in SS_SKILL_DESC
 *                       and tests them to see if they hold a valid
 *                       array. If so, we add that number to our
 *                       array of valid index points to be returned
 * Returns      :        array - the valid index points from SS_SKILL_DESC
 */
public int *
query_skillnum_index()
{
    int  *valid_skills;

    valid_skills = m_indices(SkMap);
    valid_skills -= ({ SS_WEP_JAVELIN });

    return valid_skills;
} /* query_skillnum_index */


/*
 * Function name:        display_skill_enhance
 * Description  :        Display a list of skills that the palyer has
 *                       had enhanced.
 * Arguments    :        mixed who - the player to check for
 */
public void
display_skill_enhance(mixed who)
{
    int     *v_skills = query_skillnum_index();
    mapping  enhance_map;

    set_this_player(who);

    check_enhance_map(who);
    enhance_map = get_info(who, "skill_enhance");

    write("Enhanced according to Merc stuff:\n"
        + "--------------------------------\n");
    foreach (int skillnum: v_skills)
    {
        if (enhance_map[skillnum])
        {
            write(capitalize(SkMap[skillnum][0]) + ": "
              + enhance_map[skillnum] + "\n");
        }
    }

    write("Total: " + skill_extra_total(who) + "\n\n");
    write("Enhanced according to query_skill_extra():\n"
        + "-----------------------------------------\n");

    foreach (int skillnum: v_skills)
    {
        if (this_player()->query_skill_extra(skillnum))
        {
            write(capitalize(SkMap[skillnum][0]) + ": "
              + this_player()->query_skill_extra(skillnum) + "\n");
        }
    }
} /* display_skill_enhance */


/*
 * Function name:        set_skill_enhance
 * Description  :        set the enhancement of a particular skill
 *                       to a specific level.
 * Arguments    :        object who - the player to set for
 *                       string skill - the name of the skill
 *                       int amount - the amount to adjust the skill
 * Returns      :        int 0 - train successful
 *                       int 1 - train failed
 */
public int
set_skill_enhance(object who, string skill, int amount)
{
    mapping en_mapping;
    int     skillnum = Adapt_Map[skill][0];
    int     old_amount;
    int     new_amount;
    int     trained_so_far = Adapt_Log[who->query_real_name()];

    if ( (skill_extra_total(who) + amount)
        > who->query_skill(SS_MERC_ADAPT_SKILL) )
    {
        who->catch_tell("Having reached the limits of your"
          + " adaptability you step back from your training and"
          + " let the awareness of your heightened abilities"
          + " sink in a bit.\n");
        tell_room(environment(who), QCTNAME(who) + " steps back"
          + " from " + who->query_possessive() + " training and"
          + " pauses reflectively.\n", who);
        return 1;
    }

    if ( (who->query_skill(skill_num(skill)) + amount) > 100)
    {
        who->catch_tell("You have reached the limits of mortal skill"
          + " with your ability to " + Adapt_Map[skill][3] + ". You"
          + " step back from your training and smile with"
          + " satisfaction at your complete mastery of this"
          + " particular lore.\n");
        tell_room(environment(who), QCTNAME(who) + " steps back"
          + " from " + who->query_possessive() + " training and"
          + " smiles with satisfaction.\n", who);
        return 1;
    }

    check_enhance_map(who);

    en_mapping = get_info(who, "skill_enhance");
    old_amount = en_mapping[skillnum];
    new_amount = old_amount + amount;

    en_mapping[skillnum] = new_amount;

    set_info(who, "skill_enhance", en_mapping);

    old_amount = who->query_skill_extra(skill_num(skill));

    who->catch_tell("Your ability to " + Adapt_Map[skill][3]
      + " rises to " + sk_rank(who->query_skill(skill_num(skill)))
      + ".\n");

    Adapt_Log[who->query_real_name()] = trained_so_far + 1;

    return 0;
} /* set_skill_enhance */


/*
 * Function name:        check_enhance_map
 * Description  :        see if the mapping has been set yet for
 *                       the datafile. If not, set it up with a
 *                       null mapping
 * Arguments    :        mixed who - the player
 */
public void
check_enhance_map(mixed who)
{
    if (mappingp(get_info(who, "skill_enhance")))
    {
        return;
    }

    set_info(who, "skill_enhance", ([]));
    return;
} /* check_enhance_map */


/*
 * Function name:        clear_adapt
 * Description  :        Set the adaptation for each skill that the
 *                       player has set back to zero, and remove the
 *                       extra skill they possess.
 * Arguments    :        object who - the player in question
 *                       string skill - the name of the skill to
 *                                      clear. If 0, all are cleared
 *                       int    leaving - true if the player is leaving
 *                                        the guild
 */
public void
clear_adapt(object who, string skill = 0, int leaving = 0)
{
    int     *v_skills;
    int      s_amount;
    mapping  enhance_map;

    check_enhance_map(who);

    enhance_map = get_info(who, "skill_enhance");

    if (skill)
    {
        if (member_array(skill_num(skill), m_indices(enhance_map)) == -1)
        {
            who->catch_tell("You have not yet even learned how to adapt"
              + " that skill, and thus cannot remove it!\n");
            return;
        }

        if (!enhance_map[skill_num(skill)])
        {
            who->catch_tell("You are not currently adapting that"
              + " skill!\n");
            return;
        }

        v_skills = ({ skill_num(skill) });
    }
    else
    {
        v_skills = query_skillnum_index();
    }

    foreach (int skillnum: v_skills)
    {
        if (enhance_map[skillnum])
        {
            s_amount = who->query_skill_extra(skillnum);

            enhance_map[skillnum] = 0;
            set_info(who, "skill_enhance", enhance_map);
        }
    }

    if (leaving)
    {
        who->catch_tell("As you turn away from your Mercenary training,"
          + " the adapted knowledge you have gained escapes your mind"
          + " and is lost.\n\n");
    }
    else
    {
        who->catch_tell("You clear your mind of "
          + ((skill) ? "all adapted " + skill : "all previously adapted")
          + " skill allocations.\n");
    }

    write_file(LOG_DIR + "adapt_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(who->query_real_name()) 
      + " *** cleared " + ((skill) ? skill : "all") 
      + " allocations.\n");
} /* clear_adapt */


/*
 * Function name: sort_name
 * Description  : Sort two words alphabetically
 * Arguments    : string a - the first word
 *                string b - the second word
 * Returns      : int -1 - a comes before b alphabetically
 *                     1 - b comes before a alphabetically
 */
nomask int
sort_name(string a, string b)
{
    return ((a == b) ? 0 : ((a < b) ? -1 : 1));
} /* sort_name * /


/*
 * Function name:        adapt_display
 * Description  :        Print a nifty list for the player describing
 *                       which skills they have learned to adapt, and
 *                       to what levels they are currently allocating
 *                       adaptation points.
 * Arguments    :        object who - the player to display for
 */
public void
adapt_display(object who)
{
    int     *v_skills = query_skillnum_index(),
             ap_available,
             ap_spent,
             ap_remaining;
    mapping  enhance_map;
    string  *skill_names = ({});

    /* Lets make sure that a formatted datafile exists for this
     * player.
     */
    check_enhance_map(who);

    /* Lets populate an array with all of the skill numbers that this
     * player has already adapted.
     */
    enhance_map = get_info(who, "skill_enhance");

    /* Now, lets populate an array with the names of the skills that
     * the player has actually trained for adaptation so far.
     */
    foreach (int skillnum: v_skills)
    {
        if (member_array(skillnum, m_indices(enhance_map)) > -1)
        {
            skill_names += ({ SS_SKILL_DESC[skillnum][0] });
        }
    }

    ap_available = who->query_skill(SS_MERC_ADAPT_SKILL);
    ap_spent = skill_extra_total(who);
    ap_remaining = ap_available - ap_spent;

    /* Print the list header. */
    who->catch_tell(
        sprintf("%|80s",
        ".--------------------------------------------------------.\n")
      + sprintf("%|80s",
        "|             -**- Adapted Skill Levels -**-               |\n")
      + sprintf("%|80s",
        "|      (Current allocations displayed in parenthesis)      |\n")
      + sprintf("%|80s",
        sprintf("|  Adaptability Points: "
          + "%-3d Allocated: %-3d Remaining: %-3d  ",
             ap_available, ap_spent, ap_remaining)
      + "|\n")
      + sprintf("%|80s",
        "| ======================================================== |\n")
      + sprintf("%|80s",
        "|                                                          |\n"));

    /* Now, lets print the names of the skills in columns that the
     * player has adapted so far.
     */
    print_columns(skill_names, who, enhance_map);
    skill_names = ({}); /* re-initialize the array */

    /* Now, lets recreate the array, this time listing those skills
     * that the player has yet to adapt with a specialized trainer.
     */
    foreach (int skillnum: v_skills)
    {
        if (member_array(skillnum, m_indices(enhance_map)) == -1)
        {
            skill_names += ({ SS_SKILL_DESC[skillnum][0] });
        }
    }

    /* Print a divider. */
    who->catch_tell(
        sprintf("%|80s",
        "|                                                          |\n")
      + sprintf("%|80s",
        "| ======================================================== |\n")
      + sprintf("%|80s",
        "|    Skills that have yet to be trained for adaptation     |\n")
      + sprintf("%|80s",
        "| ======================================================== |\n")
      + sprintf("%|80s",
        "|                                                          |\n"));

    /* Now, we print the names of the unadapted skills in columns. */
    print_columns(skill_names, who, enhance_map);

    /* Print the list footer. */
    who->catch_tell(
        sprintf("%|80s",
        "|                                                          |\n")
      + sprintf("%|80s",
        "| ======================================================== |\n")
      + sprintf("%|80s",
        "| You may <adapt skillname> to attempt to adapt any skill. |\n")
      + sprintf("%|80s",
        "`--------------------------------------------------------'\n"));
} /* adapt_display */


/*
 * Function name:        print_columns
 * Description  :        Print a double-column alphabetized list of
 *                       a given array
 * Arguments    :        string *skill_names - the array of strings
 *                                             to print
 *                       object who - who to print it to
 *                       mapping enhance_map - mapping of the adaptation
 *                                             list from the player's
 *                                             merc data file
 */
public void
print_columns(string *skill_names, object who, mapping enhance_map)
{
    string  column1;
    string  column2;
    int     i,
            n,
            odd_true,
            half,
            c1_val,
            c2_val;

    /* Lets alphabetize the array of skill names. */
    skill_names = sort_array(skill_names, sort_name);
    n = sizeof(skill_names);
    half = n / 2;
    odd_true = (n % 2 == 1);

    if (n)
    {
        for (i = 0; i < half + odd_true; i++)
        {
            column1 = capitalize(skill_names[i]);
            column2 = "";
            c1_val = enhance_map[skill_num(skill_names[i])];

            /* If the player has currently allotted adaptation points
             * to this skill, we display how many in () alongside.
             */
            if (c1_val)
            {
                /* For formatting purposes, we need to know if the
                 * amount of adapted skill exceeds 9.
                 */
                column1 = ( (c1_val > 9) ? "(" : " (")
                        + c1_val + ") " + column1;
            }
            else
            {
                column1 = "     " + column1;
            }

            if (half > i)
            {
                /* This is a bit tricky. We have to know if the size
                 * of the list is odd. Since we are printing two columns,
                 * we want to begin the second column just past the
                 * halfway point (for alphabetical purposes). If it
                 * is odd in length, though, we want to go one more
                 * place past that.
                 */
                column2 = capitalize(
                              skill_names[i + half + odd_true]);
                c2_val = enhance_map[skill_num(
                              skill_names[i + half + odd_true])];

                if (c2_val)
                {
                    column2 = ( (c2_val > 9) ? "(" : " (")
                            + c2_val + ") " + column2;
                }
                else
                {
                    column2 = "     " + column2;
                }
            }

            /* All set. So lets print out this line! */
            who->catch_tell(sprintf("%|80s",
                "|" + sprintf(" %-26s    %-26s %2s",
                column1, column2, "|\n")));
        }
    }
    else /* Nothing to list. */
    {
        who->catch_tell(sprintf("%|80s",
        "|                          (none)                          |\n"));
    }
} /* print_columns */


/*
 * Function name:        print_columns2
 * Description  :        Print a double-column alphabetized list of
 *                       a given array
 * Arguments    :        string *skill_names - the array of strings
 *                                             to print
 *                       object who - who to print it to
 */
public void
print_columns2(string *skill_names, object who)
{
    string  column1;
    string  column2;
    int     i,
            n,
            odd_true,
            half,
            c1_val,
            c2_val;

    /* Lets alphabetize the array of skill names. */
    skill_names = sort_array(skill_names, sort_name);
    n = sizeof(skill_names);
    half = n / 2;
    odd_true = (n % 2 == 1);

    if (n)
    {
        for (i = 0; i < half + odd_true; i++)
        {
            column1 = capitalize(skill_names[i]);
            column2 = "";

            if (half > i)
            {
                /* This is a bit tricky. We have to know if the size
                 * of the list is odd. Since we are printing two columns,
                 * we want to begin the second column just past the
                 * halfway point (for alphabetical purposes). If it
                 * is odd in length, though, we want to go one more
                 * place past that.
                 */
                column2 = capitalize(
                              skill_names[i + half + odd_true]);
            }

            /* All set. So lets print out this line! */
            who->catch_tell(sprintf("%|80s",
                sprintf(" %-36s    %-36s",
                column1, column2, "\n")));
        }
    }
    else /* Nothing to list. */
    {
        who->catch_tell(sprintf("%|80s",
        "|                          (none)                          |\n"));
    }
} /* print_columns2 */


/* Function name:        query_open_guilds
 * Description  :        Generates a mapping containing all open
 *                       guilds in the game.
 * Returns      :        mapping - the guild info
 */
public mapping
query_open_guilds()
{
    string *open_guilds;
    mapping results;

    setuid();
    seteuid(getuid());

    open_guilds = filter(SECURITY->query_guilds(), guild_is_open);

    results = ([ ]);
    foreach (string guild : open_guilds)
    {
        results[guild] = SECURITY->query_guild_long_name(guild);
    }

    return results;
} /* query_open_guilds */
    


/*
 * Function name:        guild_is_open
 * Description  :        filter check to see if the guild is currently
 *                       open.
 * Arguments    :        string name - the name of the guild
 * Returns      :        1 - its open, 0 - its closed
 */
public int
guild_is_open(string name)
{
    return ((SECURITY->query_guild_phase(name) == "open") ? 1 : 0);
} /* guild_is_open */


public void
print_guild_list(object who)
{
    mapping  open_guilds = MERC_MASTER->query_open_guilds();
    string  *guild_titles = ({ });

    foreach (string guild : m_indices(open_guilds))
    {
        guild_titles += ({ open_guilds[guild] });
    }

    print_columns2(guild_titles, who);
} /* print_guild_list */


/*
 * Function name:        check_guild_membership
 * Description  :        We do not allow Mercs to affliate with a
 *                       guild they are already a member of.
 * Arguments    :        object who - the player object
 *                       string gname - the short name of the guild
 * Returns      :        int 1 - if they are a member,
 *                           0 - if they are not a member
 */
public int
check_guild_membership(object who, string gname)
{
    string  this_guild = SECURITY->query_guild_long_name(gname),
            player_guild;

    if (who->query_guild_name_lay()   != this_guild &&
        who->query_guild_name_race()  != this_guild &&
        who->query_guild_name_craft() != this_guild)
    {
        return 0;
    }

    if (!this_guild) /* It isn't a guild */
    {
        return 0;
    }

    who->catch_tell("You are already affiliated with "
      + format_the_the(gname) + " as an actual member! Choose an"
      + " affiliation you do not already naturally have.\n");
    return 1;
} /* check_guild_membership */


/*
 * Function name:        parse_affiliation
 * Description  :        allow the player to try to affiliate themselves
 *                       with something
 * Arguments    :        string arg - what the player typed 
 *                       object who - the player object
 * Returns      :        1 - success, 0 - failure
 */
public int
parse_affiliation(string arg, object who)
{
    string  txt = "So be it. You have now officially declared"
      + " yourself to be affiliated with ";
    string  mtitle;
    string  guild = "";
    string  gender = ( (who->query_gender()) ? "sister" : "brother");
    string  lay_guild;
    string  race_guild;
    string  craft_guild;
    object  other_player;

    if (get_info(who, "affiliation"))
    {
        guild = format_the_the(get_info(who, "affiliation"));

        /* Doesn't seem to be a guild, so lets call it whatever was"
         * saved in the file.
         */
        if (!strlen(guild))
        {
            guild = capitalize(get_info(who, "affiliation"));
        }

        who->catch_tell("You are already affiliated with " + guild
          + "! If you wish to switch your affiliation, you must first"
          + " <maffiliate clear> to reestablish yourself as a"
          + " Free Mercenary.\n");
        return 1;
    }

    lay_guild   = who->query_guild_name_lay();
    race_guild  = who->query_guild_name_race();
    craft_guild = who->query_guild_name_craft();

    switch(lower_case(arg))
    {
    case "army":
    case "armies":
        who->catch_tell("There are many armies in the lands. Please be"
          + " more specific.\n");
        return 0;
        break;
    case "aa":
    case "angmar":
    case "army of angmar":
    case "angmars army":
    case "angmar's army":
    case "angmarim":
        if (who->query_race() == "hobbit" ||
            who->query_race() == "elf")
        {
            who->catch_tell("The only way the Army of Angmar would"
              + " want someone of your race is cooked in a soup and"
              + " served with dinner! Forget it!\n");
            return 0;
            break;
        }

        txt += "the Army of Angmar. May the forces of the West"
          + " fear your exploits!";
        mtitle = "Weapon of the Witch King and Defender of the Army of"
          + " Angmar";
        guild = "aa";
        break;
    case "amazon":
    case "amazons":
        txt += "the Amazons. May you bring strength to the Silent"
          + " Forest!";
        mtitle = "Guardian of the Amazons and Defender of the Silent"
          + " Forest";
        guild = "amazon";
        break;
    case "ogre":
    case "ogres":
    case "army of darkness":
    case "aod":
        txt += "the Army of Darkness. May you be of value to the"
          + " Darklings and their enormous (and clumsy) servants!";
        mtitle = "Ogre Assistant and Skull-Producer for the Army"
          + " of Darkness";
        guild = "aod";
        break;
    case "archer":
    case "archers":
    case "elvish archers":
    case "ansalon elvish archers":
        txt += "the Archers of Qualinesti. May your skills protect"
          + " them and their wooded homeland!";
        mtitle = "Friend to the Elvish Archers and Protector of"
          + " Qualinesti";
        guild = "archers";
        break;
    case "bloodguard":
    case "bloodguards":
    case "blood-guard":
    case "blood-guards":
    case "blood guard":
    case "blood guards":
    case "bg":
        txt += "the Bloodguard of Terel. May you join with their"
          + " efforts to protect the Coven!";
        mtitle = "Aid to the Bloodguard in their Watch over the"
          + " Vampyr Coven";
        guild = "bg";
        break;
    case "blademaster":
    case "blademasters":
    case "blade master":
    case "blade masters":
    case "blademaster of khalakhor":
    case "blademasters of khalakhor":
    case "blade master of khalakhor":
    case "blade masters of khalakhor":
    case "bok":
        txt += "the Blademasters of Khalakhor. May your sidearm be"
          + " as a " + gender + "-blade to theirs!";
        mtitle = capitalize(gender) + "-Blade to the Blademasters"
          + " of Khalakhor";
        guild = "bok";
        break;
    case "cadet":
    case "cadets":
    case "cadet of gelan":
    case "cadets of gelan":
        txt += "the Cadets of Gelan. May you protect and guide these"
          + " young adventurers in their early days of adventuring!";
        mtitle = "Staunch Defender of the Cadets of Gelan and"
          + " Shield to Young Adventurers";
        guild = "cadet";
        break;
    case "calian":
    case "calians":
    case "calian warrior":
    case "calian warriors":
    case "warriors of calia":
        txt += "the Calian Warrior's Guild. May your strength join"
          + " with those who defend Caliana!";
        mtitle = "Sworn Ally of Caliana and her Elite Warriors";
        guild = "calian";
        break;
    case "clan":
    case "neidar":
    case "neidars":
    case "neidar clan":
    case "dwarven warriors":
    case "dwarven warriors of the neidar clan":
        txt += "the Dwarven Warriors of the Neidar Clan. May your"
          + " blood be mixed with theirs in the defence of Estwilde!";
        mtitle = "Aid to the Dwarven Warriors of the Neidar Clan"
          + " and Defender of Estwilde";
        guild = "clan";
        break;
    case "clans":
    case "clans of khalakhor":
        txt += "the Clans. May your deeds strengthen the defence of"
          + " Khalakhor!";
        mtitle = "Friend of Khalakhor and True Defender of the Clans";
        guild = "cok";
        break;
    case "dragonarmy":
    case "dragonarmies":
    case "dragon army":
    case "dragon armies":
        who->catch_tell("Which Dragonarmy do you wish to ally yourself"
          + " with? If you just wish a general affiliation, you can"
          + " do <maffiliate dragonarmy all>.\n");
        return 0;
        break;
    case "dragonarmy all":
    case "dragon army all":
    case "dragonarmies all":
    case "dragon armies all":
        txt += "the Dragonarmies of Ansalon. May Lord Ariakas be"
          + " pleased by your deeds!";
        mtitle = "Volunteer Conscript of the Dragonarmies of"
          + " Ansalon and Servant of Lord Ariakas";
        guild = "dragonarmy";
        break;
    case "red dragonarmy":
    case "red dragon army":
    case "red dragonarmies":
    case "red dragon armies":
        txt += "the Red Dragonarmies of Ansalon. May your deeds be"
          + " satisfactory to Lord Verminaard!";
        mtitle = "Volunteer Conscript of the Red Dragonarmy, and"
          + " Servant of Lord Verminaard";
        guild = "dragonarmy";
        break;
    case "blue dragonarmy":
    case "blue dragon army":
    case "blue dragonarmies":
    case "blue dragon armies":
        txt += "the Blue Dragonarmies of Ansalon. May your deeds be"
          + " satisfactory to Lady Kitiara!";
        mtitle = "Volunteer Conscript of the Blue Dragonarmy, and"
          + " Servant of Lady Kitiara";
        guild = "dragonarmy";
        break;
    case "white dragonarmy":
    case "white dragon army":
    case "white dragonarmies":
    case "white dragon armies":
        txt += "the White Dragonarmies of Ansalon. May your deeds be"
          + " satisfactory to Lord Fael-Thas!";
        mtitle = "Volunteer Conscript of the White Dragonarmy, and"
          + " Servant of Lord Fael-Thas";
        guild = "dragonarmy";
        break;
    case "black dragonarmy":
    case "black dragon army":
    case "black dragonarmies":
    case "black dragon armies":
        txt += "the Black Dragonarmies of Ansalon. May your deeds be"
          + " satisfactory to Lord Lucien!";
        mtitle = "Volunteer Conscript of the Black Dragonarmy, and"
          + " Servant of Lord Lucien";
        guild = "dragonarmy";
        break;
    case "green dragonarmy":
    case "green dragon army":
    case "green dragonarmies":
    case "green dragon armies":
        txt += "the Green Dragonarmies of Ansalon. May your deeds be"
          + " satisfactory to Lord Salah-Khan!";
        mtitle = "Volunteer Conscript of the Green Dragonarmy, and"
          + " Servant of Lord Salah-Khan";
        guild = "dragonarmy";
        break;
    case "drow":
        txt += "the Drow of Underdark. May the blood you spill be"
          + " pleasing to the Spider Queen!";
        mtitle = "Blade-Servant to the Drow and Slave of the Spider"
          + " Queen";
        guild = "drow";
        break;
    case "dunedan":
    case "dunedain":
        txt += "the Dunedain of Middle Earth. May your blade ever"
          + " rise to the needs of the Men of Westernesse!";
        mtitle = "Friend of the Dunedain and Ally to the Men of"
          + " Westernesse";
        guild = "dunedain";
        break;
    case "eilgalaith":
    case "eil galaith":
    case "eil-galaith":
        txt += "the Eil-Galaith of Khalakhor. May you protect the"
          + " bloodlines of the Elves!";
        mtitle = "Protector of the Sanctuary Tower of Galaith";
        guild = "eilgalaith";
        break;
    case "gardener":
    case "gardeners":
    case "gardener of gont":
    case "gardeners of gont":
        txt += "the Gardeners of Gont. May ... uh ... you protect them"
          + " from root weevils! ... ?";
        mtitle = "Fanatical Supporter of the Gardeners of Gont and"
          + " Mortal Enemy of Root Weevils";
        guild = "gardeners";
        break;
    case "gladiator":
    case "gladiators":
    case "gladiator guild":
    case "gladiators guild":
        txt += "the Gladiator Guild. May your involvement bring glory"
          + " to Kalak!";
        mtitle = capitalize(gender) + " in Blood to the Gladiator"
          + " Guild and Devotee of Kalak";
        guild = "gladiator";
        break;
    case "grunt":
    case "grunts":
    case "grunt guild":
    case "grunts guild":
        txt += "the Grunts Guild. May your thrown poo mix with"
          + " theirs!";
        mtitle = "Enthusiastic Grunt Supporter and Lover of Goblin"
          + " \"Traditions\"";
        guild = "grunt";
        break;
    case "herald":
    case "heralds":
    case "herald of the valar":
    case "heralds of the valar":
    case "valar":
    case "valars":
    case "ainu":
    case "ainur":
        if (who->query_race() == "goblin" ||
            who->query_race_name() == "orc")
        {
            who->catch_tell("The Valar have no use for creaturs of"
              + " Sauron like yourself!\n");
            return 0;
            break;
        }

        txt += "the Heralds of the Valar. May your blade be a boon"
          + " to the disciples of the Ainur!";
        mtitle = "Source of Strength to the Heralds of the Valar and"
          + " Warrior for the Ainur";
        guild = "heralds";
        break;
    case "hobbit":
    case "hobbits":
    case "adventuresome hobbit":
    case "adventuresome hobbits":
    case "hobbit guild":
    case "hobbits guild":
    case "adventuresome hobbit guild":
    case "adventuresome hobbits guild":
        if (who->query_race() == "goblin" ||
            who->query_race_name() == "orc")
        {
            who->catch_tell("What?! A goblin befriend the Shirefolk?"
              + " Forget it, you'd be run out of the Four Farthings"
              + " immediately!\n");
            return 0;
            break;
        }

        txt += "the Adventuresome Hobbits Guild! May your watch on"
          + " the Shire be vigilant!";
        mtitle = "Champion of Hobbits and their Needs and Extreme"
          + " Enthusiast of All Forms of Pipeweed";
        guild = "hobbit";
        break;
    case "inventor":
    case "inventors":
    case "gnome":
    case "gnomes":
    case "gnomish inventor guild":
    case "gnomish inventors":
    case "gnomish inventors guild":
        txt += "the Gnomish Inventors. May you fight alongside them"
          + " without being accidentally blown up!";
        mtitle = "Tinkerer Enthusiast and Proud Protector of the"
          + " Gnomish Inventors Guild";
        guild = "inventor";
        break;
    case "kender":
    case "kenders":
    case "kender guild":
    case "kenders guild":
    case "secret society":
    case "secret society of uncle trapspringer":
        txt += "the Secret Society of Uncle Trapspringer. Wait ..."
          + " aiding Kenders? Are you sure about this?! Very well,"
          + " but don't blame anyone but yourself when you find"
          + " your favorite heirloom \"borrowed\" by your new"
          + " allies!";
        mtitle = "Staunch Supporter of Kenders and their Wanton"
          + " Ways";
        guild = "inventor";
        break;
    case "knight":
    case "knights":
    case "knighthood":
    case "solamnia":
    case "solaminan":
    case "solamnians":
    case "solamnian knight":
    case "solamnian knights":
    case "knight of solamnia":
    case "knights of solamnia":
        if (who->query_race() == "goblin")
        {
            who->catch_tell("The Knighthood would never accept"
              + " the help of a goblin like yourself!\n");
            return 0;
            break;
        }

        txt += "the Solamnian Knights. May your exploits at their"
          + " side bring glory to Paladine!";
        mtitle = capitalize(gender) + "-In-Arms to the Knights of"
          + " Solamnia and Loyal Servant of the Conclave";
        guild = "knight";
        break;
    case "mage":
    case "mages":
    case "magic":
    case "magic user":
    case "magic users":
    case "magic-user":
    case "magic-users":
        who->catch_tell("There are many types of magic users in the"
          + " realm. Which, specifically, do you wish to affiliate"
          + " yourself with?\n");
        return 0;
        break;
    case "morgul mage": 
    case "morgul mages":
    case "mages of morgul":
    case "mage of morgul":
    case "morgul":
    case "nazgul":
    case "nazguls":
    case "lord nazgul":
    case "lord of the nazgul":
    case "the nine":
    case "mm":
        if (who->query_race() == "elf" &&
            who->query_race_name() != "orc")
        {
            who->catch_tell("An elf, an ally of Morgul? What, is this"
              + " some sort of April Fool's joke?\n");
            return 0;
            break;
        }

        txt += "the Society of Morgul Mages. May your service be"
          + " pleasing to the Nine!";
        mtitle = "Shield Knight of Minas Morgul and Dark Crusader of"
          + " the Nine";
        guild = "mage";
        break;
    case "mariner":
    case "mariners":
        txt += "the Mariners of Genesis. May you protect them from"
          + " brigands, pirates, and other sea scum!";
        mtitle = "Fierce Loyalist to the Mariners of Genesis and"
          + " All Seafaring Interests of Kalaman";
        guild = "mariner";
        break;
    case "merc":
    case "mercenary":
    case "mercenaries":
    case "free mercenary":
    case "mercenary guild":
    case "free mercenaries":
        who->catch_tell("Ummmmm .... right. We'll pretend you aren't"
          + " drunk and just move on.\n");
        return 0;
        break;
    case "militia":
    case "thornlin":
    case "thornlin militia":
        txt += "the Thornlin Militia. May you aid these good folk"
          + " in holding the forces of the East at bay!";
        mtitle = "Aid to the Thornlin Militia and Determined Ward"
          + " Against the Forces of the Enemy";
        guild = "militia";
        break;
    case "minotaur":
    case "minotaurs":
    case "minotaur guild":
    case "minotaurs guild":
        txt += "the Bloodsea Minotaurs. May your skills blend with"
          + " their strength!";
        mtitle = "Sworn Ally of Minotaurs throughout the Bloodsea of"
          + " Istar";
        guild = "mino";
        break;
    case "minstrel":
    case "minstrels":
    case "minstrel guild":
        txt += "the August Order of Minstrels. May your deeds lend"
          + " greater passion to their songs in wartime and peace!";
        mtitle = "Protector of the August Order of Minstrels and"
          + " Patron of the Musical Arts";
        guild = "minstrel";
        break;
    case "monk":
    case "monks":
    case "order of the dragon": 
    case "dragon order":
        txt += "the Order of the Dragon. May your walk with them"
          + " bring harmony and balance to the Donut!";
        mtitle = "Monk Defender and Protector of Dragons";
        guild = "monk";
        break;
    case "necro":
    case "necromancer":
    case "necromancers":
    case "necro guild":
    case "necromancer guild":
        txt += "the Necromancer Guild. May your involvement in their"
          + " sepulcheral arts make the darkness that much more vile!";
        mtitle = "Reagent Supplier for the Necromancer Guild and"
          + " Contributor to Vile Darkness";
        guild = "necro";
        break;
    case "noldor":
    case "noldor guild":
    case "imladris":
    case "rivendell":
        if (who->query_race() == "goblin" ||
            who->query_race_name() == "orc")
        {
            who->catch_tell("The Elves of Imladris would never"
              + " suffer an alliance with a goblin like yourself!\n");
            return 0;
            break;
        }
        txt += "the Noldor of Imladris. May your deeds bring light"
          + " and joy to the Elves of the West!";
        mtitle = "Honor Guard to the Noldor and Shield"
          + ((gender = "Brother") ? "sman" : "-maiden")
          + " of Imladris";
        guild = "noldor";
        break;
    case "orc":
    case "orcs":
    case "orc guild":
    case "orcs guild":
        if (who->query_race() == "elf")
        {
            who->catch_tell("An elf affiliated with Orcs? What are"
              + " you smoking, and why aren't you sharing!?\n");
            return 0;
            break;
        }

        txt += "the Orcs of Middle Earth. May your blade be smeared"
          + " with the blood of of their enemies!";
        mtitle = "Elf-Hater and Ally of the Orcs of Middle Earth";
        guild = "orcs";
        break;
    case "pirate":
    case "pirates":
    case "bloodsea pirates":
    case "bloodsea pirate":
        txt += "the Pirates of the Bloodsea. May the sight of you be"
          + " as welcome to them as a full barrel 'o grog!";
        mtitle = "Pirate Ally and Fierce Supporter of Grog Swilling";
        guild = "pirates";
        break;
    case "priest":
    case "priests":
    case "cleric":
    case "clerics":
        who->catch_tell("There are many clerics in the realm. Please"
          + " be more specific.\n");
        return 0;
        break;
    case "pot":
    case "priests of takhisis":
    case "takhisis":
        txt += "the Priests of Takhisis. May your service to them be"
          + " pleasing to the Dark Queen!";
        mtitle = "Volunteer Servant to the Priests of Takhisis and"
          + " Willing Slave of the Dark Queen";
        guild = "pot";
        break;
    case "ranger":
    case "rangers":
    case "rangers of gondor":
    case "rangers of ithilien":
    case "ranger of the north":
    case "rangers of the north":
        if (who->query_race() == "goblin" ||
            who->query_race_name() == "orc")
        {
            who->catch_tell("The Rangers would sooner slit your"
              + " throat than allow a creature of the Dark Lord like"
              + " yourself within their trust! Forget it!\n");
            return 0;
            break;
        }

        txt += "the Rangers of the Westlands. May your deeds help bring"
          + " the Forces of Mordor to a halt!";
        mtitle = "Sworn Ally of the Rangers and Dedicated Defender of"
          + " the Westlands";
        guild = "rangers";
        break;
    case "redfang":
    case "red fang":
    case "red fang guild":
    case "redfang guild":
        if (who->query_race() == "human")
        {
            who->catch_tell("The Red Fang would never trust a human"
              + " like you!\n");
            return 0;
            break;
        }

        txt += "the Red Fang Guild. May you aid them in their quest"
          + " for vengeance!";
        mtitle = "Fierce Supporter of the Red Fang Guild and Follower"
          + " of the Orders of Brutakis";
        guild = "redfang";
        break;
    case "rockfriend":
    case "rockfriends":
    case "rock friend":
    case "rock friends":
        if (who->query_race() == "goblin" ||
            who->query_race_name() == "orc")
        {
            who->catch_tell("The dwarves would sooner cut off their"
              + " beards than allow one of your kind into their"
              + " trust!\n");
            return 0;
            break;
        }

        txt += "the Rockfriend Guild. May you be a blessing to your"
          + " bearded commerades!";
        mtitle = "Advocate for the Rockfriend Guild and Boon to the"
          + " Bearded";
        guild = "rockfriend";
        break;
    case "spirit circle":
    case "circle":
    case "spirit circle of psuchae":
    case "scop":
        if (who->query_guild_name_lay() == "Bloodguards of Terel")
        {
            who->catch_tell("The Spirit Circle would never accept"
              + " the help of one who favors the undead as you"
              + " have!\n");
            return 0;
            break;
        }

        if (who->query_prop(LIVE_I_UNDEAD))
        {
            who->catch_tell("The undead have no place among the"
              + " Spirit Circle!\n");
            return 0;
            break;
        }

        txt += "the Spirit Circle. May your deeds be in accordance"
          + " with the Divine will of Psuchae!";
        mtitle = "Defender of the Spirit Circle and Proponent of"
          + " Psuchae";
        guild = "scop";
        break;
    case "shieldbearer":
    case "shield bearer":
    case "shieldbearers":
    case "shield bearers":
        txt += "the Shieldbearers of Iron Delving. May you be a"
          + " boon to the needs of the Neidar Clan!";
        mtitle = "Sword-Arm to the Shieldbearers and Defender of"
          + " Iron Delving";
        guild = "sh_bearers";
        break;
    case "smith":
    case "smiths":
        txt += "the Smiths Guild. May your support increase their"
          + " productivity tenfold!";
        mtitle = "Firm Advocate for the Smiths Guild and Lover of"
          + " the Metalurgical Arts";
        guild = "smiths";
        break;
    case "templar":
    case "templars":
        txt += "the Templar of Takhisis. May the Dark Queen be pleased"
          + " with your service!";
        mtitle = capitalize(gender) + "-In-Arms to the Templar of"
          + " Takhisis and Servant of the Dark Queen";
        guild = "templar";
        break;
    case "thanar":
    case "thanar guild":
        if (who->query_race() != "human")
        {
            who->catch_tell("The Thanar would never accept one such"
              + " as you, whom they consider to be of lesser race"
              + " than they, as an ally!\n");
            return 0;
            break;
        }

        txt += "the Thanar Guild. May you help bring destruction to"
          + " the lesser races!";
        mtitle = "Sworn Ally of the Thanar Guild and Loather of the"
          + " Lesser Races";
        guild = "thanar";
        break;
    case "thief":
    case "thieves":
    case "cabal":
    case "hiddukel":
    case "cabal of hiddukel":
        who->catch_tell("If there were such an entity as you describe,"
          + " they would never accept such simple affiliation as you"
          + " could hope for as a Mercenary. You would need to"
          + " join them outright.\n");
        return 0;
        break;
    case "traveller":
    case "travellers":
    case "travellers guild":
    case "traveller guild":
        txt += "the Traveller Guild. May your wanderings with these"
          + " allies be filled with fortune!";
        mtitle = "Friend to Travellers and Wanderer of the Realm";
        guild = "traveller";
        break;
    case "trickster":
    case "tricksters":
    case "tricksters guild":
    case "trickster guild":
        who->catch_tell("Ally yourself with the Tricksters?! You'd be"
          + " better off pledging your allegiance to a giant anthill"
          + " at a picnic. They wouldn't accept you as a friend"
          + " anyway - friends make them nervous!\n");
        return 0;
    case "union":
    case "shadow union":
    case "warriors of shadow":
    case "su":
        txt += "the Shadow Union. May you aid them in their watch"
          + " over Sybarus!";
        mtitle = "Loyal Protector of the Shadow Union and Servant"
          + " of the Flame";
        guild = "union";
        break;
    case "vamp":
    case "vamps":
    case "vampire":
    case "vampires":
    case "vampire guild":
    case "vampyr":
    case "vampyrs":
    case "vampyr guild":
    case "eldest":
        txt += "the Vampyr Coven of Terel. May the Coven find your"
          + " friendship acceptable!";
        mtitle = "Fierce Defender of the Vampyr Coven of Terel and"
          + " Immortal Benefactor";
        guild = "vamps";
        break;
    case "wildelves":
    case "wild elves":
    case "wildrunners":
    case "wildrunner":
        txt += "the Wild Elves Guild. May the forest welcome your"
          + " aid!";
        mtitle = "Friend to the Wild Elves of Faerie and Protector"
          + " of the Forest Ways";
        guild = "wildelves";
        break;
    case "worshipper":
    case "worshippers":
    case "ew":
    case "elemental worshipper":
    case "elemental worshippers":
    case "elementalist":
    case "elementalists":
    case "elemental guild":
        txt += "the Elemental Worshippers. May your might mix with"
          + " their magic in the defense of Calia!";
        mtitle = "Beneficiary of the Elementals and Promoter of"
          + " Worshippers of Calia";
        guild = "worshipper";
        break;
    case "dagarim aran":
        txt += "the Dagarim Aran! May your efforts with those of like"
          + " mind thwart the foul devices of the Dark Lord!";
        mtitle = "Soldier of the Dagarim Aran";
        guild = "Dagarim Aran";
        break;
/*
    case "liwitch":
    case "liwitch domain":
        who->catch_tell("Affiliate with Liwitch? Are you insane? Don't"
          + " you know about ... but no, you couldn't know ... well,"
          + " nevermind. Affiliate as a loyalist or a separatist?\n");
        return 0;
        break;
    case "loyalist":
    case "liwitch loyalist":
    case "loyalist of liwitch":
    case "styles":
        txt += "the Lands of Liwitch and as a loyalist of the"
          + " exiled Liege! I hope you know what you are doing.";
        mtitle = "Loyalist of Liwitch and Comfort to the Exiled";
        guild = "Liwitch Loyalists";
        break;
    case "oppositionist":
    case "liwitch oppositionist":
    case "oppositionist of liwitch":
        txt += "the Lands of Liwitch and as a separatist in"
          + " opposition to the exiled Liege! We're all behind you!";
        mtitle = "Oppositionist of Liwitch and Sworn Separatist of the"
          + " Exiled Liege";
        guild = "Liwitch Oppositionists";
        break;
*/
    default:
        if (SECURITY->exist_player(arg))
        {
            /* We get here if the Merc is trying to target an
             * existing player for affiliation.
             */
            if (!check_affiliation_valid(who, arg))
            {
                return 0;
            }

            other_player = SECURITY->finger_player(arg);
            who->catch_tell(txt + "the one known as " + capitalize(arg)
              + ". May you be as a " + gender + " to "
              + other_player->query_objective() + " in all "
              + other_player->query_possessive() + " exploits!\n");
            set_info(who, "title",
                capitalize(gender) + "-In-Arms and Fierce Ally of "
              + capitalize(arg) + " and "
              + other_player->query_possessive() + " many exploits");
            other_player->remove_object();

            set_info(who, "affiliation", arg);

            write_file(LOG_DIR + "affiliations",
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(who->query_real_name()) 
              + " affiliated with " + capitalize(arg) + ".\n");

            return 1;
            break;
        }

        who->catch_tell("No such entity is known to exist!\n");
        return 0;
        break;
    }

    if (check_guild_membership(who, guild))
    {
        return 0;
    }

    if (!check_affiliation_valid(who, guild))
    {
        return 0;
    }

    who->catch_tell(txt + "\n");
    set_info(who, "title", mtitle);
    set_info(who, "affiliation", guild);

    write_file(LOG_DIR + "affiliations",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(who->query_real_name()) 
      + " affiliated with " + capitalize(guild) + ".\n");
} /* parse_affiliation */


/*
 * Function name:        check_affiliation_valid
 * Description  :        Mercs may choose a new affiliation only
 *                       once per day.
 * Arguments    :        object who - the player
 *                       string aff - the desired affiliation
 * Returns      :        int 1 - allow the affiliation
 *                       int 0 - do not allow
 */
public int
check_affiliation_valid(object who, string aff)
{
    string  today = TIME2FORMAT(time(), "mm/dd/yyyy");
    mixed   new   = get_info(who, "most_recent_aff");
    mixed   old   = get_info(who, "recent_aff");

    if (today == new && new == old)
    {
        who->catch_tell("What is this nonsense? The Free Mercenary"
          + " Guild has a reputation to maintain! They are not fickle"
          + " agents who flit between contracts on a whim! Do not be"
          + " so wishy-washy! You will need to wait until tomorrow"
          + " until choosing a new affiliation.\n");
        return 0;
    }

    set_info(who, "recent_aff", new);
    set_info(who, "most_recent_aff", today);

    return 1;
} /* check_affiliation_valid */


/*
 * Function name:        format_the_the
 * Description  :        We will often want to check the guild name
 *                       as it is defined by SECURITY->query_guilds()
 *                       and use it with a preceeding "the". The
 *                       problem is that some guild names already have
 *                       a capitalized "The" at the beginning in
 *                       the official name. If so, we change it to
 *                       lower case. If not, we add a "the".
 * Arguments    :        the short name of the guild
 * Returns      :        string - the long name of the guild formatted
 *                                with "the" the way we want it
 */
public string
format_the_the(string name)
{
    string  gname;
    string *gname_txt;

    gname = query_open_guilds()[name];

    if (!strlen(gname))
    {
        return gname;
    }

    gname_txt = explode(gname, " ");

    if (lower_case(gname_txt[0]) == "the")
    {
        gname_txt[0] = lower_case(gname_txt[0]);
        gname = implode(gname_txt, " ");
    }
    else
    {
        gname = "the " + gname;
    }

    return gname;
} /* format_the_the */


/*
 * Function name:        compute_guildstat_title
 * Description  :        determine which title the Merc should have
 *                       based on his or her guildstat
 * Arguments    :        object who - the player
 * Returns      :        int - the index point for the title array
 */
public int
compute_guildstat_title(object who)
{
    string *titles;
    int     gstat = who->query_stat(SS_OCCUP);

    switch(gstat)
    {
        case 0..4:
            return 0;  /* Newcomer */
            break;
        case 5..14:
            return 1;  /* Rookie */
            break;
        case 15..24:
            return 2;  /* Initiate */
            break;
        case 25..39:
            return 3;  /* Hireling */
            break;
        case 40..59:
            return 4;  /* Blade for Hire */
            break;
        case 60..79:
            return 5;  /* Professional */
            break;
        case 80..99:
            return 6;  /* Specialist */
            break;
        case 100..119:
            return 7;  /* Veteran */
            break;
        case 120..139:
            return 8;  /* Savant */
            break;
        case 140..159:
            return 9;  /* Soldier of Fortune */
            break;
        case 160..179:
            return 10; /* Blademaster for Hire */
            break;
        case 180..199:
            return 11; /* Battle Authority */
            break;
        default:
            return 12; /* Warlord of Fortune */
    }

    return 0; /* should never happen */
} /* query_guildstat_title */


/*
 * Function name:        compute_adapt_title
 * Description  :        determine which title the Merc should have
 *                       based on his or her adapt
 * Arguments    :        object who - the player
 * Returns      :        int - the index point for the title array
 */
public int
compute_adapt_title(object who)
{
    string *titles;
    int     adapt = who->query_skill(SS_MERC_ADAPT_SKILL);

    switch(adapt)
    {
        case 0..9:
            return 0;  /* Untalented */
            break;
        case 10..19:
            return 1;  /* Fairly Limited */
            break;
        case 20..29:
            return 2;  /* Somewhat Resourceful */
            break;
        case 30..39:
            return 3;  /* Resourceful */
            break;
        case 40..49:
            return 4;  /* Well-Rounded */
            break;
        case 50..59:
            return 5;  /* Extremely Well-Rounded */
            break;
        case 60..69:
            return 6;  /* Versatile */
            break;
        case 70..79:
            return 7;  /* Highly Versatile */
            break;
        case 80..89:
            return 8;  /* Exceptionally Versatile */
            break;
        case 90..99:
            return 9;  /* Supremely Adaptable */
            break;
        default:
            return 10; /* Limitless */
    }

    return 0; /* should never happen */
} /* query_adapt_title */