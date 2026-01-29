/* friedelf.c: Food for the Red Eye Inn. */

inherit "/std/food";

#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

int react_elf_alarm;
int react_other_alarm;

void react_elf(object pl);
void react_other(object pl);

void
create_food()
{
    set_name("elfmeat");
    set_pname("elfmeats");
    add_pname("plates");
    add_name("plate");
    add_name("fried");
    set_short("plate of fried elfmeat");
    set_pshort("plates of fried elfmeat");
    set_long("@@long_desc");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(560);
    add_prop(OBJ_I_WEIGHT,550);
    add_prop(OBJ_I_VOLUME,540);
}

string
long_desc()
{
    string desc;
    desc = "It is a large piece of meat, probably from the shoulder. "
    + "And for once it does look like the innkeeper actually did "
    + "tell the truth on his menu. This seems to be meat from an "
    + "elf indeed! You feel sick! ";
    if(TP->query_npc()) return BSN(desc);
    switch(QRACE(TP))
    {
    case "goblin":
	desc = "This plate of fried elfmeat looks truely appetizing " 
	+ "and smells so delicious that you feel like devouring "
	+ "it right now. You never knew that elves can be good "
	+ "like this. "; break;
    case "elf": 
	if (!get_alarm(react_elf_alarm))
	    react_elf_alarm = set_alarm(2.0, 0.0, &react_elf(TP));
	break;
    case "human":
    case "hobbit":
    case "dwarf":
    case "gnome":
	if (!get_alarm(react_other_alarm))
	    react_other_alarm = set_alarm(2.0, 0.0, &react_other(TP));
    default:
    }
    return BSN(desc);
}

void
react_elf(object pl)
{
    pl->command("puke");
    if(environment() == pl) pl->command("drop elfmeat");
    pl->command("groan");
}

void
react_other(object pl)
{
    if (pl->query_alignment() < -200)
	return;
    pl->command("puke");
}
