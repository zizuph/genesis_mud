inherit "/std/monster";
 
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"
 
#include "/d/Rhovanion/lib/kill_log.h"
 
#define MMAN_AXE "_mirk_man_axe_"
#define MMAN_AXE_FILE "/d/Rhovanion/gundif/mman_axe"
#define LOST_AXE "_this_man_has_lost_his_axe_"
#define BASE_STAT 50
#define RAND 60
#define ADJ_LIST ({ "tall", "short", "plump", "lean", "fat" })
#define ADJ2_LIST ({ "dark-haired", "light-haired", "red-haired", \
                     "bald", "aging" })
 
 
void
create_monster()
{
    string adj1=ONE_OF_LIST(ADJ_LIST);
    string adj2=ONE_OF_LIST(ADJ2_LIST);
    set_race_name("human");
    set_name(({ "woodcutter", "man" }));
    set_gender(G_MALE);
    set_adj(adj1);
    add_adj(adj2);
    add_name("_mirk_man_");
    set_short(adj1+" "+adj2+" man");
 
    set_long("A man who spends most of his time in Mirkwood. "+
             "Judging by his equipment, his main occupation is "+
             "cutting the trees.\n");
 
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,"eyes you suspiciously. "+
             "It seems as if he thinks the item you try to give "+
             "him, could be poisoned.\n");
 
    set_base_stat(SS_STR,BASE_STAT+random(RAND));
    set_base_stat(SS_DEX,BASE_STAT+random(RAND));
    set_base_stat(SS_CON,BASE_STAT+random(RAND));
    set_base_stat(SS_DIS,BASE_STAT+random(RAND));
 
    set_skill(SS_WEP_AXE, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_KNIFE, 20);
    set_skill(SS_PARRY, 30);
    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_AWARENESS,60);
 
    set_act_time(15);
 
    add_act("emote peers warily around.");
    add_act("emote eyes you suspiciously.");
    add_act("sneeze");
    add_act("emote clenches his fists, as he looks around "+
            "for spiders.");
    add_act("@@clean_axe");
 
    set_cact_time(10);
 
    add_cact("say Why do you attack me, "+
              "when there are spiders around?! Do you like them?!\n");
    add_cact("ask enemy Are you mad?!!\n");
    add_cact("shout Help! I am being attacked!\n");
    add_cact("emote roars loudly in anger.\n");
 
    set_this_player(TO);
 
    seteuid(getuid(TO));
 
    call_out("arm_me",1.0,TO);
 
}
 
void arm_me(object ob)
{
    clone_object(MMAN_AXE_FILE)->move(ob);
    ob->command("wield all");
 
}
void clean_axe()
{
    object ob;
 
    ob=present(MMAN_AXE,all_inventory(TO));
    if (ob)
    {
      command("emote polishes his axe carefully.");
    }
    else if (TO->query_prop(LOST_AXE))
    {
        add_act("say Dammit! I have lost my axe somewhere!");
        add_act("emote looks at you suspiciously.");
        TO->add_prop(LOST_AXE,1);
    }
    command("emote searches around for his axe.");
}
