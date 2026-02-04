/* rigor.c
 *
 * The Mystic Order rigor spell. It paralyzes victims.
 *
 * Made by Sorgum
 */
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>

#define TP         this_player()
#define TO         this_object()
#define NF(xx)     notify_fail(xx)
#define SPELL_COST 500
#define GUILD_NAME "The Ancient Mystic Order"
#define PARA_OBJ   "/std/paralyze"
#define HYPER_PARA_OBJ   "/d/Terel/sorgum/spells/para"

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
            tmplist = tmplist + ({ oblist[i] });
    }
    return tmplist;
}

unparalyze(object ob)
{
     tell_room(environment(ob), QCTNAME(ob) + " recovers from being " +
	       "paralyzed\n", ob);
     tell_object("You recover from being paralyzed.\n");
}

int
rigor(string str)
{
  int i, cost, time, mana, suc;
  object *who, ob, dumb;

  NF("Rigor who?\n");
  if (!str) return 0;

  who = parse_this(str, "[to] %l");
  if (!sizeof(who)) return 0;

  for (i=0; i<sizeof(who); i++) {
      ob = who[i];
      cost = SPELL_COST + ob->query_stat(SS_WIS)/2;
      mana = TP->query_mana();
      if (mana <= cost && (TP->query_name() != "Sorgum")) {
	  TP->catch_msg("You do not have enough mental strength to " +
			"silence " + QTNAME(ob) + ".\n");
	  continue;
      }
      suc = random(TP->query_skill(SS_FORM_ENCHANTMENT));
      suc -= random(ob->query_skill(SS_FORM_ABJURATION));
      if (suc <= 0 && (TP->query_name() != "Sorgum")) {
	  if (mana > SPELL_COST) TP->add_mana(-SPELL_COST);
	  TP->catch_msg("You failed to silence " + QTNAME(ob) + ".\n");
	  ob->catch_msg(QCTNAME(TP) + " tried to silence you.\n");
	  continue;
      }
/*      time = 50 + random(TP->query_skill(SS_SPELLCRAFT)); */
      time = 60;
      TP->add_mana(-cost);
      seteuid(getuid(TO));
      if (TP->query_name() == "Sorgum")
	   dumb = clone_object(HYPER_PARA_OBJ);
      else
	   dumb = clone_object(PARA_OBJ);	   
      dumb -> set_stop_verb("");
      dumb -> set_remove_time(time);
      dumb -> set_stop_fun("unparalyze");
      dumb -> move(ob);
      TP->catch_msg("You paralyze " + QTNAME(ob) + ".\n");
      ob->catch_msg(QCTNAME(TP) + " has paralyzed you.\n");
  }
  return 1;
}
     

		 
     
