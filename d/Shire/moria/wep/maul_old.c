/*  -*- LPC -*-  */

/*
 * maul.c - Bolg's Maul.
 *
 * This is a giant Maul of Shield and Armour-slaying. It is a
 * black alloyed spiked mace/hammer that strikes as a war
 * mattock, and delivers crush criticals, twice normal concussion
 * hits. (x3 if Bolg wields it two-handed)
 *
 *
 *
 * Note further that since war hammers are not properly
 * captured in Genesis, it was decided that polearm was most
 * appropriate, due to the immense weight and impaling nature
 * of this weapon.  Dunstable, 7/95
 *   Added keepable functionality "/lib/keep"  -Igneous Dec 13th 1996
 *   Made the maul #include "hit_msgs.h" to take care of the hit msgs
 *   -Igneous 1/97
 *   Lowered the stat needed to wield this weapon -Igneous June 11th 97
 *
 *   After looking over the weapon it seemed that it was doing triple damage
 *   In certain occasions. THe header says it does 2X damage so I corrected it.
 *   Igneous June 11th 1997
 *
 *   Fixed a small typo. Toby 2007-04-23
 *   Fixed damage so it actually does x3 as intended (x4 had been happening)
 *     - Gorboth (June 2008)
 * 
 * Navarre October 30th 2010. Added CAN_SEE check to the 'change grip' wielding.
 * You can still wield it in dark rooms, but if the halberd has set_no_show, 
 * and/or set_no_show_composite, it cannot be wielded. Some holsters and 
 * scabbards set that on the weapon to hide it, and the 'special' way to 
 * wield the weapon circumvent setting it back to normal, so it ends up
 * being 'the player is wielding something'.
 */
#define DEBUG(x) find_player("toby")->catch_msg("DEBUG - [giant black maul]: " + x + "\n")

#include "defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <options.h>

inherit "/std/weapon";
inherit "/lib/keep";

inherit "/d/Shire/moria/lib/hit_msg";


#ifdef DROP_LOG
int  log_drop();
#endif

void
create_weapon()
{
    set_name("maul");
    add_name("mace");
    add_name("hammer");
    add_name("_bolgs_maul");
    set_adj(({"giant", "alloy", "spiked", "bolg's", "black"}));

    set_short("giant black maul");

    set_long("Ashburz's Maul.\n" +
      "This is a giant black alloy spiked mace/hammer, which " +
      "belonged to Ashburz the Large, Son of Burzuruk, Captain of " +
      "the Red-Claws of Moria and  male uruk champion. It is said " +
      "that Ashburz the Large managed to wield the maul in one " +
      "hand, but it also said that he liked to use it two-handed. " +
      "You might try this trick by changing the grip of this weapon.\n");

    set_hit(35);
    set_pen(45);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_hands(W_BOTH);
    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);

    set_wf(TO);

    add_prop(OBJ_I_VOLUME, 12200);
    add_prop(OBJ_I_WEIGHT, 16600); /* 16.6 kg */
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_BUY, 1);

    //  Added this prop so I can log when Bolg drops his maul.
#ifdef DROP_LOG
    add_prop(OBJ_M_NO_DROP,log_drop);
#endif

    add_prop(MAGIC_AM_MAGIC, ({60, "enchantment", 50, "armour-slaying"}));
    add_prop(MAGIC_AM_ID_INFO, ({
    "It is enchanted.\n", 15,
    "This maul has a heavy enchantment of black magic on it.\n", 30,
    "It is very powerful magic indeed, capable of damaging " +
    "the toughest of armours.\n", 50
      }));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
      "This giant maul is essentially a club with sharp spikes " +
      "extending from it. It has been enchanted by the Balrog's " +
      "magic to enable Ashburz, his Uruk Champion to defend the Mines " +
      "from any silly dwarves wanting to reclaim their " +
      "former kingdom.\n");
    set_keep();
}

#ifdef DROP_LOG
int
log_drop()
{
    if (TP->query_real_name() == "ashburz" && TP->query_hp() != 0)
    {
    setuid(); seteuid(getuid());
    write_file(DROP_LOG, ctime(time()) +" "+ TP->query_name() +" drops "+
      HIS_HER(TP) + " "+short()+" with "+
      COMPOSITE_WORDS(FILTER_PLAYERS(INV(ENV(TP)))->query_name()) +
      " present.\n");
    }
    return 0;
}
#endif

