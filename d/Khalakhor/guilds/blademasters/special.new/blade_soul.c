/* Blademaster soul
 * Creation date undocumented
 * Added "bstudy" and cleaned up the code a wee bit
 * Tapakah, 09/2021
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include "defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Khalakhor/guilds/blademasters/special/help";

#include "emotes.c"
#include "forms.c"


#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))


/*
 * Function name: create
 * Description  : Called when loading to set up some initial
 *                variables.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create ()
{
  setuid();
  read_help_dir(DOCS + "help/");
  set_help_type(({"blademasters", "blademaster"}));
}

/*
 * Function name: get_soul_id
 * Description  : Returns the id string for this cmdsoul
 * Arguments    : n/a
 * Returns      : "Blademasters"
 */
string
get_soul_id ()
{
  return "Blademasters";
}

/*
 * Function name: query_cmd_soul
 * Description  : Identifies this object as a cmdsoul.
 * Arguments    : n/a
 * Returns      : 1
 */
int
query_cmd_soul ()
{
  seteuid(getuid());
  return 1;
}

int
do_bnews (string str)
{
  setuid(); seteuid(getuid());
  TP->more(read_file(DOCS + "news"));
  (SPECIAL + "guildmaster")->update_news(TP->query_real_name());
  return 1;
}

/*
 * Allow em to toggle the decapitation.
 *
 */
int
do_bdecapitate (string str)
{
  int val;

  val = TP->query_prop(BLADEMASTER_NO_DECAPITATE);

  if (stringp(str)) {
    str = lower_case(str);
    if (str == "on")
      val = 0;
    else if (str == "off")
      val = 1;
    else {
      notify_fail("bdecapitate on or off?");
      return 0;
    }
          
  }

  TP->add_prop(BLADEMASTER_NO_DECAPITATE, val);
  write("Decapitate enemies: " + (val ? "Off" : "On") + "\n");
  return 1;
}

int
notice_bstudy (object ob)
{
  return random((ob->query_skill(SS_AWARENESS)-50)*2) >= 20 ? 1 : 0;
}

int
sort_hitlocs (mixed *a, mixed *b)
{
  return a[1] < b[1] ? 1 : a[1] == b[1] ? 0 : -1;
}

mixed *
compact_hitlocs (mixed *observed)
{
  mixed *_observed = allocate(sizeof(observed));
  int o=0;

  foreach (mixed observed_hitloc: observed) {
    if (! _observed[0])
      _observed[0] = ({ observed_hitloc });
    else {
      if (abs(observed_hitloc[1] - _observed[o][0][1]) < 6)
        _observed[o] += ({ observed_hitloc });
      else
        _observed[++o] = ({ observed_hitloc });
    }
  }
  _observed -= ({ 0 });
  return _observed;
}

string
map_hitloc_name (mixed *hitloc)
{
  return "the " + hitloc[0];
}

void
report_hitlocs (mixed *observed)
{
  string desc = "You notice it's the easiest to hit on ";
  string extra_desc = "";
  int h = 0;
  string names, margin = "";
  string *unprotected = ({});
  string *names_l;
  
  foreach (mixed hitloc: observed) {
    if (! pointerp(hitloc))
      continue;
    names_l = map(hitloc, map_hitloc_name);
    names = COMPOSITE_WORDS_WITH(names_l, "or");
    if (h && observed[h][0][1]*2 < observed[h-1][0][1])
      margin = ", by a significant margin, ";
    else
      margin = " ";
    desc += (h ? "then" + margin : "") + names;
    foreach (mixed hl: hitloc)
      if (! hl[2])
        unprotected += ({"the " + hl[0]});
    h++;
    desc += (h < sizeof(observed)) ? ", " : "";
  }
  if (sizeof(unprotected))
    extra_desc += "You also observe that " + COMPOSITE_WORDS(unprotected) +
      " appear to be unprotected.\n";
  desc += ".\n" + extra_desc;
  TP->catch_msg(desc);
}

