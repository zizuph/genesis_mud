// CREATURE: hallowe'en black cat

    /* Calia Domain

    HISTORY
    [99-10-06] Created by Sheytansha
    PURPOSE
    A little black cat created to put some fright and fun into the
    lives of players on Hallowe'en.

    */

// INCLUSIONS AND DEFINITIONS

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <formulas.h>

inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/creature";
inherit "/std/combat/unarmed";

// GLOBAL VARIABLES

string *Start_Rooms =
    ({
    "/d/Calia/sheytansha/workroom",
    "/d/Calia/uhclem/workroom",
    });

string *good_emotes = ({"pet", "hug", "snuggle", "cuddle", "kiss"});
string *bad_emotes = ({"kick", "scold", "spit", "knee", "tease"});

// FUNCTIONS

//

int
good_emote_hook(string emote, object actor, string adverb)

{

    string tp = actor->query_real_name();
    object cat_fur = present("cat fur", actor);

    if (!cat_fur)

    {

        cat_fur = clone_object("/d/Calia/weenware/cat_fur");
        cat_fur->move(actor);

    }

    switch (emote)

    {

        case "pet" :
        cat_fur->add_luck_level(-1);
        command("emote soaks up the attention like a sponge.");
        return 1;
        break;

        case "hug" :
        cat_fur->add_luck_level(-1);
        command("purr");
        return 1;
        break;

        case "cuddle" :
        case "snuggle" :
        cat_fur->add_luck_level(-2);
        command("purr");
        command("lick " + tp);
        return 1;
        break;

        case "kiss" :
        cat_fur->add_luck_level(-2);
        command("snuggle " + tp);
        return 1;
        break;

    }

    return 0;

}

//

int
bad_emote_hook(string emote, object actor, string adverb)

{

    string tp = actor->query_real_name();
    object cat_fur = present("cat fur", actor);

    if (!cat_fur)

    {

        cat_fur = clone_object("/d/Calia/weenware/cat_fur");
        cat_fur->move(actor);

    }

    switch (emote)

    {

        case "knee" :
        case "kick" :
        cat_fur->add_luck_level(3);
        command("growl " + tp);
        return 1;
        break;

        case "scold" :
        cat_fur->add_luck_level(1);
        command("cower");
        return 1;
        break;

        case "spit" :
        cat_fur->add_luck_level(2);
        command("emote hisses up at " + QTNAME(actor) + " in rebuttal.");
        return 1;
        break;

        case "tease" :
        cat_fur->add_luck_level(1);
        command("pout");
        return 1;
        break;

    }

    return 0;

}

//

void
emote_hook(string emote, object actor, string adverb, object *oblist)

{

    if (!sizeof(oblist) || objectp(query_attack())) return;

    if (good_emote_hook(emote, actor, adverb)) return;

    if (bad_emote_hook(emote, actor, adverb)) return;

}

// Function:  go_cat_go()

/*

Purpose:  transport the cat to a new location.

Arguments:  none

Returns:  nothing

*/

void
go_cat_go()

{

    int n = random(sizeof(Start_Rooms) - 1);

    move_living("X", Start_Rooms[n]);

    Start_Rooms = Start_Rooms - ({Start_Rooms[n]}) + ({Start_Rooms[n]});

    log_file("halloween", "At " + ctime(time()) + " I went to " +
        file_name(environment()) + ".\n");

}

// Function:  eat_cat_eat()

/*

Purpose:  make the cat eat some food he has been given.

Arguments:  none

Returns:  nothing

*/

void
eat_cat_eat()

{

    object *my_stuff = all_inventory(this_object());

    command("eat all");

    if (sizeof(all_inventory(this_object())) < sizeof(my_stuff))

    {

        command("emote licks his chops thoroughly to get every last" +
            " bit of flavor and nutrition.");

    }

    command("drop all");

}

// Function:  enter_inv(ob, from)

/*

Purpose:  this function is automatically called when an object enters this
object's inventory.  It is used here to detect and eat food given by players.

Arguments:  ob, the object entering the inventory; from, the object (most
likely a player) from which it came.

Returns:  nothing

*/

void
enter_inv(object ob, object from)

{

    object cat_fur = present("cat fur", from);

    ::enter_inv(ob, from);

    /*  Food and herbs both contain query_amount; eat food only.  */

    if (ob->query_amount() > 0 && !ob->query_herb_name())

    {

        set_alarm(1.0, 0.0, eat_cat_eat);

        if (!cat_fur)

        {

            cat_fur = clone_object("/d/Calia/weenware/cat_fur.c");
            cat_fur->move(from);
            cat_fur->set_luck_level(-100);

        }

    }

    else

    {

        command("drop all");

    }

}

// Function:  look_at_cat

