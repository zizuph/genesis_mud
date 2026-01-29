/*
 *  /d/Emerald/common/guild/aod/rooms/forge.c
 *
 *  This is the Forge for the Army of Darkness. This is earned when
 *  they have collected either enough elf or dwarf skulls to get a
 *  skilled artisan working the equipment.
 *
 *  Copyright (C) July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";
inherit "/lib/shop";
inherit "/lib/trade";

#include <cmdparse.h>  /* for NORMAL_ACCESS    */
#include <language.h>  /* for LANG_ADDART      */
#include <macros.h>    /* for CAN_SEE          */
#include <money.h>     /* for MONEY_TEXT_SPLIT */
#include <time.h>      /* for TIME2FORMAT      */
#include <wa_types.h>  /* for W_BOTH, TS_CHEST */

#define            DEAL_FACTOR        2
#define            TRAINER            AOD_NPC_DIR + "forge_ogre"
#define            NORMAL_SCRAP       1
#define            EXCELLENT_SCRAP    2
#define            ACCEPTABLE_METALS ({ "iron",             \
                                        "steel",            \
                                        "bronze",           \
                                        "tempered-steel",   \
                                        "gold",             \
                                        "golden",           \
                                        "silver",           \
                                        "copper",           \
                                        "platinum",         \
                                        "metal",            \
                                        "metallic",         \
                                        "brass",            \
                                        "titanium",         \
                                        "orichalcum",       \
                                        "mithril",          \
                                        "adamantite",       \
                                        "adamant",          \
                                        "adamantium",       \
                                        "electrum",         \
                                        "lead",             \
                                        "leaden",           \
                                        "tempered-iron",    \
                                        "tempered-bronze",  \
                                        "tempered-copper",  \
                                        "tempered-platinum",\
                                        "tempered-mithril", \
                                        "tempered-lead",    \
                                     })
#define            MAGIC_REJECTS     ({                        \
                     "/d/Sparkle/area/faerie/arm/e_chainmail", \
                                     })
#define            FORGE_WEP_CREDITS  ({  5, 10, 15, 20,   \
                                         25, 30, 35, 40,   \
                                         45, 50,           \
                                      })
#define            FORGE_ARM_CREDITS  ({ 20, 10, 15, 35,   \
                                         20, 30, 40, 25,   \
                                         35, 45, 50, 30    \
                                      })
#define            FORGE_WEP_PRICES   ({  60,               \
                                          144,              \
                                          720,              \
                                          1728,             \
                                          8640,             \
                                          17280,            \
                                          43200,            \
                                          86400,            \
                                          172800,           \
                                          172800,           \
                                      })
#define            FORGE_ARM_PRICES   ({  720,              \
                                          720,              \
                                          1440,             \
                                          3456,             \
                                          1728,             \
                                          5184,             \
                                          17280,            \
                                          129600,           \
                                          172800,           \
                                          172800,           \
                                          172800,           \
                                          172800,           \
                                      })
#define        WEP_SHORTS ( ({ "twisted sheet of scrap iron",  \
                               "crude iron post",              \
                               "heavy iron bar",               \
                               "huge iron rod",                \
                               "great iron hammer",            \
                               "colossal spiked morningstar",  \
                               "darksteel face mallet",        \
                               "darksteel head spiker",        \
                               "darksteel death stick",        \
                               "sledgehammer of the colossus", \
                            }) )
#define        ARM_SHORTS ( ({ "crude slab of scrap metal",     \
                               "huge iron can",         \
                               "dented iron tubs",             \
                               "enormous curtain of ringmail", \
                               "monstrous iron skullcap",      \
                               "gigantic chain leggings",   \
                               "darksteel ogre breastplate",   \
                               "darksteel troll bracers",      \
                               "darksteel goliath helm",       \
                               "titan's darksilver greaves", \
                               "deathplate of the behemoth",         \
                               "vast darksilver arm-bands",     \
                            }) )

/* Prototypes */
public void        create_cave_room();
public string      describe();
public void        init();
public int         do_melt(string arg);
public string     *strip_punc(mixed str_arr);
public void        scrap_item(object obj, object who);
public void        list_credits(object who);
public mixed       trainer_present();
public void        make_trainer();
public void        reset_room();
public int         forge_list(string arg);
public void        list_weapons(object player);
public void        list_armour(object player);
public void        check_armament(int armour = 0);
public int         forge_buy(string arg);
object *           buy_it(object *ob, string str2, string str3);
public int         forge_allow(string arg);

