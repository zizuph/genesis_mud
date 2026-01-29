/*  -*- LPC -*-  */


 
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>

#define LIVE_I_DONT_CLING  "_live_i_dont_cling"
//#define ORC_LAIR MINES_DIR + "orc_lair"

#define RNAMES ({\
    "tharburz", "frushkul", "shakh", "aarshlut", "tharguz", \
    "muzgaash", "durgaz", "bishuk", "fotkurz", "narnulubat",\
    "glob", "lugburzum", "lughorn", "nurzum", "brogud",\
    "ashbarzg", "daruk", "nurzum", "dargum", "skrithurz",\
    "barash", "durgaz", "ulkurz", "lagurz", "garshuk"\
})

#define RADJ ({ \
"large black-eyed", "skinny hideous", "long-armed evil", "grey-skinned pale", "large club-footed",\
"large fanged", "grim pale", "grinning brutal", "dull-witted terrible", "squat broad",\
"dark-skinned swarthy", "large wide mouthed", "flat-nosed sallow skinned", "deadly flat-nosed","hideous warring",\
"squint-eyed flat-nosed", "large brutal", "cruel pale", "repulsive squat", "red squint-eyed broad",\
"hideous brutal", "terrible black-eyed", "savage black-skinned", "large black", "leering squint-eyed"})

#define SKCOM  ({ 94, 42, 20, 50, 64, 42, 75, 78, 99, 64, \
          85, 54, 76, 100, 47, 76, 49, 95, 120, 100,\
          48, 75, 110, 26, 57 })
#define SKDEF  ({ 57, 30, 20, 50, 30, 30, 70, 99, 100, 46, \
          32, 30, 53, 80, 32, 73, 53, 20, 100, 96, \
          46, 20, 56, 99, 10 })

/* str dex con int wis dis */
#define RSTAT ({ \
    ({  60,  70,  70, 30, 13,  60 }), \
    ({    45,  45,  75, 27, 20,  50 }), \
    ({    30,  20, 120, 21, 23,  34 }), \
    ({  50,  50,  90, 25, 25,  50 }), \
    ({  75,  45, 130, 23, 27,  51 }), \
    ({  70,  71, 161, 14, 15,  80 }), \
    ({  75,  95, 170, 15, 36,  45 }), \
    ({  90,  75, 125, 24, 24,  70 }), \
    ({ 100, 100, 200, 50, 40, 100 }), \
    ({  50,  50, 100, 27, 25,  30 }), \
    ({  51,  52,  48, 12, 18,  70 }), \
    ({    25,  75, 202, 15, 27, 100 }), \
    ({    45,  52,  82, 32, 49,  75 }), \
    ({ 120, 100, 240, 25, 45, 100 }), \
    ({ 100,  20, 100, 20, 12, 102 }), \
    ({  63, 121, 120, 14, 15,  19 }), \
    ({  74,  45,  68, 29, 29,  49 }), \
    ({ 101,  74, 178, 16, 16, 100 }), \
    ({ 150, 149, 250, 45, 49, 150 }), \
    ({  63, 150, 130, 22, 22,  70 }), \
    ({    25,  21, 100, 45, 45, 150 }), \
    ({    45,  20, 212, 47, 12,  50 }), \
    ({ 125, 125, 224, 10, 10, 125 }), \
    ({    45,  45,  96, 62, 51, 100 }), \
    ({ 170, 160, 180, 20, 15, 120 }) })

#define RLONG ({ \
    "has black eyes and is tall.",\
    "looks skinny and hideos.",\
    "looks evil and has long arms.",\
    "looks pale and grey-skinned.",\
    "looks large and has club feet.",\
    "has large, dripping fangs and is tall.",\
    "has a grim look on his pale face.",\
    "looks dim-witted but terrible.",\
    "looks squat and broad.",\
    "has dark skin and looks dark skinned.",\
    "has dark skin and looks terrible with its dripping fangs.",\
    "has a wide mouth and is very tall.",\
    "has a flat nose and sallow skin.",\
    "looks deadly and has a flat nose.",\
    "looks hideous and ready to attack anything.",\
    "has squint eyes and a flat nose.",\
    "looks very tall and very brutal.",\
    "has pale skin and appears cruel.",\
    "looks repulsive and squat.",\
    "looks tall and has red, squinting eyes.",\
    "looks hideous and brutal.",\
    "has black eyes and looks terrible.",\
    "has black skin and looks savage",\
    "looks tall and has black skin.",\
    "looks leering with squint eyes.",\
})

inherit BASE_MONSTER;
inherit IM_TELL_FILE;

//--**-- GLOBAL VARIABLES --**--//
int do_not_intro;
int troll_id;
 
/* prototypes */
void arm_me();
void re_intro();
void do_intro(string who);
void do_spit(string who);
int do_help(string what);
void react_quit(string who);
void do_follow(string pl, string dir);
void set_restrain_path_with_delay();
 
