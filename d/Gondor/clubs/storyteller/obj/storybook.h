/*
 * /d/Gondor/clubs/storyteller/obj/storybook.h
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 */

#ifndef STORYBOOK_DEFINITIONS
#define STORYBOOK_DEFINITIONS

#define	STORYBOOK_NAME	"Storyteller's Book"

/* values for the format chars */
#define	BLANK		""	/* comment line			*/
#define	NEWLINE		"\n"	/* comment line			*/
#define	COMMENT		"#"	/* comment line			*/
#define	EMOTE_PROC	"+"	/* emote w/ name processing	*/
#define	EMOTE		"&"	/* emote style line		*/
#define	ATMOS_PROC	"-"	/* atmos w/ name processing	*/
#define	ATMOS		"@"	/* room atmosphere style line	*/
#define	ALARM		"="	/* end of this alarm block	*/

#define	STR_POSSESSIVE	"POS"	/* possessive */
#define	STR_PRONOUN	"PRO"	/* nominative */
#define	STR_OBJECTIVE	"OBJ"	/* objective  */
#define	STR_NAME	"NAM"	/* name or "the <nonmet desc>" */

#define	MAX_NO_MREAD	50	/* use "more" on stories longer than this */


#define	MIN_ALARM	4.0	/* minimum delay between sections */
#define	DEFAULT_ALARM	8.0	/* default ... */
#define	MAX_ALARM	30.0	/* max ... */

#ifndef STORYT_DIR
#include "/d/Gondor/defs.h"
#endif /* !STORYT_DIR */

#define STORIES_DIR	(STORYT_DIR + "stories/")
#define TELLERS_DIR     (STORYT_DIR + "tellers/")
#define	ARCHIVE		(STORYT_DIR + "rooms/test_archive")

#endif /* STORYBOOK_DEFINITIONS */
