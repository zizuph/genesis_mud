/*
   knife.c

   A sample weapon
*/
inherit "/std/weapon";
#include <stdproperties.h>
#include <macros.h>

string
query_auto_load()
{
    return (MASTER_OB(this_object()) + ":");
}

create_weapon()
{
    set_name("sword");
    set_short("singing sword");
    set_adj("singing");
    set_long("It is a very simple looking knife, quite deadly though.\n");
    
    set_default_weapon();
    add_prop(OBJ_M_NO_DROP, "@@wiz_check");
    add_prop(OBJ_M_NO_GIVE, "@@wiz_check");
}

int
wiz_check()
{
    if (this_player()->query_wiz_level()) {
	set_alarm(1.0, -1.0, "check_carry");
	return 0;
    } else return 1;
}

void
check_carry() {
    if (!living(environment()) || environment()->query_npc())
	remove_object();
}

