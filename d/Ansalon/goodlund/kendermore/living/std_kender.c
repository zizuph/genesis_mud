/*
 * Std_kend.c
 *
 * A Standard Kender for Kendermore.
 *
 * Mhyrmarius
 * 
 * Modified by Gwyneth, May - June, 1999
 *
 * Navarre April 9th 2009, Kendermore doesn't have (m)any 
 * visitors. Perhaps by increasing the size of the kenders
 * to match more with what we have in the realm of players 
 * these days will help this a bit.
 *
 * Navarre June 23rd 2009, adding check on size of obvious exits
 *                         to fix runtime on the walk commands.
 */

inherit "/d/Ansalon/std/monster";
inherit "/d/Krynn/std/equip";

#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <money.h>
#include <macros.h>
#include <filter_funs.h>
#include <poison_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include DL_CLOCK

#define VMASTER "/d/Ansalon/guild/society/room/vote_room"

/* Variable adjectives for the first part of the description */

string *adjs=({"whistling", "excited", "happy", "unkempt", "carefree",
    "nosy", "inquisitive", "busy", "cheerful", "talkative", "bouncy", 
    "friendly", "curious", "grinning", "merry", "smiling", "energetic"});


/* Variable adjectives for the second description. Split so we don't
*  wind up with a brown-haired black-haired male kender or the like.*/

string *adjs2=({"brown-haired", "black-haired", "red-haired", "blond-haired",
    "long-haired", "gray-haired", "tanned", "wrinkled", "chubby", "slender",
    "young", "red-cheeked", "brown-eyed", "green-eyed", "round-cheeked",
    "blue-eyed", "grey-eyed", "wide-eyed", "dimpled"});

string *junk = ({(KOBJ + "bells"), (KOBJ + "brick"), (KOBJ + "butterscotch"),
    (KOBJ + "candle"), (KOBJ + "candlestick"), (KOBJ + "caramel"),
    (KOBJ + "carving"), (KOBJ + "cfeather"), (KOBJ + "cloth"), (KOBJ + "doll"),
    (KOBJ + "gbead"), (KOBJ + "licorice"), (KOBJ + "lollipop"),
    (KOBJ + "maple"), (KOBJ + "metal"), (KOBJ + "pbottle"), (KOBJ + "ring"),
    (KOBJ + "rock"), (KOBJ + "sbottle"), (KOBJ + "shell"), (KOBJ + "stone"),
    (KOBJ + "string2"), (KOBJ + "taffy"), (KOBJ + "map")});

int night_emote, day_emote;
string *raw_dirs;
string statstr;
string glob_adj1, glob_adj2;
string query_statstrs() {return statstr;}
void setup_kender();
string query_kender_activity();
void arm_me();
string kender_act();
string kender_walk();

int should_walk = 1;

void
create_krynn_monster()
{
    string *adjecs;
    set_name("my_kender");
    set_race_name("kender");
    add_adj(adjs[random(17)]);  /* Chooses the first adjective randomly. */
    add_adj(adjs2[random(19)]); /* Chooses the second adjective randomly. */
    adjecs=query_adjs();
    glob_adj1 = adjecs[0]; glob_adj2 = adjecs[1];
    set_gender(random(2)); /* Female or male randomly */
    set_long("This is a " + adjecs[0] + " " + adjecs[1] + 
        " citizen of Kendermore, most likely just back from a long journey. " + 
        "A race known on Krynn to " +
        "be as bothersome as a mosquito, kender resemble young teenage " + 
        "humans. They have childish faces and pointed ears. Even at an old " + 
        "age, a kender's only sign of age are wrinkles, laugh lines, and " + 
        "perhaps a larger selection of taunts and stories. " + 
        "Their insatiable curiousity is " + 
        "reminiscent of young children, as is their ability to taunt and " + 
        "find mischief. " + 
        "@@query_kender_activity@@" + "\n" + capitalize(HE(TO)) +
        "@@query_statstrs@@"+".\n");
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and hands it " + 
        "back, saying 'See, sometimes I do remember to return things!'\n");
    set_act_time(2); /* Kender are very active. */
    add_act("@@kender_walk@@"); /* Sets up emotes and random actions */
                               /* depending on the time of day.     */

    set_cact_time(3);
    add_cact("swing hoopak");
    add_cact("emote taunts: I've seen blind, drunken gully dwarves with " + 
        "more grace than you have!");
    add_cact("emote taunts: Don't you have a terribly empty feeling -- in " + 
        "your skull?");
    add_cact("emote taunts: Looks CAN kill, yours are killing me!");
    add_cact("emote taunts: Did your parents lose a bet with a black robe?");

    setup_kender(); /* Sets stats for big, medium and small kender. */
    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 50);     /* Defence skill */
    set_skill(SS_WEP_POLEARM, 50); /* Polearm skill for hoopak using */
    set_skill(SS_WEP_KNIFE, 50);   /* Knife skill for knife using */
    set_skill(SS_AWARENESS, 50);   /* Kender are pretty aware */
    set_skill(SS_2H_COMBAT, 50);   /* To use knife and hoopak at once */

    set_exp_factor(70);

    if (IS_CLONE)
	    arm_me();
}

