/************************************************
 * Name: Wraith                                                      
 * By: Elmore
 * Desc: A wraith for Dargaard Keep.
 * Note: Has a hunting function.
 *                                                                             
 ************************************************/
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

void arm_me();

object *gHunted = ({ });
int gHaveSetTrigger = 0;

int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}



void
create_krynn_monster()
{
    set_name("hunter");    
    set_race_name("undead");
    set_adj("ethereal");
    add_adj("mage");

    set_short("ethereal mage hunter");

    TO->add_prop(LIVE_I_NO_CORPSE, 1);
    TO->add_prop(MAGIC_I_BREATH_WATER, 1);
    TO->add_prop(LIVE_I_UNDEAD, 100);

    set_long("Before you hovers the ancient wraith of an Istarian " +
       "mage hunter! Over 300 years ago, before the cataclysm tore " +
       "the lands of Krynn part, the Clerics of Istar warred against " +
       "all spellcasters, hunting them down and putting them to the " +
       "sword for their 'sins'. This hunter seems to have fallen to his prey, " +
       "his spirit caught in a magical trap, leaving his body to die and " +
       "decay.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);

    set_gender(G_NEUTER);
    set_random_move(50);
    set_aggressive(VBFC_ME("check_aggressive"));

    /* Undead can see in the dark */
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_stats(({80+random(30),50+random(50),80+random(20),80,90,180}));

    set_exp_factor(120);  // Because they have a drain special attack
                          // and hunting ability.

    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 60);

    set_alignment(-1150);
    set_knight_prestige(100);
    set_all_hitloc_unarmed(20);

    clone_object("/d/Ansalon/dargaard/obj/armour/shroud.c")->move(TO,1);
    clone_object("/d/Krynn/common/scrolls/curse_scroll")->move (TO,1);
    command("wear all");

}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int
attack_id, int target_hitloc = -1)
{
    mixed a;

    a = ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    return a;
}

arm_me()
{
    seteuid(getuid(this_object()));

    command("wield all");
    command("wear all");
  
}

string
check_estring(object ob)
{
    int i;
    string str1,*str;
    str1 = ob->query_m_out();
    str = explode(str1," ");
    for(i=0;i<sizeof(str);i++)
    {
        str[i] = "'"+str[i]+"'";
    }
    str1 = implode(str," ");
    return str1;
}

int
set_hunting(object ob)
{
    if(!ob)
        return 0;

    if (!gHaveSetTrigger)
        trig_new("%s 'leaves' / 'sneaks' / 'rides' / 'panics' [and] [rides] [flees] [limping] %w",
        "react_leave");
    gHaveSetTrigger = 1;
    if (member_array(ob, gHunted) == -1)
    {
        if(E(ob) == E(TO))
        {
            ob->catch_msg(QCTNAME(TO) + " turns its red eyes at you.\n");
            tell_room(E(TO),QCTNAME(TO) + " turns its red eyes at " +
                QTNAME(ob) +".\n", ob);
        }
        gHunted += ({ ob });
    }
    gHunted -= ({ 0 });
    return 1;
}

void
react_leave(string name, string dir)
{
    object tone;
    tone = find_player(lower_case(name));
    if(!tone)
    {
        return;
    }
    if(member_array(tone,gHunted) != -1)
    {
        dir = extract(dir,0,-3);
        set_alarm(0.0,0.0,&command(dir));
        return;
    }
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc,
    hps;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    object extra_wraith;
    string description, name;

    attacktype = random(12);

    hitloc = ({"left arm","right arm","body","left leg","right leg","head"});

    if (attacktype == 0)
    {
        pen = 100 + random(100);
        hitres = enemy->hit_me(pen, 45, TO, -1);
        TO->heal_hp(pen);

        wloc = random(6);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "tiny";
        if(hitres[0] > 0)
            how = "small";
        if(hitres[0] > 10)
            how = "bleeding";
        if(hitres[0] > 20)
            how = "serious";
        if (hitres[0] > 40)
            how = "lethal";
        if (hitres[0] > 60)
            how = "mortal";


        enemy->catch_msg(QCTNAME(TO) + 
          " grabs around your " + hitloc[wloc] + " with "+
          "his ghostlike hands.\n"+
          "You feel a sudden coldness spreading from your "+
          hitloc[wloc]+".\n");

        tell_room(E(TO), QCTNAME(TO) + " grabs around " +
          QTNAME(enemy) +"'s "+ hitloc[wloc] + " with his "+
          "ghostlike hands.\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);     
        }
        return 1;
    }
    return 0;
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(0.0,0.0,&set_hunting(ob));
}

void
attack_object(object ob)
{
   ::attack_object(ob);
   set_alarm(0.0,0.0,&set_hunting(ob));
}
