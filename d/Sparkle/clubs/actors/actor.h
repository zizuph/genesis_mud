/*
 * Some actor's club definitions
 *
 * Updated for the Genesis -> Sparkle move 2005.
 * Updates and move by Lunatari.
 *
 * 2008-02-18 : Lunatari
 * + Added WIZ_MANAGER to the IS_WIZ Macro.
 * + Changed AC_CENTRAL back to central.c so that the new 
 *   code will actually work.
 */
#define AC_DIR       "/d/Sparkle/clubs/actors/"
#define AC_SAVES     (AC_DIR+"var/")
#define AC_OBJS      (AC_DIR+"obj/")
#define AC_LOGS      (AC_DIR+"log/")
#define AC_ROOMS     (AC_DIR+"room/")

#define AC_IBOARD    (AC_OBJS+"iboard")
#define AC_EBOARD    (AC_OBJS+"eboard")
#define AC_IBOARDVAR (AC_SAVES+"iboard")
#define AC_EBOARDVAR (AC_SAVES+"eboard")
#define AC_SYMBOL    (AC_OBJS+"symbol")
#define AC_MEMBERS   (AC_SAVES+"members")
#define AC_EXPELLED  (AC_SAVES+"expelled")
#define AC_REMOVED   (AC_SAVES+"removed")
#define AC_SUGGESTED (AC_SAVES+"suggested")
#define AC_INVITED   (AC_SAVES+"invited")
#define AC_UNINVITED (AC_SAVES+"uninvited")
#define AC_CENTRAL   (AC_DIR+"central")
#define AC_CLUB	     (AC_ROOMS+"club")
#define AC_INNER     (AC_ROOMS+"inner")
#define AC_INNER2    (AC_ROOMS+"new_inner")
#define AC_HELP	     (AC_DIR+"help/")
#define AC_TOKEN     "_genesis_actor_symbol_"
#define AC_LOG	     (AC_LOGS+"events.log")
#define CONFIRM_LOG  (AC_LOGS+"confirm.log")
#define EMOTE_LOG    (AC_LOGS+"emote/")
#define ATTEND_LOG   (EMOTE_LOG+"ATTEND")
#define ATTEND_NAME  "ATTEND"
#define WIZ_MANAGER  "lunatari"
#define WIZM_PROP    "_notify_actor"

// Inidices in the control array
#define AC_TIME	 0
#define AC_NLIST 1
#define AC_RANK	 2
#define AC_LAST	 3
#define AC_RCH	 4

// Reasons for removal of membership
#define REASON_NONE	0
#define REASON_RESIGN	1
#define REASON_WIZ	2
#define REASON_VANISHED	3

// Ranks
#define AC_RANK_NAMES ({ \
    "Hypokritos",\
    "Performer",\
    "Actor",\
    "Dramathurgian",\
    "Thespian", \
    "Esteemed Thespian" })

/* As of 2008-02-21 only Actor rank aka MEMBER_RANK
 * is the one that will be of any "use" the rest will
 * be just names/memory of a long gone time. */
#define EMOTE_RANK	1
#define MEMBER_RANK	2
#define TRUSTED_RANK	3
#define ADMIN_RANK	4
#define HONOURED_RANK	5

#define MAX_RANK	4

#define INVITE_MIN	3
#define INVITE_MOD	({ 0, 0, 1, 1, 1, 1, })
#define DEMOTE_MIN	6
#define DEMOTE_MOD	({ 0, 0, 1, 1, 1, 1, })

/* These are not used */
#define PROMOTE_MIN     10	
#define PROMOTE_MOD	({ 0, 0, 1, 1, 3, 1, })
#define HONOUR_MIN	10

#define INVITE_PROP	"_actor_invite_name"
#define IN_SANCT_PROP	"_actor_sanctum_name"
#define DEMOTE_PROP	"_actor_demote_name"
#define PROMOTE_PROP	"_actor_promote_prop"
#define HONOUR_PROP	"_actor_honour_prop"
#define LEAVE_PROP	"_actor_leave"

#define TP		this_player()

#define FIND_SYMBOL(ob)	    (present(AC_TOKEN, (ob)))
#define QUERY_LEVEL(ob)	    (AC_CENTRAL->query_level((ob)->query_real_name()))
#define CHECK_MEMBER(ob)    (AC_CENTRAL->query_member((ob)->query_real_name()))
#define QUERY_LEVEL_N(who)  (AC_CENTRAL->query_level(who))
#define CHECK_MEMBER_N(who) (AC_CENTRAL->query_member(who))
#define IS_MANAGER(ob)      (ob->query_real_name() == WIZ_MANAGER)
#define IS_WIZ(ob)    	    (SECURITY->query_wiz_rank((ob)->query_real_name()) > WIZ_LORD || SECURITY->query_wiz_dom((ob)->query_real_name()) == creator(this_object()) || (ob->query_real_name() == WIZ_MANAGER))