string
steal_something()
{
    int i;
    object *ob;
    object who, what;
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
    if (what->query_no_show() || what->query_no_show_composite() ||
     what->query_prop(OBJ_M_NO_STEAL) || what->query_prop(OBJ_M_NO_DROP) ||
     what->query_prop(OBJ_M_NO_GIVE)||(who->query_wiz_level()))
        /* The check for wiz-level was added by Macker after
        a kender stole Grace's racenamer. *grin* */
        return "";
    if (what->query_value() < (who->query_average_stat() - 20) && random(2))
    {
        if (who->query_skill(SS_AWARENESS) > random(50) + 50)
            who->catch_msg("You catch " + QTNAME(TO) + " rifling through " + 
                "your private belongings.\n");
        else
        {
            what->move(TO);
         }
    }
    else
    {
        switch(random(3))
        {
        case 0:
            command("say Where did this come from?");
            if (random(2))
                break;
        case 1:
            command("say Is that yours?");
            if (random(2))
                break;
        case 2:
            command("say I must have found it somewhere.");
            if (random(2))
                break;
        case 3:
            command("say You must have lost it. What would have happened if " + 
                "I hadn't found it?");
        }

        tell_room(QCTNAME(TO) + " gives " + LANG_ASHORT(what) + " to " +
            QTNAME(who) + ".\n", who);
        who->catch_msg(QCTNAME(TO) + " gives you " + LANG_ASHORT(what) + ".\n");
    }
    return "";
}

/* Function name : Setup kender
 * Description : Sets kenders stats to three different types: big, average,
 *     and small, giving descriptions for each for the long description.
 * Returns : Null
*/

void 
setup_kender()
{
/* The size of kender will vary between small, average and big */

	int big=random(10); /* Size is random */
	switch (big)
	{
	case 0..4:
	   set_stats(({40+random(20),80+random(20),50+random(20),
               40+random(20),50+random(20),60+random(20)}));
	   statstr=" looks rather small";
	break;
	case 5..7:
	   set_stats(({100+random(20),140+random(20),120+random(20),
               80+random(20),90+random(20),100+random(20)}));
	   statstr=" looks like an average kender";
	break;
	case 8..10:
	   set_stats(({120+random(20),160+random(20),130+random(20),
               115+random(20),130+random(20),110+random(20)}));
	   statstr=" looks big for a kender";
	break;
	}
}

/* Function name : Kender activity
 * Description : Gets activity descriptions for the long description
 *     depending on the time of day.
 * Returns : The activity string
*/

string 
query_kender_activity()
{
    string str;
    switch (GET_TIMEOFDAY)
    {    
    case TOD_NIGHT:
	str ="This kender should be sound asleep, since the hour " + 
            "is late.";
	break;
    case TOD_DAWN:
	str = "This kender is yawning and rubbing " +
        HIS(TO) + " eyes this early in the morning.";
	break; 
    case TOD_DAY:
	str = "This kender is running about, doing all sorts of " + 
	"things. Chattering madly and whistling merrily seem to be the " +
	"favourite activities at the moment, however.";
	break; 
   case TOD_TWILIGHT:
	str = "This kender is yawning and, looking for a place " +
        "to sleep for a bit.";
	break;
    }    
return str;
}

/* Function name : Arm me
 * Description : Clones, wears and wields coins, armours and weapons.
 *     Blouses for females, shirts for males. Large knives for big kender,
 *     medium knives for average kender, and small knives for small kender.
 *     Hoopak, leggings, boots, cloak standard to all.
 * Returns : Null
*/

