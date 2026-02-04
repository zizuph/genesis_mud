/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/weapon";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO      this_object()
#define TP      this_player()
#define ETO     environment(TO)
#define MIN_DUR 1
#define MAX_DUR 2000

public void set_duration(int t);
public void poof();
public void drop_me();

int aid=0;

public void
create_weapon()
{
    add_prop(MYSTIC_WEAPON, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This weapon is just an illusion. It cannot " +
             "be used at all, since try_hit() always returns -1.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"This is a mysterious weapon. You sense something is " +
          "wrong with it.\n", 20,
          "It appears to be an illusion.\n", 40}));
}

public int
try_hit(object target)
{
    object who, where;

    if (random(2) == 0) return -1;
    
    who = TO->query_wielded();
    if (!who) return -1;
    where = environment(who);

    who->catch_msg("You try to hit " + QTNAME(target) + " with your " +
                   TO->short() + ", but you do not manage to control it.\n");
    target->catch_msg(QCTNAME(who) + " tries to hit you with " +
                      who->query_possessive() + " " + TO->short() +
                      ", but " + who->query_pronoun() +
                      "does not manage to control it properly.\n");
    tell_room(where, QCTNAME(who) + " tries to hit " + QTNAME(target) +
              " with " + who->query_possessive() + " " + TO->short() +
              ", but " + who->query_pronoun() +
              "does not manage to control it properly.\n", ({who, target}));
    if (random(5) == 0)
        set_alarm(1.0, -1.0, drop_me);

    return -1;
}

public void
drop_me()
{
    object who = TO->query_wielded();
    
    if (!who) {
        who = ETO;
        if (!who || !living(who)) return;
    } else
        TO->unwield_me();
    
    TO->move(environment(who));
    who->catch_msg("You drop the " + TO->short() + ".\n");
    tell_room(ETO, QCTNAME(who) + " drops " +
              LANG_ADDART(TO->short()) + ".\n");
}

public void
poof()
{
    object who = TO->query_wielded();
    
    if (!who)
        who = ETO;
    else
        TO->unwield_me();
    
    if (living(who)) {
        who->catch_msg("Your " + TO->short() +
                  " vanishes in a blinding flash.\n");
        tell_room(environment(who), QCTNAME(who) + "'s " + TO->short() +
                  " vanishes in a blinding flash.\n", who);
    } else if (who->query_prop(ROOM_I_IS)) {
        tell_room(who, capitalize(LANG_ADDART(TO->short())) +
                  " vanishes in a blinding flash.\n");
    }
    TO->remove_object();
}

void
set_duration(int t)
{
    if (aid) remove_alarm(aid);
    if (t < MIN_DUR) t = MIN_DUR;
    if (t > MAX_DUR) t = MAX_DUR;
    aid = set_alarm(itof(t), -1.0, poof);
}

string
query_recover()
{
    mixed *a;
    
    if (aid) {
        a = get_alarm(aid);
        return MASTER + ":" + TO->query_wep_recover() +
               "##" + ftoi(a[2]) + "##";
    } else
        return "";
}

void
init_recover(string arg)
{
    string foo;
    int tleft;
    
    TO->init_wep_recover(arg);
    sscanf(arg, "%s##%d##", foo, tleft);
    set_duration(tleft);
}

string
stat_object()
{
    mixed *a;
    string str;

    str = ::stat_object();

    if (!aid) return str;
    
    a = get_alarm(aid);
    str += "Time left before destruction: "+ftoi(a[2])+"\n";
    return str;
}
