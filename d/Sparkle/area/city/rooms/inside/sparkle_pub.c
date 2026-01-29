/*
 *  /d/Sparkle/area/city/rooms/inside/sparkle_pub.c
 *
 *  This room is a real multi-tasker! It has the following functionality:
 *
 *    - You can order food/drink, courtesy of Gondor Inn code.
 *    - You can sit at tables, courtesy of Gnadnar's excellent
 *      room_chair.c code, also originally from Gondor.
 *    - You can enjoy the fire, relighting it and such if it goes
 *      out, courtesy again of Gnadnar and her fireplace code from
 *      Gondor.
 *    - The barkeep is (possibly?) the first non-gendered npc in
 *      Genesis, hoping that we can feel welcoming to all players,
 *      and connect with a few who might relate to this themselves.
 *    - It has a very tough bouncer - Kiki the Hellcat!
 *    - The parlor and lounge each have interesting activities which
 *      give players some things to enjoy during their sessions, if
 *      they choose to stay active.
 *    - This pub will host a quest to keep the rested-exp spirits
 *      flowing, asking players to harvest the primary ingredient.
 *
 *  Most importantly, this location is our first test-implementation of
 *  the concept of "rested-exp", which gives players an incentive to take
 *  a break from the grind and do something social with their time to
 *  get a grinding exp boost afterwards. For details see:
 *
 *      /d/Sparkle/XXX
 *
 *  Created August 2018, by Cooper Sherry (Gorboth)
 *    - Much credit must go to Gnadnar - so much of the Gondor code is hers.
 *    - Additionally, this replaces Styles' original Garyn's Pub, which
 *      featured some ideas that have been carried forward (no fighting,
 *      thieving, spitting, etc, rules.)
 *
 *  April 2021 : Added Iron Delving Export Brew functionality 
 *    "/d/Ansalon/common/brewcraft/brewcraft.h"
 *       by Vitwitch
 */
#pragma strict_types

#include "../../defs.h"

inherit SPARKLE_ROOM_BASE;
inherit "/lib/trade";
inherit "/d/Emerald/blackwall/delrimmon/legacy/fireplace";
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Sparkle/area/city/sys/session.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/fireplace.h"
#include "/d/Ansalon/common/brewcraft/brewcraft.h"


/* definitions */
#define NUM                sizeof(MONEY_TYPES)
#define COIN_TYPES         ({ "cc", "sc", "gc", "pc" })
#define MY_PRICES          ({ 12, 32, 70, 21, 210, 530 })
#define BLOCK_NAME         "bar tables"
#define ANNOYING           "_sparkle_pub_annoying_customer"
#define BANNED_FROM_PUB    "_sparkle_banned_from_pub"
#define BANNED_DURATION    7200   /* two hours */
#define SESSION_AVAILABLE  0



#define INNKEEPER_PRESENT \
    (!Have_innkeeper || (objectp(Innkeeper_npc) && \
      environment(Innkeeper_npc) == this_object()))
#define CAP_INNKEEPER(pl) \
    (Have_innkeeper ? Innkeeper_npc->query_The_name(pl) : Innkeeper_Name)
#define LOW_INNKEEPER(pl) \
    (Have_innkeeper ? Innkeeper_npc->query_the_name(pl) : Innkeeper_name)
#define QCT_INNKEEPER \
    (Have_innkeeper ? QCTNAME(Innkeeper_npc) : Innkeeper_Name)
#define QT_INNKEEPER \
    (Have_innkeeper ? QTNAME(Innkeeper_npc) : Innkeeper_name)


/* Global Variables */
static int         Have_innkeeper; /* is there an npc bartender?   */
static object      Innkeeper_npc;  /* the npc.                     */
public mixed       Summoner = 0;   /* Excessive bell ringers       */

/* if not using an npc, can still customize the innkeeper's name */
static string      Innkeeper_Name = "The bartender";
static string      Innkeeper_name = "the bartender";
static object      Innkeeper;

/* Prototypes */
public void        create_sparkle();
public string      exa_painting();
public int         check_exit();
public void        summon_innkeeper(int silent = 0, mixed annoyer = 0);
public void        reset_room();
public int         can_afford(int price, int number, string ware,
                       string pay_type, string get_type);
public int         do_buy(string str);
public string      price_long();
public void        set_innkeeper_npc(object npc);
public void        set_innkeeper_name(string name);
public void        ring_bell(string arg);
public string      fire_desc(string arg);
public int         do_sit(string arg);
public void        do_sit_msgs(object pl, string prep, string name);
public void        do_stand_msgs(object pl, string name);
public string      look_tables();
public void        leave_inv(object ob, object dest);
public string      show_subloc(string subloc, object pl, object for_obj);
public string      sitting_on_chair(string name, object for_obj, int namesonly, int definite = 1);
public string      kick_for_brawling();
public string      kick_for_stealing();
public void        ban_patron(object who);
public int         judge_entry(object who);
public int         do_session(string arg);
public int         session_duration(object who);
public string      duration_text(object who);
public int         check_session(object who);


/*
 * Function name:        create_sparkle
 * Description  :        set up the room
 */