void
arm_me()
{
    string *items = ({ });
    if (query_stat(1) > 69)
        items += ({ KOBJ + "std_knife" });
    if (query_stat(1) > 39 && query_stat(1) < 70)
	items += ({ KOBJ + "medium_knife" });
    if(query_stat(1) < 40)
	    items += ({ KOBJ + "small_knife" });

	items += ({ KOBJ + "hoopak" });
	items += ({ KOBJ + "leggings" });
	items += ({ KOBJ + "boots" });
	items += ({ KOBJ + "cloak" });
	items += ({ KOBJ + "vest" });
	items += ({ junk[random(24)], junk[random(24)] });

    if (TP->query_gender() == G_FEMALE)
        items += ({ KOBJ + "blouse" });
	else
		items += ({ KOBJ + "shirt" });

    equip(items);
    add_prop(OBJ_M_HAS_MONEY, ({ 0, random(10) + 4 }));
}

/* Function name : Attacked by
 * Description : Wield weapons and comment when attacked.
 * Returns : Null
*/

public void 
attacked_by(object ob)
{
    ::attacked_by();
    command("wield all");

    if ((GET_TIMEOFDAY == NIGHT) && (TO->query_attack() == 0))
    {
        night_emote = 0;
        tell_room(E(TO), QCTNAME(TO) + " looks very startled.\n", TO);
    }

    if(!VMASTER->query_banished(ob->query_real_name()) &&
        !VMASTER->query_member(ob->query_real_name()))
        {
            write("A kender nearby sees your attack and runs off as " +
                "fast as he can.\n");
            VMASTER->add_banished(ob->query_real_name());
        }
}

/* Function name : Kender walk
 * Description : Gives a 50/50 chance to either do a random emote (kender_act)
 *     or to choose an obvious exit and take it during the day. random_move 
 *     turned out to be too slow for a kender. During the night, it will
 *     just call kender act, and not wander.
 * Returns : Null
*/

void
kender_walk()
{
int i;
    if(GET_TIMEOFDAY == NIGHT)
    {
        night_emote = 1;
        command (kender_act());
    }
    else 
    {
        day_emote = 1;
        i = random(2);
        if (i == 1)
            command(kender_act());  
        if (i == 0)
        {
            string *raw_dirs = environment(TO)->query_obvious_exits();
	    // Adding check to avoid index out of bounce.
	    if(sizeof(raw_dirs) > 0 && should_walk)
	    {
	      command(raw_dirs[random(sizeof(raw_dirs))]);
	    }
        }
    }
}

/* Function name : Kender act
 * Description : Chooses a random emote dependant on the time of day and
 *     kender description.
 * Returns : The random emote
*/

