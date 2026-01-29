/*
 * Tharkadan cave trolls. - Arman 2017
 * Based off the Neraka and Mithas trolls originally coded by                                                      
 * Ashlar, 19 Jul 97                                                                                                                   
 *                                                                            
 */
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Genesis/gems/gem.h"

inherit M_FILE
inherit AUTO_TEAM

int gOkDropLimb = 1;
mixed gArms = -1;
int gRegens = 5;
object *gHunted = ({ });
object gem;
int gHaveSetTrigger = 0;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

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

    set_name("cave troll");    
    set_race_name("troll");
    add_adj("two-headed");

    set_short("two-headed cave troll");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_long("Before you stands a two-headed cave troll, a mutated " +
        "version of his cave troll brethren. Apart from the obvious " +
        "second head, this troll is considerably bulkier and more " +
        "muscular. His mean little eyes glow red with a cunning you " +
        "haven't seen in other cave trolls.\n");

    add_prop(CONT_I_HEIGHT, 195);
    add_prop(CONT_I_WEIGHT, 190000);
    add_prop(CONT_I_VOLUME, 100000);

    /* Trolls can see in the dark */
    add_prop(LIVE_I_SEE_DARK, 10);

    // some vulnerability to fire
    add_prop(OBJ_I_RES_FIRE, -10);

    // some vulnerability to acid
    add_prop(OBJ_I_RES_ACID, -10);

    /* Team with other trolls */
    set_pick_up_team(({"troll"}));

    set_stats(({250,185,200,170,170,180}));
    set_hp(query_max_hp());

    set_all_hitloc_unarmed(50);
    set_all_attack_unarmed(67, 40);

    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 50);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 95); //they smell and listen and ...

    set_alignment(0);
    set_knight_prestige(300);

    set_alarm(0.0,0.0,&command("assist troll"));
}

void
regrow(string limb)
{
    TO->tell_watcher(QCTNAME(TO) + " grows a new " + limb + "!\n");
    gOkDropLimb = 1;
}

void
limb_fall_off(object attacker, string limb)
{
    object o,w;
    int reg_time;

    if (!objectp(attacker) || !gOkDropLimb || gRegens-- <= 0)
        return;

    gOkDropLimb = 0;

    if (limb == "legs")
        limb = ONE_OF(({"left leg","right leg"}));

    attacker->catch_tell("You severed " + TO->query_the_name(attacker) + 
        "'s " + limb + ", which falls to the ground.\n");
    attacker->tell_watcher(QCTNAME(attacker) + " severed " + QTNAME(TO) +
        "'s " + limb + ", which falls to the ground.\n", TO);

    o = clone_object(TOBJ + "troll_limb");
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
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
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
    return 0; // we disable hunting ability

    if(!ob)
        return 0;

    if (!gHaveSetTrigger)
        trig_new("%s 'leaves' / 'rides' / 'sneaks' / 'panics' [and] [flees] [limping] %w",
        "react_leave");
    gHaveSetTrigger = 1;
    if (member_array(ob, gHunted) == -1)
    {
        if(E(ob) == E(TO))
        {
            ob->catch_tell(TO->query_The_name(ob) + " sniffs at you " +
                "and a light glints in his eyes.\n");
            TO->tell_watcher(QCTNAME(TO) + " sniffs at " + QTNAME(ob) +
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
        tell_room(E(TO), QCTNAME(TO) + " screams in rage and fear at " +
            "the sight of a fire.\n", TO);
        // run_away();
    }
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (env->query_prop(OBJ_I_HAS_FIRE))
        set_alarm(0.0,0.0,panic_fire);
}
