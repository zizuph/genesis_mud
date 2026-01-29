/*
 * definitions.h
 *
 * Definition used mainly by Rogon, perhaps this should be included
 * in domain.h?
 * 
 * Lord Jaypeg - Jan 1999
 * Most of these defs are already used by ~Shire/sys/defs.h
 * Commented out duplicates and including the above.
 *
 */

#ifndef _MORIA_DEFINITIONS_
#define _MORIA_DEFINITIONS_

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

// Added by Lord Jaypeg  - Jan 1999
#include "/d/Shire/sys/defs.h"

// #define TP          this_player()
// #define TO          this_object()
// #define TI          this_interactive()
#define ETP         environment(this_player())
#define ETO         environment()

// #define ENV(x)	    environment(x)
#define INV(x)	    all_inventory(x)

// #define CAP(x)	    capitalize(x)
// #define LOW(x)	    lower_case(x)

// #define HE_SHE(x)   x->query_pronoun()
// #define HIM_HER(x)  x->query_objective()
// #define HIS_HER(x)  x->query_possessive()

#define CHE_SHE(x)  CAP(HE_SHE(x))
#define CHIM_HER(x) CAP(HIM_HER(x))
#define CHIS_HER(x) CAP(HIS_HER(x))

#define STR(x)	    x->query_stat(SS_STR)
#define DEX(x)	    x->query_stat(SS_DEX)
#define CON(x)	    x->query_stat(SS_CON)
#define INT(x)	    x->query_stat(SS_INT)
#define WIS(x)	    x->query_stat(SS_WIS)
#define DIS(x)	    x->query_stat(SS_DIS)

#define ADD_STAT(who, stat, with) \
    who->set_stat_extra(stat, who->query_stat_extra(stat) + with);
// #define ADD_SKILL(who, skill, with) \
//    who->set_skill_extra(skill, who->query_skill_extra(skill) + with);
#define ADD_PROP(who, prop, with) \
    who->add_prop(prop, who->query_prop(prop) + with);
#define ADD_ARRAY_PROP(who, prop, with) \
    if (!who->query_prop(prop)) who->add_prop(prop, with) \
    else who->add_prop(prop, who->query_prop(prop) + with);

#define IS_IN(member, array) \
    (member_array(member, array) == -1)

#define HP(x)	    x->query_hp()
#define MAX_HP(x)   x->query_max_hp()

// #define FIXEUID     setuid(); seteuid(getuid())

#define LIMIT(var, min, max) \
    var = (var < min ? min : var > max ? max : var)

// #define WRITE(x)    this_player()->catch_msg(x)

#endif

