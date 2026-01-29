/* poor_mob: A vast quantity of meaningless life. */
inherit "/d/Cirath/std/monster";
#include "defs.h"

#define MOBRACE ({"human", "dwarf", "half-giant", "elf", "half-elf",\
                  "human", "dwarf", "halfling", "thri-kreen"})[random(9)]

#define MOBADJ1 ("poor")

#define MOBADJ2 ({"ugly", "unhappy", "malnurished", "angry", "dejected",\
                  "hopefull", "desperate", "ragged"})[random(8)]
 
#define COOL_ECHOS ({"begs for a few coins.", "wanders in.", \
                     "picks someone's pocket.", "leaves.", \
                     "sizes you up.", "wanders off.",\
                     "arrives.", "begs for food.",\
                     "is dragged away by some Templars."})[random(9)]

create_monster()
{
    set_name (({"mob","dweller"}));
    set_short ("unruly slum mob");
    set_long ("Like many of the unfortunates in Athas, these folks have "
             +"neither home nor income. Still it could be worse: "
             +"Many of their kind end up in the slave pits.\n");
    set_adj ("unruly");
    add_adj ("slum");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(OBJ_M_NO_ATTACK, "And face the wrath of the entire mob?  You must be mad!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "And face the wrath of the entire mob?  You must be mad!\n");

    set_alignment(random(150)-50);

    set_stats(({500,50,50,50,50,50}));

    set_act_time(5);
    add_act("@@do_something_cool@@");
    trig_new("%w 'drops' %s", "react_drop");
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
react_drop(string person, string what)
{
    tell_watcher("The crowd surges forward.\n");
    command("get all");
}

void
blast_subloc()
{
    remove_subloc("_subloc_misc_extra");
}
