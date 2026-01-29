#define COUNCIL (CRPALACE_TEXTS+"council")
#define COUNCIL_CODE (CRPALACE_SPECIALS+"council_code")


/* council action "skills" */

#define PUNISHMENT 114002    /* for disciplining erring Calians */
#define REWARD 114003         /* increased when members show a special
                                 evidence of Calian qualities such as
                                 loyalty to guild, bravery etc.  */

/* punishments / rewards unique id numbers */

#define NO_PUNISHMENT 0
#define REMOVE_PUNISHMENTS 1
#define NO_SANCTUARY 2
#define NO_SWARM 3
#define NO_TRAINING 4
#define EXPULSION 5
#define ADD_REWARD 6
#define DISCHARGED 7

// The above punishments (first 3 bits) can only be done one at a time.
// The punishments below can all be done concurrently because each punishment
// owns a specific "bit".
#define NO_TUNNEL_ACCESS 8
#define NO_VOTE 16
#define NO_RACK 32

/* reward subloc */
#define CALIA_REWARD "_calia_reward"

/* council max size */
#define COUNCIL_MAX_SIZE 3

/* Team object */
#define CALIAN_TEAM_OBJ "_calian_team_obj"

