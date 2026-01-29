/* Cavalry - Knight Layman Guild Shadow, by Morrigan */
/*
 * Revisions :
 *
 *   Lucius, 12.24.1999 - Reorganized and cleaned up *alot*.
 *
 *   Vencar, 20,09,2003 - Copied to cavalry_npc_shadow as the
 *                        guild shadow doesn't go well with npcs.
 *                        Which inherits from the /std/guild/layman base.
 */

inherit "/std/shadow";

#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include "/d/Krynn/open/sys/combat.h"

/*
 * If diverting the attacks of the enemy of the charger to another
 * opponent for the duration of the charge becomes a problem,
 * undefine DIVERT_ATTACKS
 */
#define DIVERT_ATTACKS 1
#define KNIGHT_I_MANEUVERED "_knight_i_maneuvered"

object *enemies = ({});

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Shadow Mask Functions
 */
string *
query_guild_trainer_lay()
{
    return ({ VROOM + "inner_court" });
}

int
query_guild_tax_lay()
{
    return CAVALRY_TAX;
}

string
query_guild_style_lay()
{
    return "fighter";
}

string
query_guild_name_lay()
{
    return "Solamnian Cavalry";
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Mudlib Mask Functions
 */
int
query_not_attack_me(object who, int aid)
{
    object combat_object = who->query_combat_object();
    int attack = combat_object->query_attack(aid);

    if (aid == -1)
        return shadow_who->query_not_attack_me(who, aid);

    if (!shadow_who->query_prop("_kcharge_preparing"))
        return shadow_who->query_not_attack_me(who, aid);

    return 1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Guild Internal Functions
 */
mixed
prop_attack()
{
    object st = shadow_who->query_prop(LIVE_O_STEED);

    if (!st || !shadow_who->query_prop("_kcharge_preparing"))
    {
    if (st)
        st->remove_prop(OBJ_M_NO_ATTACK);
//  shadow_who->remove_prop(OBJ_M_NO_ATTACK);
    return 0;
    }

    return shadow_who->query_The_name(this_player()) +
    " is too far away at the moment.\n";
}

void
remove_maneuver(object st)
{
    st->remove_prop(OBJ_M_NO_ATTACK);
}

void
reset_maneuver(object ob)
{
    ob->remove_prop(KNIGHT_I_MANEUVERED);
    ob->catch_tell("You may try to maneuver your horse out of "+
      "the range of attackers again, if you wish.\n");
}

int
maneuver(string str)
{
    object me = shadow_who, st = me->query_prop(LIVE_O_STEED);
    object *enemies, *tmp;
    int duration, i, lev;

    if (!st)
    {
        NF("You need a mount first!\n");
        return 0;
    }

    if (me->query_prop(KNIGHT_I_MANEUVERED))
    {
        NF("You are unable to do that presently.\n");
        return 0;
    }

    if (!(enemies = st->query_enemy(-1)))
    {
        NF("Your " + st->steed_short() + " is not under attack, "+
          "there is no need.\n");
        return 0;
    }

    lev = me->query_knight_level();
    if (lev > 3)
        lev = 10;
    else if (lev == 3)
        lev = me->query_knight_sublevel();
    else
        lev = (me->query_knight_sublevel() / 2);

    duration = ((me->query_stat(SS_INT) + (lev * 2) +
        me->query_skill(SS_MOUNTED_COMBAT)) / 2);

    if (duration > 100)
        duration = 100;

    if (sizeof(enemies) >= 4)
    {
        me->catch_tell("The onslaught is too overwhelming, you "+
          "cannot possibly save your steed from so many attackers "+
          "at once.\n");

        me->add_prop(KNIGHT_I_MANEUVERED, 1);
        set_alarm(60.0, 0.0, &reset_maneuver(me));
        return 1;
    }

    if ((duration - (sizeof(enemies) * 25)) <= 0)
    {
        me->catch_tell("You fail to maneuver your steed safely out "+
          "of harm's way.\n");
        me->add_prop(KNIGHT_I_MANEUVERED, 1);
        set_alarm(60.0, 0.0, &reset_maneuver(me));
        return 1;
    }

    duration = (duration - (sizeof(enemies) * 20) + 20);

    me->add_prop(KNIGHT_I_MANEUVERED, 1);
    st->add_prop(OBJ_M_NO_ATTACK, "As you move to attack the "+
      st->steed_short() + ", " + QTNAME(me) + " whirls the steed "+
      "around to face you.\n");
    me->catch_tell("Recalling your training of mounted combat, you "+
      "spur your " + st->steed_short() + " forward and whirl " +
      POSSESSIVE(st) + " around to face " + POSSESSIVE(st) +
      " assailents.\n");

    tmp = enemies;
    tmp += ({ me });
    tell_room(E(me), QCTNAME(me) + " spurs " + POSSESSIVE(me) + " " +
      st->steed_short() + " forward and whirls around, facing " +
      POSSESSIVE(me) + " assailants head on.\n", tmp);

    i = sizeof(enemies);
    while( i-- )
    {
        enemies[i]->stop_fight(st);
        st->stop_fight(enemies[i]);
        enemies[i]->attack_object(me);
        enemies[i]->catch_tell(me->query_The_name(enemies[i]) +
          " spurs " + POSSESSIVE(me) + " " + st->steed_short() +
          " forward and whirls around, facing you head on.\n");
    }

    set_alarm(60.0, 0.0, &reset_maneuver(me));
    set_alarm(itof(duration), 0.0, &remove_maneuver(st));
    return 1;
}

varargs void
sever_limb(string piece, string killed, object killer)
{
    object corpse, part, me = shadow_who;
    string *str, *message, tmp;
    int i;

    corpse = P("corpse", E(me));
    if (corpse->query_npc())
        corpse = 0;

    if (!corpse)
        return;

    // query_short might return function pointer causing runtime
    if (!stringp(corpse->query_short()))
    return;

    if (piece == "body")
        piece = "head";

    setuid(); seteuid(getuid());

    switch(piece)
    {
    case "head":
        corpse->set_short("headless "+corpse->query_short());
        corpse->remove_leftover("scalp");
        corpse->remove_leftover("skull");
        part = clone_object("/std/leftover");
        part->leftover_init("head", corpse->query_prop(CORPSE_S_RACE));
        part->move(E(corpse));
        break;
    case "legs":
        corpse->set_short("legless "+corpse->query_short());
        corpse->remove_leftover("thighbone");
        part = clone_object("/std/leftover");
        part->leftover_init("leg", corpse->query_prop(CORPSE_S_RACE));
        part->move(E(corpse));
        break;
    case "right arm":
        corpse->set_short("armless "+corpse->query_short());
        part = clone_object("/std/leftover");
        part->leftover_init("arm", corpse->query_prop(CORPSE_S_RACE));
        part->move(E(corpse));
        break;
    case "left arm":
        corpse->set_short("armless "+corpse->query_short());
        part = clone_object("/std/leftover");
        part->leftover_init("arm", corpse->query_prop(CORPSE_S_RACE));
        part->move(E(corpse));
        break;
    }
}

object *
query_kweapon(object liv)
{
    object left, right, medal, *tmp;
    int one, two, pr, skill, lvl, slvl, j, i = random(100) + 1;

    tmp = liv->query_weapon(-1);
    j   = sizeof(tmp);

    if (!tmp || !sizeof(tmp))
        return ({ 0 });
    else if (j < 2)
        return ({ tmp[0] });

    medal = P("pal_med", shadow_who);
    skill = liv->query_skill(SS_2H_COMBAT);
    lvl   = liv->query_knight_level();
    slvl  = liv->query_knight_sublevel();

    if (lvl == 2)
        j = (skill + (2 * (slvl - random(slvl))));
    else if (lvl == 3)
        j = (skill + (3 * (slvl - random(slvl))));
    else if (lvl > 3)
    {
        if (slvl < 10)
            j = skill + 30 - random(10);
        else
            j = (skill + (3 * (slvl - random(slvl))));
    }

    left  = liv->query_weapon(W_LEFT);
    right = liv->query_weapon(W_RIGHT);
    pr    = medal->query_primary();

    if (pr == 2)
    {
        if (random(2))
            tmp = ({ right, left, });
        else
            tmp = ({ left, right, });
    }
    else if (pr == 1)
        tmp = ({ left, right, });
    else
    {
        one = ((right->query_hit() + right->query_pen()) / 2);
        two = ((left->query_hit() + left->query_pen()) / 2);

        if (one >= two)
            tmp = ({ right, left, });
        else
            tmp = ({ left, right, });
    }

    if (i < j)
        return tmp;
    else
        return ({ tmp[1], tmp[0], });
}

void
reset_charge_special(object liv)
{
    liv->catch_tell("\nYour steed is ready to charge again.\n\n");
    liv->remove_prop("_kcharge_resetting");
    liv->remove_prop(OBJ_M_NO_ATTACK);
}

void
check_enemies(object liv)
{
#ifdef DIVERT_ATTACKS
    int i;

    if (sizeof(enemies))
    {
        enemies = filter(enemies -= ({ 0 }),
            &operator(==)(environment(liv)) @ environment);
    }

    if (i = sizeof(enemies))
    {
        liv->catch_tell("As you return to the battle, "+
          COMPOSITE_LIVE(enemies) + (i > 1 ? " turn " : " turns ")+
          "back to face you.\n");

        enemies->catch_msg("As "+ QTNAME(liv) +" returns to the "+
            "battle, you turn to face "+ OBJECTIVE(liv) +" again.\n");

        tell_room(E(liv), "As "+ QTNAME(liv) +" returns to the battle, "+
             COMPOSITE_LIVE(enemies) + (i > 1 ? " turn " : " turns ")+
             "to face "+ OBJECTIVE(liv) +" again.\n", enemies + ({ liv }));

        enemies->attack_object(liv);
    }
#endif DIVERT_ATTACKS
}

void
do_charge_special(object ob, object liv, object horse)
{
    mixed hitresult;
    object weapon;
    int hres, wstat, wmod, smod, lmod, skill, pen, thit, i;
    string tar, att, aud, rcry, hdesc, str;

    liv->remove_stun();

    if (!P(ob, E(liv)) || liv->query_prop(LIVE_O_STEED) != horse)
    {
        liv->catch_tell("You are unable to charge your target.\n");
        liv->remove_prop("_kcharge_preparing");
        check_enemies(liv);
        return;
    }

    if (!(weapon = query_kweapon(liv)[0]))
    {
        liv->catch_tell("Congratulations, you charged into battle "+
          "without a weapon!\n");
        liv->remove_prop("_kcharge_preparing");

        check_enemies(liv);
        return;
    }

    switch(liv->query_knight_level())
    {
    case 5..4:
        if (liv->query_knight_sublevel() == 11)
            lmod = 11;
        else
            lmod = 10;
        break;
    case 3: lmod = liv->query_knight_sublevel(); break;
    case 2..1: lmod = (liv->query_knight_sublevel() / 2); break;
    default: lmod = 0; break;
    }

    wstat = ((weapon->query_hit() + weapon->query_pen()) / 2);
    smod  = (((liv->query_stat(SS_STR) * 2) + liv->query_stat(SS_WIS) +
        liv->query_stat(SS_DIS)) / 4);

    smod = MIN(120, smod);

    if (weapon->query_wt() == W_POLEARM)
        wmod = (weapon->query_pen() * 3) / 2;
    else
        wmod = ((wstat * 10) / 8);

    skill = (liv->query_skill(SS_MOUNTED_COMBAT) + 25);
    pen   = ((((smod/2) + wmod) / 2) + (lmod * 2) + 20);
    hres  = F_PENMOD(pen, skill);

    thit  = MAX(65, MIN(100, wmod + (lmod * 2) +
        ((liv->query_skill(SS_MOUNTED_COMBAT) - 15) / 3)));

    if ((liv->query_combat_object())->cb_tohit(-1, thit, ob) != 1)
        hitresult = ob->hit_me(0, weapon->query_dt(), liv, -1);
    else
        hitresult = ob->hit_me(hres, weapon->query_dt(), liv, -1);

    liv->attack_object(ob);
    hdesc = hitresult[1];

    if (!random(3) &&
      hitresult[0] >= 20 &&
      !liv->query_prop("_i_quiet_knight"))
    {
        switch( random(10) )
        {
        case 0: rcry = "For Vingaard and the Orders!"; break;
        case 1:
            switch( liv->query_knight_level() )
            {
            case 5: rcry = "For the Order of the Rose!";  break;
            case 4: rcry = "For the Order of the Sword!"; break;
            case 3: rcry = "For the Order of the Crown!"; break;
            default: rcry = "For the Knighthood!"; break;
            }
            break;
        case 2:
            switch(liv->query_knight_level())
            {
            case 4: rcry = "Kiri-Jolith!"; break;
            case 3: rcry = "Habbakuk!";    break;
            default: rcry = "Paladine!";   break;
            }
            break;
        case 3: rcry = "By the Measure!"; break;
        case 4: rcry = "For Vingaard!";   break;
        case 5: rcry = "By the Oath and the Measure!"; break;
        case 6: rcry = "Victory to the Knighthood!";   break;
        case 7: rcry = "For Solamnia!"; break;
        case 8: rcry = "For the Knighthood!"; break;
        case 9:
            switch(liv->query_knight_level())
            {
            case 5:  rcry = "In the name of justice!";  break;
            case 4:  rcry = "In the name of courage!";  break;
            case 3:  rcry = "In the name of honour!";   break;
            default: rcry = "In the name of Solamnia!"; break;
            }
            break;
        }
        liv->command("$shout "+ rcry);
    }

    if (hitresult[0] > 0 &&
      ob->query_prop(LIVE_I_NO_BODY) &&
      !weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
        liv->add_prop("_kcharge_resetting", time());
        liv->remove_prop("_kcharge_preparing");
        set_alarm(60.0, 0.0, &reset_charge_special(liv));

        liv->catch_tell("Your "+ weapon->short() +" passes through "+
          ob->query_the_name(liv) +", leaving "+ OBJECTIVE(ob) +
      " unharmed.\n");
        ob->catch_tell(liv->query_The_name(ob) +"'s "+ weapon->short()+
          " passes through you, leaving you unharmed.\n");
        liv->tell_watcher(QCTNAME(liv)+"'s "+weapon->short()+" passes "+
          "through "+ QTNAME(ob) +", leaving "+
          OBJECTIVE(ob) +" unharmed.\n");

        check_enemies(liv);
        return;
    }

    liv->remove_prop("_kcharge_preparing");
    liv->catch_msg("   DAMAGE -- "+hitresult[3]+"\n");
    liv->add_prop("_kcharge_resetting", time());

    set_alarm(60.0, 0.0, &reset_charge_special(liv));

    if (ob->query_hp() < 1)
    {
        switch( weapon->query_wt() )
        {
        case W_SWORD:   str = "severs";       break;
        case W_AXE:     str = "cleaves";      break;
        case W_KNIFE:   str = "slices into "; break;
        case W_POLEARM: str = "impales";      break;
        default:        str = "crushes";      break;
        }

        if (weapon->query_wt() == W_AXE || weapon->query_wt() == W_SWORD)
        {
            liv->catch_tell("The thundering crescendo of your "+
              horse->steed_short() +" reaches its peak as you collide "+
              "with "+ ob->query_the_name(liv) +" in a deafening "+
              "explosion of sound. Aided by your tremendous momentum, "+
              "your "+ weapon->short()+ " "+ str +" "+
              ob->query_the_name(liv) +"'s "+ (hdesc == "body" ? "head" :
                hdesc) + " from "+ POSSESSIVE(ob) +" body.\n");

            ob->catch_tell("The thundering crescendo of "+
              liv->query_the_name(ob) +"'s "+ horse->steed_short()+
              " reaches its peak as "+ PRONOUN(liv)+" collides with "+
              "you in a deafening explosion of sound. Aided by "+
              POSSESSIVE(liv) +" tremendous momentum, "+POSSESSIVE(liv)+
              " " +weapon->short() +" "+ str +" your " +
              (hdesc == "body" ? "head" : hdesc)+ " from your body.\n");

            liv->tell_watcher("The thundering crescendo of "+
              QTNAME(liv) +"'s "+ horse->steed_short() +" reaches its "+
              "peak as "+ PRONOUN(liv) +" collides with "+ QTNAME(ob)+
              "in a deafening explosion of sound. Aided by "+
              POSSESSIVE(liv)+" tremendous momentum, "+ POSSESSIVE(liv)+
              " "+ weapon->short() +" "+ str +" "+ QTNAME(ob) +"'s "+
              (hdesc == "body" ? "head" : hdesc) +" from "+
              POSSESSIVE(ob) +" body.\n", ob);

            ob->do_die(liv);
            sever_limb(hdesc, ob->query_real_name(), liv);
            check_enemies(liv);
            return;
        }
        else
        {
            liv->catch_tell("The thundering crescendo of your "+
              horse->steed_short()+" reaches its peak as you collide "+
              "with "+ ob->query_the_name(liv) +" in a deafening "+
              "explosion of sound. Aided by your tremendous momentum, "+
              "your "+ weapon->short() +" "+ str +" "+
              ob->query_the_name(liv) +"'s "+ hdesc +".\n");

            ob->catch_tell("The thundering crescendo of "+
              liv->query_the_name(ob) +"'s "+ horse->steed_short()+
              " reaches its peak as "+ PRONOUN(liv) +" collides with "+
              "you in a deafening explosion of sound. Aided by "+
              POSSESSIVE(liv) +" tremendous momentum, "+
              POSSESSIVE(liv) +" "+ weapon->short() +" "+ str+
              " your "+ hdesc +".\n");

            liv->tell_watcher("The thundering crescendo of "+
              QTNAME(liv) +"'s "+ horse->steed_short() +" reaches its "+
              "peak as "+ PRONOUN(liv) +" collides with "+ QTNAME(ob)+
              "in a deafening explosion of sound. Aided by "+
              POSSESSIVE(liv)+" tremendous momentum, "+ POSSESSIVE(liv)+
              " "+ weapon->short() +" "+ str +" "+ QTNAME(ob) +"'s "+
              hdesc+".\n", ob);

            ob->do_die(liv);
            sever_limb(hdesc, ob->query_real_name(), liv);
            check_enemies(liv);
            return;
        }
    }

    str  = horse->steed_short();
    rcry = weapon->short();

    switch( hitresult[0] )
    {
    case 0:
        att = "Your attempt to strike "+ ob->query_the_name(liv)+
        " with your "+ rcry +" misses. You tug on the "+
        "reins of your "+ str +", turning to face your foe.";

        tar = liv->query_The_name() +"'s attempt to strike you with "+
        POSSESSIVE(liv) +" "+ rcry +" misses. "+
        C(PRONOUN(liv)) +" tugs on the reins of "+ POSSESSIVE(liv)+
        " "+ str +", turning to face you.";

        aud = QCTNAME(liv) +"'s attempt to strike "+ QTNAME(ob)+
        " with "+POSSESSIVE(liv) +" "+ rcry +" misses. "+
        C(PRONOUN(liv)) +" tugs on the reins of "+ POSSESSIVE(liv)+
        " "+ str +", turning to face "+ QTNAME(ob) +".";
        break;
    case 1..5:
        att = "As your "+ str +" bears down upon "+
        ob->query_the_name(liv)+ ", you strike "+
        POSSESSIVE(ob) +" "+ hdesc +" with a glancing blow from "+
        "your "+ rcry +".";

        tar = "As "+ POSSESSIVE(liv) +" "+ str +" bears down upon you, "+
        liv->query_the_name(ob) +" strikes your "+ hdesc +" with a "+
        "glancing blow from "+ POSSESSIVE(liv) +" "+ rcry +".";

        aud = "As "+ POSSESSIVE(liv) +" "+ str +" bears down upon "+
        QTNAME(ob) +", "+ QTNAME(liv) +" strikes "+ POSSESSIVE(ob)+
        " "+ hdesc +" with a glancing blow from "+ POSSESSIVE(liv)+
        " "+ rcry +".";
        break;
    case 6..20:
        att = "The rumbling of the ground beneath your "+ str +
        "'s feet nearly drowns out the sound of the impact as you "+
        "score a moderate hit on the "+ hdesc +" of "+
        ob->query_the_name(liv) +" with your "+ rcry +".";

        tar = "The rumbling of the ground beneath your feet nearly "+
        "drowns out the sound of the impact as "+
        liv->query_the_name(ob) +" scores a moderate hit on your "+
        hdesc +" with "+ POSSESSIVE(ob) +" "+ rcry +".";

        aud = "The rumbling of the ground beneath your feet nearly "+
        "drowns out the sound of the impact as "+ QTNAME(liv)+
        " scores a moderate hit on the "+ hdesc +" of "+
        QTNAME(ob) +" with "+ POSSESSIVE(liv) +" "+ rcry +".";
        break;
    case 21..35:
        att = "Weapon meets foe as you heavily wound "+
        ob->query_the_name(liv) +"'s "+ hdesc +" with your "+
        rcry +", the momentum of your "+ str +" lending its "+
        "strength to the blow.";

        tar = liv->query_The_name(ob) +" heavily wounds your "+ hdesc
        +" with "+ POSSESSIVE(liv) + " "+ rcry +", the momentum "+
        "of "+POSSESSIVE(liv) +" "+ str +" lending its strength "+
        "to the blow.";

        aud = QCTNAME(liv) +" heavily wounds "+ QTNAME(ob) +"'s "+ hdesc+
        " with "+ POSSESSIVE(liv) +" "+ rcry +" as the two collide, "+
        "the momentum of "+ QTNAME(liv) +"'s "+ str +" lending its "+
        "strength to the blow.";
        break;
    case 36..50:
        att = "Your "+ str +" charges by "+ ob->query_the_name(liv)+
        ", and you land a perfectly placed blow on "+ POSSESSIVE(ob)+
        " "+ hdesc +" with your "+ rcry +", wounding "+ OBJECTIVE(ob)+
        " badly.";
        tar = liv->query_The_name(ob) +"'s "+ str +" charges by you, "+
        "and "+ PRONOUN(liv) +" lands a perfectly placed blow on "+
        "your "+ hdesc +" with "+ POSSESSIVE(liv) +" "+ rcry +
        ", wounding you badly.";

        aud = QCTNAME(liv) +"'s "+ str +" charges by "+ QTNAME(ob) +", "+
        "and "+ PRONOUN(liv) +" lands a perfectly placed blow on "+
        QTNAME(ob) +"'s "+ hdesc +" with "+ POSSESSIVE(liv) +" "+
        rcry +", wounding "+ OBJECTIVE(ob) +" badly.";
        break;
    case 51..100:
        att = "Your thundering "+ str +" reaches "+
        ob->query_the_name(liv)+ ", and your "+ rcry +" smashes "+
        "into "+ POSSESSIVE(ob) +" "+ hdesc +" with a tremendous "+
        "thud and devastating power.";

        tar = liv->query_The_name(ob) +"'s thundering "+ str +" reaches "+
        "you, and "+ POSSESSIVE(liv) +" "+ rcry +" smashes into your "+
        hdesc +" with a tremendous thud and devastating power.";

        aud = QCTNAME(liv) +"'s thundering "+ str +" reaches "+ QTNAME(ob)+
        ", and "+ POSSESSIVE(liv) +" "+ rcry +" smashes into "+
        POSSESSIVE(ob) +" "+ hdesc +" with a tremendous thud and "+
        "devastating power.";
        break;
    }

    liv->catch_tell( att +"\n");
    ob->catch_tell( tar +"\n");
    liv->tell_watcher( aud +"\n", ob);
    check_enemies(liv);
}

void
do_charge_prespecial2(object ob, object me, object horse)
{
    if (!P(ob, E(me)) || me->query_prop(LIVE_O_STEED) != horse)
    {
        me->catch_tell("You are unable to charge your target.\n");
        me->remove_prop("_kcharge_preparing");
        me->remove_stun();
        check_enemies(me);
        return;
    }

    set_alarm(3.0, 0.0, &do_charge_special(ob, me, horse));

    me->catch_tell("You lean forward in the saddle as your "+
      horse->steed_short()+ " thunders toward "+
      ob->query_the_name(me)+". Preparing yourself for the impact, "+
      "you shout out a Solamnic battlecry, barely audible over "+
      "the earth-shaking rumble of your steed!\n");

    ob->catch_tell("The ground beneath your feet rumbles as "+
      me->query_the_name(ob) +" thunders toward you, astride "+
      POSSESSIVE(me) +" "+ horse->steed_short() +"! You feel fear "+
      "creep over you as "+ PRONOUN(me)+ " shouts out a "+
      "Solamnic battlecry.\n");

    me->tell_watcher("The ground rumbles beneath your feet as "+
      QTNAME(me) +" thunders toward "+ QTNAME(ob) +", astride "+
      POSSESSIVE(me) +" "+ horse->steed_short() +". Leaning forward "+
      "in the saddle, "+ QTNAME(me) +" shouts "+
      "out a Solamnic battlecry!\n", ({ ob, me }));
}

void
do_charge_prespecial1(object ob, object me, object horse)
{
    if (!P(ob, E(me)) || me->query_prop(LIVE_O_STEED) != horse)
    {
        me->catch_tell("You are unable to charge your target.\n");
        me->remove_prop("_kcharge_preparing");
        me->remove_stun();
        check_enemies(me);
        return;
    }

    set_alarm(3.0, 0.0, &do_charge_prespecial2(ob, me, horse));

    me->catch_tell("Your adrenaline begins to surge as you slap "+
      "the reins back and forth as your "+ horse->steed_short()+
      " gains momentum.\n");

    ob->catch_tell(me->query_The_name(ob) +" slaps the reins "+
      "back and forth as "+ POSSESSIVE(me) +" "+ horse->steed_short()+
      " gains momentum.\n");

    me->tell_watcher(QCTNAME(me)+" slaps the reins back and forth as "+
      POSSESSIVE(me)+" "+horse->steed_short()+" gains momentum.\n",
      ({ ob, me }));
}

void
do_charge_engaged_prespecial1(object ob, object me, object horse)
{
    int i;
    object tmp;

    if (!P(ob, E(me)) || me->query_prop(LIVE_O_STEED) != horse)
    {
        me->catch_tell("You are unable to charge your target.\n");
        me->remove_prop("_kcharge_preparing");
        me->remove_stun();
        check_enemies(me);
        return;
    }

    set_alarm(4.0, 0.0, &do_charge_special(ob, me, horse));
    tmp = ob->query_attack();

    if (tmp && sizeof(enemies) == 1)
    {
        me->catch_tell("You turn back to face the battle, noticing "+
          "that your enemy, "+ ob->query_the_name(me) +", has "+
          "engaged "+ tmp->query_the_name(me) +
          ". You pause briefly before digging your heels into "+
          "your "+ horse->steed_short() +", sending the great steed "+
          "charging back toward your enemy!\n");
    }
    else if (tmp && sizeof(enemies) > 1)
    {
        me->catch_tell("You turn back to face the battle and, to your "+
          "dismay, see that your enemies have turned to attack "+
          "others. You pause briefly before digging your heels into "+
          "your "+ horse->steed_short() +", sending the great steed "+
          "charging back toward "+ ob->query_the_name(me) +"!\n");
    }
    else
    {
        me->catch_tell("You turn back to face the battle, pausing "+
          "briefly before digging your heels into your "+
          horse->steed_short() +", sending the great steed charging "+
          "back toward "+ ob->query_the_name(me) +"!\n");
     }

    ob->catch_tell(me->query_The_name(ob) +" turns back to face "+
      "the battle, pausing briefly before digging "+
      POSSESSIVE(me) +" heels into the "+ horse->steed_short()+
      ", which begins charging toward you at alarming speed!\n");

    tell_room(E(me), QCTNAME(me) +" turns back to face the battle, "+
      "pausing briefly before digging "+ POSSESSIVE(me)+
      " heels into the "+ horse->steed_short() +", which begins "+
      "charging toward "+ QTNAME(ob) +" at great speed!\n",
      ({ ob, me }));
}

int
charge_special(object str)
{
    object weapon, *enemy_list, ob, medal, horse;
    int i, j;
    mixed tmp;

    medal = P("pal_med", shadow_who);
    horse = shadow_who->query_prop(LIVE_O_STEED);

    if (!str)
    {
        ob = shadow_who->query_attack();
    }
    else
    {
        ob = str;
    }

    if (E(shadow_who)->query_prop(ROOM_I_INSIDE))
    {
        NF("There is not enough room to maneuver your horse "+
          "to charge indoors.\n");
        return 0;
    }

    if (tmp = shadow_who->query_prop("_kcharge_resetting"))
    {
        /* Safeguard to fix locked special attacks */
        if (time() > (tmp + 60))
        {
            set_alarm(60.0, 0.0, &reset_charge_special(shadow_who));
        }

        NF("You are not ready to charge again.\n");
        return 0;
    }

    if (shadow_who->query_prop(LIVE_I_ATTACK_DELAY) ||
      shadow_who->query_prop(LIVE_I_STUNNED))
    {
        NF("You are too stunned to charge.\n");
        return 0;
    }

    if (shadow_who->query_prop("_kspecial_preparing"))
    {
        NF("You are focusing on a different sort of attack already.\n");
        return 0;
    }

    if (tmp = shadow_who->query_prop("_kcharge_preparing"))
    {
        /* Safeguard to fix locked special attacks */
        if (time() > (tmp + 20))
        {
            shadow_who->remove_prop("_kcharge_preparing");
            shadow_who->add_prop("_kcharge_resetting",time());
            set_alarm(60.0,0.0, &reset_charge_special(shadow_who));
            NF("You are not ready to charge again.\n");
        }
        else
        {
            NF("You are already preparing to charge.\n");
        }
        return 0;
    }

    if (!(weapon = query_kweapon(shadow_who)[0]))
    {
        NF("You cannot charge without a weapon.\n");
        return 0;
    }

    tmp = horse->steed_short();
    horse->add_prop(OBJ_M_NO_ATTACK, C(tmp) + " is too far away.\n");
    shadow_who->add_prop(OBJ_M_NO_ATTACK, &prop_attack());
    shadow_who->add_prop("_kcharge_preparing", time());
    shadow_who->add_stun();

    if (shadow_who->query_attack() == ob)
    {
        set_alarm(4.0, 0.0,
          &do_charge_engaged_prespecial1(ob, shadow_who, horse));

        tell_object(shadow_who, "You gallop away from the battle "+
          "astride your "+ tmp +", putting some distance between "+
          "yourself and the battle.\n");

        tell_room(E(shadow_who), QCTNAME(shadow_who) +" gallops away "+
          "from the battle astride "+ POSSESSIVE(shadow_who) +" "+
          tmp +", putting some distance between "+
          OBJECTIVE(shadow_who) +"self and the battle.\n",
          ({ ob, shadow_who }));

        tell_object(ob, shadow_who->query_The_name(ob) +" gallops away "+
          "from the battle astride "+ POSSESSIVE(shadow_who) +
          " "+ tmp +", putting some distance between "+
          OBJECTIVE(shadow_who) +"self and the battle.\n");
    }
    else
    {
        set_alarm(3.0, 0.0, &do_charge_prespecial1(ob, shadow_who, horse));

        tell_object(shadow_who, "You salute "+
          ob->query_the_name(shadow_who)+ " in the traditional "+
          "Solamnic manner with your "+ weapon->short() +", then "+
          "spur your "+ tmp +" forward, snapping the reins.\n");

        tell_room(E(shadow_who), QCTNAME(shadow_who) +" salutes "+
          QTNAME(ob) +" in the traditional Solamnic manner with "+
          POSSESSIVE(shadow_who) +" "+ weapon->short() +", then "+
          "spurs "+ POSSESSIVE(shadow_who) +" "+ tmp +" forwards, "+
          "snapping the reins.\n", ({ ob, shadow_who }));

        tell_object(ob, shadow_who->query_The_name(ob) +" salutes you "+
          "in the traditional Solamnic manner with "+
          POSSESSIVE(shadow_who) +" "+ weapon->short() +", then "+
          "spurs "+ POSSESSIVE(shadow_who) +" "+ tmp +" forwards, "+
          "snapping the reins.\n");
    }

#ifdef DIVERT_ATTACKS
    /* Redirection of enemies attacks when Knight charges away */
    enemy_list = ({}); enemies = ({}); tmp = ({});

    tmp = shadow_who->query_enemy(-1);
    tmp = filter(tmp, &operator(==)(environment(shadow_who)) @ environment);

    if (i = sizeof(tmp))
    {
        while( i-- )
        {
            if (tmp[i]->query_attack() == shadow_who)
                enemies += ({ tmp[i] });
        }

        enemies->stop_fight(shadow_who);
        shadow_who->stop_fight(enemies);

        tmp = 0;
        i = sizeof(enemies);
        while( i-- )
        {
            enemy_list = enemies[i]->query_enemy(-1);
            enemy_list = filter(enemy_list,
              &operator(==)(environment(enemies[i])) @ environment);

            if (!(j = sizeof(enemy_list)))
                continue;

            if (!(tmp = enemy_list[random(j)]))
                continue;

            tell_object(tmp, "As "+ shadow_who->query_the_name(tmp) +
              " charges away from battle, "+
              enemies[i]->query_the_name(tmp) +
              " turns to attack you!\n");

            tell_room(E(shadow_who), "As "+ QTNAME(shadow_who) +
              " charges away from battle, "+ QTNAME(enemies[i]) +
              " turns to attack "+ QTNAME(tmp) +".\n",
              ({ tmp, enemies[i], shadow_who }));

            tell_object(enemies[i], "As your foe charges off the "+
              "battlefield, you turn to attack "+
              tmp->query_the_name(enemies[i]) +".\n");

            enemies[i]->attack_object(tmp);
        }
    }
#endif DIVERT_ATTACKS
    return 1;
}
