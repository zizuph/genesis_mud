/*
 *  /d/Genesis/imbuement/npc/enchanter.c
 *
 *  This is Karkadelt the Enchanter. He is two important things:
 *
 *    - The main quest npc for the Orc Temple quests in Sparkle.
 *    - The interface for players who wish to learn about and participate
 *      in the imbuement system.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/npc/sparkle_npc";
inherit "/d/Genesis/lib/intro";
inherit "/d/Sparkle/lib/quest_reward";

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"


/* Definitions */
#define            ENCHANTER_DIARY_CHECK "_imbue_diary_check"
#define            ALREADY_SEEN          "_imbue_already_seen"
#define            NULLSTONE_ADVICE      "_imbue_nullstone_advice"
#define            ID_CONFIRMATION       "_imbue_confirmed_id_payment"
#define            IMBUE_CONFIRMATION    "_imbue_confirmed_imbue_payment"
#define            STONE_CONFIRMATION    "_imbue confirmed_nullstone"
#define            AMULET_CONFIRMATION   "_imbue_confirmed_amulet"
#define            DIS_CONFIRMATION      "_imbue_confirmed_disenchant"
#define            TRANS_CONFIRMATION    "_imbue_confirmed_transmogrify"
#define            DISENCHANT_VETERAN    "_imbue_veteran_disenchanting"
#define            TRANS_VETERAN         "_imbue_veteran_transmogrifying"
#define            DATA_OBJ    ("/d/Sparkle/area/city/obj/vendor_master")

#define            IMBUE_COST          1000
#define            STONE_COST          25
#define            LAPIDARIUM_COST     10
#define            IDENTIFY_COST       100
#define            DISENCHANT_REWARD   5
#define            IMBUE_FILE(n)       (extract((n), 0, 0) + "/" + (n))
#define            DIARY_NUM_FILE      "enchanter_diary"



/* Global Variables */
public int         Busy = 0;
public mapping     Imbuements;
public string     *Indoor_Acts = ({
                       "emote runs his finger down an ancient scroll"
                     + " silently scanning what is written upon it.",
                       "emote appears to be looking right through you,"
                     + " as if totally absorbed in his own thoughts.",
                       "emote pulls a brightly coloured stone from"
                     + " the confines of his robe, and compares it to"
                     + " something written on a chart on the wall.",
                       "emote narrows his eyes, and a flash of pain"
                     + " crosses his features only to be replaced an"
                     + " instant later by the former look of focused"
                     + " concentration.",
                       "emote crosses the room and begins working on"
                     + " something you are unable to see.",
                       "emote pauses, considering something, and then"
                     + " nods silently to himself.", });
public mapping      Create_Stone = ([
                        "bane_dragon"        : "heavenstone",
                        "bane_dwarf"         : "gallstone",
                        "bane_elf"           : "charstone",
                        "bane_gnome"         : "gearstone",
                        "bane_goblin"        : "darkstone",
                        "bane_hobbit"        : "piestone",
                        "bane_human"         : "fellstone",
                        "bane_minotaur"      : "hoofstone",
                        "bane_ogre"          : "doomstone",
                        "bane_troll"         : "firestone",
                        "bane_undead"        : "lifestone",
                        "damage_acid"        : "ruststone",
                        "damage_air"         : "blowstone",
                        "damage_cold"        : "snapstone",
                        "damage_death"       : "blackstone",
                        "damage_earth"       : "sinkstone",
                        "damage_electricity" : "ampstone",
                        "damage_fire"        : "orangestone",
                        "damage_water"       : "bluestone", 
                        "effect_darkness"    : "nightstone",
                        "effect_darkvision"  : "torchstone",
                        "effect_haste"       : "mercurystone",
                        "effect_healing"     : "balmstone",
                        "effect_light"       : "morningstone",
                        "effect_poison"      : "aspstone",
                        "effect_slow"        : "grogstone",
                        "effect_unbreakable" : "ironstone",
                        "extra_ac"           : "wardstone",
                        "extra_hit"          : "guidestone",
                        "extra_pen"          : "stingstone",
                        "resist_acid"        : "salvestone",
                        "resist_air"         : "tarpstone",
                        "resist_cold"        : "woolstone",
                        "resist_death"       : "larsstone",
                        "resist_earth"       : "riverstone",
                        "resist_electricity" : "rubberstone", 
                        "resist_fire"        : "powderstone",
                        "resist_life"        : "mummystone",
                        "resist_magic"       : "quietstone",
                        "resist_poison"      : "sweatstone",
                        "resist_water"       : "duckstone", 
                        "skill_2handed"      : "twinstone",
                        "skill_air"          : "guststone",
                        "skill_awareness"    : "eyestone",
                        "skill_axe"          : "cleavestone",
                        "skill_blindcombat"  : "molestone",
                        "skill_club"         : "crushstone",
                        "skill_death"        : "corpsestone",
                        "skill_defence"      : "shieldstone",
                        "skill_earth"        : "soilstone",
                        "skill_fire"         : "emberstone",
                        "skill_knife"        : "needlestone",
                        "skill_life"         : "ankhstone",
                        "skill_parry"        : "deftstone",
                        "skill_polearm"      : "skewerstone",
                        "skill_sneakhide"    : "rodentstone",
                        "skill_spellcraft"   : "lodestone",
                        "skill_sword"        : "edgestone",
                        "skill_unarmed"      : "palmstone",
                        "skill_water"        : "surfstone",
                        "stat_con"           : "dwarfstone",
                        "stat_dex"           : "hobbitstone",
                        "stat_dis"           : "steelstone",
                        "stat_int"           : "gnomestone",
                        "stat_str"           : "ogrestone",
                        "stat_wis"           : "elfstone",
                          ]);

/* Prototypes */
public void        create_sparkle_npc();
public void        add_sparkle_asks();
public void        ask_crafting();
public void        introduce(object who);
public void        react_intro(object tp);
public string      default_answer();
public void        run_away();
public void        arm_me();
public void        alert_hour_change_hook(int hour);
public void        show_hook(object ob);
public void        react_items(object obj, object to);
public void        init_living();
public int         do_report(string arg);
public int         id_imbuements(string arg);
public int         complete_payment(object who, int needed, string reason);
public void        intro_check(object who);
public int         do_buy(string arg);
public int         enchanter_work(string arg);
public int         enchanter_imbue(string arg);
public int         week_elapsed(object who);
public string      get_weekday(string day);
public void        return_imbued_item(object ob, object temp_location, object who);
public void        react_stones(object stone);
public void        action_answers(string arg);
public void        diary_check(object who, object obj, string why);


/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sparkle_npc()
{
    set_living_name("karkadelt");
    set_name("karkadelt");
    add_name( ({ "enchanter", "_imbuement_enchanter_npc" }) );
    set_race_name("half-elf");
    add_adj( ({ "dressed", "ornately", }) );

    set_title("the Enchanter, Master of the Arcane");

    set_short("ornately dressed enchanter");
    set_long("Robes of magenta with many rings of rare stones stitched"
      + " around a tight-fitting cowl adorn this imposing individual."
      + " His every movement is quiet, and yet utterly decisive, with"
      + " a poise and dignity that might suggest noble upbringing. Though"
      + " unmistakably elven, the features of his sharply-lined face are"
      + " clearly mixed with something other, as a darker and harder"
      + " bloodline also struggles to make itself known.\n"
      + "---------------------------------------------------------"
      + "------------\n"
      + "You sense that you could <ask> him about tasks he may need"
      + " help with.\n"
      + "---------------------------------------------------------"
      + "------------\n");

    set_stats( ({ 130, 190, 90, 300, 500, 500 }) ); /* He is impressive. */
    set_alignment(0); /* He serves his own loyalties, and none other. */

    set_default_answer(VBFC_ME("default_answer"));

    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(OBJ_M_NO_ATTACK, "Just as you begin to make your move,"
      + " the enchanter touches one of the brightly coloured stones"
      + " on his robes, and a shockwave jolts your body. After a moment"
      + " of painful tingling, you find that your violent impulse has"
      + " been replaced by a respect for this person's power.\n");

    set_skill(SS_UNARM_COMBAT, 20);      /* Just a bit here ... */
    set_skill(SS_ALCHEMY, 100);          /* A grandmaster.      */
    set_skill(SS_AWARENESS, 100);        /* He sees much.       */
    set_skill(SS_SPELLCRAFT, 100);       /* Master of magic.    */
    set_skill(SS_FORM_ENCHANTMENT, 100); /* THE grandmaster.    */
    set_skill(SS_FORM_DIVINATION, 100);  /* Utterly proficient  */
    set_skill(SS_APPR_OBJ, 100);         /* He sees deeply.     */

    add_ask( ({ "task", "tasks", "help", "help with tasks",
                "task help", "helping", "helping with tasks",
                "tasks you may need help with",
                "tasks he may need help with" }),
        "say Your help is indeed needed. The events at the orc"
      + " temple are of dreadful importance. Thus, there are quests"
      + " you could undertake to assist me. Also, there is an"
      + " ongoing need to deal with any imbued items you may find in"
      + " your journeys. Please <ask> me either about quests,"
      + " or about imbuements.", 1);
    add_ask( ({ "conduction", "disintegration" }),
        "say It is a practice far too advanced for me to describe. I am afraid"
      + " can teach you nothing about that.", 1);
    add_ask( ({ "imbued items", "items", "imbuement",
                "imbuements" }),
        "say Please read the poster, for it will tell you much of what"
      + " I offer here. If you are interested in the crafting your"
      + " own imbuements, you may ask me about the art of enchantment.", 1);
    add_ask( ({ "poster" }), "point poster", 1);
    add_ask( ({ "enchantment", "art", "art of enchantment",
                "enchanting", "craft", "crafting", }),
        "@@ask_crafting@@");
    add_ask( ({ "spirit", "spirits", "trapped spirit", "trapped spirits",
                "victim", "innocent victim", "victims",
                "innocent victims" }),
        "say The fact that spirits of living beings are being used in"
      + " this way is unacceptable. We must put a stop to it.", 1);
    add_ask( ({ "codex", "book", "leatherbound codex",
                "leatherbound book" }),
        "say The codex contains much of what I can share about the art of"
      + " enchantment. Study it, and you too may become proficient in"
      + " the basics of the art.", 1);
    add_ask( ({ "orc dungeon", "orc dungeons", "orc temple",
                "temple", "dungeon", "dungeons" }),
        "say To find the dungeons, you must travel west from Sparkle"
      + " until you reach the orc woods. Proceed west through the woods"
      + " until you see the orc fortress on your magic map. Enter the"
      + " fortress and you will find a stairway down to the dungeons just"
      + " north of the temple.", 1);
    add_ask( ({ "orc wood", "orc woods", "woods" }),
        "say The orc woods are just west of the city.", 1);
    add_ask( ({ "magic map", "map" }),
        "say If you have lost your magic map, you can get a new one by"
      + " walking past the church.", 1);
    add_ask( ({ "church", "first church of sparkle", "sparkle church",
                "church of sparkle" }),
        "say The First Church of Sparkle is south and east of here down"
      + " Center Street.", 1);
    add_ask( ({ "orc", "orcs" }),
        "say I am not an enemy of the orcs, for I share a kinship with"
      + " them through my father. Even so, I will not sit by and allow"
      + " these particular orcs to continue their practices.", 1);
    add_ask( ({ "father", "dad", "your father" }),
        "say Yes. Though orc blood flows through my veins, I prefer to"
      + " identify with elf kind.", 1);
    add_ask( ({ "elf", "elf kind", "half-elf", "half-elven" }),
        "say I am half-elven through my mother. She was an elf maiden"
      + " of some nobility, and I was raised by her near Faerie.", 1);
    add_ask( ({ "faerie", "home", "homeland" }),
        "say I have always considered Faerie my homeland.", 1);
    add_ask( ({ "quest", "quests" }),
        "@@ask_quest@@");
    add_ask( ({ "brother", "your brother", "kerchak" }),
        "say I do not consider him a brother, but a misguided fool.", 1);
    add_ask( ({ "fool", "misguided fool" }),
        "say I do not wish to speak more about it!", 1);
    add_ask( ({ "priest", "high priest", "high-priest" }),
        "say He must be stopped. He places the entire realm in peril!", 1);
    add_ask( ({ "demon", "arch demon", "yogsathoth", "yog-sathoth",
                "yog sathoth" }),
        "say Yog-Sothoth - Devourer of Souls! That such a being has"
      + " been summoned to our plane is unforgivable.", 1);
    add_ask( ({ "dagger", "nullstone dagger" }),
        "say A nullstone dagger is forged from a special material that is"
      + " known only to a very few.", 1);
    add_ask( ({ "reward" }),
        "@@ask_reward@@");
    add_ask( ({ "flute", "bone flute" }),
        "say A bone flute is a very difficult artifact to make. Only"
      + " one who is skilled in the arts of enchantment could manage"
      + " it.", 1);
    add_ask( ({ "ghost", "ghosts" }),
        "say The ghosts that haunt the dungeon beneath the orc temple"
      + " are none other than the victims that have been fed to"
      + " Yog-Sothoth. Their tortured souls will hopefully one day"
      + " find rest.", 1);
    add_ask( ({ "soul", "souls" }),
        "say When Yog-Sothoth's incarnation was nearly destroyed, every"
      + " soul fragment that remained in his belly from the thousands"
      + " of victims he has devoured was expelled into the ether to"
      + " eventually find rest in a host object. This is the reason"
      + " the imbuements continue to appear throughout the realms.", 1);
    add_ask( ({ "yog sothoth", "yog-sothoth" }),
        "say I am not adept with the lore of demon-kind, but I have seen"
      + " enough to know that this is one of the Greater Demons from"
      + " some nether plane. It's incarnation brings us all to the"
      + " brink of disaster.", 1);
    add_ask( ({ "amulet", "amulets", "amulet of diminution",
                "amulets of dimunution", "diminution amulets" }),
        "say I have prepared amulets of diminution for those who would"
      + " assist me. Young adventurers may not need them, but any who"
      + " are more advanced in their travels will find the horror in"
      + " the dungeon attacking them with maddening visions the moment"
      + " they set foot within those halls. By wearing the amulet,"
      + " more advanced players will find their powers reduced to"
      + " very low levels, thus avoiding the notice of the demon. If"
      + " you have need of one you may <buy> one here in my shop.", 1);
    add_ask( ({ "stair", "stairway", "stairs", "forge", "staircase",
                "stair case", "basement" }),
        "say I only allow those who have helped me with the dreadful"
      + " problems in the orc temple to access my forge. If you would"
      + " know more, you can <ask> me about quests.", 1);
    add_ask( ({ "imbue", "imbuement" }), &action_answers("imbue"));
    add_ask( ({ "transmogrify" }), &action_answers("transmogrify"));
    add_ask( ({ "identify" }), &action_answers("identify"));
    add_ask( ({ "disenchant" }), &action_answers("disenchant"));
    add_ask( ({ "your sister", "sister", "silvette" }),
        "say My sister was the bravest person I have ever known. I do"
      + " not wish to speak of her.", 1);
    add_ask( ({ "shalewood", "village" }),
        "say My village, the village of Shalewood, is nearly five days"
      + " march to the southwest of here. I do not know what has become"
      + " of it.", 1);
    add_ask( ({ "harstaff" }),
        "say Harstaff is a man for whom I have great respect. I very much"
      + " hope he is well.", 1);
    add_ask( ({ "bertram", "old bertram" }),
        "say Bertram was a good man. He is an excellent example of the"
      + " sort of person my brother has destroyed.", 1);
    add_ask( ({ "mother", "your mother" }),
        "say My mother was an elf of noble lineage. I am proud to have been"
      + " her son.", 1);
    add_ask( ({ "journal", "tome", "priest journal", "priest tome",
                "priests journal", "priests tome",
                "priest's journal", "priest's tome" }),
        "say The High Priest has recorded many things in his journal, which"
      + " he keeps in his personal chambers on the third level of the"
      + " dungeons.", 1);
    add_ask( ({ "diary", "your diary" }),
        "say My diary is private. I would never discuss it with you, even"
      + " if you had somehow found and read it.", 1);


    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());
} /* create_sparkle_npc */   



