/*
 *	This file is obsolete and has been replaced by
 *	/d/Gondor/common/lib/herbsearch.c
 *
 *	Please do not use this file anymore and replace it
 *	in old code!
 */
/*
 * Herbsearch.h
 * This file is included in rooms where herbs grow.
 * The file contains the search-function of the room.
 * Elessar, Gondor. Oct 92.
 *
 * Modification log:
 * 06-jan-1994: Olorin
 *   Changed herb_search so it is no possible to 
 *   'search <place> for <herb name>  following a suggestion by Falke
 *   (Works only with modified search_for_herb in /std/room/description)
 *              
 */

/*
 * Functions: set_search_places(string *places)
 * Description: sets the place(s) where the herb grows in the room.
 *   The player must then type 'search <place> for herbs' to search.
 *   If not set, it defaults to 'ground' and 'here'.
 */
#include "/d/Gondor/common/lib/herbsearch.h"

