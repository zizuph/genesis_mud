/*
 *  /d/Sparkle/area/city/obj/questvendor.c
 *
 *  This is code that represents vendors who show up one day a week in
 *  Sparkle to offer a random quest to players. The idea is simple.
 *  This quest represents a very large amount of quest experience that
 *  can be rewarded over time to players. The idea is to make it about
 *  the same size as the largest quests currently in the game (zodiac,
 *  torque, etc - lets say around 50,000 quest experience points.)
 *  However, this quest experience is not handed out all at once.
 *  Rather, once a week, the Market vendors come to town to sell and
 *  buy wares. They will advertise the need for a particular item in
 *  a particular quantity. By bringing that quantity to the vendors
 *  of the particular item, the player is awarded 100 quest experience.
 *  They then must wait another week before the vendors return to town
 *  to do the quest again. The quest will be randomized with a very
 *  large number of items that can be found throughout the game, so it
 *  is unlikely that the quest will be the same from week to week.
 *
 *  Since we are putting a cap on the amount of experience that can
 *  be gained from doing this quest at 50,000, and each individual
 *  reward at 100, this means that a player can do the quest 500 times
 *  for quest experience. At once per week, this would take roughly
 *  ten years to accomplish. Once the max has been achieved, the
 *  quest will cease to give out quest experience, and give out general
 *  experience instead.
 *
 *  Created February 2008, by Gorboth (Cooper Sherry)
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>

#include "/d/Sparkle/sys/quests.h"
#include "../defs.h"

/* Global Variables */
/* Please keep these tasks arranged alphabetically! */
public mixed *Kiosk_Tasks = 
                       ({                              
                          ({ "acorn", 1 }),               
                          ({ "ale", 30 }),                
                          ({ "amulet", 2 }),              
                          ({ "apple", 5 }),               
                          ({ "apron", 1 }),               
                          ({ "arrow", 30 }),              
                          ({ "axe", 30 }),                
                                                          
                          ({ "baldric", 1 }),             
                          ({ "ball", 1 }),                
                          ({ "banana", 1 }),              
                          ({ "bandana", 3 }),             
                          ({ "basket", 1 }),              
                          ({ "battleaxe", 5 }),           
                          ({ "belt", 3 }),                
                          ({ "berry", 20 }),              
                          ({ "blouse", 1 }),              
                          ({ "book", 2 }),                
                          ({ "boot", 5 }),                
                          ({ "bow", 5 }),                 
                          ({ "bracelet", 2 }),            
                          ({ "bread", 5 }),               
                          ({ "breastplate", 5 }),         
                          ({ "broom", 1 }),               
                                                          
                          ({ "cape", 1 }),                
                          ({ "chainmail", 5 }),           
                          ({ "claymore", 5 }),            
                          ({ "cleaver", 2 }),             
                          ({ "cloak", 10 }),              
                          ({ "club", 30 }),               
                          ({ "chalice", 1 }),             
                          ({ "cheese", 1 }),              
                          ({ "cheesecake", 1 }),          
                          ({ "clover", 4 }),              
                          ({ "coconut", 1 }),             
                          ({ "codpiece", 1 }),            
                          ({ "cognac", 1 }),              
                          ({ "cologne", 1 }),             
                          ({ "comb", 1 }),                
                          ({ "corslet", 5 }),             
                          ({ "crown", 2 }),               
                          ({ "cutlass", 3 }),             
                                                          
                          ({ "dagger", 20 }),             
                          ({ "dirk", 1 }),                
                          ({ "driftwood", 1 }),           
                          ({ "drum", 1 }),                
                                                          
                          ({ "egg", 10 }),                
                          ({ "eggplant", 1 }),            
                          ({ "eyepatch", 1 }),            
                                                          
                          ({ "feather", 2 }),             
                          ({ "fish", 5 }),                
                          ({ "flamberge", 3 }),           
                          ({ "flower", 20 }),             
                          ({ "flute", 1 }),               
                          ({ "fork", 3 }),                
                                                          
                          ({ "gem", 30 }),                
                          ({ "gladius", 1 }),             
                          ({ "glaive", 5 }),              
                          ({ "glasses", 1 }),             
                          ({ "glove", 5 }),               
                          ({ "gorget", 1 }),              
                                                          
                          ({ "hat", 10 }),                
                          ({ "halberd", 10 }),            
                          ({ "hammer", 2 }),              
                          ({ "harmonica", 1 }),           
                          ({ "harp", 1 }),                
                          ({ "hatchet", 5 }),             
                          ({ "helmet", 10 }),             
                          ({ "honneycomb", 1 }),          
                          ({ "hood", 1 }),                
                          ({ "horseshoe", 1 }),           
                                                          
                          ({ "jerky", 3 }),               
                                                          
                          ({ "kettle", 1 }),              
                          ({ "key", 3 }),                 
                          ({ "kilt", 1 }),                
                                                          
                          ({ "ladder", 1 }),              
                          ({ "lamp", 10 }),               
                          ({ "lance", 5 }),               
                          ({ "lobster", 1 }),             
                          ({ "loincloth", 1 }),           
                          ({ "longsword", 5 }),           
                                                          
                          ({ "mace", 10 }),               
                          ({ "marble", 1 }),              
                          ({ "mattock", 5 }),             
                          ({ "medallion", 10 }),          
                          ({ "mint", 3 }),                
                          ({ "monacle", 1 }),             
                          ({ "morningstar", 10 }),        
                                                          
                          ({ "necklace", 3 }),            
                                                          
                          ({ "oar", 3 }),                 
                          ({ "onion", 5 }),               
                                                          
                          ({ "parchment", 2 }),           
                          ({ "pelt", 10 }),               
                          ({ "pickaxe", 1 }),             
                          ({ "pie", 10 }),                
                          ({ "pillow", 1 }),              
                          ({ "pitchfork", 1 }),           
                          ({ "plate", 10 }),              
                          ({ "poleaxe", 5 }),             
                          ({ "potato", 5 }),              
                          ({ "pumpkin", 1 }),             
                                                          
                          ({ "quarterstaff", 2 }),        
                          ({ "quill", 1 }),               
                          ({ "quiver", 2 }),              
                                                          
                          ({ "rapier", 1 }),              
                          ({ "ring", 5 }),                
                          ({ "rope", 5 }),                
                                                          
                          ({ "saber", 3 }),               
                          ({ "salmon", 1 }),              
                          ({ "sandal", 2 }),              
                          ({ "sardine", 1 }),             
                          ({ "sash", 1 }),                
                          ({ "sausage", 5 }),             
                          ({ "scepter", 1 }),             
                          ({ "scimitar", 5 }),            
                          ({ "scroll", 3 }),              
                          ({ "shell", 3 }),               
                          ({ "shield", 25 }),             
                          ({ "shirt", 5 }),               
                          ({ "shoe", 4 }),                
                          ({ "shovel", 5 }),              
                          ({ "spear", 15 }),              
                          ({ "spoon", 3 }),               
                          ({ "staff", 1 }),               
                          ({ "steak", 5 }),               
                          ({ "stiletto", 1 }),            
                          ({ "sword", 30 }),              
                                                          
                          ({ "tomato", 1 }),              
                          ({ "toothbrush", 1 }),          
                          ({ "toothpick", 1 }),           
                          ({ "torch", 15 }),              
                          ({ "tunic", 3 }),               
                                                          
                          ({ "vest", 5 }),                
                          ({ "vodka", 1 }),               
                                                          
                          ({ "wand", 1 }),                
                          ({ "whip", 1 }),                
                          ({ "whiskey", 15 }),            
                      });

