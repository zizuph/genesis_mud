/*
 * This fisherman is able to be cloned by 2 different rooms,
 * ~Cirath/ak_wela/pier2 and ~Cirath/ak_wela/pier7.
 */

inherit "/std/monster";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Shire/common/monster/tobacco.h"

void create_monster()
{
    string *poss_races = ({"human", "elf", "hobbit"});
    object rod, hat;

    seteuid(getuid());

    set_name("fisherman");
    set_race(poss_races[random(sizeof(poss_races))]);
    if (query_race() == "hobbit")
        clone_tobacco();

    set_short("dozing fisherman");
    set_pshort("dozing fishermen");
    set_long("This \n");


    add_prop(CONT_I_WEIGHT, 65000);     /* 65 Kg */
    add_prop(CONT_I_HEIGHT, 173);     /* 173 cm */

              /* STR DEX CON INT WIS DIS */
    set_stats(({ 15, 15, 15, 15, 15, 15 }));

    set_pick_up(0);
    set_hp(query_max_hp()); /* Heal fully */

    clone_object(AK_WELA_DIR + "wep/fishing_rod")->move(TO);
    command("wield rod");
    clone_object(AK_WELA_DIR + "arm/fishing_hat")->move(TO);
    command("wear hat");

    (MONEY_MAKE_CC(random(12)))->move(TO);

    /* Actions */
    set_act_time(5);
    add_act("snore");
    add_act("nod sleepily");
    add_act("grumble sleepily");
    add_act("smile sleepily");

    /* Triggers */
    trig_new("%w 'introduces' %s", "react_introduce");
}


void depressed_chat()
{
  tell_room(environment(TO), "The bandit mutters, \"Sorry, " + friendly() +
                             ", but a guy's gotta make a living!\"\n");
}


void react_depressed(string dummy1, string dummy2)
{
  call_out("depressed_chat", 1);
}


void intro_chat()
{
  tell_room(environment(TO),
            break_string("His voice dripping with sarcasm, the robber says, " +
            "\"Pleased to meet you.  Now gimme your money!!\"\n", 70));
}


void react_introduce(string dummy1, string dummy2)
{
  call_out("intro_chat", 1);
}
