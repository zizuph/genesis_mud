/* A magician. Mortricia 920927 */

inherit "/d/Terel/std/mystic";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(xx)          notify_fail(xx)
#define TP              this_player()
#define TO              this_object()
#define ETP             environment(TP)
#define ETO             environment(TO)

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define TENT_DIR        CAMP_DIR + "tent/"
#define ARM_DIR         MORTRICIADIR + "armours/"
#define WEP_DIR         MORTRICIADIR + "weapons/"
#define INCENSE         (GUILD_DIR + "obj/mana_incense")

#define ALIGN           276
#define SPELL_DELAY     8

private object check_sh_pr(string sh_desc, string prop, object ob);

public void
init_living()
{
    ::init_living();
/*
    add_action("do_show", "show");
*/
    add_action("do_ask",  "ask");
}

public void
create_monster()
{
    ::create_monster();

    set_name("penthir");
    add_name("magician");
    set_living_name("penthir");
    set_title("magician");
    set_long("It's a tall human and he is a magician. No doubt! " +
             "He also is a dedicated disciple of the Ancient Ones.\n");
    set_adj(({"black-bearded", "tall"}));
    set_race_name("human");
    set_gender(0);

    set_stats(({105,102,112,120,120,109}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(10, 10);
    set_rank(MYSTIC_EXARCH);
    set_piety(700);
    set_blessed(1);
    set_mystic_skills(78);
    set_skill(SS_WEP_SWORD, 99);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 90);
    set_spell_delay(SPELL_DELAY);

    add_prop("no_show_title", 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    enable_intro();

    set_act_time(80);
    add_act(({"turn hourglass", "frown", "exa buttons"}));

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

public void
dress_me()
{
    object sword, dagger, cloak, ring;

    seteuid(getuid());

    cloak = clone_object(ARM_DIR + "cloak");
    cloak->set_name("robe");
    cloak->set_short("black robe");
    cloak->set_long("A black robe.\n");
    cloak->set_adj("black");
    cloak->set_default_armour(32, A_ROBE, 0, 0);
    cloak->add_prop(MYSTIC_ARMOUR, 1);
    cloak->move(TO);
    command("wear robe");

    sword = clone_object(WEP_DIR + "blue_sword");
    sword->set_name("sword");
    sword->set_short("black sword");
    sword->set_adj("black");
    sword->set_long("It's a black sword of high quality.\n");
    sword->add_prop(MYSTIC_WEAPON, 1);
    sword->move(TO);
    command("wield sword");

    dagger = clone_object(GUILD_DIR + "obj/dagger");
    dagger->move(TO);
    command("wield dagger");
}

public int
do_ask(string what)
{
    int tp_smart, q_no;
    object ring;
    string who, s;

    NF("Ask about what?\n");
    if (!what) return 0;

    if (sscanf(what, "magician %s", s) == 1) what = s;
    if (sscanf(what, "penthir %s", s) == 1) what = s;
    if (sscanf(what, "about %s", s) == 1) what = s;
    if (sscanf(what, "for %s", s) == 1) what = s;

/*
    if (what == "goblin") {
        ring = check_sh_pr("gold ring", "q_solver", TP);
        if (ring && ring->query_prop("q_number")==6) {
            return 1;
        }
        TO->command("shrug");
        return 1;
    }
 */
    NF("Sorry, I don't understand your question.\n");
    if (what != "apparatus" && what != "weird apparatus" &&
        what != "purpose" && what != "the purpose") return 0;

    tp_smart = (TP->query_stat(SS_WIS) + TP->query_stat(SS_INT))/2;
    who = lower_case(TP->query_name());
    ring = check_sh_pr("iron ring", "q_solver", TP);
    if (ring || tp_smart > 50) {
        if (ring) q_no = ring->query_prop("q_number");
        if (q_no == 6 || tp_smart > 50) {
           write("The magician tells you that the apparatus is " +
                 "used to transform iron to gold. But it isn't " +
                 "quite ready yet, it works only for small objects. " +
                 "The magician also tells you that it is dangerous " +
                 "to stay in the room after pressing the right " +
                 "button. Leave this room while the transformation " +
                 "process is going on, and return afterwards.\n");
           command("smile " + who);
           return 1;
        }
    }
    command("stare " + who);
    write("The magician takes a good look at you, and decides not " +
          "to reveal any secrets about the apparatus to you.\n");
    command("grin");
    return 1;
}

public void
show_hook(object item)
{
    object ring = check_sh_pr("iron ring", "q_solver", TP);
    string who = lower_case(TP->query_name());
    
    if (ring && ring == item && ring->query_worn()) {
        command("say So, you're a quest solver.");
        command("ruffle " + who);
    } else {
        ring = check_sh_pr("gold ring", "q_solver", TP);
        if (ring && ring == item && ring->query_worn()) {
            command("whisper " + who + " Go to my carriage!");
            command("whisper " + who + " There you will find " +
                          "out how to use the ring.");
            command("msmile");
        } else {
            command("poke " + who);
            command("say What? Don't waste my time!");
        }
    }
}

private object
check_sh_pr(string sh_desc, string prop, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->query_short() == sh_desc &&
            ob_arr[i]->query_prop(prop) == ob->query_name()) {
            r_ob = ob_arr[i];
        }
    }
    return r_ob;
}

public void
spell_attack(object me, object victim)
{
    int spell, hp, hp_max, v_hp;
    string who;

    who = lower_case(victim->query_name());
    hp = me->query_hp();
    hp_max = me->query_max_hp();
    v_hp = victim->query_hp();

    spell = 0;
    if (spell==4 || spell==5) { /* use healing spells when hurt */
        if (hp_max - hp <= 200) spell -= 2;
    }
    if (spell==0) {
        me->command("say You are doomed to die!");
        me->command("say I put a curse on you!");
        me->command("point " + who);
        victim->reduce_hit_point((3*v_hp)/4);
        tell_object(victim,
                  "Something very powerful hits you!\n");
        tell_room(environment(victim), QCTNAME(victim) + " is hit " +
                  "by a magic bolt of fire.\n", victim);
        me->command("grin");
        me->command("chant");
    }
/*
    if (spell==1) me->command("flammis " + who);
    if (spell==2) me->command("validus");
    if (spell==3) {
        seteuid(getuid());
        clone_object(INCENSE)->move(TO);
        me->command("angelicus");
        set_alarm(4.0, -1.0, "defend_me", me);
    }
    if (spell==4) me->command("mederi");
    if (spell==5) {
        seteuid(getuid());
        clone_object(INCENSE)->move(TO);
        me->command("angelicus");
        set_alarm(4.0, -1.0, "heal_me", me);
    }
    if (spell==6) me->command("venenare dagger");
*/

    set_alarm(itof(10+random(query_spell_delay())), -1.0, &set_spell_prop(me));
    return;
}

public void
defend_me(object ob)
{
    if (ob) ob->command("defend me spirit");
}

public void
heal_me(object ob)
{
    if (ob) ob->command("heal me spirit");
}

public void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);
    if (!old || !living(old)) return;
    if (old->query_wiz_level()) return;
    set_alarm(2.0, -1.0, "drop_ob", ob);
}

public void
drop_ob(object ob)
{
    ob->move(ETO);
    tell_room(ETO, QCTNAME(TO)+" drops "+LANG_ASHORT(ob)+".\n", TO);
}
