/* move_mob: Guild moving van mob. */
inherit "/std/monster";
#include "defs.h"
 
#define MOBRACE ("templar")
 
#define MOBADJ1 ({"tired", "bored", "pleased", "greedy", "grumbling",\
                  "vibrant", "muscular", "tan"})[random(8)]
 
#define MOBADJ2 ("tyrian")
 
#define COOL_ECHOS ({"draws some runes on the ground.", \
                     "calculates some figures on a parchment.", \
                     "asks 'How did they move this last time?'", "runs in circles chanting.", "is dragged away by another templar."})[random(5)]
 
create_monster()
{
    set_name ("crew");
    set_race_name ("crew");
    set_gender(2);
    add_prop(NPC_I_NO_LOOKS,1);
    set_short ("templar moving crew");
    set_long ("A group of tyrian templars is milling about, preparing "
             +"for some awesome spell.  They seem to be scrawling "
             +"runes of movement and change on every surface nearby. "
             +"What do you suppose is going on?\n");
    set_adj("templar");
    add_adj("moving");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "And face the wrath of the entire mob?  You must be mad!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "And face the wrath of the entire mob?  You must be mad!\n");
 
    set_stats(({100,100,100,100,100,100}));
 
    set_act_time(5);
    add_act("@@do_something_cool@@");
    set_alarm(1.0, 0.0, "blast_subloc");
}
 
string
do_something_cool()
{
    tell_room(environment(TO),
        "A "+MOBADJ1+" "+MOBADJ2+" "+MOBRACE+" "+COOL_ECHOS+"\n");
    return "";
}

void blast_subloc()
{
    remove_subloc("_subloc_misc_extra");
}
