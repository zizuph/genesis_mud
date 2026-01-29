/*
 *	/d/Gondor/common/wep/nazgul_sword.c
 *
 *	pragma strict_types
 *	Magical resistance updated after change in query_magic_res()
 *	Olorin, 1-dec-1995
 * 
 * Modification log:
 * Gwyneth, January 2001 - changed the write_file to log_file. There's
 *                         no need for a non-cycling log on this.
 *
 *   29-Mar-2007, Toby: Fixed typo
 *	
 */
#pragma strict_types

inherit "/std/weapon";
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

/* players with lower sword skill will drop the sword when attacking */
#define MIN_SKILL_NAZGUL_SWORD 70
#define MIN_SKILL_NAZGUL_SPELLCRAFT 20

int     given_away;
string  dropped_by_wiz,
        cloned_by_wiz;

void
create_weapon()
{
    set_name(({"sword","broadsword"}));
    add_name("_nazgul_broadsword");
    set_pname("swords");
    add_pname("broadswords");
    set_adj("black");
    add_adj("nazgul");
    set_short("@@short_func");
    set_long("@@long_func");
    set_default_weapon(60,60,W_SWORD,W_SLASH | W_BLUDGEON,W_BOTH,TO);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_RES_FIRE,  100);
    add_prop(OBJ_I_RES_AIR,    50);
    add_prop(MAGIC_AM_MAGIC,({ 33, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({ "The black sword seems to be magical.\n",1,
      "It seems to burn with magical flames, scorching the opponent.\n",25,
      "It will help you to resist magic calling on the power of the air.\n",70 }));
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_M_NO_GIVE,"@@test_give");
    add_prop(OBJ_M_NO_DROP, "@@drop_check");
    add_prop(OBJ_I_WEIGHT, 17000);
    add_prop(OBJ_I_VOLUME, 1900);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(60,60) + random(1000));

    add_prop(OBJ_S_WIZINFO,
      "The flaming broadsword of the nazgul.\n"
      + "Wielded by the nazgul /d/Gondor/common/npc/blackrider.\n"
      + "Magic resistance MAGIC_I_RES_MAGIC 20, additive,\n"
      + "                 MAGIC_I_RES_AIR   10, additive,\n"
      + "Special attack.\n");
}

string
long_func()
{
  if (query_wielded())
    return BSN("The massive black broadsword has strange dark flames " +
      "licking along the blade. It looks like a dangerous and powerful " +
      "weapon.");
  return BSN("The broadsword is jet black, made from a metal you have " +
    "never seen before.");
}

string
short_func()
{
    if (objectp(query_wielded()))
        return "flaming black broadsword";
    return "black broadsword";
}

int
test_give()
{
    FIX_EUID
    given_away = 1;
    if (TP->query_wiz_level())
    {
        log_file("items", TP->query_name()
          + " gave the Nazgul sword to "+ENV(TO)->query_name()
          + ". "+ctime(time())+".\n");
    }
    return 0;
}

mixed
drop_check()
{
    if ((ENV(TO)->id("nazgul")) && (ENV(TO)->query_hp() > 0))
        return "The Nazgul cannot drop his broadsword.\n";
    if (TP->query_wiz_level() && query_verb() != "give")
    {
        log_file("items",TP->query_name()
          +" dropped the Nazgul sword in "+file_name(ENV(TP))
          +" "+ctime(time())+".\n");
        dropped_by_wiz = TP->query_name();
    }
    else if (TP->query_wiz_level())
    {
        dropped_by_wiz = TP->query_name();
    }
    return 0;
}

mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    object  tp = TO->query_wielded();

    if (protectee == tp)
    {
        if (prop == MAGIC_I_RES_MAGIC)
            return ({ 20, 1});
        if (prop == MAGIC_I_RES_AIR)
            return ({ 10, 1});
    }

    return ::query_magic_protection(prop, protectee);
}

public mixed
wield(object wep)
{
    if (ENV(TO) == TP)
        TP->add_magic_effect(TO);

    write(BSN("You take a firm hold of the red hilt of the black broadsword. "
      + "Black flames suddenly start flickering around the blade!"));
    LSAY("As ", " wields the black broadsword, dark flames start flickering "
      + "along the blade!");
    return 1;
}

public mixed
unwield(object wep)
{
    object  tp = TO->query_wielded();

    if (!living(tp))
        return 0;

    if (tp->query_npc() && tp->id("nazgul") && !query_prop(OBJ_I_BROKEN))
        return "The nazgul cannot unwield the black broadsword.\n";

    tp->remove_magic_effect(TO);

    tp->catch_msg(BSN("As you release your grip on the black broadsword, "
      + "the flames surrounding the blade disappear!"));
    tell_room(ENV(tp), "As "+QTNAME(tp)+" unwields the black broadsword, "
      + "the dark flames surrounding its blade disappear!\n", tp);
    return;
}