CONSTRUCT_MONSTER
{
    seteuid(getuid());
}

string
query_nonmet_name()
{
    return implode(query_adj(1), " ") + " soldier";
} 

int query_no() { return troll_id; }
void set_no(int num) { troll_id = num; }

public void
set_restrain_path_with_delay()
{
    if (!query_restrain_path() || !sizeof(query_restrain_path()))
        set_restrain_path(implode(explode(file_name(ENV(TO)),"/")[0..3], "/"));
}  

create_troll_soldier(int r)
{
    set_no(r);
    set_living_name(RNAMES[r]);
    set_name(({RNAMES[r], "soldier", "_orc_soldier_"}));
    set_pname("soldiers");
    add_adj(RADJ[r]);
    set_short(RADJ[r] + " orc");
    add_adj("orc");
    set_race_name("orc");
    set_long("This is a "+RADJ[r]+" orc soldier. It is one of the orcs " +
        "from the Mines of Moria. From the sign on its shield, it is " +
        "from the tribe of the Red Claw. He "+RLONG[r]+" He looks very evil.\n");
    set_title("Vicious Clan Member of the Red Claw");

    add_prop(CONT_I_WEIGHT, myrand(SKCOM[r]) * 1000);
    add_prop(CONT_I_HEIGHT, myrand(SKDEF[r]) + 100);

    set_stats(RSTAT[r]);
    refresh_mobile();
    setup_skills();

    set_skill(SS_UNARM_COMBAT, skill_random(SKCOM[r]));
    set_skill(SS_WEP_SWORD,    skill_random(SKCOM[r]));
    set_skill(SS_WEP_AXE,      skill_random(SKCOM[r]));
    set_skill(SS_WEP_KNIFE,    skill_random(SKCOM[r]));
    set_skill(SS_WEP_CLUB,     skill_random(SKCOM[r]));
    set_skill(SS_DEFENCE,      skill_random(SKDEF[r]));
    set_skill(SS_PARRY,        skill_random(SKDEF[r]));

    add_prop(LIVE_I_SEE_DARK,  2);
    add_prop(LIVE_I_QUICKNESS, 150);
 
    set_pick_up(75);

    set_aggressive(1); set_attack_chance(90);

    set_alignment(-500 + random(200));

//    set_tell_active(1);      // Takes a lot of cpu.

    set_act_time(5);
    add_act("shout Karanthan! Bah karindan!");
    add_act("emote says something unpronouncable.");
    add_act("shout Throqu bag ruk!"); 
    add_act("grin");
    add_act("spit");
    add_act("puke");
    add_act("laugh hyste");

    set_cact_time(5);
    add_cact("shout KIRIN! Agz burzum hantan!");
    add_cact("shout I kuduk zgram!");
    add_cact("emote hisses: Garan tuli ARHAGH UZUMA!");
    add_cact("emote kicks you around.");
    add_cact("emote hisses: Get lozt, snaga!");

//    set_monster_home(ORC_LAIR);
    set_restrain_path("/d/Shire/moria/mines"); 
 

    set_alarm(1.0, 0.0, &arm_me());
    trig_new("%w 'leaves' %s", "do_follow");
    trig_new("%w 'sneaks' %s", "do_follow");
    trig_new("%s 'introduces' %s", "react_intro");
    trig_new("%s 'spits' 'on' 'you' %s", "react_hostile");
    trig_new("%s 'kicks' 'you' %s", "react_hostile");
    trig_new("%s 'shouts:' 'ONA' 'SNAGA' 'AKI!!' %s", "react_help");

    ::create_monster();
}

arm_me()
{
    int *skills, i, m, max, no;
    string wep;

    skills = ({
    query_skill(SS_WEP_AXE),
    query_skill(SS_WEP_SWORD),
    query_skill(SS_WEP_CLUB),
    query_skill(SS_UNARM_COMBAT)
    });
    for (i=0, max=0; i<sizeof(skills); i++)
    if (skills[i] > max) { max = skills[i]; m = i; }

    switch(m) 
    {
        case 0:
            clone_object(MORIA_WEP+"orcaxe")->move(TO);
            break;
        case 1:  
            clone_object(MORIA_WEP+"orcfalch")->move(TO);
            break;
        case 2:  
            clone_object(MORIA_WEP+"orcscim")->move(TO);
            break;
        default: 
            clone_object(MORIA_WEP+"orcscim")->move(TO);
            break;
    }
    
    command("wield weapons");
    clone_object(MORIA_ARM+"orcplate")->move(TO); 
    clone_object(MORIA_ARM+"orcshield")->move(TO);
    clone_object(MORIA_ARM+"orchelm")->move(TO);
    clone_object(MORIA_OBJ+"lootsack")->move(TO);
    command("wear armours");

    no = random(STR(TO)/15) + 3;
    for (i=0; i < no; i++)
    clone_object(MORIA_OBJ+"orcdrink")->move(TO);
    set_alarm(1.0, 15.0 * 60.0 / itof(no), "drink_tarin_tar");
    if (!query_restrain_path() || !sizeof(query_restrain_path()))
        set_alarm(0.0, 0.0, set_restrain_path_with_delay); 

}

