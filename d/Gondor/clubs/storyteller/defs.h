/*
 * /d/Gondor/clubs/storyteller/defs.h
 *
 */

#ifndef _STORYTELLER_DEFS
#define _STORYTELLER_DEFS

#include "/d/Gondor/defs.h"


#define TELLERS		(STORYT_DIR + "misc/tellers")
#define TELLER_HELP_DIR	(STORYT_DIR + "help/")
#define TELLER_SOUL	(STORYT_DIR + "obj/telsoul")
#define SPECTACLES	(STORYT_DIR + "obj/spectacles")
#define STORYBOOK       (STORYT_DIR + "obj/storybook")
#define ARCHIVES        (STORYT_DIR + "rooms/archives")
#define SPECTACLES_ID   ("Storyteller_Spectacles")
#define KEY_ID		("_StoRyTelLer_kEy_")
#define IS_STORYTELLER(x) (TELLERS->query_member(x->query_real_name()))
#define IS_LIBRARIAN(x) (TELLERS->query_librarian(x->query_real_name()))
#define DRINK_BASE	("/d/Gondor/clubs/storyteller/obj/drink_base")
#define FOOD_BASE	("/d/Gondor/clubs/storyteller/obj/food_base")

#endif /* _STORYTELLER_DEFS */
