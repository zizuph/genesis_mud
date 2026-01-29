/*
 *  /d/Sparkle/area/city/obj/herbvendor.c
 *
 *  This is a direct copy of the concept used by the Wednesday Market
 *  Quest in Sparkle. In this case, though, the theme is that the chef
 *  of the Silver Swan Inn makes a weekly special every Saturday, for
 *  which he needs a specific herb. Check the header file for the
 *  market quest for information about the concept and how it should
 *  work:
 *
 *      /d/Sparkle/area/city/obj/questvendor.c
 *
 *  Created April 2011, by Gorboth (Cooper Sherry)
 *
 *  2017-11-09 Malus: Reversed query_auto_load() and query_prop(OBJ_M_NO_DROP)
 *  check since some calls to query_auto_load() temporarily set that property
 *  to avoid drops during logout
 *
 * HERB NOTES: Footleaf and Gylvir have been complained about, but should
 *             not be removed. They are available in Faerun, but not in
 *             other domains, and aren't common in herb stores.
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>

#include "/d/Sparkle/sys/quests.h"
#include "../defs.h"

/* Definitions */
#define  HERB_NUM_NEEDED 10 /* Number of herbs we ask for any quest */
#define  QUEST_STRLEN    16
#define  MAX_REPEATS  250 /* Total of 50,000 quest experience is what is
                           * intended, similar to larger quests in the
                           * game. The quest is repeatable, with a
                           * reward of 200 qexp per completion. Once
                           * the player has solved it 250 times, they
                           * have earned the max allowed reward, and
                           * we switch to giving them a reward other
                           * than quest experience.
                           */
#define GEM_DIR            "/d/Genesis/gems/obj/"
#define REWARD_GEMS     ({ ("emerald"),    \
                           ("ruby"),       \
                           ("alexandrite"),\
                           ("diamond"),    \
                        })

/* Global Variables */
/* Please keep these herbs arranged alphabetically! */

mixed     *Gondor_Herbs = ({
                              ({ "alfirin",    "Gondor" }),
                              ({ "angurth",    "Gondor" }),
                              ({ "astaldo",    "Gondor" }),
                              ({ "athelas",    "Gondor" }),
                              ({ "attanar",    "Gondor" }),
                              ({ "basil",      "Gondor" }),
                              ({ "blackberry", "Gondor" }),
                              ({ "blueberry",  "Gondor" }),
                              ({ "blung",      "Gondor" }),
                              ({ "caraway",    "Gondor" }),
                              ({ "catnip",     "Gondor" }),
                              ({ "chervil",    "Gondor" }),
                              ({ "clove",      "Gondor" }),
                              ({ "coccinea",   "Gondor" }),
                              ({ "culkas",     "Gondor" }),
                              ({ "curugwath",  "Gondor" }),
                              ({ "dill",       "Gondor" }),
                              ({ "fennel",     "Gondor" }),
                              ({ "foxglove",   "Gondor" }),
                              ({ "frostheal",  "Gondor" }),
                              ({ "garlic",     "Gondor" }),
                              ({ "ginger",     "Gondor" }),
                              ({ "handasse",   "Gondor" }),
                              ({ "hemlock",    "Gondor" }),
                              ({ "ithilgil",   "Gondor" }),
                              ({ "laurel",     "Gondor" }),
                              ({ "lissuin",    "Gondor" }),
                              ({ "lothore",    "Gondor" }),
                              ({ "madwort",    "Gondor" }),
                              ({ "marigold",   "Gondor" }),
                              ({ "marjoram",   "Gondor" }),
                              ({ "mint",       "Gondor" }),
                              ({ "morgurth",   "Gondor" }),
                              ({ "nettle",     "Gondor" }),
                              ({ "oregano",    "Gondor" }),
                              ({ "redweed",    "Gondor" }),
                              ({ "rosemary",   "Gondor" }),
                              ({ "saffron",    "Gondor" }),
                              ({ "sage",       "Gondor" }),
                              ({ "savory",     "Gondor" }),
                              ({ "seregon",    "Gondor" }),
                              ({ "simbelmyne", "Gondor" }),
                              ({ "strawberry", "Gondor" }),
                              ({ "sumac",      "Gondor" }),
                              ({ "suranie",    "Gondor" }),
                              ({ "tarragon",   "Gondor" }),
                              ({ "thyme",      "Gondor" }),
                              ({ "tuo",        "Gondor" }),
                              ({ "tyelka",     "Gondor" }),
                              ({ "ungolestel", "Gondor" }),
                              ({ "yam",        "Gondor" }),
                          });