/*
 * Function name:       add_sparkle_asks
 * Description  :       Redefine this so he doesn't jabber the same way
 *                      the standard Sparkle npc might.
 */
public void
add_sparkle_asks()
{
    add_ask( ({ "city", "sparkle", "city of sparkle", "town",
            "village", "area" }),
        "say I have come to this city out of necessity.", 1);
    add_ask( ({ "job", "occupation", "work", "career" }),
        "say I do not consider my work here to be that of a career or"
      + " job, but that of a necessity for the good of the realm.", 1);
    add_ask( ( Swear_Words ),
        "say Most unimpressive.", 1);
        
} /* add_sparkle_asks */


/*
 * Function name:        ask_crafting
 * Description  :        State-dependant reaction to questions about
 *                       crafting
 * Returns      :        string
 */
public void
ask_crafting()
{
    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_GHOST_GROUP,
            ORCTEMPLE_GHOST_BIT))
    {
        command("say Your mind is not yet ready for the subtleties of"
          + " enchantment. Only by experiencing firsthand the touch of"
          + " the trapped spirits can you begin this study. Ask me about"
          + " the orc temple to discover more.");
        return;
    }

    command("say Your mind has touched the minds of the torn spirits"
      + " that lie at the heart of the imbuement process. You are"
      + " thererfore ready to begin your own journey in the ways of"
      + " the enchanter.");
    command("say The beginnings of the art form can be studied within"
      + " the pages of the codex I have prepared in my enchanter's"
      + " forge.");
    command("say Once you feel prepared, you are welcome to use the"
      + " forge, which is located down the spiral staircase.");
    command("emote gestures to the staircase with a welcoming smile.");


    return;
} /* ask_crafting */


/*
 * Function name:        ask_quest
 * Description  :        State-dependant reaction to questions about
 *                       the quests he gives
 * Returns      :        string
 */
public void
ask_quest()
{
    object  obj;

    intro_check(this_player());

    write("\n\n"); /* Easier to see what is happening for the player */

    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_WEAPON_GROUP,
            ORCTEMPLE_WEAPON_BIT))
    {
        command("say West of town, you will find the Orc Road. As you"
          + " follow it west, you will eventually see an orc fortress on"
          + " your magic map.");
        write("\n"); /* for player readability */
        command("say Terrible things are happening in the dungeons"
          + " beneath the temple within that fortress. The High Priest of"
          + " the orcs is involved in matters beyond his control, and the"
          + " entire realm is paying the price.");
        write("\n"); /* for player readability */
        command("say I require ongoing help to know of his activities."
          + " The first thing I would ask you to do is to locate the"
          + " weapon storage chamber on the first level of the dungeon."
          + " Here, again, I suggest you employ the magic map, for it"
          + " will prove invaluable within the dungeons.");
        write("\n"); /* for player readability */
        command("say If the High Priest is continuing his terrible plan,"
          + " you are likely to find a nullstone dagger within that"
          + " room. Please <show> me a nullstone dagger, if you can find"
          + " it. I warn you though, you will need to kill any orcs"
          + " who guard it.");
        write("\n"); /* for player readability */
        command("say One final thing - the dreadful power that"
          + " inhabits the dungeons will suffer no threat from"
          + " outsiders it considers dangerous. If you find you cannot"
          + " enter the dungeons, you may need to return here and"
          + " purchase one of my amulets of diminution. They will"
          + " make it possible for you to enter.");
        write("\n"); /* for player readability */
        if (this_player()->query_prop(ORC_TEMPLE_QUEST_PROP) != "weapon")
        {
            write_file(LOG_DIR + "quest_begin", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_name())
              + " began the Orc Temple weapon quest.\n");
        }

        this_player()->add_prop(ORC_TEMPLE_QUEST_PROP, "weapon");
        return;
    }

    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_JOURNAL_GROUP,
            ORCTEMPLE_JOURNAL_BIT))
    {
        command("say It is clear to me that the High Priest of the orcs"
          + " continues to endanger us all.");
        write("\n"); /* for player readability */
        command("say I must know of his latest discoveries and intentions"
          + " and need you to help. In his personal chambers, he keeps"
          + " a journal. I need to know what has been written there"
          + " lately.");
        write("\n"); /* for player readability */
        command("say Read the latest entries in his journal, and return"
          + " to me with a <report> of your discoveries. Beware, however,"
          + " for the High Priest resides on the third level of the"
          + " dungeon, and you will not get that far without a fight!");
        write("\n"); /* for player readability */

        if (this_player()->query_prop(ORC_TEMPLE_QUEST_PROP) != "journal")
        {
            write_file(LOG_DIR + "quest_begin", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_name())
              + " began the Orc Temple journal quest.\n");
        }

        this_player()->add_prop(ORC_TEMPLE_QUEST_PROP, "journal");
        return;
    }

    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_FLUTE_GROUP,
            ORCTEMPLE_FLUTE_BIT))
    {
        command("say You have learned much not only about the dreadful"
          + " plans of the High Priest, but also a great deal about"
          + " me as well. I assure you that though the High Priest is"
          + " indeed my brother, I have no love for him. His soul is"
          + " forfeit, as I am sure he will eventually discover.");
        write("\n"); /* for player readability */
        command("say Nonetheless, he has become terribly powerful. In"
          + " fact, I believe he has sealed a pact with the arch demon,"
          + " such that should he be killed, he will be reincarnated"
          + " by Yog-Sothoth so that he be continuously at work to"
          + " feed more and more souls to his Master.");
        write("\n"); /* for player readability */
        command("say But kill him you must. For as you have discovered,"
          + " the bone flute around his neck is the tool we will need"
          + " to undo some of the evil he has done as we are able.");
        write("\n"); /* for player readability */
        command("say Kill the High Priest, take the bone flute from"
          + " the dungeon, and <show> it to me. I will then decide what"
          + " our next steps should be.");
        write("\n"); /* for player readability */

        if (this_player()->query_prop(ORC_TEMPLE_QUEST_PROP) != "flute")
        {
            write_file(LOG_DIR + "quest_begin", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_name())
              + " began the Orc Temple flute quest.\n");
        }

        this_player()->add_prop(ORC_TEMPLE_QUEST_PROP, "flute");
        return;
    }

    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_GHOST_GROUP,
            ORCTEMPLE_GHOST_BIT))
    {
        command("say Excellent. We must now make sure that my fool of"
          + " a brother has not made progress beyond what is detailed"
          + " in his journal, and in so doing release a few poor torn"
          + " souls from their misery.");
        write("\n"); /* for player readability */
        command("say On the second level of the dungeons are the many"
          + " cells where the orcs are holding their prisoners. It is"
          + " in these cells that the fragmented souls of some of the"
          + " prisoners who have been driven mad and died remain to"
          + " haunt the temple as ghosts. You will need to get the keys"
          + " from the jailer, who is a fearsome brute, I warn you!");
        write("\n"); /* for player readability */
        command("say In each cell, <play> the bone flute to coax any"
          + " ghost out into the open. You will then need to kill the"
          + " ghost, which should not prove too difficult. When it is"
          + " destroyed, take the tear that appears.");
        write("\n"); /* for player readability */
        command("say Here, this ointment I am rubbing on your hands"
          + " will allow you to hold the tears without destroying"
          + " them. They are very fragile, and will evaporate at the"
          + " touch of untreated corporeal flesh.");
        write("\n"); /* for player readability */
        command("say Once you have collected eight of these tears,"
          + " use the method described in my brother's journal to"
          + " imbue a nullstone dagger. Once this is done, return the"
          + " imbued weapon and <show> it to me so that I may see the"
          + " degree to which his methods are currently effective.");
        write("\n"); /* for player readability */

        if (present(QUEST_WEAPON, this_player()))
        {
            command("say Excellent. I see you already possess"
              + " a nullstone dagger. Use that one in your"
              + " task.");
            write("\n"); /* for player readability */
        }
        else
        {
            obj = clone_object(WEP_DIR + "quest_weapon");
            obj->move(this_player());

            command("say Here is the nullstone dagger you brought"
              + " to me. Use it in your task.");
            write(
              "\n" + this_object()->query_The_name(this_player())
              + " gives you a nullstone dagger.\n\n");
            tell_room(environment(this_object()),
                QCTNAME(this_object()) + " gives " +
                QTNAME(this_player()) + " a nullstone dagger.\n",
                this_player());
        }

        if (this_player()->query_prop(ORC_TEMPLE_QUEST_PROP) != "ghost")
        {
            write_file(LOG_DIR + "quest_begin", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_name())
              + " began the Orc Temple ghost quest.\n");
        }

        this_player()->add_prop(ORC_TEMPLE_QUEST_PROP, "ghost");
        return;
    }

