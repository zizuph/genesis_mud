/* Rogon, I'd like you to try to remove most references to this file
 * and its abbreviations from your code.  Use the ones from
 * ~Shire/common/defs.h instead, inherited in every defs.h file in the
 * domain, or, at least it should be.  I'll be moving many of these
 * to that file, but I'll also change some of the names.  All #defines
 * will be capitalized, C(x) will change to CAP(x), and E(x) to ENV(x).
 * There may be others.  This is to be done so that we have a more
 * consistent environment throughout the Shire.  It allows me to
 * debug your code easier, you to debug mine easier, and the many
 * newbie wizards I try to teach a better chance of understanding
 * the code.  I know it will be an inconvenience to you, but we need
 * as much consistency in the domain as possible.  I'll try to help
 * keep your discomfort at a minimum.
 * Astro!
 */
#ifndef ABBREVS_H
#define ABBREVS_H

#define SetUid() setuid(); seteuid(getuid())
#define CommaUid() setuid(), seteuid(getuid())
#include "/d/Shire/common/include/dirs.h"

#define C(x)  capitalize(x)
#define he(x) x->query_pronoun()
#define He(x) C(he(x))
#define him(x) x->query_objective()
#define Him(x) C(him(x))
#define his(x) x->query_possessive()
#define His(x) C(his(x))
#define Name(x) x->query_name()

#define TP this_player()
#define TO this_object()
/*
#define TI this_interactive()
*/
#define E(x) environment(x)
#define EO environment(this_object())
#define EP environment(this_player())
#define EI environment(this_interactive())

#define MYBS(x) "/d/Shire/rogon/lib/bs"->break_string(x, 78)
#define WF(x) "/d/Shire/rogon/spells/spell_list"->wf(x)
#define Fail(x) return "/d/Shire/rogon/spells/spell_list"->nf(x);
/*
#define NF(x) notify_fail("/d/Shire/rogon/spells/spell_list"->notify(x))
*/

#define AddSkill(ob,sk,x) ob->set_skill_extra(sk, ob->query_skill_extra(sk) + x)
#define AddProp(ob, prop, x) ob->add_prop(prop, ob->query_prop(prop)+x)
#define AddStat(ob, s, x) ob->set_stat_extra(s, ob->query_stat_extra(s)+x)

#include <ss_types.h>
#define Str(x) x->query_stat(SS_STR)
#define Dex(x) x->query_stat(SS_DEX)
#define Con(x) x->query_stat(SS_CON)
#define Int(x) x->query_stat(SS_INT)
#define Wis(x) x->query_stat(SS_WIS)
#define Dis(x) x->query_stat(SS_DIS)

#define Hp(x)  x->query_hp()
#define MaxHp(x) x->query_max_hp()

#define LocSense(x)   x->query_skill(SS_LOC_SENSE)
#define Language(x)   x->query_skill(SS_LANGUAGE)
#define Tracking(x)   x->query_skill(SS_TRACKING)
#define Climbing(x)   x->query_skill(SS_CLIMB)
#define Awareness(x)  x->query_skill(SS_AWARENESS)
#define FRTraps(x)    x->query_skill(SS_FR_TRAPS)
#define TwoHanded(x)  x->query_skill(SS_2H_COMBAT)
#define Unarmed(x)    x->query_skill(SS_UNARM_COMBAT)
#define Blind(x)      x->query_skill(SS_BLIND_COMBAT)
#define Parry(x)      x->query_skill(SS_PARRY)
#define Defence(x)    x->query_skill(SS_DEFENCE)
#define Spellcraft(x) x->query_skill(SS_SPELLCRAFT)
#define Herbalism(x)  x->query_skill(SS_HEBALISM)
#define Alchemy(x)    x->query_skill(SS_ALCHEMY)
#define OpenLocks(x)  x->query_skill(SS_OPEN_LOCK)
#define PickLocks(x)  OpenLocks(x)
#define Acrobatics(x) x->query_skill(SS_ACROBAT)
#define FindAndRemoveTraps(x) x->query_skill(SS_FR_TRAP)

/* Room specific things */

#define Exit(where,dir) add_exit(STD_DIR+where,dir,0)
#define North(where) add_exit(STD_DIR+where,"north",0)
#define East(where) add_exit(STD_DIR+where,"east",0)
#define West(where) add_exit(STD_DIR+where,"west",0)
#define South(where) add_exit(STD_DIR+where,"south",0)
#define Up(where) add_exit(STD_DIR+where,"up",0)
#define Down(where) add_exit(STD_DIR+where,"down",0)

#define NorthEast(where) add_exit(STD_DIR+where,"northeast",0)
#define SouthEast(where) add_exit(STD_DIR+where,"southeast",0)
#define NorthWest(where) add_exit(STD_DIR+where,"northwest",0)
#define SouthWest(where) add_exit(STD_DIR+where,"southwest",0)

#define Item(what,desc) add_item(what,desc)
#define Itemn(what,desc) add_item(what,desc+"\n")
#define Exa(what,desc) add_exa(what,desc)
#define Exan(what,desc) add_exa(what,desc+"\n")
#define CmdItem(what,how,desc) add_cmd_item(what,how,desc)
#define Cmd(what,how,desc) add_cmd_item(explode(what,","),explode(how,","),desc)


#endif
