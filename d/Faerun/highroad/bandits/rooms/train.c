/*
 * Bandit Training
 * -- Finwe, September 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CAVE;
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";

static object trainer;
void set_up_skills();

void
create_cave()
{
    add_prop(ROOM_I_INSIDE,1);
    ALLOW_STEEDS;
    set_short("a wide cave");
    set_long("This cave is larger than the other side caves. Bandits come " +
        "here and teach each other skills to help them patrol the roads " +
        "and rob travellers. The are rough walls and the ceiling higher " +
        "than others. There is a sign hanging on a wall.\n");

    create_skill_raise();
    set_up_skills();
    reset_room();

    add_item("sign", "Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    add_exit(CAVE_DIR + "entr", "east");

}

void
init() 
{
    ::init();
    init_skill_raise();
    init_guild_support();
}

void
set_up_skills() 
{
    string me;

    me = "Learn to pick locks";
    sk_add_train(SS_OPEN_LOCK,      ({ me, me }),   0,0,20);
    me = "Learn to pick pockets";
    sk_add_train(SS_PICK_POCKET,    ({ me, me }),   0,0,20);
    me = "Train acrobatic maneuvers";
    sk_add_train(SS_ACROBAT,        ({ me, me }),   0,0,20);
    me = "Find and remove traps";
    sk_add_train(SS_FR_TRAP,        ({ me, me }),   0,0,20);
    me = "Sneak into rooms";
    sk_add_train(SS_SNEAK,          ({ me, me }),   0,0,20);
    me = "Be aware of surroundings";
    sk_add_train(SS_AWARENESS,      ({ me, me }),   0,0,30);
    me = "Know where you are";
    sk_add_train(SS_LOC_SENSE,      ({ me, me }),   0,0,25);
    me = "Hide inside rooms";
    sk_add_train(SS_HIDE,           ({me, me}),     0,0,20);
    me = "Hunt for a living creatures";
    sk_add_train(SS_HUNTING,        ({me, me}),     0,0,25);
    me = "Track something in the wild";
    sk_add_train(SS_TRACKING,       ({me, me}),     0,0,25);
    me = "Determine the value of an object";
    sk_add_train(SS_APPR_VAL,       ({me, me}),     0,0,25);

}

int
gs_meditate(string str) 
{
    return ::gs_meditate(str);
}

int
sk_improve(string str) 
{
    return ::sk_improve(str);
}


string read_sign()
{
    return "\n\n" +
"+-------------------------------------------------------------------+\n" +
"|                                                                   |\n" +
"|                  B A N D I T ' S   S K I L L S                    |\n" +
"|                                                                   |\n" +
"|  These are the skills that bandits who live here study. If you    |\n" +
"|  can afford to pay them, you can learn them also.                 |\n" +
"|                                                                   |\n" +
"|      Acrobat. . . . . . . . . . . . . . . . Superior Amateur      |\n" +
"|      Appraise Value . . . . . . . . . . . . Confident Layman      |\n" +
"|      Awareness. . . . . . . . . . . . . . . Superior Layman       |\n" +
"|      Find and Remove Traps. . . . . . . . . Superior Amateur      |\n" +
"|      Hide . . . . . . . . . . . . . . . . . Superior Amateur      |\n" +
"|      Hunting. . . . . . . . . . . . . . . . Confident Layman      |\n" +
"|      Location Sense . . . . . . . . . . . . Confident Layman      |\n" +
"|      Open Lock. . . . . . . . . . . . . . . Superior Amateur      |\n" +
"|      Pick Pocket. . . . . . . . . . . . . . Superior Amateur      |\n" +
"|      Sneak. . . . . . . . . . . . . . . . . Superior Amateur      |\n" +
"|      Tracking . . . . . . . . . . . . . . . Confident Layman      |\n" +
"|                                                                   |\n" +
"| You can also 'meditate' to learn more about yourself.             |\n" +
"|                                                                   |\n" +
"| 'list guilds' will show you basic information about the guilds    |\n" +
"| you belong to.                                                    |\n" +
"+-------------------------------------------------------------------+\n\n";
}


void reset_room() 
{ 
    if(!trainer)
        trainer = clone_object(NPC_DIR + "trainer");
    trainer->move(TO);

}