/* Global variables */
public mixed       Trainer;
public string      Trainer_Id = "_aod_forge_ogre";
public int         Armament = 0; /* what armament is available? */


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("the forge for the Army of Darkness");
    set_em_long("@@describe@@");

    add_item( ({ "here", "area", "cave", "cavern", "huge cavern" }),
        "Even though this cavern is massive, the feeling here is rather"
      + " cramped due to the piles of metal that are strewn around the"
      + " floor.\n");
    add_item( ({ "forge" }),
        "Truly, this is a forge run for and by Ogres. Everything here is"
      + " positively huge!\n");
    add_item( ({ "pile", "piles", "pile of scrap", "piles of scrap",
                 "huge pile of scrap", "huge piles of scrap", "huge pile",
                 "huge piles", "metal", "scrap pile", "scrap piles",
                 "piles of metal", "pile of metal" }),
        "Though the piles of scrap appear little more than carelessly"
      + " heaped hunks of metal and broken gear, they have definitely"
      + " been sorted according to the type of metal involved. Even"
      + " Ogres, it seems, can learn the basics of blacksmithing."
      + " A monstrous anvil rises amid the piles.\n");
    add_item( ({ "anvil", "monstrous anvil" }),
        "This anvil is almost six feet in height and must way dozens of"
      + " tons. Various tools are leaning against its base.\n");
    add_item( ({ "base", "base of the anvil", "anvil base" }),
        "Tools are leaning against it.\n");
    add_item( ({ "tools", "various tools", "tong", "tongs" }),
        "They are leaning against the base of the anvil.\n");
    add_item( ({ "pot", "melting pot", "fluid", "metalurgical fluid",
                 "melted metal" }),
        "The melting pot of this forge is a rather ominous sight. It"
      + " hangs suspended above intensely hot flames which do quite"
      + " an effective job keeping the thing hot enough to melt down"
      + " even the most stubborn substances. Were this to suddenly"
      + " tip over ... well, best not to think about it.\n");
    add_item( ({ "coal", "coals", "magic coal", "magic coals",
                 "purple flame", "purple flames", "magically burning coal",
                 "magically burning coals", "spark", "sparks",
                 "purple spark", "purple sparks" }),
        "The coals which heat the melting pot are clearly of some magic"
      + " origin. Perhaps the Darklings have assisted with this process,"
      + " for rather than the normal orange and yellow of a typical"
      + " plasma, these flames jump and dance with purple sparks!\n");
    add_item( ({ "hole", "large hole", "flames", "flame" }),
        "Every so often, flames burst from a hole in the cavern wall with"
      + " a deafening roar. You can see strange glowing metal inside that"
      + " hole, buzzing with a magic aura.\n");
    add_item( ({ "strange glowing metal", "strange metal",
                 "glowing metal" }),
        "You really don't understand what you are seeing inside that"
      + " hole. You do, however, know for a fact that you don't want to"
      + " get anywhere near it!\n");
    add_item( ({ "corridor", "tunnel", "west" }),
        "To the west, a corridor leads out of the forge.\n");
    add_item( ({ "ground", "floor", "down" }),
        "The floor of the cavern is littered with piles of scrap metal,"
      + " leaving surprisingly little room for walking space.\n");
    add_item( ({ "wall", "walls", "cavern wall", "cavern walls",
                 "walls of the cavern", "shadow", "shadows" }),
        "Shadows dance along the walls of the cavern which are eerily"
      + " lit by the bright flames of the forge.\n");
    add_item( ({ "roof", "ceiling", "up", "chimney" }),
        "The walls of the cavern travel up beyond sight, perhaps"
      + " forming a tall chimney allowing the fumes of the forge to"
      + " escape through some distant opening in the top of the"
      + " mountain.\n");

    add_exit("tunnel3", "west");
    add_spike("forge");

    check_armament();
    config_default_trade();

    reset_room();
} /* create_cave_room */

 
/*
 * Function name:        describe
 * Description  :        provide text for the long description which is
 *                       state dependant.
 * Returns      :        string - the long description text
 */
public string
describe()
{
    string dtxt;

    dtxt = "You stand in a huge cavern that the Army of Darkness uses"
      + " as a forge. Huge piles of scrap containing all types of metal"
      + " are heaped around the floor. In the middle of the piles,"
      + " suspended over some sort of magically burning coals of intense"
      + " heat is a positively enormous melting pot, which bubbles with"
      + " metalurgical fluid. Flames spout from a large hole in one"
      + " of the cavern walls where it appears as if some other melting"
      + " process must take place. ";

    if (this_player()->query_guild_name_occ() == GUILD_NAME)
    {
        dtxt += "You may use <ogghelp forge> to receive information on"
          + " the function of this place. If you have any metal armours"
          + " or weapons you have collected you can try to <scrap> them"
          + " here for credit. You can also get a <forgelist>"
          + " here of 'credits', 'armours', or 'weapons'. ";
    }

    dtxt += "A corridor leads out of the cavern to the west.";

    return dtxt + "\n";
} /* describe */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_melt, "scrap");
    add_action(forge_list, "list");
    add_action(forge_list, "forgelist");
    add_action(forge_buy, "buy");
    add_action(forge_allow, "allow");
} /* init */


/*
 * Function name:        do_melt
 * Description  :        Allow the player to try to melt down any
 *                       armours and weapons that he finds for forge
 *                       credits
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 -- success, 0 -- failure
 */
