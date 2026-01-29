/*
 * /d/Gondor/common/lib/logkill.c
 *
 * Inherit this to log player kills of your monsters.
 *
 * Modified from ~elessar/lib/goodkill.h and ~elessar/lib/evilkill.h
 * by Olorin, 21-Nov-1996
 *
 * Copyright (c) 1996 by Christian Markus
 */
#include <macros.h>

public void
notify_you_killed_me(object player)
{
    string  file;

    command("get all from corpse");
    if (player->query_npc()) 
        return;
    seteuid(getuid(this_object()));

    if (this_object()->query_alignment() < 0)
        file = "evilkill";
    else
        file = "goodkill";

    log_file(file, player->query_name()
      + " (" + player->query_average_stat()
      + ") was killed by "+ this_object()->query_name()
      + " on " + ctime(time()) + " ("
      + file_name(environment(this_object())) + ").\n");
}
