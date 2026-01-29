/*
 * Elf generator for Faerie
 * Based on the hobbitmaker in the Shire
 * -- Finwe August 2004
 */

#include "defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>

inherit "/std/monster";
inherit "/std/act/attack";
inherit MAKE_MONEY;

#define NUM_TYPES 4  /* Number of types of elfmaker elfs */
#define NPC_SUBLOC   "_elf_ears"

// Allowable types of elfs to be set with set_type when cloning
//   All other types are randomly set to female or male

// Function prototypes
//void get_soul();
nomask public void set_elf_type();
nomask public void set_elf_stats(int level);
nomask public void set_elf_skills();
string elf_chats();
string elf_cchats();
string elf_acts();
string elf_cacts();
void arm_elf();
string get_adjective();

// Global Vars
int npc_power, ran_num, npc_type;
static string *gEquipment = ({});

void create_elf() {}

nomask void
create_monster()
{
    setuid(); seteuid(getuid());
    if (!IS_CLONE)
    return;
    ran_num = 1 + random(10);
    npc_type = -1;

    set_name("elf");
    add_name("_faerie_elf");
    set_long("@@elf_long@@");
    set_title("");
    set_race_name("elf");
    get_adjective();
    set_stats(({ 50, 50, 50, 50, 50, 50 }));
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_HEIGHT,   500);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_S_WIZINFO,"This elf was made by the faerie elfmaker. See " +
        "it for more info.\nFinwe\n");

    this_object()->add_subloc(NPC_SUBLOC,this_object());

    set_chat_time(5+random(5));
    add_chat("@@elf_chats@@");
    set_act_time(5+random(5));
    add_act("@@elf_acts@@");
    set_cchat_time(7);
    add_cchat("@@elf_cchats@@");
    set_cact_time(5);
    add_cact("@@elf_acts@@");


    create_elf();
}

nomask public int
query_elf_type()
{
    return npc_type;
}

public string
get_adjective()
{
    string *adjectives, adj1, adj2;

// mental appearance
    adjectives = ({"able-bodied", "adventurous", "alert", "arrogant",
        "bold", "brave", "bright", "brilliant", "capable", "cheerful",
        "clever", "courageous", "dangerous", "deadly", "decisive",
        "dextrous", "dignified", "energetic", "fierce", "forceful",
        "formidable", "glorious", "happy", "impressive", "intelligent",
        "mighty", "nimble", "noble", "perceptive", "powerful", "profound",
        "proud", "quick", "robust", "serene", "serious", "sharp",
        "stealthy", "strong", "thoughtful", "watchful", "wise", "witty"});

    adj1 = adjectives[random(sizeof(adjectives))];

// physical appearance
    adjectives = ({"slim", "slight", "pale", "muscular", "dark-haired",
        "silver-haired", "golden-haired", "violet-eyed", "dark-eyed",
        "amber-eyed", "brown-eyed", "lustrous-haired", "white-haired"});

    adj2 = adjectives[random(sizeof(adjectives))];
    set_adj(({adj1, adj2}));
//    return adj;
}

public string
elf_long()
{
    string str;

    str = (TP->query_met(TO) ? TO->query_met_name() : "The "+TO->query_nonmet_name());

    switch(npc_type)
    {
        case -1:
            str += " isn't really a elf...  Some silly wizard seems " +
                "to have forgotten to set this elf right.\nPlease " +
                "make a bug report about this.\n";
            break;
        case YOUNG:
            str += " appears younger than most elves. " + CAP(HE_SHE(TO)) +
                " seems spry and very active, and ready to go out and explore, " +
                "and learn all " + HE_SHE(TO) + " can.\n";
            break;
        case ADULT:
            str += " looks like " + HE_SHE(TO) + " has lived for a " +
                "number of years. " + CAP(HE_SHE(TO)) + " seems to knows " +
                "much about the world.\n";
            break;
        case ELDER:
            str += " has the look of wisdom in " + HIS_HER(TO) + " eyes, " +
                "a wisdom which is only learned through age. Faint " +
                "wrinkles line " + HIS_HER(TO) + " face. Nonetheless, " +
                HE_SHE(TO) + " still appears agile enough.\n";
            break;
        case GUARD:
            str += " is one of the guards of Green Oaks. " +
                CAP(HE_SHE(TO)) + " is well armed and ready to defend " +
                HIM_HER(TO) + "self against the dangers that assault " +
                "the elves.\n";
            break;
    }
    return str;
}