void
complete_bstudy (object target)
{
  object cbo = target->query_combat_object();
  int *hitloc_ids = cbo->query_hitloc_id();
  int num_hitlocs = sizeof(hitloc_ids);
  
  if (! num_hitlocs) {
    write("You realize that there is nothing you can hit " +
          QCTNAME(target) + " on.\n");
    return;
  }

  if (num_hitlocs == 1) {
    write("You realize that you can only hit " + QCTNAME(target) +
          " on the " + cbo->query_hitloc(hitloc_ids[0]) + ".\n");
    return;
  }

  mixed hitloc_data;
  int randomness = 100 -
    (TP->query_skill(SS_APPR_MON) +
     TP->query_base_stat(SS_LAYMAN) / 5);
  if (randomness < 10)
    randomness = 10;

  int spread, covered;
  mixed *observed = ({});
  foreach (int hitloc_id: hitloc_ids) {
    hitloc_data = cbo->query_hitloc(hitloc_id);
    if (! hitloc_data[1])
      continue;
    spread = random(randomness*2) - randomness;
    covered = hitloc_data[4]
      ? (100-randomness)*sizeof(hitloc_data[4])
      : randomness;
    covered = random(covered);
    observed += ({({
                    hitloc_data[2],
                    hitloc_data[1] * (100+spread) / 100,
                    covered > 20 ? 1 : 0,
                  })});
  }
  sort_array(observed, sort_hitlocs);
  observed = compact_hitlocs(observed);
  report_hitlocs(observed);
}

int
do_bstudy (string str)
{
  object target;

  if (! str)
    NF0("Who would you like to bstudy?");

  if (! parse_command(str, ENV, " %l ", target))
    NF0("Who would you like to bstudy?");

  target = target[1];
  if (TP->query_attack())
    NF0("You cannot study your opponent during a fight!");

  if (ENV->query_prop(ROOM_M_NO_ATTACK))
    NF0("It's too peaceful here for such a hostile action.");

  if (target->query_prop(OBJ_M_NO_ATTACK))
    NF0("You feel the divine forces protecting this creature "+
        "diverting your stare.");

  if (! F_DARE_ATTACK(TP, target))
    NF0("You don't dare to study such a formidable opponent.");

  TP->catch_msg("You narrow your eyes, studying " + QCTNAME(target) +
                " carefully.\n");
  object *audience = filter(FILTER_PLAYERS(all_inventory(ENV)), notice_bstudy);
  tell_room(ENV, QCTNAME(TP) + " narrows his eyes, studying "
            + QCTNAME(target) +" carefully.\n", ({TP, target}));
  
  if (TP->check_seen(target) && notice_bstudy(target)) {
    target->catch_msg(QCTNAME(TP) + " narrows his eyes, studying you " +
                      "carefully.\n");
    TP->catch_msg(QCTNAME(target) + " seems to have noticed your interest!");
    if (! interactive(target) && ! random(4)) {
      TP->catch_msg(QCTNAME(target) + " flexes the muscles just in case...\n");
      //target->attack_object(TP);
      return 1;
    }
  }
  set_alarm(2.0, 0.0, &complete_bstudy(target));
  return 1;
}

mapping
query_ability_map ()
{
  return ([
    "battack" : BATTACK_ABILITY,
  ]);
}

/*
 * Function name: query_cmdlist
 * Description  : Returns a mapping of all the commands provided
 *                by this soul.
 * Arguments    : n/a
 * Returns      : As described above.
 */       
mapping
query_cmdlist ()
{
  return ([
    "bnews"   : "do_bnews",
    "battack" : "do_ability",
    "bstudy"  : "do_bstudy",
    "bdecapitate" : "do_bdecapitate", 
    "bflip"   : "do_flip",        /* emotes.c */
    "bform1"  : "do_form1",       /* forms.c */
    "bform2"  : "do_form2",       /* forms.c */
    "bform3"  : "do_form3",       /* forms.c */
    "boath"   : "do_oath",        /* emotes.c */
    "bsalute" : "do_salute",      /* emotes.c */
    "bsmile"  : "do_smile",       /* emotes.c */
    "bbreak"  : "do_break",       /* emotes.c */
    "bwar"    : "do_bwar",        /* emotes.c */
  ]) + help_cmdlist();
}
