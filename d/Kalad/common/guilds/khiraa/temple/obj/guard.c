/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/guard.c
 * Purpose    : The Death Knight Guild Guards. They guard the entrance.
 * Located    : ~khiraa/temple/rooms/temple_main
 * Created By : Sarr 22.Apr.97
 * Modified By: 
 */ 

inherit "/d/Kalad/common/raum/std/undead_std.c";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

/* By Sarr */

void
create_monster()
{
    ::create_monster();
    set_name("knight");
    set_adj("death");
    add_adj("guardian");
    set_short("guardian death knight of the Khiraa");
    set_race_name("knight");
    set_knight_prestige(1200);
    set_alignment(-1200);
    set_long("You gaze upon a giant armoured knight radiating nothing "+
    "but pure coldness and evil. Fully covered in black plate, it "+
    "stands motionless. Such a great aura of power and might surrounds "+
    "it, that you sense that these are Doom Lord Knights, the most "+
    "powerful of the death knights, and would kill you easily if "+
    "disturbed.\n");
    set_stats(({200,180,200,150,150,180}));
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_BASHSTUN,100);
    set_skill(SS_WHIRLWIND,100);
    set_cact_time(8);
    add_cact("kwail");
    add_cact("klaugh");
    add_cact("emote echos from within his black steel helm: Ye shall die!");
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(LIVE_I_UNDEAD,100);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(UNDEAD_I_NO_AUTO,1);
    add_magic_effect(TO);
}

mixed *
query_magic_protection(string what, object me)
{
    return ({100,0});
}

void
attacked_by(object ob)
{
        ::attacked_by(ob);
        command("ksay Run now little one......or DIE.");
}


void
arm_me()
{
    object arm,arm2,arm3,arm4,arm5,wep;
    seteuid(getuid(TO));
    arm = clone_object(RAUM(arm/gfplate));
    arm->move(TO,1);
    arm3 = clone_object(RAUM(arm/gboots));
    arm3->move(TO,1);
    arm4 = clone_object(RAUM(arm/ggloves));
    arm4->move(TO,1);
    arm5 = clone_object(RAUM(arm/dmrobe));
    arm5->move(TO,1);
    wep = clone_object(RAUM(wep/kbsword));
    wep->move(TO,1);
    wep = clone_object(RAUM(wep/kblsword));
    wep->move(TO,1);
    add_cmdsoul("/d/Kalad/common/guilds/khiraa/dk/commands/dk_soul");
    update_hooks();
    command("wear all");
    command("wield all");
}

int
special_attack(object enemy)
{
    command("kwhirl");
    command("kbash");
    if(random(3))
        return 0;
    command("emote hisses something incomprehensible.");
    if(random(100) < 50)
       set_alarm(4.0,0.0,"burn",enemy);
    else
       set_alarm(4.0,0.0,"death",enemy);
    if(!random(3))
        set_alarm(6.0,0.0,"shredem",enemy);
    else
        if(!random(3))
            set_alarm(6.0,0.0,"charge",enemy);
    return 1;
}

void
shredem(object en)
{
    tell_object(en,"The "+short()+" hacks away deeply into your "+
    "legs!\n");
    tell_room(E(en),"The "+short()+" hacks away deeply into "+QTNAME(en)+
    "'s legs!\n",en);
    en->heal_hp(-400);
}

void
charge(object en)
{
    tell_object(en,"The "+short()+" rams into your body with its "+
    "bloody horned helmet.\n");
    tell_room(E(en),"The "+short()+" rams into "+QTNAME(en)+"'s "+
    "body with its bloody horns!\n",en);
    en->heal_hp(-400);
}



void
burn(object enemy)
{
    string str;
    mixed *hr;
    if(!present(enemy,E(TO)))
        return;
    add_mana(-30);
    enemy->catch_msg(QCTNAME(TO)+" waves its hand through the air, and suddenly "+
    "a flaming arrow appears and slams into you!\n");
    tell_room(E(enemy),QCTNAME(TO)+" waves its hand through the air, "+
    "and suddenly a flaming arrow appears and slams into "+QTNAME(enemy)+
    "!\n",enemy);
    hr = enemy->hit_me(random(500)+1800,W_IMPALE,TO,-1);
    switch(hr[0])
    {
        case 0..10:
            str = "burnt a little bit";
        break;
        case 11..20:
            str = "burnt";
        break;
        case 21..30:
            str = "seared";
        break;
        case 31..50:
            str = "burnt badly";
        break;
        case 51..70:
            str = "seared badly";
        break;
        default:
            str = "burnt to a crisp";
    }
    enemy->catch_msg("You are "+str+"!\n");
    if(enemy->query_hp() <= 0)
        enemy->do_die(TO);
}

void
death(object enemy)
{
    string str;
    mixed *hr;
    if(!present(enemy,E(TO)))
        return;
    add_mana(-40);
    enemy->catch_msg(QCTNAME(TO)+" points an armoured hand at you "+
    "and utters: Die.\n");
    tell_room(E(enemy),QCTNAME(TO)+" points an armoured hand at "+
    QTNAME(enemy)+" and utters: Die.\n",enemy);
    hr = enemy->hit_me(random(800)+2000,MAGIC_DT,TO,-1);
    switch(hr[0])
    {
        case 0..10:
            str = "slightly";
        break;
        case 11..20:
            str = "solidly";
        break;
        case 21..30:
            str = "with solid force";
        break;
        case 31..50:
            str = "with crushing force";
        break;
        case 51..70:
            str = "with lethal force";
        break;
        default:
            str = "with awsome force";
    }
    enemy->catch_msg("A black beam shoots out of its hand "+
    "and strikes you "+str+"!\n");
    tell_room(E(enemy),"A black beam shoots out of its hand "+
    "and strikes "+HIM(enemy)+" "+str+"!\n",enemy);
    if(enemy->query_hp() <= 0)
        enemy->do_die(TO);
}



void
attack_object(object ob)
{
    if(!ob->query_npc())
        ::attack_object(ob);
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("ksay Ye shall die now!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