int
try_to_burn(object enemy, int dam)
{
  object wielder = query_wielded();
  int    res     = enemy->query_magic_res(MAGIC_I_RES_FIRE);
  dam = dam - (res*dam/100);
  if (dam < 1) {
    enemy->catch_msg("The dark flames surrounding the black blade do not harm you.\n");
    return 1;
    }
  enemy->heal_hp(-dam);
  enemy->catch_tell("The dark flames sizzle and burn your skin painfully!\n");
  wielder->catch_tell("You smell burnt flesh as the dark flames of the black sword "+
    "burn your opponent!\n");
  wielder->tell_watcher("You smell burnt flesh as the dark flames of the black sword burn " +
    QTNAME(enemy) + ".\n", enemy);
  return 1;
}

int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
  string msg;
  object wielder;

  wielder = query_wielded();
  if (phurt == -2)
  {
    wielder->catch_msg("You swing the black broadsword towards " +
        QTNAME(enemy) + ", but " + PRONOUN(enemy) + " parries the attack!\n");
    enemy->catch_msg("The black broadsword swings towards you, but " +
        "you parry the attack!\n");
    wielder->tell_watcher(QCTNAME(wielder) + " swings the black broadsword " +
        "towards " + QTNAME(enemy) + ", but " + PRONOUN(enemy) +
        " parries the attack!\n", enemy);
  }
  else if (phurt == -1)
  {
    wielder->catch_tell("You swing the black broadsword through open air!\n");
    enemy->catch_msg(BSN("The black broadsword cuts a hole in the air where " +
      "your head was just a second ago!"));
    msg = " swings the black broadsword through open air!\n";
    wielder->tell_watcher(QCTNAME(wielder) + msg,enemy);
  }
  else if (phurt == 0)
  {
    wielder->catch_msg(QCTNAME(enemy)+" just barely manages to avoid your black blade this time. "+
      "Dark flames flicker close by "+POSSESSIVE(enemy)+" "+hdesc+".\n");
    enemy->catch_msg("The dark flames of "+QTNAME(wielder)+"'s black broadsword "+
      "flicker close by your "+hdesc+", as the blade misses.\n");
    wielder->tell_watcher(QCTNAME(wielder)+" just barely misses the "+hdesc+" of "+QTNAME(enemy)+
      " with the flaming black broadsword.\n",enemy);
  }
  else
  {
    switch(phurt)
    {
      case 1..4:
        wielder->catch_msg("The black blade just grazes the "+hdesc+
        " of "+QTNAME(enemy)+", dark flames flickering around it.\n");
        enemy->catch_msg("The dark blade of "+QTNAME(wielder)+" just grazes your "+
        hdesc+", dark flames flickering around it.\n");
        wielder->tell_watcher(QCTNAME(wielder)+" grazes the "+hdesc+" of "+QTNAME(enemy)+
        ", dark flames flickering around it.\n",enemy);
        break;
      case 5..9:
        wielder->catch_msg("Your flaming black sword strikes "+QTNAME(enemy)+"'s "+hdesc+". "+
        "Dark flames lick the "+hdesc+" of "+QTNAME(enemy)+".\n");
        enemy->catch_msg("The flaming black sword strikes your "+hdesc+". "+
        "Dark flames lick your "+hdesc+" painfully.\n");
        wielder->tell_watcher("The flaming black sword strikes the "+hdesc+" of "+QTNAME(enemy)+", "+
        "dark flames licking the wound.\n",enemy);
        break;
      case 10..19:
        wielder->catch_msg("Swinging the black broadsword at "+QTNAME(enemy)+
        ", you hurt "+POSSESSIVE(enemy)+" "+hdesc+" with both blade and dark flames.\n");
        enemy->catch_msg("Swinging the black broadsword at you, "+QTNAME(wielder)+
        " hurts your "+hdesc+", with both blade and dark flames.\n");
        wielder->tell_watcher("Swinging the black broadsword at "+QTNAME(enemy)+", "+
        QTNAME(wielder)+" hurts "+POSSESSIVE(wielder)+" enemy's "+hdesc+
        " with both blade and dark flames.\n",enemy);
        break;
      case 20..29:
        wielder->catch_msg("With a strong slash you hurt "+QTNAME(enemy)+
        "'s "+hdesc+" rather badly, dark flames arcing from the black blade.\n");
        enemy->catch_msg("With a strong slash, "+QTNAME(wielder)+" hurts your "+hdesc+
        " rather badly, dark flames arcing from the black blade.\n");
        wielder->tell_watcher("With a strong slash, "+QTNAME(wielder)+" hurts "+QTNAME(enemy)+
        "'s "+hdesc+" rather badly. Dark flames arc from the black blade.\n",enemy);
        break;
      case 30..49:
        wielder->catch_msg("Your mighty black blade causes great pain as it hits "+
        QTNAME(enemy)+" in the "+hdesc+", dark flames engulfing the wound.\n");
        enemy->catch_msg("You feel great pain as "+QTNAME(wielder)+" hits your "+
        hdesc+" engulfed by dark flames!\n");
        wielder->tell_watcher(QCTNAME(wielder)+" hurts "+QTNAME(enemy)+" very bad with the "+
        "black blade, dark flames engulfing "+POSSESSIVE(wielder)+" enemy's "+hdesc+"!\n",enemy);
        break;
      case 50..69:
        wielder->catch_msg("The black blade strikes your enemy's "+hdesc+" with a sick sound.\n");
        enemy->catch_msg("The black blade of "+QTNAME(wielder)+" strikes your "+hdesc+" with a sickening sound.\n");
        wielder->tell_watcher("The black blade strikes the "+hdesc+" of "+QTNAME(enemy)+
        " with a sickening sound.\n",enemy);
        break;
      case 70..89:
        wielder->catch_msg("Blood is splattered all around as you wreak havoc upon the "+
        hdesc+" of "+QTNAME(enemy)+" with your black sword. The dark flames seem to "+
        "feed from the massacre.\n");
        enemy->catch_msg("Blood splatters all around as the flaming black blade of "+
        QTNAME(wielder)+" wreaks havoc upon your "+hdesc+". The dark fire seems to "+
        "feed upon your pain.\n");
        wielder->tell_watcher("Blood splatters all around as "+QTNAME(wielder)+" wreaks havoc on "+
        QTNAME(enemy)+"'s "+hdesc+"!\n",enemy);
        break;
      default:
        wielder->catch_msg("Your flaming black broadsword nearly cuts off the "+hdesc+
        " of "+QTNAME(enemy)+" as you slash with all your might!\n");
        enemy->catch_msg("Your "+hdesc+" is nearly cut off as "+QTNAME(wielder)+
        " swings "+POSSESSIVE(wielder)+" flaming black broadsword at you with great force!\n");
        wielder->tell_watcher(QCTNAME(enemy)+"'s "+hdesc+" is nearly cut off as the flaming black broadsword of "+
        QTNAME(wielder)+" hits with great force!\n",enemy);
        break;
      }
    try_to_burn(enemy,dam/3);
  }
  return 1;
}