/* Definitions */
#define  QUEST_STRLEN 16
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


/* Prototypes */
public void          create_object();
public string        exa_kiosk();
public void          init();
public int           read_poster(string arg);
public int           do_deliver(string arg);
public int           claim_reward(string arg);
public void          tally_results();
public int           perform_inquiry(string arg);
public void          goodbye();
public void          day_check();
nomask varargs void  log_quest(object player, int exp, string name);


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("market");

    add_name( ({ MARKETDAY + "market", VENDORNAME }) );
    set_adj( ({ "large", "outdoor" }) );

    set_short("large outdoor market");
    set_long("Every corner of Market Square is crowded with vendors who"
      + " have set up shop today to buy and sell goods to would-be"
      + " customers. They show up every " + MARKETDAY + ", offering"
      + " their unique services to travellers and citizens alike. You"
      + " notice a large kiosk that has been set up in the middle"
      + " of the square between vending stations.\n");

    add_prop(OBJ_M_NO_GET, "Surely, you jest.\n");
    add_prop(OBJ_I_WEIGHT, 10000000);
    add_prop(OBJ_I_VOLUME, 10000000);

    add_item( ({ "kiosk", "large kiosk" }), exa_kiosk);
    add_item( ({ "vendor", "vendors", "merchant", "merchants" }),
        "Most of the merchants are middle-aged men with rough hands,"
      + " long beards, and kind eyes. They stand proudly over their"
      + " wares, looking for people who will take an interest in their"
      + " merchandise. Only a few of the vendors seem to be women.\n");
    add_item( ({ "men", "man", "male vendor", "male vendors",
                 "male merchant", "male merchants" }),
        "Yes, most of the vendors are male. You do notice a few women"
      + " behind the tables, though.\n");
    add_item( ({ "women", "woman", "female vendor", "female vendors",
                 "female merchant", "female merchants" }),
        "The few female vendors have placed their tables beside one"
      + " another. Most of their wares seem to be jewelry and"
      + " luxuries.\n");
    add_item( ({ "jewel", "jewels", "jewelry", "luxuries" }),
        "The women seem to be the ones handling those sorts of"
      + " items at this market.\n");
    add_item( ({ "table", "tables" }),
        "Tables are set up all around the square, each one displaying"
      + " the wares of a particular vendor. They are crowded together"
      + " almost to the point where it is difficult to know where one"
      + " merchant's goods end and another's begin.\n");
    add_item( ({ "ware", "wares", "good", "goods", "merchandise" }),
        "It seems as if one could find just about anything at this"
      + " market. The goods on display represent everything from"
      + " the everyday tool to the exotic spice. Some merchants seem"
      + " more interested in buying than selling, though. Perhaps"
      + " you could find out more about that on the kiosk.\n");
    add_item( ({ "tool", "tools", "everyday tool", "everyday tools", }),
        "There are tools on display at numerous locations around the"
      + " square. Some look familiar while others are quite unlike"
      + " those normally found in a household.\n");
    add_item( ({ "familiar tool", "familiar tools" }),
        "Yep. Quite familiar.\n");
    add_item( ({ "unfamiliar tool", "unfamiliar tools" }),
        "Hmmm ... never seen that one before!\n");
    add_item( ({ "spice", "spices", "exotic spice", "exotic spices" }),
        "Some of the spices have names you have never heard before,"
      + " others are quite mundane.\n");
    add_item( ({ "middle-aged men", "middle aged men",
                 "middle-aged man", "middle aged man" }),
        "They are probably about forty-five years old.\n");
    add_item( ({ "vending station", "vending stations", "station",
                 "stations" }),
        "The stations are mostly tables which have been set up around"
      + " the square. In the midst of it all, a large kiosk has been"
      + " erected to advertise the items the vendors are interested"
      + " in purchasing today.\n");

    add_cmd_item( ({ "vendor", "vendors", "merchant", "merchants", }),
                  ({ "kill" }),
        "Too many witnesses.\n");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        exa_kiosk
 * Description  :        provide text and quest information unique
 *                       for each player that examines it, based on
 *                       each player's datafile.
 * Returns      :        string - the text for the kiosk
 */