public int
do_melt(string arg)
{
    mixed  *obj;
    int     i,
            instances;
    object  npc_trainer; 

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i [in] [the] [forge]", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {

        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    this_player()->reveal_me(1);
    if (!objectp(npc_trainer = present(Trainer_Id, this_object())))
    {
        write("There is no one present who can help you do that.\n");
        return 1;
    }

    if (!CAN_SEE(npc_trainer, this_player()))
    {
        write("The " + npc_trainer->query_nonmet_name()
         + " cannot see you to help you do that!\n");
        return 1;
    }
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
    {
        write(NPC + " bellows: What?! Who you??"
          + " FORGE ONLY FOR ARMY!!!\n");
        if (this_player()->query_wiz_level())
            write(NPC + " bellows: Hmm... You look like boss."
                      + " Me scrap for you.\n");
        else
            return 1;
    }

    if (!obj[0]->check_weapon() && !obj[0]->check_armour())
    {
        notify_fail(NPC + " bellows: What this?! Not weapon."
          + " Not armour. ME NOT MELT!\n");
        return 0;
    }

    if (obj[0]->id(AOD_FORGED_ITEM))
    {
        notify_fail(NPC + " bellows: YOU STUPID! NOT MELT DOWN"
          + " THIS! IT MADE IN FORGE!\n");
        return 0;
    }

    if (obj[0]->query_prop(AOD_RACK_ITEM))
    {
        if (!obj[0]->query_prop(OBJ_I_BROKEN))
        {
            notify_fail(NPC + " bellows: NO! YOU NASTY PULP PACK!"
              + " NOT STEAL FROM DROPROOM TO MELT DOWN!! PULP! PULP!!"
              + " PULP!!!\n");
            npc_trainer->command("kill " + this_player()->query_real_name());
            return 0;
        }
    }

    if (obj[0]->query_auto_load() ||
        obj[0]->query_prop(OBJ_M_NO_DROP))
    {
        notify_fail(NPC + " bellows: You want scrap "
          + obj[0]->short() + "??? Me not think you do!\n");
        return 0;
    }

    if (obj[0]->query_worn() ||
        obj[0]->query_wielded())
    {
        notify_fail(NPC + " bellows: You want me scrap it? Good. First"
          + " you NOT WIELD OR WEAR IT!!!\n");
        return 0;
    }

    for (i = 0; i < sizeof(ACCEPTABLE_METALS); i++)
    {
        if (member_array(ACCEPTABLE_METALS[i],
                strip_punc(explode(obj[0]->short(), " "))) != -1 ||
            member_array(ACCEPTABLE_METALS[i],
                strip_punc(explode(obj[0]->long(), " "))) != -1 ||
            member_array(ACCEPTABLE_METALS[i],
                obj[0]->query_adj(1)) != -1)
        {
            write(NPC + " bellows: Hmm ... what this ...\n");
            scrap_item(obj[0], this_player());
            return 1;
        }
    }
    
    i = METAL_MASTER->get_info("forge_allow",
        MASTER_OB(obj[0]));
    
    switch (i)
    {
    case 1:     // Allowed
        write(NPC + " bellows: Hmm ... what this ...\n");
        scrap_item(obj[0], this_player());
        return 1;
    
    case 0:     // Not seen before, no idea
        notify_fail(NPC + " bellows: Uhhh ... me not see good"
          + " metal to melt. Maybe me too stupid, but it not obvious if"
          + " it there. Bring back later, maybe then I know.\n");
        
         METAL_MASTER->set_info("forge_allow", MASTER_OB(obj[0]),
            666 );    
         break;           

    case 666:     // Seen before, still not sure
        notify_fail(NPC + " bellows: I see this before. What this?"
          + " Still not know if this good metal. You bring back"
          + " later.\n");
        break;           

    case -1:      // Not allowed
        notify_fail(NPC + " bellows: What you call this?"
          + " THIS NOT METAL! You try trick??\n");
        break;
    }
    
    /* I'm going to keep track of these weapons, and fix them as I'm
     * able.
     */
    instances  = METAL_MASTER->get_info("forge_rejects",
        MASTER_OB(obj[0]));
    instances ++;

    if (this_player()->query_guild_name_occ() == GUILD_NAME)
        METAL_MASTER->set_info("forge_rejects", MASTER_OB(obj[0]),
            instances );

    return 0;
} /* do_melt */



/*
 * Function name:       strip_punc
 * Description  :       take an array of strings, and strip each
 *                      of trailing punctuation marks
 * Arguments:           mixed str_arr -- an array of strings
 * Returns  :           string -- the array, stripped of punctuation marks
 */
public string *
strip_punc(mixed str_arr)
{
    mixed        tmp_word = 0;
    int          i;

    for (i = 0; i < sizeof(str_arr); i++)
    {
        sscanf(str_arr[i], "%s?", tmp_word);
        sscanf(str_arr[i], "%s.", tmp_word);
        sscanf(str_arr[i], "%s,", tmp_word);
        sscanf(str_arr[i], "%s!", tmp_word);
        sscanf(str_arr[i], "%s;", tmp_word);

        if (tmp_word)
        {
            str_arr[i] = tmp_word;
        }

        tmp_word = 0;
    }

    return str_arr;
} /* strip_punc */


