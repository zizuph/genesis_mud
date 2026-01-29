/* 
 * /d/Kalad/common/central/arena/under_arena10.c
 * Purpose    : Messhall beneath the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Under the arena*/
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
object ob1;
object rat1;
object rat2;
object rat3;
object rat4;
object big_rat;
int kettle_found;

create_room()
{
    ::create_room();
    hear_bell = 1;
    add_prop(ROOM_I_INSIDE,1);
    set_short("Mess room");
    set_long("You have entered the mess hall of the gladiators. Except "+
        "from the straw-covered floor, the room contains just a long "+
        "table surrounded with wooden benches. In a corner you notice "+
        "a small fireplace with a pot hanging inside it.\n");
    add_item(({"floor","straw"}),"A carpet of straws are spread "+
        "out to cover most of the floor in this room.\n");
    add_item(({"fireplace"}),"The fireplace is small but manages to "+
        "give some light and heat to the room. It also keeps the pot "+
        "and its contents warm.\n");
    add_item("pot","The iron pot hangs inside the fireplace in a long "+
        "chain. The outside of it has been blackened by all the soot. "+
        "A weird smell wafts out from it, so you conclude it contains "+
        "some kind of soup or stew.\n");
    add_item("table","The table is of oak and stretches from each end of "+
        "the room. All around it it some wooden benches where the gladiators "+
        "sits when being served their meals.\n");
    add_item(({"bench","benches"}),"The benches runs along the long table, "+
        "and doesn't look very comfertable to sit on.\n");
    add_item(({"walls"}),"The walls are of rough-cut stones that are "+
        "damp to the touch.\n");
    add_exit(CENTRAL(arena/under_arena9),"north",0,-1,-1);
    set_alarm(0.0,0.0,"reset_room");
}

void
init()
{
    ::init();
    add_action("search","search");
}

void
reset_room()
{
    int i;
    kettle_found = 0;
    if(!ob1){
        ob1 = clone_object("/d/Kalad/common/central/npc/cook");
        ob1 -> move_living("M",TO);
        tell_room(TO,"A fat man enters the Mess hall.\n");
        ob1 -> command("emote walks towards the pot and smells on the "
			+ "content.\n");
        ob1 -> command("shout Dinner is ready! Its soup today, as usual.\n");
    }
    if (!rat1 || !rat2 || !rat3)
        {
        rat1=clone_object("/d/Kalad/common/central/npc/rat");
        rat1->move_living("xxx",TO);
        rat2=clone_object("/d/Kalad/common/central/npc/rat");
        rat2->move_living("xxx",TO);
        rat3=clone_object("/d/Kalad/common/central/npc/rat");
        rat3->move_living("xxx",TO);
    }
    if (!objectp(big_rat))
        {
        big_rat = clone_object("/d/Kalad/common/central/npc/big_rat");
        big_rat->move_living("M",TO);
        big_rat->command("emote arrives from the dark.");
    }
    big_rat->team_join(rat1);
    big_rat->team_join(rat2);
    big_rat->team_join(rat3);
}


int
search(string str)
{
    if(!str || str != "table")
        return 0;
    if(kettle_found)
        {
        write("You start to search the table thorougly and "+
            "find nothing special.\n");
        return 1;
    }
    write ("You start to search the table.\n");
    say(QCTNAME(TP) + " starts to search the table.\n");
    set_alarm(4.0,0.0,"do_search");
    return 1;
}

void
do_search()
{
    kettle_found = 1;
    write ("All you find except rotten pieces of food, is a kettle. "+
        "You pick it up.\n");
    say(QCTNAME(TP) + " picks up something from the table.\n");
    clone_object("/d/Kalad/common/central/obj/kettle")->move(TP);
    return;
}