mixed     *Shire_Herbs = ({
                              ({ "bilberry",    "Shire" }),
                              ({ "blackroot",   "Shire" }),
                              ({ "calendula",   "Shire" }),
                              ({ "chives",      "Shire" }),
                              ({ "columbine",   "Shire" }),
                              ({ "daffodil",    "Shire" }),
                              ({ "hensbane",    "Shire" }),
                              ({ "huckleberry", "Shire" }),
                              ({ "khuz",        "Shire" }),
                              ({ "lamia",       "Shire" }),
                              ({ "laranthas",   "Shire" }),
                              ({ "maroea",      "Shire" }),
                              ({ "marshmallow", "Shire" }),
                              ({ "nasturtium",  "Shire" }),
                              ({ "oreste",      "Shire" }),
                              ({ "parsley",     "Shire" }),
                              ({ "pawnrose",    "Shire" }),
                              ({ "pindan",      "Shire" }),
                              ({ "tansy",       "Shire" }),
                              ({ "tobacco",     "Shire" }),
                          });

mixed     *Krynn_Herbs = ({
                              ({ "amanita",      "Krynn" }),
                              ({ "angeltear",    "Krynn" }),
                              ({ "asparagus",    "Krynn" }),
                              ({ "breadroot",    "Krynn" }),
                              ({ "bunchberry",   "Krynn" }),
                              ({ "cattail",      "Krynn" }),
                              ({ "chantrelle",   "Krynn" }),
                              ({ "chicory",      "Krynn" }),
                              ({ "cladina",      "Krynn" }),
                              ({ "cranberry",    "Krynn" }),
                              ({ "crocus",       "Krynn" }),
                              ({ "dandelion",    "Krynn" }),
                              ({ "elidross",     "Krynn" }),
                              ({ "fireweed",     "Krynn" }),
                              ({ "fucus",        "Krynn" }),
                              ({ "hawthorn",     "Krynn" }),
                              ({ "hazelnut",     "Krynn" }),
                              ({ "horsetail",    "Krynn" }),
                              ({ "jewelweed",    "Krynn" }),
                              ({ "laminaria",    "Krynn" }),
                              ({ "licorice",     "Krynn" }),
                              ({ "locoweed",     "Krynn" }),
                              ({ "mandrake",     "Krynn" }),
                              ({ "onoclea",      "Krynn" }),
                              ({ "sargassum",    "Krynn" }),
                              ({ "sarsaparilla", "Krynn" }),
                              ({ "saskatoon",    "Krynn" }),
                              ({ "skullcap",     "Krynn" }),
                              ({ "soapweed",     "Krynn" }),
                              ({ "solinaith",    "Krynn" }),
                              ({ "sphagnum",     "Krynn" }),
                              ({ "tangleshoot",  "Krynn" }),
                              ({ "veronica",     "Krynn" }),
                          });

mixed     *Earthsea_Herbs = ({
                              ({ "bergamot",    "Earthsea" }),
                              ({ "broccoli",    "Earthsea" }),
                              ({ "cinquefoil",  "Earthsea" }),
                              ({ "emmelti",     "Earthsea" }),
                              ({ "ginseng",     "Earthsea" }),
                              ({ "lebannen",    "Earthsea" }),
                              ({ "moly",        "Earthsea" }),
                              ({ "monkshood",   "Earthsea" }),
                              ({ "morel",       "Earthsea" }),
                              ({ "nilgu",       "Earthsea" }),
                              ({ "oakmoss",     "Earthsea" }),
                              ({ "paramol",     "Earthsea" }),
                              ({ "rushwash",    "Earthsea" }),
                              ({ "sparkweed",   "Earthsea" }),
                              ({ "spinach",     "Earthsea" }),
                              ({ "yarrow",      "Earthsea" }),
                          });

mixed     *Avenir_Herbs = ({
                              ({ "belladonna",   "Avenir" }),
                              ({ "bloodcreep",   "Avenir" }),
                              ({ "carlith",      "Avenir" }),
                              ({ "chartess",     "Avenir" }),
                              ({ "fordinfa",     "Avenir" }),
                              ({ "mittikna",     "Avenir" }),
                              ({ "narcissus",    "Avenir" }),
                              ({ "nethra",       "Avenir" }),
                              ({ "ronwath",      "Avenir" }),
                              ({ "strangleweed", "Avenir" }),
                          });

