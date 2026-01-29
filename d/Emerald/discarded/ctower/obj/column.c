/* ctower/obj/colum.c is cloned by ctower/done1.c */
inherit "/std/container";

#include "../ctower.h"
#include "/d/Emerald/quest_handler/quest_handler.h"

#include <stdproperties.h>
#include <macros.h>

void reward_player(object ob);
void give_torque(object ob);
void give_reward(object ob, int step);
void start_speach(object ob);

void
create_container()
{
    set_name("column");
    add_name("ctower_colum");
    add_adj("crystal");
    set_long("This rectangular crystal column contains every color in "+
        "the spectrum swirling inside.  It stands about one " +
        "meter high, and each side is approximately six centimeters " +
        "across.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 3600);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
   
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_NO_GET, 1);
}

int
prevent_enter(object ob)
{
    object *items;

    if (ob->id("ctower_cube") && !id("fin_column"))
    {
        items = filter(all_inventory(environment()), &->id("fin_pillar"));
        if (sizeof(items) == 4)
	{
            return 0;
	}
    }

    write("The " + ob->short() + " resists being placed on " +
        "the " + short() + ".\n");
    return 1;
}

void
fuse(object cube)
{
    write("The " + cube->short() + 
        " fuses into place on the column, which starts to glow.\n");
    say(QCTNAME(this_player()) + " does something to the crystal " +
        "column and it starts to glow.\n");

    cube->remove_object();    
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob->id("ctower_cube"))
    {
        return;
    }

    add_name("fin_column");
    add_adj("glowing");
  
    set_long(query_long() + "The crystal column is glowing softly.\n");

    start_speach(this_player());

    set_alarm(0.0, 0.0, &fuse(ob));
}

void
start_speach(object ob)
{
    if (ob && present(ob, environment()))
    {
        set_alarm(4.0, 0.0, &give_reward(ob, 0));
    }
}
 
void
give_reward(object ob, int step)
{
    if (!ob || !present(ob, environment()))
    {
        return;
    }
  
    switch (++step) 
    {
    	case 1:
	    tell_room(environment(),"As soon as the cube fuses to "+
		"the column, each of the four pillars emit a radiant light "+
		"corresponding to its color.  This rainbow "+
		"of colors is captured and redirected by the pyramids "+
		"atop the pillars, focusing the lights onto the facets "+
		"of the cube.  The focused light lances out in a " +
		"scintilating cascade of colors blossoming from the top "+
		"of the cube.\n");
		break;
    	case 2:
	    ob->catch_msg("The dazzling display begins "+
	        "to sparkle and you begin to make out a crystal circlet "+
		"amongst the prismatic display.\n");
	    break;
    	case 3:
	    ob->catch_msg("A melodic voice, with just a hint "+
	        "of mischievousness, whispers in your mind:  You have proven "+
		"yourself both resourceful...and persistant.  I hereby judge "+
		"you worthy of the crystal torque.  It will be your "+
		"symbol of success in the Crystal Tower.\n");
	    break;
	case 4:
	    give_torque(ob);
	    ob->catch_msg("The torque floats over and "+
	        "settles comfortably around your neck.\n");
	    tell_room(environment(), "A torque floats over and settles "+
		"comfortably around " + QTNAME(ob) + "'s neck.\n", ob);
	    break;
	case 5:
	    ob->catch_msg("The voice continues:  Know that "+
	        "when the time is right you will be able to pass through yon "+
		"portal to seek further knowledge and adventure.  Also, if you "+
		"sing at either of the chandeliers you shall be transported "+
		"to the other.  This is the only egress currently available "+
		"to you.  It is also an easier means of reaching the portal "+
		"should the need arise.\n");
	    break;
	case 6:
	    ob->catch_msg("The voice says:  Good luck and good travels!\n");
	    break;
	case 7:
	    ob->catch_msg("With that the voice fades away, giggling merrily.  "+
	        "The lighting drops back to the softly "+
		"glowing pillars and column, leaving you with a profound sense "+
		"of accomplishment and a smile on your face.  Good travels " +
		"indeed!\n");
	    tell_room(environment(), "The lighting drops back to the softly "+
		  "glowing pillars and column.\n", ob);
	    break;
	default:
	    reward_player(ob);
	    return;
    }
  
    set_alarm(4.0, 0.0, &give_reward(ob, step));
}
 
void
reward_player(object ob)
{
    if (!ob || !present(ob, environment())) 
    {
        return;
    }

    setuid();
    seteuid(getuid());

    if (QH_QUEST_COMPLETED(ob, CTOWER_QUEST_NAME))
    {
        return;
    }
  
    QH_QUEST_COMPLETED(ob, CTOWER_QUEST_NAME);
    ob->catch_tell("You feel more experienced.\n");
}
 
void
give_torque(object ob)
{
    if (!ob || !present(ob, environment()))
    {
        return;
    }  
    
    if (!QH_QUEST_COMPLETED(ob, CTOWER_QUEST_NAME))
    {
        return;
    }
  
    if (!present("ctower_torque", ob))
    {
    	setuid();
    	seteuid(getuid());
    	clone_object(CTOWER_OBJ + "torque")->move(ob, 1);
    }
}

void
describe_contents(object for_obj, object *obarr)
{
    return;
}
