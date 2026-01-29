/*
 * Some actor's club definitions
 */

#define AC_IBOARD	"/d/Genesis/clubs/rpg/ac_iboard"
#define AC_EBOARD	"/d/Genesis/clubs/rpg/ac_eboard"
#define AC_SYMBOL	"/d/Genesis/clubs/rpg/ac_symbol"
#define AC_MEMBERS	"/d/Genesis/clubs/rpg/ac_members"
#define AC_EXPELLED	"/d/Genesis/clubs/rpg/ac_expelled"
#define AC_REMOVED	"/d/Genesis/clubs/rpg/ac_removed"
#define AC_CENTRAL	"/d/Genesis/clubs/rpg/ac_central"
#define AC_CLUB		"/d/Genesis/clubs/rpg/ac_club"
#define AC_INNER	"/d/Genesis/clubs/rpg/ac_inner"
#define AC_HELP		"/d/Genesis/clubs/rpg/help/"
#define AC_TOKEN	"_genesis_actor_symbol_"
#define AC_LOG		"/d/Genesis/clubs/rpg/log/ac_log"
#define EMOTE_LOG	"/d/Genesis/clubs/rpg/log/emote/"
#define ATTEND_LOG	"/d/Genesis/clubs/rpg/log/emote/ATTEND"

// Inidices in the control array
#define AC_NAME		0
#define AC_NLIST	1
#define AC_RANK		2

// Reasons for removal of membership
#define REASON_NONE	0
#define REASON_RESIGN	1
#define REASON_WIZ	2
#define REASON_VANISHED	3

// Ranks
#define AC_RANK_NAMES ({ "Hypokritos",\
			 "Performer",\
			 "Actor",\
			 "Dramathurgian",\
			 "Thespian", \
    			 "Esteemed Thespian" })

#define MEMBER_RANK	2
#define TRUSTED_RANK	3
#define ADMIN_RANK	4
#define HONOURED_RANK	5

#define MAX_RANK	4

#define INVITE_MIN	3
#define INVITE_MOD	({ 0, 0, 1, 2, 3, 2, })
#define DEMOTE_MIN	4
#define DEMOTE_MOD	({ 0, 0, 1, 2, 3, 2, })
#define PROMOTE_MIN	3
#define PROMOTE_MOD	({ 0, 0, 1, 2, 3, 2, })
#define HONOUR_MIN	8

#define INVITE_PROP	"_actor_invite_name"
#define IN_SANCT_PROP	"_actor_sanctum_name"
#define DEMOTE_PROP	"_actor_demote_name"
#define PROMOTE_PROP	"_actor_promote_prop"
#define HONOUR_PROP	"_actor_honour_prop"
#define LEAVE_PROP	"_actor_leave"

#define TP		this_player()

#define FIND_SYMBOL(ob)		(present(AC_TOKEN, (ob)))
#define QUERY_LEVEL(ob)		(AC_CENTRAL->query_level((ob)->query_real_name()))
#define CHECK_MEMBER(ob)	(AC_CENTRAL->query_member((ob)->query_real_name()))
#define QUERY_LEVEL_N(who)	(AC_CENTRAL->query_level((who)))
#define CHECK_MEMBER_N(who)	(AC_CENTRAL->query_member((who)))
#define IS_WIZ(ob)    		(SECURITY->query_wiz_rank((ob)->query_real_name()) > WIZ_LORD || SECURITY->query_wiz_dom((ob)->query_real_name()) == creator(this_object()))