public string
exa_kiosk()
{
    string    name = this_player()->query_name(),
              date = TIME2FORMAT(time(), "yyyymmdd"),
              v_item,
             *old_array = VENDOR->get_info(CURRENT_QUESTS, "unfinished"),
             *new_array = allocate(sizeof(old_array) + 1);
    mixed    *task = one_of_list(Kiosk_Tasks);
    int       num,
              remaining,
              returned,
              i = 0;

    /* If the date on the old quest assignment isn't the same as the
     * date today for this player, they must be looking at the kiosk
     * in a new week, so we assign them a new quest.
     */
    if (VENDOR->get_info(QUEST_FILE(name), "day") != date)
    {
        VENDOR->set_info(QUEST_FILE(name), "day",  date);
        VENDOR->set_info(QUEST_FILE(name), "done", "no");
        VENDOR->set_info(QUEST_FILE(name), "item", task[0]);
        VENDOR->set_info(QUEST_FILE(name), "returned", 0);
        VENDOR->set_info(QUEST_FILE(name), "num",  task[1]);

        /* Now we need to declare this an unfinished task in our
         * tracking system so we can see if some quests never get
         * solved, and are thus too hard.
         */
        foreach (string s: old_array)
        {
            new_array[i] = s;
            i++;
        }

        new_array[sizeof(old_array)] = task[0];

        VENDOR->set_info(CURRENT_QUESTS, "unfinished", new_array);

        /* And here we need to keep track of how many times this
         * particular quest has been assigned, to compare to how
         * many times it has been successfully solved (or failed.)
         */
        i = VENDOR->get_info(QUEST_ASSIGNED, task[0]);
        i++;
        VENDOR->set_info(QUEST_ASSIGNED, task[0], i);
    }

    v_item = VENDOR->get_info(QUEST_FILE(name), "item");
    returned = VENDOR->get_info(QUEST_FILE(name), "returned");
    num = VENDOR->get_info(QUEST_FILE(name), "num");

    remaining = num - returned;

    if (VENDOR->get_info(QUEST_FILE(name), "done") == "yes")
    {
        return "You look over the kiosk, but don't see anything of"
          + " particular interest. Perhaps next week there will be"
          + " more for you to do here.\n";
    }

    if (!remaining)
    {
        return "Looking over the kiosk, you realize that you could"
          + " probably <claim> a reward from the vendors now. You"
          + " seem to have done everything that they have asked"
          + " for.\n";
    }

    return "Looking over the kiosk, you are able to glean that the"
      + " merchants wish to acquire " + LANG_NUM2WORD(remaining)
      + " more " + ((remaining > 1) ? LANG_PWORD(v_item) : v_item)
      + ". A meaningful reward will be"
      + " given to the person who can complete this task for them.\n\n"
      + "You also notice a poster with instructions on the kiosk.\n";
} /* exa_kiosk */


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
        + "\t|        Instructions for dealing with the Vendors       |\n"
        + "\t|                                                        |\n"
        + "\t|  <deliver x>    - Give a desired item to the vendors.  |\n"
        + "\t|  <claim reward> - Receive payment for fulfilling the   |\n"
        + "\t|                   requests of the vendors.             |\n"
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
              v_item = VENDOR->get_info(QUEST_FILE(name), "item");
    object   *objs;
    int       num = VENDOR->get_info(QUEST_FILE(name), "num"),
              returned = VENDOR->get_info(QUEST_FILE(name), "returned"),
              remaining,
              delivered = 0,
              heap_amount;

    day_check();

    if (!strlen(arg))
    {
        notify_fail("What do you wish to deliver to the vendors?\n");
        return 0;
    }

    if (VENDOR->get_info(QUEST_FILE(name), "day") != date)
    {
        notify_fail("You'd better check the kiosk to make sure you"
          + " know what the vendors are in the market for first.\n");
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
    if (VENDOR->get_info(QUEST_FILE(name), "done") == "yes")
    {
        write("The vendors do not seem to need any more "
          + LANG_PWORD(v_item) + " but they thank you for your hard"
          + " work once again.\n");
       return 1;
    }

    /* Has the player already returned the necessary number of items,
     * but not yet claimed their reward?
     */
    if (returned >= num)
    {
        write("The vendors smile at you, and one proclaims: \"You are"
          + " an overachiever, my friend! We need no more from you."
          + " Please, <claim> your reward that we might repay your"
          + " hard work.\"\n");
        return 1;
    }

    foreach (object obj: objs)
    {
        if (!obj->id(v_item))
        {
            notify_fail("The vendors are not in the market for that item.\n");
            continue;
        }
        /* We can't allow players to discard things they shouldn't be able to!
         */
        if (obj->query_auto_load() ||
            obj->query_prop(OBJ_M_NO_DROP))
        {
            notify_fail("No ... that item cannot leave you.\n");
            continue;
        }
        
        /* Now to remove the object from the inventory of the player. If the
         * object in question is a heap object, we have to deal with that a bit
         * differently.
         */
        if (IS_HEAP_OBJECT(obj))
        {
            remaining = num - returned;
            heap_amount = obj->num_heap();
            if (heap_amount > remaining)
            {
                obj->set_heap_size(heap_amount - remaining);

                delivered += remaining;
                returned = num;
                break;
            }

            obj->remove_object();
            delivered += heap_amount;
            returned += heap_amount;
        }
        else
        {
            obj->remove_object();
            delivered++;
            returned++;
        }
    }

    if (!delivered)
    {
        return 0;
    }

    VENDOR->set_info(QUEST_FILE(name), "returned", returned);

    write("You hand " + ((delivered > 1) ?
        LANG_NUM2WORD(delivered) + " " + LANG_PWORD(v_item) :
        "a single " + v_item) + " over to the vendors.\n");

    /* Is this the final delivery for the quest? */
    if (num == returned)
    {
        write("The vendors examine your delivery and gratefully accept"
          + " it, proclaiming: \"You have done well for us! You may"
          + " now rightfully <claim> your reward!\"\n");
    }
    else
    {
        remaining = num - returned;

        if (delivered > 1)
        {
            write("The vendors examine each of your deliveries in turn,"
              + " and gratefully accept them. One says: \"Ah! These are"
              + " some very fine " + LANG_PWORD(v_item) + " you have"
              + " brought us. Excellent. Now we need but "
              + LANG_NUM2WORD(remaining) + " more. ");
        }
        else
        {
            write("The vendors examine your delivery and gratefully"
              + " accept it. One says: \"Ah! A very fine " + v_item 
              + " you have brought us. Excellent. Now we need but "
              + LANG_NUM2WORD(remaining) + " more. ");
        }

        write("Bring us " + ((remaining > 1) ? "these" : "this")
          + " and we will reward you!\n");
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
    mixed    *quest_arr = VENDOR->get_info(CURRENT_QUESTS, "unfinished");
    string    name = this_player()->query_name(),
              date = TIME2FORMAT(time(), "yyyymmdd"),
              v_item = VENDOR->get_info(QUEST_FILE(name), "item"),
             *new_arr = allocate(sizeof(quest_arr));
    int       num = VENDOR->get_info(QUEST_FILE(name), "num"),
              returned = VENDOR->get_info(QUEST_FILE(name), "returned"),
              repeats = VENDOR->get_info(QUEST_FILE(name), "repeats"),
              remaining,
              arr_point,
              reward = this_player()->query_exp(),
              exp = SPARKLE_VENDOR_EXP,
              group = SPARKLE_VENDOR_GROUP,
              bit = SPARKLE_VENDOR_BIT;
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

    if (VENDOR->get_info(QUEST_FILE(name), "day") != date)
    {
        notify_fail("You have yet to even check the kiosk, let alone"
          + " assist the vendors! They owe you nothing.\n");

        return 0;
    }

    if (VENDOR->get_info(QUEST_FILE(name), "done") == "yes")
    {
        notify_fail("The vendors smile politely at you, and one"
          + " proclaims: \"My friend, you have already received your"
          + " reward. Come see us next week and we may have more"
          + " need of your services.\"\n");

        return 0;
    }

    if (returned >= num)
    {
        write("At your request, the vendors quietly deliberate over"
          + " what reward you are due. At last, one proclaims: \"Yes,"
          + " my friend, we are indeed in your debt. Accept this"
          + " reward for your hard work!\"\n");

        repeats++;
        VENDOR->set_info(QUEST_FILE(name), "repeats", repeats);
        VENDOR->set_info(QUEST_FILE(name), "done", "yes");

        if (this_player()->test_bit(getuid(), group, bit))
        {
            write("The vendors hand you some valuable gems.\n"
              + "You don't feel any more experienced, though. Perhaps"
              + " you have learned all you can by helping the"
              + " vendors. In any case, you are a bit richer now!\n");
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

            if (MAX_REPEATS - 
                VENDOR->get_info(QUEST_FILE(name), "repeats") == 1)
            {
                this_player()->set_bit(group, bit);

                /* Lets capitalize it so it is highlighted in the log
                 * when a player completes it for the final quest 
                 * reward.\n");
                 */
                log_quest(this_player(), reward, capitalize(v_item));
            }
            else
            {
                log_quest(this_player(), reward, v_item);
            }

            this_player()->add_exp_quest(reward);
            this_player()->catch_tell("You feel more experienced!\n");

        }

        /* Well, they solved it, so we should remove this quest item
         * from the array of unsolved items that we are keeping track
         * of for logging purposes.
         */
        arr_point = member_array(v_item, quest_arr);

        if (arr_point > -1)
        {
            new_arr = exclude_array(quest_arr, arr_point, arr_point);
            VENDOR->set_info(CURRENT_QUESTS, "unfinished", new_arr);
        }

        /* We will also now increase the tally for this particular
         * item on the number of times it has been solved. Since its
         * not being used anymore, we'll use the arr_point variable
         * for our new purposes.
         */
        arr_point = VENDOR->get_info(QUEST_SUCCESSES, v_item);
        arr_point++;
        VENDOR->set_info(QUEST_SUCCESSES, v_item, arr_point);

        day_check();

        return 1;
    }

    remaining = num - returned;

    write("The vendors smile politely at you, and one proclaims: "
      + "\"We are still in need of " + LANG_NUM2WORD(remaining)
      + " more " + ((remaining > 1) ? LANG_PWORD(v_item) : v_item)
      + ". We are in no position to reward you until we have"
      + " received the full amount.\"\n");

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
    string *quests = VENDOR->get_info(CURRENT_QUESTS, "unfinished");
    int     num = 0;

    /* Here we increase the tally for all quests that remain unfinished
     * this week.
     */
    foreach (string quest: quests)
    {
        num = VENDOR->get_info(QUEST_FAILURES, quest);
        num++;
        VENDOR->set_info(QUEST_FAILURES, quest, num);
    }

    /* Now we need to wipe out the current quests listed in the
     * datafile.
     */
    VENDOR->set_info(CURRENT_QUESTS, "unfinished", ({}));
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

    successes = VENDOR->get_info(QUEST_SUCCESSES, v_item);
    failures = VENDOR->get_info(QUEST_FAILURES, v_item);
    assigned = VENDOR->get_info(QUEST_ASSIGNED, v_item);

    if (!assigned)
    {
        write("The vendors, mildly annoyed by your request, take out"
          + " their records and begin pouring over many pieces of"
          + " tattered parchment. After much arguing amongst themselves,"
          + " one peers at you and proclaims, \"We have never given"
          + " such a task to anyone!\"\n");
        return 1;
    }

    write("The vendors, mildly annoyed by your request, take out their"
      + " records and begin carefully sifting through many pieces of"
      + " tattered parchment. Eventually, they all nod at one another"
      + " and one proclaims, \"We have given out that task "
      + LANG_NUM2WORD(assigned) + " " + ((assigned > 1) ? "times" :
        "time") + ". ");

    if (successes)
    {
        if (successes > 1)
        {
            write("There have been " + LANG_NUM2WORD(successes)
              + " successes, and ");
        }
        else
        {
            write("There has been one success, and ");
        }
    }
    else
    {
        write("None have been successful, and ");
    }

    if (failures)
    {
        if (failures > 1)
        {
            write(LANG_NUM2WORD(failures) + " failures.");
        }
        else
        {
            write("one failure.");
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
        "Suddenly, without warning, the vendors begin boxing up their"
      + " wares and packing in all of their belongings. They swiftly"
      + " load everything onto their carts and wagons, and in an"
      + " impressive display of organization swiftly depart, leaving"
      + " the square quite clean of any debris. As they wind down the"
      + " road out of sight, one of the vendors turns and calls, \""
      + "We will be back next " + MARKETDAY + ", my friends! Come and"
      + " find us again then!\"\n");

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
    if (ctime(time())[0..2] != MARKETDAY[0..2])
    {
        set_alarm(1.0, 0.0, goodbye);
    }
} /* day_check */


/*
 * Function name: log_quest
 * Description  : This function makes the log of a quest when it is
 *                solved and is placed here to make a uniform log-format.
 * Arguments    : player - the player who did the quest
 *                exp    - the experience gained
 *                name   - the name of the item returned
 */
nomask varargs void
log_quest(object player, int exp, string name)
{
    write_file(VENDOR_QUEST_LOG, sprintf("%s %-20s %-12s (%3d) %6d\n",
        ctime(time()),
        ((strlen(name) > QUEST_STRLEN) ? name[0..(QUEST_STRLEN - 1)] : name ),
        (string)player->query_name(),
        (int)VENDOR->get_info(QUEST_FILE(player->query_name()), "repeats"),
        exp));
} /* log_quest */