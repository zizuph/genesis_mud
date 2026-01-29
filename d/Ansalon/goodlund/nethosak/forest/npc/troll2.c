/******************************************************************************
 * Mithas forest trolls.                                                      
 * Ashlar, 19 Jul 97                                                          
 * Altered by Elmore.                                                         
 *                                                                            
 * Remarks:                                                                   
 * Boron, the AoB asked me to raise their int/wis and set_exp_factor(130) due 
 * to their hunting ability. This has now been done.                          
 * - Elmore, 27.March - 2001                                                  
 * Due to huge exp they give in very short time I reduced exp to 100%
 * plus set extra stat on str and dex instead of having them on base (that also
 * reduces given exp. Trolls are hard to fight but not that hard.
 *        Thorgal 05.04.2001
 * Since they now give about as much xp as the 'normal' trolls in Neraka,
 * I've added 20% more xp to the main trolls.
 * - Elmore, April 2001.
 *
 * Added stun and damage special.
 * Added 7 more Ac.
 * Added 5% more xp.
 * Improved the hunting ability.
 * Added gems.
 * - Elmore, Jun 2001.
 ******************************************************************************/
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "../local.h"
#include "/d/Genesis/gems/gem.h"

inherit AM_FILE
inherit AUTO_TEAM

#define WEP NWEP + "club"

string *gAdj1 = ({ "huge", "lurking", "snarling", "powerful",
    "large", "big", "muscular", "drooling", "massive" });
string *gAdj2 = ({ "forceful", "repulsive", "horrid", "snarling",
    "beastly", "frightening", "dangerous", "lethal" });

string adj1, adj2;
int gOkDropLimb = 1;
mixed gArms = -1;
int gRegens = 5;
object *gHunted = ({ });
object gem;
int gHaveSetTrigger = 0;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

void arm_me();

/*
 * Call this if the troll grows from another's limb
 * (called by the limb)
 */
void
set_arms(mixed a)
{
    gArms = a;
}

void
set_regens(int r)
{
    gRegens = r;
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("forest troll");    
    set_race_name("troll");

    adj1 = ONE_OF(gAdj1);
    adj2 = ONE_OF(gAdj2);
    set_adj(adj1);
    add_adj(adj2);

    set_short(adj1+ " "+adj2+" forest troll");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_long("The " + short() + " is a large humanoid creature, covered " +
        "in thick fur. Long, yellow fangs reach out of his cruel mouth, " +
        "and a foul smell surrounds him. His green-grey skin makes him "+
        "blend in with the forest, making him very hard to see. These "+
        "trolls might appear stupid, but as you look into their dark eyes "+
        "you sense a form of intelligence.\n");

    add_prop(CONT_I_HEIGHT, 230);
    add_prop(CONT_I_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 140000);

    /* Trolls can see in the dark */
    add_prop(LIVE_I_SEE_DARK, 3);

    /* Team with other trolls */
    set_pick_up_team(({"troll"}));

    set_stats(({240,165,220,140,140,170}));
    set_hp(query_max_hp());
    set_exp_factor(125);

    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 50);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 95); //they smell and listen and ...

    set_alignment(0);
    set_knight_prestige(100);

    set_all_hitloc_unarmed(37);

    set_alarm(0.0,0.0,&command("assist troll"));
    arm_me();
}

void
regrow(string limb)
{
    tell_room(E(TO), QCTNAME(TO) + " grows a new " + limb + "!\n");
    gOkDropLimb = 1;
}