public string
show_subloc(string subloc, object on, object for_who)
{
// sets elf ears
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc !=NPC_SUBLOC)
        return ::show_subloc(subloc, on, for_who);
    if (on != for_who)
    {
        return CAP(HE_SHE(TO)) + " has pointed ears.\n";
    }

    return "";
}




nomask public void
set_power(int level)
{
    if(level > 100)
    {
    level = 100;
    }

    set_elf_stats(level);
}

nomask public void
set_elf_stats(int level)
{
    int   *npc_stats,
    initial_stat,
    is;

    initial_stat = level;

    npc_stats = allocate(6);

    npc_stats[0] = initial_stat - (ran_num * 3);   // STR
    npc_stats[1] = initial_stat + (ran_num * 5);   // DEX
    npc_stats[2] = initial_stat - (ran_num * 2);   // CON
    npc_stats[3] = initial_stat - ran_num;         // INT
    npc_stats[4] = initial_stat + ran_num;         // WIS
    npc_stats[5] = initial_stat + ran_num;         // DIS

    for (is = 0; is < 6; is++)
    {
    if (npc_stats[is] < 10)
        npc_stats[is] = 10;
    }

    set_stats(npc_stats);
    set_alarm(0.5,0.0,&set_elf_skills());
}


nomask public void
set_elf_skills()
{
    int     ran_num2,
    npc_stat_avg = query_average_stat(),
    mod_skills,
    com_skill,
    spe_skill,
    gen_skill;

    ran_num2 = random(6) + 5;

//    set_alignment(250 + 2 * npc_stat_avg);
    set_alignment(0);
    set_hp(query_max_hp());   // Start off healthy

    if(npc_stat_avg > 50)
    {
    mod_skills = npc_stat_avg/3 + 100;
    }
    else
    {
    mod_skills = npc_stat_avg * 2;
    }

    com_skill = mod_skills * 50 / 100;
    spe_skill = mod_skills * 45 / 100;
    gen_skill = mod_skills * 55 / 100;

    if(spe_skill > 60)
    spe_skill = 60;
    else if(spe_skill < 5)
    spe_skill = 5;
    if (npc_type == 3) // Fighting elf like militia
    spe_skill += 15;

    if(com_skill > 60)
    com_skill = 60;
    else if(com_skill < 5)
    com_skill = 5;
    if (npc_type == 3) // Fighting elf like militia
    com_skill += 15;

    if(gen_skill > 60)
    gen_skill = 60;
    else if(gen_skill < 10)
    gen_skill = 10;

    set_skill(SS_WEP_SWORD,spe_skill + random(5));
    set_skill(SS_WEP_KNIFE,spe_skill + random(5));
    set_skill(SS_WEP_POLEARM,spe_skill + random(5));
    set_skill(SS_WEP_CLUB,spe_skill - 20);
    set_skill(SS_WEP_AXE,spe_skill - 10);
    set_skill(SS_WEP_MISSILE,spe_skill + random(10) + 10);
    set_skill(SS_PARRY,com_skill + random(5));
    set_skill(SS_DEFENCE,com_skill + random(5));
    set_skill(SS_SNEAK,gen_skill + random(5));
    set_skill(SS_HIDE,gen_skill + random(5));
    set_skill(SS_AWARENESS,gen_skill + random(5));
    set_skill(SS_HERBALISM,gen_skill + random(10));
    set_skill(SS_ACROBAT,gen_skill + random(5));

    arm_elf();
}

