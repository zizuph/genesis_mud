//-*-C++-*-
//               Avenir domain_link.c
// creator(s):   Tepisch Aug 94
// purpose:      Mudlib uses this when Genesis boots & goes down 
// note:         Be VERY careful about the order in which you place
//               preload() files. 
//               Any files which are frequently changed should be put 
//               last, since, if they are buggy or won't load, they will 
//               prevent the loading of all other files following it.
// bug(s):
// to-do:        

#include "/d/Avenir/common/common.h"

inherit "/std/domain_link";

/*
 * Function name: preload_link
 * Description:   Build a list of objects that should be loaded
 *                before the first player enters the game.
 */
public void
preload_link(void)
{
    /* SMIS Manager */
    preload("/d/Avenir/smis/smis_mgr");

    /* For room tells. */
    preload("/d/Avenir/inherit/telltimer");

    /* Ship and shop rooms            */
    preload("/d/Avenir/common/port/port11");
    preload("/d/Avenir/common/port/port12");
    preload("/d/Avenir/common/port/port13");
    preload("/d/Avenir/common/port/port14");
    preload("/d/Avenir/common/port/port15");
    preload("/d/Avenir/common/ships/bazaar/boat_path2");
    preload("/d/Avenir/common/bazaar/intr/d_landing");
    preload("/d/Avenir/common/dark/l4/merchant_store");

    /* Herb master file for herb-containing rooms */
    preload("/d/Avenir/common/herbs/herb_master");
  
    /* Area mappers/handlers           */
    preload("/d/Avenir/common/map/mapper");
 
    /* Guild master objects. */
    preload("/d/Avenir/union/list");
    
    /* Union start room. */
    preload("/d/Avenir/union/room/guild");
	
    /* For auto-save restoration. */
    preload("/d/Avenir/union/room/alcove");
    preload("/d/Avenir/union/room/arsenal");
	
	/* Frequently modified (error-prone) files  */
    preload("/d/Avenir/common/source_flux");
    preload("/d/Avenir/common/bazaar/bazaar_tells");
	preload("/d/Avenir/common/holm/jadestone/load_room");
}