/* This is not yet implemented, and perhaps never will be ...
    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_DEMON_GROUP,
            ORCTEMPLE_DEMON_BIT))
    {
        command("say I am satisfied by what you have shown me. Though"
          + " he is getting closer to effective imbuement, the High"
          + " Priest has not yet understood the true nature of the"
          + " art, and fails to craft effective magical weapons.");
        command("say Though it will not be possible for one such as you"
          + " to banish the arch demon Yog-Sothoth from our plane, it"
          + " would indeed be possible to destroy, for a time, its"
          + " corporeal form. This would release the souls that it"
          + " has devoured into the peaceful oblivion they deserve.");
        command("say Its powers are truly great, however, and it"
          + " protects itself by an unbreakable repulsion spell that"
          + " prevents any powerful beings from approaching it.");
        command("say To even enter the fourth level of the dungeon"
          + " to face the demon, you would need to wear a special"
          + " medallion that I have crafted. Wearing this medallion"
          + " will reduce your power to the point where you will"
          + " be able to approach the demon.");
        command("say You may <ask> me about the medallion, and I will"
          + " give you one if you need it. If you are able to destroy"
          + " the demon's form, <show> me one of its tentacles and"
          + " will reward you.");
        return;
    }
 */

    command("say Your help has been of great importance. All that"
      + " remains is for you to continue to bring me as many imbued"
      + " items as you are able to locate, so that I can release the"
      + " trapped spirits within.");
        write("\n"); /* for player readability */
    command("say If you have not already begun your study of the art"
      + " of enchantment, please do feel free to study what is in"
      + " the codex you will find in the forge beneath this shop.");
        write("\n"); /* for player readability */
    command("emote gestures to the spiral staircase.");
        write("\n"); /* for player readability */
    command("say The knowledge within can serve you well.");
    write("\n"); /* for player readability */
    return;
} /* ask_quest */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("emote narrows his eyes and goes back to his studies.");
        return;
    }

    command("introduce me");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    string  answer = one_of_list( ({
        "On that topic I have little to offer you.",
        "Perhaps that question is best left for another to answer.",
        "I fear my knowledge of that is slight.",
        "You will need to seek elsewhere for answers to such as that.",
        "I know not. Ask another.",
        "Ply me not with such matters, for I know naught of them.",
        "You must seek elsewhere for the answer to this question.",
        "I cannot aid you with that.",
        "Perhaps you should ask another of these matters, for I know"
      + " little." }) );

    command("emote considers briefly before answering.");
    command("say " + answer);
    return "";
} /* default_answer */


/*
 * Function name:        run_away
 * Description  :        we mask the fun from /std/living/combat.c to
 *                       make sure he doesn't go anywhere. Not sure if
 *                       this is possible, but just in case.
 */
public void
run_away()
{
    command("peer stonily");
    command("say I have suffered worse things than this. I shall not"
      + " be moved.");

    return;
} /* run_away */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object("/d/Sparkle/area/orc_temple/arm/enchanter_robes");
    arm->move(this_object());

    command("wear all");
} /* arm_me */


/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 *                      In the case of the enchanter, we use this to
 *                      trigger his acts, rather than using add_act().
 * Arguments    :       hour - current hour in Sparkle time
 */
public void
alert_hour_change_hook(int hour)
{
    if (is_busy())
    {
        // Don't participate in daily routines when interacting.
        return;
    }
    
    switch (hour)
    {
    case 0:
    case 3:
    case 6:
    case 9:
    case 12:
    case 15:
    case 18:
    case 21:
    case 16:
    case 18:
    case 20:
        /* We only have him perform actions every 3 Sparkle hours, to
         * avoid undue spam. We'll limit even further with a random
         * chance.
         */
        if (!random(3))
        {
            command(one_of_list(Indoor_Acts));
        }
        break;
    case 23:
        command("$emote exhales stiffly.");
        command("$say The hour is late, but I must not sleep.");
        command("$emote touches a shining black stone on his robe,"
          + " nods off for a brief instant, and then"
          + " opens his eyes, looking completely refreshed.");
        break;
    default:
        break;
    }
} /* alert_hour_change_hook */


/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    set_alarm(1.0, 0.0, &react_items(ob, this_player()));
} /* show_hook */


/*
 * Function name:        react_items
 * Description  :        have the npc respond to a specific object
 * Arguments    :        object obj - the object that was shown
 *                       object to  - the player who showed it
 */
public void
react_items(object obj, object to)
{
    object    reward;

    intro_check(this_player());

    if (obj->id(STONE_NAME))
    {
        react_stones(obj);
        return;
    }

    if (obj->id(AMULET))
    {
        command("say By wearing that amulet, you will be able to avoid"
          + " detection by the evil power that rules the orc temple. But"
          + " take great care! You will also be completely at the mercy"
          + " of any enemies you may have who would take advantage of"
          + " your weakened state. I do not recommend wearing it outside"
          + " of the temple.");
        return;
    }

    /* The player shows the quest weapon to him. */
    if (obj->id(QUEST_WEAPON))
    {
        if (to->test_bit("Sparkle", ORCTEMPLE_WEAPON_GROUP,
                                    ORCTEMPLE_WEAPON_BIT))
        {
            if (to->test_bit("Sparkle", ORCTEMPLE_FLUTE_GROUP,
                                        ORCTEMPLE_FLUTE_BIT))
            {
                if (to->test_bit("Sparkle", ORCTEMPLE_GHOST_GROUP,
                                            ORCTEMPLE_GHOST_BIT))
                {
                    command("say Hmmm ... these should be destroyed.");
                    command("emote takes the dagger and destroyes it with"
                      + " a wave of his hand.");
                    obj->remove_object();
                    return;
                }
    
                /* reward sequence here for the ghost quest */
                if (to->query_prop(ORC_TEMPLE_QUEST_PROP) !=
                    "ghost")
                {
                    command("say I have not yet given you a task that"
                      + " has anything to do with that item. Perhaps"
                      + " you should first <ask> me for a quest?");
                    return;
                }

                if (!obj->query_imbued())
                {
                    command("say Yes, good. You have a nullstone dagger,"
                      + " still. You will need to kill ghosts on the"
                      + " prison level of the dungeon, and then follow"
                      + " the instructions set down in my brother's"
                      + " journal to imbue that weapon. Once you have"
                      + " done so, return to me and <show> me the"
                      + " dagger again.");
                    return;
                }

                to->catch_msg("\n"); /* for player readability */
                command("emote takes the nullstone dagger.");
                to->catch_msg("\n"); /* for player readability */
                command("say Ah! Excellent, excellent ... let me see ...");
                to->catch_msg("\n"); /* for player readability */
                command("emote sets the nullstone dagger before him, and"
                  + " begins passing his hands over it, muttering softly"
                  + " words you do not understand.");
                to->catch_msg("\n"); /* for player readability */

                if (obj->query_imbued() != to->query_real_name())
                {
                    command("emote looks up sharply.");
                    to->catch_msg("\n"); /* for player readability */
                    command("say This dagger was not imbued by you! I"
                      + " do not know where you got this, but I need you"
                      + " to complete the process yourself before I can"
                      + " discuss the matter further.");
                    to->catch_msg("\n"); /* for player readability */
                    command("emote performs an incantation, and the"
                      + " dagger crumbles into ash and vanishes.");

                    obj->remove_object();
                    return;
                }

                command("say Yes ... yes ... you have succeeded in"
                  + " following the methods I set out for my brother."
                  + " And I see he has not been able to improve on them.");
                to->catch_msg("\n"); /* for player readability */
                command("say This binding is incomplete, and the torn"
                  + " souls will be able to escape and find rest. Ah,"
                  + " what a relief. I know my brother will continue to"
                  + " try to perfect this process, but thus far, he remains"
                  + " uncertain of the means. Excellent!");
                to->catch_msg("\n"); /* for player readability */
                command("emote performs an incantation, and the dagger"
                  + " crumbles to ash and vanishes.");
                to->catch_msg("\n"); /* for player readability */
                command("say You have been of immense help. But more than"
                  + " this, you have learned something of the art of"
                  + " enchanting. I will now permit you to study with"
                  + " me, and make use of my enchanter's forge. There"
                  + " you will find a codex that contains knowledge"
                  + " I have to offer those who would pursue the craft.");
                to->catch_msg("\n"); /* for player readability */
                command("emote gestures to the spiral staircase.");
                to->catch_msg("\n"); /* for player readability */

                give_reward(to,
                            ORCTEMPLE_GHOST_GROUP,
                            ORCTEMPLE_GHOST_BIT,
                            ORCTEMPLE_GHOST_EXP,
                            "orc_temple_ghost");  
                to->catch_msg("\n"); /* for player readability */

                obj->remove_object();

                return;
            }

            command("say Ah, I see you have another of the High Priest's"
              + " nullstone daggers. Perhaps in time we will have need"
              + " of such a thing, but there are other matters to"
              + " which we must first attend.");
            return;
        }

        if (to->query_prop(ORC_TEMPLE_QUEST_PROP) !=
                "weapon")
        {
            to->catch_msg("\n"); /* for player readability */
            command("say What? Where did you get this? Are you a"
              + " servant of the High Priest?! Give that to me"
              + " immediately!");
            to->catch_msg("\n"); /* for player readability */
            command("emote takes the nullstone dagger and"
              + " destroys it with a wave of his hands.");
            to->catch_msg("\n"); /* for player readability */
            command("glare " + to->query_real_name());
            obj->remove_object();
            return;
        }

        command("emote takes the dagger, and inspects it closely.");
        to->catch_msg("\n"); /* for player readability */
        command("say So! The High Priest continues his efforts. It is"
          + " as I feared. You have done excellent work.");
        to->catch_msg("\n"); /* for player readability */

        reward = MONEY_MAKE_GC(10);
        reward->move(this_object());
        command("give coins to " + OB_NAME(to));
        to->catch_msg("\n"); /* for player readability */

        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        give_reward(to,
                    ORCTEMPLE_WEAPON_GROUP,
                    ORCTEMPLE_WEAPON_BIT,
                    ORCTEMPLE_WEAPON_EXP,
                    "orc_temple_weapon");  
        to->catch_msg("\n"); /* for player readability */

        obj->remove_object();
        to->remove_prop(ORC_TEMPLE_QUEST_PROP);

        command("say There is yet more work to do. You may <ask> me"
          + " about quests again when you feel ready to continue.");
        to->catch_msg("\n"); /* for player readability */

        return;
    } /* end of quest weapon reactions */

    /* The player shows the quest flute to him. */
    if (obj->id(QUEST_FLUTE))
    {
        if (to->test_bit("Sparkle", ORCTEMPLE_FLUTE_GROUP,
                                    ORCTEMPLE_FLUTE_BIT))
        {
            if (!to->test_bit("Sparkle", ORCTEMPLE_GHOST_GROUP,
                                         ORCTEMPLE_GHOST_BIT))
            {
                command("say You will have use of that soon, if"
                  + " you are to aid me further.");
                return;
            }

            to->catch_msg("\n"); /* for player readability */
            command("say These bone flutes are artifacts of misery, and"
              + " should be destroyed.");
            to->catch_msg("\n"); /* for player readability */
            command("emote takes the flute and destroys it with a wave"
              + " of his hands.");
            to->catch_msg("\n"); /* for player readability */
            obj->remove_object();
            return;
        }

        if (to->query_prop(ORC_TEMPLE_QUEST_PROP) != "flute")
        {
            command("say A bone flute! You should hang on to that, as"
              + " there may come a time when we will need to put it to"
              + " use.");
            return;
        }

        to->catch_msg("\n"); /* for player readability */
        command("say Ah ... you have done what is required, I see, and"
          + " taken the bone flute from the High Priest! Good. Very"
          + " good. I am sure this was no easy task.");
        to->catch_msg("\n"); /* for player readability */
        command("say We will need to put that to use soon, but first"
          + " things first. You have earned a reward for doing so much"
          + " to help with this problem.");
        to->catch_msg("\n"); /* for player readability */

        reward = MONEY_MAKE_PC(5);
        reward->move(this_object());
        command("give coins to " + OB_NAME(to));
        to->catch_msg("\n"); /* for player readability */

        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        give_reward(to,
                ORCTEMPLE_FLUTE_GROUP,
                ORCTEMPLE_FLUTE_BIT,
                ORCTEMPLE_FLUTE_EXP,
                "orc_temple_flute");  
        to->catch_msg("\n"); /* for player readability */

        this_player()->remove_prop(ORC_TEMPLE_QUEST_PROP);

        command("say There is yet more work to do. You may <ask> me"
          + " about quests again when you feel ready to continue.");
        to->catch_msg("\n"); /* for player readability */

        return;
    } /* end of quest flute reactions */

    if (obj->id(QUEST_TEAR))
    {
        command("say Ah yes ... a ghost tear!");
        command("say Excellent. I am glad to know that another poor soul"
          + " has been given peace.");
        return;
    }

    command("say This object is of no importance to me.");
    return;
} /* react_items */


