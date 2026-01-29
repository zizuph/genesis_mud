/*
 *    Great forge for Smiths Guild
 */

inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "smiths.h"
#include <macros.h>
#include <filter_funs.h>

#define FORGING "_live_o_forge_"

void start_fire();
void end_fire();


void
create_object() {
   set_name(({"forge","_great_smith_forge"}));
   set_adj("great");
   set_short("great forge");
   set_long("This great forge is used to heat metals in before " +
        "they are hammered into shape. Large embers glow bright " +
        "red, yellow and blue with alot of heat.\n");
    add_item(({"red embers", "yellow embers", "blue embers", "embers"}),
        "The embers are large pieces of burning coal, providing " +
        "extreme heat for smiths to forge items.\n");
   add_item("coal",
        "The coal is black and piled in spots for use by the " +
        "smiths. It serves as fuel for the forge. Some burns " +
        "brightly in the forge.\n");

   add_prop(OBJ_I_WEIGHT,5000000);
   add_prop(OBJ_I_NO_GET,1);
}

void
start_fire()
{
    TO->add_prop(OBJ_I_BELLOW_USED, 1);
    set_alarm(itof(30+random(60)),0.0,end_fire);
    write("Waves of heat roll across your exposed skin as you pump "+
        "air into the forge.\n");
    say("Waves of heat roll across your exposed skin as "+
        QTNAME(TP)+" pumps air into the forge.\n");
}

void
end_fire()
{
    object *obs = deep_inventory(ENV(TO)),
           *pl = FILTER_LIVE(obs);
    int     i, sz = sizeof(pl);

    TO->remove_prop(OBJ_I_BELLOW_USED);
    for (i = 0; i < sz; i++)
        pl[i]->catch_tell("The forge's heat subsides a little.\n");
}