public void
create_sparkle()
{
    set_short("in a loud, crowded pub");
    set_long("@@fire_desc@@"); /* use VBFC for room description */

    add_chair(BLOCK_NAME, "[down] [at] [in] [on] [one] [of] [the] [nearby]"
                        + " [large] [dining]"
                        + " 'table' / 'tables' / 'chair' / 'chairs'",
                          20, "at", 0);
    set_fire_container("chimney");
    /* set the pattern for the parse_command() */
    set_parse_pattern("[the] [enormous] 'chimney'");

    add_item( ({ "here", "area", "room", "pub", "bar", "tavern",
                 "boars head tavern", "boars head pub", "boars head bar",
                 "boar's head tavern", "boar's head pub", "main room",
                 "boar's head bar", "hall", "main hall", "bar hall" }),
        "This is one of the most popular rooms in the Sparkle, and one"
      + " can see why - a roaring fire, drinks, and a place to sit down."
      + " What more can a tired traveller ask for? Well, a good drinking"
      + " <session> perhaps!\n");
    add_item( ({ "shelf", "shelves" }),
        "The shelves behind the bar are filled with the standard"
      + " array of colourful bottles of many shapes and sizes you would"
      + " expect to see in a busy watering hole in a major port of"
      + " call such as this.\n");
    add_item( ({ "array", "standard array", "array of bottles",
                 "bottles", "bottle", "colorful bottle",
                 "colourful bottle", "colourful bottles",
                 "standard array of bottles",
                 "array of colorful bottles",
                 "array of colourful bottles",
                 "standard array of colorful bottles",
                 "standard array of colourful bottles" }),
        "A display like this excites the imagination of any proper"
      + " drunkard!\n");
    add_item( ({ "nothing too exotic" }),
        "You find nothing too exotic. So far.\n");
    add_item( ({ "display" }),
        "SO EXCITING ........ you try to calm yourself.\n");
    add_item( ({ "shape", "shapes", "size", "sizes",
                 "shapes and sizes", "sizes and shapes" }),
        "You ponder the glass-blowing industry and its impact on"
      + " your life.\n");
    add_item( ({ "glass-blowing", "glass blowing", "industry",
                 "glass blowing industry", "glass-blowing industry" }),
        "You catch your mind wandering, and refocus on what you were"
      + " doing.\n");
    add_item( ({ "traveller", "travellers", "tired traveller",
                 "tired travellers" }),
        "Ah, the weary road ... perhaps drink will cure the ache"
      + " in a tired body.\n");
    add_item( ({ "road", "weary road" }),
        "Folks like you come here to escape it.\n");
    add_item( ({ "port", "port of call" }),
        "Sparkle is most definitely that.\n");
    add_item( ({ "drunkard" }),
        "You find no drunkard. Wait, yes you do.\n");
    add_item( ({ "drunkards" }),
        "You find no drunkards. Wait, yes you do.\n");
    add_item( ({ "arch", "archway" }),
        "The archway leads west past the fireplace, heading into a"
      + " parlor off the main room.\n");
    add_item( ({ "parlor", "parlour" }),
        "The parlor is west of here, and not much can be seen without"
      + " heading in and taking a look for yourself.\n");
    add_item( ({ "watering hole" }),
        "Everyone needs a good place to call their own ... a place where"
      + " everyone knows your name.\n");
    add_item( ({ "place to call their own", "place to call my own",
                 "place where everyone knows your name", "my name",
                 "name", "your name" }),
        "... and they're always glad you came.\n");
    add_item( ({ "came", "you came", "glad you came",
                 "always glad you came" }),
        "... Cheers!\n");
    add_item( ({ "cheers" }),
        "You're no Sam Malone.\n");
    add_item( ({ "malone", "sam malone" }),
        "You find your mind wandering, and you snap out of it.\n");
    add_item( ({ "sparkle", "town" }),
        "This is one of the most popular places in town.\n");
    add_item( ({ "flavor", "flavour", "local flavor", "local flavour", }),
        "Well, and probably a bit of foreign flavour, too ...\n");
    add_item( ({ "foreign flavor", "foreign flavour" }),
        "Nothing too exotic. Well, who knows? Maybe you should mingle"
      + " and see who you meet?\n");
    add_item( ({ "hub", "hub of genesis" }),
        "All roads lead to Rome ... or, in this case ... Sparkle.\n");
    add_item( ({ "rome" }),
        "When in Sparkle, do as the ... Sparklers? ... do?\n");
    add_item( ({ "sparklers" }),
        "You catch your mind wandering, and blink a few times.\n");
    add_item( ({ "road", "roads" }),
        "They all lead here, to Sparkle, the hub of Genesis.\n");
    add_item( ({ "genesis" }),
        "It is everywhere.\n");
    add_item( ({ "everywhere" }),
        "The concept is too vast to fully appreciate.\n");
    add_item( ({ "concept" }),
        "Inconceivable!\n");
    add_item( ({ "patrons", "patron", "many patrons" }),
        "They have all come here, just like you, to find whatever it is"
      + " people look for in bars.\n");
    add_item( ({ "wall", "walls" }),
        "Which wall do you wish to examine?\n");
    add_item( ({ "food" }),
        "Your belly can be cheered up a bit if you feel like placing"
      + " an <order> with the waitress.\n");
    add_item( ({ "bartender" }),
        "If s/he isn't around, just <ring> the bell.\n");
    add_item( ({ "bell", "brass bell", "large bell", "large brass bell" }),
        "A large brass bell is mounted on the bar. If there was a reason"
      + " to summon the bartender, you could probably <ring> it.\n");
    add_item( ({ "chimney", "enormous chimney", "fireplace",
                 "huge fireplace" }),
        "The chimney fills much of the western wall. It has been built"
      + " with deep red bricks.\n");
    add_item( ({ "western wall", "west wall", "west",
                 "wall to the west", "far wall" }),
        "The western wall is occupied"
      + " by the huge fireplace, beside which an archway"
      + " leads into a parlor off the main hall.\n");
    add_item( ({ "brick", "bricks", "red brick", "red bricks",
                 "deep red brick", "deep red bricks" }),
        "Hardened mortar has slopped from between the bricks where they"
      + " were pressed together to make the chimney.\n");
    add_item( ({ "mortar", "hardened mortar" }),
        "The sloppy look of the mortar has a certain quaint charm.\n");
    add_item( ({ "north wall", "north", "northern wall", "wall to the north" }),
        "The northern wall is comprised almost entirely of a large bar"
      + " and shelves filled with drinks.\n");
    add_item( ({ "bar", "large bar", "long bar", "wooden bar",
                 "wood bar", "long wooden bar", "large wooden bar",
                 "counter", "bar counter" }),
        "A long wooden bar fills most of the northern wall, behind which"
      + " shelves are filled with drinks of various types. A bell is"
      + " on the bar, and you are sure you could <order> drinks or start"
      + " a drinking <session> if you wanted to.\n");
    add_item( ({ "south wall", "southern wall",
                 "wall to the south", "south" }),
        "The southern wall is covered with many paintings which surround"
      + " the opening to a short hallway which leads south into a"
      + " lounge.\n");
    add_item( ({ "opening", "opening to a hallway",
                 "opening to a short hallway", "south opening",
                 "opening in the south wall" }),
        "A hallway leads past the opening into a lounge south of"
      + " this main part of the bar.\n");
    add_item( ({ "hallway", "short hallway" }),
        "The hallway leads south past all the paintings on the wall.\n");
    add_item( ({ "lounge" }),
        "It is down the hallway south of here.\n");
    add_item( ({ "painting", "paintings", "many paintings" }),
        "@@exa_painting@@");
    add_item( ({ "east", "east wall", "eastern wall",
                 "wall to the east" }),
        "The wall to the east has a doorway leading out onto the piers."
      + " A few windows line the wall on each side.\n");
    add_item( ({ "east window", "window in the east wall", "windows",
                 "window", "east windows", "few windows" }),
        "The windows look like they haven't been cleaned in ... forever."
      + " You can't see anything through them.\n");
    add_item( ({ "doorway", "door", "passage", "passageway" }),
        "The door is open, and leads east onto the piers.\n");
    add_item( ({ "fireplace", "chimney", "enormous chimney", }),
        &fire_desc("firepit"));
    add_item( ({ "firelight", "warmth", "flickering firelight", "shadows",
                 "light", "glow", "bouncing light" }),
        &fire_desc("firelight"));
    add_item( ({ "dark", "darkness", "murky darkness",
                 "murky atmosphere" }), &fire_desc("darkness"));
    add_item( ({ "fire", "flame", "flames", "blazing fire", "atmosphere",
                 "roaring fire", "huge fire" }), &fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in fireplace",
                 "firewood in fireplace", "wood in chimney",
                 "firewood in fireplace", "burning wood", "burning firewood" }),
        &fire_desc("wood"));
    add_item( ({ "ash", "ashes", "ash in fireplace",
                 "ashes in fireplace", "ash in chimney",
                 "ashes in chimney", "chimney bottom",
                 "bottom of the chimney" }),
        &fire_desc("ashes"));
    add_item( ({ "head", "boar", "boars head", "boar's head",
                 "huge boar", "huge head", "huge boar head",
                 "huge boar's head" }), &fire_desc("boar"));
    add_item( ({ "snout", "boar snout", "boar's snout" }),
        "It's all about the snout.\n");
    add_item( ({ "whisker", "whiskers", "boar whisker",
                 "boar whiskers", "boars whisker", "boar's whisker",
                 "boar's whiskers", "boar's whiskers" }),
        "The whiskers on the boar's head are long, but not as long as"
      + " the ones on the nearby hellcat.\n");
    add_item( ({ "table", "tables", "large table", "large tables",
                 "one of the tables", "one of the bar tables",
                 "various tables", "various bar tables",
                 "large bar table", "large bar tables",
                 "bar table", "bar tables", "place to sit",
                 "place to sit down" }),
        look_tables);
    add_item( ({ "chair", "chairs", "bar chair", "bar chairs" }),
        "Chairs are crowded around the bar tables, tempting the"
      + " weary traveller to <sit> and <order> something from the menu.\n");
    add_item( ({ "pricelist", "list", "prices", "menu", "bill", "board",
                 "bill of fare", "sign", "large menu" }), price_long());
    add_item( ({ "perch", "perch above the bar", "cat perch" }),
        "Above the bar there appears to be room for a perch for the"
      + " resident bouncer.\n");
    add_item( ({ "torch", "magical torch", "magic torch",
                 "torches", "magical torches", "magic torches" }),
        "The torches provide dim but servicable light even if the"
      + " fire has gone out. They seem impervious to any type of"
      + " darkness.\n");
    add_item( ({ "up", "ceiling", "roof" }),
        "There are a few magical torches hanging from the ceiling.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor is very crowded - mostly with the feet of"
      + " patrons like yourself!\n");
    add_item( ({ "feet", "feet of patrons", "patron feet" }),
        "So many feet.\n");

    add_cmd_item( ({ "boar", "head", "boar head", "boars head",
                     "boar's head" }),
                  ({ "search" }),
        "You wander over and give the boar's head a careful"
      + " examination. A few bar patrons follow you with their eyes."
      + " You don't seem to find anything interesting.\n");
    add_cmd_item( ({ "boar", "head", "boar head", "boars head",
                     "boar's head" }),
                  ({ "pull" }),
        "You wander over and pull a bit on the boar's head, seeing if"
      + " it is loose at all. It doesn't seem all that well attached"
      + " to the wall, and you figure it probably wouldn't be wise"
      + " to cause it to fall down, so you leave it alone and return"
      + " to where you were.\n");
    add_cmd_item( ({ "boar", "head", "boar head", "boars head",
                     "boar's head" }),
                  ({ "push" }),
        "You wander over and push a bit on the boar's head. It doesn't"
      + " seem to move much, so you return to other things.\n");
    add_cmd_item( ({ "boar", "head", "boar head", "boars head",
                     "boar's head" }),
                  ({ "move", "lift", "pry" }),
        "You approach the boar's head and give it a wiggle. It seems"
      + " only loosely held to the bricks, perhaps by a hook or two"
      + " and some sturdy twine. You don't feel this is really getting"
      + " you anywhere, though.\n");
    add_cmd_item( ({ "boar", "head", "boar head", "boars head",
                     "boar's head" }),
                  ({ "get", "pick", "take", "steal" }),
        "The boar's head is massive. What would you possibly do with"
      + " it? Plus, you figure that you wouldn't be able to steal it"
      + " without quite a few people noticing.\n");
    
    add_cmd_item( ({ "window", "windows" }),
                  ({ "clean" }),
        "A hopeless task, and not one you care to waste time on.\n");

    add_cmd_item( ({ "pricelist", "list", "prices", "menu", "bill",
                     "bill of fare", "sign", "large menu", "board" }),
                  ({ "read" }), price_long());

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out( ({ 2000, 700, 50, 4 }) );
    set_money_give_reduce( ({ 1, 1, 1, 1 }) ); 

    set_fire_state(FIRE_BURNING);

    /* I do not use this feature lightly - it is very powerful and
     * should not be used often at all. However, this room is intended
     * to be a social hub for the game, and I do not want griefers to
     * be able to cause problems by making it dark. So, we'll use
     * some thematics to intentionally prevent it from ever becoming
     * dark.
     */
    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "@@kick_for_brawling");
    add_prop(ROOM_M_NO_STEAL, "@@kick_for_stealing");

    add_exit("sparkle_pub_parlor", "west", check_sitting, 1, 0);
    add_exit("/d/Genesis/start/human/town/pier2", "east",
        "@@check_session@@", 1, 0);
    add_exit("sparkle_pub_lounge", "south", check_sitting, 1, 0);
    

    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest" }),
        "You poke around the corner of the room, but find nothing.\n");
    set_no_exit_msg( ({ "north" }),
        "You belly up to the bar, but can go no further.\n");

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_sparkle */


