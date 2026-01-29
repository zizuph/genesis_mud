/*
 * File name  : quiker.c
 * Date       : 15.03.2004 
 * Modified by: Blizzard, from the new standard kender base
 *
 *
 * Note by Navarre, November 22th 2005:
 *
 * This Npc carried many inappropriate items that was created.
 * Those items has been altered.
 * - I removed the arrows from this npc, he doesn't use arrows.
 *   So there is no reason for him to have extremely good arrows.
 * - I made him a little smaller, he was quite big.
 * - Changed the clones, so only the ring clones unique now, since its magical.
 */


/*
 *
 * This base can be used all by itself to produce a full-featured
 * kender from Goodlund, or can be changed to accomodate the
 * circumstances.
 *
 * Intended redefinable functions:
 * public void create_kender()
 * public void set_kender_origin()
 * 
 * Optional redefinable functions:
 * public void kender_act()
 * public string steal_something()
 * public void kender_walk() -- You must call this in create_kender
 *                              in order to activate it. Otherwise your
 *                              kender needs to be made to move in a
 *                              different way. If you want your kender
 *                              to stick to a single area, you must make
 *                              your own unique movement in create_kender.
 *
 * Gwyneth - September - October 1999
 * 
 * steal_something() taken and modified slightly from the
 * original kender base (by Aridor) to take alignment into
 * account. Kender are apt to steal more valuable things
 * the more evil a person is.
 *
 * Modification log:
 * Gwyneth - fixed a few errors in setup. Fixed stealing worn/wielded items.
 */

#pragma strict_types

inherit "/d/Ansalon/std/monster";
inherit "/lib/unique";

#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

#define KOBJ  "/d/Ansalon/goodlund/kendermore/obj/"
#define QOBJ  "/d/Krynn/qualinesti/"

/* Prototypes */
public string  query_kender_origin();
public void    arm_me();
public string  set_kender_origin();
public string  kender_extra_long();

string gKenderOrigin = "";
string gHair         = "";
string gEyes         = "";
string gColour       = "";


/* Function name : create_kender
 * Description   : sets up the kender, redefine for custom made kender
*/
public void 
create_kender() 
{
    add_act("@@kender_walk",1);
}

/* Function name : create_krynn_monster
 * Description   : sets up the monster 
 */
void
create_krynn_monster()
{
    int i = random(20);

    set_name("quiker");
    set_living_name("quiker");
    set_title("Lightfoot");
    set_race_name("kender");
    set_gender(G_MALE);
    set_adj("energetic");
    add_adj("wide-eyed");
    set_extra_long(kender_extra_long); /* Hair and eyes */

    set_alignment(100);     
    set_knight_prestige(-200);   /* Bad knights, killing kender */
    set_pick_up(1);             /* Pick things up */

    /* Random size */
    set_stats(({80 + i, 130 + i, 80 + i, 55 + i, 55 + i, 80 + i}));

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_SNEAK, 90);
    set_skill(SS_HIDE, 90);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_LANGUAGE, 65);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_OPEN_LOCK, 75);
    set_skill(SS_PICK_POCKET, 75);

    add_prop(LIVE_I_QUICKNESS, 150);
    add_prop(NPC_I_NO_FEAR, 1);            /* Able to attack anything */
    add_prop(NPC_I_NO_RUN_AWAY, 1);        /* Won't wimpy */
    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and " +
        "hands it back saying, 'See, sometimes I do remember to " +
        "return things!'\n");

    set_act_time(2);
    add_act("say Ykies! These dogs never get bored?! I already am!");
    add_act("say This forest is so fun! First I meet elves who share " +
        "their arrows with me and now these dogs!");
    add_act("emote says 'Yay, I wish I had a few pine cones to throw at " +
        "these dogs!' and bursts into an uncontrollable fit of giggle.");
    add_act("say We have splendid woods in Hylo too, but this forest " +
        "seem to be sooooo big!");
    add_act("emote says 'While I'm sitting here I could sketch a map!' " +
        "and starts looking for something in his pouches.");
    add_act("say I don't know why the elves keep losing things even " +
        "in this big forest, it's not easy to find them again!");
    add_act("exa ground");
    add_act("@@steal_something");
    add_act("@@kender_act");

    set_cact_time(2);
    set_default_answer("Your question falls on deaf ears as the kender " +
        "is distracted by something new.\n");

    set_kender_origin();  /* From Hylo or Goodlund */
    arm_me();             /* Clone equipment */

    create_kender();      /* Set things up */
}

