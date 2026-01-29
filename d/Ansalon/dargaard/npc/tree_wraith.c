/************************************************
 * Name: Wraith                                                      
 * By: Elmore, modified by Arman
 * Desc: An undead knight outside of Dargaard.
 * Note: Has a hunting function.
 * Hounds summoning modified by Blizzard, 1.04.2004.
 *                                                                             
 ************************************************/
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit AUTO_TEAM

string *gAdj1 = ({"ethereal", "shadowy", "shimmering", "evil"});

string adj1;

void arm_me();

object *gHunted = ({ });
int    gHaveSetTrigger = 0;
int    hound_here = 0;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif


int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}



void
create_krynn_monster()
{
    set_pick_up_team(({"hound"}));
    set_max_team_size_auto_join(5);

    set_name("wraith");    
    set_race_name("undead");

    adj1 = ONE_OF(gAdj1);
    set_adj(adj1);

    set_short(adj1+ " wraith");

    TO->add_prop(LIVE_I_NO_CORPSE, 1);
    TO->add_prop(MAGIC_I_BREATH_WATER, 1);
    TO->add_prop(LIVE_I_UNDEAD, 100);

    set_long("You stand before the cursed soul of a fallen knight, "+
             "a wraith from Dargaard Keep. "+
             "This horrible creature resembles a black, vaguely "+
             "man-shaped cloud shaped in the form of a knight of "+
             "Solamnia, dressed in ancient armours. Two hellish "+
             "red eyes glow from beneath its ghostly visor.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);

    set_gender(G_NEUTER);
    set_aggressive(VBFC_ME("check_aggressive"));

    /* Trolls can see in the dark */
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_stats(({140,140,140,80,90,180}));

    set_exp_factor(175);  // Because they have a drain special attack
                          // and hunting ability.

    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 60);

    set_alignment(-1150);
    set_knight_prestige(800);
    set_all_hitloc_unarmed(20);

    set_act_time(random(15));
    add_act("say Free me mortal from this cursed existance!");
    add_act("emote howls: Undeath before dishonour!");
    add_act("emote hisses: Death to you, mortal!");

    clone_object(DARM + "shroud.c")->move(TO,1);
    clone_object(DOBJ + "hilt.c")->move (TO,1);

    if(random(5) == 1)
      clone_object("/d/Krynn/common/scrolls/speak_with_dead_scroll")->move (TO,1);
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
        pen = 300 + random(100);
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
          "his claw-like arms.\n"+
          "You feel a sudden coldness spreading from your "+
          hitloc[wloc]+".\n");

        tell_room(E(TO), QCTNAME(TO) + " grabs around " +
          QTNAME(enemy) +"'s "+ hitloc[wloc] + " with his "+
          "claw-like arms.\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->add_prop(LIVE_I_NO_CORPSE, 1);
            tell_room(E(TO),QCTNAME(enemy) + "'s corpse turns to dust.\n" +
                "Suddenly a new wraith appears!\n", enemy);
            extra_wraith = clone_object(DNPC + "wraith");
            enemy->do_die(TO);    
            extra_wraith->move(E(TO));
            extra_wraith->command("get armours");
            extra_wraith->command("get weapons");
            extra_wraith->command("wear all");
            extra_wraith->command("wield all");
            extra_wraith->command("howl");
            extra_wraith->command("assist "+adj1+ " wraith");
 
        }
        return 1;
    }
    return 0;
}

public void
summon_hounds(object ob)
{
    int    num;
    object g1;

    for (num = 0; num < 4; num++)
    {
        command("shout This one is worthy of Lord Soth's graveyard! "+
            "Hounds of the Abyss! Come to my summons!");

        tell_room(E(TO),"From the depths of the shadows, a pack of " +
            "hounds from the pits of hell comes to the wraiths call!\n");

        for ( num = 0; num < 4; num++)
        {
            if ( !random(5) )
                g1 = clone_object(DNPC + "hound");
            else
                g1 = clone_object(DNPC + "hound2");
    
            g1->move(E(TO), 1);
            g1->command("kill " + ob->query_real_name());                
        } 
    }

    g1->command("emote howls chillingly into the air!");
    g1->command("emote snarls malevolently!");

}

void
attack_object(object ob)
{
    if(ob->query_average_stat() < 155)
    return;
 
    if ( hound_here == 0 )
    {
        summon_hounds(ob);
        hound_here = 1;
    }

    ::attack_object(ob);
    set_alarm(0.0,0.0,&set_hunting(ob));
}

void
attacked_by(object ob)
{
    if(ob->query_average_stat() < 155)
    return;
 
    if ( hound_here == 0 )
    {
        summon_hounds(ob);
        hound_here = 1;
    }

    ::attacked_by(ob);
    set_alarm(0.0,0.0,&set_hunting(ob));
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