mixed     *Calia_Herbs = ({
                              ({ "athly",       "Calia" }),
                              ({ "streyroot",   "Calia" }),
                              ({ "strim",       "Calia" }),
                              ({ "wildfeather", "Calia" }),
                          });

mixed     *Faerun_Herbs = ({
                              ({ "adildra",    "Faerun" }),
                              ({ "amaranth",   "Faerun" }),
                              ({ "angelica",   "Faerun" }),
                              ({ "bellarnon",  "Faerun" }),
                              ({ "bloodfruit", "Faerun" }),
                              ({ "borage",     "Faerun" }),
                              ({ "buttercup",  "Faerun" }),
                              ({ "carolden",   "Faerun" }),
                              ({ "firemoss",   "Faerun" }),
                              ({ "footleaf",   "Faerun" }),
                              ({ "glowcap",    "Faerun" }),
                              ({ "gylvir",     "Faerun" }),
                              ({ "illavina",   "Faerun" }),
                              ({ "lavendar",   "Faerun" }),
                              ({ "lobelia",    "Faerun" }),
                              ({ "lorea",      "Faerun" }),
                              ({ "maicari",    "Faerun" }),
                              ({ "marymoor",   "Faerun" }),
                              ({ "osarni",     "Faerun" }),
                              ({ "ranindir",   "Faerun" }),
                              ({ "ripplebark", "Faerun" }),
                              ({ "selevon",    "Faerun" }),
                              ({ "sussur",     "Faerun" }),
                          });

mixed     *Kalad_Herbs = ({
                              ({ "blade",       "Kalad" }),
                              ({ "dajla",       "Kalad" }),
                              ({ "darfern",     "Kalad" }),
                              ({ "drudgeworth", "Kalad" }),
                              ({ "flameroot",   "Kalad" }),
                              ({ "fungari",     "Kalad" }),
                              ({ "glowshroom",  "Kalad" }),
                              ({ "kuko",        "Kalad" }),
                              ({ "lore",        "Kalad" }),
                              ({ "mindleech",   "Kalad" }),
                              ({ "numbis",      "Kalad" }),
                              ({ "pumpkin",     "Kalad" }),
                              ({ "vinerot",     "Kalad" }),
                          });


mixed     *Khalakhor_Herbs = ({
                              ({ "beatha",      "Khalakhor" }),
                              ({ "honeysuckle", "Khalakhor" }),
                              ({ "lilac",       "Khalakhor" }),
                              ({ "shamrock",    "Khalakhor" }),
                          });

mixed     *Terel_Herbs = ({
                              ({ "aravelis",  "Terel" }),
                              ({ "argil",     "Terel" }),
                              ({ "lukilvor",  "Terel" }),
                              ({ "moosho",    "Terel" }),
                              ({ "ramira",    "Terel" }),
                              ({ "sebre",     "Terel" }),
                              ({ "whitehorn", "Terel" }),
                              ({ "wilcol",    "Terel" }),
                              ({ "ylpi",      "Terel" }),
                              ({ "ylpoe",     "Terel" }),
                         });

mixed     *All_Herbs = ({    Gondor_Herbs
                           + Shire_Herbs
                           + Krynn_Herbs
                           + Earthsea_Herbs
                           + Avenir_Herbs
                           + Calia_Herbs
                           + Faerun_Herbs
                           + Kalad_Herbs
                           + Khalakhor_Herbs
                           + Terel_Herbs
                       });


/* Prototypes */
public void          create_object();
public string        exa_special();
public void          init();
public int           read_poster(string arg);
public int           do_deliver(string arg);
public int           claim_reward(string arg);
public void          tally_results();
public int           perform_inquiry(string arg);
public void          goodbye();
public void          day_check();
nomask varargs void  log_quest(object player, int exp, string name, int final = 0);