#define LEFT_HAND ({ "left hand", "lefthanded", "left-handed", "left" })
#define RIGHT_HAND ({ "right hand", "righthanded", "right-handed", "right" })
#define ANY_HAND ({ "any hand", "whatever hand", "free hand", "any free hand", "any", \
            "one hand", "one handed", "one-handed", "one"})
#define BOTH_HANDS ({ "both hands", "using both hands", "both", "two-handed", "twohanded" })

int change_to(int hands)
{
    mixed res;

    if (query_wielded() && wep_hands != hands)
        unwield_me();

    wep_hands = hands;
    res = wield_me();

    if (stringp(res))
        return notify_fail(res);
    return 1;
}

int do_change(string hand)
{
    if (member_array(hand, LEFT_HAND) >= 0)
        return change_to(W_LEFT);
    else if (member_array(hand, RIGHT_HAND) >= 0)
        return change_to(W_RIGHT);
    else if (member_array(hand, ANY_HAND) >= 0)
        return change_to(W_ANYH);
    else if (member_array(hand, BOTH_HANDS) >= 0)
        return change_to(W_BOTH);
    else
        return 0;
}

int test_change(object ob)
{
    return stringp(function_exists("do_change", ob));
}

int change_grip(string arg)
{
    object ob;
    mixed *obs;
    string handedness;

    notify_fail("Eh? The syntax is: 'change grip on <weapon> to <handedness>'\n");
    if (!strlen(arg))
        return 0;
    ob = this_object();

    if (parse_command(arg, INV(TP),
                      "[the] [grip] [on] [of] [the] %i [to] [using] [the] %s",
                      obs,
                      handedness) && CAN_SEE(TP, TO))
    {
      obs = CMDPARSE_STD->normal_access(obs, "test_change", TO);
      if (sizeof(obs) == 0)
      {
          return 0;
      }
      if (sizeof(obs) >= 2)
      {
          return notify_fail("Eh? Try one weapon at a time.\n");
      }
      return obs[0]->do_change(handedness);
    }

    if (parse_command(arg, ({}), "[the] [grip] [to] [using] [the] %s", handedness) && CAN_SEE(TP, TO))
    {
        return do_change(handedness);
    }
    return 0;
}

init()
{
    ::init();
    add_action(change_grip, "change");
}

int query_usable(object who)
{
    if (who->query_race() == "uruk")
        return 1;
    else if (wep_hands == W_BOTH)
        return STR(who) > 100;
    else
        return STR(who) > 140 && DEX(who) > 110;
}

int
wield(object to)
{
    string how;

    if (!query_usable(TP))
    {
        write("You are not strong enough to wield this weapon.\n");
        return -1;
    }

    switch(wielded_in_hand)
    {
    case W_BOTH:
        how = "two-handed";
        break;
    case W_LEFT:
        how = "left-handed";
        break;
    case W_RIGHT:
        how = "right-handed";
        break;
    }

    write("With a great deal of effort, you manage to wield the "+
    short()+ " "+how+".\n");
    say(QCTNAME(TP) + " manages to wield the "+short()+" "+ how + ".\n");
    return 1;
}

int unwield(object to)
{
    wep_hands = W_BOTH;
    return 0;
}

int
get_hitloc_id(string hdesc, object who)
{
    int i, found, *hitloc_id;
    object co;
    mixed hitloc;

    co = who->query_combat_object();

    hitloc_id = co->query_hitloc_id();
    for (i=0; i<sizeof(hitloc_id); i++)
    {
        hitloc = co->query_hitloc(hitloc_id[i]);

        if (hitloc[2] == hdesc)
            return hitloc_id[i];
    }

    return -1;
}

mixed
get_hitloc_data(string hdesc, object who)
{
    int id = get_hitloc_id(hdesc, who);
    return who->query_combat_object()->query_hitloc(id);
}

