/*
 * Code to make npcs wander from point A to point B
 * Borrowed from Gondor's Haradrim warriors
 * Converted over to Shire by Finwe, November 2005

 * Elf traveller code from Rivendell along the Great Road to Frogmorton -- Tomas 2018
   File: /d/Shire/std/elf_gr_patrol.c
 */

#include <ss_types.h>
#include "/d/Shire/sys/defs.h"
// inherit "/d/Shire/room";

static int     move_alarm;
static string  patrol_dir = "west";
string npc_name = "_is_elf_gr_traveller";

public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
move_patrol(object ob)
{
    move_alarm = 0;
    ob->command("sneak " + query_patrol_dir(ob));
}

void
stand_to_fight()
{
    if (move_alarm)
        remove_alarm(move_alarm);
}

void
continue_patrol(object ob)
{
    if (move_alarm && sizeof(get_alarm(move_alarm)))
        return;

    move_alarm = set_alarm(10.0 + rnd() * 20.0, 30.0, &move_patrol(ob));
}


