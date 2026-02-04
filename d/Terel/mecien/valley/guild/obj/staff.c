/* A staff for The Ancient Mystic Order
 * This staff can only be used by guild members. Its
 * main usage, besides showing the level of the player, is
 * to contain a limited amount of mana. The maximum amount
 * it can contain is presently defined by (see function
 * query_max_mana() below)
 *         2*(this_player()->query_stat(SS_OCCUP))
 * That is: it's based on the guild stat of the player.
 *
 * Three commands are enabled by the staff:
 * raise staff                A maximum amount of, defined by
 *                            MANA_INC and query_mana_inc(), is
 *                            channeled from the player into the staff.
 * lean on staff              A maximum amount of MANA_INC is channeled
 *                            from the staff to the player,
 * direct staff towards <who> The amount of mana (MANA_INC) is channeled
 *                            from the staff to the living object <who>.
 * hold staff                 The ownwer takes hold of the staff. Must be
 *                            done to enable the cmds above.
 * hide staff                 The owner hides away the staff.
 */
inherit "/std/object";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <wa_types.h>
#include <std.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP         this_player()
#define TO         this_object()
#define ETO        environment(TO)
#define ETP        environment(TP)
#define NF(xx)     notify_fail(xx)

#define MANA_INC   20
#define SUBLOC     "held_staff_subloc"

		   
int mana_stored, max_stored;
int held, aid = 0;
string hand = "left";
string owner;

public int query_mana();
public int query_mana_inc();
public int query_max_mana();
public int allowed(object ob);
public string query_owner();
public void destroy_staff(object holder);
public void hold_me();
public void set_owner(string s);
public void add_mana(int m);
public void check_for_other_staffs(object ob);
static mixed parse_this(string str, string form);

public void
create_object()
{
   set_name("staff");
   add_name(MYSTIC_STAFF);
   set_adj("@@level_type@@");
   set_long(
       "A mysterious staff, carved of fine wood and inscribed with "
     + "arcane symbols and runes.\n");
   add_item("symbols", "It's a circle and a star.\n");
   add_item("runes", "@@my_runes@@");
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 400);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_NO_DROP, 1);
}

public string
my_runes()
{
   if (MEMBER(TP)) {
       return "The runes read: " + owner + "\n";
   } else {
       return "You don't understand the runes.\n";
   }
}

public string
query_auto_load()
{
    return MASTER+":"+mana_stored+"##"+owner+"##"+held;
}

public void
init_arg(string str)
{
    if (sscanf(str, "%d##%s##%d", mana_stored, owner, held) != 3) {
        owner = "";
        mana_stored = 0;
        held = 0;
    }
}

public void
init()
{
    ::init();
    if (ETO == TP) {
        add_action("do_point", "direct");
        add_action("do_lean", "lean");
        add_action("do_raise", "raise");
        add_action("do_hold", "hold");
        add_action("do_hide", "hide");
        add_action("do_read", "read");
        add_action("do_tap", "tap");
    }
}

public int
do_tap(string str)
{
    if (!str || !id(str)) return 0;
    write("You tap your " + short() + " against the ground.\n");
    tell_room(ETP, QCTNAME(TP) + " taps " + TP->query_possessive() +
                   " " + short() + " against the ground.\n", TP);
    return 1;
}

public int
do_read(string str)
{
    if (!str || str != "runes") return 0;
    write(my_runes());
    return 1;
}

public void
enter_env(object dest, object old)
{
   ::enter_env(dest, old);
   
   if (!dest || !living(dest)) return;
   
   if (!strlen(owner))
       owner = dest->query_name();
   
   if (!allowed(dest) && !aid) {
       aid = set_alarm(1.0, -1.0, &destroy_staff(dest));
       return;
   } 
   check_for_other_staffs(dest);
   max_stored = query_max_mana();
   if (mana_stored > max_stored)
       mana_stored = max_stored;
   if (held)
       set_alarm(2.0, -1.0, hold_me);
}

public void
leave_env(object from, object to)
{
  held = 0;
  if (living(from))
      from->remove_subloc(SUBLOC);
  ::leave_env(from, to);
}

