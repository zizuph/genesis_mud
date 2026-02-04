/** guild_defs.h **/

/*
 * Handy definitions, shared by every file in the guild.
 * Cedric 3/93
 *
 * Updated by Arman 11/8/2019
 */

/*
 * SG_INSTRUMENTAL      The instrumental skill..how well can s/he play?
 * SG_READ_MUSIC        The ability to read music..namely, the Songs of Power.
 * SG_VOCAL             The vocal skill..how well can s/he sing?
 * SG_TUNE_REPAIR       The ability to tune/repair one's instrument.
 * 
 * MUSE         The number of the player's Muse:
 *                          1) Thalia       Comedy
 *                          2) Calliope     Epic poetry
 *                          3) Melpomene    Tragedy
 *                          4) Clio         History
 *
 * SG_FAKE_SKILL        A hack used within the song code.
 * SG_VOCAL_DAMAGE      The damage level of the player's voice. 0=healthy.
 * SG_FLAG              Several flags compounded into one integer:
 *                      Bells, Ballads, Dais, Mood, and Muse.
 */

#define BS(message)     break_string(message,76)
#define TP              this_player
#define TO              this_object
#define TI		this_interactive
#define NF(xx)          notify_fail(xx)
#define CM(xx)          catch_msg(xx)

#define GUILD                 "/d/Terel/cedric/guild/"
#define NEW_GUILD             "/d/Terel/guilds/minstrels/"
#define NEW_GUILDOBJ          (NEW_GUILD + "obj/")
#define GUILDOBJ              GUILD+"Obj/"
#define MINSTREL_OBJ          (GUILD + "obj/")
#define MINSTREL_SOUL         (NEW_GUILD + "soul/")
#define GUILDNPC              GUILD+"Npcs/"
#define GUILDTEXT             GUILD+"Text/"
#define GUILDLOG	      GUILD+"Log/"
#define MINSTREL_HELP_DIR     (NEW_GUILD + "help/")
#define MINSTREL_LOG          (GUILD + "log/")
#define MINSTREL_DATA         (NEW_GUILD + "data/")
#define MINSTREL_LIB          (NEW_GUILD + "lib/")
#define MINSTREL_NEW_LOG      (NEW_GUILD + "log/")
#define MIN_SPELLS            (NEW_GUILD + "spells/")
#define M_GUILDLOG            M_GUILD+"Log/" 
#define SONG_ROOT             (GUILD + "songs/")
#define GUILDSOUL	      NEW_GUILD+"soul/soul"
#define GUILDSHADOW           NEW_GUILD+"shadow/m_shadow"
#define CYCLE_SOUL            (MINSTREL_SOUL + "cycle_soul")
#define SONG_INDEX            (MINSTREL_LIB + "song_index5")
#define SONGBOOK_MANAGER      (MINSTREL_LIB + "songbook_manager")
#define MEMBER_MANAGER        (MINSTREL_LOG + "member_manager")
#define PERFORM_MANAGER       (MINSTREL_LIB + "performance_manager")
#define LOGFILE		      GUILDLOG+"members"
#define M_LOGFILE             M_GUILDLOG+"members"
#define LEAVE_LOG             GUILDLOG + "leave.log"
#define JOIN_LOG              GUILDLOG + "join.log"
#define TOP_MUNDANE_LOG       (MINSTREL_NEW_LOG + "top_twenty_mundane.txt")

#define GUILD_NAME      "The August Order of Minstrels"

// GUILD_SHORT_NAME - the short name of the guild as listed in the
// guild registry
#define GUILD_SHORT_NAME "minstrel"

#define GUILDMASTER     "arman"
#define GUILDMASTERJR	"armanjr"
#define ASSISTANT       "cedric"
#define ASSISTANT1      "horatio"
#define CYCLE_POSITION_EMPTY "NONE"

#define COMMITTEE_SIZE	4
#define COMMITTEE_FILE	(GUILD+"committee")
#define GUILD_TAX	17

#define MINSTREL_GUILD_OBJECT    (NEW_GUILDOBJ + "songbook")

#define STOREROOM	(GUILD+"storeroom")
#define OFFICE		(GUILD+"office")

#define MEMBER(xx)      xx->query_guild_member(GUILD_NAME)
#define OPP_MEMBER(xx)  xx->query_guild_member(OPP_GUILD_NAME)

#define IS_PERFORMER(x) PERFORM_MANAGER->query_is_member(x)
#define REPUTATION(x)   PERFORM_MANAGER->query_reputation_level(x)
#define MINOR_LOC       1
#define AVERAGE_LOC     2
#define PROMINENT_LOC   3
#define WELL_KNOWN_LVL  6
#define MIN_PERFORMING  "_minstrel_currently_performing"
#define NEXT_PERFORM    "_minstrel_next_performance"
#define LAST_PERFORMED  "_minstrel_last_performed_here_"
#define FIFTEEN_MINUTES 900
#define TWENTY_HOURS    72000