/*
 * Function name:        scrap_item
 * Description  :        melt the item down, and give the player the
 *                       appropriate number of forge points.
 *
 * Arguments    :        object obj -- the object to scrap
 *              :        object who -- the person scrapping it
 */
public void
scrap_item(object obj, object who)
{
    int     quality = 0,
            magical = 0;

    set_this_player(who);

    if (obj->check_weapon())
    {
        if (obj->query_hands() == W_BOTH ||
            obj->query_prop(AOD_WIELD_PROP))
        {
            quality = 2;
        }
    }
    else
    {
        if (member_array(TS_CHEST, obj->query_slots(1)) > -1)
        {
            quality = 2;
        }
    }

    if (quality < 2)
    {        
        write(NPC + " bellows: This teeny thing? Okay, me melt!\n");
    }
    else
    {
        write(NPC + " bellows: Good! This solid! Me melt!\n");
    }

    if (obj->query_prop(MAGIC_AM_MAGIC))
    {
        write(NPC + " bellows: Oho!! This magic metal!\n");

        if (AOD_MASTER->query_guild_total("elf") < AOD_RACEREWARD &&
            AOD_MASTER->query_guild_total("dwarf") < AOD_RACEREWARD)
        {
            write(NPC + " bellows: Wish me had more dwarf or elf"
              + " juice in brain. Go get more dwarf and elf heads! Then"
              + " me know how to use magic metal for extra face"
              + " smashing!\n");
        }
        else
        {
            /* If there are certain magic items in the game that come too
             * cheaply and easily, we want to prevent them from being
             * used for magic credits here.
             */
            if (member_array(MASTER_OB(obj), MAGIC_REJECTS) == -1)
            {
                magical = 1;
            }
            else
            {
                write(NPC + " bellows: Wait ... Bosses say this thing"
                  + " not very powerful magic. Oh well, still good for"
                  + " normal scrap!\n");
            }
        }
    }

    if (magical)
    {
        write(NPC + " bellows: This go in special magic"
          + " melter pot!\n");
        write(NPC + " tosses the " + obj->short()
          + " into a firey hole in the wall. There is a flash of"
          + " magical energy as flames erupt from the hole!\n");
    }
    else
    {
        write(NPC + " tosses the " + obj->short()
          + " into a huge melting pot, where it sinks beneath"
          + " the surface of the bubbling liquid metal.\n");
    }
    
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
    {
    // We are non-guildmember wizard
        obj->move(this_object());
        obj->remove_object();       
        return; 
    }

    if (quality < 2)
    {
        write("\n" + NPC + " looks up at your picture on the wall and"
          + " scratches " + LANG_NUM2WORD(NORMAL_SCRAP) + " line next"
          + " to it" + ((magical > 0) ? " with magical glowing chalk." :
            " with a piece of chalk.") + "\n");

        if (magical)
        {
            AOD_MASTER->collect_skull(this_player(), AOD_FORGE_MAGIC,
                NORMAL_SCRAP);
        }
        else
        {
            AOD_MASTER->collect_skull(this_player(), AOD_FORGE_NORM,
                NORMAL_SCRAP);
        }
    }
    else
    {
        write("\n" + NPC + " looks up at your picture on the wall and"
          + " scratches " + LANG_NUM2WORD(EXCELLENT_SCRAP) + " lines"
          + " next to it" + ((magical > 0) ? " with magical glowing"
          + " chalk." : " with a piece of chalk.") + "\n");

        if (magical)
        {
            AOD_MASTER->collect_skull(this_player(), AOD_FORGE_MAGIC,
                EXCELLENT_SCRAP);
        }
        else
        {
            AOD_MASTER->collect_skull(this_player(), AOD_FORGE_NORM,
                EXCELLENT_SCRAP);
        }
    }

    write_file(AOD_LOG_DIR
      + ((magical == 1) ? "magic_scrap" : "norm_scrap"),
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(this_player()->query_name()) + " "
      + MASTER_OB(obj) + "("
      + ((quality < 2) ? NORMAL_SCRAP : EXCELLENT_SCRAP) + ")\n");

    obj->move(this_object());
    obj->remove_object();
//  list_credits(this_player());
} /* scrap_item */


/*
 * Function name:        list_credits
 * Description  :        Print a list of the amount of Forge credits
 *                       that the player has currently earned
 * Arguments    :        object who -- the player in question
 */
public void
list_credits(object who)
{
    set_this_player(who);

    write(sprintf("%|80s", ".---------------------------.\n"));
    write(sprintf("%|80s",
        "**********| Total Forge Credits Earned: |**********\n"));
    write(sprintf("%|80s",
        "*          `---------------------------'          *\n"));
    write(sprintf("%15s%|49s%-3s",
                  "*", 
                  "Non-magical: " + sprintf("%,d",
                   AOD_MASTER->get_info(this_player(), 
                   AOD_FORGE_NORM)),
                  "*\n"));
    write(sprintf("%15s%|49s%-3s",
                  "*",
                  "Magical: " + sprintf("%,d",
                   AOD_MASTER->get_info(this_player(),
                   AOD_FORGE_MAGIC)),
                  "*\n"));
    write(sprintf("%|80s",
        "***************************************************\n"));
} /* list_credits */