public void
destroy_staff(object holder)
{
    aid = 0;
    tell_room(environment(holder), "The " + short() + 
        " bursts into flame and disintigrates in a blinding light.\n");
    remove_object();
}

/*
 * This function returns true if object ob is allowed to possess
 * this staff.
 */
public int
allowed(object ob)
{
    if (!living(ob)) return 1;
    if (T_WIZ(ob)) return 1;
    if (owner != ob->query_name()) return 0;
    if (MEMBER(ob)) return 1;
    return 0;
}

public string
level_type()
{
   int gl;
   
   if (TP == ETO) {
      gl = TP->query_stat(SS_OCCUP);
      switch(gl) {
         case 100..1000: return "ancient runed"; break;
         case 80..99:    return "runed ebony";   break;
         case 50..79:    return "silvery runed"; break;
         case 20..49:    return "runed white";   break;

	 default: return "arcane"; break;
      }
   } else {
      return "arcane";
   }
}

public int
do_hold(string str)
{
    object *obs;

    NF("Hold what?\n");
    if (!str) return 0;

    obs = FIND_STR_IN_OBJECT(str, TP);
    if (sizeof(obs) == 0) return 0;
    if (sizeof(obs) > 1) return 0;
    if (obs[0] != TO) return 0;
    NF("It's already held by you.\n");
    if (held) return 0;
    NF("You do not have a hand free.\n");
    if (TP->query_weapon(W_LEFT))  {
        hand = "right";
        if (TP->query_weapon(W_RIGHT))
            return 0;
    }
    hold_me();
    held = 1;
    return 1;
}

public void
hold_me()
{
    if (!living(ETO)) return;
    ETO->catch_msg("You take hold of your "+short()+".\n");
    ETO->add_subloc(SUBLOC, TO);
}

public int
do_hide(string str)
{
    object *obs;

    NF("Hide what?\n");
    if (!str) return 0;

    obs = FIND_STR_IN_OBJECT(str, TP);
    if (sizeof(obs) == 0) return 0;
    if (sizeof(obs) > 1) return 0;
    if (obs[0] != TO) return 0;
    NF("It's already hidden.\n");
    if (!held) return 0;
    write("You hide your "+short()+".\n");
    TP->remove_subloc(SUBLOC);
    held = 0;
    return 1;
}

public int
do_point(string str)
{
    int ob_max_mana, m_inc;
    object ob;
    object *obs;

    NF("You must take hold of your staff first.\n");
    if (!held) return 0;
    NF("Direct staff towards whom?\n");
    if (!str) return 0;
    obs = parse_this(str, "'staff' [towards] %l");
    if (!sizeof(obs)) return 0;
    if (sizeof(obs) > 1) return 0;
    ob = obs[0];

    TP->catch_msg("You direct your " + short()+ " towards " +
		  QTNAME(ob)+".\n");
    ob->catch_msg(QCTNAME(TP) + " points at you with " +
		  TP->query_possessive() + " " + short() + ".\n");
    say(QCTNAME(TP) + " points at " + QTNAME(ob) + " with " +
	TP->query_possessive() + " " + short() + ".\n", ({TP, ob}));
    ob_max_mana = ob->query_max_mana();
    if (mana_stored > 0 && ob->query_mana() < ob_max_mana) {
	tell_room(environment(TP), "The "+TO->query_name()+
		  " starts to glow faintly.\n");
	if (mana_stored < query_mana_inc()) {
	    m_inc = mana_stored;
	} else {
	    m_inc = query_mana_inc();
	}
	if (ob->query_mana() + m_inc > ob_max_mana) {
	    ob->set_mana(ob_max_mana);
	    ob->catch_msg("Your mental powers have been restored.\n");
	} else {
	    ob->add_mana(m_inc);
	    ob->catch_msg("You feel less tired, mentally.\n");
	}
	mana_stored -= m_inc;
    }
    return 1;
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if (for_obj == carrier)
        str = "You are holding your " + short() + ".\n";
    else
        str = capitalize(carrier->query_pronoun()) +
              " holds a mysterious " + short() + ".\n";

    return str;

}

