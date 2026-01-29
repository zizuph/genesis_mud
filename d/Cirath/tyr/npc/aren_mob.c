/* aren_mob: A vast quantity of meaningless life. */
inherit "/d/Cirath/std/monster";
#include "defs.h"
 
#define MOBRACE ({"human", "dwarf", "half-giant", "elf", "half-elf",\
                  "human", "dwarf", "halfling", "thri-kreen"})[random(9)]
 
#define MOBADJ1 ({"screaming", "happy", "jumping", "violent", "puzzled",\
                  "crazy-eyed", "laughing", "hungry"})[random(8)]
 
#define MOBADJ2 ({"rich", "poor", "poor", "enslaved", "common"})[random(5)]
 
#define COOL_ECHOS ({"jumps up and down with enthusiasm.",\
                     "pounds on the person next to him.",\
                     "screams for blood.", "orders some food.",\
                     "whines about a lost bet.", "dances around.",\
                     "is dragged away by some Templars."})[random(7)]
 
create_monster()
{
    set_name ("audience");
    set_race_name ("audience");
    set_gender(2);
    set_short ("huge arena audience");
    set_long ("A huge mass of every race and profession in Athas, from "+
              "slave to noble. All are united by their lust to watch "+
              "people fight and die in the arena, the only entertainment "+
              "that can satisfy the citizenry of a dying land.\n");
    set_adj("huge");
    add_adj("arena");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS,1);
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

void
blast_subloc()
{
    remove_subloc("_subloc_misc_extra");
}
