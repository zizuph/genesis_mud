/*
 * File:     kaheda.h
 * Updated:  Cirion, 1998.4.25
 * Purpose:  This file is to contain all the definitions, macros,
 *           and symbolic constants specific to the monks. This
 *           includes directory definitions, skill numbers,
 *           and property names.
 */
#undef KAHEDA

/*******************************************************
 * General guild definitions
 */

// array of the names of the guild masters (who can
// perform administrative commands, receieve
// debugging messages, etc.)
#define MONK_GUILD_MASTERS   ({ "amelia", "cirion", "lilith" })


/*******************************************************
 * General macros
 */
#define BIT(x)      (1 << (x))


/*******************************************************
 * Directory definitions
 */
#define MONK "/d/Genesis/guilds/monks/"
#define MONK_ROOM   MONK + "room/"
#define MONK_LOG    MONK + "log/"
#define MONK_BOARD  MONK + "board/"
#define MONK_SOUL   MONK + "soul/"
#define MONK_SHADOW MONK + "shadow/"
#define MONK_OBJ    MONK + "obj/"
#define MONK_LIB    MONK + "lib/"
#define MONK_NPC    MONK + "npc/"
#define MONK_HELP   MONK + "help/"
#define MONK_DOC    MONK + "doc/"
#define MONK_QUEST  MONK + "quest/"

/*******************************************************
 * Definitions for important objects in the guild
 */
#define MONKLIB       (MONK_LIB + "monklib")
#define MANAGER       (MONK_LIB + "monk_master")
#define ROOMBASE      (MONK_ROOM + "room_base")
#define MONKBOARD     (MONK_OBJ + "board")
#define MONKBOARDPRIV (MONK_OBJ + "board_private")
#define MONK_CTOKEN   (MONK_OBJ + "council_token")

/*******************************************************
 * Definitions for the occupational branch of the guild.
 */
#define MONK_OCC_SOUL     (MONK_SOUL + "soul")
#define MONK_OCC_SHADOW   (MONK_SHADOW + "occupational_shadow")
#define MONK_OCC_EMBLEM   (MONK_OBJ + "emblem")
#define MONK_OCC_STARTLOC (MONK_ROOM + "start")
#define MONK_OCC_STYLE    "fighter"
#define MONK_OCC_TAX      20
#define MONK_OCC_NAME     "Order of the Dragon"
#define MONK_OCC_TYPE     "occupational"

/*******************************************************
 * Definitions for the layman branch of the guild.
 */
#define MONK_LAY_SOUL     MONK_OCC_SOUL
#define MONK_LAY_SHADOW   (MONK_SHADOW + "layman_shadow")
#define MONK_LAY_EMBLEM   MONK_OCC_EMBLEM
#define MONK_LAY_STARTLOC MONK_OCC_STARTLOC
#define MONK_LAY_STYLE    "fighter"
#define MONK_LAY_TAX      12
#define MONK_LAY_NAME     MONK_OCC_NAME
#define MONK_LAY_TYPE     "layman"

/*******************************************************
 * Definitions for skill numbers used by the guild
 */
#define MONK_SKILL_FOCUS  147001
#define MONK_SKILL_STRIKE 147002
#define MONK_SKILL_PLEXUS 147003

/*******************************************************
 * Definitions for properties used by the guild
 */
#define MONK_I_BUSY "_kahedan_i_busy"
#define MONK_AM_BLESSED "_dragon_monk_am_blessed"
#define MONK_HAS_WARNED "_dragon_monk_has_warned"

/*******************************************************
 * Definitions for special object IDs
 */
#define MONK_PLEXUS_STUN_ID "monk_plexus_stun"

/*******************************************************
 * Voting symbolic constants
 */

// may only vote for people
#define M_VOTE_PEOPLE              BIT(2)
// only members may vote
#define M_VOTE_MEMBERS_ONLY        BIT(3)
// may only vote yae or nae
#define M_VOTE_YESNO               BIT(4)
// wizards may not vote
#define M_VOTE_DISALLOW_WIZARDS    BIT(5)
// may not vote for yourself
#define M_VOTE_NO_SELF             BIT(6)
// voting list is anonymous
#define M_VOTE_ANONYMOUS           BIT(7)
// cannot see the results of the vote
#define M_VOTE_NO_SHOW             BIT(8)
// only council members may participate
#define M_VOTE_COUNCIL_ONLY        BIT(9)
// only council members or elders may participate
#define M_VOTE_COUNCIL_ELDER_ONLY  BIT(10)


/*******************************************************
 * Punishment symbolic constants
 */
// player may not train skills
#define M_PUNISH_NOTRAIN           BIT(2)
// player may not start at the order
#define M_PUNISH_EXILE             BIT(3)
// player is banished from the guild, and will be removed at
// next login
#define M_PUNISH_BANISH            BIT(4)
// player may not buy anything from NPCs in the guild
#define M_PUNISH_NOBUY             BIT(5)
// player has a disgraced title
#define M_PUNISH_DISGRACE          BIT(6)
// player cannot vote
#define M_PUNISH_NOVOTE            BIT(7)


/*******************************************************
 * General symbolic constants
 */
#define MONK_GUILD_STATE_OPEN        1
#define MONK_GUILD_STATE_CLOSED     -1

// stub until we get a guru quest
#define MONK_TRAIN_GURU(who)         (0)