void
arm_elf()
{
    ADD_MONEY;

    switch(npc_type)
    {
        case GUARD:
            equip(({
                WEP_DIR + ({"e_spear", "e_lsword", "e_2lsword"})[random(3)],
                ARM_DIR + "e_robe",
                ARM_DIR + "e_chainmail"
            }));
            make_gold(1+random(3));
            return;

        case YOUNG:
            equip(WEP_DIR + ({"e_knife", "e_dagger"}) [random(2)]);
            break;
        case ADULT:
        case ELDER:
            equip(WEP_DIR + ({"e_ssword", "e_dagger"}) [random(2)]);
            break;
    }
    equip(({
        (ARM_DIR + "e_tunic"),
        (ARM_DIR + "e_robe")
    }));

}

nomask public void
set_type(int some_num)
{
    if(some_num < 0 || some_num > NUM_TYPES)
    some_num = 0;

    npc_type = some_num;

    set_elf_type();
}

nomask public void
set_elf_type()
{
    set_gender(random(2));  //  Could be male or female
    switch(npc_type)
    {
        case YOUNG:
            add_name("young");
            break;
        case ADULT:
            add_name("adult");
            break;
        case ELDER:
            add_name("elder");
            break;
        case GUARD:
            add_name("guard");
            break;
    }
/*
    if (!query_gender())
    set_name(get_male_name());
    else
    set_name(get_female_name());
*/
//    set_adj(({get_adjective(),get_adjective()}));
}

string
elf_chats()
{
    if (query_attack())
    return elf_cchats();

    switch(npc_type)
    {
        case -1:
            return "I'm buggy, please make a bug report about CHATS.";
        case YOUNG:
            switch (random(5))
            {
                case 0:
                    return "I have learned a lot from my teachers.";
                case 1:
                    return "Someday soon I'll be an adult.";
                case 2:
                    return "One day I plan on going adventuring.";
                case 3:
                    return "I have heard many exciting things from " +
                        "the outside.";
                case 4:
                    return "There is so much to learn.";
            }
            break;
        case ADULT:
            switch (random(5))
            {
                case 0:
                    return "Life has many experiences to learn from.";
                case 1:
                    return "There are many adventures I can't wait to have.";
                case 2:
                    return "I finally have the respect of the Elders.";
                case 3:
                    return "Next week I get to go on an exploration " +
                        "with the guards.";
                case 4:
                    return "Those adolescent elves are so childish.";
            }
            break;

        case ELDER:
            switch (random(5))
            {
                case 0:
                    return "Things have changed greatly since I awoke.";
                case 1:
                    return "I could teach you many things.";
                case 2:
                    return "I am regarded with great reverence.";
                case 3:
                    return "My travels now do not take me far from here.";
                case 4:
                    return "You should learn much as you can in your life.";
            }
            break;
        case GUARD:
            switch (random(5))
            {
                case 0:
                    return "Beware of bandits. They have been causing trouble.";
                case 1:
                    return "I have beaten many enemies.";
                case 2:
                    return "Those orcs have been nothing but trouble.";
                case 3:
                    return "Don't be causing any mischief around here.";
                case 4:
                    return "Next week I go out on patrol again.";

            }
            break;
    }
    return "Hurry up and make some chats for me you lazy wizard!";
}