object *
get_armours_protecting(string hdesc, object who)
{
    int id = get_hitloc_id(hdesc, who);
    return who->query_combat_object()->query_armour(id);
}

#define TYPES_OF_ARMOUR (A_BODY | A_SHIELD | A_HEAD | A_L_ARM | A_R_ARM | A_FEET)

int
breakable_armour(object what)
{
    if ( (what->query_likely_break() > 0) )
    {
        return 1;
    }
    return 0;
}

int
protects_hdesc(object what, int id)
{
    return member_array(id, what->query_protects()) >= 0;
}


int
break_armour(object ob)
{
    object tp = query_wielded();
    object enemy = ob->query_worn();
    object wear_func;
    object wearer;

    tp->catch_msg("Your "+short()+" hits "+QTNAME(enemy)+"'s "+QSHORT(ob)+
      " with shattering force!\n");
    enemy->catch_msg(QCTNAME(tp)+"'s "+short()+" hits your "+QSHORT(ob)+
      " with shattering force!\n");
    tp->tell_watcher(QCTNAME(tp)+"'s "+short()+
    " hits "+QCTNAME(enemy)+"'s "+
      QSHORT(ob)+" with shattering force!\n", enemy);

    if (TP->query_race() == "uruk" && !random(5))
    {
    tell_room(ENV(tp),
      CAP(LANG_THESHORT(ob))+" breaks into several pieces and " +
      "seems useless.\n");
    ob->remove_broken(1);
    }
    if (!random(10))
    {
    tell_room(ENV(tp),
      CAP(LANG_THESHORT(ob))+" breaks into several pieces and seems useless.\n");
    ob->remove_broken(1);
    }
    else
    {
    if (TP->query_race() == "uruk")
        ob->set_condition(ob->query_condition() + 6);
    else
        ob -> set_condition(ob->query_condition() + random(2) + 1);
    }
    return 1;
}

int
break_random_armour(object enemy, int dam, string hdesc)
{
    object *arms;
    object ob;
    mixed *magic_arr;
    int   ind;
    int tmp;

    arms = enemy->query_armour(-1);

    arms = filter(arms, breakable_armour);

    arms = filter(arms, &protects_hdesc(TO, get_hitloc_id(hdesc, enemy)) );



    if (!sizeof(arms))
    {
        return -1;
    }

    ob = arms[random(sizeof(arms))];

    if (ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        magic_arr = ob->query_prop(MAGIC_AM_MAGIC);

        ind = member_array("enchantment", magic_arr);
        if (ind>-1 && random(magic_arr[ind-1]) < dam/100)
            return break_armour(ob);

        if (random(ob->query_ac()) < dam/20)
            return break_armour(ob);
    }
    else
    {
        tmp = random(ob->query_ac());
        if ( tmp < dam/5)
            return break_armour(ob);
    }

    return 0;
}

int
did_hit(int aid, string hdesc, int phurt, object enemy,
  int dt, int phit, int dam)
{
    object tp = query_wielded();
    int break_status;

    if (dt==0)
    dt = W_BLUDGEON;

    if (!query_usable(tp))
    {
    tp->catch_msg("You fumble and drop your weapon!\n");
    tell_room(ENV(tp),QCTNAME(tp)+" fumbles and drop "+HIS_HER(tp)+
      " weapon!\n");
    tp->command("$drop _bolgs_maul");
    return 0;
    }

    if (wep_hands == W_BOTH)
    {
    if (dam >= 100)
    {
        break_status = break_random_armour(enemy, dam, hdesc);
        if (break_status == 1) // Did smash an armour
        {
        produce_msg(enemy,hdesc,phurt,dt);
        return 1;
        }
    }
    if (dam > 0)
    {
        if (break_status == -1) // Did not have armour at all
        {
        if (query_wielded()->query_race() == "uruk")
            enemy->heal_hp(-dam * 2);  // x3 damage
        else
            enemy->heal_hp(-dam);  // x2 damage.
        phurt += phurt;
        }
    }
    }
    produce_msg(enemy,hdesc,MIN(phurt,100),dt);
    return 1;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_reocver(string arg)
{
    init_wep_recover(arg);

    init_keep_recover(arg);
}