/*
 * Function name:        exa_painting
 * Description  :        Let the player look at one of the paintings
 * Returns      :        string - the description
 */
public string
exa_painting()
{
    string  ptxt = "As you gaze at the paintings on the wall, one stands"
                 + " out to you. It depicts ";

    ptxt += one_of_list( ({

        "a very detailed portrait of a nude green-skinned orc lying"
      + " sideways on a filthy log and smiling grotesquely",

        "a clipper-ship in a windblown bay",

        "a bunch of dogcows playing poker around a table",

        "a kender being mercilessly beaten by a group of Dragonarmy"
      + " soldiers",

        "a very fat man peering greedily into an oven filled with"
      + " donuts",

        "a mysterious island whose name is not spoken aloud",

        "a battlefield strewn with corpses beneath the Misty Mountains",

        "a light-robed mystic casting a spell on the head of a"
      + " vampyr he has pulled from his backpack",

        "a group of small adventurers looking on in outrage as a"
      + " massive dead-eyed dwarf arrives and steals their kills",

        "a pale brooding female human sitting in a dark corner, smiling"
      + " to reveal pearlescent fangs",

        "a street filled with powerful adventurers all sitting quietly"
      + " while they lovingly stroke pet turkeys they are holding",

        "a woodpecker on a tree, whose eyes seem to follow you",

        "a flaming black broadsword gripped in an uplifted black-clad"
      + " fist",

        "an overhead view of a forest filled with lost"
      + " adventurers, all peering at various flowers and plants,"
      + " wandering in circles around a small hut that none seem to"
      + " find",

        "a disappointed warrior, standing over the corpse of a slain"
      + " balrog, frowning at a rather unimpressive flaming whip that"
      + " lies on the ground",

        "a parrot being interrogated by a slender, mysterious drow",

        "a massive angry female goblin smashing her foes with wild"
      + " joyous fury",

        "a bald flabby goblin stepping over hundreds of corpses"
      + " outside the Redeye Inn in Minas Morgul while an ancient"
      + " menacing human Nazgul observes in the shadows",

        "a group of oddly-clothed young male humans peering at"
      + " strange green-glowing boxes that are situated one next to"
      + " the other at long tables in a white, brightly lit room. There"
      + " are no females present, and the young men look like they"
      + " need to bathe",

        }) ) + ".\n";

    return ptxt;
} /* exa_painting */


