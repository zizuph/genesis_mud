/*
 * /d/Gondor/common/dwarf_guild/titles.h
 *
 * This file contains the defines with the titles and beard descriptions
 * possible for members of the Rockfriend guild.
 *
 * /Mercade, 28 October 1994
 *
 * Revision history:
 */

/* NUM_TITLES should define the number of titles possible, as they are
 * defined in BEARD_DESCRIPTIONS and TITLES. Those defines should contain
 * exactly that much descriptions and titles.
 */
#define NUM_TITLES    43

/* Everyone with SS_RACE >= MAX_SS_RACE will get the maximum title.
 */
#define MAX_SS_RACE   90

/* The possible descriptions for a beard of a Rockfriend. The number of
 * descriptions must equal the number of titles possible and it must
 * also equal the number set in NUM_TITLES.
 */
#define BEARD_DESCRIPTIONS     \
    ({ "fake",                 \
       "stubbly",              \
       "meaningless",          \
       "awkward",              \
       "daringly short",       \
       "farcical",             \
       "witty",                \
       "knotted",              \
       "wavy",                 \
       "funny",                \
       "smooth",               \
       "fantasy",              \
       "prudish",              \
       "curly",                \
       "full and broad",       \
       "modern",               \
       "medium sized",         \
       "lovely",               \
       "heavy",                \
       "challenging",          \
       "fashionable",          \
       "pronounced",           \
       "well groomed",         \
       "cultivated",           \
       "attractive",           \
       "charming",             \
       "long, forked",         \
       "pompous",              \
       "stylish",              \
       "handsome",             \
       "long, braided",        \
       "noble",                \
       "beautiful",            \
       "gallant",              \
       "wonderful",            \
       "splendid",             \
       "proud",                \
       "brilliantly modelled", \
       "state of the art",     \
       "fantastic",            \
       "astonishing",          \
       "magnificent",          \
       "majestic",             \
    })

/* This define contains the strlen() of the longest title in the TITLES
 * define.
 */
#define LONGEST_TITLE 13

/* The possible titles for the members of the Rockfriend guild. The number
 * of titles must equal the number of descriptions possible for beards and
 * it must also equal the number set in NUM_TITLES.
 */
#define TITLES          \
    ({ "Adopted",       \
       "Farcical",      \
       "Ignorant",      \
       "Inexperienced", \
       "Layman",        \
       "Junior",        \
       "Acolyte",       \
       "Apprentice",    \
       "Moderate",      \
       "Benevolent",    \
       "Capable",       \
       "Talented",      \
       "Skilled",       \
       "Chauvinistic",  \
       "Audacious",     \
       "Dignified",     \
       "Remarkable",    \
       "Attentive",     \
       "Gallant",       \
       "Determined",    \
       "Achieving",     \
       "Creative",      \
       "Respected",     \
       "Distinguished", \
       "Honourable",    \
       "Seasoned",      \
       "Famous",        \
       "Qualified",     \
       "Courageous",    \
       "Devoted",       \
       "Heroic",        \
       "Professional",  \
       "Leading",       \
       "Noble",         \
       "Proud",         \
       "Great",         \
       "Master",        \
       "Experienced",   \
       "Superior",      \
       "Senior",        \
       "Genius",        \
       "Elder",         \
       "Mighty",        \
    })
