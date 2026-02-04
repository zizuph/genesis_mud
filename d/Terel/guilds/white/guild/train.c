/* A simple guild trainer */

#pragma strict_types

/* Base file for skill trainers */
#include "/d/Terel/include/Terel.h"
inherit "/lib/skill_raise";
inherit WHITE+ "guild/keep_room";

#include "/d/Terel/guilds/white/lib/white.h"

#include <ss_types.h>

object door;

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_RIDING, "in riding", "riding", 0, 50);
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 60);
    sk_add_train(SS_CLIMB, "climb", "climb", 0, 60);
    sk_add_train(SS_LOC_SENSE, "avoid getting lost", "location sense", 0, 60);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 60);
    sk_add_train(SS_PARRY, "deflect attacks", "parry", 0, 60);
    sk_add_train(SS_MOUNTED_COMBAT, "fight while riding",
	"mounted combat", 0, 50);
    sk_add_train(SS_TRACKING, "track", "tracking", 0, 60);
    sk_add_train(SS_2H_COMBAT, "fight with two weapons", "two handed combat",
	0, 60);
    sk_add_train(SS_WEP_SWORD, "fight with a sword", "sword", 0, 60);
}

void
create_terel_room()
{
    ::create_terel_room();
    set_short("Guild Trainer");
    set_long("This is the " + GUILD_NAME + " training hall.\n");

    door=clone_object(WHITE+"guild/tr_door")->move(TO);

    /* configure the trainer */
    set_up_skills();
    
}

void
init()
{
    ::init();

    /* add the trainer's commands */
    init_skill_raise();
}

int sk_improve(string str)
{
    object member = find_object(WHITE_LOG);
    if(!member->query_member(TP->query_name()))
    {
        write("There is nothing for you to learn here.\n");
        return 1;
    }
    write("You prepare to practice your skills.\n");
    return ::sk_improve(str);
}