/* Function name : arm_me
 * Description   : Clone and wear/wield equipment
*/

public void
arm_me()
{
    int num = random(100);
    /* Random junk cloned into inventory. Add more in alpha order. */
    string *junk = ({(KOBJ + "bells"), (KOBJ + "brick"),
        (KOBJ + "butterscotch"), (KOBJ + "candle"),
        (KOBJ + "candlestick"), (KOBJ + "caramel"),
        (KOBJ + "carving"), (KOBJ + "cfeather"),
        (KOBJ + "cloth"), (KOBJ + "doll"),
        (KOBJ + "gbead"), (KOBJ + "licorice"),
        (KOBJ + "lollipop"), (KOBJ + "maple"),
        (KOBJ + "metal"), (KOBJ + "pbottle"),
        (KOBJ + "ring"), (KOBJ + "rock"),
        (KOBJ + "sbottle"), (KOBJ + "shell"),
        (KOBJ + "stone"), (KOBJ + "string2"),
        (KOBJ + "taffy"), (KOBJ + "map")});

    setuid();
    seteuid(getuid(TO));

    /* Random hoopaks */
    if (num > 75)
        clone_object(KOBJ + "lwood_hoopak")->move(TO);
    else if (num > 50)
        clone_object(KOBJ + "hick_hoopak")->move(TO);
    else if (num > 25)
        clone_object(KOBJ + "oak_hoopak")->move(TO);
    else
        clone_object(KOBJ + "yew_hoopak")->move(TO);

    clone_object(QOBJ + "arm/blouse")->move(TO);
    clone_object(QOBJ + "obj/apple")->move(TO);
    clone_object(QOBJ + "obj/apple")->move(TO);
    clone_object(QOBJ + "obj/apple")->move(TO);
    clone_object(QOBJ + "obj/apple")->move(TO);
    
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(QOBJ + "arm/kender_boots")->move(TO);
    clone_unique(QOBJ + "obj/copper_ring", 5)->move(TO);
    clone_object(KOBJ + "vest")->move(TO);
    clone_object(KOBJ + "cloak")->move(TO);
    clone_object(QOBJ + "arm/fur_gloves")->move(TO);

    command("wear all");
    command("wield hoopak");

    MONEY_MAKE_SC(random(15) + 5)->move(TO);  /* Some coins */
}

/* Function name : kender_extra_long
 * Description   : Puts together the extra long description
 * Returns       : The extra long description.
*/

public string
kender_extra_long()
{
    string extra_string = "";
    if (TO->query_stat(0) < 75)
        extra_string = (C(HE(TO)) + " is very short and skinny for " + 
            "a kender.\n");
    else if (TO->query_stat(0) < 95)
        extra_string = (C(HE(TO)) + " is of normal length and of normal " + 
            "width for a kender.\n");
    else
        extra_string = (C(HE(TO)) + " is extremely tall and fat for " + 
            "a kender.\n");

    /* Goodlund kender have long hair: topknots, braids, pony tails, etc. */
    if (gKenderOrigin == "Goodlundg")
    {
        switch(random(4))
        {
            case 0:
                gHair = "tied up in a topknot";
                break;

            case 1:
                gHair = "tied into a long braid";
                break;

            case 2:
                gHair = "pulled back in a pony tail";
                break;

            case 3:
                gHair = "left loose in a combed mane";
                break;
        }
    }

    /* Hylo kender have short shag haircuts */
    if (gKenderOrigin == "Hylo")
        gHair = "cropped short in a shag style";

    /* Hair colours */
    switch(random(7))
    {
        case 0:
            gColour = "sandy blonde";
            break;

        case 1:
            gColour = "dark brown";
            break;

        case 2:
            gColour = "coppery red";
            break;

        case 3:
            gColour = "red-orange";
            break;

        case 4:
            gColour = "auburn";
            break;

        case 5:
            gColour = "light brown";
            break;

        case 6:
            gColour = "dark blonde";
            break;
    }

    /* Eye colours */
    switch(random(5))
    {
        case 0:
            gEyes = "pale blue";
            break;

        case 1:
            gEyes = "sea green";
            break;

        case 2:
            gEyes = "olive coloured";
            break;

        case 3:
            gEyes = "light brown";
            break;

        case 4:
            gEyes = "hazel";
            break;
    }

    return (C(HE(TO)) + " has " + gColour + " hair which is " + gHair + ".\n" + 
        C(HE(TO)) + " has " + gEyes + " eyes.\n" + extra_string + 
        C(HE(TO)) + " seems to be a " + query_kender_origin() + " kender " + 
        "from Krynn.\n");
}