/*
 * Function name:        init living
 * Description  :        set up some actions for the players who
 *                       enter the room
 */
public void
init_living()
{
    ::init_living();

    add_action(do_report, "make");
    add_action(do_report, "report");
    add_action(id_imbuements, "identify");
    add_action(do_buy, "buy");
    add_action(do_buy, "purchase");
    add_action(enchanter_work, "disenchant");
    add_action(enchanter_work, "transmogrify");
    add_action(enchanter_imbue, "imbue");
} /* init_living */


/*
 * Function name:        do_report
 * Description  :        Allow players to report to him when they have
 *                       read the journal.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_report(string arg)
{
    object  reward;

    if (query_verb() == "report")
    {
        notify_fail("Do you wish to <make> a report?\n");
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Make a report, perhaps?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
            "[a] [the] 'report' [about] [the] [journal]"))
    {
        notify_fail("Do you wish to make a report, perhaps?\n");
        return 0;
    }

    intro_check(this_player());

    if (this_player()->test_bit("Sparkle",
                                ORCTEMPLE_JOURNAL_GROUP,
                                ORCTEMPLE_JOURNAL_BIT))
    {
        write("\n"); /* for player readability */
        write("You again report to the enchanter what you once read"
          + " in the journal of the High Priest of the orc"
          + " dungeons.\n\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " reports something to the enchanter, who listens"
          + " with a look of confusion.\n", this_player());
        command("say Yes, very good. You have already told me these"
          + " things. I remember them clearly.");
        write("\n"); /* for player readability */

        return 1;
    }

    if (this_player()->query_prop(ORC_TEMPLE_QUEST_PROP) != "journal")
    {
        notify_fail("Make a report? You haven't been given any"
          + " quest do do that, have you?\n");
        return 0;
    }

    if (!this_player()->query_prop(JOURNAL_REAGENT_PROP))
    {
        notify_fail("You will need to first find and read the"
          + " journal of the High Priest!\n");
        return 0;
    }

    write("\n"); /* for player readability */
    write("You make your report, describing what you learned by reading"
      + " the journal of the High Priest in the orc dungeons.\n\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " reports something to the enchanter, who listens"
      + " attentively.\n", this_player());
    command("say Well done. I thank you for this report, and it is"
      + " a relief to know that the High Priest has not yet recorded"
      + " any improvements on the methods I taught him.");
    write("\n"); /* for player readability */
    command("say You see, I intentionally led him astray, showing him"
      + " the basics of imbuement, but not revealing to him the true"
      + " nature of the binding process. Thus, he will never achieve"
      + " imbuements that last, and the spirits he traps will eventually"
      + " escape the objects they have been cast into.");
    write("\n"); /* for player readability */
    command("say We must be sure, though! It is possible he has made"
      + " improvements to the imbuement generator without making record"
      + " of it in his journal. But that will have to wait. First,"
      + " you deserve a reward!");
    write("\n"); /* for player readability */

    reward = MONEY_MAKE_PC(3);
    reward->move(this_object());
    command("give coins to " + OB_NAME(this_player()));
    write("\n"); /* for player readability */

    if (environment(reward) == this_object())
    {
       command("drop coins");
    }

    give_reward(this_player(),
            ORCTEMPLE_JOURNAL_GROUP,
            ORCTEMPLE_JOURNAL_BIT,
            ORCTEMPLE_JOURNAL_EXP,
            "orc_temple_journal");  
    write("\n"); /* for player readability */

    this_player()->remove_prop(ORC_TEMPLE_QUEST_PROP);

    command("say There is yet more work to do. You may <ask> me"
      + " about quests again when you feel ready to continue.");
    write("\n"); /* for player readability */

    return 1;
} /* do_reward */


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    if (obj->id("coin"))
    {
        command("say Thank you, but I do not"
          + " need your charity. I will accept payment for services"
          + " I may render, but not otherwise.");
    }
    else if (obj->id(STONE_NAME))
    {
        react_stones(obj);
    }
    else
    {
        command("say This is of no use to me.");
    }
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
        command("drop " + OB_NAME(obj));
    }
} /* return_object */


/*
 * Function name:        ask_reward
 * Description  :        State-dependant reaction to questions about
 *                       reward
 * Returns      :        string
 */
public void
ask_reward()
{
    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_GHOST_GROUP,
            ORCTEMPLE_GHOST_BIT))
    {
        command("say Rewards will come to those who have helped me"
          + " with the important tasks which are at hand. You can"
          + " <ask> me about quests to know what needs to be done.");
        return;
    }

    command("say The only rewards that I can give you from henceforth"
      + " are the gifts of knowledge I have in the way of crafting"
      + " your own enchantments. Seek below in the enchanter's forge.");
    command("emote gestures to the spiral staircase.");

    return;
} /* ask_reward */


/*
 * Function name:        load_imbuements
 * Description  :        Get a list of existing imbuements for use in
 *                       identifying specific items' mods.
 */
public void
load_imbuements()
{
    Imbuements = IMBUE_MASTER->get_imbuements();
} /* load_imbuements */