/*
 * Function name:        check_exit
 * Description  :        If the waitress is present, she won't let people
 *                       into the kitchen
 * Returns      :        0 - allow passage, 1 - prevent passage
 */
public int
check_exit()
{
    if (!present("_sparkle_pub_bartender"))
    {
        return 0;
    }

    if (this_player()->id("_merc_guild_cook"))
    {
        Innkeeper_npc->command("glare cook");
        Innkeeper_npc->command("say You overslept! Typical ...");
        return 0;
    }

    if (this_player() == Innkeeper_npc)
    {
        return 0;
    }

    if (!CAN_SEE(Innkeeper_npc, this_player()))
    {
        write("You manage to slip past the waitress ...\n");
        return 0;
    }

    Innkeeper_npc->command("glare " + this_player()->query_real_name());
    Innkeeper_npc->command("emote shrieks: Keep out of the kitchen!!");

    if (this_player()->query_wiz_level())
    {
        Innkeeper_npc->command("emote mutters: Oh ... a wizard. Very well,"
          + " but don't slow down the cook! We're already backed up!");
        return 0;
    }

    return 1;
} /* check_exit */


/*
 * Function name:       summon_innkeeper
 * Description  :       restore npc as needed
 * Arguments    :       int silent - true if we don't want the waitress
 *                                   to act as if she's just showing up.
 *                      mixed annoyer - a player who is ringing the
 *                                    bell when the barkeep is present
 *                                    (default = 0)
 */
public void
summon_innkeeper(int silent = 0, mixed annoyer = 0)
{
    object    npc;
    int       annoying_summons = 0;
    string    stxt;

    if (!present("_sparkle_pub_bartender"))
    {
        npc = clone_object(NPC_DIR + "bartender");
        npc->move(this_object());
        npc->command("emote arrives.");

        if (!silent)
        {
            npc->command("shout Alrighty! Let's get some sessions"
              + " going! Who's first?");
        }

        npc->arm_me();

        set_innkeeper_npc(npc);
        set_innkeeper_name("ellingnor");
    }
    else
    {
        if (annoyer)
        {
            annoying_summons = annoyer->query_prop(ANNOYING);

            switch (annoying_summons)
            {
                case 0:
                    stxt = " chirps: I'm right here, you goofball!"
                      + " If you want to <order> something, just say"
                      + " so!";
                    break;
                case 1:
                    stxt = " chirps: Hey. Knock it off with the bell.";
                    break;
                case 2:
                    stxt = " chirps: I said no more bell from you!";
                    break;
                case 3:
                    stxt = " chirps: NO ... MORE ... BELL.";
                    break;
                case 4:
                    stxt = " screams: Kiki, get this annoying idiot"
                      + " out of here!!!";
                    set_alarm(0.0, 0.0,
                      &Innkeeper_npc->kick_out_of_bar(annoyer,
                       "being annoying"));
                    break;
                default:
                    stxt = " screams: Not you again!!! KIKI!!";
                    set_alarm(0.0, 0.0,
                      &Innkeeper_npc->kick_out_of_bar(annoyer,
                       "being annoying"));
                    break;
            }

            Innkeeper_npc->command("emote" + stxt);
            annoying_summons++;
            annoyer->add_prop(ANNOYING, annoying_summons);
        }
        else if (!silent)
        {
            Innkeeper_npc->command("emote wipes down the bar and"
              + " looks around for some clean glasses.");
        }
    }
} /* summon_innkeeper */


/*
 * Function name:       reset_room
 * Description  :       clone sign, etcetera
 * Arguments    :       float summon delay - the delay we want for the
 *                                           arrival of the waitress.
 *                                           Default = 2.0
 */
public void
reset_room()
{
    set_alarm(0.0, 0.0, &summon_innkeeper(1));

    /* reset wood to default amount */
    set_wood(-1);

    /* if fire's gone out and Ellingnor is around to rekindle it,
     * start it up again.
     */
    if (query_fire_state() != FIRE_BURNING &&
        present("_sparkle_pub_bartender", this_object()))
    {
        Innkeeper_npc->command("say Oh, the fire's out! Let's get"
          + " things cozy again ...");
        Innkeeper_npc->command("emote tosses some dry logs on"
          + " the fire in the chimney and sets it freshly ablaze.");
        set_fire_state(FIRE_BURNING);
    }
} /* reset_room */


/*
 * Function name: init
 * Description:   set up the commands
 */
void
init()
{
    ::init();

    init_fire();
    init_room_chairs();

    add_action(do_buy, "buy",   0);
    add_action(do_buy, "order", 0);
    add_action(ring_bell, "hit");
    add_action(ring_bell, "ring");
    add_action(ring_bell, "smack");
    add_action(do_session, "session");
} /* init */


/*
 * Function name: money_text
 * Description:   convert a price in cc into a formatted
 *                string, giving the price using the smallest
 *                number of coins
 * Arguments:     am - the price in cc
 * Returns:       the string, eg: 1 pc  2 gc 10 sc  9 cc
 */
public string
money_text(int am)
{
    int    *arr = MONEY_SPLIT(am),
            ind = NUM;
    string  txt = "";

    while (--ind >= 0)
    {
        if (arr[ind])
            txt += sprintf("%2d %2s ", arr[ind], COIN_TYPES[ind]);
        else
            txt += "      ";
    }

    return txt;
} /* money_text */


/*
 * Function name: price_long
 * Description:   print the menu
 *                dummy example
 * Usage:         in create_room()
 *                add_item(({"menu", "prices", }), price_long());
 *                add_cmd_item(({"menu", "prices", }), "read", price_long());
 */