string
elf_acts()
{
    if (query_attack())
    return elf_cacts();

    switch(npc_type)
    {
        case -1:
            return "I'm buggy, please make a bug report about my ACTS.";
        case YOUNG:
            switch (random(5))
            {
                    return "smile merrily";
                case 1:
                    return "laugh happily";
                case 2:
                    return "blush";
                case 3:
                    return "giggle";
                case 4:
                    return "smile happily";
            }
            break;
        case ADULT:
            switch (random(5))
            {
                case 0:
                    return "smile proudly";
                case 1:
                    return "emote observes you carefully.";
                case 2:
                    return "emote listens to something nearby.";
                case 3:
                    return "emote pauses and gets a far away look in " +
                    HIS_HER(TO) + " eyes.";
                case 4:
                    return "emote looks around.";
            }
            break;
        case ELDER:
            switch (random(5))
            {
                case 0:
                    return "emote smiles wisely.";
                case 1:
                    return "emote begins to talk of a long ago adventure.";
                case 2:
                    return "emote drums " + HIS_HER(TO) + " fingers quietly.";
                case 3:
                    return "emote watches you carefully.";
                case 4:
                    return "laugh happily";
            }
            break;
        case GUARD:
            switch (random(5))
            {
                case 0:
                    return "emote examines you carefully.";
                case 1:
                    return "emote sharpens " + HIS_HER(TO) + " weapon.";
                case 2:
                    return "emote looks off into the distance.";
                case 3:
                    return "flex";
                case 4:
                    return "emote looks around warily.";

            }
            break;
    }
    return "emote tells you to make "+HIM_HER(TO)+" some acts.";
}


string
elf_cchats()
{
    if (!query_attack())
    return elf_chats();

    switch(npc_type)
    {
        case YOUNG:
            switch(random(6))
            {
                case 0:
                    return "Leave me alone you bully!";
                case 1:
                    return "Help!! Help!! I'm being repressed!";
                case 2:
                    return "Leave me alone, you wretched creature. I " +
                        "have done nothing to you!";
                case 3:
                    return "What have I done to you to deserve this?";
                case 4:
                    return "You aren't fighting fairly!";
                case 5:
                    return "This isn't a fair fight!";
            }
            break;
        case ADULT:
        case ELDER:
            switch(random(6))
            {
                case 0:
                    return "Begone, foul creature!";
                case 1:
                    return "Guards! Guards! We're under attack!!!";
                case 2:
                    return "You will regret this fight!";
                case 3:
                    return "Stop this at once!!";
                case 4:
                    return "Just wait until the guards come!";
                case 5:
                    return "I shall kill you quickly!";
            }
            break;
        case GUARD:
            switch(random(5))
            {
                case 0:
                    return "You are under arrest, foul " +
                        query_attack()->query_race_name() +
                        "! Please come quietly!";
                case 1:
                    return "You will answer for your crimes!";
                case 2:
                    return "Lay down your "+(!sizeof(query_attack()->query_weapon(-1))
                        ? ("arms") : (query_attack()->query_weapon(-1)[0]->short())) +
                        " and come quietly!";
                case 3:
                    return "You will pay for this senseless act!";
                case 4:
                    return "Stop this at once, or I shall have to take " +
                        "stronger actions against you!";
            }
            break;
    }
    return "Hurry up and make some combat chats for me!";
}

string
elf_cacts()
{

    if (!query_attack())
    return elf_acts();

    switch(npc_type)
    {
        case -1:
            return "is buggy.";
        case YOUNG:
            switch(random(6))
            {
                case 0:
                    return "sob";
                case 1:
                    return "cry";
                case 2:
                    return "whine";
                case 3:
                    return "scream";
                case 4:
                    return "slap "+query_attack()->query_real_name();
                case 5:
                    return "emote tries to run away.";
            }
            break;
        case ADULT:
            switch(random(4))
            {
                case 0:
                    return "emote tries to disarm you.";
                case 1:
                    return "sigh";
                case 2:
                    return "shout Call the guards! This evil " +
                    query_attack()->query_nonmet_name() + " is attacking me!!";
                case 3:
                    return "emote charges you with renewed strength.";
            }
            break;
        case ELDER:
            switch(random(4))
            {
                case 0:
                    return "shout Help!! Help!! This no good " +
                        query_attack()->query_nonmet_name() +
                        " is trying to kill me!!";
                case 1:
                    return "emote screams in horror!";
                case 2:
                    return "emote begs to be spared.";
                case 3:
                    return "emote pleads for " + HIS_HER(TO) + " life.";
            }
            break;
        case GUARD:
            switch(random(6))
            {
                case 0:
                    return "shout Stop this senseless killing at once!";
                case 1:
                    return "shout Guards, over here!!  This " +
                    query_attack()->query_race_name() + " is fighting me!";
                case 2:
                    return (!sizeof(query_weapon(-1)) ? ("grumble") :"emote tightens "+
                        HIS_HER(TO) + " grip on "+HIS_HER(TO) + " " +
                        query_weapon(-1)[0]->short()+".");
                case 3:
                    return "emote calls for help.";
                case 4:
                    return "emote attacks with renewed vigour.";
                case 5:
                    return "shout You will pay for your crimes " +
                        query_attack()->query_nonmet_name() + "!";

            }
            break;
        }
    return "emote asks you to make some combat acts for "+HIM_HER(TO)+".";
}