public mixed         query_herbs() { return one_of_list(one_of_list(All_Herbs))[0]; }
public void          add_quickness_reward(object who);

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("station");

    add_name( ({ HERBDAY + "special", H_VENDORNAME }) );
    set_adj( ({ "rolling", "chef", "chefs", "chef's" }) );

    set_short("rolling chef's station");
    set_long("A skilled-looking chef sits behind a rolling station"
      + " that has been wheeled into the main room of the inn. Every "
      + HERBDAY + " the chef offers a very special cuisine which"
      + " calls for high quantities of a particular ingredient which can be"
      + " found somewhere in the realms. You notice information about"
      + " a weekly special which you can <read> about on the station.\n");

    add_prop(OBJ_M_NO_GET, "The chef will murder you if you try.\n");
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 100000);

    add_item( ({ "special", "about special",
                 "weekly special", "about weekly special",
                 "ingredient", "about ingredient",
                 "information", "about information", }), exa_special);
    add_cmd_item( ({ "special", "about special",
                     "weekly special", "about weekly special",
                     "ingredient", "about ingredient",
                     "information", "about information",
                     "station", }),
                  ({ "read", "check" }), exa_special);

    add_item( ({ "chef", "skilled-looking chef" }),
        "The chef sits patiently behind the station, appearing hopeful"
      + " that someone will <read> the information about his weekly"
      + " special.\n");
    add_cmd_item( ({ "chef", "skilled-looking chef" }),
                  ({ "kill", "kick", "slap", "spit", "poke",
                     "tackle", "kiss", "tickle" }),
        "Oh, leave him alone. He really just wants people to help him"
      + " with his weekly special. Perhaps you can <read> about it at his"
      + " station?\n");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        exa_special
 * Description  :        provide text and quest information unique
 *                       for each player that examines it, based on
 *                       each player's datafile.
 * Returns      :        string - the text for the special
 */
public string
exa_special()
{
    string    name = this_player()->query_name(),
              date = TIME2FORMAT(time(), "yyyymmdd"),
              v_item,
              v_domain,
             *old_array = VENDOR->get_info(CURRENT_H_QUESTS, "h_unfinished");
    mixed    *task = one_of_list(one_of_list(All_Herbs));
    int       num,
              remaining,
              returned,
              i = 0;

    /* If the date on the old quest assignment isn't the same as the
     * date today for this player, they must be looking at the special
     * in a new week, so we assign them a new quest.
     */
    if (VENDOR->get_info(QUEST_FILE(name), "h_day") != date)
    {
        VENDOR->set_info(QUEST_FILE(name), "h_day",  date);
        VENDOR->set_info(QUEST_FILE(name), "h_done", "no");
        VENDOR->set_info(QUEST_FILE(name), "h_item", task[0]);
        VENDOR->set_info(QUEST_FILE(name), "h_returned", 0);
        VENDOR->set_info(QUEST_FILE(name), "h_num",  HERB_NUM_NEEDED);
        VENDOR->set_info(QUEST_FILE(name), "h_domain", task[1]);

        /* Now we need to declare this an unfinished task in our
         * tracking system so we can see if some quests never get
         * solved, and are thus too hard.
         */
        if (sizeof(old_array))
        {
            old_array += ({ task[0] });
        }
        else
        {
            old_array = ({ task[0] });
        }

        VENDOR->set_info(CURRENT_H_QUESTS, "h_unfinished", old_array);

        /* And here we need to keep track of how many times this
         * particular quest has been assigned, to compare to how
         * many times it has been successfully solved (or failed.)
         */
        i = VENDOR->get_info(QUEST_H_ASSIGNED, task[0]);
        i++;
        VENDOR->set_info(QUEST_H_ASSIGNED, task[0], i);

        v_item = task[0];
        v_domain = task[1];

        write_file(HERB_ASSIGN_LOG,
            sprintf("%s %-14s assigned %-30s\n",
            ctime(time()),
            this_player()->query_name(),
            ((strlen(v_item) > QUEST_STRLEN) ? 
                v_item[0..(QUEST_STRLEN - 1)] : v_item )));
    }

    v_item = VENDOR->get_info(QUEST_FILE(name), "h_item");
    returned = VENDOR->get_info(QUEST_FILE(name), "h_returned");
    num = VENDOR->get_info(QUEST_FILE(name), "h_num");
    v_domain = VENDOR->get_info(QUEST_FILE(name), "h_domain");

    remaining = num - returned;

    tell_room(environment(this_object()),
        QCTNAME(this_player()) + " walks over and examines the"
      + " weekly special on the rolling chef's station.\n", this_player());

    if (VENDOR->get_info(QUEST_FILE(name), "h_done") == "yes")
    {
        return "You check the weekly special, but then remember that"
          + " you've already completed this task. Perhaps next week there"
          + " will be another opportunity to help out.\n";
    }

    if (!remaining)
    {
        return "As you check the weekly special, you realize that you could"
          + " probably <claim> a reward from the chef now. You"
          + " seem to have done everything that he has asked"
          + " for.\n";
    }

    return "You check the weekly special, and read that the chef is"
      + " in need of " + LANG_NUM2WORD(remaining)
      + " more herb" + ((remaining > 1) ? "s" : "") + " of the "
      + v_item + " variety"
      + " to complete his entree. The information written down suggests"
      + " that this ingredient can usually be found by searching for"
      + " herbs in the lands of " + v_domain + ". A meaningful reward"
      + " will be given to the person who can deliver them.\n\n"
      + "You also notice a poster with instructions on the station.\n";
} /* exa_special */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(read_poster, "read");
    add_action(read_poster, "exa");
    add_action(do_deliver, "deliver");
    add_action(claim_reward, "claim");
    add_action(perform_inquiry, "inquire");
} /* init */


