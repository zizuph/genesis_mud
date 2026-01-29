//
// whip.c
/*      Updates
 *       Zizuph, 2021-12-25:
 *         Turn into a spell enhancer, power 44.
 */
//

inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

#define HIM_HER(o)  o->query_objective()
#define HE_SHE(o)   o->query_pronoun()
#define HIS_HER(o)  o->query_possessive()

string my_short();
string my_long();

create_weapon()
{
    set_name("whip");
    set_short(my_short);
    set_long(my_long);
    add_prop(OBJ_I_VALUE, 1034);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT,  400);

    wep_wt = SS_WEP_CLUB;
    set_dt(W_SLASH);
    set_hit(65);
    set_pen(60);


    set_wf(this_object());
    set_hands(W_ANYH);
    
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(50);   
}

int
query_aflame()
{
    return living(wielder) && wielder->query_race_name() == "balrog";
}

int
query_hit()
{
    return query_aflame() ? 100: 40;
}

int
query_pen()
{
    return query_aflame() ? 60 : 20;
}

string
my_short()
{
    if (query_aflame())
        return "flaming whip";
    else
        return "awesome whip";
}

string
my_long()
{
    return "The Balrog's " + my_short() + ".\n";
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object tp;
    string whip;

    tp = this_object()->query_wielded();
    whip = my_short();

    if (enemy->query_hp() <= 0)
    {
        tp->catch_msg(QCTNAME(enemy) + " screams in pain as the terrible flick of your " +
        whip + " flails " + HIS_HER(enemy) + " " + hdesc + " severely!\n");
        enemy->catch_msg("You scream in pain as " + QTPNAME(enemy) + " terrible " + whip +
        "flails your " + hdesc + " severely!\n");
        tp->tell_watcher(QCTNAME(enemy) + " screams in pain as the terrible flick of " +
        QTPNAME(tp) + " " + whip + " flails " + HIM_HER(enemy) + " severely!\n", enemy);
        enemy->do_die(tp);
    }
    else
    {
        switch (phurt)
    {
        case -1:
            case -2:
        tp->catch_msg("You snap your " + whip + " towards " + QTNAME(enemy) +
                  ", but it whistles above " + HIS_HER(enemy) + " head.\n");
        enemy->catch_msg(QCTNAME(tp)+" snaps " + HIS_HER(tp) + " " + whip +
                 " towards you, but it whistles above your head.\n");
        tp->tell_watcher_miss(QCTNAME(tp)+" snaps " + HIS_HER(tp) + " " + whip +
                      " towards " + QTNAME(enemy) + ", but it whistles above " +
                      HIS_HER(tp) + " head.\n", enemy);
        break;
        case 0:
        tp->catch_msg("You whip " + QTPNAME(enemy) + " " + hdesc + ", but the " +
                  whip + " does not harm " + HIM_HER(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " whips your " + hdesc + ", but the " +
                 whip + " does not harm you.\n");
        tp->tell_watcher(QCTNAME(tp) + " whips " + QTPNAME(enemy) + " " + hdesc +
                 ", but the " + whip + " does not harm " + HIM_HER(enemy) + ".\n", enemy);
        break;
        case 1..20:
        tp->catch_msg("You snap your " + whip + " against " + QTNAME(enemy) + ", " +
                  "grazing " + HIS_HER(enemy) + " " + hdesc + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " snaps " + HIS_HER(tp) + " " + whip + " against " +
                 "you, grazing your " + hdesc + ".\n");
        tp->tell_watcher(QCTNAME(tp) + " snaps " + HIS_HER(tp) + " " + whip + " against " +
                 QTNAME(enemy) + ", grazing " + HIS_HER(enemy) + " " + hdesc + ".\n", enemy);
        break;
        case 21..40:
        tp->catch_msg("Your " + whip + " lashes against " + QTPNAME(enemy) + " " + hdesc +
                  ", hurting " + HIM_HER(enemy) + " with a sharp cracking sound.\n");
        enemy->catch_msg(QCTPNAME(tp) + " " + whip + " lashes against your " + hdesc +
                 ", hurting you with a sharp cracking sound.\n");
        tp->tell_watcher(QCTPNAME(tp) + " " + whip + " lashes against " + QTPNAME(enemy) +
                 " " + hdesc + ", hurting " + HIM_HER(enemy) +
                 " with a sharp cracking sound.\n", enemy);
        break;
        case 41..60:
        tp->catch_msg("You flog " + QTNAME(enemy) + " as your " + whip + " delivers a " +
                  "painful blow to " + HIS_HER(enemy) + " " + hdesc + ".\n");
        enemy->catch_msg(QCTNAME(tp) + " flogs you as " + HIS_HER(tp) + " " +
                 whip + " delivers a painful blow to your " + hdesc + ".\n");
        tp->tell_watcher(QCTNAME(tp) + " flogs " + QTNAME(enemy) + " as " + HIS_HER(tp) + " " +
                 whip + " delivers a painful blow to " + QTPNAME(enemy) + " " + hdesc + ".\n",
                 enemy);
        break;
        default:
        case 61..100:
        tp->catch_msg("A loud crack pierces the air as your " + whip +
                  " smacks " + QTPNAME(enemy) + " " + hdesc + ", causing intense pain!\n");
        enemy->catch_msg("A loud crack pierces the air as " + QTPNAME(tp) + " " + whip +
                 " smacks your " + hdesc + ", causing intense pain!\n");
        tp->tell_watcher("A loud crack pierces the air as " + QTPNAME(tp) + " " + whip +
                 "smacks " + QTPNAME(enemy) + " " + hdesc + ", causing intense pain!\n",
                 enemy);
        break;
    }
    }

#if 0
    {
    int time;
#define FUMBLE(who, time, call, obj) \
    (MORIA_DIR + "skills/fumble")->add_fumble_call(who, time, call, obj)

    // If the attack is targeted against the legs, there is a chance of being
    // fumbled.

    if (!sizeof(enemy->query_prop(LIVE_AS_ATTACK_FUMBLE)) &&
        hdesc == "legs" && (time = random(phit) - random(100) -50) > 0)
    {
        tellem(tp, enemy, "$N's "+QSHORT(TO)+" snatches around #n's " +
           (random(2)?"left":"right") + " leg!\n" +
           "#N #stumble and #fall down on the " +
           (ENV(enemy)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
           "!\n");
        FIXEUID;
        if (query_aflame()) {
        if (time > 300)
            time = 300;
        } else if (time > 150)
        time = 150;
        FUMBLE(enemy, time/10, "fumble_message", TO);
    }
    }
#endif
    return 1;
}

#if 0
mixed
fumble_message(object who, int last)
{
    if (last) {
    tellem(who, 0, "$N $manage to get on $p feet again!\n");
    return;
    }

    tell_room(ENV(who),
    QCTNAME(who) + " struggles while trying to get onto " +
    HIS_HER(who) + " feet again.\n", who);

    return "You struggle while trying to get onto your feet again.\n";
}
#endif

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
