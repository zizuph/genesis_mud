inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

#define TO      this_object()
#define ENV(xx) environment(xx)
#define ETO     ENV(TO)
#define DAGGER  "/d/Terel/mecien/bdagger"
#define ROBE    "/d/Terel/mecien/robe"

public void
create_monster()
{
    ::create_monster();
    
    set_name("wraith");
    set_pname("wraiths");
    set_adj("crimson");
    set_race_name("wraith");
    set_gender(2);
    set_pshort("crimson wraiths");
    set_long(
        "This spirit, born of the dark reaches of the underworld, seeks only\n"
       +"to devour the living and thereby sustaining its own need.\n");
    set_alignment(-856);

    set_base_stat(SS_INT, 80);
    set_base_stat(SS_WIS, 80);
    set_base_stat(SS_DIS, 90);
    set_base_stat(SS_STR, 100);
    set_base_stat(SS_DEX, 100);
    set_base_stat(SS_CON, 100);
    set_skill(SS_WEP_SWORD, 35);
    set_skill(SS_WEP_KNIFE, 120);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_AWARENESS, 100);
    set_hp(10000);

    set_all_attack_unarmed(60, 50);
    set_all_hitloc_unarmed(90);
    set_aggressive(1);

    add_prop(LIVE_I_UNDEAD, 87);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(1);
    add_act("@@dispell");
    add_act("@@grow");
    
    seq_new("do_things");
    seq_addfirst("do_things", "@@arm_me");
}

/* Added a set_wf() to ensure that the dagger is reset properly.
   Mortricia. */
public void
arm_me()
{
    object bdagger, robe;
    
    seteuid(getuid(TO));
    bdagger = clone_object(DAGGER);
    bdagger->set_hit(90);
    bdagger->set_pen(90);
    bdagger->set_wf(bdagger);
    bdagger->move(TO);

    robe = clone_object(ROBE);
    robe->move(TO);
    
    command("wield dagger");
    command("wear robe");
}

public string
dispell()
{
    object sp = present("spirit_of_peace", ETO);
    
    if (sp) {
        command("emote holds out its crimson fingers and speaks " +
                "horrible words, pointing at the spirit.");
        sp->command("emote falls to the ground.");
        sp->remove_object();
        init();
    }
    return "";
}

public string
grow()
{
    command("emote seems to call forth strength from some " +
            "horrible place of darkness.");
    heal_hp(100);
    dispell();
    return "";
}

public void
destroy(object ob)
{
    if (!ob) return;
    
    if (ENV(ob)->query_prop(ROOM_I_IS)) {
        tell_room(ENV(ob), "The " + ob->short() +
                  " disintegrates with a strange hissing noise.\n");
    } else if (living(ENV(ob))) {
        ENV(ob)->catch_msg("The " + ob->short() +
                  " disintegrates with a strange hissing noise.\n");
    }
    ob->remove_object();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (ob->query_name("dagger"))
        set_alarm(0.1, -1.0, &destroy(ob));
}

public void
do_die(object killer)
{
    object dagger;

    if (query_hp() > 0)
        return;

    if (dagger = present("dagger", TO)) {
        seteuid(getuid(TO));
        dagger->remove_object();
        clone_object(DAGGER)->move(TO);
    }

    ::do_die(killer);
}

public int
special_attack(object enemy)
{
    object me = TO;
    mixed* hitresult;
    string how;

    if (random(3) || query_hp() <= 25)
        return 0;

    hitresult = enemy->hit_me(35+random(40), MAGIC_DT, me, -1);
    me->catch_msg("You chill the soul of your victim!\n");
    enemy->catch_msg(QCTNAME(me) + " chills your soul with its " +
                     "touch of darkness!\n");
    tell_watcher(QCTNAME(me) + " chills the soul of " +
                 QTNAME(enemy) + " with its touch of darkness!\n", enemy);
    me->heal_hp(-25);

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
}
