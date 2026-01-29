/* Stralle @ Genesis 001024
 *
 * The newadmin.h
 */

#ifndef NEW_POT_ADMIN
#define NEW_POT_ADMIN

#define M_AGE     0 /* playerage when joined */
#define M_LAST    1 /* last time logged in */
#define M_PROMO   2 /* promotions recieved */
#define M_PUN     3 /* punishment levels */
#define M_ABSENCE 4 /* Absence for the council */
#define M_SPONSOR 5 /* who sponsored us into the guild */
#define M_GLEV    6 /* Saved guild level (since /secure/finger_player
                     * does not cover skills
                     */
#define M_GAGE    7 /* playerage when we got the current guildlevel */
#define M_QUEST   8 /* Decimal representation of binary guildquests */
#define M_LOCS    9 /* Array of remembered locations for planeswalk */
#define M_CURSIZE 10 /* The current size of the array. If this is !=
                     * to the true array size we automagically pad
                     * it when the priest logs in (init_priest())
                     */
/* Punishment levels */
#define P_SPELLS_RESTRICTED     (1)
#define P_TRAINING_RESTRICTED   (1 << 1)
#define P_TRAVEL_RESTRICTED     (1 << 2)
#define P_EXPELLED              (1 << 3)

#define COUNCIL_IDLE 14 /* Number of days a councilmember can be idle */
#define COUNCIL_SEATS (sizeof(COUNCIL_TITLES))

/* Define this to check for races in the array when trying to join */
#undef RACES_BLOCK ({ "hobbit", "kender", "gnome" })
/* Hobbits are not of this world
 * Takhisis would most likely never take on a kender
 * Gnomes are too busy with their inventions to bother about religion
 */

#endif /* NEW_POT_ADMIN */
