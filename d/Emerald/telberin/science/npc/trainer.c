/*
 *  /d/Emerald/telberin/science/npc/trainer.c
 *
 *  Inhuin is the Potion Master of the Science Guild of Telberin.
 *  He provides training in the alchemical arts as well as selling
 *  a variety of unique resistance potions to players.
 *
 *  Location: /d/Emerald/telberin/science/apothecarium.c
 *
 *  Copyright (c) May 2003, by Cooper Sherry (Gorboth)
 *
 *  Revision History:
 *    March-21-2014: (Gorboth) Added potion selling stuff.
 */

inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Genesis/lib/intro";

#include <const.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>


/* prototypes */
public void    create_telberin_elf();
public void    introduce(object who);
public void    react_intro(object tp);
public int     complete_payment(object who, int needed, string reason);
public int     do_buy(string arg);
public void    init_living();
public void    intro_check(object who);

/* global variables */
public mapping     Potions = ([ 
                        "asidda"   : "acid",
                        "yradda"   : "air",
                        "caldarra" : "cold",
                        "dythorra" : "death",
                        "yrthella" : "earth",
                        "elecca"   : "electricity",
                        "firadda"  : "fire",
                        "iluyya"   : "illusion",
                        "lyfella"  : "life",
                        "pysella"  : "poison",
                        "watalla"  : "water",
                              ]);
public mapping     Prices = ([
                        "dull"     : 10,
                        "shiny"    : 25,
                        "luminous" : 100,
                            ]);
public mapping     Levels = ([
                        "dull"     : 0,
                        "shiny"    : 1,
                        "luminous" : 2,
                            ]);

/* Definitions */
#define           POTION_DIR  "/d/Emerald/telberin/science/potions/"
#define           TELL_G(x) (find_living("gorboth")->catch_tell("DEBUG: "+(x)+"\n"))


/*
 * Function name:        create_telberin_elf
 * Description  :        set up the npc
 */
