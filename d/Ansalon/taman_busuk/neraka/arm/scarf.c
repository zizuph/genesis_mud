/* Ashlar, 29 Jun 97 - a scarf */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS    2

string c1 = "white",c2 = "",type = "";
       
void
create_armour()
{
    set_name("scarf");
    set_adj(c1);
    set_short(c1 + " scarf");
    set_ac(ARMOUR_CLASS);
    set_at(A_NECK);
    set_long("It is a @@query_colour_string@@ scarf@@query_type_string@@, " +
        "worn around the neck. The scarf is made of cloth.\n");

    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}

int
do_wave(string str)
{
    object obj;

    NF("Wave what?\n");
    if (!stringp(str) || (str == ""))
        return 0;

    if(!parse_command(str,this_player()," [the] %o ",obj))
        return 0;

    if (obj != TO)
        return 0;

    if (query_worn())
    {
        write("You cannot wave a worn scarf.\n");
        return 1;
    }

    write("You wave your " + short() + " in the air.\n");
    COMMAND_DRIVER->allbb(" waves " + POSSESSIVE(TP) + " " +
        short() + " in the air.");
    return 1;
}
        
void
init()
{
    ::init();
    add_action(do_wave,"wave");
}

string
query_type_string()
{
    mixed s;
    s = type;

    if ((s != "") && (c1 != c2))
    {
        return " with " + c2 + " " + s;
    }
    else
        return "";
}

string
query_colour_string()
{
    return c1;
}

void
redo_short()
{
    set_short(c1 + " scarf" + query_type_string());
}

void
set_colour(string new_colour)
{
	remove_adj(c1);
    c1 = new_colour;
    add_adj(c1);
    redo_short();
}

void
set_type(string new_type)
{
    type = new_type;
    redo_short();
}

void
set_colour2(string new_colour2)
{
    c2 = new_colour2;
    redo_short();
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + c1 + ";" + type + ";" + c2;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    string cc1,cc2,t;

    sscanf(a[1],"%s;%s;%s",cc1,t,cc2);
    c2 = cc2;
    type = t;
    set_colour(cc1);
    
    init_arm_recover(a[0]);
}