/*
 * Function name:        id_imbuements
 * Description  :        Have the enchanter give the player detailed
 *                       information about a given item that has been
 *                       imbued.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
id_imbuements(string arg)
{
    object  *obj;
    string   word;
    int      is_wearable;
    int      is_weapon;
    int      imbue_id;
    mixed   *imbue_info;
    mixed    mod1;
    mixed    mod2;
    mixed    mod3;
    int      mod1_lvl;
    int      mod2_lvl;
    int      mod3_lvl;
    string   item_short;
    string   log_text;
    mixed   *imbue_descs;
    mixed    mod1_txt = "";
    mixed    mod2_txt = "";
    mixed    mod3_txt = "";
    string   secret_1;
    string   secret_2;
    string   secret_3;
    string  *final_thoughts = ({ "a fairly common find.",
                                 "a somewhat rare find.",
                                 "a rare find.",
                                 "a truly rare find.",
                                 "an exceedingly rare find.",
                                 "an outrageously rare find.",
                                 "a nearly unheard-of find!",
                                 "an unthinkably rare find!",
                                 "an unimaginable rarity! By the Gods!",
                              });

    string  *power_descs = ({ "The power of this particular imbuement,"
                            + " while considerable, is well within the"
                            + " range I consider normal.",
                              "The power of this particular imbuement"
                            + " is quite dramatic! It is rare to see such"
                            + " energy held stable in an item like this.",
                              "The power of this particular imbuement"
                            + " is ... is ... absolutely astounding! Few"
                            + " times in my life have I seen its equal!"
                            });
    int      how_many = 1;
    int      sentence_nums;
    mapping  mod_secrets = ([
      "bane_dragon"        : ({ "is the bane of all dragon kind, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all dragon kind, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_dwarf"         : ({ "is the bane of all dwarves, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all dwarves, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_elf"           : ({ "is the bane of all elves, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all elves, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_gnome"         : ({ "is the bane of all gnomes, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all gnomes, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_goblin"        : ({ "is the bane of all goblin kind, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all goblin kind, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_hobbit"        : ({ "is the bane of all halflings, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all halflings, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_human"         : ({ "is the bane of all humans, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all humans, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_minotaur"      : ({ "is the bane of all minotaur, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all minotaur, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_ogre"          : ({ "is the bane of all ogres, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all ogres, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_troll"         : ({ "is the bane of all trolls, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of all trolls, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "bane_undead"        : ({ "is the bane of the undead, who will"
                              + " suffer fire damage upon being struck by"
                              + " this weapon, if the trapped soul so chooses",
                                "is the bane of the undead, who will"
                              + " suffer fire damage when they strike"
                              + " it if it so chooses" }),
      "damage_acid"        : ({ "is filled with a fierce anger that will"
                              + " lash out at your enemies with acid"
                              + " whenever it chooses" }),
      "damage_air"         : ({ "is filled with a fierce anger that will"
                              + " lash out at your enemies with the powers"
                              + " of air whenever it chooses" }),
      "damage_cold"        : ({ "is filled with a fierce anger that will"
                              + " lash out at your enemies with fierce"
                              + " cold whenever it chooses" }),
      "damage_death"       : ({ "is filled with a fierce anger that will"
                              + " lash out at your enemies with the powers"
                              + " of death whenever it chooses" }),
      "damage_earth"       : ({ "is filled with a fierce anger that will"
                              + " lash out at your enemies with the powers"
                              + " of earth whenever it chooses" }),
      "damage_electricity" : ({ "is filled with a fierce anger that will"
                              + " lash out at your enemies with dangerous"
                              + " electricity whenever it chooses" }),
      "damage_fire"        : ({ "is filled with a fierce anger that will"
                              + " lash out at your enemies with the powers"
                              + " of fire whenever it chooses" }),
      "damage_water"       : ({ "is filled with a fierce anger that will"
                              + " lash out at your enemies with the powers"
                              + " of water whenever it chooses" }),
      "effect_darkness"    : ({ "will fill the area with darkness whenever"
                              + " it is equipped" }),
      "effect_darkvision"  : ({ "will grant its master the ability to see"
                              + " in darkness whenever it is equipped" }),
      "effect_haste"       : ({ "will grant its master with exceptional"
                              + " speed whenever it is equipped" }),
      "effect_healing"     : ({ "will bestow upon any who equip it powerful"
                              + " healing magics" }),
      "effect_light"       : ({ "will fill the area with light whenever"
                              + " it is equipped" }),
      "effect_poison"      : ({ "will deal fearful poison to an enemy at"
                              + " various intervals" }),
      "effect_slow"        : ({ "will place a curse of slowness upon any"
                              + " it strikes",
                                "will place a curse of slowness upon any"
                              + " who strike it", }),
      "effect_unbreakable" : ({ "is filled with powerful magic that protects"
                              + " it from many forms of wear and tear,"
                              + " causing it to last much longer" }),
      "extra_ac"           : ({ "is enchanted to provide additional"
                              + " protection to any who wear it" }),
      "extra_hit"          : ({ "is enchanted such that it practically"
                              + " guides itself toward an enemy, increasing"
                              + " the chance of striking" }),
      "extra_pen"          : ({ "is enchanted such that it penetrates much"
                              + " more deeply upon striking an enemy,"
                              + " causing more grievous wounds" }),
      "resist_acid"        : ({ "will protect the wearer from all forms"
                              + " of damage from acid" }),
      "resist_air"         : ({ "will protect the wearer from all forms"
                              + " of damage from the powers of air" }),
      "resist_cold"        : ({ "will protect the wearer from all forms"
                              + " of damage from cold" }),
      "resist_death"       : ({ "will protect the wearer from all forms"
                              + " of damage from the powers of death" }),
      "resist_earth"       : ({ "will protect the wearer from all forms"
                              + " of damage from the powers of earth" }),
      "resist_electricity" : ({ "will protect the wearer from all forms"
                              + " of damage from electricity" }),
      "resist_fire"        : ({ "will protect the wearer from all forms"
                              + " of damage from fire" }),
      "resist_life"        : ({ "will ward the wearer from all forms"
                              + " of influence from the powers of life" }),
      "resist_magic"       : ({ "will protect the wearer from all forms"
                              + " of magic" }),
      "resist_poison"      : ({ "will protect the wearer from all forms"
                              + " of damage from poison" }),
      "resist_water"       : ({ "will protect the wearer from all forms"
                              + " of damage from water" }),
      "skill_2handed"      : ({ "will increase the skill of any who equip"
                              + " it in the art of fighting with two"
                              + " weapons at once" }),
      "skill_air"          : ({ "will increase the skill of any who equip"
                              + " it in the ways of air magic" }),
      "skill_awareness"    : ({ "will increase the skill of any who equip"
                              + " it in their sense of awareness" }),
      "skill_axe"          : ({ "will increase the skill of any who equip"
                              + " it in the art of fighting with an axe" }),
      "skill_blindcombat"  : ({ "will increase the skill of any who equip"
                              + " it in the art of fighting without"
                              + " sight" }),
      "skill_club"         : ({ "will increase the skill of any who equip"
                              + " it in the art of fighting with clubs" }),
      "skill_death"        : ({ "will increase the skill of any who equip"
                              + " it in the ways of death magic" }),
      "skill_defence"      : ({ "will increase the skill of any who equip"
                              + " it in their ability to defend"
                              + " themselves" }),
      "skill_earth"        : ({ "will increase the skill of any who equip"
                              + " it in the ways of earth magic" }),
      "skill_fire"         : ({ "will increase the skill of any who equip"
                              + " it in the ways of fire magic" }),
      "skill_knife"        : ({ "will increase the skill of any who equip"
                              + " it in the art of fighting with knives" }),
      "skill_life"         : ({ "will increase the skill of any who equip"
                              + " it in the ways of life magic" }),
      "skill_parry"        : ({ "will increase the skill of any who equip"
                              + " it in their ability to parry"
                              + " incoming blows" }),
      "skill_polearm"      : ({ "will increase the skill of any who equip"
                              + " it in the art of fighting with"
                              + " polearms" }),
      "skill_sneakhide"    : ({ "will increase the skill of any who equip"
                              + " it in their ability to sneak and hide"
                              + " effectively" }),
      "skill_spellcraft"   : ({ "will increase the skill of any who equip"
                              + " it in the art of spellcraft" }),
      "skill_sword"        : ({ "will increase the skill of any who equip"
                              + " it in the art of fighting with swords" }),
      "skill_unarmed"      : ({ "will increase the skill of any who equip"
                              + " it in the art of fighting unarmed" }),
      "skill_water"        : ({ "will increase the skill of any who equip"
                              + " it in the ways of water magic" }),
      "stat_con"           : ({ "will increase the constitution of any"
                              + " who equip it" }),
      "stat_dex"           : ({ "will increase the dexterity of any"
                              + " who equip it" }),
      "stat_dis"           : ({ "will increase the discipline of any"
                              + " who equip it" }),
      "stat_int"           : ({ "will increase the intelligence of any"
                              + " who equip it" }),
      "stat_str"           : ({ "will increase the strength of any"
                              + " who equip it" }),
      "stat_wis"           : ({ "will increase the wisdom of any"
                              + " who equip it" }),
                            ]);

    if (!strlen(arg))
    {
        notify_fail("Identify what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (parse_command(arg, ({}),
            "[the] %w", word))
        {
            notify_fail(capitalize(word)
              + " ... what " + word + "? You possess no such thing!\n");
            return 0;
        }

        notify_fail("What do you wish to identify?\n");
        return 0;
    }

    tell_room(environment(this_object()), QCTNAME(this_player())
      + " presents " + obj[0]->short() + " for identification.\n",
        this_player());
    write("You present your " + obj[0]->short() + " for "
      + "identification.\n");

    if (!CAN_SEE_IN_ROOM(this_object()) ||
        !CAN_SEE(this_object(), this_player()))
    {
        command("say I would love to have you business, if only I could"
          + " see you.");
        return 1;
    }

    /* It could happen. Players try all sorts of things. */
    if (obj[0]->id(QUEST_WEAPON))
    {
        react_items(obj[0], this_player());

        command("say I do not count this as a true identification"
          + " service, of course, so there is no charge.");

        return 1;
    }

    intro_check(this_player());

    imbue_id = obj[0]->query_id();
    item_short = obj[0]->short();

    if (!imbue_id)
    {
        command("say Without even a second glance, I can tell that your "
          + item_short + " is not an item of the kind I seek.");
        command("say I will not count this as a true identification"
          + " service, of course, so there is no charge.");
        return 1;
    }

    if (obj[0]->query_prop(ID_CONFIRMATION) !=
        this_player()->query_real_name())
    {
        command("say Yes, I see that this " + item_short + " is indeed imbued"
          + " with powers that I could reveal to you. The cost will be "
          + LANG_NUM2WORD(IDENTIFY_COST)
          + " platinum coins. If you agree to that price, then"
          + " make your request a second time.");
        obj[0]->add_prop(ID_CONFIRMATION, this_player()->query_real_name());
        return 1;
    }

    load_imbuements();
    imbue_info = Imbuements[imbue_id];

    mod1     = imbue_info[1];
    mod1_lvl = imbue_info[2];
    mod2     = imbue_info[3];
    mod2_lvl = imbue_info[4];
    mod3     = imbue_info[5];
    mod3_lvl = imbue_info[6];

    is_wearable = obj[0]->query_wearable_item();
    is_weapon = obj[0]->check_weapon();

    imbue_descs = explode(obj[0]->long(), ".\n");

    if (!complete_payment(this_player(), IDENTIFY_COST, "identify"))
    {
        notify_fail(""); /* We don't want a fail message for this. */
        return 0;
    }

    tell_room(environment(this_object()), "\n");
    command("emote places the " + item_short + " on the table before him"
      + " and passes his hands over it, muttering silently.");
    tell_room(environment(this_object()), "\n");

    if (mod3)
    {
        how_many = 3;
        mod1_txt = imbue_descs[-3..-3];
        mod2_txt = imbue_descs[-2..-2];
        mod3_txt = imbue_descs[-1..-1];
        secret_1 = mod_secrets[mod1][0];
        secret_2 = mod_secrets[mod2][0];
        secret_3 = mod_secrets[mod3][0];

        if (sizeof(mod_secrets[mod1]) > 1 && is_wearable)
        {
            secret_1 = mod_secrets[mod1][1];
        }

        if (sizeof(mod_secrets[mod2]) > 1 && is_wearable)
        {
            secret_2 = mod_secrets[mod2][1];
        }

        if (sizeof(mod_secrets[mod3]) > 1 && is_wearable)
        {
            secret_3 = mod_secrets[mod3][1];
        }

        command("say Incredible! Three separate souls have found their"
          + " way into this object. This is exceptionally rare!");
        tell_room(environment(this_object()), "\n");
        command("say Now, let us examine each soul separately ...");
        tell_room(environment(this_object()), "\n");
        command("say Firstly, see how " + lower_case(mod1_txt[0])
          + "? This reveals to us that this item " + lower_case(secret_1)
          + ". " + power_descs[mod1_lvl - 1]);
        tell_room(environment(this_object()), "\n");
        command("say But here, see also how " + lower_case(mod2_txt[0])
          + "? By this, we learn that the item " + lower_case(secret_2)
          + ". " + power_descs[mod2_lvl - 1]);
        tell_room(environment(this_object()), "\n");
        command("say And finally, you have surely noticed how "
          + lower_case(mod3_txt[0]) + "? Well, in addition to all the"
          + " rest, this can only mean that the item "
          + lower_case(secret_3) + ". " + power_descs[mod3_lvl - 1]);
        tell_room(environment(this_object()), "\n");
    }
    else if (mod2)
    {
        how_many = 2;
        mod1_txt = imbue_descs[-2..-2];
        mod2_txt = imbue_descs[-1..-1];
        secret_1 = mod_secrets[mod1][0];
        secret_2 = mod_secrets[mod2][0];

        if (sizeof(mod_secrets[mod1]) > 1 && is_wearable)
        {
            secret_1 = mod_secrets[mod1][1];
        }

        if (sizeof(mod_secrets[mod2]) > 1 && is_wearable)
        {
            secret_2 = mod_secrets[mod2][1];
        }

        command("say Fascinating! Two separate souls have found their"
          + " way into this object. This is not something I usually"
          + " see!");
        tell_room(environment(this_object()), "\n");
        command("say Now, let us examine each soul separately ...");
        tell_room(environment(this_object()), "\n");
        command("say Firstly, see how " + lower_case(mod1_txt[0])
          + "? This reveals to us that this item " + lower_case(secret_1)
          + ". " + power_descs[mod1_lvl - 1]);
        tell_room(environment(this_object()), "\n");
        command("say But here, see also how " + lower_case(mod2_txt[0])
          + "? By this, we learn that the item " + lower_case(secret_2)
          + ". " + power_descs[mod2_lvl - 1]);
        tell_room(environment(this_object()), "\n");
    }
    else
    {
        how_many = 1;
        mod1_txt = imbue_descs[-1..-1];
        secret_1 = mod_secrets[mod1][0];

        if (sizeof(mod_secrets[mod1]) > 1 && is_wearable)
        {
            secret_1 = mod_secrets[mod1][1];
        }

        command("say Ah, yes! A soul has managed to find its way into"
          + " this object. This is becoming all too common.");
        tell_room(environment(this_object()), "\n");
        command("say Now, let us examine this soul ...");
        tell_room(environment(this_object()), "\n");
        command("say Yes, see here how " + lower_case(mod1_txt[0])
          + "? This reveals to us that this item " + lower_case(secret_1)
          + ". " + power_descs[mod1_lvl - 1]);
        tell_room(environment(this_object()), "\n");
    }

    command("say Overall, I believe this item represents "
      + final_thoughts[mod1_lvl + mod2_lvl + mod3_lvl - 1]);
    command("emote returns the " + item_short + ".");

    diary_check(this_player(), obj[0], "identify");

    IMBUE_GENERATOR->imbue_log("imbue_id", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name())
      + " identifies imbuements in an object:\n\t"
      + obj[0]->short() + ": " + file_name(obj[0]) + "\n\t"
      + "mod1:\t\t" + mod1 + "\n\t"
      + "power level:\t" + mod1_lvl + "\n\t"
      + "mod2:\t\t" + mod2 + "\n\t"
      + "power level:\t" + mod2_lvl + "\n\t"
      + "mod3:\t\t" + mod3 + "\n\t"
      + "power level:\t" + mod3_lvl + "\n");

    return 1;
} /* id_imbuements */


/*
 * Function name:        complete_payment
 * Description  :        See if the player has the right number of
 *                       platinum coins for the transaction. If not,
 *                       we let them know.
 * Arguments    :        string skill - the name of the skill to adapt,
 *                       object who - the player trying to pay
 *                       int needed - the number of plats it will cost
 *                       string reason - to log the reason for payment
 * Returns      :        int 1 - successful payment made
 *                           0 - not able to pay
 */
public int
complete_payment(object who, int needed, string reason)
{
    object  *inv_items = all_inventory(who);
    object  coin;
    object  temp_location;
    object  npc = this_object();

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
        command("peer annoy " + who->query_real_name());
        command("say First, I will require payment in the"
          + " form of " + LANG_NUM2WORD(needed) + " platinum coins."
          + " Seeing that you do not have even a single platinum"
          + " coin (and I do not trifle with lesser coinage) you will"
          + " need to return when you have the proper means for my"
          + " services.");
        return 0;
    }

    if (coin->num_heap() < needed)
    {
        command("peer patient " + who->query_real_name());
        command("say First, I will require payment in the"
          + " form of " + LANG_NUM2WORD(needed) + " platinum coins."
          + " Your " + LANG_NUM2WORD(coin->num_heap())
          + ((coin->num_heap() == 1) ? " falls" : " fall" ) + " somewhat"
          + " short of the mark, I am afraid. I prefer not to trifle with"
          + " lesser coinage, frankly, so you will need to return"
          + " when you have the proper means for my services.");
        return 0;
    }

    who->catch_tell("You pay " + needed + " platinum coins to "
      + npc->query_the_name(who) + ".\n");
    tell_room(environment(who), QCTNAME(who) + " pays some platinum"
      + " coins to " + QTNAME(npc) + ".\n", who);
    command("emote smiles slowly.");
    command("say Excellent, thank you for your payment.");

    temp_location = clone_object("/std/room");
    coin->split_heap(needed);
    coin->move(temp_location);
    /* Clean up afterward. */
    temp_location->remove_object();

    IMBUE_GENERATOR->imbue_log("imbue_payments", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name())
      + " pays " + needed + " platinum coins. (" + reason + ")\n");

    return 1;
} /* complete_payment */


/*
 * Function name:        intro_check
 * Description  :        Lets shorten the spam by having him intro if
 *                       the player doesn't know him yet.
 * Arguments    :        object who - the player
 */
public void
intro_check(object who)
{
    if (!IN_ARRAY(this_object()->query_real_name(),
         m_indices(who->query_introduced())))
    {
        command("say First, allow me to introduce myself.");
        command("introduce myself");
    }
}


/*
 * Function name:        do_buy
 * Description  :        allow players to try to buy a nullstone or
 *                       an amulet
 * Description  :        string arg - what was typed after the verb
 * Returns      :        int 1 - success
 *                           0 - failure
 */
