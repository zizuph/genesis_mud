/*  /d/Ravenloft/droptables/fos_drops/r_healing_potion_cooldown
*
*  Cooldown object for the healing potions.
*
*  Nerull, 2015
*
*/

inherit "/std/object";
#include "../defs.h";
#include "/d/Ravenloft/defs/magicalitems_stats.h";
#include <stdproperties.h>
#include <macros.h>


void
do_destroy()
{
    //write("You destroy the darkened bear claw!\n");
    tell_object(environment(this_object()),"You feel normal again.\n");
    remove_object();
}


void
create_object()
{
    set_name("_r_healing_potion_cooldownob");

    set_no_show();

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_TELEPORT, 1);

    // Removes the object in 60 seconds.
    set_alarm(R_HEAL_POTION_COOLDOWN, 0.0, &do_destroy());
}


