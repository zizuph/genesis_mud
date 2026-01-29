#include "defs.h"
inherit "/d/Raumdor/std/guard_std.c";
inherit "/d/Raumdor/lib/intro";
inherit "/lib/unique";


/* The crystal knight of Drakmere */
object Genemy;

void arm_me();

int friend_names;
int start_time;
int total_time;

void
set_menemy(object ob)
{
    Genemy = ob;
    start_time = time();
}

object
query_menemy()
{
   return Genemy;
}


void arm_me_special()
{
    seteuid(getuid());
    
    object magic_ring;
    
     magic_ring = clone_unique(one_of_list(({
                    DRAKMERE_ARM_DIR + "ring_of_vigor.c",
                   })),
        15, DRAKMERE_ARM_DIR + "c_skirt.c", 0, 25),
        
    //magic_ring->move(this_object(), 1);
    
    //this_object()->command("wear all");
    
    KLOG("gilbert_drop","Gilbert cloned a "+magic_ring+".\n");
}


void
create_monster()
{
    ::create_monster();
    set_name("Sir Gilbert");
    set_race_name("human");
    add_name("knight");
    add_name("gilbert");
    add_name("_gilbert_new");
    set_adj("crystal");
    add_adj("shimmering");
    set_short("crystal shimmering knight");
    set_long("You gaze upon a knightish looking figure decked in formal "+
    "full-plate armour. The armour seems to be made of some kind of "+
    "crystal that shimmers with a bright light.\n");
    set_stats(STAT_ARRAY(200));
    set_skill(SS_DEFENCE,100);
    add_prop(NPC_I_NO_FEAR,1);
    set_skill(SS_PARRY,100);
    set_skill(SS_WEP_POLEARM,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_AXE,100);

    set_skill(SS_AWARENESS,100);
    set_skill(SS_HIDE,100);
    set_act_time(2);

    add_act("emote seems to gaze around the room, searching for something.");
    add_act("emote shimmers brightly.");
    set_cact_time(5);
    add_cact("emote burns with a holy light.");
    add_cact("emote utters: Ye shall burn in Hell!");
    set_alignment(DRAKMERE_ALIGN);
    set_title("of Drakmere, the Banisher of Darkness");
    set_all_hitloc_unarmed(30);
    
    seteuid(getuid());
    
    equip(({ 
        DRAKMERE_WEP_DIR + "g_claymore",
        DRAKMERE_ARM_DIR + "shim_plate",
    }));
    
    MONEY_MAKE_GC(random(15))->move(TO,1);
    
    arm_me();
}


void
arm_me()
{
    seteuid(getuid());
    
    object magic_ring;
    
     magic_ring = clone_unique(one_of_list(({
                    DRAKMERE_ARM_DIR + "ring_of_vigor.c",
                   })),
        15, DRAKMERE_ARM_DIR + "c_skirt.c", 0, 25),
        
    magic_ring->move(this_object(), 1);
    
    command("wear all");
    
    //KLOG("gilbert_drop","Gilbert cloned a "+magic_ring->short()+".\n");
}


void
do_die(object me)
{
    int i;
    string str;
    
    object magic_ring;
    
    object *obs;
    obs = me->query_team_others();
    total_time = time() - start_time;
    if(sizeof(obs))
        str = "with the following team:\n";
    else
        str = "alone.\n";
    for(i=0;i<sizeof(obs);i++)
        str += obs[i]->query_name()+" (stat ave: "+obs[i]->query_average_stat()+
        ")\n";
    KLOG("killed_gilbert",me->query_name()+" (stat ave: "+
    me->query_average_stat()+") killed Gilbert "+str+
    "It took "+total_time+" seconds.\n");
    command("shout No! I have... failed.");
    command("emote collapses to the ground.");
    
   
    
    
    ::do_die(me);
}
  

int
special_attack(object enemy)
{
    mixed *hitres;
    int i;
    int reduce;
    string str;
    if(random(5))
        return 0;
        
    if(query_hp() <= 500)
    {
        command("emote mutters a prayer to heal his wounds.");
        heal_hp(1500);
    }
    
    tell_room(E(TO),QCTNAME(TO)+" raises his arms and utters: Burn!\n");
    enemy->catch_msg("A fire sprouts from under you, and consumes you!\n");
    tell_room(E(TO),"A fire sprouts from under "+QTNAME(enemy)+", and "+
    "consumes "+HIM(enemy)+".\n",enemy);
    i = random(200)+250;
    
    hitres = enemy->hit_me(i,MAGIC_DT,TO,-1);
    reduce = hitres[3] * (enemy->query_magic_res(MAGIC_I_RES_FIRE) / 100);
    enemy->heal_hp(reduce);
    
    switch(hitres[0])
    {
        case 0..15:
            str = "hardly ";
        break;
        case 16..30:
            str = "";
        break;
        case 31..45:
            str = "badly ";
        break;
        case 46..60:
            str = "severly ";
        break;
        case 61..75:
            str = "to a crisp ";
        break;
        default:
            str = "and nearly incinirated ";
    }
    enemy->catch_msg("You are burnt "+str+"by the fire.\n");
    return 1;
}


void
attack_object(object ob)
{
    int i;
    object *friends;
    friends = query_team();
    ::attack_object(ob);
    for(i=0;i<sizeof(friends);i++)
        friends[i]->command("assist");
        
    if(sizeof(friends))
        ob->attack_object(friends[0]);
        
    
}


void
attacked_by(object ob)
{
    object *obs;
    ::attack_object(ob);
    obs = query_team();
    if(sizeof(obs))
    {
        ob->attack_object(obs[0]);
    }
   
}