int
react_intro(string who, string dummy)
{
    if (do_not_intro)
    return 1;
    do_not_intro = 1;

    if (strlen(who)) 
    {
    who = lower_case(who);
    set_alarm(3.0, 0.0, &do_intro(who));
    return 1;
    }
}

void re_intro()
{
    do_not_intro = 0;
}

void
do_intro(string who)
{
    object obj;

    set_alarm(itof(random(20)), 0.0, &re_intro());
 

    if((obj=present(who, ETO)) && !obj->query_npc())
    {
    switch(random(4))
    {
        case 0:
        command("shout Ha! I'll eat you alive, "+obj->query_name()+"!\n");
        command("kick "+who);
        command("kill "+who);
        return;
        case 1:
        command("introduce me");
        command("shout Let it be known, that I will spit on your corpse "+obj->query_name()+"!!");
        command("kill "+who);
        return;
        case 2:
        command("introduce me");
        command("spit "+who);
        command("laugh hyste");
        command("kill "+who);
        return;
        case 3:
        command("introduce me");
        command("puke "+who);
        command("cackle");
        command("kill "+who);
        return;
     }
    }
}

int
react_hostile(string who, string dummy)
{
    object obj = present(who, ENV(TO));
    if(!obj)
    return 0;
    set_alarm(2.0, 0.0, &do_spit(lower_case(who)));
    return 1;
}

void do_spit(string who)
{
    command("shout Barin-zan Uruk-Hai! Giranban taran Mordor Ayan!!");
    command("spit "+who);
}

void
orc_can_you_help_me(object *enemies)
{
    object to_help = previous_object();
    object pick;

    if (!sizeof(enemies))
    return 0;

    if (query_attack())
    {
    command("shout " + CAP(to_help->query_real_name()) +
        "!! Kirn tuk ta!");
    command("grin");
    } 
    else
    {
    command("laugh evilly");
    attack_object(enemies[0]);
    tellem(TO, enemies[0],
            "$N $turn towards #n, attacking #o, "+ 
        "hackin' and slashing like a maniac.\n");
    command("shout Tulik tasj tasj! Snaga hin hel!!");
    }
}

int
react_help(string what, string dummy)
{
    set_alarm(2.0, 0.0, &do_help(lower_case(what)));
    return 1;
}

int
do_help(string what)
{
    object obj = present(what, ENV(TO));
    object *enemies;

    if(!obj) {
    command("shout Karantum Uruk-Hai!!! Garin talak!");
    return 1;
    }
    else
    {
    command("kick "+what);
    obj->command("scream");
    command("laugh evil");
    if(!obj->id("_orc_soldier_"))
        return 1;
    enemies = (object *)obj->query_enemy(-1) - ({ (object)obj->query_attack() });
    if(!sizeof(enemies))
        return 1;
    attack_object(enemies[random(sizeof(enemies))]);
    command("emote hisses to the "+obj->short()+": Hai! Tarum kadak! Snaga hin hel!!");
    return 1;
    }
}

//----------------------------------------------------------------

int
drink_tarin_tar()
{
    if (query_hp() * 3 < query_max_hp() || 
    (query_intoxicated() < 10 && query_hp() * 3  < 2 * query_max_hp()) || 
    random(44) == 0)
    {
    if (!present("_tarin_tar_", TO))
        return 0;
    command("drink orc-water");
    return 1;
    }
    return 0;
}
    
int
special_attack(object attacker)
{
    if (drink_tarin_tar())
    return 1;

    return ::special_attack(attacker);
}

void
react_quit(string who)
{
    command("get all");
}
 
void
do_follow(string pl, string dir)
{  
    int     dn;
    mixed   exits;
    object  enemy = query_attack(),
            room = ENV(TO);
     
    if (!objectp(enemy) ||
        (lower_case(pl) != enemy->query_real_name()) ||
        query_prop(LIVE_I_DONT_CLING))
        return;
    
    // strip trailing .\n from dir string 
    dir = dir[0..(strlen(dir)-3)];
    
    if (dir == "the game")
    {
        set_alarm(2.0 + 5.0*rnd(), 0.0, &react_quit(pl));
        return;
    }
        
    exits = room->query_exit();
    if ((dn = member_array(dir, exits)) < 0)
        return;     
 
    if (!sizeof(filter_exits(exits[dn-1..dn+1])))
    {
        command("scream");
        return;
    }
        
    set_alarm(0.0, 0.0, &command(dir));
} 
