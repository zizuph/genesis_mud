/* /d/Emerald/mine/obj/stat_logger.c is used by the runed axe (path is     */
/* /d/Emerald/mine/wep/r_axe.c) to log the stats of enemies.               */
/* Coded for the benefit of game balance on 13/06/96 by Tulix III.         */

inherit "/std/object";

#include "/d/Emerald/tulix/t_defs.h"
 
#pragma strict_types

object axe_pointer;
int victim_av_stats;

public void
create_object()
{
    set_name("axe_stat_logger");
    set_no_show();
}

public void
log_stats(object axe)
{
    object victim;
    
    axe_pointer = axe;

    victim = ENV(TO);
    if (victim && living(victim))
        victim_av_stats = victim->query_average_stats();
    else
        remove_object();
}

public int
query_victim_av_stats()
{
    return victim_av_stats;
}

public object
query_axe_pointer()
{
    return axe_pointer;
}