/* Function name : set_kender_origin
 * Description   : Set this to Goodlund or Hylo (case sensitive)
*/

public void
set_kender_origin()
{
    gKenderOrigin = "Hylo";
}

/* Function name : query_kender_origin
 * Description   : Finds the origin of the kender
 * Returns       : The kender's origin
*/

public string
query_kender_origin()
{
    return gKenderOrigin;
}

/* Function name : kender_walk
 * Description   : Moves the kender to a random next room
*/

public void
kender_walk()
{
    string *raw_dirs = environment(TO)->query_exit_cmds();
    if (sizeof(raw_dirs) != 0)
    {
        if (random(2) == 1)
        {
            set_m_in("skips in with pouches bouncing");
            set_m_out("skips away with pouches bouncing");
            command("emote raises " + HIS(TO) + " hand in the air, " + 
                "telling everyone to set their faces to the sun, their " + 
                "feet to the moons and follow the wind.");
            command(raw_dirs[random(sizeof(raw_dirs))]);
            set_m_in("arrives");
            set_m_out("leaves");
        }
        else
            command("sneak " + raw_dirs[random(sizeof(raw_dirs))]);
    }
    else log_file("move_fail", ctime(time()) + " " + file_name(E(TO)) +
        ".\n");
}

/* Function name : kender_act
 * Description   : Gives kender emotes
*/

public void
kender_act()
{
    switch(random(15))
    {
        case 0:
            command("emote claps " + HIS(TO) + " hands in delight.");
            break;

        case 1:
            command("emote dances around joyfully.");
            break;

        case 2:
            command("emote bursts into an uncontrollable fit of giggles.");
            break;

        case 3:
            command("emote grins broadly, a mischievous glint in " + HIS(TO) +
                " eyes.");
            break;

        case 4:
            command("emote collapses in gales of high-pitched laughter.");
            break;

        case 5:
            command("emote asks: Do you have a story to tell? I love " +
                "stories!\n" + C(HE(TO)) + " sits down on the ground and " + 
                "gazes up at you delightedly in expectation.");
            break;

        case 6:
            command("emote stops to smooth " + HIS(TO) + " hair and " +
                "pull some leaves out.");
            break;

        case 7:
            command("emote starts rummaging through " + HIS(TO) + " pockets " +
                "and pouches.");
            break;

        case 8:
            command("emote declares: Every new road needs a hoopak!\n" +
                C(HE(TO)) + " lifts " + HIS(TO) + " hoopak above " + HIS(TO) +
                " head and thrusts the pointed end into the ground firmly.");
            break;

        case 9:
            command("emote plops " + HIM(TO) + "self down on the ground " +
                "and starts rummaging through the contents of " + HIS(TO) + 
                " pouches.");
            break;

        case 10:
            command("emote skips a little step, almost ready to break into " +
                "a joyful dance.");
            break;

        case 11:
            command("emote struggles to keep a solemn face, but a " +
                "tiny amused smile and a giggle escape anyway.");
            break;

        case 12:
            command("emote claps a hand over " + HIS(TO) + " mouth " +
                "to stifle a giggle.");
            break;

        case 13:
            command("emote fidgets restlessly, staring off into " + 
                "the distance.");
            break;

        case 14:
            command("emote furrows up " + HIS(TO) + " brow in " +
                "concentration as " + HE(TO) + " thinks of the " + 
                "possibilities.");
            break;

        case 15:
            command("emote holds " + HIS(TO) + " hands behind " + 
                HIS(TO) + " back saying: 'I don't have anything, honest!'");
            break;

        case 16:
            command("emote does " + HIS(TO) + " best impression " + 
                "of a dwarf, folding " + HIS(TO) + " arms across " + 
                HIS(TO) + " chest and snorting in disgust.");
            break;

        case 17:
            command("emote crosses " + HIS(TO) + " eyes and lets a " + 
                "little drool escape from " + HIS(TO) + " slack lips " + 
                "as " + HE(TO) + " does " + HIS(TO) + " best imitation " + 
                "of a goblin.");
            break;

        case 18:
            command("emote does " + HIS(TO) + " best impression of a " + 
                "hobbit, pulling " + HIS(TO) + " belt tight, while " + 
                "looking mournfully around for a bite to eat.");
            break;

        case 19:
            command("emote does " + HIS(TO) + " best impression of an " + 
                "elf, sticking " + HIS(TO) + " nose high into the air " + 
                "and saying in a snobbish voice, 'Kender are not " + 
                "descended from elves!'");
            break;

        case 20:
            command("emote does " + HIS(TO) + " best impression of " + 
                "a gnome, getting a very worried expression on " + 
                HIS(TO) + " face, " + HE(TO) + " says, 'OhIDoHopeMyLatest" + 
                "NosePickingMachineDoesn'tExplodeInYourFace!'");
            break;

        case 21:
            command("emote does " + HIS(TO) + " best impression of a " + 
                "human, biting " + HIS(TO) + " nails as if afraid, " + 
                "saying, 'Eeks! There's a mouse! I'm afraid of " + 
                "everything!'");
            break;

        case 22:
            command("emote shakes your hand, greeting you in a friendly " + 
                "manner. You'd better check your belongings.");
            break;

        case 23:
            command("emote stands on " + HIS(TO) + " tiptoes to get a " + 
                "better view of " + HIS(TO) + " surroundings.");
            break;
    }
}

