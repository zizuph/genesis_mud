/* mrkt_mob: A vast quantity of meaningless life. */
inherit "/d/Cirath/std/monster";
#include "defs.h"
 
#define MOBADJ2 ({"human", "dwarf", "half-giant", "elf", "half-elf",\
                  "human", "dwarf", "halfling", "elf"})[random(9)]
 
#define MOBRACE ("merchant")
 
#define MOBADJ1 ({"happy", "wealthy", "colorful", "sneaky", "shady",\
                  "hopeful", "toothless", "loud"})[random(8)]
 
#define COOL_ECHOS ({"smiles at you.", "shows his wares.", \
                     "shouts what he is selling.", "yawns.", \
                     "polishes a piece of metal.", "makes a sale.",\
                     "closes shop.", "opens a stand.",\
                     "is dragged away by some Templars."})[random(9)]
 
create_monster()
{
    set_name (({"traders","trader"}));
    set_short ("crowd of traders");
    add_name("crowd");
    set_long ("It is said that everything legal or illegal in Athas "
             +"can be had in the Shadow Square, for a price.\n");
    set_adj ("crowd");
    add_adj ("of");
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
