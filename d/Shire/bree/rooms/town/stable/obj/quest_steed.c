/*
 * /d/Shire/bree/rooms/town/stable/obj/steed.h
 *
 * Horse for "horse quest"
 *
 * By, Palmer
 * Date: December 2002
 */

inherit "/d/Genesis/steed/new/steed";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/commands";

#include <wa_types.h>
#include <adverbs.h>
#include <const.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bree/rooms/town/stable/bree_stables.h"
#include "../bree_stables.h"

void    add_acts();
string  emote;
void    touch_horse(object who, string emote);

void
create_steed()
{
    add_name("_steed_");
    add_name("_quest_steed_");
    set_living_name("black_horse");
    id("_steed_");
    set_gender(random(2));

    set_stats(({180, 150, 250, 40, 40, 150}));
    set_skill(SS_CLIMB, 25);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_SWIM, 40);
    set_skill(SS_AWARENESS, 40);
    set_skill(SS_LOC_SENSE, 30);
    set_long("A large horse with all black features. This looks like a fine " +
             "steed but seems a little thin. " + capitalize(HIS_HER(TO)) + " coat is bit dull. " +
    capitalize(HE_SHE(TO)) + " seems frightened.\n");
    set_adj(({"sleek", "black"}));
    set_short("sleek black horse");

    set_m_in("comes galloping in");
    set_m_out("gallops");

    set_leader_object_file(BREE_STABLES_OBJ_DIR + "quest_leader_object");
    set_rider_object_file(BREE_STABLES_OBJ_DIR + "quest_rider_object");
    set_allowed_food(({"oats", "apple", "hay", "sugarcube"}));

    allow_mounted_combat(0);
    set_no_trans(0);
    set_max_riders(1);
    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    set_stuffed(TO->query_prop(6400));
    add_acts();
}

void
destruct_me()
{
    TO->remove_object();
}

void
go_to_minion(object minion)
{
    minion->take_horse();
}

void
enter_env(object ob, object from)
{
    object minion, player;
    object reward_scroll;

    ::enter_env(ob, from);
    if (file_name(ENV(TO)) == "/d/Gondor/morgul/road/mrd2")
    {
        minion = clone_object(BREE_STABLES_NPC_DIR + "dark_minion");
        minion->move_living("null", "/d/Gondor/morgul/road/mrd2");
        player = TO->query_leader();
        player->catch_tell("The skeletal human hands you a scroll.\n");
        reward_scroll = clone_object(BREE_STABLES_OBJ_DIR + "scroll");
        reward_scroll->move(player);

        set_alarm(1.0, 0.0, &go_to_minion(minion));
        set_alarm(4.0, 0.0, destruct_me);
    }
}


void
add_acts()
{
    set_act_time(5);
    add_act("emote suddenly snorts, and tosses "+ HIS_HER(TO) + " mane.");
    add_act("emote swings "+HIS_HER(TO)+" tail to the side, slapping " +
            HIS_HER(TO)+" flank.");
    add_act("emote stomps "+HIS_HER(TO)+" hoof on the ground, neighing " +
            "softly.");
    add_act("emote lowers " + HIS_HER(TO) + " head, tossing " +
            HIS_HER(TO) + " mane from one side to the other.");
    add_act("emote throws back " + HIS_HER(TO) +
            " head and whinnies loudly.");
    add_act("emote tosses "+HIS_HER(TO)+" head around and snorts "+
            "loudly.");
}

void
emote_hook(string emote, object actor, string adverb, object *oblist, int cmd_attr, int target)
{
    if (!target) /* Only make horse react if its the one getting touched */
    {
        return;
    }

    if (!interactive(actor))  /* Only make horse react if its a player touching it */
    {
        return;
    }

    switch(emote)
    {
    case "snuggle":
    case "ruffle":
    case "fondle":
    case "snuggle":
    case "hug":
    case "pat":
    case "pet":
    case "kiss":
        touch_horse(TP, emote);
    default:
        break;
    }
}


void
touch_horse(object who, string emote)
{
    int trust;
    trust = TP->query_prop("_horse_trust_");
    if(!trust)
    {
    write("The " + short() + " swiftly moves its head and bites you after you " +
          emote + " it!\n");
    say("The " + short() + " swiftly moves its head and bites " + QTNAME(who) +
        " after " + HE_SHE(TO) + " " + emote + " it!\n");
    }
    return;
}

void hook_feed(object feeder, object food)
{
    int trust;

    ::hook_feed(feeder, food);
    trust = TP->query_prop("_horse_trust_");
    if(!trust)
    {
        TP->catch_tell("The horse seems a bit more calm and at ease.\n");
        TP->add_prop("_horse_trust_", 1);
    }
}

void
lead_hook(object o)
{
    int trust;
    trust = TP->query_prop("_horse_trust_");
    if(!trust)
    {
        o->catch_tell("You take the reigns and try to lead the horse but it rears up " +
        "and backs away.\n");
        do_unlead(o, 1);
    }
    else
    {
        o->catch_tell("You take the reigns and start leading the black horse.\n");
    }
}


void
mount_hook(object o)
{
        o->catch_tell("You try to climb on the horse but it throws you off.\n");
        do_dismount(o, 1);
        tell_room(environment(this_object()), QCTNAME(o) + " tries to mount the " +
        this_object()->steed_short() + " but it throws " + HIM_HER(o) + " off.\n", o);
}