void
limb_fall_off(object attacker, string limb)
{
    object o,w;
    int reg_time;

    if (!gOkDropLimb)
        return;

    if (gRegens-- <= 0)
        return;

    gOkDropLimb = 0;

    if (limb == "legs")
        limb = ONE_OF(({"left leg","right leg"}));

    attacker->catch_msg("You severed " + QTNAME(TO) + "'s " + limb +
        ", which falls to the ground.\n");
    tell_room(E(TO), QCTNAME(attacker) + " severed " + QTNAME(TO) +
        "'s " + limb + ", which falls to the ground.\n", attacker);

    o = clone_object("/d/Ansalon/goodlund/nethosak/forest/obj/troll_limb");
    o->set_limb(limb);
    if (limb == "left arm")
        w = query_weapon(W_LEFT);
    if (limb == "right arm")
        w = query_weapon(W_RIGHT);

    if (w)
    {
        object t = this_player();
        set_this_player(TO);
        w->unwield_me();
        w->move(o, 1);    
        o->set_weapon(w);
        set_this_player(t);
    }
    o->move(E(TO));

    reg_time = 10 + random(10);
    
    o->set_regen(reg_time);
    add_attack_delay(25,0);
    set_alarm(20.0,0.0,&regrow(limb));
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int
attack_id, int target_hitloc = -1)
{
    mixed a;

    a = ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    switch(a[1])
    {
        case "left arm":
        case "right arm":
        case "legs":
            if ((a[0] > 9) && random(4))
                set_alarm(0.0,0.0,&limb_fall_off(attacker,a[1]));
            break;
    }
    return a;
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    object stun;

    int currentHp, maxHp;

    attacktype = random(3);

    hitloc = ({"left arm","right arm","left leg","right leg"});
  
    maxHp = TO->query_max_hp() / 2;
    currentHp = TO->query_hp();

    if (attacktype == 1 && currentHp < maxHp && !TP->query_prop(I_AM_SLOWED_FROM_TROLLS))
    {

        hitres = enemy->hit_me(pen, 40, TO, -1);

        wloc = random(4);
        att  = random(2);

        switch(random(5))
        {
            case 0:
                how = "misses";
                break;
            case 1:
                how = "barely misses";
                pen = random(50);
                break;
            case 2:
                how = "slight bruises";
                pen = random(100);
                break;
            case 3:
                how = "numbs";
                pen = random(150);
                break;
            default:
                how = "smashes";
                pen = random(200);
                break;
        }

        enemy->catch_msg(QCTNAME(TO) + 
          " joins his fists and takes a swing at you. "+
          "His joined fists "+how+" your muscles in your "+ hitloc[wloc]+ "!\n");

        tell_room(E(TO), QCTNAME(TO) + " joins his fists and takes a swing " +
          "at " + QTNAME(enemy) + ". His joined fists " + how + " the muscles in "+
          QTNAME(enemy)+ "'s " + hitloc[wloc] + "!\n",({enemy, TO}));


        stun = clone_object("/d/Ansalon/goodlund/nethosak/forest/obj/stun");
        stun->move(TP,1);
             
        TP->add_prop(I_AM_SLOWED_FROM_TROLLS,1);

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }

        return 1;
    }

    return 0;
}

arm_me()
{
    seteuid(getuid(this_object()));

    if (gRegens == 5)
    { 
        gem = RANDOM_GEM(1);
        gem->move(TO,1);
    }
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
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
        trig_new("%s 'leaves' / 'sneaks' / 'panics' [and] [flees] [limping] %w",
        "react_leave");
    gHaveSetTrigger = 1;
    if (member_array(ob, gHunted) == -1)
    {
        if(E(ob) == E(TO))
        {
            ob->catch_msg(QCTNAME(TO) + " sniffs at you and a light " +
                "glints in his eyes.\n");
            tell_room(E(TO),QCTNAME(TO) + " sniffs at " + QTNAME(ob) +
                " and a light glints in the " + TO->query_race_name() +
                "'s eyes.\n", ob);
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

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(0.5,0.0,&set_hunting(ob));
}

void
attack_object(object ob)
{
    ::attack_object(ob);
    set_alarm(0.5,0.0,&set_hunting(ob));
}

void
panic_fire()
{
    if (E(TO)->query_prop(OBJ_I_HAS_FIRE))
    {
        tell_room(E(TO), QCTNAME(TO) + " screams in rage and fear at the " +
            "sight of a fire.\n", TO);
        run_away();
    }
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (env->query_prop(OBJ_I_HAS_FIRE))
        set_alarm(0.0,0.0,panic_fire);
}
