inherit "/std/monster";
 
#include "rdefs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
 
#define TROLL_LAIR D_HOLLIN+"trolls_lair"
 
#define RNAMES ({ \
   "Gwashin","Gnaum","Garb","Gufs","Uzag", \
   "Zak", "Zagh","Zokk","Bism","Urk" })
 
#define RLONG ({ \
"has a pair of fathomless black eyes which penetrates your "+\
"heart. You can clearly see that he is a master of his profession.\n",\
"is a ghastly sweating figure of a strong nature.\n",\
 "is obviously not in the mood for conversations.\n",\
"is figuratively awesome! He is twice as tall as you and \n"+\
"equally wide. \n",\
 "looks stern and rigid. What a troll soldier!\n",\
 "really looks awesome! His feet drum as he walks!\n",\
 "has got a frightening look. Beware, he might be dangerous!\n",\
"has a pair of red, hypnotizing eyes. They burn with intensity as they look at you.\n",\
"looks tall and dangerously hungry.\n", \
"is laughing mockingly at you.\n" })
 
#define RWEIGHT ({ 230, 203, 235, 233, 304, 280, 298, 276, 245, 226 })
#define RHEIGHT ({ 320, 250, 301, 304, 410, 290, 360, 260, 210, 360 })
 
#define RADJ ({ "black eyed","moronic looking", "ghastly","fierce","huge", \
               "rigid","deadly","frightful","red eyed","vicious"})
 
/* str dex con int wis dis */
#define RSTAT ({ \
                ({ 75, 89, 76, 23, 16, 78 }), \
                ({ 67, 45, 60,  2,  4, 40 }), \
                ({ 97, 67, 75, 40, 35, 89 }), \
                ({ 70, 99, 78, 29, 32, 90 }), \
                ({ 99, 47, 76, 15, 15, 79 }), \
                ({ 92, 62, 74, 23, 70, 84 }), \
                ({ 97, 59, 89, 39, 32, 90 }), \
                ({ 87, 69, 96, 95, 48, 91 }), \
                ({ 54, 99, 89, 89, 87, 90 }), \
                ({ 56, 64, 99, 67, 75, 90 }) })
 
#define SKUCOM ({ 67, 34, 56, 89, 43, 42, 49, 59, 97, 94 })
#define SKDEF  ({ 67, 20, 50, 94, 50, 32, 79, 78, 91, 40 })
 
int time_next;
 
create_monster()
{
    seteuid(getuid());
    create_troll_soldier(random(10));
}
 
int myrand(int val)
{
    return val-val/4+random(val/2)+1;
}
 
void setup_skills();
 
create_troll_soldier(int r)
{
    set_name(({"troll soldier", "soldier", RNAMES[r], "_troll_soldier_"}));
    set_pname("soldiers");
    set_short(RADJ[r] + " troll soldier");
    set_pshort("troll soldiers");
    set_adj(RADJ[r]);
    set_race_name("troll");
    set_long(
        "This is one of the troll soldiers that patrol " +
        "the Mines of Moria. It is evil and loathing like " +
        "all creatures perverted by the will of Sauron, but the " +
        "troll soldiers, who result from the crossbreeding of " +
        "orcs and trolls, are known to be more cruel than " +
        "imaginable.\n"+
        "This particular beast, " + RLONG[r]);
    add_prop(CONT_I_WEIGHT, RWEIGHT[r] * 1000);
    add_prop(CONT_I_HEIGHT, RHEIGHT[r]);
    MAKE_MONEY;
 
 
    set_stats(RSTAT[r]);
    set_hp(50000);
 
    setup_skills();
 
    set_skill(SS_UNARM_COMBAT, myrand(SKUCOM[r]));
    set_skill(SS_WEP_SWORD,    myrand(SKUCOM[r]));
    set_skill(SS_WEP_AXE,      myrand(SKUCOM[r]));
    set_skill(SS_WEP_KNIFE,    myrand(SKUCOM[r]));
    set_skill(SS_WEP_CLUB,     myrand(SKUCOM[r]));
    set_skill(SS_DEFENCE,      myrand(SKDEF[r]));
    set_skill(SS_PARRY,        myrand(SKDEF[r]));
    set_pick_up(75);
 
    set_aggressive(1); set_attack_chance(90);
 
    set_alignment(-360 + random(100));
 
    set_act_time(5);
    add_act("emote growls ferociously at you.");
    add_act("grin");
    add_act("emote licks its lips, anticipating eating you alive.");
    add_act("emote licks its weapon evilly, watching your response.");
    add_act("emote swings its weapon past your head, narrowly missing your throat.");
    add_act("emote inspects his armour.");
    add_act("emote growls: Hey you! Get lost!");
 
    set_cact_time(5);
    add_cact("shout RRRRRMmmmmm baaaaaaaaaaah!!");
    add_cact(({"emote hisses: You Snaga! Obey! Die!!", "laugh"}));
    add_cact("emote knocks you to the ground, leaving you " +
        "battered and bleeding.");
    add_cact("emote grins evilly and laughs.");
    add_cact("emote hisses something evil at you");
    add_cact("says Uruk-hai! Snaga burzum hak, hak!");
    add_cact("emote bites you in the throat!");
    add_cact("emote attacks you with renewed vigor!"); 
    add_cact("emote charges, knocking you against the wall!");
    add_cact("emote charges, narrowly missing you!");

    set_restrain_path(D_HOLLIN);
    set_monster_home(TROLL_LAIR);
    set_random_move(1);
 
}
 
void
setup_skills()
{
    mapping allskills = SS_SKILL_DESC;
    int *skills = m_indexes(allskills);
    int i;
 
    for(i=0;i<sizeof(skills);i++)
        set_skill(skills[i], myrand(query_stat(allskills[skills[i]][2]))/2);
}
 
void
arm_me()
{
    string wep = ({"trollaxe","trollsword","trollclub",
        "trollscimitar"})[random(4)];
    clone_object(D_WEAPON+wep)->move(TO);
    clone_object(D_ARMOUR+"wtrplate")->move(TO);
    clone_object(D_ARMOUR+"trollshield")->move(TO);
    command("wield weapon");
    command("wear armours");
}
 
int
in_domain(object who)
{
    string d1,d2;
    if(!E(who)) return 0;
    if(sscanf(file_name(E(who)), "/d/Shire/common/hollin/%s", d1)==1)
        return 1;
    return 0;
}
 
 
#ifdef PROBABLY_NOT_EY
 
set_spell_mess1(navn + " hurls a huge block of stone upon its opponent.");
set_spell_mess2(navn + " hurls a huge block of stone upon you.");
set_chance(lvl);
set_spell_dam(10 + lvl);
if (!pick)
    set_random_pick(9);
 
}
 
monster_init(this)
{
    object          say_str, says;
    say_str =
        ({
 
        });
    if (this_player()->query_npc())
        return 1;
    if (query_attack() != this_player() &&
        find_armour(this_player(), "trollcloak", 1)) {
        says = say_str[random(3)];
        ws(NAME(TO) + " turns to you and says: " + says + "\n",
           NAME(TO) + " says: " + says + "\n");
        return 1;
    } else {
        ws(NAME(TO) + " screams ugly and starts bashing and slicing you!\n",
           NAME(TO) + " screams ugly starting bashing and slicing " + 
               NAME(TP) + "!\n");
        return 0;
    }
}
ws(w, s)
{
    set_alarm(1.0, 0.0, "do_say", ({TP, w, s}));
}
do_say(arr)
{
    tell_object(arr[0], arr[1]);
    say(arr[2], arr[0]);
}
 
#endif