public int
do_raise(string str)
{
    object *obs;

    NF("You must take hold of your staff first.\n");
    if (!held) return 0;
    NF("Raise what?\n");
    if (!str) return 0;
    obs = parse_this(str, "[the] %i");
    if (sizeof(obs) == 0 || sizeof(obs) >= 2) return 0;
    if (obs[0] != TO) return 0;
    write("You raise the staff above your head.\n");
    say(QCTNAME(TP) + " raises " + TP->query_possessive() + " " +
	short() + ".\n");
    max_stored = query_max_mana();
    if (TP->query_mana()>query_mana_inc() && mana_stored<max_stored) {
	tell_room(ETP, "The " + short() +
		      " starts to glow faintly.\n");
	TP->add_mana(-query_mana_inc());
	if (mana_stored + query_mana_inc() > max_stored) {
	    mana_stored = max_stored;
	} else {
	    mana_stored += query_mana_inc();
	}
    }
    return 1;
}

public int
do_lean(string str)
{
    int max_mana, m_inc;
    object *obs;

    NF("You must take hold of your staff first.\n");
    if (!held) return 0;
    NF("Lean on what?\n");
    if (!str) return 0;
    obs = parse_this(str, "[on] %i");
    if (sizeof(obs) == 0 || sizeof(obs) >= 2) return 0;
    if (obs[0] != TO) return 0;
    write("You lean on the "+TO->query_name()+".\n");
    say(QCTNAME(TP) + " leans on " + TP->query_possessive() + " " +
	short() + ".\n");
    max_mana = TP->query_max_mana();
    if (mana_stored > 0 && TP->query_mana() < max_mana ) {
	if (mana_stored < query_mana_inc()) {
	    m_inc = mana_stored;
	} else {
	    m_inc = query_mana_inc();
	}
	mana_stored -= m_inc;
	if (TP->query_mana() + m_inc > max_mana) {
	    TP->set_mana(max_mana);
	    write("Your mental powers have been restored.\n");
	} else {
	    TP->add_mana(m_inc);
	    write("You feel less tired, mentally.\n");
	}
    }
    return 1;
}

static mixed
parse_this(string str, string form)
{
    object   *oblist, *tmplist;
    int      i;

    tmplist = ({});
    if (!CAN_SEE_IN_ROOM(TP)) return tmplist;

    if (!str || (!parse_command(lower_case(str), environment(TP),
                         form, oblist)))
        return ({});

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist)) return ({});

    for (i=0; i<sizeof(oblist); i++) {
        if (objectp(oblist[i]) && living(oblist[i]) &&
                (TP != oblist[i]) && CAN_SEE(TP, oblist[i]))
            tmplist += ({ oblist[i] });
	if (!living(oblist[i]) && CAN_SEE(TP, oblist[i]))
            tmplist += ({ oblist[i] });
    }
    return tmplist;
}

public void
add_mana(int m)
{
    mana_stored += m;
    if (mana_stored < 0) mana_stored = 0;
    if (mana_stored > query_max_mana()) mana_stored = query_max_mana();
}

public int
query_mana()
{
    return mana_stored;
}

public int
query_max_mana()
{
    int mana;
    object who;

    if (!strlen(owner)) return 0;
    who = find_player(lower_case(owner));
    if (!who) return 0;
    return 2*(who->query_stat(SS_OCCUP));
}

public int
query_mana_inc()
{
    return MANA_INC;
}

public string
query_owner()
{
    return owner;
}

public void
set_owner(string s)
{
    owner = s;
}

public void
check_for_other_staffs(object ob)
{
    int i;
    object *obs;

    obs = deep_inventory(ob);
    for (i=0; i<sizeof(obs); i++) {
	if (MASTER_OB(obs[i]) == MASTER && obs[i] != TO) {
	    obs[i]->remove_object();
	}
    }
}

public string
stat_object()
{
    string str;

    str = ::stat_object();

    str += capitalize(query_name()) + " owner: " + owner + "\n";
    str += "The mana stored: " + mana_stored + "(" + max_stored +
           ")\n";
    return str;
}