/*
 * Function name:        trainer_present
 * Description  :        Function to see if the trainer is present.
 *                       If so, we return the string of their nonmet
 *                       name
 * Returns      :        int 1 -- trainer present, int 0 -- not present
 */
public mixed
trainer_present()
{
    object  npc_trainer;

    if (!objectp(npc_trainer = present(Trainer_Id, this_object())))
    {
        return 0;
    }

    return npc_trainer->query_The_name(this_player());
} /* trainer_present */


/*
 * Function name:        make_trainer
 * Description  :        Move the trainer into this room.
 */
public void
make_trainer()
{
    if (objectp(Trainer))
    {
        return;
    }

    Trainer = clone_object(TRAINER);
    Trainer->add_name(Trainer_Id);
    Trainer->move_living("down", this_object());
} /* make_trainer */


/*
 * Function name:        reset_room
 * Description  :        Upon reset, make sure the room has a trainer.
 */
public void
reset_room()
{
    make_trainer();
} /* reset_room */



/*
 * Function name:        forge_list
 * Description  :        Print a list of available weapons or armours
 *                       that can be purchased with credit and money
 *                       at the forge
 * Arguments    :        string arg -- what was typed after the verb.
 * Returns      :        int 1 -- success, int 0 -- failure
 */
public int
forge_list(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("List what? Armours, weapons, or credits?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [available] 'armour' / 'armours' / 'weapon' / 'weapons'"
      + " / 'armor' / 'armors' / 'credit' / 'credits'"))
    {
        notify_fail("There is no such thing to list. You may list"
          + " weapons, armours, or credits.\n");
        return 0;
    }

    if (arg != "weapon" && arg != "weapons")
    {
        if (arg == "credit" || arg == "credits")
        {
            list_credits(this_player());
            return 1;
        }

        list_armour(this_player());
        return 1;
    }

    list_weapons(this_player());
    return 1;
} /* forge_list */


/*
 * Function name:        list_weapons
 * Description  :        List the weapons available for purchase
 * Arguments    :        object player -- the person seeing the list
 */
public void
list_weapons(object player)
{
    int     i,
            officer_true = 1,
            forge_price,
            credit_price,
            tmp_credit;
    string  cred = "";

    check_armament();

    if (!AOD_GENERAL(player) &&
        !AOD_CORPORAL(player))
    {
        officer_true = 0;
    }

    player->catch_tell(
        "\t .-------------------------------------------------------.\n"
      + "\t|       Weapons Available for Purchase at the Forge       |\n"
      + "\t|                                                         |\n"
      + "\t| Weapon Name:                  Credit Cost:   Pc  Gc  Sc |\n"
      + "\t| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n");

    for (i = 0; i < (Armament + 1); i++)
    {
        forge_price = FORGE_WEP_PRICES[i];
        credit_price = FORGE_WEP_CREDITS[i];

        if (officer_true)
        {
            tmp_credit = credit_price;

            forge_price = (forge_price / DEAL_FACTOR);
            credit_price = (credit_price / DEAL_FACTOR);

            if ( (credit_price * 2) < tmp_credit)
            {
                credit_price++;
            }
        }  

        if (Armament < 10)
        {
            if (AOD_MASTER->query_membership_status(player) ||
                player->query_wiz_level())
            {
                if (i > 5)
                {
                    cred = "(magical)";
                }

                player->catch_tell("\t| "
                  + sprintf("%-28s%1s%9s %3d%1s %3d %3d %3d %-2s",
                    capitalize(WEP_SHORTS[i]),
                    "|",
                    cred,
                    credit_price,
                    "|",
                    forge_price / 1728,
                   (forge_price % 1728) / 144,
                   (forge_price % 144) / 12, 
                    "|\n"));
            }
        }
    }

    player->catch_tell(
        "\t| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n"
      + "\t '-------------------------------------------------------'\n");

    if (Armament < 9)
    {
        player->catch_tell(
         "\n\t  *******************************************************\n"
       + "\t  *    Note: The Forge is capable of producing finer    *\n"
       + "\t  *  weapons than these. Return the heads of elves so   *\n"
       + "\t  * that the Blacksmith might achieve greater knowledge!*\n"
       + "\t  *******************************************************\n");
    }
} /* list_weapons */


/*
 * Function name:        list_armour
 * Description  :        List the armour available for purchase
 * Arguments    :        object player -- the person seeing the list
 */
