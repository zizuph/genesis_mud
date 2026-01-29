/* /d/Faerun/guilds/vampires/rooms/occ_train.c
 *
 * Nerull 2020
 *
 */
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
inherit "/lib/skill_raise";
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";




void set_up_skills();


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    add_prop(ROOM_I_INSIDE, 0);

    set_short("Somewhere high up in the sky");
    
    set_long("Your are hanging somewhere high up in the "
    +"sky, only supported by a powerful claw clasped around your "
    +"neck! Below you see various landscape and clouds, openly "
    +"inviting you to fall into your doom! The entity "
    +"that is holding you is behind you, and you see nothing of him "
    +"or her!\n");
    
    create_skill_raise();
    set_up_skills();

    reset_faerun_room();
}


void
set_up_skills()
{
    string to;
    
    // Occ skills 
    
    // Only 1 skill will be used per vampire.
    to = "x";
    sk_add_train(SS_WEP_KNIFE,         ({ to, to }), 0, 0, 100);
    
    to = "x";
    sk_add_train(SS_WEP_SWORD,         ({ to, to }), 0, 0, 100);
    
    to = "x";
    sk_add_train(SS_WEP_AXE,         ({ to, to }), 0, 0, 100);
    
    to = "x";
    sk_add_train(SS_WEP_POLEARM,         ({ to, to }), 0, 0, 100);
    
    
    to = "x";
    sk_add_train(SS_2H_COMBAT,         ({ to, to }), 0, 0, 100);
    
    to = "x";
    sk_add_train(SS_PARRY,           ({ to, to }), 0, 0, 85);
    
    to = "x";
    sk_add_train(SS_DEFENSE,         ({ to, to }), 0, 0, 85);
    
   to = "x";
    sk_add_train(SS_BLIND_COMBAT,    ({ to, to }), 0, 0, 85);
    
    to = "x";
    sk_add_train(SS_ACROBAT,         ({ to, to }), 0, 0, 75);
    
    to = "x";
    sk_add_train(SS_AWARENESS,         ({ to, to }), 0, 0, 100);
}


int
do_blockskillraise()
{
    write("What?\n");
    
    return 1;
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    init_skill_raise();
    
    ::init();
}