/*
 * Function name:        read_poster
 * Description  :        allow players to read the poster
 * Arguments    :        string arg - what was typed following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
read_poster(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[at] [the] 'poster' / 'instruction' / 'instructions'"))
    {
        notify_fail("You find no " + arg + "\n");
        return 0;
    }

    write("\n"
        + "\t .------------------------------------------------------.\n"
        + "\t|        Instructions for those delivering herbs:        |\n"
        + "\t|                                                        |\n"
        + "\t|  <deliver x>    - Give a desired item to the chef.     |\n"
        + "\t|  <claim reward> - Receive payment for fulfilling the   |\n"
        + "\t|                   requests of the chef.                |\n"
        + "\t .______________________________________________________.\n"
        + "\n");

    day_check();

    return 1;
} /* read_poster */


/*
 * Function name:        do_deliver
 * Description  :        allow players to turn in things to the vendors
 *                       for progress on the quest
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
do_deliver(string arg)
{
    string    name = this_player()->query_name(),
              date = TIME2FORMAT(time(), "yyyymmdd"),
              v_item = VENDOR->get_info(QUEST_FILE(name), "h_item");
    mixed    *objs;
    object    delivery;
    int       num = VENDOR->get_info(QUEST_FILE(name), "h_num"),
              returned = VENDOR->get_info(QUEST_FILE(name), "h_returned"),
              remaining,
              delivered = 0,
              heap_amount,
              i;

    day_check();

    if (!strlen(arg))
    {
        notify_fail("What do you wish to deliver to the chef?\n");
        return 0;
    }

    if (VENDOR->get_info(QUEST_FILE(name), "h_day") != date)
    {
        notify_fail("You'd better check the weekly special to make sure you"
          + " know what the chef needs for his entree first.\n");

        return 0;
    }

    if (!sizeof(objs = PARSE_COMMAND(arg, all_inventory(this_player()),
        "[the] %i [to] [the] [vendor] [vendors]")))
    {
        notify_fail("You don't seem to have any such thing.\n");
        return 0;
    }

    this_player()->reveal_me(1);

    /* Has the player already completed the quest for this week? */
    if (VENDOR->get_info(QUEST_FILE(name), "h_done") == "yes")
    {
        write("The chef does not seem to need any more "
          + LANG_PWORD(v_item) + " but again thanks you for your hard"
          + " work.\n");

        return 1;
    }

    /* Has the player already returned the necessary number of items,
     * but not yet claimed their reward?
     */
    if (returned >= num)
    {
        write("The chef smiles at you, and exclaims: \"You are"
          + " an overachiever, my friend! I have no need for more."
          + " Please, <claim> your reward that I might repay your"
          + " hard work.\"\n");

        return 1;
    }

    foreach (object obj: objs)
    {
        returned = VENDOR->get_info(QUEST_FILE(name), "h_returned");

        if (!obj->id(v_item) &&
            obj->query_herb_name() != v_item)
        {
            notify_fail("The chef has no need for that"
              + " item.\n");
            continue;
        }
        /* We can't allow players to discard things they shouldn't be able
         * to!
         */
        else if (obj->query_prop(OBJ_M_NO_DROP) || 
                obj->query_auto_load())
        {
            notify_fail("No ... that item cannot leave you.\n");
            continue;
        }
        else if (obj->query_worn())
        {
            notify_fail("You would need to remove it first.\n");
            continue;
        }
        else if (obj->query_wielded())
        {
            notify_fail("You would need to unwield it first.\n");
            continue;
        }
        else if (obj->query_keep())
        {
            notify_fail("That item is currently set to be kept. You"
              + " will first need to <unkeep> it.\n");
            continue;
        }


        remaining = num - returned;

        /* Now to remove the object from the inventory of the
         * player. If the object in question is a heap object,
         * we have to deal with that a bit differently.
         */
        if (IS_HEAP_OBJECT(obj))
        {
            heap_amount = obj->num_heap();

            if (heap_amount > remaining)
            {
                i = heap_amount - remaining;
                obj->set_heap_size(i);

                delivered += remaining;
                VENDOR->set_info(QUEST_FILE(name), "h_returned", num);
                break;
            }
            else
            {
                i = heap_amount - remaining;
                obj->remove_split_heap();
            }

            i = remaining - heap_amount;

            delivered += heap_amount;
            VENDOR->set_info(QUEST_FILE(name), "h_returned",
                (returned + heap_amount));
        }
        else if (returned > 9)
        {
            break;
        }
        else
        {
            obj->remove_object();
            VENDOR->set_info(QUEST_FILE(name), "h_returned",
                (returned + 1));
            delivered++;
        }
    }

    if (!delivered)
    {
        return 0;
    }

    returned = VENDOR->get_info(QUEST_FILE(name), "h_returned");

    write("You hand " + ((delivered > 1) ?
        LANG_NUM2WORD(delivered) + " " + LANG_PWORD(v_item) :
        "a single " + v_item) + " over to the chef.\n");
    tell_room(environment(this_object()),
        QCTNAME(this_player()) + " hands " + ((delivered > 1) ?
        LANG_NUM2WORD(delivered) + " " + LANG_PWORD(v_item) :
        "a single " + v_item) + " over to the chef.\n",
        this_player());

    /* Is this the final delivery for the quest? */
    if (num == returned)
    {
        write("The chef examines your delivery and gratefully accepts"
          + " it, exclaiming: \"Ah yes, you have done well! You may"
          + " now rightfully <claim> your reward!\"\n");
    }
    else
    {
        remaining = num - returned;

        if (delivered > 1)
        {
            write("The chef examines each of your deliveries in turn,"
              + " and gratefully accepts them. He says: \"Ah! These are"
              + " some very fine " + LANG_PWORD(v_item) + " you have"
              + " brought me. Excellent. Now I need but "
              + LANG_NUM2WORD(remaining) + " more to prepare my entree. ");
        }
        else
        {
            write("The chef examines your delivery and gratefully"
              + " accepts it. He says: \"Ah! A very fine " + v_item 
              + " you have brought me. Excellent. I need but "
              + LANG_NUM2WORD(remaining) + " more to prepare my entree. ");
        }

        write("Bring me " + ((remaining > 1) ? "these" : "this")
          + " and I will reward you!\"\n");
    }

    return 1;
} /* do_deliver */


