/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* mutus.c
 *
 * The Mystic Order mutus spell. It silences victims, i.e.
 * prohibits the victims of using say cmds for a while.
 *
 * Made by Mortricia
 */
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <comb_mag.h>
#include <filter_funs.h>
#include <composite.h>

#define TP         this_player()
#define TO         this_object()
#define SPELL_COST 10
#define GUILD_NAME "The Ancient Mystic Order"
#define DUMB_OBJ   "/d/Terel/mecien/valley/guild/spells/dumbness"

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

nomask mixed
mutus(string str)
{
  int i, cost, time, mana, suc;
  object *who, ob, dumb;

  if (!str) return "Mutus who?\n";

  who = parse_this(str, "[to] %l");
  if (!sizeof(who)) return 0;

  for (i=0; i<sizeof(who); i++) {
      ob = who[i];
      cost = SPELL_COST + ob->query_stat(SS_WIS)/2;
      mana = TP->query_mana();
      if (mana <= cost) {
	  TP->catch_msg("You do not have enough mental strength to " +
			"silence " + QTNAME(ob) + ".\n");
	  continue;
      }
      if (NPMAGIC(ob)) {
          TP->catch_msg("You failed to silence " + QTNAME(ob) + ".\n");
          continue;
      }
      suc = random(TP->query_skill(SS_FORM_ENCHANTMENT));
      suc -= random(ob->query_skill(SS_FORM_ABJURATION));
      if (suc <= 0) {
	  if (mana > SPELL_COST) TP->add_mana(-SPELL_COST);
	  TP->catch_msg("You failed to silence " + QTNAME(ob) + ".\n");
	  ob->catch_msg(QCTNAME(TP) + " tried to silence you.\n");
	  continue;
      }
      time = 45 + random(TP->query_skill(SS_SPELLCRAFT));
      TP->add_mana(-cost);
      seteuid(getuid(this_object()));
      dumb = clone_object(DUMB_OBJ);
      dumb -> set_caster(TP);
      dumb -> set_standard_dumbness();
      dumb -> set_remove_time(time);
      dumb -> move(ob);
      TP->catch_msg("You silence " + QTNAME(ob) + ".\n");
      ob->catch_msg(QCTNAME(TP) + " has made you dumb.\n");
  }
  return 1;
}
