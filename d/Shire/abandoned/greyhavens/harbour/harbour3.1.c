#pragma save_binary
#pragma strict_types

#include "local.h"

inherit GREY_HAVENS;

void
create_gh_room()
{
    area = "not far from";
    areaname = "the City of Mithlond";
    land = "Eriador";
    areatype = 8;
    areadesc = "grassy area";
    grass = "dark green";

    extraline = "Down the gently sloping road to the southwest " +
	"is the harbour area. White towers rise above the city " +
	"walls of Grey Havens to the northeast. Waves crash upon " +
	"the shore in the west. Off to the the east is a dense forest.\n";

    add_item("path", "A well-worn path descending towards the Mithlond " +
        "lighthouse.\n");

    add_exit(GH_HARBOUR_DIR +  "harbour2.c", "south");
    add_exit(GH_HARBOUR_DIR +  "harbour12.c", "west");
    add_exit(GH_HARBOUR_DIR +  "harbour19.c", "north");
    add_exit(GH_HARBOUR_DIR +  "harbour4.c", "northeast");

}
/* 
 * Function name: update_internal
 * Description:   Updates the light, weight and volume of things inside
 *                also updates a possible environment.
 * Arguments:     l: Light diff.
 *                w: Weight diff.
 *                v: Volume diff.
 */
public void
update_internal(int l, int w, int v)
{
    int old_light_level, new_light_level;
    
    old_light_level = this_object()->query_prop(OBJ_I_LIGHT);
    ::update_internal(l, w, v);    
    new_light_level = this_object()->query_prop(OBJ_I_LIGHT);
    
    if (new_light_level < old_light_level)
    	tell_room(this_object(), "The light dims.\n");
    
}

    