/*
 * Function name:        claim_reward
 * Description  :        allow the player to claim their reward
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
claim_reward(string arg)
{
    mixed    *quest_arr = VENDOR->get_info(CURRENT_H_QUESTS, "h_unfinished");
    string    name = this_player()->query_name(),
              date = TIME2FORMAT(time(), "yyyymmdd"),
              v_item = VENDOR->get_info(QUEST_FILE(name), "h_item"),
             *new_arr = allocate(sizeof(quest_arr));
    int       num = VENDOR->get_info(QUEST_FILE(name), "h_num"),
              returned = VENDOR->get_info(QUEST_FILE(name), "h_returned"),
              repeats = VENDOR->get_info(QUEST_FILE(name), "h_repeats"),
              remaining,
              arr_point,
              reward = this_player()->query_exp(),
              exp = SPARKLE_HERB_EXP,
              group = SPARKLE_HERB_GROUP,
              bit = SPARKLE_HERB_BIT;
    object    gems;

    if (sizeof(quest_arr))
    {
        new_arr = allocate(sizeof(quest_arr) - 1);
    }

    if (!strlen(arg) ||
        !parse_command(arg, ({}), "[my] [the] 'reward' / 'rewards'"))
    {
        notify_fail("Claim your reward?\n");
        return 0;
    }

    if (VENDOR->get_info(QUEST_FILE(name), "h_day") != date)
    {
        notify_fail("You have yet to even check the weekly special, let alone"
          + " assist the chef! He owes you nothing.\n");

        return 0;
    }

    if (VENDOR->get_info(QUEST_FILE(name), "h_done") == "yes")
    {
        notify_fail("The chef smiles politely at you and"
          + " exclaims: \"Ah, but you have already received your"
          + " reward. Come see me next week and I may have more"
          + " need of your services.\"\n");

        return 0;
    }

    if (returned >= num)
    {
        write("At your request, the chef considers what you have done"
          + " and finally exclaims: \"Yes,"
          + " yes! I am indeed in your debt. Accept this"
          + " reward for your hard work!\"\n\n");

        repeats++;
        VENDOR->set_info(QUEST_FILE(name), "h_repeats", repeats);
        VENDOR->set_info(QUEST_FILE(name), "h_done", "yes");

        if (this_player()->test_bit(getuid(), group, bit))
        {
            write("The chef hands you some valuable gems.\n"
              + "You don't feel any more experienced, though. Perhaps"
              + " you have learned all you can by helping the"
              + " chef. In any case, you are a bit richer now!\n");
            gems = clone_object(GEM_DIR + (one_of_list(REWARD_GEMS)));
            gems->set_heap_size(2 + random(4));

            /* Move to player failed, lets drop them on the floor. */
            if (gems->move(this_player()))
            {
                write("Ooops! You are carrying too much and drop your"
                  + " reward on the ground!\n");
                tell_room(environment(this_player()),
                    QCTNAME(this_player()) + " drops something on the"
                  + " ground.\n");
                gems->move(environment(this_player()));
            }
        }
        else
        {
            /* We don't give out more experience than the player already
             * has.
             */
            if (reward > exp)
            {
                reward = exp;  
            }

            if (MAX_REPEATS ==
                VENDOR->get_info(QUEST_FILE(name), "h_repeats"))
            {
                this_player()->set_bit(group, bit);

                /* Lets capitalize it so it is highlighted in the log
                 * when a player completes it for the final quest 
                 * reward.\n");
                 */
                log_quest(this_player(), reward, upper_case(v_item));
                log_quest(this_player(), reward, upper_case(v_item), 1);
            }
            else
            {
                log_quest(this_player(), reward, v_item);
            }

            this_player()->add_exp_quest(reward);
            this_player()->catch_tell("You feel more experienced!\n");

        }
        write("\nThe chef says: Here! I'd also like to reward you with"
          + " a sip of my special mercurystone cordial! The enchanter"
          + " makes it for me special order, and it helps me get all"
          + " my cooking done in time. Just one sip lasts for 24 hours"
          + ", if you can believe it!\n\nHe unstops a crystal vial"
          + " and lets you take a swig. It burns all the way down.\n");

        add_quickness_reward(this_player());

        write("\nThe chef says: \"Oh, and please remember to"
          + " come back next " + HERBDAY + "! I am sure to need"
          + " your services again then.\"\n");

        /* Well, they solved it, so we should remove this quest item
         * from the array of unsolved items that we are keeping track
         * of for logging purposes.
         */
        arr_point = member_array(v_item, quest_arr);

        if (arr_point > -1)
        {
            new_arr = exclude_array(quest_arr, arr_point, arr_point);
            VENDOR->set_info(CURRENT_H_QUESTS, "h_unfinished", new_arr);
        }

        /* We will also now increase the tally for this particular
         * item on the number of times it has been solved. Since its
         * not being used anymore, we'll use the arr_point variable
         * for our new purposes.
         */
        arr_point = VENDOR->get_info(QUEST_H_SUCCESSES, v_item);
        arr_point++;
        VENDOR->set_info(QUEST_H_SUCCESSES, v_item, arr_point);

        day_check();

        return 1;
    }

    remaining = num - returned;

    write("The chef smiles politely at you, and exclaims: "
      + "\"I am still in need of " + LANG_NUM2WORD(remaining)
      + " more " + ((remaining > 1) ? LANG_PWORD(v_item) : v_item)
      + " before I can prepare my entree. I really can't reward you until"
      + " I have received the full amount.\"\n");

    day_check();

    return 1;
} /* claim_reward */