public void
create_telberin_elf()
{
    set_living_name("inhuin");
    set_name("inhuin");
    add_name("inhuin ralei");
    add_name( ({ "scientist", "apothecary" }) );
    set_adj( ({ "preoccupied", "grey-cloaked" }) );

    set_title("Ralei, Potions Master of the Science Guild of"
            + " Telberin");

    set_short("preoccupied, grey-cloaked elf");
    set_long("This elf appears to be fully absorbed in various"
      + " scientific experiments and studies which he has"
      + " placed around the room. He moves silently from one"
      + " station to the next, carefully monitoring the"
      + " progress of his work. He doesn't seem to notice"
      + " you at all.\n");

    config_elf(90);  /* A man of science, he isn't too big */

    set_act_time(20);
    add_act("emote carefully pours fluid from one vial to"
      + " another.");
    add_act("emote steps away from his experiments and runs"
      + " his finger down a long parchment, studying what"
      + " is written there.");
    add_act("emote pauses, and strokes his chin while seeming"
      + " to do some calculations in his head.");
    add_act("emote mutters angrily under his breath: I just"
      + " knew I was going to run out ... why didn't I send"
      + " for more?");
    add_act("emote rushes to attend to a container which has"
      + " started to boil over.");

    set_cact_time(10);
    add_cact("emote tries desparately to avoid your attacks.");
    add_cact("emote peers at you in fear and anger.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote grabs a nearby vial, and throws it at you!");

    set_job_response("I am a teacher of the sciences. If you"
      + " desire to <learn> or <improve> skills with me, I am at"
      + " your service. You may also <buy> my potions, if you have"
      + " need of them.");

    add_ask( ({ "potion", "potions" }),
        "say I sell many varieties of potions. Please read the"
      + " pricelist for details.", 1);
    add_ask( ({ "asidda", "assidda potion" }),
        "say The Asidda potion is a mixture comprised of many substances,"
      + " including lemon zest. It provides protection from acid.", 1); 
    add_ask( ({ "yradda", "yradda potion" }),
        "say The Yradda potion is a strange one. There is actually some"
      + " resin from the pine tree included in the mixture! It will"
      + " provide protection from the powers of air.", 1);
    add_ask( ({ "caldarra", "caldarra potion" }),
        "say Bruised mint leaves are part of the mixture that makes up"
      + " the Caldarra potion. It is most useful for protection against"
      + " cold.", 1);
    add_ask( ({ "dythorra", "dythorra potion" }),
        "say Who would have known that licorice could help ward off death? It"
      + " is a recent discovery of the Science guild, and part of the"
      + " mixture of the Dythorra potion.", 1);
    add_ask( ({ "yrthella", "yrthella potion" }),
        "say Carefully sifted soil is present in the mixture of the"
      + " Yrthella potion, which lends protection against the"
      + " powers of earth.", 1);
    add_ask( ({ "elecca", "elecca potion" }),
        "say The Elecca potion actually has tiny shavings of bronze"
      + " in its mixture. It is a key component in helping ward off"
      + " the effects of electricity.", 1);
    add_ask( ({ "firadda", "firadda potion" }),
        "say Cinnamon is used to mask the powerful alcoholic fumes"
      + " used in the mixture of the Firadda potion, which provides"
      + " protection against fire.", 1);
    add_ask( ({ "iluyya", "iluyya potion" }),
        "say Petals from the Rose Gardens of the Royal Circle are used"
      + " in the Iluyya potion, which guards against the powers of"
      + " illusion.", 1);
    add_ask( ({ "lyfella", "lyfella potion" }),
        "say There used to be a bee-keeper just south of the gates of"
      + " Telberin, in the old days. His honey is still kept on hand"
      + " in the Science guild, and provides potency to the Lyfella"
      + " potion which protects against the powers of life.", 1);
    add_ask( ({ "pysella", "pysella potion" }),
        "say Unfortunately, week-old eggs are needed in the mixing"
      + " of the Pysella potion. Though unpleasant, it is far less"
      + " unpleasant than the poisons it might protect you from.", 1);
    add_ask( ({ "watalla", "watalla potion" }),
        "say Wine from the coast is brought in as a reagent in the"
      + " mixture needed to create the Watalla potion, which is"
      + " very effective in warding against the powers of water.", 1);
    add_ask( ({ "apothecary", "apothecarium" }),
        "say Yes, I've worked in this Apothecarium for many years now."
      + " I started as a mere Understudy, but have finally achieved"
      + " Master Status within the Science Guild, thanks to my"
      + " achievements with potion-making.", 1);
    add_ask( ({ "help", "task", "quest" }),
        "say I need no help, but perhaps if you <buy> one of my"
      + " potions, it will help you today in your adventures.", 1);
    add_ask( ({ "price", "pricelist", "price list" }),
        "say The pricelist is right there on the wall. You should"
      + " read it.", 1);
    add_ask( ({ "beaker", "beakers" }),
        "say It is unfortunate that the beakers are so heavy, but it"
      + " is the only way to contain such caustic mixtures for any"
      + " useful length of time.", 1);
    add_ask( ({ "science", "guild", "science guild",
                "science guild of telberin" }),
        "The Science Guild of Telberin is one of the earliest"
      + " scholarly societies known in the realms.", 1);

    setuid();
    seteuid(getuid());
} /* create_elf */


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
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");
} /* react_intro */


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
        command("peer patient " + who->query_real_name());
        command("say First, notice please that the cost for this"
          + " potion is " + LANG_NUM2WORD(needed) + " platinum coins."
          + " Seeing that you do not have even a single platinum"
          + " coin (and I do not trifle with lesser coinage) you will"
          + " need to return when you have the required payment.");
        return 0;
    }

    if (coin->num_heap() < needed)
    {
        command("peer patient " + who->query_real_name());
        command("say Notice, please, that the cost for this"
          + " potion is " + LANG_NUM2WORD(needed) + " platinum coins."
          + " Your " + LANG_NUM2WORD(coin->num_heap())
          + ((coin->num_heap() == 1) ? " falls" : " fall" ) + " somewhat"
          + " short of the mark, I am afraid. I prefer not to trifle with"
          + " lesser coinage, frankly, so you will need to return"
          + " when you have the full amount.");
        return 0;
    }

    who->catch_tell("You pay " + needed + " platinum coins to "
      + npc->query_the_name(who) + ".\n");
    tell_room(environment(who), QCTNAME(who) + " pays some platinum"
      + " coins to " + QTNAME(npc) + ".\n", who);
    command("emote nods approvingly.");
    command("say Yes, very good. Thank you.");

    if (present("kot_guild_emblem", who))
    {
        command("say Always a pleasure doing business with one"
          + " of our esteemed former Keepers of Telberin!");
        command("bow respect");
    }

    temp_location = clone_object("/std/room");
    coin->split_heap(needed);
    coin->move(temp_location);
    /* Clean up afterward. */
    temp_location->remove_object();

    write_file(POTION_DIR + "potion_log",
          TIME2FORMAT(time(), "mm/dd/yyyy")
        + " (" + ctime(time())[11..18] + ") "
        + capitalize(this_player()->query_name())
        + " pays " + needed + " platinum coins. (" + reason + ")\n");

    return 1;
} /* complete_payment */

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
    int      pl_size;
    string   s;
    string  *p_names = m_indices(Potions);
    string   p_name;
    string  *p_lvls = ({ "dull", "shiny", "luminous" });
    string   p_lvl;
    string   e_type;

    tell_room(environment(this_object()), QCTNAME(this_player())
      + " inquires about making a purchase.\n",
        this_player());

    if (!CAN_SEE_IN_ROOM(this_object()) ||
        !CAN_SEE(this_object(), this_player()))
    {
        command("say I would love to have you business, if only I could"
          + " see you.");
        return 1;
    }

    intro_check(this_player());

    if (!strlen(arg))
    {
        notify_fail("");
        command("say What do you wish to buy? I can sell you any of the"
          + " potions on the pricelist.");
        return 0;
    }

    if (arg == "potion" || arg == "potions")
    {
        notify_fail("");
        command("say Yes, yes. I sell many potions. Please be"
          + " specific. Perhaps if you consult the pricelist"
          + " you will be able to make a selection.");
        return 0;
    }

    if (parse_command(arg, all_inventory(this_player()),
        "[the] [a] [an] %p [potion] [potions]", p_names))
    {
        p_name = p_names[0];

        notify_fail("");
        command("say Certainly, I can sell you " + LANG_ADDART(p_name)
          + " potion. They are excellent for protection against "
          + Potions[p_name] + ", as you perhaps already know. In any"
          + " case, there are three levels of potency with three"
          + " different prices: dull, shiny, or luminous. Please"
          + " specify which you desire.");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] [a] [an] %p %p [potion]", p_lvls, p_names))
    {
        notify_fail("");
        command("say I do not sell that item. Please consult my"
          + " pricelist for information on what I have in stock.");
        return 0;
    }

    p_name = p_names[0];
    p_lvl  = p_lvls[0];
    e_type = Potions[p_name];

    if (!complete_payment(this_player(), Prices[p_lvl],
        p_lvl + " " + e_type))
    {
        notify_fail(""); /* No fail message for this. */
        return 0;
    }

    sale = clone_object(POTION_DIR + e_type + "_potion");
    sale->set_lvl(Levels[p_lvl]);
    sale->setup_resistance_potion();
    sale->move(this_player());

    write("You purchased " + LANG_ADDART(sale->short()) + ".\n");
    tell_room(environment(this_object()), QCTNAME(this_player())
      + " purchases " + LANG_ADDART(sale->short()) + ".\n",
        this_player());

    return 1;
} /* do_buy */


/*
 * Function name:        init living
 * Description  :        set up some actions for the players who
 *                       enter the room
 */
public void
init_living()
{
    ::init_living();

    add_action(do_buy, "buy");
    add_action(do_buy, "purchase");
} /* init_living */


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
} /* intro_check */