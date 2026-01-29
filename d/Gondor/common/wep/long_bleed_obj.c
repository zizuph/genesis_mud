/* 
 *Bleeding object, to work with the haradrim shamshir. long bleed time
 *Altrus, July 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define IS_BLD "_bleeding_shamshir_wound"

void
create_object()
{
    set_name("_bleeding_object");
    add_name("_invis_item");
    set_short("invisible item");
    set_long("If you can see this, 'bug _invis_item' so I know I totally goofed up on it.\n");
    
    //No peaky ;)
    set_no_show();

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME,  0);

}

void
reset_bleed(object me)
{
    me->remove_prop(IS_BLD);
    TO->remove_object();
}

void
close_wound(object me)
{
	write("The deep wound closes and the bleeding stops.\n");
	say(QCTNAME(me)+ "'s deep wound stops bleeding.\n",me);
	me->remove_subloc("_long_bleeding");
	set_alarm(25.0, 0.0, &reset_bleed(me));
}

void
bleed_me(object me, int stage)
{
    float time;

   switch (stage)
    {
    case 1:
    write("The deep wound bleeds, leaving you feeling weak.\n");
    say(QCTNAME(me)+ "'s deep wound bleeds slightly.\n",me);
    time = 10.5;
    break;
    case 2:
    write("Your deep wound bleeds some more, draining you physically.\n");
    say(QCTNAME(me)+"'s deep wound bleeds some more.\n",me);
    time = 15.5;
    break;
    case 3:
    write("The wound oozes blood.\n");
    say(QCTNAME(me)+"'s wound oozes blood.\n",me);
    time = 10.5;
    break;
    case 4:
    write("The deep wound spurts blood all over the ground. You feel a little dizzy.\n");
    say("Blood spurts from " +QCTNAME(me)+"'s deep wound.\n",me);
    time = 20.5;
    break;
    case 5:
    write("Blood flows freely from your deep wound.\n");
    say("Blood flows freely from " +QCTNAME(me)+ "'s deep wound.\n",me);
    time = 10.0;
    break;
    case 6:
    write("Your shallow wound bleeds some more, draining you physically.\n");
    say(QCTNAME(me)+"'s shallow wound bleeds some more.\n",me);
    time = 10.5;
    break;
    default:
    return;
    }
    if(stage < 6)
    {
	me->heal_hp(-(50+random(350)));
        set_alarm(time, 0.0, &bleed_me(me, ++stage));
    }
    else
    {
	me->heal_hp(-(50+random(350)));
	set_alarm(time, 0.0, &close_wound(me));
    }
}

void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    to->add_subloc("_long_bleeding", this_object());
    set_alarm(15.0, 0.0, &bleed_me(to,1));
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if(subloc!="_long_bleeding")
      return "";

    //What they see in their inventory
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
 
    //What they see when they examine themselves
    if (for_obj == me)
        return "You are bleeding from a deep wound!\n";
    
    //What others see when they examine the welt-haver
    else
        return CAP(HE_SHE(me))+" is bleeding from a deep wound!\n";
}
