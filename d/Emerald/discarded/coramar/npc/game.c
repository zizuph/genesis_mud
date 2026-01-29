#include "../coramar.h"
#include "../dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit "/std/object";

void
create_object()
{
    set_name("rabbit");
    set_adj("small"); add_adj("dead");
    set_short("small dead rabbit");

    add_name("_mist_forest_small_game_");

    set_long("This small, furry little creature appears to be quite dead. There are "+
	"several small puncture wounds in its hide from the pit trap that snared it. The "+
	"wounds seem small enough not to prevent this rabbit's trapper from being "+
	"able to use the meat.\n");

    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VALUE, 0);
    
}