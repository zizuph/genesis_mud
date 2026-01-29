/* temphold.c: This object is the hold person spell used by the
 *     Templars of Athas. -- Serpine 12/5/95.
 */
 
#pragma strict_types
 
inherit "/std/object";
#include "defs.h"
 
int remove_time;
 
void
create_object()
{
    set_name("_templar_hold_");
 
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_INVIS, 100);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    set_no_show();
}
 
void set_remove_time(int setting) { (remove_time = setting); }
 
void
init()
{
    ENV(TO)->add_attack_delay(remove_time, 1);
    set_alarm (itof(remove_time), 0.0, "end_spell");
    add_action("stop", "", 1);
}
 
int
stop(string str)
{
    ENV(TO)->catch_msg("You feel frozen by the Templar's spell.\n");
    if (!this_player()->query_wiz_level()) return 1;
    ENV(TO)->catch_msg("Not that that matters to a wizard.\n");
    return 0;
}
 
void end_spell()
{
    ENV(TO)->catch_msg("Gradually you feel motion return to you.\n");
    remove_object();
}
 
int
dispel_magic (int magic)
{
    if (magic > (remove_time) ) return 1;
    return 0;
}
