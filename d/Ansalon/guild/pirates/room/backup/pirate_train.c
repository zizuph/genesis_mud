/*
 * File Name        : pirate_center_room.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : The training room of the pirates.
 *                    I might add a npc that teaches them
 *                    the skills.
 *
 *
 * Modified by Navarre: June 14th 2006.
 * Added skill for stagger, and increased the acroabat skill
 * as the new stagger works on Acrobat.
 *
 */

#pragma strict_types

/* Base file for skill trainers */
inherit "/lib/skill_raise";
inherit "/d/Ansalon/std/room";
inherit "/lib/guild_support";

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_TRADING, "make deals", "trading", 0, 45);
    sk_add_train(SS_ACROBAT, "make acrobatics", "acrobat", 0, 60);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 40);
    sk_add_train(SS_2H_COMBAT, "fight with two weapons", "two handed combat", 0, 50);
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 50);
    sk_add_train(SS_WEP_KNIFE, "fight with a knife", "knife", 0, 60);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 50);
    sk_add_train(SS_PARRY, "parry attacks", "parry", 0, 50);
    sk_add_train(SS_WEP_SWORD, "fight with a sword", "sword", 0, 50);
    sk_add_train(SS_LANGUAGE, "speak languages", "language", 0, 45);
    sk_add_train(SS_SPECIAL_STAGGER, "knowledge about alcohol", "alcohol lore", 100, 100);
}

object trainer; 

void 
reset_room()
{
    if(!objectp(trainer))
    {
      trainer = clone_object(GUILD_NPC + "ramirez");
      trainer->move(this_object());
   }
}

void
create_room()
{
    set_short("Practice hall");
    set_long("You are standing in a huge underground cave, beneath the isle of Mithas. The "+
             "cave must have been made by some sort of violent erosion of the stones that "+
             "form the bedrock of the isle. The black rock walls are drenched with water and "+
             "the smell of the fresh seawater and wet soil dominate this place. This might be "+
             "a good place to hide yourself or something. To the south is a large cavern. "+
             "A large wooden dummy has been placed in the center of the room.\n");

    add_exit("pirate_center_room", "south");

    add_item(({"stone", "walls", "wall", "stones"}),"The walls here are "+
             "black, but in some places the water, coming from above, "+
             "has colored them grey.\n");

    add_item(({"wooden", "dummy"}),"The wooden dummy is used to train "+
             "the pirates in various skills. A few large scars in the "+
             "wooden structure can be seen.\n");

    add_item(({"floor", "ground"}),"The floor is fairly smoothe, a few "+
             "footprints leads from a large hole in the center of the "+
             "towards the north.\n");

    add_prop(ROOM_I_INSIDE, 1);
    /* configure the trainer */
    set_up_skills();
    reset_room();
}

void
gs_hook_start_meditate()
{
    write("You start to concentrate solely upon your own mind and you " +
      "block off all your senses. A feeling of great ease and self " +
      "control falls upon you as you slowly sink into a deep " +
      "trance.\n");

    say(QCTNAME(TP) + " enters into a trance and slowly kneels " +
      "down. " + C(PRONOUN(TP)) + " sinks into a deep trance and " +
      "seems lost to the world around " + OBJECTIVE(TP) + ".\n"); 
}


int
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface " +
      "of your consciousness. You exhale and feel very relaxed as " +
      "you get up and prepare yourself for whatever may lie ahead. " +
      " \n");

}


void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

int
remove_medi_props()
{
    TP->remove_prop(LIVE_I_MEDITATES);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    init_guild_support();
    add_action("gs_meditate","meditate");
}

void
init()
{
    init_guild_support();
    add_action("gs_meditate","meditate");
    init_skill_raise();
    ::init();
}