string
price_long()
{
   return ("\n"
     + "          +----------------------------------------+\n"
     + "          |.--------------------------------------.|\n"
     + "          ||  Welcome to the Boar's Head Tavern!  ||\n"
     + "          ||                                      ||\n"
     + "          ||     Things you can <order> here:     ||\n"
     + "          ||                                      ||\n"
     + "          ||  Beer                       1 silver ||\n"
     + "          ||  Wine                       3 silver ||\n"
     + "          ||  Iron Delving Export Brew   4 silver ||\n"
     + "          ||  Our Special Brew           6 silver ||\n"
     + "          ||  Captains' Rum              1 gold   ||\n"
     + "          ||  Firebreather               2 gold   ||\n"
     + "          ||                                      ||\n"
     + "          ||  Water                     10 copper ||\n"
     + "          ||                                      ||\n"
     + "          | >------------------------------------< |\n"
     + "          ||  Drinking <session>  1 platinum      ||\n"
     + "          | >------------------------------------< |\n"
     + "          ||             NO BRAWLING              ||\n"
     + "          ||             NO THIEVING              ||\n"
     + "          ||       NO SPITTING ON THE FLOOR       ||\n"
     + "          | `------------------------------------' |\n"
     + "          +----------------------------------------+\n");
} /* price_long */


/*
 * Function name: buy_item
 * Description:   clone and move the bought item
 * Arguments:     item   - filename of item to clone
 *                number - heap size of item
 *                desc   - description for item
 */
void
buy_item(string item, int number = 1, string desc = 0)
{
    object  ob,
            tp = this_player();

    ob = clone_object(item);
    ob->set_heap_size(number);

    if (ob->move(tp))
    {
        write("Since you cannot carry that much, " + LOW_INNKEEPER(tp)
            + " sets the " + ob->query_short() + " down in front of you.\n");
        if (ob->move(TO))
            ob->move(TO, 1);
    }

    if (strlen(desc))
    {
        say(QCTNAME(tp) + " orders " + desc + ".\n");
    }
    else
    {
        say(QCTNAME(tp) + " orders " + LANG_ASHORT(ob) + ".\n");
    }
} /* buy_item */


/*
 * Function name: buy_it
 * Description:   identify the item the player tries to buy
 *                dummy example
 * Arguments:     item_name - the name
 *                number    - the amount
 *                pay_type  - coins to pay with
 *                get_type  - coins for change
 * Returns:       0/1 - failure/success
 */
public int
buy_it(string item_name, int number, string pay_type, string get_type)
{
    string      file,
                ware;
    int         price;

    switch (lower_case(item_name))
    {
        case "ale":
        case "ales":
        case "beer":
        case "beers":
        case "cold ale":
        case "cold ales":
        case "cold beer":
        case "cold beers":
        case "glass":
        case "glasses":
        case "glass of ale":
        case "glasses of ale":
        case "glass of beer":
        case "glasses of beer":
                file = OBJ_DIR + "beer";
                ware = "cold beer";
                price = 12;
            break;
        case "wine":
        case "wines":
        case "red wine":
        case "red wines":
        case "cup":
        case "cups":
        case "cup of wine":
        case "cups of wine":
        case "cup of red wine":
        case "cups of red wine":
                file = OBJ_DIR + "wine";
                ware = "cup of red wine";
                price = 36;
            break;
        case "export":
        case "exports":
        case "export brew":
        case "export brews":
        case "iron delving":
        case "iron delvings":
        case "iron delving export":
        case "iron delving exports":
        case "iron delving brew":
        case "iron delving brews":
        case "iron delving export brew":
        case "iron delving export brews":
                file = "/d/Ansalon/estwilde/obj/" + "brewcraft_beermug";
                ware = BREWCRAFT_MENU;
                price = 24;
            break;
        case "special":
        case "specials":
        case "our special":
        case "our specials":
        case "special brew":
        case "specials brew":
        case "special brews":
        case "our special brew":
        case "our specials brew":
        case "our special brews":
                file = OBJ_DIR + "special_brew";
                ware = "special brew";
                price = 72;
            break;
        case "rum":
        case "rums":
        case "captain rum":
        case "captain rums":
        case "captains rum":
        case "captains rums":
        case "captain's rum":
        case "captain's rums":
        case "flagon":
        case "flagons":
        case "flagon of rum":
        case "flagons of rum":
        case "flagon of captain rum":
        case "flagons of captain rum":
        case "flagons of captains rum":
        case "flagon of captains rum":
        case "flagon of captain's rum":
        case "flagons of captain's rum":
                file = OBJ_DIR + "rum";
                ware = "flagon of rum";
                price = 144;
            break;
        case "firebreather":
        case "firebreathers":
        case "fire":
        case "fires":
        case "fire breather":
        case "fire breathers":
                file = OBJ_DIR + "firebreather";
                ware = "firebreather";
                price = 288;
            break;
        case "water":
        case "waters":
        case "mug of water":
        case "mug of waters":
        case "mug":
        case "mugs":
        case "mugs of water":
                file = OBJ_DIR + "water";
                ware = "mug of water";
                price = 10;
            break;
        case "drink":
        case "drinks":
            notify_fail("Well, sure, but which one? Read the menu"
              + " and be a bit more specific!\n");
            return 0;
            break;
        case "session":
        case "sessions":
        case "drinking session":
        case "drinking sessions":
            notify_fail("To do that, just use the <session>"
              + " command.\n");
            return 0;
            break;
        default:
            notify_fail(
              "You'd better check the menu again. That isn't on it.\n");
            return 0;
            break;
    }

    if (can_afford(price, number, ware, pay_type, get_type))
    {
        buy_item(file, number, ware);
    }

    return 1;
} /* buy_it */


public int
hook_query_max_items()
{
    return 6;
} /* hook_query_max_items */


/*
 * Function name: do_buy
 * Description:   parse the command
 * Arguments:     str - argument to command verb
 * Returns:       0/1 - failure/success
 */
public int
do_buy(string str)
{
    object  tp = this_player();
    int     number,
            the_max = hook_query_max_items();
    string  item_name,
            pay_type,
            get_type;

    if (!strlen(str))
    {
        notify_fail("What do you wish to buy? You can <read menu> for"
          + " a list of available items.\n");
        return 0;
    }

    if (this_object()->query_prop(OBJ_I_LIGHT) < 1)
    {
        if (present("_sparkle_pub_bartender"))
        {
            if (CAN_SEE_IN_ROOM(tp))
            {
                write(CAP_INNKEEPER(tp)
                  + " says: What the ... ? I can't see a dang thing!\n");
            }
            else
            {
                write("Someone says: What the ... ?  I can't see a"
                  + " dang thing!\n");
            }
        }
        else
        {
            if (CAN_SEE_IN_ROOM(tp))
            {
                write("There is no one here to serve you.\n");
            }
            else
            {
                /* strictly speaking, we should let them figure out that
                 * there's no response by making no response, but someone's
                 * sure to report that as a bug.
                 */
                 write("You hear no response to your request for service.\n");
            }
        }
        return 1;
    }

    if (!present("_sparkle_pub_bartender"))
    {
        write("There is no one here to serve you. You notice a large"
          + " brass bell mounted on the bar, however. You can probably"
          + " <ring bell> to try and get some service.\n");
        return 1;
    }

    str = lower_case(str);

    if ((sscanf(str,"%d %s for %s and get %s",
                number, item_name, pay_type, get_type) != 4) &&
        (sscanf(str,"%s for %s and get %s",
                item_name, pay_type, get_type) != 3))
    {
        get_type = "";
        if ((sscanf(str,"%d %s for %s", number, item_name, pay_type) != 3) &&
            (sscanf(str,"%s for %s", item_name, pay_type) != 2))
        {
            pay_type = "";
            if (sscanf(str, "%d %s", number, item_name) != 2)
                item_name = str;
        }
    }

    if (number <= 0)
        number = 1;

    if (number > the_max)
    {
        notify_fail("I'm afraid you cannot buy more than " + the_max
                  + " items at a time.\n");
        return 0;
    }

    return buy_it(item_name, number, pay_type, get_type);
} /* do_buy */