public void
list_armour(object player)
{
    int     i,
            officer_true = 1,
            forge_price,
            credit_price,
            tmp_credit;
    string  cred = "";

    check_armament(1); /* arg = true, we want armours not weapons */

    if (!AOD_GENERAL(player) &&
        !AOD_CORPORAL(player))
    {
        officer_true = 0;
    }

    player->catch_tell(
        "\t .-------------------------------------------------------.\n"
      + "\t|       Armour Available for Purchase at the Forge        |\n"
      + "\t|                                                         |\n"
      + "\t| Armour Name:                  Credit Cost:   Pc  Gc  Sc |\n"
      + "\t| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n");

    if (Armament == 9)
    {
        Armament = 11;
    }

    for (i = 0; i < (Armament + 1); i++)
    {
        forge_price = FORGE_ARM_PRICES[i];
        credit_price = FORGE_ARM_CREDITS[i];

        if (officer_true)
        {
            tmp_credit = credit_price;

            forge_price = (forge_price / DEAL_FACTOR);
            credit_price = (credit_price / DEAL_FACTOR);

            if ( (credit_price * 2) < tmp_credit)
            {
                credit_price++;
            }
        }   

        if (Armament < 13)
        {
            if (AOD_MASTER->query_membership_status(player) ||
                player->query_wiz_level())
            {
                if (i > 5)
                {
                    cred = "(magical)";
                }

                player->catch_tell("\t| "
                  + sprintf("%-28s%1s%9s %3d%1s %3d %3d %3d %-2s",
                    capitalize(ARM_SHORTS[i]),
                    "|",
                    cred,
                    credit_price,
                    "|",
                    forge_price / 1728,
                   (forge_price % 1728) / 144,
                   (forge_price % 144) / 12, 
                    "|\n"));
            }
        }
    }

    player->catch_tell(
        "\t| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n"
      + "\t '-------------------------------------------------------'\n");

    if (Armament < 9)
    {
        player->catch_tell(
         "\n\t  *******************************************************\n"
       + "\t  *    Note: The Forge is capable of producing finer    *\n"
       + "\t  *  armours than these. Return the heads of dwarves so *\n"
       + "\t  * that the Blacksmith might achieve greater knowledge!*\n"
       + "\t  *******************************************************\n");
    }
} /* list_armours */


/*
 * Function name:        check_armament()
 * Description  :        check to see how many elf skulls have been
 *                       turned in to determine how many items the
 *                       Blacksmith currently knows how to forge
 * Arguments    :        int armour  -- true if we want to check for
 *                                      armours instead of weapons.
 *                                   -- default = 0
 */
public void
check_armament(int armour = 0)
{
    switch((armour == 1) ? AOD_MASTER->query_guild_total("dwarf")
                         : AOD_MASTER->query_guild_total("elf"))
    {
        case 0..499:
            Armament = 0;
            break;
        case 500..999:
            Armament = 1;
            break;
        case 1000..1999:
            Armament = 2;
            break;
        case 2000..4999:
            Armament = 3;
            break;
        case 5000..9999:
            Armament = 4;
            break;
        case 10000..24999:
            Armament = 5;
            break;
        case 25000..49999:
            Armament = 6;
            break;
        case 50000..74999:
            Armament = 7;
            break;
        case 75000..99999:
            Armament = 8;
            break;
        default:
            Armament = 9;
            break;
    }
} /* check_armament */


/*
 * Function name:        forge_buy
 * Description  :        Allow players to try to purchase the items which
 *                       are avaliable at the forge
 * Arguments    :        string arg -- what was typed after the verb
 * Returns      :        1 -- success, 0 -- failure
 */
