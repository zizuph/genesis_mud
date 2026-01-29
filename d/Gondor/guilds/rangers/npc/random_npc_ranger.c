/*
 *  A random ranger with random equipment
 *
 * Coded by Elessar
 * Brawling added by Mercade, sept 17, 1993
 * Undone Mercade's changes, changed inherit to /d/Gondor/common/npc/npc_ranger.c
 * Olorin, 18-sep-1993
 * Updated code: May 30. 1996
 *                5-Feb-1997, Olorin: Changed triggers to hooks.
 *                8-Mar-2002, Alto: Moved and modified for new ranger code.
 *                29-Oct-2003, Tigerlily: updated for genders, refreshed
 *                    descriptions
 */
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "npc_ranger.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#define RADJ ({ "tall", "rugged", "weather-beaten", "scarred", \
                "lean", "grim", "vigilant", "stern"})
#define RLONG ({ \
    ", whose long shanks stride far with each step, " + \
    "is quite a bit taller than the average human.\n",  \
    " has a strong, rugged build, quite capable of " + \
    "enduring long journeys through the wilderness.\n", \
    " has a weathered face that is lined with " + \
    "age and experience and hair bleached by sun and wind.\n", \
    ", whose face and hands bear ugly scars, stands proud " + \
    "and grim.\n", \
    ", whose clothes seem a few sizes " + \
    "too large, is very lean for a human.\n", \
    " has grim piercing eyes and a noble bearing, " + \
    "though dressed in dirty travel-stained clothes.\n", \
    " looks keen-eyed and vigilant, constantly glancing in all " + \
    "directions.\n", \
    " gazes back at you with a stern and solemn expression " + \
    "that brooks no argument.\n"\
})

#define RWEIGHT ({ 120, 107, 103,  99,  87,  70, 112, 105 })
#define RHEIGHT ({ 200, 185, 188, 193, 185, 186, 184, 190 })
                  /* str dex con int wis dis */
#define RSTAT ({ \
                   ({ 102, 108, 103, 104, 83, 140 }), \
                   ({ 119, 111, 113, 115, 94, 150 }), \
                   ({ 104, 103, 97, 102, 82, 145 }), \
                   ({ 106, 102, 83, 103, 83, 140 }), \
                   ({ 86, 94, 99, 95, 78, 130 }), \
                   ({ 109, 104, 94, 105, 86, 140 }), \
                   ({ 106, 100, 107, 105, 84, 155}), \
                   ({ 107, 109, 100, 103, 84, 80 }) })


#define RWEAPON ({ "r_brsword","r_lsword","r_spear" })
#define RWSHORT ({ "broadsword","longsword","spear" })
#define RARMOUR ({ "drcloak","studlarm","dlboots" })
#define RASHORT ({ "cloak","armour","boots" })

#define SKUCOM ({ 93, 87, 81, 57, 89, 93, 85, 78 })
#define SKDEF  ({ 73, 80, 85, 53, 80, 75, 87, 98 })

public void    do_an_emote();
public void    make_fire();

static void
set_up_stats(int ran)
{
   set_stats(RSTAT[ran]);
   set_alignment(450);

   set_skill(SS_WEP_SWORD,   SKUCOM[ran]);
   set_skill(SS_WEP_AXE,     SKUCOM[ran]);
   set_skill(SS_WEP_KNIFE,   SKUCOM[ran]);
   set_skill(SS_WEP_POLEARM, SKUCOM[ran]);
   set_skill(SS_DEFENCE,     SKDEF[ran]);
   set_skill(SS_PARRY,       SKDEF[ran]);
}

public void
add_guild_token()
{
    clone_object(RANGERS_ITH_EMBLEM)->move(TO, 1);
    set_alarm(2.0, 0.0, &command("wear all"));
}

void
create_ranger()
{
    int ran = random(8);
    string gen, lng;
      
    seteuid(getuid(TO));
    set_name(({"ranger", "_random_ranger_"}));
    set_pname("rangers");

    if (query_gender() == G_FEMALE)
        gen = "This woman";
    else
        gen = "This man";

    set_short(RADJ[ran] + " ranger");
    set_pshort(RADJ[ran] + " rangers");
    set_race_name("human"); 
    set_adj(RADJ[ran]);
    lng = gen + RLONG[ran];
    set_long(lng);
    if (ran == 4)
        set_scar(1023); /* give him lots of scars! */
    
    add_prop(CONT_I_WEIGHT, RWEIGHT[ran] * 1000);
    add_prop(CONT_I_HEIGHT, RHEIGHT[ran]);
    add_prop("_ranger_i_recognizing_brawl", 500);
    
    set_up_stats(ran);
    add_guild_token();
    set_size_descs("tall", "lean");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_cchat_time(3 + random(6));
    add_cchat("By Elendil! We will not be defeated, foe!");
    add_cchat("Rangers are not easily beaten!");
    add_cchat("Begone, ere defeat is upon you!");
    add_cchat("By Gondor! I will kill you!");

    set_act_time(5);

    // add_act() does not support function variables:
    add_act("@@do_an_emote@@");
    add_act("@@make_fire@@");

    set_cact_time(2);
    add_cact("battle");
}

