// file name:	     /d/Avenir/include/paths.h
// creator(s):       Denis, Mar'97,
//		     based on /d/Avenir/common/common.h, written by
//		     the original members of Avenir: 1993
// revision history:
// purpose:          To ease the interconnect of different directory
//		     substructures.
// note:             If you feel this file is missing anything, feel free
//                   to discuss it with Avenir's Liege.
#ifndef _AVENIR_PATHS
#define _AVENIR_PATHS
 
#define COM	"/d/Avenir/common/"	/* Common directory     */
#define BAZAAR	(COM + "bazaar/")	/* Seers, Rotbuck & co  */
#define BSEA	(COM + "sea/")		/* Sailing Seas         */
#define CITY	(COM + "city/")		/* Forbidden City       */
#define DEAD	(COM + "dead/")		/* Isle of the Dead     */
#define HOLM	(COM + "holm/")		/* Holm of the Icondite */
#define SEASIDE (COM + "seaside/")      /* Seaside town at Fort */
#define SHIP	(COM + "ships/")	/* Directory for Ships  */
#define VILL	(COM + "village/")	/* Merchants village    */
#define ZIGG	(CITY + "zigg/")	/* Ziggurat             */

/* Utterdark directories */
#define DARK	(COM + "dark/")		/* the Utterdark        */
#define L1	(DARK + "l1/")          /* dark elves + Terel   */
#define L2	(DARK + "l2/")		/* albi, gneiss gnomes  */
#define L3	(DARK + "l3/")          /* imp tunnels          */
#define L4	(DARK + "l4/")		/* ...tunnels...        */
#define L5	(DARK + "l5/")		/* gem ogre tunnels     */
#define HOB	(DARK + "hob/")		/* hobgoblins lair      */
#define LAIR	(DARK + "lair/")	/* worm lair            */

#define OUTPOST	(COM + "outpost/")      /* Fort Sybarus         */
#define OUTPATH	(COM + "outpath/")      /* Ledge to Outpost      */
#define PK	(COM + "park/")	        /* Park Area 1 of Holm  */
#define PORT	(COM + "port/")		/* The Port in the Rift */
#define LEDGE	(COM + "ledge/")	/* Path from Port to Out*/
#define SHIP	(COM + "ships/")	/* Directory for Ships  */

// Guilds.
#define UNION		"/d/Avenir/union/"

// Herbs, Potions, Scrolls
#define HERB		(COM + "herbs/")
#define HERB_MASTER	(HERB + "herb_master")
#define AVHERB		HERB
#define GOHERB		"/d/Gondor/common/herbs/"
#define KRHERB		"/d/Krynn/common/herbs/"
#define SHHERB		"/d/Shire/common/herbs/"
#define TRHERB		"/d/Terel/common/herbs/"
#define GONDOR		GOHERB
#define SHIRE		SHHERB

#define POTION		(COM + "obj/potions/")
#define SCROLL		(COM + "obj/scrolls/")

// Misc. dirs
#define LOG		"/d/Avenir/log/"

#endif  /* _AVENIR_PATHS */
