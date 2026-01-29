// Ziggurat  (stairs.c)
// creator(s):   Lucius 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <money.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Genesis/gems/gem.h"
#include "zigg.h"

inherit ZIG_ROOM;

public void
zig_room(void)
{
    setuid();
    seteuid(getuid());	
	
    set_short("Stairwell outside the Sanctorium");
    set_long("You've come upon a small landing in a stairwell outside the "+
    	"Sanctorium. On the west side of the landing, dim light spills "+
	"through an archway opening to the south. On the east side, "+
	"stairs climb south toward the Ziggurat's entrance and descend north, "+
	"leading further into the depths of the Ziggurat. Carved black "+
	"stone surrounds you devouring the light from the archway before "+
	"it reaches the stairs. The ceiling mirrors the slope of the stairs "+
	"making the stairwell feel confined, almost claustrophobic, like a "+
	"tunnel cut through the stone as an afterthought. Only the "+
	"faint glow of Source-crystal dust thoughtfully poured into a crevice "+
	"between the wall and stairs will guide your steps from one landing to "+
	"the next.\n");

    add_item(({"stair","stairwell","stairs","steps"}),
        "The stairs are made of carved black stone. They descend into darkness "+
        "toward the north. The air seems fresher toward the north where they "+
        "ascend toward a very faint light. Climbing either way would be "+
        "precarious at best were it not for a faintly glowing crevice outlining "+
        "the shape of the stairs where they meet the wall.\n");
    add_item(({"floor","ground"}),
        "The ground is made of black stone which does nothing to light this "+
        "narrow landing.\n");
    add_item(({"crevice","dust", "Source-crystal dust", "source-crystal dust",
    	"crystal dust", "glowing dust"}), "Even the dust produced by mining or "+
    	"cutting Source crystals is regarded as precious in the Sybarun cavern. "+
    	"Never wasted, here the dust has been put to use limning the shape of the "+
    	"steps in this stairway tunnel. The very faint glow from the dust-filled "+
    	"crevice is just enough to guide your steps and keep you from "+
    	"tumbling into darkness.\n");
    add_item(({"wall","walls"}),
        "The walls constructed out of black stone and unpolished. They quickly "+
        "absorb every speck of light so that even with a light source the "+
        "stairway would seem dim.\n");
    add_item(({"ceiling","roof","above"}),
        "The ceiling mirrors the slope of the stairs making the "+
	"stairwell feel confined, almost claustrophobic, like a "+
	"tunnel cut through the stone as an afterthought\n");	
	
	
    add_exit("sanctorium", "south",  0);
    add_exit(ZIG_RL1 + "entrance", "up", 0);
    add_exit(ZIG_RL3 + "stairs", "down", 0);
    
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_zigg();
}


/*
 * Function name: do_search
 * Description:   Search results for add_items in the Dark.
 *                Gives general experience 100 each for max of  
 *                5 successful searches per login.
 * Returns:       string for success
 */
public string 
do_search(object player, string str)
{
    object ob;

    str = lower_case(str);
    
    /* What I can find*/    
    if (!parse_command(str, ({}), "[glowing] [source-crystal] / [source] "+
    "[crystal] 'dust' / 'crevice' / 'stair' / 'stairway'"))
    {
	return "";
    }    
    
    /* If I've found objects already, I'm not finding any more */   
    if (player->query_prop("_avenir_zig_dust_found") > 5)
        return "";    

    /* Do I have the simple awareness to find something
     * and the wisdom to recognize it as being of value?
     */
    if (player->resolve_task(TASK_SIMPLE, ({ TS_WIS, SS_AWARENESS,})) < 0)
        return "";    

    /* What I can find*/
    switch (random(15))
    {
	case 0..3:
	    ob = clone_object("/d/Avenir/common/outpost/obj/lsource");
	    break;	    
	case 4:
	    ob = RANDOM_GEM_BY_RARITY(GEM_RARE);      break;
	case 5..7:
	    ob = RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_RARE);  break;
	case 8:
	    ob = clone_object("/d/Avenir/common/obj/syb_coin");  break;    
	case 9:
	    ob = MONEY_MAKE_PC(1);  break;                       
	default:  return "";
    }
  
    /* Make sure to add to the counter */
    ALTER_PROP(player, "_avenir_zig_dust_found", 1);

    /* I get some general experience for succeeeding */
    player->add_exp_general(100 + random(50));
    ob->move(player, 1);          
    
    return "You find "+LANG_ASHORT(ob)+".\n";
}