public void
arm_me()
{
    clone_object(WEP_DIR + RWEAPON[random(3)])->move(TO);
    clone_object(ARM_DIR + RARMOUR[random(3)])->move(TO);
    command("wield all");
    command("wear all");
}

/********************************************************************
 *
 *  Some feelings to make the ranger more vivid.
 *  The feelings are split in two parts: the part that is called by
 *  a emote_hook function, and a part that is called after a random 
 *  time. This is done to get a feeling of reality in the game.
 *
 */
public void
return_sigh(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
        return;

   switch (random(3))
   {
   case 0:
       command("say What is troubling you, "
               + actor->query_nonmet_name() + "?");
       break;
   case 1:
       command("eyebrow . " + OB_NAME(actor));
       break;
   case 2:
       command("say Something wrong, friend?");
       command("peer . " + OB_NAME(actor));
       break;
   }
}

public void
return_smile(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
        return;

    switch (random(7))
    {
    case 0:
        command("say You seem pleased today, " +
           (actor->query_gender() ? "madam" : "sir") + ".");
        break;
    case 1:
        command("smile . " + OB_NAME(actor));
        break;
    case 2:
        command("say I wish I could share your good mood.");
        command("say I lost my best friend in Ithilien two days ago.");
        command("sigh .");
        break;
    default:
        break;
    }
}

/*
 * Function name: emote_hook
 * Description  : Whenever an emotion is performed on this NPC, or when it
 *                is performed on in the room in general, this function is
 *                called to let the NPC know about the emotion. This way we
 *                can avoid the usage of all those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverbs - the adverb used with the emotion, if there
 *                    was one. When an adverb is possible with the emotion,
 *                    this argument is either "" or it will contain the used
 *                    emotion, preceded by a " " (space). This way you can
 *                    use the adverb in your reaction if you please without
 *                    having to parse it further.
 */
public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (TO->query_prop(OBJ_I_HIDE)) 
        return 0;
    if (!objectp(actor) || !interactive(actor))
        return 0;

    switch (emote)
    {
    case "sigh":
        set_alarm(2.0, 0.0, &return_sigh(actor));
        break;
    case "smile":
        set_alarm(2.0, 0.0, &return_smile(actor));
        break;
    }
}

void
check_enemy(object tp)
{
    if (query_friend_or_foe(tp) < -1)
    {
        if (!random(2))
            command("kick campfire");
        if (!agg_ranger)
            return;
        if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, TP)) 
        {
            command("shout Evil " + CAP(LANG_PWORD(TP->query_race_name())) + 
                "!! Attack!!");
            command("battle " + OB_NAME(tp));
            command("brawl");
        }
    }
}

public void
init_living()
{
    ::init_living();

    if (!agg_ranger) 
        return;

    set_alarm(0.0, 0.0, &check_enemy(TP));
}

/* For the solamnic Knights */
public int
query_knight_prestige()
{
    return (-7);
}

public void
make_fire()
{
    object env = ENV(TO);

    if (random(4))
        return;
    else if (TO->query_prop(OBJ_I_HIDE)) 
        return;
    else if (!objectp(env))
        return;
    else if (env->query_prop(ROOM_I_INSIDE))
        return;
    else if (present("firewood", env))
    {
        command("light fire");
        return;
    }
    else if (present("ashes", env) && (random(3)))
    {
        command("kick ashes");
        return;
    }
    else if (present("firewood", TO))
    {
        command("drop firewood");
        command("light firewood");
    }
    else
        command("rgather firewood");
}

public void
do_an_emote()
{
    if (query_prop(OBJ_I_HIDE)) 
        return;

    switch (random(10))
    {
    case 0:
        command("rdirt");
        break;
    case 1:
        command("rhush");
        break;
    case 2:
        command("rstudy");
        break;
    case 3:
        command("smile grim");
        break;
    case 4:
        command("rrest");
        break;
    case 5:
        command("rtroubled");
        break;
    case 6:
        command("rsuspicious");
        break;
    case 7:
        command("rsing gondor");
        break;
    case 8:
        command("light firewood");
        command("rwarm");
        break;
    case 9:
        command("kick ashes");
        break;
    }
}

int
second_life(object killer)
{
    FIX_EUID
    MANAGER->add_outlaw(killer->query_real_name());
    return 0;
}