// constant for no council token
#define MONK_TOKEN_NONE       "TOKEN_NONE"

// idle applications will be automatically be deleted
// after 2 months (after which rejected applicants
// may re-apply).
#define MONK_APPLICATION_MAX_TIME   (60 * 60 * 24 * 30 * 2)

// this defines the maximum number of council members
// the monks may have. If the current number of council
// members ever falls below this number, a vote is
// automatically started to elect a new council member
#define MONK_MAX_COUNCIL_MEMBERS     3
#define MONK_MAX_ELDERS              10


// number of seconds between strike attacks
#define MONK_STRIKE_DELAY            8

// pen for the "strke" attack
#define F_MONK_STRIKE_PEN(str, strike)                                    \
        (F_PENMOD(W_HAND_PEN + F_UNARMED_PEN(strike, str), strike))

// delay of 8 seconds for skills of 100
#define F_MONK_STRIKE_DELAY(strike, dex, wis)  \
        (2400 / (strike + dex + wis))

#define F_MONK_PLEXUS_STUN_MIN_DURATION  5

// number of seconds between plexus attacks
// This define is no longer used -- F_MONK_PLEXUS_STUN_DURATION
// is used instead.
//#define MONK_PLEXUS_DELAY            8

// Minimum interval between when something can be stunned
#define MONK_PLEXUS_STUN_MIN_INTERVAL 40


// support for making it so monsters have a minimum respite
// of 12 seconds between plexuses (so we don't have multiple
// monks overlapping their plexuses).
#define MONK_I_LAST_PLEXXED           "_monk_i_last_plexxed"
#define MONK_PLEXUS_MIN_INTERVAL      8

// duration of stun for the "plexus" attack
#define F_MONK_PLEXUS_STUN_DURATION(plexus, str)      \
        (((plexus) + (str) - random(20) + random(20)) / 20)

// the max amout of time someone can stun for (for the
// tax-calc formulas below)
#define F_MONK_PLEXUS_MAX_STUN_DURATION(plexus, str)      \
        (10)

// delay of 20 seconds for skills of 100
#define F_MONK_PLEXUS_DELAY(plexus, con, wis)   \
        ((6000 / (plexus + con + wis)) + random (10) - random (10))

// duration for which we can be focused. The longer it has
// bin since the last time we were in the focus means that
// we can stay in this one much longer. Max 200 seconds.
#define F_MONK_FOCUS_DURATION(skill, last_focus)  \
        ( ((MIN(((time() - last_focus) / 60), 100)) * (skill * 2)) / 100 )

// a focus of 100 gives special attacks 133% potency
#define F_MONK_FOCUS_COMBAT_BONUS(skill)    \
        (skill / 3)


// the minimum amount of time focus can last for us to be
// able to enter it.
#define MONK_FOCUS_MIN_DURATION  10
#define MONK_FOCUS_MANA_COST     40
#define MONK_FOCUS_FATIGUE_COST  10

// hit factors for hit_me in special attacks
#define MONK_PLEXUS_HIT       85
#define MONK_STRIKE_HIT       90

// on empirical execution of the command:
/*
exec int i, j, plex_hit = 80; int num_hits = 0; int num_tests = 1000; object a
, arm, wep; a = clone_object ("/std/monster");  for (i = 0; i < 100; i++) { a->s
et_skill (i, 100); a->set_stat (i, 100); } wep = clone_object ("/std/weapon"); w
ep->set_hit(35); wep->set_pen (35); wep->set_wt(W_SWORD); arm = clone_object ("/
std/armour");  arm->set_at (A_BODY | A_ARMS | A_LEGS | A_HEAD); arm->set_ac (60)
; a->move (environment (find_living ("cirion"))); a->wear_arm (arm); a->wield (w
ep); a->command ("wear all"); a->command ("wield all"); for (j = 0; j < num_test
s; j++) {  if (a->query_combat_object ()->cb_tohit (W_ANYH, plex_hit, a) > 0) nu
m_hits++; } return num_hits * 100 / num_tests;
*/
#define F_MONK_PLEXUS_HIT_CHANCE  74

// duration of an average combat round in seconds
#define COMBAT_ROUND_DURATION       5

// the pen of the best non-magical weapon
#define F_STD_WEAPON_BEST_PEN       280

// the ac of the best non-magical armour
#define F_STD_ARMOUR_BEST_AC        40

#define MF_PL_SDUR(skill, stat) (itof (F_MONK_PLEXUS_MAX_STUN_DURATION(skill, stat)))
#define MF_CRND  (itof (COMBAT_ROUND_DURATION))
#define MF_PL_DEL(skill, stat) (itof (F_MONK_PLEXUS_DELAY(skill, stat, stat)))
#define MF_PL_HIT ((itof(F_MONK_PLEXUS_HIT_CHANCE)) / 100.0)

#define F_MONK_COMBAT_BONUS_PLEX(skill, stat)    \
    ((MF_PL_SDUR(skill, stat) / MF_CRND) / (MF_PL_DEL(skill, stat) / MF_CRND))    \
    * MF_PL_HIT * 100.0

#define F_MONK_COMBAT_BONUS_PLEX_OCC    \
    F_MONK_COMBAT_BONUS_PLEX(100, 100)

#define F_MONK_COMBAT_TAX_PLEX_OCC \
    (F_MONK_COMBAT_BONUS_PLEX_OCC / (6.0 * 2.0))