string
kender_act()
{
int num;
    if(GET_TIMEOFDAY == NIGHT) 
    {
        num = random(3); /* Make night emotes random */

        if (day_emote)
        {
            day_emote = 0;
            tell_room(E(TO), QCTNAME(TO) + " slowly closes " + HIS(TO) +
                " eyes, fighting to stay awake.\n" + C(HE(TO)) + " curls up " + 
                "in a comfortable spot, and falls asleep.\n", TO);
        }
    }

    else 
    {
        num = random(21); /* Make day emotes random */
        num += 3;         /* Differentiate from night emotes */

        if (night_emote)
        {
            night_emote = 0;
            tell_room(E(TO), QCTNAME(TO) + " rubs " + HIS(TO) +
                " eyes as " + HE(TO) + " rises, fully awake.\n", TO);
        }
    }

    if(num == 0) 
        return "emote snores softly.";

    if(num == 1)
    {
        if(glob_adj1 == ("whistling")) /* If first adjective is whistling */
            return ("emote whistles in " + HIS(TO) + " sleep.");

        if(glob_adj1 != ("whistling")) return "emote snores loudly.";
    }

    if(num == 2) 
        return ("emote giggles in " + HIS(TO) + " sleep.");

    if(num == 3) 
        return "emote chatters merrily about nothing in particular.";

    if(num == 4) 
        return "emote begins to look bored, never a good sign considering " + 
            "the mischievous nature of kender.";

    if(num == 5) 
        return "emote skips merrily.";

    if(num == 6) 
        return "emote is filled with wonder about all the nice things " + 
            "here and eyes them curiously.";

    if(num == 7)
    {
        if (glob_adj1 == ("whistling")) /* If first adjective is whistling */
            return "emote whistles an uplifting melody."; 
        else
        {
            command (steal_something()); 
            return "";
        }
    }

    if(num == 8)
    {
        if (glob_adj2 == ("brown-haired")) 
            return ("emote tosses " + HIS(TO) + " brown topknot " +  
            "over " + HIS(TO) + " shoulder.");
        else
        {
             command("get all from corpse");
             return "emote flips head over heels.";
        }
    }

    if(num == 9)
    {
        if(glob_adj2 == ("chubby"))
            return "emote idly chews on a piece of candy.";
        else
            return "emote bursts into an uncontrollable fit of giggles.";
    }

    if(num == 10)
    {
        if(glob_adj2 == ("green-eyed"))
            return "emote blinks " + HIS(TO) + " bright green eyes.";
        else
        {
            command(steal_something());
            return "";
        }
    }

    if(num == 11)
    {
        if(glob_adj2 == ("brown-eyed"))
            return "emote gets a mischievious look in " + HIS(TO) + 
                " big brown eyes.";
        else
        {
            command("get all from corpse");
            return "emote gasps in astonishment.";
        }
    }

    if(num == 12)
    {
        if(glob_adj2 == ("blue-eyed"))
            return "emote looks at you with " + HIS(TO) + " wide blue eyes.";
        else
        {
            command(steal_something());
            return "";
        }
    }

    if(num == 13)
    {
        if(glob_adj2 == ("grey-eyed"))
            return "emote peers curiously at you with " + HIS(TO) + 
                " sparkling grey eyes.";
        else
            return "emote looks up wide-eyed and says that awful word " + 
                "that sends most adventurers experienced with kender " + 
                "running, 'Oops!'.";
    }

    if(num == 14)
    {
        if(glob_adj2 == ("black-haired"))
            return "emote closes " + HIS(TO) + " eyes as a cool breeze " + 
                "blows through " + HIS(TO) + " black topknot.";
        else
            return "emote sticks " + HIS(TO) + " tongue out.";
    }

    if(num == 15)
    {
        if(glob_adj2 == ("blond-haired"))
            return "emote absentmindedly tosses " + HIS(TO) + " blond " + 
                "topknot over " + HIS(TO) + " shoulder.";
        else
        {
            command("get all from corpse");
            return "emote twiddles " + HIS(TO) + " thumbs.";
        }
    }

    if(num == 16)
    {
        if(glob_adj2 == ("wrinkled"))
            return "emote smiles at you, wrinkles crinkling.";
        else
            return "emote smiles joyfully at you.";
    }

    if(num == 17)
    {
        if(glob_adj2 == ("red-haired"))
            return "emote hops up and down, making " + HIS(TO) + " red " + 
                "topknot fly into disarray.";
        else
            return "emote hops up and down with endless energy.";
    }

    if(num == 18)
    {
        if(glob_adj2 == ("long-haired"))
            return "emote brushes " + HIS(TO) + " long topknot out " + 
                "of " + HIS(TO) + " face.";
        else
            return "emote chatters: Hello there!";
    }

    if(num == 19)
    {
        if(glob_adj2 == ("tanned"))
            return "emote turns " + HIS(TO) + " face to the sun, soaking " + 
                "up the rays.";
        else
            return "emote chatters: I think I'll go visit the Ruins today.";
    }

    if(num == 20)
    {
        if(glob_adj1 == ("curious"))
        {
            command("get all from corpse");
            return "emote chatters: Everyone says I'm curious, even for " + 
                "a kender! That's pretty curious isn't it? Hey, what's " + 
                "that shiny thing there?";
        }
        else
            return "emote chatters: Have you ever seen a griffon? I saw " + 
                "one once!";
    }

    if(num == 21)
    {
        if(glob_adj1 == ("friendly"))
            return "shake all";
        else
        {
           command("get all from corpse"); 
           return "peek goblin";
        }
    }

    if(num == 22)
    {
        if(glob_adj1 == ("bouncy"))
        {
            command("get all from corpse");
            return "bounce all";
        }
        else
            return "emote bumps into you.\nHmmm, are you sure you're not " + 
                "missing anything?";
    }

    if(num == 23)
    {
        if(glob_adj1 == ("talkative"))
            return "emote chatters so much that you hold your hands over " + 
                "your ears.";
        else
       {
            command("get all from corpse");
            return "emote gets a mischievous twinkle in " + HIS(TO) + " eyes.";
       }
    } 
}

public void
set_should_walk(int i)
{
  should_walk = i;
}

public void
do_die(object killer)
{
    command("remove vest");
    ::do_die(killer);
}