public void
hook_not_got_coin_type(string pay_type, object tp)
{
    write(CAP_INNKEEPER(tp) + " chirps: Well, if you had any "
      + pay_type + " coins, we might get somewhere!\n");
    Innkeeper_npc->command("emote sighs and returns to other matters.");
} /* hook_not_got_coin_type */


public void
hook_not_enough_coin_type(string pay_type, string ware, object tp)
{
    write(CAP_INNKEEPER(tp) + " says: Looks like you are a few "
      + pay_type + " coins short. Get a few more if"
      + " you want to buy " + ware + "!\n");
} /* hook_not_enough_coin_type */


public void
hook_not_enough_money(object tp, string ware)
{
    write(CAP_INNKEEPER(tp) + " chirps: This isn't a potluck, friend! You"
      + " better find the money to pay for it, first!\n");
} /* hook_not_enough_money */


/*
 * Function name: can_afford
 * Description:   Test if this_player has more money on him than the price
 * Arguments:     price  - the price in cc
 *                number - the amount to buy
 *                ware   - a description of the item to buy
 *                pay_type - coins to pay with
 *                get_type - coin type for change
 * Returns:       0/1 - failure/success
 */
public int
can_afford(int price, int number, string ware, string pay_type, string get_type)
{
    object  tp = TP;
    int    *money_arr,
            tot_price;
    string  coin_pay_text,
            coin_get_text;

    tot_price = price * number;

    if (sizeof(money_arr = pay(tot_price, tp, pay_type, 0, 0, get_type)) == 1)
    {
        switch (money_arr[0])
        {
            case 2:
                hook_not_got_coin_type(pay_type, tp);
                break;
            case 1:
                hook_not_enough_coin_type(pay_type, ware, tp);
                break;
            default:
                hook_not_enough_money(tp, ware);
                break;
        }
        return 0;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM * 2 - 1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM - 1));

    if (number == 1)
    {
        write("You order " + LANG_ADDART(ware) + " and pay "
          + coin_pay_text +".\n");
    }
    else
    {
        write("You order " + LANG_WNUM(number) + " " + LANG_PWORD(ware)
          + " and pay " + coin_pay_text + ".\n");
    }

    if (strlen(coin_get_text))
    {
        write(CAP_INNKEEPER(tp)+" nods quickly and hands you "
          + coin_get_text + " back in change.\n");
    }

    return 1;
} /* can_afford */


/*
 * Function name:       set_innkeeper_npc
 * Description  :       use a real npc as the innkeeper
 * Arguments    :       object npc -- the npc
 *
 * This should be called each time the npc is cloned.
 */
public void
set_innkeeper_npc(object npc)
{
    Have_innkeeper = 1;
    Innkeeper_npc = npc;
} /* set_innkeeper_npc */


/*
 * Function name:       set_innkeeper_name
 * Description  :       customize the innkeeper name when not
 *                      using a real npc as the innkeeper
 * Arguments    :       string arg -- the name (e.g., "the waiter")
 */
public void
set_innkeeper_name(string name)
{
    if ( strlen(name) )
    {
        Innkeeper_name = lower_case(name);
        Innkeeper_Name = capitalize(name);
    }
} /* set_innkeeper_name */


/*
 * Function name:        ring_bell
 * Description  :        allow players to summon the innkeeper if
 *                       the innkeeper is not present.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
ring_bell(string arg)
{
    object *weapon;
    string  wshort = "knuckles";

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    weapon = this_player()->query_weapon(-1);

    if (sizeof(weapon) && objectp(weapon[0]))
    {
        wshort = weapon[0]->short();
    }

    write("With a swift stroke of your " + wshort
      + ", you give the bell a good ring. CLANGGG!\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " rings the bar-mounted bell with a swift stroke of "
      + this_player()->query_possessive() + " " + wshort
      + ". CLANGGG!\n", this_player());

    summon_innkeeper(0, this_player());

    return 1;
} /* ring_bell */


/*
 * Function name:        fire_desc
 * Description  :        VBFC for room and items that vary w/ fire
 * Arguments    :        string arg -- what we're looking at
 * Returns      :        string description
 */
public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();

    switch (arg)
    {
        case "firepit":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "The chimney is enormous, taking up a large"
                      + " portion of the western wall. Within it,"
                      + " flames dance beneath a huge boar's head"
                      + " which hangs above the brightly burning fire.\n";
                    break;
                case FIRE_UNLIT_WOOD:
                    return "The chimney is enormous, taking up a large"
                      + " portion of the western all. A huge boar's head"
                      + " hangs above a stack of wood which no one"
                      + " has bothered to light.\n";
                    break;
                default:        /* FIRE_ASHES */
                    return "The chimney is enormous, taking up a large"
                      + " portion of the western wall. A huge boar's head"
                      + " hangs above a pile of ashes within it.\n";
                    break;
            }
            break;
        case "fire":
            if (fire_state == FIRE_BURNING)
            {
                return "A fire burns brightly beneath the boar's head"
                  + " on the chimney.\n";
            }
            return "There doesn't seem to be any fire burning.\n";
            break;
        case "wood":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "The wood in the chimney burns"
                             + " brightly beneath the boar's head,"
                             + " emitting a pleasant warmth.\n";
                    break;
                case FIRE_UNLIT_WOOD:
                    return "Unlit wood is piled in the"
                             + " chimney beneath the boar's head.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "You find no firewood, only ashes.\n";
                    break;
            }
            break;
        case "firelight":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "The fire casts light and shadows which dance"
                      + " throughout the room with the movement of the"
                      + " flames. You also see some type of magical"
                      + " torches hanging from the ceiling.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "There is no fire. Thus, you see none."
                      + " There are a few magical torches hanging"
                      + " from the ceiling, however.\n";
                    break;
            }
            break;
        case "darkness":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "The firelight provides ample light in here,"
                      + " so there isn't much of that.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "Someone really should light the fire so that"
                      + " there is more warmth and the ability to see"
                      + " better in here.\n";
                    break;
            }
            break;
        case "ashes":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "Beneath the brightly burning fire,"
                             + " ashes cover the bottom of the"
                             + " chimney.\n";
                    break;
                case FIRE_UNLIT_WOOD:
                    return "Beneath the wood, ashes cover the"
                             + " bottom of the chimney.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "Ashes cover the bottom of the"
                             + " chimney.\n";
                    break;
            }
            break;
        case "boar":
            switch (fire_state)
            {
                case FIRE_BURNING:
                    return "A huge boar's head (quite obviously the"
                      + " namesake of this establishment) hangs above"
                      + " the blazing fire in the chimney, its"
                      + " snout and whiskers glinting in the glow.\n";
                    break;
                default:    /* FIRE_ASHES */
                    return "A huge boar's head (quite obviously the"
                      + " namesake of this establishment) hangs above"
                      + " the dark chimney, only dimly visible in"
                      + " the murkey atmosphere.\n";
                    break;
            }
            break;
        default:    /* room long description */
            return "You stand in the Boar's Head Tavern, a"
                  + " watering hole as noisy and filled with local"
                  + " flavour as one could hope to expect in the"
                  + " hub of Genesis. "

                  + ((fire_state == FIRE_BURNING)
                  ? "A huge fire blazes in an enormous chimney on the"
                    + " far wall, casting bouncing light off"
                  : "Someone has let the fire go out (a shame!) in"
                    + " an enormous chimney in the far wall, creating"
                    + " murkey darkness which surrounds")

                  + " the many patrons who have come to drink their cares"
                  + " away. Numerous tables provide a place to"
                  + " <sit>, and a large menu hangs painted on"
                  + " a board above the bar counter.\n\n";
            break;
    }
    return "";  /* "cannot" happen */
} /* fire_desc */