/*
 * Function name:        tally_results
 * Description  :        We want to keep track of the quests that were
 *                       not solved by this week's questers. If it is
 *                       shown that certain quests are impossible, they
 *                       will need to be removed from the list.
 */
public void
tally_results()
{
    string *quests = VENDOR->get_info(CURRENT_H_QUESTS, "h_unfinished");
    int     num = 0;

    /* Here we increase the tally for all quests that remain unfinished
     * this week.
     */
    foreach (string quest: quests)
    {
        num = VENDOR->get_info(QUEST_H_FAILURES, quest);
        num++;
        VENDOR->set_info(QUEST_H_FAILURES, quest, num);
    }

    /* Now we need to wipe out the current quests listed in the
     * datafile.
     */
    VENDOR->set_info(CURRENT_H_QUESTS, "h_unfinished", ({}));
} /* tally_results */


/*
 * Function name:        perform_inquiry
 * Description  :        Allow someone to ask the vendors about the
 *                       task they are currently wanting to have solved
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
perform_inquiry(string arg)
{
    string  v_item;
    int     successes,
            failures,
            assigned;

    notify_fail("Inquire about what item?\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[about] [a] [an] [the] %w", v_item))
    {
        return 0;
    }

    successes = VENDOR->get_info(QUEST_H_SUCCESSES, v_item);
    failures = VENDOR->get_info(QUEST_H_FAILURES, v_item);
    assigned = VENDOR->get_info(QUEST_H_ASSIGNED, v_item);

    if (!assigned)
    {
        write("The chef has an iron-clad memory for ingredients, and"
          + " quickly recalls, \"I have never asked"
          + " for such an ingredient from anyone!\"\n");
        return 1;
    }

    write("The chef has an iron-clad memory for ingredients, and"
      + " quickly recalls, \"I have asked for that ingredient "
      + LANG_NUM2WORD(assigned) + " " + ((assigned > 1) ? "times" :
        "time") + ". ");

    if (successes)
    {
        if (successes > 1)
        {
            write("There have been " + LANG_NUM2WORD(successes)
              + " who succeeded, and ");
        }
        else
        {
            write("There has been one who succeeded, and ");
        }
    }
    else
    {
        write("None have succeeded, and ");
    }

    if (failures)
    {
        if (failures > 1)
        {
            write(LANG_NUM2WORD(failures) + " have failed.");
        }
        else
        {
            write("one has failed.");
        }
    }
    else
    {
        write("none have failed.");
    }

    write("\"\n");
    return 1;
} /* perform_inquiry */


