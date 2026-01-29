/* csno_mob: A vast quantity of meaningless life. */
inherit "/d/Cirath/std/monster";
#include "defs.h"
 
#define MOBRACE ({"human", "dwarf", "half-giant", "elf", "half-elf",\
                  "human", "dwarf", "mul", "elf"})[random(9)]
 
#define MOBADJ1 ({"greedy", "broke", "shabby", "wealthy", "puzzled",\
                  "distracted", "pleased", "extactic"})[random(8)]
 
#define MOBADJ2 "gambling"
 
#define COOL_ECHOS ({"bets a coin and looses.",\
                     "bets a few coins and looses.",\
                     "goes broke.", "wins a coin.",\
                     "is caught cheating and is beaten.", "drinks.",\
                     "is dragged away by some Templars."})[random(7)]
 
create_monster()
{
    set_name ("crowd");
    set_race_name ("crowd");
    set_gender(2);
    set_short ("large gambling crowd");
    set_long ("From all walks of life they come hopeing to win big. "
             +"Most loose only what they came in with. They are "
             +"among the lucky ones.\n");
    set_adj("large");
    add_adj("gambling");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(OBJ_M_NO_ATTACK, "And face the wrath of the entire mob?  You must be mad!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "And face the wrath of the entire mob?  You must be mad!\n");
 
    set_stats(({100,100,100,100,100,100}));
 
    set_act_time(9);
    add_act("@@do_something_cool@@");
    set_alarm(1.0, 0.0, "blast_subloc");
}
 
string
do_something_cool()
{
    if (((environment(this_object()))->dealer_in_motion())==1)
    {
        tell_room(environment(this_object()),
            "A "+MOBADJ1+" "+MOBADJ2+" "+MOBRACE+" watches the game.\n");
        return "";
    }
 
    tell_room(environment(TO),
        "A "+MOBADJ1+" "+MOBADJ2+" "+MOBRACE+" "+COOL_ECHOS+"\n");
    return "";
}
 
void
blast_subloc()
{
    remove_subloc("_subloc_misc_extra");
}
