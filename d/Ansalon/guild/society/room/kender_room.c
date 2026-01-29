/* 
 * /d/Ansalon/guild/society/room/kender_room.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Master room to distribute kender around Krynn/Ansalon   
 * With reset times of 30 minutes, this room should         
 * Produce a kender every 2 hours. The kender will choose
 * one of the exits at random.       
 *
 * Gwyneth - 29 September 1999
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/kendermore/local.h"
inherit KENDERMORE_IN;

#define PLAINS     "/d/Krynn/solamn/splains/room/xroad"
#define XAK        "/d/Krynn/xak/marsh7"
#define FLOTSAM    "/d/Ansalon/balifor/flotsam/room/street43"
#define SANCTION   "/d/Ansalon/taman_busuk/sanction/room/city/street5"
#define SOLACE     "/d/Krynn/solace/new_village/intersection"
#define KENDERMORE "/d/Ansalon/goodlund/kendermore/room/in_gate"
#define NERAKA     "/d/Ansalon/taman_busuk/neraka/inner/r1"
#define ESTWILDE   "/d/Ansalon/estwilde/plains/11g"
#define KENDER     "/d/Ansalon/common/monster/new_kender"

object wanderer;
int i;

void
reset_kendermore_room()
{
    if (!present(wanderer, TO) && i == 1)
    {
        wanderer = clone_object(KENDER);
        wanderer->move(this_object());
    }
    if (i < 4)
        i++;
    else
        i = 1;
}

void
create_kendermore_room()
{
    set_short("Master Kender Room");
    set_long("This room is where the kender are cloned and wander into " + 
        "the lands of Krynn and Ansalon.\n");
    add_exit(PLAINS, "plains", 0);
    add_exit(XAK, "xak", 0);
    add_exit(FLOTSAM, "flotsam", 0);
    add_exit(SANCTION, "sanction", 0);
    add_exit(SOLACE, "solace", 0);
    add_exit(KENDERMORE, "kendermore", 0);
    add_exit(NERAKA, "neraka", 0);
    add_exit(ESTWILDE, "estwilde", 0);
    i = 1;
    reset_room();
}

void
dummy_function()
{
    return;
}