public int
forge_buy(string arg)
{
    string  order;
    int     fprice;
    int     cprice;
    int     ordernum;
    int     my_cred;
    int     is_armour = 0;
    int     officer_true = 1;
    int     tmp_credit;
    object *obj = allocate(1);
    object  npc_trainer;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!objectp(npc_trainer = present(Trainer_Id, this_object())))
    {
        notify_fail("There is no one present who can help you do that.\n");
        return 0;
    }

    notify_fail("That is not available for purchase. You may <list"
      + " weapons> or <list armours> to see what is.\n");

    check_armament(); /* first, check the weapon armament */

    switch(arg)
    {
        case "iron":
        case "sheet":
        case "twisted sheet":
        case "scrap iron":
        case "sheet of scrap iron":
        case "twisted scrap iron":
        case "twisted sheet of scrap iron":
        case "twisted sheet of scrap":
        case "twisted sheet of iron":
        case "sheet of iron":
            ordernum = 0;
            break;
        case "post":
        case "iron post":
        case "crude post":
        case "crude iron post":
            if (Armament < 1)
            {
                return 0;
            }
            ordernum = 1;
            break;
        case "bar":
        case "iron bar":
        case "heavy bar":
        case "heavy iron bar":
            if (Armament < 2)
            {
                return 0;
            }
            ordernum = 2;
            break;
        case "rod":
        case "huge rod":
        case "iron rod":
        case "huge iron rod":
            if (Armament < 3)
            {
                return 0;
            }
            ordernum = 3;
            break;
        case "hammer":
        case "iron hammer":
        case "great hammer":
        case "great iron hammer":
            if (Armament < 4)
            {
                return 0;
            }
            ordernum = 4;
            break;
        case "morningstar":
        case "spiked morningstar":
        case "colossal morningstar":
        case "colossal spiked morningstar":
            if (Armament < 5)
            {
                return 0;
            }
            ordernum = 5;
            break;
        case "mallet":
        case "face mallet":
        case "darksteel mallet":
        case "darksteel face mallet":
            if (Armament < 6)
            {
                return 0;
            }
            ordernum = 6;
            break;
        case "spiker":
        case "head spiker":
        case "darksteel spiker":
        case "darksteel head spiker":
            if (Armament < 7)
            {
                return 0;
            }
            ordernum = 7;
            break;
        case "stick":
        case "death stick":
        case "darksteel stick":
        case "darksteel death stick":
            if (Armament < 8)
            {
                return 0;
            }
            ordernum = 8;
            break;
        case "sledgehammer":
        case "colossus sledgehammer":
        case "sledgehammer of the colossus":
            if (Armament < 9)
            {
                return 0;
            }
            ordernum = 9;
            break;
        default:
            check_armament(1); /* maybe they are buying an armour? */

            switch(arg)
            {
                case "metal":
                case "scrap metal":
                case "slab":
                case "crude slab":
                case "crude slab of metal":
                case "crude slab of scrap metal":
                case "slab of metal":
                case "slab of scrap metal":
                    is_armour = 1;
                    ordernum = 0;
                    break;
                case "can":
                case "iron can":
                case "huge can":
                case "huge iron can":
                    if (Armament < 1)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 1;
                    break;
                case "tub":
                case "tubs":
                case "iron tub":
                case "iron tubs":
                case "dented tub":
                case "dented tubs":
                case "dented iron tub":
                case "dented iron tubs":
                    if (Armament < 2)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 2;
                    break;
                case "ringmail":
                case "mail":
                case "curtain":
                case "enormous curtain":
                case "curtain of ringmail":
                case "enormous curtain of ringmail":
                    if (Armament < 3)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 3;
                    break;
                case "skullcap":
                case "iron skullcap":
                case "monstrous skullcap":
                case "monstrous iron skullcap":
                    if (Armament < 4)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 4;
                    break;
                case "chain":
                case "chain leggings":
                case "leggings":
                case "gigantic chain":
                case "gigantic leggings":
                case "gigantic chain leggings":
                    if (Armament < 5)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 5;
                    break;
                case "breastplate":
                case "ogre breastplate":
                case "darksteel breastplate":
                case "darksteel ogre breastplate":
                    if (Armament < 6)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 6;
                    break;
                case "bracers":
                case "troll bracers":
                case "darksteel bracers":
                case "darksteel troll bracers":
                    if (Armament < 7)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 7;
                    break;
                case "helm":
                case "goliath helm":
                case "darksteel helm":
                case "darksteel goliath helm":
                    if (Armament < 8)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 8;
                    break;
                case "greaves":
                case "darksilver greaves":
                case "titan greaves":
                case "titan's greaves":
                case "titans greaves":
                case "titan's darksilver greaves":
                case "titans darksilver greaves":
                    if (Armament < 9)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 9;
                    break;
                case "deathplate":
                case "behemoth deathplate":
                case "deathplate of the behemoth":
                    if (Armament < 9)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 10;
                    break;
                case "arm-bands":
                case "arm bands":
                case "bands":
                case "darksilver arm-bands":
                case "darksilver arm bands":
                case "darksilver bands":
                case "vast darksilver arm-bands":
                case "vast darksilver arm bands":
                case "vast darksilver bands":
                    if (Armament < 9)
                    {
                        return 0;
                    }
                    is_armour = 1;
                    ordernum = 11;
                    break;
                default:
                    return 0;
                    break;
            }
            break;
    }

    if (!AOD_GENERAL(this_player()) &&
        !AOD_CORPORAL(this_player()))
    {
        officer_true = 0;
    }

    if (is_armour)
    {
        order = AOD_ARM_DIR + "forgearm" + ordernum;
        fprice = FORGE_ARM_PRICES[ordernum];
        cprice = FORGE_ARM_CREDITS[ordernum];
    }
    else
    {
        order  = AOD_WEP_DIR + "forgeclub" + ordernum;
        fprice = FORGE_WEP_PRICES[ordernum];
        cprice = FORGE_WEP_CREDITS[ordernum];
    }

    if (officer_true)
    {
        tmp_credit = cprice;

        fprice = fprice / DEAL_FACTOR;
        cprice = cprice / DEAL_FACTOR;

        if ( (cprice + cprice) < tmp_credit)
        {
            cprice++;
        }
    }

    if (!can_pay(fprice, this_player()))
    {
        notify_fail("You haven't got enough money to pay the price!\n");
        return 0;
    }

    if (ordernum > 5)
    {
        my_cred = AOD_MASTER->get_info(this_player(),
                  AOD_FORGE_MAGIC);

        notify_fail("You haven't got enough Magical credits to"
          + " buy that item. Return magical armours and weapons"
          + " for the smith to melt down for scrap!\n");
    }
    else
    {
        my_cred = AOD_MASTER->get_info(this_player(),
                  AOD_FORGE_NORM);

        notify_fail("You haven't got enough credits to"
          + " buy that item. Return weapons and armours for the"
          + " smith to melt down for scrap!\n");
    }

    if (my_cred < cprice)
    {
        return 0;
    }

    obj[0] = clone_object(order);
    obj[0]->add_prop(OBJ_I_VALUE, fprice);

    if (sizeof(buy_it(obj, "", "")))
    {
        my_cred -= cprice;

        if (ordernum > 5)
        {
            AOD_MASTER->set_info(this_player(), AOD_FORGE_MAGIC,
                my_cred);

            write("You spent " + cprice + " Magical credits.\n");
        }
        else
        {
            AOD_MASTER->set_info(this_player(), AOD_FORGE_NORM,
                my_cred);
            write("You spent " + cprice + " credits.\n");
        }

        write("The blacksmith hands you "
          + LANG_ADDART(obj[0]->short()) + ".\n");
        write_file(AOD_LOG_DIR + "forge_buy",
            TIME2FORMAT(time(), "mm/dd") + " (" + ctime(time())[11..18]
          + ") " + capitalize(this_player()->query_name()) + " -- "
          + ( (ordernum > 5) ? upper_case(LANG_ADDART(obj[0]->short()))
          : LANG_ADDART(obj[0]->short()) ) + "("
          + AOD_MASTER->get_info(this_player(), AOD_FORGE_NORM)
          + ":" + AOD_MASTER->get_info(this_player(), 
            AOD_FORGE_MAGIC) + ")\n");
    }
        
    return 1;
} /* forge_buy */


