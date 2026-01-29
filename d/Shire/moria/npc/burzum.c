/*
 * A big bad uruk.
 * Altrus, July 2005
 *
 * Added lots of goodies, like stuns for bouncing, a team
 * attack special, a push out of the room that also adds
 * a temporary block for re-entering the room.
 *
 * Update Log:
 * Added 'assist friend' to code so his orcs help fight when called.
 * Updated long descr.
 * -- Finwe, March 12, 2006
 *
 * Fixed a typo in description.
 * -- Toby, Feb 12, 2007
 *
 * Refactored the special attack code and fixed a runtime.
 * Cut down on the block time and removed the 'anti union' code.
 * Magic resistance code fixed, lowered resistance a bit
 *
 * -- Cotillion, Feb 2014
 *
 * Cotillion - 2020-09-29
 * - Fixed type confusion with object
 */
#include "/d/Shire/sys/defs.h"
inherit SHIRE_MONSTER;
inherit "/lib/unique";
inherit KILL_LOGGER;
inherit "/d/Shire/lib/assist_friend";


#include "/d/Shire/private/shire_admin.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <composite.h>
#include "/d/Shire/common/lib/evilkill.h"

#define ARM_DIR "/d/Shire/moria/arm/"
#define WEP_DIR "/d/Shire/moria/wep/"
#define DID_ATTACK "_attacked_burzum"
#define IS_STUN "_stunned_by_burzum"
#define WILL_STUN "_burzum_will_stun"
#define TREASURE_ROOM "/d/Shire/moria/mines/mining/treasure_room"


int uruk_allies = 0;
object *leader;

void create_shire_monster()
{
    set_name("burzum");
    add_name("uruk");
    add_name("orc");
    add_name("_burzum_blocks_exit");
    add_adj("hulking");
    add_adj("brutish");
    set_title("the Brutal");
    set_race_name("uruk-hai");

    set_short("hulking brutish uruk-hai");

    set_long("This fearsome creature is one the larger orcs in Moria. " +
             "He is taller than most and looks more dangerous. His scaly " +
             "skin is black and scarred from numerous battles, and his eyes " +
             "burn with a red fury as he watches you. The muscular creature " +
             "has sharp tusks that protrude from his large mouth, adding a " +
             "sense of strength to the beast. He is muscular and has a sense " +
             "of evil about him. He does not look like one to be trifled with.\n");

    set_kill_log_name("burzum");
    set_kill_log_size(50000);


    set_stats(({330, 250, 375, 200, 200, 300}));

    set_alignment(-1200);
    set_appearance(10);
    set_gender(G_MALE);
    set_exp_factor(175);

    add_prop(CONT_I_WEIGHT, 200 * 1000);
    add_prop(CONT_I_VOLUME, 100 * 1000);
    add_prop(CONT_I_HEIGHT, 270);

    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_2H_COMBAT, 85);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 85);
    set_skill(SS_BLIND_COMBAT, 95);
    set_appearance_offset(50); // this thing's uglier than sin...

    add_prop(OBJ_I_RES_MAGIC, 80);
    add_prop(OBJ_I_RES_POISON, 80);
    add_prop(OBJ_I_RES_DEATH, 80);
    add_prop(OBJ_I_RES_FIRE, 80);
    add_prop(OBJ_I_RES_LIFE, 80);
    add_prop(OBJ_I_RES_LIGHT, 80);

    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(LIVE_I_QUICKNESS, 75);
    add_prop("_live_m_no_drain", "As you approach the hulking brutish " +
             "uruk-hai, he swats you away carelessly, saying 'I don't want no " +
             "stinking kiss!'\n");

    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_chat_time(6);
    add_chat("Could go for a bit o' elvish meat right now.");
    add_chat("Bah! These puny orcs know nothing of true fighting!");
    add_chat("Ha! The only thing in these mines that unnerves me is the Fiery One!");
    add_chat("Get lost you maggot!");
    add_chat("Be gone! Lest I find some use for your skin.");

    set_cchat_time(7);
    add_cchat("You will fall like all the rest!");
    add_cchat("I will gladly feast on your flesh!");
    add_cchat("Is that the best you can do? Pathetic!");
    add_cchat("So, you think you can take me?");
    add_cchat("I WILL BURY YOU!!");

    equip(({
        ARM_DIR + ({"uruk_helm", "uruk_cap", "uruk_helmet"})[random(3)],
        ARM_DIR + ({"uruk_greaves", "uruk_guards"})[random(2)],
        ARM_DIR + ({"uruk_chain", "uruk_plate", "uruk_hauberk"})[random(3)],
        WEP_DIR + ({"uruk_sword", "uruk_axe"})[random(2)],
        WEP_DIR + ({"uruk_club", "uruk_knife"})[random(2)],
    }));
}

void
push_out_enemy(object enemy) {
    if (!objectp(enemy) || environment(enemy) != environment(this_object()))
        return;

    enemy->catch_msg("The force of the attack pushes you from the room, leaving you bruised and shaken.\n");
    tell_room(ENV(enemy), "The force of the attack pushes " + QTNAME(enemy) + " from the room.\n", enemy, enemy);

    clone_object("/d/Shire/moria/obj/block_obj")->move(enemy, 1);
    enemy->move_living("M", "/d/Shire/moria/mines/mining/mining.8", 1);
}

