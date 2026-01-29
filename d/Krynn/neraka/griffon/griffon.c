/* Dragon by percy*/
/* Transformed into a Griffon by Macker */
#include "/d/Krynn/common/defs.h"

inherit C_FILE

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <options.h>
#include <macros.h>
#include <filter_funs.h>
#include "local.h"

inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */



void
create_creature()
{
    int i;

    set_living_name("Thunderheart");
    set_name("thunderheart");
    set_short("large fearless griffon");
    set_race_name("griffon");
    set_long(BS("A large fearless griffon. It looks like it has travelled everywhere " +
        "imagineable and done just about everything. He is definitely large " +
        "enough and strong enough to carry you in flight. Why not try to mount him?", 70));
    set_adj("large");
    add_adj("fearless");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 160 + random(20));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 100);
    set_knight_prestige(-8);

    set_alignment(1200);


    set_attack_unarmed(0, 95, 90, W_IMPALE, 50, "bite");
    set_attack_unarmed(1, 85, 80, W_BLUDGEON, 20, "wing");
    set_attack_unarmed(2, 75, 70, W_SLASH, 30, "claw");

    set_hitloc_unarmed(0, 100, 10, "head");
    set_hitloc_unarmed(1, 90, 60, "body");
    set_hitloc_unarmed(2, 90, 30, "tail");

    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 5679000);
    add_prop(CONT_I_WEIGHT, 5784000);
}

void
land(object ob)
{
    string room;

    room = ob->query_place();
    tell_room(E(TO), "The mighty griffon suddenly takes off into the sky. The " +
      "force of the wind created by his wings nearly knocks you over, but you " +
      "manage to steady yourself.\n");

    move(room, 1);
    tell_room(E(TO), "A large fearless looking griffon descends from " +
      "the heavens. The wind created by his huge wings almost " +
      "knocks you over, but when " +
      "he settles in his huge nest, all becomes calm again.\n");
    call_out("go_void", 60);
    call_out("no_flight", 5);
}

void
time_to_land(int time, object ob)
{
    if (time > 0)
        call_out("land", time, ob);

    else
        land(ob);
}

void
init_living()
{
    ADA("mount");
}

int
mount(string str)
{
    NF("Mount who?\n");
    if (str != "griffon")
        return 0;
    if(!(TP->test_bit("Krynn", 2, 11)))
    {
        NF("You try to mount the griffon, but he won't let you.\n");
        say(QCTNAME(TP) + " tried to mount the griffon but failed.\n");
        return 0;
    }
    remove_call_out("no_flight");
    remove_call_out("go_void");
    call_out("go_void", 90);
    E(TO)->set_dircmd("griffon");

    TP->move_living("mounting the griffon", ON_DRAGON);
    (DRAGON_ROOM)->set_flying(1);
    return 1;
}

void
rem_void() { remove_call_out("go_void"); }

void
no_flight() { (DRAGON_ROOM)->set_flying(0); }

int
go_void()
{
    tell_room(E(TO), "The mighty griffon suddenly takes off into the sky. The force of the wind created by his wings nearly knocks you over, but you manage to steady yourself.\n");
    (ON_DRAGON)->drop_all();
    (DRAGON_ROOM)->set_place(2);
    (DRAGON_ROOM)->set_flying(0);
    move(VOID, 1);
    return 1;
}

void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_option(OPT_BLOOD) == 0)
            ob[i]->catch_msg(str);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    remove_call_out("no_flight");
    remove_call_out("go_void");
    stop_fight(({ob, this_object()}));
    go_void();
}