/*
 * Function name:       do_sit
 * Description  :       mask parent to block "sit" and "sit down"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if (!arg ||
        arg == "down")
    {
        notify_fail("Sit where?\n");
        return 0;
    }
    return ::do_sit(arg);
} /* do_sit */


/*
 * Function name:       do_sit_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You find a place at one of the tables, and take a seat.\n");
    say(QCTNAME(pl) + " finds a place at one of the tables and takes"
      + " a seat.\n");
} /* do_sit_msgs */


/*
 * Function name:       do_stand_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You stand up from the table at which you were seated.\n");
    say(QCTNAME(pl) + " stands up from " + pl->query_possessive()
      + " table.\n");
} /* do_stand_msgs */


/*
 * Function name:        look_tables
 * Description  :        VBFC for block; include occupants
 * Returns      :        string -- the desc
 */
public string
look_tables()
{
    return "Somewhat crowded tables are arranged around the room,"
      + " offering a place to <sit> for anyone who might want to"
      + " <order> a drink or begin a <session> in the bar.\n"
         + sitting_on_chair(BLOCK_NAME, this_player(), 0, 0);
} /* look_block */


/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from table occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:       show_subloc
 * Description  :       generate "foo is sitting ..." msg
 *                      for living's desc.
 * Arguments    :       string subloc -- the subloc
 *                      object pl -- the player
 *                      object for_obj -- who's doing the looking
 * Returns      :       string -- the "is sitting" msg
 *
 * This is a mask from the room_chairs.c code, because I don't want to
 * have it be someone sitting at "the" anything ... I want my own
 * verbage here.
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    string      name;
    mixed       *chairptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (subloc != SITTING_S_SUBLOC)
    {
        return pl->show_subloc(subloc, pl, for_obj);
    }

    if (strlen(name = pl->query_prop(LIVE_S_SITTING)) &&
        pointerp(chairptr = query_room_chairs()[name]))
    {
        if (for_obj != pl)
        {
            return capitalize(pl->query_pronoun()) + " is sitting " +
                chairptr[3] + " one of the " + name + ".\n";
        }
        return "You are sitting " + chairptr[3] + " one of the"
          + " tables.\n";
    }
    return "";
} /* show_subloc */


/*
 * Function name:       sitting_on_chair
 * Description  :       describe who's on the chair.
 * Arguments    :       string name -- the chair name
 *                      object for_obj -- who's doing the looking
 *                      int namesonly -- if true, returns only
 *                              the names of occupants, suitably
 *                              formatted, + " is" or " are"
 *                      int definite -- if true, we use a
 *                                     definite article when
 *                                     we modify the ledge name
 * Returns      :       string -- the desc of the occupants
 *
 * N.B. if namesonly is false, the returned string will have an ending
 * newline. if namesonly is true, it will not. it follows that if you
 * want to embed info about who's sitting on what in the middle of 
 * other text, you set namesonly to true and append your own location
 * string (e.g., " at the desk.").
 *
 * Ugh. I had to mask this one from the parent, too. I just didn't like
 * having the prepositions locked into "a" or "the". I needed "one"
 * or "various." (Gorboth)
 */
public string
sitting_on_chair(string name, object for_obj, int namesonly, int definite = 1)
{
    mixed       *chairptr;
    object      *occupants,
                *others;
    int         i,
                s;
    string      *names,
                 desc,
                 my_art,
                 some = " one of the ";

    my_art = (definite ? " the " : " a ");

    if (!strlen(name) ||
        !pointerp(chairptr = query_room_chairs()[name]) ||
        !(s = sizeof(occupants = chairptr[2])))
    {
        return "";
    }

    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }

    if (s == 1)
    {
        if (occupants[0] != for_obj) 
        {
            desc =  occupants[0]->query_Art_name(for_obj) + " is";
        }
        else
        {
            desc = "You are";
        }
    }
    else
    {
        some = " various ";
        if ((i = member_array(for_obj, occupants)) < 0)
        {
            names = occupants->query_art_name(for_obj);
        }
        else
        {
            others = exclude_array(occupants, i, i);
            names = others->query_art_name(for_obj)  +  ({ "you" });
        }
        desc =  capitalize(COMPOSITE_WORDS(names)) + " are";
    }

    if (!namesonly)
        desc += " sitting " + chairptr[3] + some + name + ".\n";
    return desc;
} /* sitting_on_chair */


/*
 * Function name:        kick_for_brawling
 * Description  :        Kick players out if they try to start any
 *                       type of fight in the bar.
 * Returns      :        null string
 */
public string
kick_for_brawling()
{
    object tp = this_player();

    tp->catch_msg("You decide to start a pub brawl!\n");
    tell_room(this_object(), QCTNAME(tp) + " decides to start a"
      + " pub brawl!\n", tp);

    summon_innkeeper(1);

    Innkeeper_npc->command("shout Hey! We'll not have any of that!!");
    Innkeeper_npc->command("scowl " + tp->query_real_name());
    Innkeeper_npc->command("emote points at the sign.");
    Innkeeper_npc->command("shout You're outta here!");

    Innkeeper_npc->kick_out_of_bar(tp, "brawling");

    return "";
} /* kick_for_brawling */