int
try_hit(object ob)
{
  if (query_wielded()->query_skill(SS_WEP_SWORD) >= MIN_SKILL_NAZGUL_SWORD &&
    query_wielded()->query_skill(SS_SPELLCRAFT) >= MIN_SKILL_NAZGUL_SPELLCRAFT)
  {
    return 1;
  }

  query_wielded()->catch_msg(BSN("When you try to hit your opponent with " +
    LANG_ADDART(short_func()) +
    ", you clumsily drop it. Perhaps you should first learn " +
    "how to control magical powers, and how to fight well "+
    "with a sword, before you try to wield "+
    "a powerful weapon like this one, if not, you are more " +
    "likely to hurt yourself than your foe!"));
  query_wielded()->command("drop _nazgul_broadsword");

  return 0;
}

void
enter_env(object to, object from)
{
  ::enter_env(to, from);
  seteuid(getuid(this_object()));
  if (!from && TP->query_wiz_level()) {
    cloned_by_wiz = CAP(TP->query_real_name());
    if (!living(to)) log_file("items",TP->query_name()+" cloned the Nazgul sword into "+file_name(ENV(TO))+". "+ctime(time())+".\n");
    else log_file("items",TP->query_name()+" cloned the Nazgul sword."+ctime(time())+".\n");
    }
  else if (given_away && from->query_wiz_level())
  {
    log_file("items",from->query_name()+" gave the Nazgul sword to "+to->query_name()+". "+ctime(time())+".\n");
  given_away = 0;
  }
  if (!living(from) && strlen(dropped_by_wiz)) {
    log_file("items",TP->query_name()+" picked up the Nazgul sword dropped by "+dropped_by_wiz+" in "+file_name(ENV(TP))+". "+ctime(time())+".\n");
    }
  else if (!living(from) && strlen(cloned_by_wiz)) {
    log_file("items",TP->query_name()+" picked up the Nazgul sword cloned by "+cloned_by_wiz+" in "+file_name(ENV(TP))+". "+ctime(time())+".\n");
  }
}

void
leave_env(object from, object to)
{
    string  fn = "the void";
    
    ::leave_env(from, to);

    if (!objectp(from))
        return;
    if (from->query_prop(ROOM_I_IS))
	fn = file_name(from);
    else if (objectp(ENV(from)))
	fn = file_name(ENV(from));
    if (!objectp(to))
	log_file("items", from->query_name()
		   + " destructed the Nazgul sword, in " + fn + ". "
		   + ctime(time()) + ".\n");
}