/*
 * Function name: buy_it
 * Description:   Try to let the player buy the item array
 * Arguments:     ob - the object array
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       1 on sucess
 */
object *
buy_it(object *ob, string str2, string str3) 
{
    int price, i, j, k, *value_arr, *arr, error, num, err;
    object *bought;
    mixed tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);
    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_buy(ob[i]))
            continue;

        if (tmp = ob[i]->query_prop(OBJ_M_NO_BUY))
        {
            shop_hook_buy_no_buy(ob[i], tmp);
            continue;
        }

        price = ob[i]->query_prop(OBJ_I_VALUE);

        /* be sure they can pay before we try to move ob to player,
         * because if ob is a heap and the move succeeds and the player
         * is holding another of that ob, they will merge.
         * too late then to discover that the player can't pay.
         * set 'test' (4th) arg so this call doesn't actually move coins
         */
        if (sizeof(arr = pay(price, this_player(), str2, 1, 0, str3)) == 1)
        {
            shop_hook_buy_cant_pay(ob[i], arr);
            continue;
        }

        /* If you don't feel greedy you can shorten the calculation above. */
        if (err = ob[i]->move(this_player()))
        {
            write("You are too encumbered to carry the "
              + ob[i]->short() + ". Lighten your load first.\n");
            continue;
        }

        if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
        {
            ob[i]->remove_object();
            shop_hook_buy_cant_pay(ob[i], arr);
            continue;  /* pay() can handle notify_fail() call */
        }

        /* Detect if there was a move error. */
        if (error = arr[sizeof(arr) - 1])
        {
            if (error < -1)
            {
            /* Couldn't take the money from player, the coins were stuck */
                shop_hook_buy_magic_money(ob[i]);
                ob[i]->remove_object();
                continue;
            }
            /* We don't want the money so no move error to us, if there was one
               it was because the player couldn't hold all coins, and if so the
               drop text is already written, but the deal is still on :) */
        }

        for (k = 0; k < 2 * num; k++)
            value_arr[k] += arr[k];

        bought[j] = ob[i];
        j++;
        if (j >= 1)
            break;
        /* Well, we don't want to let a player accidentily buy too much :) */
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
        shop_hook_buy_pay_money(
                text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));

    return bought;
} /* buy_it */


/*
 * Function name:        forge_allow
 * Description  :        Let wizards set allowed/disallowed status for
 *                       scrapping items
 *                       
 * Arguments    :        string arg -- what was typed after the verb.
 * Returns      :        int 1 -- success, int 0 -- failure
 */
public int
forge_allow(string arg)
{
    int old, new;
    string path;
    
    if (!this_player()->query_wiz_level())
        return 0;
    
    notify_fail("Usage: allow <path> <flag>\n"
        + "Where <flag> is 1 for allowed, -1 for disallowed\n");

    if (!arg)
        return 0;
        
    if (!sscanf(arg, "%s %d", path, new))
        return 0;

    if ((new != -1) && (new != 1))
        return 0;

    old = METAL_MASTER->get_info("forge_allow", path);

    if (!old)
    {
        write("That object hasn't been seen yet.\n");
        return 1;
    }
    
    METAL_MASTER->set_info("forge_allow", path, new);    
    
    write (path + " changed from " + old + " to " + new + "\n");

    return 1;    

} /* forge_allow */
