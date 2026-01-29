/* Ashlar, 19 Jul 97 - A Troll */
/* Modified June 24th by Navarre:
 * improved the stats of the troll to make him a little more
 * challenging and rewarding.
 */
/* Added some vulnerability to fire and acid
 * Arman, July 2016
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit AUTO_TEAM

#define WEP NWEP + "club"
#define DEBUG(x)    (find_player("ashlar")->catch_msg("TROLL: " + x + "\n"))

string *gAdj1 = ({ "huge", "lurking", "snarling", "powerful",
    "large", "big", "muscular" });
string *gAdj2 = ({ "shaggy", "repulsive", "horrid", "snarling",
    "beastly", "frightening", "dangerous" });

int gOkDropLimb = 1;
mixed gArms = -1;
int gRegens = 5;
object *gHunted = ({ });
int gHaveSetTrigger = 0;
object priest1, priest2;


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

    set_name("troll");    
    set_race_name("troll");

    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_long("The " + short() + " is a large humanoid creature, covered " +
        "in thick fur. Long, yellow fangs reach out of his cruel mouth, " +
        "and a foul smell surrounds him. He slowly swings his long arms " +
        "ending in clawed hands while a malicious glint shines in his " +
        "eyes.\n");

    add_prop(CONT_I_HEIGHT, 230);
    add_prop(CONT_I_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 140000);

    /* Trolls can see in the dark 
     * normally 3 was enough but with new
     * guild that creates 15+
     * these trolls can now see in 20.
     */
    add_prop(LIVE_I_SEE_DARK, 20);

    // some vulnerability to fire
    add_prop(OBJ_I_RES_FIRE, -15);

    // some vulnerability to acid
    add_prop(OBJ_I_RES_ACID, -15);

    /* Team with other trolls */
    set_pick_up_team(({"troll", "_new_priest_"}));

    set_stats(({190+random(20),130+random(30),140+random(10),
                110+random(10),110+random(10),130+random(30)}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY, 30);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 100);
    add_prop(LIVE_I_QUICKNESS, 25);
    set_alignment(-100);
    set_knight_prestige(100);

    set_all_hitloc_unarmed(14);
    set_alarm(5.0,0.0,&command("assist troll"));

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

    if(!attacker || !TO)
       return;

    gOkDropLimb = 0;

    if (limb == "legs")
        limb = ONE_OF(({"left leg","right leg"}));

    attacker->catch_msg("You severed " + TO->query_the_name(attacker) + "'s " + limb +
        ", which falls to the ground.\n");
    tell_room(E(TO), capitalize(attacker->query_the_name(TO)) + " severed " + TO->query_the_name(attacker) +
        "'s " + limb + ", which falls to the ground.\n", attacker);

    o = clone_object(NOBJ + "troll_limb");
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
                set_alarm(0.1,0.0,&limb_fall_off(attacker,a[1]));
            break;
    }
    return a;
}

arm_me()
{
    seteuid(getuid(this_object()));

    if (intp(gArms) && (gArms == -1))
    {
        clone_object(WEP)->move(this_object(),1);
    }
    command("wield all");
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
    object* priests = ({});

    ::attacked_by(ob);


    set_alarm(0.5,0.0,&set_hunting(ob));

    // They have vowed to enforce peace in the city
    // So they should not kill the inhabitants.
    // After discussion with the guilds, they agree that they 
    // are enforcing no fighting, and as such it should enforce
    // a little RP in their members. At the same time let us add
    // a little challenge to the larger players.
    if (ob->query_guild_name_occ() == "Priests of Takhisis")
    {
        if(!random(5) && !objectp(priest1) && !objectp(priest2))
        {
            priests = filter(all_inventory(environment(this_object())), &->id("_new_priest_"));
            if(sizeof(priests) == 0)
            { 
                priest1 = clone_object(NNPC+"new_priest");
                priest1->arm_me();
                priest1->move(environment(this_object()), 1);
                tell_room(environment(this_object()), QCTNAME(priest1) +
                          " bursts into the room.\n");

                priest2 = clone_object(NNPC+"new_priest2");
                priest2->arm_me();
                priest2->move(environment(this_object()), 1);
                tell_room(environment(this_object()), QCTNAME(priest2) +
                          " bursts into the room.\n");

                priest1->command("shout A traitor amongst our ranks! You swore " +
                                 "to ensure peace, you betrayer!");
                priest1->command("emote explains: You will now suffer the consequences!");
                priest1->command("kill "+ob->query_real_name());
                priest1->command("kill "+ob->query_real_name());

                priest2->command("kill "+ob->query_real_name());
                priest2->command("kill "+ob->query_real_name());
            }
            else if(sizeof(priests) == 1)
            {
                priest1 = clone_object(NNPC+"new_priest");
                priest1->arm_me();
                priest1->move(environment(this_object()), 1);
                tell_room(environment(this_object()), QCTNAME(priest1) +
                          " bursts into the room.\n");
                priest1->command("shout A traitor amongst our ranks! You swore " +
                                 "to ensure peace, you betrayer!");
                priest1->command("emote explains: You will now suffer the consequences!");
                priest1->command("kill "+ob->query_real_name());
                priest1->command("kill "+ob->query_real_name());

            }               
        }

    }
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