/*
 * Function name:        kick_for_stealing
 * Description  :        Kick players out if they try to do any
 *                       stealing in the bar.
 * Returns      :        null string
 */
public string
kick_for_stealing()
{
    object tp = this_player();

    /* Kenders' auto-borrow code will make it impossible for them
     * to complete sessions in here if we boot them for steal
     * attempts which they cannot control. So, we'll make a special
     * routine for them, which prevents the stealing, but does not
     * kick them out of the bar.
     */
    if (tp->query_guild_name_occ() ==
            "Secret Society of Uncle Trapspringer")
    {
        return "Your hand wanders absentmindedly (and innocently!)"
          + " toward the pocket of a nearby patron. A low growl"
          + " from above the bar draws your attention to the"
          + " massive hellcat, who has risen from her perch and"
          + " looks ready to eat you! Your hand jerks behind your"
          + " back and you smile at the cat who sits slowly back"
          + " down again. Sheesh! You weren't"
          + " even doing anything wrong!! How typical ...\n";
    }

    tp->catch_msg("You eye the crowd for an easy pocket to pick...\n");

    summon_innkeeper(1);

    Innkeeper_npc->command("scowl "+tp->query_real_name());
    Innkeeper_npc->command("shout Hey, keep your hands off my"
      + " patrons!");
    Innkeeper_npc->command("emote points at the sign.");
    Innkeeper_npc->command("shout Get out of here, you"
      + " thieving loser!");

    Innkeeper_npc->kick_out_of_bar(tp, "stealing");

    return "Oooof!\n";
} /* kick_for_stealing */


/*
 * Function name:        ban_patron
 * Description  :        Ban someone from coming into the bar for
 *                       a period of time if they break the rules
 *                       or annoy the bartender too much.
 * Arguments    :        object who - the player to ban
 */
public void
ban_patron(object who)
{
    who->add_prop(BANNED_FROM_PUB, time() + BANNED_DURATION);
} /* ban_patron */


/*
 * Function name:        judge_entry
 * Description  :        When someone tries to come into the tavern,
 *                       the bouncer will stop them if they got
 *                       kicked out and have not let the duration
 *                       of their ban elapse.
 * Arguments    :        object who - the player to judge
 * Returns      :        int - 1: cannot enter, 2: can enter
 */
public int
judge_entry(object who)
{
    int     ban_time = who->query_prop(BANNED_FROM_PUB);
    int     time_remaining = ban_time - time();
    string  ban_msg = "";

    if (time_remaining < 1)
    {
        return 0;
    }

    switch(time_remaining)
    {
        case 0:
            return 0;
            break;
        case 1..10:
            ban_msg = "just a few more seconds";
            break;
        case 11..60:
            ban_msg = "another minute or so";
            break;
        case 61..180:
            ban_msg = "a few more minutes";
            break;
        case 181..600:
            ban_msg = "a little while";
            break;
        case 601..1800:
            ban_msg = "quite a wait";
            break;
        case 1801..2700:
            ban_msg = "more than a half hour";
            break;
        case 2701..3600:
            ban_msg = "nearly an hour";
            break;
        case 3601..5400:
            ban_msg = "over an hour";
            break;
        default:
            ban_msg = "a couple of hours";
            break;
    }

    who->catch_tell("As you approach the door of the tavern, a low"
      + " growl from within lets you know that you aren't welcome."
      + " You figure it will be " + ban_msg + " before that"
      + " damned cat-thing lets you back in.\n");

    return 1;
} /* judge_entry */


/*
 * Function name:        do_session
 * Description  :        allow players to begin a drinking session
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
do_session(string arg)
{
    if (!SESSION_AVAILABLE)
    {
        summon_innkeeper(1);
        Innkeeper_npc->command("say Sessions are coming as soon as"
          + " enough people have helped me out. I will need a much"
          + " greater supply of my secret ingredient!");
        return 1;
    }

    if (check_session(this_player()))
    {
        return 1;
    }

    if (this_player()->rested_exp_active())
    {
        write("You've still not recovered from your last drinking"
          + " session, and "
          + lower_case(this_player()->rested_exp_status_msg()) + "\n");
        return 1;
    }

    if (!can_afford(1728, 1, "drinking session", "platinum", "copper"))
    {
        return 1;
    }

    write("You begin a session!!\n");
    this_player()->start_resting();
    this_player()->add_prop(LIVE_I_PUB_SESSION, time());

    return 1;
} /* do_session */


/*
 * Function name:        session_duration
 * Description  :        calculate the duration of a player's
 *                       drinking session so far
 * Arguments    :        object who - the player
 * Returns      :        int - the duration in seconds (heartbeats)
 */
public int
session_duration(object who)
{
    return (time() - this_player()->query_prop(LIVE_I_PUB_SESSION));
} /* session_duration */


/*
 * Function name:        duration_text
 * Description  :        provide a text readout of the general duration
 *                       that a player has been at their session.
 * Arguments    :        object who - the player to judge
 * Returns      :        string - the message
 */
public string
duration_text(object who)
{
    string  duration_msg = "";

    switch(session_duration(who))
    {
        case 0:
            return 0;
            break;
        case 1..10:
            duration_msg = "just a few seconds.";
            break;
        case 11..60:
            duration_msg = "a minute or so.";
            break;
        case 61..180:
            duration_msg = "a few minutes.";
            break;
        case 181..600:
            duration_msg = "a little while.";
            break;
        case 601..1600:
            duration_msg = "not quite half an hour yet.";
            break;
        case 1601..1800:
            duration_msg = "nearly half an hour.";
            break;
        case 1801..2700:
            duration_msg = "over half an hour - too long, perhaps.";
            break;
        case 2701..3600:
            duration_msg = "nearly an hour - too long, perhaps.";
            break;
        case 3601..5400:
            duration_msg = "over an hour - too long, probably!";
            break;
        default:
            duration_msg = "... how long now? You can hardly remember!";
            break;
    }

    return duration_msg;
} /* duration_text */


/*
 * Function name:        check_session
 * Description  :        see if the player is in a session, and give them
 *                       info on how long they have been at it. Serves
 *                       in some cases to block exits out of the bar.
 * Arguments    :        object who - the player
 * Returns      :        int 1 - in session, 0 - not in session
 */
public int
check_session(object who = this_player())
{
    if (who->query_prop(LIVE_I_PUB_SESSION))
    {
        who->catch_tell("You are currently enjoying your drinking"
          + " session here in the pub, having been at it for "
          + duration_text(who)
          + " You can <end session> if you feel ready to get on with"
          + " your adventures.\n");

        if (who->query_wiz_level())
        {
            who->catch_tell("Because you are a wizard, you leave"
              + " anyway.\n");
            return 0;
        }

        return 1;
    }

    return 0;
} /* check_session */