/*

Purpose:  Returns a description, but will also dispense a bad luck timer to
    the player if he/she hasn't gotten one already when they look at
    the cat.

Arguments:  none

Returns:  A string containing the cat's description.

*/

string
look_at_cat()

{

    object tp = this_player();
    object cat_fur;

    string text = "This rather thin black cat appears not to have had" +
        " a decent meal in quite some time. It seems more than one" +
        " person believes this poor helpless animal is the harbinger" +
        " of bad luck. ";

    if (!present("cat fur", tp))

    {

        cat_fur = clone_object("/d/Calia/weenware/cat_fur.c");
        cat_fur->move(tp);

        text = text + "As you look at the scraggly cat, he appears to" +
            " notice you too! He wanders over to you and rubs up against" +
            " your leg, leaving a collection of black cat hairs on you.\n";

        tell_room(environment(), "The cat notices " + QTNAME(tp) +
            " and decides to move in for a closer look.\n", tp);

    }

    else

    {

        text = text + "The cat sits back on his haunches, having already" +
            " investigated anything of interest to him on your person.\n";

    }

    return text;

}

// Function:  kill_cat

/*

Purpose:  Removes the cat from harm's way, and makes sure the player gets
    their just deserts for trying to abuse the cat.  Cat will be moved
    to a different coded starting point, rather than recloned.

Arguments:  none

Returns:  A text string stating what happens to the cat.

*/

string
kill_cat()

{

    object tp = this_player();
    object cat_fur = present("cat fur", tp);

    string text = "You go to attack the cat viciously," +
        " but much to your amazement the black cat turns into a witch!" +
        " She climbs onto her broomstick and flies into the air over" +
        " your head, cackling evilly, 'Oh you're going to regret your" +
        " cat-hating ways! You just wait and see!!!'\nWith that, she" +
        " zooms out of sight. Hmm... Maybe you shouldn't have done that.\n";

    tell_room(environment(), "To your absolute horror " + QTNAME(tp) +
        " attacks the defenseless cat! Amazingly enough, however, the cat" +
        " turns into a witch! She climbs onto her broomstick and comes" +
        " to hover over " + QTNAME(tp) + "'s head, cackling,'Oh you're"  +
        " going to regret your cat-hating ways! You just wait and see!!!'" +
        " before she flies out of sight.\n", tp);

    if (!cat_fur)

    {

        cat_fur = clone_object("/d/Calia/weenware/cat_fur.c");
        cat_fur->move(tp);
        cat_fur->set_luck_level(100);

    }

    move_living("M", Start_Rooms[random(sizeof(Start_Rooms) - 1)]);

    tell_room(environment(),
        "A thin black cat slinks in.\n");

    return text;

    log_file("halloween", "At " + ctime(time()) + " I was attacked by " +
        this_player()->query_name() + ".\n");

}

// CREATURE DEFINITION

void
create_creature()

{

    set_name("cat");
    set_short("thin black cat");
    set_adj("thin black");
    set_race_name("cat");
    set_long("@@look_at_cat@@");
    set_hp(500);
    set_alignment(100);
    set_stats(({4,10,8,10,10,20}));

    //  COMBAT ATTRIBUTES

    set_skill(SS_UNARM_COMBAT, 35);
    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "sharp claws");
    set_attack_unarmed(2, 15, 6, W_IMPALE, 20, "sharp teeth");
    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");

    //  PROPERTIES

    add_prop(LIVE_I_MAX_EAT, 1000000);      /*  big appetite  */
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_ACCEPT_GIVE, 0);     /*  will accept food  */
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_DROP, 0);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_M_NO_ATTACK, "@@kill_cat@@");

    set_act_time(10);
    add_act("emote mewls at you hungrily.");
    add_act("emote twitches his tail as he sniffs the air around him.");
    add_act("emote arcs his back and glares at a butterfly menacingly.");
    add_act("emote flicks his ears and peers around cautiously.");

    set_random_move(15);
    set_m_out("bolts");
    set_m_in("scampers in");
    set_mm_out("bolts out like a bat out of hell.");
    set_mm_in("comes tearing into the room like his tail's on fire.");

    // START MOTION LOOP

    /*
     *  Thanks to Aridor and Jaypeg for providing rooms for the cat to visit in 
     *  Shire, Ansalon, and Krynn.    
     */

    Start_Rooms =
        ({
        "/d/Calia/domain_office",
        "/d/Calia/gelan/rooms/square_eastend_n",
        "/d/Calia/mountain/road/road19",
        "/d/Calia/argos/metro/rooms/lroad8",
        "/d/Shire/eastroad/western/er1n",
        "/d/Krynn/solamn/palan/city/street15",
        "/d/Krynn/que/newports/village",
        "/d/Ansalon/balifor/port_balifor/room/city09"
        });

    set_alarm(900.0, 900.0, go_cat_go);

}
