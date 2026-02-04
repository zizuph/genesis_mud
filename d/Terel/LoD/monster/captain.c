/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * captain.c
 *
 * a captain of the legion 921104 redhawk
 * Modified by Sorgum 941029
 */

#include "/d/Terel/include/Terel.h"
inherit "/lib/unique";
inherit LOD_DIR + "monster/legion_soldier";

#include <ss_types.h>

#define PEACE_DELAY     7

#define KILL_LOG "/d/Terel/log/cap_kills"

static object my_boss;
static object *my_foes;

void arm_me();
void help_the_boss(object boss);
void attack_someone();
public nomask void peace_attack(object who);


/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name ("captain");
    set_short("legion captain");
    set_long("A captain in the legion army, they who have sworn not to " +
	     "rest until they have spread darkness all over the " +
	     "world.\n");
    set_adj("legion");
    set_race_name("elf");
    set_gender(MALE);
    set_alignment(-400);

    set_stats(({80, 75, 70, 100, 105, 105}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      77 + random(11));
    set_skill(SS_PARRY,        77 + random(11));
    set_skill(SS_WEP_SWORD,    95 + random(5));
    set_skill(SS_WEP_KNIFE,    95 + random(5));
    set_skill(SS_2H_COMBAT,    90);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_UNARM_COMBAT, 77 + random(11));
    
    add_prop(LIVE_I_QUICKNESS, 100);
    AGGRESSIVE;
    arm_me();
}

void
help_the_boss(object boss)
{
    if (!boss) return;
    my_boss = boss;
    my_foes = my_boss->query_my_enemies();
}

void
attack_someone()
{
    int i, found_foe = 0;
    object foe;

    if (!query_attack()) {
        help_the_boss(my_boss);
        for (i=0; i<sizeof(my_foes); i++) {
            foe = my_foes[i];
            if (foe && environment(TO) == environment(foe)) {
                command("kill " + foe->query_real_name());
          found_foe = 1;
                break;
            }
        }
     if (!found_foe && my_boss &&
         environment(my_boss) != environment(TO)) {
         tell_room(environment(TO), QCTNAME(TO) +
                " leaves to seek his master.\n", TO);
         move_living("M", environment(my_boss));
         tell_room(environment(my_boss), QCTNAME(TO) +
                " arrives.\n", TO);
            set_alarm(4.0, -1.0, attack_someone);
         return;
     }
    }
    set_alarm(20.0, -1.0, attack_someone);
}

public nomask void
stop_fight(mixed elist)
{
    if (TP->query_wiz_level()) {
        ::stop_fight(elist);
        return;
    }
    ::stop_fight(elist);
    remove_prop(LIVE_O_SPELL_ATTACK);
    set_alarm(itof(PEACE_DELAY+random(5)), -1.0, "peace_attack", TP);
}

public nomask void
peace_attack(object who)
{
    int i;
    
    if (query_hp() <= 0) return;

    set_spell_prop(TO);
    tell_room(ETO, QCTNAME(TO) + " looks a bit confused for a while.\n");

    for (i=0; i<sizeof(my_foes); i++)
        if (my_foes[i] && present(my_foes[i], ETO))
            command("kill " + my_foes[i]->query_real_name());

    if (who && present(who, ETO))
        command("kill " + who->query_real_name());
}

int
notify_you_killed_me(object player)
{
    command("get all from corpse");
    if(player->query_npc()) return 1;
    seteuid(getuid(this_object()));
    write_file(KILL_LOG ,player->query_name() +
            " ("+player->query_average_stat()+
            ") by "+this_object()->query_name()+" on " +
            ctime(time())+" ("+file_name(environment(this_object()))+").\n");
    return 1;
}
void
arm_me()
{
    FIX_EUID;
    clone_unique(LOD_DIR + "armour/battle_chainmail",20,LOD_DIR +
                 "armour/steel_chainmail",50)->move(TO);
    clone_object(LOD_DIR + "armour/battle_helmet")->move(TO);
    clone_object(LOD_DIR + "weapon/steel_stiletto")->move(TO);  
    clone_object(LOD_DIR + "weapon/swordofchaos")->move(TO); 
    command("wear all");
    command("wield sword");
    command("wield all");
    return;
}