public int
do_buy(string arg)
{
    object   sale;
    float    rate;
    float    discount;
    int      price;
    string   s;
    string  *sales = ({ "nullstone",
                        "null stone",
                        "stone",
                        "amulet",
                        "amulet of diminution",
                        "diminution amulet",
                        "lapidarium",
                     });

    tell_room(environment(this_object()), QCTNAME(this_player())
      + " inquires about making a purchase.\n",
        this_player());

    if (!strlen(arg))
    {
        notify_fail("");
        command("say What do you wish to buy? I can sell you a nullstone,"
          + " a lapidarium, or an amulet of diminution.");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] [a] [an] %p", sales))
    {
        if (parse_command(arg, ({}),
            "[the] %w 'nullstones'", s) || 
            arg == "nullstones")
        {
            command("say Nullstones may only be purchased one at a time.");
            return 1;
        }

        notify_fail("");
        command("say I do not sell that item. I can sell you a nullstone,"
          + " a lapidarium, or an amulet of diminution.");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(this_object()) ||
        !CAN_SEE(this_object(), this_player()))
    {
        command("say I would love to have you business, if only I could"
          + " see you.");
        return 1;
    }

    intro_check(this_player());

    switch(sales[0])
    {
        case "nullstone":
        case "null stone":
        case "stone":
            if (!present(LAPID_NAME, this_player()))
            {
                command("say Before I will sell you any nullstones, you"
                  + " will first need to purchase a lapidarium so that"
                  + " you can safely store your future collection of"
                  + " imbuement stones. You can <buy lapidarium> for"
                  + " the low cost of ten platinum coins.");
                return 1;
            }

            if (!this_player()->query_prop(STONE_CONFIRMATION))
            {
                command("say I would be happy to sell you as many"
                  + " nullstones as you desire to own. First, however,"
                  + " be advised that they cost "
                  + LANG_NUM2WORD(STONE_COST) + " platinum coins"
                  + " each. If you wish to proceed, please repeat your"
                  + " order.");
                this_player()->add_prop(STONE_CONFIRMATION, 1);
                return 1;
            }

            if (!complete_payment(this_player(), STONE_COST, "nullstone"))
            {
                notify_fail(""); /* No fail message for this. */
                return 0;
            }

            if (this_player()->query_prop(NULLSTONE_ADVICE))
            {
                command("say Here you are, use it well.");
            }
            else
            {
                command("say Nullstones are an essential ingredient in the"
                  + " art of enchantment. I recommend that you immediately"
                  + " <store> this in your lapidarium for safe keeping.");
                this_player()->add_prop(NULLSTONE_ADVICE, 1);
            }

            write("You purchased a nullstone.\n");
            tell_room(environment(this_object()), QCTNAME(this_player())
              + " purchases a nullstone.\n", this_player());

            sale = clone_object(IMBUE_OBJ_DIR + "imbuement_stone");

            if (sale->move(this_player()))
            {
                write("Oops! You dropped it!\n");
                sale->move(environment(this_object()));
            }

            write_file(IMBUE_LOG_DIR + "nullstones", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_name())
              + " purchased a nullstone.\n");

            return 1;
            break;
        case "amulet":
        case "amulet of diminution":
        case "diminution amulet":
            if (present(AMULET, this_player()))
            {
                command("say You already possess an amulet of dimunution."
                  + " You have no need for two.");
                return 1;
            }

            if (this_player()->query_average_stat() <
                THREAT_THRESHHOLD)
            {
                command("say I do not think you are experienced"
                  + " enough to be viewed as a threat by the evil that"
                  + " is beneath the temple. You will almost certainly"
                  + " be able to venture into that place without one.");
                return 1;
            }

            rate = itof(this_player()->query_skill(SS_TRADING)
                     + this_player()->query_stat(5)) * 0.001;
            discount = itof(this_player()->query_average_stat()) * rate;
            price = (this_player()->query_average_stat()
                  - ftoi(discount)) / 2;

            if (!this_player()->query_prop(AMULET_CONFIRMATION))
            {
                command("say I price the amulet on a sliding scale"
                  + " based on the experience you've had in the realms."
                  + " For you, the price will be "
                  + LANG_NUM2WORD(price) + " platinum coins. If you"
                  + " wish to proceed, simply restate your order.");
                this_player()->add_prop(AMULET_CONFIRMATION, 1);
                return 1;
            }

            if (!complete_payment(this_player(), price, "amulet"))
            {
                notify_fail(""); /* No fail message for this. */
                return 0;
            }

            command("say I must warn you ... wearing this amulet will"
              + " reduce your powers drastically. While wearing it,"
              + " you will be in considerable danger if you are"
              + " attacked by even a medium-sized opponent.");
            write("You purchased a shiny steel amulet.\n");
            tell_room(environment(this_object()), QCTNAME(this_player())
              + " purchases a shiny steel amulet.\n", this_player());

            sale = clone_object(OBJ_DIR + "amulet");
            sale->move(this_player());

            write_file(LOG_DIR + "amulet", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_name())
              + " purchased an amulet for " + price + " platinum.\n");

            return 1;
            break;
        case "lapidarium":
            if (present(LAPID_NAME, this_player()))
            {
                command("say You already possess a lapidarium."
                  + " You have no need for two.");
                return 1;
            }

            if (!complete_payment(this_player(),
                 LAPIDARIUM_COST, "lapidarium"))
            {
                notify_fail(""); /* No fail message for this. */
                return 0;
            }

            command("say This will serve you well. It is an essential"
              + " resource for anyone who wishes to seriously pursue the"
              + " art of enchantment.");
            write("You purchased a lapidarium.\n");
            tell_room(environment(this_object()), QCTNAME(this_player())
              + " purchases a lapidarium.\n", this_player());

            sale = clone_object(IMBUE_OBJ_DIR + "lapidarium");
            sale->move(this_player());

            write_file(LOG_DIR + "buy_lapidarium", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_name())
              + " purchased a lapidarium.\n");

            return 1;
            break;
        default:
            command("say I am afraid I have so such thing for sale.");
            return 1;
            break;
    }

    /* Should never happen, but just in case. */
    return 0;
} /* do_buy */


/*
 * Function name:        enchanter_work
 * Description  :        The enchanter will either disenchant or transmogrify
 *                       the item for the player.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
enchanter_work(string arg)
{
    object  *inv_items = all_inventory(this_player());
    object  *obj;
    object  *stones = ({});
    object   coins;
    object   temp_location;
    string   word;
    int      i = 1;
    int      still_needed;
    int      imbue_id;
    mixed   *imbue_info;
    mixed    mod1;
    mixed    mod2;
    mixed    mod3;
    int      mod1_lvl;
    int      mod2_lvl;
    int      mod3_lvl;
    int      num_imbuements = 1;
    string   item_short;
    string   log_txt;
    int      disenchant = (query_verb() == "disenchant");
    string  *quality = ({ "",
                          "cracked",
                          "blemished",
                          "ordinary",
                       });
    string   the_verb = query_verb();

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (parse_command(arg, ({}),
            "[the] %w", word))
        {
            notify_fail(capitalize(word)
              + " ... what " + word + "? You possess no such thing!\n");
            return 0;
        }

        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    tell_room(environment(this_object()), QCTNAME(this_player())
      + " asks the enchanter to " + query_verb()
      + " " + this_player()->query_possessive()
      + " " + obj[0]->short() + ".\n",
        this_player());
    write("You ask the enchanter to " + query_verb() + " your " 
      + obj[0]->short() + ".\n");

    if (Busy)
    {
        command("emote appears too busy to deal with your request right"
          + " now.");
        return 1;
    }

    if (!CAN_SEE_IN_ROOM(this_object()) ||
        !CAN_SEE(this_object(), this_player()))
    {
        command("say I would love to have you business, if only I could"
          + " see you.");
        return 1;
    }

    /* It could happen. Players try all sorts of things. */
    if (obj[0]->id(QUEST_WEAPON))
    {
        react_items(obj[0], this_player());

        command("say I have nothing for you, as that weapon did not"
          + " possess a typical imbuement.");

        return 1;
    }

    intro_check(this_player());

    imbue_id = obj[0]->query_id();
    item_short = obj[0]->short();

    if (!imbue_id)
    {
        command("say Without even a second glance, I can tell that your "
          + item_short + " is not the type of item I could "
          + the_verb + ".");
        return 1;
    }

    if (disenchant &&
        obj[0]->query_prop(DIS_CONFIRMATION) !=
        this_player()->query_real_name())
    {
        if (this_player()->query_prop(DISENCHANT_VETERAN))
        {
            command("say Of course. Just as before, please confirm that you"
              + " are prepared to lose your " + item_short + " in this"
              + " process by asking me to <disenchant> it a second time.");
            obj[0]->add_prop(DIS_CONFIRMATION,
                this_player()->query_real_name());
            return 1;
        }

        command("say Yes, I see that this " + item_short + " does indeed contain"
          + " spirits which must be released. However, I feel it is only"
          + " fair to warn you that this object might be useful to"
          + " you. Were you to equip it, the powers within might make"
          + " you more successful in your various exploits. Furthermore, if"
          + " you were to ask me to <transmogrify> the item, I could"
          + " transfer those powers into a nullstone for you to use in the"
          + " future.");
        command("say However, if you wish to proceed, the object will"
          + " be destroyed, the powers released, and I will pay you for"
          + " your trouble. Please ask me to <disenchant> the item a second"
          + " time to confirm your decision.");
        obj[0]->add_prop(DIS_CONFIRMATION, this_player()->query_real_name());
        return 1;
    }

    if (!disenchant &&
        obj[0]->query_prop(TRANS_CONFIRMATION) !=
        this_player()->query_real_name())
    {
        if (this_player()->query_prop(TRANS_VETERAN))
        {
            command("say Of course. Just as before, please confirm that you"
              + " are prepared to lose your " + item_short + " in this"
              + " process by asking me to <transmogrify> it a second time.");
            obj[0]->add_prop(TRANS_CONFIRMATION,
                this_player()->query_real_name());
            return 1;
        }

        command("say Yes, I see that this " + item_short + " does indeed contain"
          + " spirits which must be released. However, I feel it is only"
          + " fair to warn you that the this object might be useful to"
          + " you. Were you to equip it, the powers within might make"
          + " you more successful in your various exploits.");
        command("say However, if you wish to proceed, the object will"
          + " be destroyed and the powers transfered into any nullstones you"
          + " may possess. Please ask me to <transmogrify> the item a second"
          + " time to confirm your decision.");
        obj[0]->add_prop(TRANS_CONFIRMATION, this_player()->query_real_name());
        return 1;
    }

    load_imbuements();
    imbue_info = Imbuements[imbue_id];

    mod1     = imbue_info[1];
    mod1_lvl = imbue_info[2];
    mod2     = imbue_info[3];
    mod2_lvl = imbue_info[4];
    mod3     = imbue_info[5];
    mod3_lvl = imbue_info[6];

    if (disenchant)
    {
        command("say So be it. Let us end the suffering for this soul.");
        tell_room(environment(this_object()), "\n");
        command("emote takes the " + item_short + " and places it on"
          + " the table before him. He passes a strange prism of some"
          + " kind over the table, muttering quietly. With a swift gesture"
          + " of his hands, the " + item_short + " crumbles to ash and"
          + " is gone!");
        tell_room(environment(this_object()), "\n");
        command("say Thank you. Here is your payment.");
        tell_room(environment(this_object()), "\n");

        coins = clone_object("/std/coins");
        coins->set_coin_type("platinum");
        coins->set_heap_size(DISENCHANT_REWARD);

        this_player()->catch_tell("Karkadelt gives you"
          + " five platinum coins.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())
          + " gives " + QTNAME(this_player()) + " some money.\n",
            this_player());

        this_player()->add_prop(DISENCHANT_VETERAN, 1);

        if (coins->move(this_player()))
        {
            write("Ooops! You dropped them!\n");
            coins->move(environment(this_object()));
        }

        IMBUE_GENERATOR->imbue_log("disenchantments", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " disenchanted an object for 5 plats:\n\t"
          + obj[0]->short() + ": " + file_name(obj[0]) + "\n\t"
          + "mod1:\t\t" + mod1 + "\n\t"
          + "power level:\t" + mod1_lvl + "\n\t"
          + "mod2:\t\t" + mod2 + "\n\t"
          + "power level:\t" + mod2_lvl + "\n\t"
          + "mod3:\t\t" + mod3 + "\n\t"
          + "power level:\t" + mod3_lvl + "\n");

        diary_check(this_player(), obj[0], "disenchant");

        obj[0]->remove_object();
        return 1;
    }

    if (mod2_lvl)
    {
        num_imbuements++;
    }

    if (mod3_lvl)
    {
        num_imbuements++;
    }

    still_needed = num_imbuements;

    foreach (object inv_item: inv_items)
    {
        if (inv_item->id(STONE_NAME) && inv_item->id("nullstone"))
        {
            if (still_needed)
            {
                stones += ({ inv_item });
                still_needed--;
            }
        }
    }

    switch(num_imbuements)
    {
        case 1:
            if (this_player()->query_prop(TRANS_VETERAN))
            {
                word = "Another unusual object? Excellent. One more"
                  + " nullstone will be required. ";
            }
            else
            {
                word = "Ah, yes. Unusual objects like this are becoming all"
                  + " too common, I fear. A soul is most definitely"
                  + " trapped within, but a nullstone will be required before"
                  + " we can proceed. ";
            }
            break;
        case 2:
            word = "Ah! Peculiar objects like this are most rare. They"
              + " contain not one, but two trapped souls. As such, two"
              + " nullstones will be required before we begin. ";
            break;
        case 3:
            word = "By the Gods! An exotic object like this is something"
              + " I almost never see! This is an example of no less than"
              + " three souls trapped in a single item! Of course, this"
              + " means that three nullstones will be required before"
              + " we can begin. ";
            break;
        default:
            command("say What devilry is this? There appears to be"
              + " a so-called bug at work. Please contact a wizard"
              + " immediately!");
            return 1;
            break;
    }

    if (sizeof(stones) < num_imbuements)
    {
        switch(num_imbuements)
        {
            case 1:
                break;
            case 2:
                if (sizeof(stones))
                {
                    word += "It looks as if you will need one more. ";
                }
                else
                {
                    word += "You appear not to possess any. ";
                }
 
                break;
            case 3:
                if (sizeof(stones))
                {
                    word += "It looks as if you have only "
                      + LANG_NUM2WORD(sizeof(stones)) + ". ";
                }
                else
                {
                    word += "You appear not to possess any. ";
                }

                break;
            default:
                command("say What devilry is this? There appears to be"
                  + " a so-called bug at work. Please contact a wizard"
                  + " immediately!");
                return 1;
                break;
        }

        word += "If you wish, you may <buy> one, or perhaps you"
             + " already have one stored somewhere?";
        command("say " + word);

        return 1;
    }

    if (num_imbuements == 1)
    {
        this_player()->add_prop(TRANS_VETERAN, 1);
    }

    command("say " + word);

    write("\nYou hand Karkadelt " + ((num_imbuements == 1) ?
        "a nullstone" : LANG_NUM2WORD(num_imbuements) + " of your nullstones")
      + ".\n\n");
    tell_room(environment(this_object()), "\n"
      + QCTNAME(this_player()) + " hands something to Karkadelt.\n\n",
        this_player());

    word = " places the " + item_short + " on the table before"
      + " him, and begins chanting slowly. ";

    if (num_imbuements > 1)
    {
        word += "One by one, he passes the nullstones over the table,"
          + " circling them in strange patterns above the imbued"
          + " object.";
    }
    else
    {
        word += "He passes the nullstone over the table, circling it"
          + " in strange patterns above the imbued object.";
    }

    command("emote" + word);
    tell_room(environment(this_object()),
        "\nThere is a bright flash of light, and the " + item_short
      + " crumbles to ash!\n\n");

    foreach (object stone: stones)
    {
        switch (i)
        {
            case 1:
                stone->set_stone_type(Create_Stone[mod1]);
                stone->set_stone_quality(quality[mod1_lvl]);
                break;
            case 2:
                stone->set_stone_type(Create_Stone[mod2]);
                stone->set_stone_quality(quality[mod2_lvl]);
                break;
            case 3:
                stone->set_stone_type(Create_Stone[mod3]);
                stone->set_stone_quality(quality[mod3_lvl]);
                break;
            default:
                break;
        }
                
        i++;
    }

    this_player()->catch_tell("Karkadelt gives you "
      + COMPOSITE_DEAD(stones) + ".\n\n");
    tell_room(environment(this_object()), "Karkadelt hands something to "
      + QTNAME(this_player()) + ".\n\n", this_player());

    command("say Such stones should be stored immediately in your"
      + " lapidarium for safekeeping. Use them well.");

    log_txt = TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name())
      + " transmogrifies an object and receives stones:\n\t"
      + obj[0]->short() + ": " + file_name(obj[0]) + "\n\t"
      + "mod1:\t\t" + mod1 + " (lvl " + mod1_lvl + ")\n\t"
      + "stone:\t\t" + stones[0]->short() + "\n";

    if (sizeof(stones) > 1)
    {
        log_txt += "\tmod2:\t\t" + mod2 + " (lvl " + mod2_lvl + ")\n\t"
          + "stone:\t\t" + stones[1]->short() + "\n";
    }

    if (sizeof(stones) > 2)
    {
        log_txt += "\tmod3:\t\t" + mod3 + " (lvl " + mod3_lvl + ")\n\t"
          + "stone:\t\t" + stones[2]->short() + "\n";
    }

    diary_check(this_player(), obj[0], "transmogrify");

    obj[0]->remove_object();

    IMBUE_GENERATOR->imbue_log("stones_created", log_txt);

    return 1;
} /* enchanter_work */