// Experience gained from performing at a venue. At superior guru 
// max success is 497, so max possible general xp gain is 12,425gxp
// (which is less than the xp for killing a 60 stat avg mob).
// This function is called in the ~obj/performance_obj.c file.

#define F_EXP_PERFORM(success) (250 + (25 * (success)))

#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define MANA_SHADOW           "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define DEBUG(x)	     find_player("arman")->catch_msg("[Min] " + x + "\n")


#define SG_INSTRUMENTAL 130050
#define SG_VOCAL        130051
#define SG_READ_MUSIC   130052
#define SG_TUNE_REPAIR  130053

#define SG_FAKE_SKILL   	130055
#define SG_VOCAL_DAMAGE 	130056
#define SG_FLAG         	130057
#define SG_NATURAL_VOICE	130058

#define MINSTREL_I_VOICE_TRAINING "_minstrel_i_voice_training"
#define MINSTREL_I_VOLUME "_minstrel_i_volume"
#define LOUD 1
#define SOFT -1

#define MUSE1           "Thalia"
#define MUSE2           "Calliope"
#define MUSE3           "Melpomene"
#define MUSE4           "Clio"

#define MUNDANEDIR      GUILD+"Mundanes/"
#define BALLADDIR       GUILD+"Ballads/"
#define POWERDIR        GUILD+"Power/"
// #define POWER_SONGS_DIR  (GUILD + "Power/")
#define POWER_SONGS_DIR  (NEW_GUILD + "spells/")
#define MUNDANE_SONGS_DIR (SONG_ROOT + "mundane/")
#define BALLAD_SONGS_DIR  (SONG_ROOT + "ballad/")
#define BALLAD_SONGS_SUBMISSION_DIR (BALLAD_SONGS_DIR + "submissions/")
#define EPIC_SONGS_DIR    (SONG_ROOT + "epic/")
#define SUBMITDIR       GUILD+"Submit/"
#define BANISHDIR	GUILD+"Banished/"
#define DEMOTEDIR	GUILD+"Demote/"
#define PROMOTEDIR	GUILD+"Promote/"
#define REJECTDIR	GUILD+"Reject/"
#define AWARDDIR	GUILD+"Award/"

#define IS_MUNDANE(title) wildmatch(MUNDANE_SONGS_DIR + "*", title)
#define IS_BALLAD(title)  wildmatch(BALLAD_SONGS_DIR + "*", title)
#define IS_EPIC(title)    wildmatch(EPIC_SONGS_DIR + "*", title)
#define IS_POWER(title)   wildmatch(POWER_SONGS_DIR + "*", title)

/* note: skipping countertenor for now */
#define MALEVOICES "basso profundo", "basso", "baritone", "tenor"
#define FEMALEVOICES "contralto", "alto", "mezzo soprano", "soprano"
   
    
/*
 * A few definitions added by Horatio.  10.15.93
 */

#define return_fail(x);         {notify_fail(x); return 0;}
#define fetch(x)                clone_object(x)->move(this_object())

/*============
 *           |
 *   FLAGS:  |
 *           |
 * ===========
 *
 *
 */

#define MOODMASK        15
#define BELLMASK        16
#define DAISMASK        32
#define BALLADMASK      64
#define MUSEMASK        896     /* 128+256+512 ... three consecutive bits */
#define MUSEMASKBASE    128     /* lowest bit in the series               */

/*
 * Moods:  :-) :-| :-( |-) ;-) |-| (-) )-|
 */
#define RANDOM      	0
#define SERIOUS     	1
#define JOVIAL      	2
#define BRAVE       	3
#define CONVERSE    	4
#define SAD         	5
#define ANGRY       	6
#define SONG        	7
#define SARCASTIC   	8
#define NEUTRAL		9
#define ROMANTIC	10
#define SECRETIVE	11
#define PLAINTIVE	12
#define CAREFREE	13
#define OBSERVANT	14
#define IMPATIENT	15
#define HAUGHTY		16


#define GUILD_FUNS			(GUILD + "guild_funs")
#define PARSE_SONG(t,w,n,b,e,p)	  	GUILD_FUNS->parse_song(t,w,n,n,e,p)
#define CAP_TITLE(s)			GUILD_FUNS->cap_title(s)
#define ON_LINE()			GUILD_FUNS->on_line()
#define BOOK_RESET()			GUILD_FUNS->book_reset()
#define COMMENT_FILTER(s) 		GUILD_FUNS->comment_filter(s)
#define QUERY_BANISHED(s)		GUILD_FUNS->query_banished(s)