/*
 * Function name:        goodbye
 * Description  :        Once the day of the Market ends (a real life
 *                       day, determined in the defs.h file) the vendors
 *                       clean up and go home.
 */
public void
goodbye()
{
    tell_room(environment(this_object()),
        "Suddenly, without warning, the chef begins packing up his"
      + " rolling station and wheels it back toward the kitchen. As he"
      + " disappears out of sight, he turns and calls, \""
      + "I will be back next " + HERBDAY + ", with a new weekly special!"
      + " Come and find me again then!\"\n");

    tally_results();
    remove_object();
} /* goodbye */


/*
 * Function name:        day_check
 * Description  :        If it isn't market day anymore, we need to
 *                       have the vendors pack their things and leave
 *                       immediately.
 */
public void
day_check()
{
    if (ctime(time())[0..2] != HERBDAY[0..2])
    {
        set_alarm(1.0, 0.0, goodbye);
    }
} /* day_check */


/*
 * Function name: log_quest
 * Description  : This function makes the log of a quest when it is
 *                solved and is placed here to make a uniform log-format.
 * Arguments    : object player - the player who did the quest
 *                int    exp    - the experience gained
 *                string name   - the name of the item returned
 *                int    final  - true if this is the final quest
 *                                reward so we can write to a special
 *                                log also. (default = 0)
 */
nomask varargs void
log_quest(object player, int exp, string name, int final = 0)
{
    write_file(HERB_QUEST_LOG, sprintf("%s %-20s %-12s (%3d) %6d\n",
        ctime(time()),
        ((strlen(name) > QUEST_STRLEN) ? name[0..(QUEST_STRLEN - 1)] : name ),
        (string)player->query_name(),
        (int)VENDOR->get_info(QUEST_FILE(player->query_name()), "h_repeats"),
        exp));

    if (final)
    {
        write_file(HERB_FINAL_LOG, sprintf("%s %-12s (%30s)\n",
            ctime(time()),
            (string)player->query_name(),
            "Finished Final Herb Quest"));
    }
} /* log_quest */


/*
 * Function name:        add_quickness_reward
 * Description  :        Give the player a haste boost for 24 hours
 *                       as a reward for the quest.
 * Arguments    :        object who - the player
 */
public void
add_quickness_reward(object who)
{
    object  haste_ob;

    haste_ob = clone_object(OBJ_DIR + "herb_quickness_effect");

    haste_ob->move(who);

    haste_ob->set_effect_caster(who);
    haste_ob->set_effect_target(who);
    haste_ob->set_maintain_mana(0);
    haste_ob->set_spell_effect_input(11);
    haste_ob->setup_spell_effect();

} /* add_quickness_reward */
