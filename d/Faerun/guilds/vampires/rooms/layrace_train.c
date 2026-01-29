/* /d/Faerun/guilds/vampires/rooms/layrace_train.c
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
    
    // Layman skills
    to = "x";
    sk_add_train(SS_APPR_MON,         ({ to, to }), 0, 0, 60);
    
    to = "x";
    sk_add_train(SS_TRACKING,         ({ to, to }), 0, 0, 60);
    
    to = "x";
    sk_add_train(SS_LOC_SENSE,        ({ to, to }), 0, 0, 60);
       
    to = "x";
    sk_add_train(SS_ELEMENT_AIR,      ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_ELEMENT_WATER,    ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_ELEMENT_DEATH,    ({ to, to }), 0, 0, 50);
       
    to = "x";
    sk_add_train(SS_FORM_ABJURATION,  ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_FORM_CONJURATION, ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_FORM_ENCHANTMENT, ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_FORM_ILLUSION,    ({ to, to }), 0, 0, 50);
       
    to = "x";
    sk_add_train(SS_SPELLCRAFT,       ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_HERBALISM,        ({ to, to }), 0, 0, 60);
    
    
    // Racial skills
    to = "x";
    sk_add_train(SS_OPEN_LOCK,   ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_APPR_VAL,    ({ to, to }), 0, 0, 50);
       
    to = "x";
    sk_add_train(SS_LANGUAGE,    ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_CLIMB,       ({ to, to }), 0, 0, 60);
    
    sk_add_train(SS_ANATOMY, "in the knowledge of Anatomy",
    "anatomy",100,100,SS_DEX,100);
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