int
special_attack(object enemy)
{
    int     npc_dex =  query_stat(SS_DEX)/4;
    int     npc_miss = query_skill(SS_WEP_MISSILE)/4;
    int     npc_str =  query_skill(SS_STR)/3;
    mixed   *hitresult;
    string  *how = allocate(2), wep;

    if (npc_type == YOUNG || npc_type == -1)
    return 0;
    if (npc_type != GUARD) // Milita attack differently
    {
    if (random(8))
        return 0;

    hitresult = enemy->hit_me(F_PENMOD(npc_dex+npc_miss, query_skill(SS_WEP_MISSILE)),
      W_BLUDGEON, TO, -1);

    switch (hitresult[0])
    {
        case -1:
            how[0] = "The arrow whistles past you harmlessly.";
            how[1] = "The arrow whistles past "+QTNAME(enemy) + "harmlessly.";
            break;
        case 0:
            how[0] = "The arrow bounces off causing no damage.";
            how[1] = "The arrow bounces off " + QTNAME(enemy) +
                " without causing any damage.";
            break;
        case 1..10:
            how[0] = "The arrow glances off you, leaving a trail of blood.";
            how[1] = "The arrow glances off " + QTNAME(enemy) +
                ", leaving a trail of blood.";
            break;
        case 11..20:
            how[0] = "The arrow lodges in you, causing a nasty wound";
            how[1] = "The arrow lodges in " + QTNAME(enemy) +
                ", causing a nasty wound.";
            break;
        case 21..35:
            how[0] = "The arrow sinks deep into you, and you begin to bleed.";
            how[1] = "The arrow sinks into " + QTNAME(enemy) + " and "
                + HE_SHE(enemy) + " begins to bleed.";
            break;
        default:
            how[0] = "The arrow is driven into you. The wound begins to " +
                "bleed profusely!";
            how[1] = "The arrow is driven into " + QTNAME(enemy) +
                ", who begins to bleed profusely!";
            break;
    }

    // Send no messages to the npc
    if (enemy->query_hp() <= 0)
    {
        enemy->catch_msg("Someone forcefully shoots an arrow at you, " +
            "hitting you so hard you fall backwards in utter shock as " +
            "the blood pours from the wound.\n");
        TO->tell_watcher("Someone forcefully shoots an arrow at " +
            QTNAME(enemy) + ", knocking " + HIM_HER(enemy) +
            " backwards. The force is so strong that blood pours from " +
            "the wound, leaving a look of utter shock on " +
            HIS_HER(enemy) + " face.\n",enemy);
        enemy->do_die(TO);
        return 1;
    }
    if (enemy->query_wiz_level())
        enemy->catch_msg(hitresult[3] + " damage was done.\n");

    enemy->catch_msg("Someone shoots an arrow at your "+hitresult[1]+
      "!\n" + how[0] + "\n");
    TO->tell_watcher("Someone shoots an arrow at "+QTNAME(enemy)+"'s "+
      hitresult[1] + "!\n" + how[1] + "\n",enemy);

    if (hitresult[1] == "head")
        enemy->add_attack_delay(5 + random(6) , 1);
    return 1;
    }
    if (random(5))
        return 0;

    if (!sizeof(query_weapon(-1)))
        return 0;

    wep = query_weapon(-1)[0]->short();

    hitresult = enemy->hit_me(F_PENMOD(npc_dex + npc_str +
    query_weapon(-1)[0]->query_pen(), 65), W_IMPALE, TO, -1);

    switch (hitresult[0])
    {
        case -1:
            how[0] = QCTNAME(TO)+"'s "+wep+" missed you completely.";
            how[1] = QCTNAME(TO)+"'s "+wep+" misses "+QTNAME(enemy)+" completely.";
            break;
        case 0:
            how[0] = QCTNAME(TO)+" swings "+HIS_HER(TO)+" "+wep+" dangerously "+
                "close to your "+hitresult[1]+".";
            how[1] = QCTNAME(TO)+" swings "+HIS_HER(TO)+" "+wep+" dangerously "+
                " close to "+QTNAME(enemy)+"'s "+hitresult[1]+".\n" ;
            break;
        case 1..10:
            how[0] = QCTNAME(TO)+"'s "+wep+" barely scratches your "+
                hitresult[1]+".";
            how[1] = QCTNAME(TO)+"'s "+wep+" barely scratches "+QTNAME(enemy)+
                "'s "+hitresult[1]+".";
            break;
        case 11..20:
            how[0] = QCTNAME(TO)+"'s "+wep+" barely pierces your "+hitresult[1]+".";
            how[1] = QCTNAME(TO)+"'s "+wep+" barely pierces "+QTNAME(enemy)+"'s "+
                hitresult[1]+".";
            break;
        case 21..35:
            how[0] = QCTNAME(TO)+" pierces your "+hitresult[1]+" deeply with "+
                HIS_HER(TO)+" "+wep+".";
            how[1] = QCTNAME(TO)+" pierces "+QTNAME(enemy)+"'s "+hitresult[1]+
                " deeply with "+HIS_HER(TO)+" "+wep+".";
            break;
        default:
            how[0] = QCTNAME(TO)+" rips open a bleeding wound in your "+
                hitresult[1]+" with "+HIS_HER(TO)+" "+wep+".";
            how[1] = QCTNAME(TO)+" rips open a bleeding wound in "+QTNAME(enemy)+
                "'s "+hitresult[1]+" with "+HIS_HER(TO)+" "+wep+".";
            break;
        }

    // Send no messages to the npc
    if (enemy->query_hp() <= 0)
    {
        enemy->catch_msg(QCTNAME(TO)+ " lunges at you with "+HIS_HER(TO)+
            " "+wep+" leaving you mortally wounded.\n");
        TO->tell_watcher(QCTNAME(TO)+ " lunges towards "+QTNAME(enemy)+" "+
            "with "+HIS_HER(TO)+" "+wep+", mortally wounding "+QTNAME(enemy)+"!\n",
            enemy);
        enemy->do_die(TO);
        return 1;
    }

    if (enemy->query_wiz_level())
        enemy->catch_msg(hitresult[3] + " damage was done.\n");

    enemy->catch_msg(QCTNAME(TO)+" lunges at your "+hitresult[1]+
        " with "+HIS_HER(TO)+" "+wep+"!\n" + how[0] + "\n");
    TO->tell_watcher(QCTNAME(TO)+" lunges towards "+QTNAME(enemy)+"'s "+
        hitresult[1] + " with "+HIS_HER(TO)+" "+wep+"!\n" + how[1] + "\n",enemy);
    return 1;
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

//    command("introduce me to " + TP->query_real_name() + "");
    command("say to " + TP->query_real_name() + " Greetings, and well met");
    command("nod " + TP->query_real_name() );
}
