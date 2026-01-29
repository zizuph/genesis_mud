/*
 * - /sys/basic.h
 *
 *  A file to hold simple, commonly used defines in one place
 *  rather then have them repeatedly spread throughout the mud.
 */
#ifndef __SYS_BASIC__
#define __SYS_BASIC__

#ifndef TP
#  define TP	this_player()
#endif
#ifndef TO
#  define TO	this_object()
#endif
#ifndef TI
#  define TI	this_interactive()
#endif

#ifndef NF
#  define NF	notify_fail
#endif
#ifndef ENV
#  define ENV	environment
#endif
#ifndef CAP
#  define CAP	capitalize
#endif
#ifndef LC
#  define LC	lower_case
#endif

#ifndef LS
#  define LS	LANG_SHORT
#endif
#ifndef LAS
#  define LAS	LANG_ASHORT
#endif
#ifndef LTS
#  define LTS	LANG_THESHORT
#endif

#ifndef HE
#  define HE(x)  (x)->query_pronoun()
#endif
#ifndef HIS
#  define HIS(x) (x)->query_possessive()
#endif
#ifndef HIM
#  define HIM(x) (x)->query_objective()
#endif

#ifndef ALTER_PROP
#  define ALTER_PROP(who, what, diff) \
    (who)->add_prop((what), (who)->query_prop(what) + (diff))
#endif
#ifndef ALTER_SKILL
#  define ALTER_SKILL(who, what, diff) \
    (who)->set_skill_extra((what), (who)->query_skill_extra(what) + (diff))
#endif
#ifndef ALTER_STAT
#  define ALTER_STAT(who, what, diff) \
    (who)->set_stat_extra((what), (who)->query_stat_extra(what) + (diff))
#endif

#endif __SYS_BASIC__