/* Function name : steal_something
 * Description   : Steals something from the livings around.
*/

public string
steal_something()
{
    object *ob = ({});
    object who, what;
    string str = "";

    if (E(TO))
        ob = all_inventory(E(TO));
    if (!ob)
        return "";
    ob = FILTER_PLAYERS(ob);
    if (ob && sizeof(ob))
        who = ob[random(sizeof(ob))];
    else
        return "";
    ob = all_inventory(who);
    if (ob && sizeof(ob))
        what = ob[random(sizeof(ob))];
    else
        return "";
    if (what->query_worn() || what->query_wielded() || what->query_held() ||
     what->query_no_show() || what->query_no_show_composite() ||
     what->query_prop(OBJ_M_NO_STEAL) || what->query_prop(OBJ_M_NO_DROP) ||
     what->query_prop(OBJ_M_NO_GIVE)||(who->query_wiz_level()))
        /* The check for wiz-level was added by Macker after
        a kender stole Grace's racenamer. *grin* */
        return "";
    if (what->query_value() < (0 - who->query_alignment()) && random(2))
    {
        if (who->query_skill(SS_AWARENESS) > random(50) + 50)
            who->catch_msg("You catch " + QTPNAME(TO) + " hands wandering " +
                "curiously through your belongings.\n");
        else
        {
            what->move(TO);
         }
    }
    else
    {
        switch(random(21))
        {
            case 0:
                str = "Guess I found it somewhere.";
                break;

            case 1:
                str = "Now how did THAT get in there?";
                break;

            case 2:
                str = "You must have dropped it!";
                break;

            case 3:
                str = "I was just holding it for you.";
                break;

            case 4:
                str = "I was just keeping it safe for you. Someone " +
                    "could steal it if you're not careful!";
                break;

            case 5:
                str = "This looks just like yours, doesn't it?";
                break;

            case 6:
                str = "Aren't you glad I found it?";
                break;

            case 7:
                str = "I was just looking at it for a minute!";
                break;

            case 8:
                str = "I forgot I had it!";
                break;

            case 9:
                str = "You walked away before I could give it back.";
                break;

            case 10:
                str = "Maybe it fell into my pocket.";
                break;

            case 11:
                str = "You put it down and I didn't think you " + 
                    "wanted it anymore.";
                break;

            case 12:
                str = "You mean that wasn't my pocket?";
                break;

            case 13:
                str = "How interesting! I wonder where that came from?";
                break;

            case 14:
                str = "You said you didn't want it anymore.";
                break;

            case 15:
                str = "It must be magical because it just appeared " + 
                    "in my pouch!";
                break;

            case 16:
                str = "I was only cleaning it for you.";
                break;

            case 17:
                str = "Someone must have put it in my pouch by mistake.";
                break;

            case 18:
                str = "I was afraid someone else would take it.";
                break;

            case 19:
                str = "It was just laying there, honest.";
                break;

            default:
                str = "You really should be more careful with your things.";
        }

        command("emote chatters merrily: " + str);
        tell_room(E(TO), QCTNAME(TO) + " gives " + LANG_ASHORT(what) + " to " +
            QTNAME(who) + ".\n", who);
        who->catch_msg(QCTNAME(TO) + " gives you " + LANG_ASHORT(what) + ".\n");
    }
    return "";
}

