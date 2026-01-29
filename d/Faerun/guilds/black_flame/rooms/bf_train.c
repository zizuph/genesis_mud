/* /d/Faerun/guilds/black_flame/rooms/bf_train.c
 *
 * Nerull 2022
 *
 */
inherit "/d/Faerun/guilds/black_flame/rooms/std/bf_std_room";
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
create_bf_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("The training grounds");
    
    set_long("This is the training grounds of the temple. It is a "
    +"large room with a high ceiling, and dark stone walls with "
    +"no windows. A heavy smell of sweat and sawdust hangs in the "
    +"air. The ground is covered in parts with fine sawdust and in "
    +"other places thick black carpets line the floors. All around "
    +"you are pieces of training equipment, including target dummies, "
    +"tight-ropes, ladders and various handheld shields and training "
    +"weapons. Scattered across the room are several teams of "
    +"trainers and trainees sparring and receiving instructions "
    +"in the Arts of the Black Flame. Along the edges of the walls, "
    +"you notice a dark clad man walking around staring intently "
    +"at the various trainers as if to ensure that their "
    +"instructions are correct.\n");
    
    add_item(({"dark clad man"}),
        "The dark clad man is walking intently around the edges "
        +"of the room like a black predator stalking its prey. "
        +"His pale white eyes are very clearly focused on the "
        +"trainers and seems to follow their every move, as "
        +"if to ensure that they teach the Arts correctly. "
        +"You also get a glimpse of a platinum signet ring "
        +"on his hand.\n");
        
    add_item(({"trainer", "trainers"}),
        "The trainers are all actively teaching one or more students "
        +"in the ways of the Black Flame.\n");
        
    add_item(({"trainees"}),
        "The trainees do not seem to even notice you. They are fully "
        +"focused on the instructions of their trainer.\n");
        
    add_item(({"instructor"}),
        "The instructor is dressed in the traditional garment "
        +"of a Black Flame Zealot. The instructor is standing by "
        +"to begin a new training session.\n");
        
    add_item(({"equipment", "training equipment", "ropes"}),
        "Scattered throughout the room is all manners of training "
        +"equipment, both for combat, stealth and agility amongst "
        +"other things.\n");
        
    add_item(({"roof", "ceiling"}),
        "This room has a high ceiling with several burning braziers "
        +"hanging from up high, which creates areas of both soft "
        +"shadow and bright light. You also see some ropes hanging "
        +"from the parts of the ceiling.\n");
        
    add_item(({"ground", "floor"}),
        "The floor is covered in parts with fine sawdust and in "
        +"other places with thick carpets.\n");
        
    add_item(({"wall", "walls"}),
        "The walls are made of white stone, so finely cut that "
        +"you can barely see where one stone block stops and the "
        +"next begins. It is somewhat warm to the touch. "
        +"You notice rust-red stains splattered on the wall "
        +"in some places.\n");
        
    add_item(({"rust-red stains", "stains"}),
        "This is definitely dried blood. It looks like they "
        +"don’t hold their punches here.\n");
        
    add_item(({"carpet", "carpets"}),
        "The black carpet is of a thick but fine weave, and "
        +"seems to be used in the training of the more "
        +"stealthy aspects of the Arts.\n");
        
    add_item(({"sawdust"}),
        "The fine sawdust covers parts of the training grounds, "
        +"perhaps to soften the blows when falling to the "
        +"ground, or perhaps to soak up the blood "
        +"splatter coming from the trainees.\n");
        
    
    add_exit(BF_ROOMS_DIR + "bf_join", "west");
    add_exit(BF_ROOMS_DIR + "bf_corridor2", "northwest");
    add_exit(BF_ROOMS_DIR + "bf_shop", "northeast");
    //add_exit(BF_ROOMS_DIR + "bf_laboratory", "southeast");
    add_exit(BF_ROOMS_DIR + "bf_corridor4", "southwest");
    
    create_skill_raise();
    set_up_skills();

    reset_faerun_room();
}


void
set_up_skills()
{
    string to;
    
    // Layman skills
    to = "use fire magic";
    sk_add_train(SS_ELEMENT_FIRE,     ({ to, to }), 0, 0, 60);
   
    to = "cast conjuration magic";
    sk_add_train(SS_FORM_CONJURATION, ({ to, to }), 0, 0, 60);
	
	to = "cast transmutation magic";
    sk_add_train(SS_FORM_TRANSMUTATION, ({ to, to }), 0, 0, 60);
    
    to = "cast enchantment magic";
    sk_add_train(SS_FORM_ENCHANTMENT, ({ to, to }), 0, 0, 60);
    
    to = "cast illusion magic";
    sk_add_train(SS_FORM_ILLUSION,    ({ to, to }), 0, 0, 60);
    
    to = "master spellcraft";
    sk_add_train(SS_SPELLCRAFT,       ({ to, to }), 0, 0, 60);
    
    to = "find and locate herbs";
    sk_add_train(SS_HERBALISM,        ({ to, to }), 0, 0, 50);
         
    to = "sneak";
    sk_add_train(SS_SNEAK,         ({ to, to }), 0, 0, 60);
    
    to = "hide";
    sk_add_train(SS_HIDE,         ({ to, to }), 0, 0, 60);   
      
    to = "handling and fighting with shivs, daggers and knives";
    sk_add_train(SS_WEP_KNIFE,         ({ to, to }), 0, 0, 50);
      
    to = "create alchemical substances";
    sk_add_train(SS_ALCHEMY,         ({ to, to }), 0, 0, 50);
    
    to = "appraise values";
    sk_add_train(SS_APPR_VAL,    ({ to, to }), 0, 0, 50);
    
    to = "track";
    sk_add_train(SS_TRACKING,         ({ to, to }), 0, 0, 50);
    
    
    
    
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