/*
 * Function name:        enchanter_imbue
 * Description  :        Once a week, players may pay the enchanter
 *                       1000 plats to imbue an object of their choice
 *                       with a fully random result.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
enchanter_imbue(string arg)
{
    object  *obj;
    object   temp_location;
    string   word;
    int      imbue_id;
    string   item_short;


    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (parse_command(arg, ({}),
            "[the] %w", word))
        {
            notify_fail(capitalize(word)
              + " ... what " + word + "? You possess no such thing!\n");
            return 0;
        }

        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    tell_room(environment(this_object()), QCTNAME(this_player())
      + " presents " + obj[0]->short() + " for imbuement.\n",
        this_player());
    write("You present your " + obj[0]->short() + " for "
      + " imbuement.\n");

    if (Busy)
    {
        command("emote appears too busy to deal with your request right"
          + " now.");
        return 1;
    }

    if (!CAN_SEE_IN_ROOM(this_object()) ||
        !CAN_SEE(this_object(), this_player()))
    {
        command("say I would love to have you business, if only I could"
          + " see you.");
        return 1;
    }

    /* It could happen. Players try all sorts of things. */
    if (obj[0]->id(QUEST_WEAPON))
    {
        react_items(obj[0], this_player());

        command("say That object was not a candidate for imbuement.");

        return 1;
    }

    if (!IS_WEAPON_OBJECT(obj[0]) &&
        !IS_ARMOUR_OBJECT(obj[0]))
    {
        command("say I will only imbue things that you might equip, such"
          + " as a weapon, armour, or certain (but not all) forms of"
          + " wearable jewellery. Mundane items or simple clothing will"
          + " not work. This item, for example, does not appear to be"
          + " a suitable candidate.");

        return 1;
    }

    if (obj[0]->query_prop(OBJ_I_BROKEN))
    {
        command("say It appears as if this item is broken. As such, it"
          + " is not a good candidate for imbuement. When an imbued item"
          + " breaks, the imbuement is not disturbed, but I do not wish"
          + " to place such valuable powers in an item that is already"
          + " ruined.");

        return 1;
    }

    if (IS_HEAP_OBJECT(obj[0]))
    {
        command("say I am afraid that this item is not a candidate"
          + " for imbuement. I could explain, but it would take far too"
          + " long. Given my busy schedule, you'll just have to take my"
          + " word on it.");

        return 1;
    }

    if (obj[0]->query_auto_load() ||
        obj[0]->query_prop(OBJ_M_NO_DROP))
    {
        command("say That item looks too important to tamper with. I do"
          + " not believe it is a good candidate for imbuement.");

        return 1;
    }

    intro_check(this_player());

    imbue_id = obj[0]->query_id();
    item_short = obj[0]->short();

    if (imbue_id)
    {
        command("say This " + item_short + " is already filled with"
          + " a powerful magical imbuement. As such, it is not a"
          + " candidate for further imbuement.");

        return 1;
    }

    if (!week_elapsed(this_player()))
    {
        return 1;
    }

    if (obj[0]->query_prop(IMBUE_CONFIRMATION) !=
        this_player()->query_real_name())
    {
        command("say Yes, I would be willing to imbue this " + item_short
          + " for you. However, I have very limited supplies of surplus"
          + " energies, and must charge very steeply for the service as"
          + " a result. The cost will be no less than "
          + LANG_NUM2WORD(IMBUE_COST) + " platinum"
          + " coins. If you wish to proceed, confirm by asking me to"
          + " <imbue> the item a second time.");
        obj[0]->add_prop(IMBUE_CONFIRMATION, this_player()->query_real_name());
        return 1;
    }

    if (!complete_payment(this_player(), IMBUE_COST, "imbuement"))
    {
        notify_fail(""); /* No fail message for this. */
        return 0;
    }

    DATA_OBJ->set_info(IMBUE_FILE(this_player()->query_real_name()),
                       "Last_Imbue", time());

    IMBUE_GENERATOR->imbue_random(obj[0]);

    temp_location = clone_object("/std/room");
    obj[0]->move(temp_location);

    set_alarm(1.1, 0.0, &return_imbued_item(
        obj[0], temp_location, this_player()));

    command("say Let us see what the fates may provide for this item.");
    tell_room(environment(this_player()), "\n");
    command("emote takes the " + item_short + " and places it on the"
      + " table before him. He withdraws a strange prism of some kind"
      + " from a shelf, and begins passing it over the table, chanting"
      + " softly.");

    Busy = 1;
    return 1;
} /* enchanter_imbue */


/*
 * Function name:        week_elapsed
 * Description  :        check to see if a week has elapsed since the last
 *                       time a particular player paid for an imbuement
 *                       from the enchanter
 * Arguments    :        who - the player in question
 * Returns      :        int 1 - a week has elapsed
 *                       int 0 - a week has not yet elapsed
 */
public int
week_elapsed(object who)
{
    int     current_time = time();
    string  current_date = TIME2FORMAT(time(), "d mmm yyyy");
    string  current_weekday = get_weekday(ctime(time())[0..2]);
    int     old_time = DATA_OBJ->get_info(IMBUE_FILE(who->query_real_name()),
                                          "Last_Imbue");
    string *old_arr;
    string  old_weekday;
    string  old_date;
    int     seven_days = 604800;
    mapping yesterday = ([ "Sunday"    : "Saturday",
                           "Monday"    : "Sunday",
                           "Tuesday"   : "Monday",
                           "Wednesday" : "Tuesday",
                           "Thursday"  : "Wednesday",
                           "Friday"    : "Thursday",
                           "Saturday"  : "Friday",
                        ]);

    if (!old_time)
    {
        return 1;
    }

    old_weekday = get_weekday(ctime(old_time)[0..2]);
    old_date    = TIME2FORMAT(old_time, "d mmm yyyy");

    if ( (current_weekday == old_weekday) &&
         (current_date != old_date) )
    {
        return 1;
    }

    if ( (current_time - old_time) >= seven_days)
    {
        return 1;
    }

    if (current_weekday == yesterday[old_weekday])
    {
        old_weekday == "tomorrow";
    }
    else if (current_weekday == old_weekday)
    {
        old_weekday = "next " + old_weekday;
    }
    else
    {
        old_weekday = "this coming " + old_weekday;
    }

    command("say I am sorry, but the disenchantments I perform only"
      + " provide me with a limited amount of surplus energies with which"
      + " to create imbuements. As such, I am forced to restrict all of my"
      + " patrons to one such imbuement per week. Please visit me again "
      + old_weekday + " and I shall oblige.");

    return 0;
} /* week_elapsed */


/*
 * Function name:        get_weekday
 * Description  :        get the full name of a weekday based on its
 *                       first three letters
 * Arguments    :        string day - the first three letters of a weekday
 * Returns      :        string - the full weekday name
 */
public string
get_weekday(string day)
{
    switch(day)
    {
        case "Sun":
            return "Sunday";
            break;
        case "Mon":
            return "Monday";
            break;
        case "Tue":
            return "Tuesday";
            break;
        case "Wed":
            return "Wednesday";
            break;
        case "Thu":
            return "Thursday";
            break;
        case "Fri":
            return "Friday";
            break;
        case "Sat":
            return "Saturday";
            break;
        default:
            return "Sunday";
            break;
    }

    /* Shouldn't be possible, but just in case. */
    return "Error";
} /* get_weekday */


/*
 * Function name:        return_imbued_item
 * Description  :        give the imbued item to the player, following
 *                       a slight delay to make sure the imbuements are
 *                       actually in place.
 * Arguments    :        object ob            - the item
 *                       object temp_location - temp location to dest
 *                       object who           - the player
 */
