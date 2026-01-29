/*
 * General stuff needed for the steed code
 */
#define	REGISTRY	"/d/Gondor/minas/houses/horseshop"
#define	HORSE		"/d/Rhovanion/elanor/horse"
#define	MEARAS		"/d/Rhovanion/elanor/mearas"
#define	PONY		"/d/Rhovanion/elanor/pony"
#define	WARG		"/d/Rhovanion/elanor/warg"
#define	PEDIGREE	"/d/Gondor/minas/obj/pedigree"
#define	POISON_PATH	"/d/Rhovanion/elanor/hunger_poison"

/*
 * Unique name of hunger poison used in steeds
 */
#define	POISON_ID	"_steed_hunger_poison_"

/*
 * How often to check the steeds age in seconds
 */
#define	CHECK_TIME	300

/*
 * If this is enabled, the horse is aged even when not loaded.
 * This does NOT mean it will age when the player is not logged
 * in!
 */
#undef AGE_IN_STABLE

/*
 * Misc. defines
 */
#define    RIDER_OCC        "The Rohirrim"
#define    RIDER_LAY        "Riders of Rohan"

/*
 * Property stating that the steed quest has been solved THIS LOGIN
 */
#define	STEED_I_QUEST	"_steed_i_quest"
#define STEED_I_BACKPACK "_steed_i_backpack"

/*
 * Properties to block the steed from entering places
 */
#define	STEED_AS_NOT_RIDE	"_steed_as_not_ride"
#define	STEED_AS_NO_ENTER	"_steed_as_no_enter"

#define ROOM_I_IS_STABLE   "_room_i_is_stable"
/*
 * How old can the steed becode, number given as days
 */
#define	BASE_AGE	10
#define	LAYMAN_BONUS	2
#define	OCCUP_BONUS	5
#define	QUEST_BONUS	3