void
summon_allies(int count)
{
    object ob;

    tell_room(ENV(this_object()), QCTNAME(this_object()) + " calls for help, and some orcs rush in to aid him!!\n");

    while (count--)
    {
        ob = clone_object("/d/Shire/moria/npc/uruk_ally");
        ob->move_living("M", ENV(TO));
    }
}


int special_attack(object enemy)
{
    mixed *hitresult;
    mixed *others = (query_enemy(-1) & all_inventory(environment())) - ({ enemy });

    string how;
    int rate;
    int hurt;
    int uruk_dex = query_stat(SS_DEX);
    int uruk_str = query_stat(SS_STR);

    if (random(5))
    {
        return 0;
    }

    if (sizeof(others) && (random(10) > 3))
    {
        rate = random(3) + 3;
        hurt = random(uruk_str + uruk_dex)/4 + 120 + random(150);
        enemy->heal_hp(-hurt);
        enemy->catch_tell("The hulking brutish uruk-hai seems to be loosing his temper. He flails about wildy, hitting you and everyone around him with brutal blows.\n");

        foreach (object target: (({ enemy }) + others)) {
            /* Don't kill people! */
            int damage = random(uruk_str + uruk_dex)/4 + 120 + random(150);

            if (damage >= target->query_hp())
                damage = target->query_hp() / rate + 20;

            target->heal_hp(-damage);
            target->catch_msg("The hulking brutish uruk-hai seems to be losing his temper. He flails about wildy, hitting you and everyone around him with brutal blows.\n");
        }

        if (random(5) > 2)
        {
            object target = enemy;

            if (random(5) <= 2)
                target = others[random(sizeof(others))];

            push_out_enemy(target);
        }
        return 1;
    }

    hitresult = enemy->hit_me(uruk_str + uruk_dex + 200, W_BLUDGEON, TO, -1);

    how = "not hurt at all";
    if (hitresult[0] > 0)
        how = "barely hurt";
    if (hitresult[0] > 5)
        how = "hurt";
    if (hitresult[0] > 10)
        how = "bruised";
    if (hitresult[0] > 15)
        how = "battered";
    if (hitresult[0] > 20)
        how = "broken";
    if (hitresult[0] > 25)
        how = "demolished";
    if (hitresult[0] > 30)
        how = "devastated";

    enemy->catch_msg("The hulking brutish uruk-hai grabs you and throws you to the floor!\n");
    enemy->catch_msg("The impact leaves you " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " grabs " + QCTNAME(enemy) + " and throws " +
                 HIM_HER(enemy) + " to the floor!\nThe impact leaves " +
                 HIM_HER(enemy) + " " + how + ".\n", enemy);

    if (TO->query_hp() <= 7000 && uruk_allies == 0)
    {
        uruk_allies = 1;
        summon_allies(2);

    }

    if (TO->query_hp() <= 5500 && uruk_allies == 1)
    {
        uruk_allies = 2;
        summon_allies(4);
    }

    if (enemy->query_hp() <= 0)
    {
        enemy->command("scream");
        enemy->catch_msg("As the uruk-hai tosses you to the floor, he brutally pummels your body! Your vision starts to fade, and you see death coming.\n");
        tell_room(ENV(this_object()), "As the uruk-hai tosses " + QCTNAME(enemy) + " to the floor, he brutally pummels " +
                  QCTNAME(enemy) + "'s body!\n" + QCTNAME(enemy) + "'s eyes start to fog over, and " + HE_SHE(enemy) + " seems to see death coming.\n");
        enemy->do_die(this_object());
    }

    return 1;
}

public void
attacked_by(object ob)
{
    object obj;
    object *arr;
    ob->add_prop(DID_ATTACK, 1);
    setuid(); seteuid(getuid());
    obj = clone_object("/d/Shire/moria/obj/b_attack_obj")->move(ob);

    ::attacked_by(ob);
    TELL_ADMIN("Burzum was attacked by " + ob->query_cap_name() + "("+ob->query_average_stat()+") at " + ctime(time()));

}

void
create_treasure() {
    object wep, treasure, room;

    setuid(); seteuid(getuid());
    LOAD_ERR(TREASURE_ROOM);

    room = find_object(TREASURE_ROOM);
    map(FILTER_DEAD(all_inventory(room)), &->remove_object());

    wep = clone_unique((WEP_DIR + "mithril_pike"), 7, ({ ("/d/Shire/orcmaker/wep/ghalberd"), ("/d/Shire/orcmaker/wep/gthsword"), }), 1, 25 );
    wep->move("/d/Shire/moria/mines/mining/treasure_room");

    treasure = clone_object("/d/Shire/moria/obj/money_pouch");
    treasure->move("/d/Shire/moria/mines/mining/treasure_room");
}

public void
notify_death(object killer)
{
    ::notify_death(killer);
    create_treasure();
}
