/*
 * lib.h
 *
 * This is the include file to use the functions defined in
 * /d/Immortal/rogon/lib/lib.c
 *
 * Interesting things are:
 *	LCAP(str) which is a late capitalizion routine.
 *	LBS(str) which is a late break string routine.
 *	LS_BS(str) which is a 'smart' late break string routine.
 *
 * The macros defined by the letter V first stands for 'vbfc'-funs.
 * These are better to use than HE_SHE() etc. if you are not sure
 * if the object is itself or not.
 *
 */

#ifndef _ROGON_LIB_FILE_H_
#define _ROGON_LIB_FILE_H_

#include <cmdparse.h>
/*
 * Replacing definitions.
 */

#ifndef LIB_FILE
#define LIB_FILE "/d/Shire/healers/lib/lib"
#endif

#define REPLACE_STRINGS(what, from, to) \
    (STRING_FILE->replace_strings(what, from, to))
#define REPLACE(arg) \
    REPLACE_STRINGS(arg, ({ "@@", "|", ":" }) , ({ "&&", "%%", ";" }))
#define REPLACE_BACK(arg) \
    REPLACE_STRINGS(arg, ({ "&&", "%%", ";" }), ({ "@@", "|", ":" }))

#define FNAME(ob) \
    (string)LIB_FILE->file_name(ob)

/*
 * Filters
 */

#define FILTER_SEES_FIGHT(arr)	filter(arr, "sees_fight", LIB_FILE)

/*
 * Vbfc's definitions.
 */

#define LIB_VBFC(func) \
    "@@" + func + ":" + LIB_FILE + "@@"
#define LIB_VBFC1(func, arg) \
    "@@" + func + ":" + LIB_FILE + "|" + arg + "@@"
#define LIB_VBFC2(func, arg1, arg2) \
    "@@" + func + ":" + LIB_FILE + "|" + arg1 + "|" + arg2 + "@@"
#define LIB_CALL(func, ob)  \
    LIB_VBFC1(func, FNAME(ob))

/*
 * For tellem.
 */

#define T_SYNTAX(str, subj, obj)    (string)TELL_FILE->tellem_format(str, subj, obj)
#define T_SUBJ(str, subj)	    (string)TELL_FILE->tellem_format(str, subj)
#define T_TP(str)		    (string)TELL_FILE->tellem_format(str, this_player())
#define T_OBJ(str, obj)		    (string)TELL_FILE->tellem_format(str, this_player(), obj)

#define TELL_S(x)	"{" + x + "}"
#define TELL_SO(x,y)	"{" + x + ";" + y + "}"
#define TELL_SOW(x,y,z) "{" + x + ";" + y + ";" + z + "}"
#define TELL_SW(x)	"{" + x + ";;*}"
#define TELL_SW2(x,y)	"{" + x + ";" + y + ";*}"

#define LCAP(str)	LIB_VBFC1("late_cap", REPLACE(str))
#define LBS(str)	LIB_VBFC1("late_break", REPLACE(str))
#define LBSL(str, len)	LIB_VBFC2("late_break", REPLACE(str), len)

#define S_BS(str)	LIB_FILE->smart_break_string(str)
#define S_BSL(str, len)	LIB_FILE->smart_break_string(str, len)

#define BRK(str)	LIB_VBFC1("late_smart_break", REPLACE(str))
#define BRKN(str, len)	LIB_VBFC1("late_smart_break", REPLACE(str), len)

#define VPOSS(ob)	LIB_CALL("vbfc_possessive", ob)
#define VCPOSS(ob)	LIB_CALL("vbfc_cap_possessive", ob)
#define VHE_SHE(ob)	LIB_CALL("he_she", ob)
#define VCHE_SHE(ob)	LIB_CALL("cap_he_she", ob)
#define VHIM_HER(ob)	LIB_CALL("him_her", ob)
#define VCHIM_HER(ob)	LIB_CALL("cap_him_her", ob)
#define VHIS_HER(ob)	LIB_CALL("his_her", ob)
#define VCHIS_HER(ob)	LIB_CALL("cap_his_her", ob)
#define VTNAME(ob)	LIB_CALL("qtname", ob)
#define VCTNAME(ob)	LIB_CALL("qctname", ob)
#define VCSELF(ob)	LIB_CALL("cap_self", ob)
#define VSELF(ob)	LIB_CALL("self", ob)

#define VEND(for_oth, for_obj, obj)	\
    "@@ending:"+LIB_FILE+"|"+for_oth+"|"+for_obj+"|"+FNAME(obj)+"@@"

#define V_ARE(ob)	VEND("is", "are", ob)
#define V_IS(ob)	VEND("are", "is", ob)
#define V_HAS(ob)	VEND("have", "has", ob)
#define V_HAVE(ob)	VEND("has", "have", ob)

#define V_NO_S(ob)	VEND("s", "", ob)
#define V_NO_ES(ob)	VEND("es", "", ob)
#define V_NO_IES(ob)	VEND("ies", "y", ob)

#define V_FOR(ob, str)	\
    "@@for_object:"+LIB_FILE+"|"+REPLACE(str)+"|"+FNAME(ob)+"@@"

#define FOR_TP(str)    V_FOR(this_player(), str)
#define FOR_TO(str)    V_FOR(this_object(), str)

#define V_FOR2(ob, str_for, str_other) \
    "@@for_object:"+LIB_FILE+"|"+REPLACE(str_for)+"|"+ \
    FNAME(ob)+"|"+REPLACE(str_other)+"@@"

#define V_ALT(str1, str2, str3, subj, obj) \
    "@@alternative_form:" + LIB_FILE + "|" + REPLACE(str1) + "|" + \
    REPLACE(str2)+ "|" + REPLACE(str3) + "|" + FNAME(subj) + "|" + \
    (objectp(obj) ? FNAME(obj) : 0) + "@@"

#define VTP_OBJ(s1, s2, s3, obj)	V_ALT(s1, s2, s3, this_player(), obj)
#define AS_SUBJ       "*"
#define AS_OBJ	      "**"

#define VVERB(str, who)	LIB_VBFC2("do_verb", str, FNAME(who))
#define VERB(str)	VVERB(str, this_player())

#define COMP_QTNAME(obs)	LIB_FILE->composite_live(obs)
#define COMP_YOURSELF(obs)	LIB_FILE->composite_live(obs, "yourself")

#define QLIVE		LIB_VBFC("fo_composite_live")

#define VOBJECTS(obj) \
    (V_FOR2(COMPOSITE_DEAD(obj), QCOMPDEAD))

#endif