public void
return_imbued_item(object ob, object temp_location, object who)
{
    int      imbue_id = ob->query_id();
    string   item_short = ob->short();
    mixed   *imbue_info;
    mixed    mod1;
    mixed    mod2;
    mixed    mod3;
    int      mod1_lvl;
    int      mod2_lvl;
    int      mod3_lvl;

    load_imbuements();
    imbue_info = Imbuements[imbue_id];

    mod1     = imbue_info[1];
    mod1_lvl = imbue_info[2];
    mod2     = imbue_info[3];
    mod2_lvl = imbue_info[4];
    mod3     = imbue_info[5];
    mod3_lvl = imbue_info[6];

    tell_room(environment(this_object()),
        "\nThere is a powerful flash of magic!\n\n");

    who->catch_tell("Karkadelt presents you with the " + item_short
      + " and says: May it serve you well.\n");
    tell_room(environment(this_object()),
        "Karkadelt presents " + QTNAME(who) + " with the " + item_short
      + " and says: May it serve you well.\n", who);

    if (ob->move(who))
    {
        who->catch_tell("Ooops! You dropped it!\n");
        ob->move(environment(this_object()));
    }

    diary_check(who, ob, "imbue");

    temp_location->remove_object();

    IMBUE_GENERATOR->imbue_log("enchanter_imbue", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name())
      + " imbued an object:\n\t"
      + item_short + ": " + file_name(ob) + "\n\t"
      + "mod1:\t\t" + mod1 + "\n\t"
      + "power level:\t" + mod1_lvl + "\n\t"
      + "mod2:\t\t" + mod2 + "\n\t"
      + "power level:\t" + mod2_lvl + "\n\t"
      + "mod3:\t\t" + mod3 + "\n\t"
      + "power level:\t" + mod3_lvl + "\n");

    Busy = 0;
    return;
} /* return_imbued_item */


/*
 * Function name:        react_stones
 * Description  :        have the enchanter react to stones he is given
 *                       and provide a bit of advice.
 * Arguments    :        object stone - the stone in question
 */
public void
react_stones(object stone)
{
    string   quality = stone->query_stone_quality();
    string   s_type = stone->query_stone_type();

    if (stone->query_prop(ALREADY_SEEN))
    {
        command("say Yes, you have already showed me this stone.");
        return;
    }

    stone->add_prop(ALREADY_SEEN, 1);

    if (stone->id("nullstone"))
    {
        command("say Ah, you have a nullstone. Very good. That will be"
          + " essential should you ever have an imbued item you wish"
          + " to have me <transmogrify>.");
        return;
    }

    switch(quality)
    {
        case "cracked":
            command("say Ah, " + LANG_ADDART(s_type) + ". A cracked"
              + " specimen like this is fairly common. However, they"
              + " are immensely important for crafting! You should try"
              + " to collect two more so that you can <combine> them"
              + " to upgrade to a blemished " + s_type + ".");
            break;
        case "blemished":
            command("say I see you have " + LANG_ADDART(s_type) + " that is"
              + " blemished in quality. These are somewhat rare, but I"
              + " have seen quite a few of them in my time. You should"
              + " try to collect two more so that you can <combine>"
              + " them to upgrade to an ordinary " + s_type + ", which"
              + " you would then be able to use for crafting your own"
              + " imbued items.");
            break;
        case "ordinary":
            command("say Oh, " + LANG_ADDART(stone->short()) + " ... "
              + " yes, very nice indeed! A stone of this quality is"
              + " sufficiently powerful to allow you to craft your"
              + " own imbuements. These are quite difficult to come"
              + " by, so you are fortunate to own one.");
            break;
        case "unblemished":
            command("say Ah, what have we here? "
              + capitalize(LANG_ADDART(s_type)) + " that is completely"
              + " unblemished? Remarkable! These are exceptionally rare,"
              + " and can be used to craft imbuements of power that is"
              + " greater than normal. You have done well to possess"
              + " such a stone as this!");
            break;
        case "glittering":
            command("say By the Gods! How did you ever come to possess"
              + " this?! I have seen many " + s_type + "s in my life,"
              + " but this ... this glitters like the stars! Such a"
              + " stone as this is more rare than you can possibly"
              + " imagine! You must have worked very hard to achieve it,"
              + " and it will reward you well. If you were to use it"
              + " to craft an imbuement, the power created would be"
              + " the stuff of legends. Guard it well!");
            break;
        default:
            command("say There is something wrong with this stone. You"
              + " should bugreport it immediately, and in the report"
              + " please indicate the name of the stone and it's"
              + " full short description.");
            break;
    }

    return;
} /* react_stones */


/*
 * Function name:        action_answers
 * Description  :        Have the enchanter respond to asks about the
 *                       actions he will perform.
 * Arguments    :        string arg - action we are talking about
 */
public void
action_answers(string arg)
{
    command("say Yes, I would be happy to <" + arg + " [item]> for "
      + ((arg == "transmogrify" || arg == "disenchant") ?
        "you." : "a price.")
      + " Please <exa poster> for a complete list of my services.");
    return;
} /* action_answers */


/*
 * Function name:        diary_check
 * Description  :        If the item is rare enough, Karkadelt will make a
 *                       note of it in his diary.
 * Arguments    :        object who - the player who brought it
 *                       object obj - the imbued item
 *                       string why - what is being done to the object?
 */
public void
diary_check(object who, object obj, string why)
{
    int      imbue_id = obj->query_id();
    object   diary_room;
    string  *diary_array;
    string   item_short = obj->short();
    string   diary_entry;
    string   diary_dir = TEXT_DIR + "enchanter_journal/";
    int      how_many;
    mixed   *imbue_info;
    mixed    mod1;
    mixed    mod2;
    mixed    mod3;
    int      mod1_lvl;
    int      mod2_lvl;
    int      mod3_lvl;
    int      entry_num;
    string  *final_thoughts = ({ "a fairly common find.",
                                 "a somewhat rare find.",
                                 "a rare find.",
                                 "a truly rare find.",
                                 "an exceedingly rare find.",
                                 "an outrageously rare find.",
                                 "a nearly unheard-of find!",
                                 "an unthinkably rare find!",
                                 "an unimaginable rarity! By the Gods!",
                              });
    mapping  months = ([ "Jan" : "January",
                         "Feb" : "February",
                         "Mar" : "March",
                         "Apr" : "April",
                         "May" : "May",
                         "Jun" : "June",
                         "Jul" : "July",
                         "Aug" : "August",
                         "Sep" : "September",
                         "Oct" : "October",
                         "Nov" : "November",
                         "Dec" : "December" ]);
    string  day;
    mixed   month;
    string  year_word;
    int     year;
    string  date;
    string  date_text;
    int     item_power = 0;

    if (!imbue_id ||
        obj->query_prop(ENCHANTER_DIARY_CHECK))
    {
        return;
    }

    obj->add_prop(ENCHANTER_DIARY_CHECK, 1);

    load_imbuements();
    imbue_info = Imbuements[imbue_id];

    mod1     = imbue_info[1];
    mod1_lvl = imbue_info[2];
    mod2     = imbue_info[3];
    mod2_lvl = imbue_info[4];
    mod3     = imbue_info[5];
    mod3_lvl = imbue_info[6];

    item_power = mod1_lvl + mod2_lvl + mod3_lvl;

    if (item_power < 5)
    {
        /* Not worthy of entering in the diary */
        return;
    }

    diary_array = get_dir(diary_dir);
    entry_num = 1;
    entry_num += DATA_OBJ->get_info(DIARY_NUM_FILE, "last_entry");

    while (IN_ARRAY(entry_num + ".txt", diary_array))
    {
        entry_num++;
    }

    day = TIME2FORMAT(time(), "d");
    month = months[TIMESTAMP[4..6]];
    year = atoi(TIME2FORMAT(time(), "yy"));

    switch(year)
    {
        case 11..13:
            year_word = year + "th";
            break;
        default:
            year_word = LANG_ORD2EXT(year);
            break;
    }

    date_text = "2" + year_word + " Year of the Fifth"
                 + " Cycle, " + month + " " + day + "\n\n";

    if (why == "imbue")
    {
        diary_entry = 
            "Today, an imbuement request from " 
          + LANG_ADDART(who->query_race_name()) + " named "
          + capitalize(who->query_real_name()) + " yielded "
          + final_thoughts[item_power -1] + " The " + obj->short()
          + " that " + who->query_pronoun() + " received ";
    }
    else
    {
        diary_entry =
            "Today, " + LANG_ADDART(who->query_race_name()) + " named "
          + capitalize(who->query_real_name()) + " brought in "
          + final_thoughts[item_power -1] + " The " + obj->short()
          + " that " + who->query_pronoun() + " asked me to " + why + " ";
    }

    if (mod3)
    {
        how_many = 3;
        diary_entry += "contained three separate imbuements. ";

        switch(item_power)
        {
            case 9:
                diary_entry += "Though it boggles the mind, all three of the"
                  + " imbuements are of a terrifying level of power! This"
                  + " is an item for the Gods themselves!";
                break;
            case 8:
                diary_entry += "Beyond almost anything I have seen, two"
                  + " of the imbuements are of a terrifying level of power,"
                  + " and the third itself is still above normal!";
                break;
            case 7:
                if ( (mod1_lvl + mod2_lvl == 6) ||
                     (mod2_lvl + mod3_lvl == 6) ||
                     (mod3_lvl + mod1_lvl == 6))
                {
                    diary_entry += "What is so fascinating"
                      + " is that an imbuement of standard power is"
                      + " joined here by not one, but two imbuements of"
                      + " truly terrifying power!";
                }
                else
                {
                    diary_entry += "While it is strange enough to find two"
                      + " two imbuements with powers greater than normal in"
                      + " a single host, here is a third imbuement that is in"
                      + " fact of terrifying power!";
                }
                break;
            case 6:
                if (mod1_lvl == 3 || mod2_lvl == 3 || mod3_lvl == 3)
                {
                    diary_entry += "Stranger still is the fact that all"
                      + " three imbuements are of different levels of"
                      + " power. One is the standard level, one is quite"
                      + " above normal, and the other is terrifying!";
                }
                else
                {
                    diary_entry += "What is truly striking is the fact that"
                      + " all three of the imbuements are greater than normal"
                      + " in their power!";
                }
                break;
            case 5:
                if (mod1_lvl == 3 || mod2_lvl == 3 || mod3_lvl == 3)
                {
                    diary_entry += "What is most surprising is the fact that"
                      + " while two of the imbuements are of the standard"
                      + " level of power, the third has a level of power"
                      + " that is truly terrifying!";
                }
                else
                {
                    diary_entry += "The rarity here comes from the fact that"
                      + " while one of the imbuements is of the standard"
                      + " level of power, both of the others are quite"
                      + " above normal!";
                }
                break;
            default:
                diary_entry += "There has been some bug. I'd better let"
                  + " Gorboth know.";
                break;
        }         
    }
    else
    {
        how_many = 2;
        diary_entry += "contained two separate imbuements. ";

        switch(item_power)
        {
            case 6:
                diary_entry += "The astonishing thing is that both"
                  + " of the imbuements are of a terrifying level of power!";
                break;
            case 5:
                diary_entry + "It is strange enough to see any imbuement of"
                  + " terrifying power like one of those contained in this"
                  + " item, but to see it joined by another that itself is"
                  + " greater than normal in power? Fascinating!";
                break;
            default:
                diary_entry += "There has been some bug. I'd better let"
                  + " Gorboth know.";
                break;
        }         
    }

    diary_entry += "\n";

    write_file(diary_dir + entry_num + ".txt",
               date_text + break_string(diary_entry, 75));

    command("emote mutters: I must remember to record this find in my"
      + " diary ...");

    if (diary_room = find_object(
            "/d/Sparkle/area/city/rooms/inside/enchanter_bedroom"))
    {
        present(DIARY_ID, diary_room)->configure_journal();
    }

    DATA_OBJ->set_info(DIARY_NUM_FILE, "last_entry", entry_num);

    IMBUE_GENERATOR->imbue_log("imbue_diary", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name())
      + " triggered a diary entry (via " + why + ")\n"
      + "\tNumber of mods (" + how_many + ")\t"
      + "Power Rating (" + item_power + ")\n\t"
      + "Entry Number (" + entry_num + ")\t"
      + "Imbue Id (#" + imbue_id + ")\n");
} /* diary_check */