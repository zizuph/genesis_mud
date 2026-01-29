/* 
 * /d/Kalad/common/central/arm/lord_helm.c
 * Purpose    : Helmet worn by the high lord in the citadel
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
High Lords helm
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/armour.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
int visor_down;
#define SUBLOC "wearing_helm_subloc"

create_armour()
{
    ::create_armour();
    set_name("helm");
    set_adj("black");
    add_adj("visored");
    set_pname("helms");
    set_short("black visored helm");
    set_pshort("black visored helms");
    set_long("This is an excellent visored helm, made of an unknown "+
      "sheeted black metal. The edges of the sheets seems to glow "+
      "in a golden colour, making you think of sunbeams. On the lower "+
      "part, you notice a hatch that can be clasped fast to protect "+
      "your neck as well. The helm's "+
      "visor has a long rectangular hole in it for vision when it is "+
      "lowered, and therebye giving extra protection of the face. "+
      "The visor is currently @@visor@@.\n");
    set_ac(25);
    set_af(TO);
    set_at(A_HEAD | A_NECK);
    add_prop(OBJ_I_VALUE,700);
    add_prop(OBJ_I_WEIGHT,3500);
    add_prop(OBJ_I_VOLUME,2000);
    visor_down = 0;
}

init()
{
    ::init();
    add_action("raise","raise");
    add_action("lower","lower");
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if (for_obj == carrier)
	str = "You carry ";
    else
	str = capitalize(carrier->query_pronoun()) + " carries ";
    return str+"a black visored helm under the left arm.\n";
}

int
raise(string str)
{
    notify_fail("Raise what?\n");
    if(!str || str != "visor")
	return 0;
    if(!visor_down)
    {
	write("But the visor is already raised!\n");
	return 1;
    }
    visor_down = 0;
    write("You raise the visor on your black visored helm.\n");
    say(QCTNAME(TP)+ " raises the visor on "+ TP->query_possessive() +
      " his black visored helm.\n");
    TO->set_ac(35);
    return 1;
}

int
lower(string str)
{
    notify_fail("Lower what?\n");
    if (!str || str!="visor")
	return 0;
    if (visor_down)
    {
	write("The visor is already down!\n");
	return 1;
    }
    visor_down = 1;
    write("You lower the visor on your black visored helm.\n");
    say(QCTNAME(TP)+ " lowers the visor on "+ TP->query_possessive() +
      " black visored helm.\n");
    TO->set_ac(38);
    return 1;
}

visor()
{
    if (visor_down)
	return "lowered down";
    else
	return "raised";
}

mixed
wear(object from)
{
    if (!visor_down)
    {
	TP->remove_subloc(SUBLOC, TO);
	return 0;
    }
    write("You try to wear the helm, but the visor is down.\n");
    return -1;
}

mixed
remove(object what)
{
    if (!visor_down)
    {
	TP->add_subloc(SUBLOC, TO);
	return 0;
    }
    write("You raise the visor of the helm and remove it.\n");
    return 0;
}

