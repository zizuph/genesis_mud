inherit "/d/Shire/std/monster";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>

#define ADJ_LIST1 ({ "red-eyed","yellow-eyed","black-eyed",\
                     "orange-eyed","one-eyed","grey-eyed",\
                     "hairy","black-scaled","scarred","battle-worn",\
                     "toothless","beady-eyed","green-scaled",\
                     "grey-scaled","bulging-eyed","big-nosed",\
                     "fierce","pale" })

#define ADJ_LIST2 ({ "long-armed","long-legged","mud-covered",\
                     "thick-chested","towering","enourmous",\
                     "barrel-chested","thick-armed","muscular",\
                     "slobbering","psychotic","broad-shouldered",\
                     "flabby","lean","drooling","ancient" })

#define ATTACK_ACT ({ "grin","snarl","growl","kick","tackle","laugh",\
                      "smirk","smile evil","smile grim" })

#define DEFAULT_STATS ({ 230,120,250,50,75,140 })

#define TROLL_EQUIP ({ "/d/Shire/common/trollsh/weapon/trollclub" })
                                                                         
//** Global Variables **//
int gAttackAlarm = 0;
int gLockStats = 0;

//** Prototypes **//
void set_troll_stats(int i);

void
create_shire_monster()
{
    string adj1 = ONE_OF_LIST(ADJ_LIST1),
           adj2 = ONE_OF_LIST(ADJ_LIST2),
          myShort = adj2+" "+adj1+" troll";

    FIXEUID

    set_name(({"troll","_trollshaw_troll"}));
    set_adj(({adj2,adj1}));
    set_short(myShort);
    set_race_name("troll");
    set_long("This "+short()+" has a black scaly hide "+
        "and is extremly tough. It probably shuns the sunlight, as it would "+
    	"turn into stone if struck by it. It prefers the harsh illumination "+
        "of fire to the glistering aura of the moon. These trolls are horrible "+
        "enemies as they fear no living thing.\n");
	       
    add_prop(CONT_I_WEIGHT, (300 + random(100)*1000));
    add_prop(CONT_I_HEIGHT, (300 + random(75)));

    add_equipment(TROLL_EQUIP);    	    
    set_stats(DEFAULT_STATS);
    set_whimpy(50);
    set_alignment(-800 -random(300));
    set_pick_up(1);
    set_aggressive(1);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_CLUB, 70);

    set_cact_time(5);
    add_cact("say You look tasty!");
    add_cact("lick");
    add_cact("knee all");
    add_cact("scream");
    add_cact("grin");
}

void
attack_random()
{
    object *pl = FILTER_PLAYERS(deep_inventory(ENV(TO))),
            victim = ONE_OF(pl); // We trolls have _no_ friends! :)

    gAttackAlarm = 0;
    if (objectp(query_attack()) || !present(victim,ENV(TO)) ||
        victim->query_wiz_level())
        return;

    if (!gLockStats)
    {
        set_troll_stats(victim->query_average_stat());
        gLockStats = 1;
    }
    command(ONE_OF_LIST(ATTACK_ACT)+" "+victim->query_real_name());
    command("kill "+victim->query_real_name());
}

void
set_troll_stats(int i)
{
    int s1 = i * 2, d1 = DEFAULT_STATS[SS_STR],
        s2 = i - random(i/10), d2 = DEFAULT_STATS[SS_DEX],
        s3 = i * 2, d3 = DEFAULT_STATS[SS_CON],
        s4 = i - random(i/5), d4 = DEFAULT_STATS[SS_INT],
        s5 = i - random(i/5), d5 = DEFAULT_STATS[SS_WIS],
        s6 = i + random(i/2), d6 = DEFAULT_STATS[SS_DIS];

    s1 = MAX(s1,d1); s2 = MAX(s2,d2); s3 = MAX(s3,d3);
    s4 = MAX(s4,d4); s5 = MAX(s5,d5); s6 = MAX(s6,d6);
    set_stats(({s1,s2,s3,s4,s5,s6}));
}

void
init_attack()
{
    if (!gAttackAlarm)
        gAttackAlarm = set_alarm(itof(random(10)),0.0,attack_random);
}

int
query_knight_prestige() { return 500 + random(300); }
    
public void
do_die(object killer)
{
    killer->add_prop("_i_killed_trollshaw_trolls",
        killer->query_prop("_i_killed_trollshaw_trolls") + 1);
    ::do_die(killer);
}
