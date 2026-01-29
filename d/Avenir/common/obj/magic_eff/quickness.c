// file name:        quickness.c
// creator(s):       Denis, Aug'97
// revision history: 
// purpose:          To provide magical quickness/slowness for the spells.
// note:             
// bug(s):           
// to-do:            

# pragma strict_types
# include <stdproperties.h>

inherit "/std/object";
inherit "/d/Avenir/inherit/magic.object";

int	gQuickness;
string	gDispell_mess_onlookers = "",
	gDispell_mess = "";

void
create_object()
{
    add_name("_Avenir_quickness_obj");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "A magic effect to change the quickness.\n");

    set_no_show();
}

public void
set_quickness(int quickness)
{
    gQuickness = quickness;
}

public void
set_dispell_mess_onlookers(string message)
{
    gDispell_mess_onlookers = message;
}

public void
set_dispell_mess(string message)
{
    gDispell_mess = message;
}

public void
init_spell(object caster, object target)
{
    target->change_prop(LIVE_I_QUICKNESS,
			target->query_prop(LIVE_I_QUICKNESS) + gQuickness);
}

public void
notify_dispel_magic(object ob)
{
    tell_object(gMaster, gDispell_mess);
    tell_room(environment(gMaster), gDispell_mess_onlookers, gMaster);
    gMaster->add_prop(LIVE_I_QUICKNESS,
		      gMaster->query_prop(LIVE_I_QUICKNESS) - gQuickness);
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
