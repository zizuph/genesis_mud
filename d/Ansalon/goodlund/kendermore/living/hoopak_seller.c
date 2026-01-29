/* Danalin, the hoopak seller in Kendermore */

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/act/action.c";
inherit AM_FILE

int make_hoopak_id = 0;

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("danalin");
    set_race_name("kender");
    set_title("Treeskipper, Hoopak Maker of Kendermore");
    add_name("shopkeeper");
    set_adj("bright");
    add_adj("auburn-haired");
    set_long("This cheerful kender makes hoopaks. Her long auburn hair " + 
        "is tied up in a topknot, which is decorated with many beads " + 
        "and brightly coloured feathers. She idly carves out pieces of " + 
        "wood into forked staves while sitting on a wide carpet.\n");
    set_gender(G_FEMALE);
    set_introduce(1);

    set_stats(({140,140,140,140,140,140}));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_alignment(350);
    set_knight_prestige(-40);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and hands it " +
        "back, saying 'See, sometimes I do remember to return things!'\n");
}


/* Function name : Arm me
 * Description : Clones, wears and wields misc. items, armours and weapons.
 * Returns : Null
*/
void
arm_me()
{
    setuid();
    seteuid(getuid(TO));
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);
    clone_object(KOBJ + "cape")->move(TO);
    clone_object(KOBJ + "blouse")->move(TO);
    clone_object(KOBJ + "vest")->move(TO);

    command("wear all");
    command("wield knife");
}

/* Function name : Reset id
 * Description : Resets the make_hoopak_id to 0 so a player can buy a 
 *     hoopak when Danalin is done with the previous hoopak.
 * Returns : Null
*/

void
reset_id()
{
    make_hoopak_id = 0;
}

/* Function name : make_hoopak
 * Description : Shows the hoopak making routine, and calls the function that
 *     loads the right hoopak.
 * Returns : Null
*/

void
make_hoopak(string str1)
{
    object buyer = TP;
    string metal;

    if (str1 == "yew")
        metal = "steel";
    if ((str1 == "lemonwood") || (str1 == "hickory"))
        metal = "iron";
    if (str1 == "oak")
        metal = "brass";

    {
        set_alarm(1.0,0.0, &command("emote chatters: " +
            "Oh, " + str1 + ", that's such a nice wood!"));
        set_alarm(3.0,0.0, &command("emote picks up a long shaft of " + 
            "already carved " + str1 + " wood, which forks at the top."));
        set_alarm(5.0,0.0, &command("emote takes out a pointed " + 
            metal + " tip."));
        set_alarm(7.0,0.0, &command("emote dabs a bit of glue on the " + 
            "end of the hoopak, and places the " + metal + " tip on the " + 
            "end."));
        set_alarm(9.0,0.0, &command("emote inserts a pin through the " + 
            metal + " tip and wood to secure it."));
        set_alarm(11.0,0.0, &command("emote ties a leather sling to " + 
            "the top."));
        set_alarm(13.0,0.0, &command("emote looks at the " + str1 +
            " hoopak with a critical eye."));
        set_alarm(15.0,0.0, &command("emote attaches a few bright " + 
            "feathers to the top, and places it in the storeroom for " + 
            "you to buy when ready."));
        set_alarm(15.1,0.0, "load_hoopak",str1);
        return;
    }
}

/* Function name : load_hoopak
 * Description : Clones a hoopak of the desired type,
 *     and moves it to the storeroom to be bought.
 * Returns : Null
*/

void
load_hoopak(string str1)
{
    object yew, lemonwood, hickory, oak;

    if (str1 == "yew")
    {
        yew = clone_object(KOBJ + "yew_hoopak");
        yew->move(KROOM + "hoopak_store2");
    }

    if (str1 == "lemonwood")
    {
        lemonwood = clone_object(KOBJ + "lwood_hoopak");
        lemonwood->move(KROOM + "hoopak_store2");
    }

    if (str1 == "hickory")
    {
        hickory = clone_object(KOBJ + "hick_hoopak");
        hickory->move(KROOM + "hoopak_store2");
    }

    if (str1 == "oak")
    {
        oak = clone_object(KOBJ + "oak_hoopak");
        oak->move(KROOM + "hoopak_store2");
    }

    reset_id();
    return;
}

/* Function name : Check id
 * Description : Prevents Danalin from making more than one hoopak at a time.
 * Returns : Null
*/

void
check_id(string str1)
{
    object buyer; 
    buyer = TP;

    if(make_hoopak_id == 0)
    {
        make_hoopak_id = 1;
        make_hoopak(str1);
    }
    else
    {
        set_alarm(1.0,0.0, &command("emote chatters: I'm sorry, I only " +
            "have two hands!"));
        set_alarm(2.0,0.0, &command("emote chatters: That would be very " +
            "interesting to have four hands! Don't you think?"));
    }
        return;
}

