/* 
 * Cotillion - 2017-05-19
 * - Fixed runtime
 */

inherit "/std/shadow";

#include "../trickster.h"
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <language.h>

#define SW shadow_who

//   Prototpyes
mixed my_no_get();
void move_me(object player);
void remove_string_shadow();

object Setter;
string Oldprop;

public varargs string
short(object for_obj)
{
    if (!ENV(SW))
        return SW->short(for_obj);

    string extra;
    switch(for_obj->query_skill(SS_AWARENESS))
    {
    case 0..35:
	extra = "";
	break;
    case 36..70:
	extra = " with a string attached";
	break;
    default:
	if (present(Setter,ENV(SW)) || present(Setter,ENV(ENV(SW))))
	    extra = " with a string attached, which leads to "+
	    Setter->query_the_name(for_obj);
	else
	    extra = " with a string attached, that leads to nothing";
	break;
    }
    if (for_obj == Setter || ENV(ENV(SW)))
	return SW->short(for_obj);
    else
	return SW->short(for_obj) + extra;
}

varargs public mixed
long(string str, object for_obj)
{
    if (!ENV(SW))
        return SW->long(str,for_obj);

    string extra;
    switch(for_obj->query_skill(SS_AWARENESS))
    {
    case 0..35:
	extra = "";
	break;
    case 36..70:
	extra = "There is a string attached this object for some reason.\n";
	break;
    default:
	if (present(Setter,ENV(SW)))
	    extra = "There is a string attached to this object leading towards "+
	    Setter->query_the_name(for_obj);
	else
	    extra = "There is a string attached to this object.\n";
	break;
    }
    if (for_obj == Setter)
	return SW->long(str,for_obj);
    else
	return SW->long(str,for_obj) + extra;
}

void
set_up_trap(object who)
{
    Setter = who;
    if (SW->query_prop(HEAP_I_IS))
    {
	Oldprop = SW->query_prop(HEAP_S_UNIQUE_ID);
	SW->add_prop(HEAP_S_UNIQUE_ID, Oldprop + "_string");
    }
}

mixed
query_prop(string prop)
{
    if (prop == OBJ_M_NO_GET)
	return my_no_get();
    return SW->query_prop(prop);
}

mixed
my_no_get()
{
    if (TP == Setter)
    {
	remove_string_shadow();
	return 0;
    }
    if (present(Setter, ENV(SW)))
    {
	if (!random(10))
	{
	    Setter->catch_msg("You were too slow in pulling the string and "+
	      QTNAME(TP)+" manages to get "+LANG_THESHORT(SW)+".\n");
	    TP->catch_msg("As you pick up "+LANG_THESHORT(SW)+" you feel a slight "+
	      "tug as "+QTNAME(Setter)+" tries to pull it away from you by "+
	      "tugging on a string that was attached to "+LANG_THESHORT(SW)+"!\n");
	    remove_string_shadow();
	    return 0;
	}
	shadow_who->set_no_merge(1);
	set_alarm(0.1,0.0,&move_me(TP));
	remove_string_shadow();
	return 0;
    }
    remove_string_shadow();
    return 0;
}

int
query_trickster_shadow()
{
    return 666;
}

void
remove_string_shadow()
{
    set_alarm(0.2,0.0,remove_shadow);
}

void
remove_shadow()
{
    if (Setter)
	Setter->remove_prop(TRICKSTER_STRING_PROP);
    if (Oldprop)
    {
	SW->add_prop(HEAP_S_UNIQUE_ID, Oldprop);
	SW->force_heap_merge();
    }
    destruct();
}

void
move_me(object player)
{
    tell_room(ENV(Setter),"As "+QTNAME(player)+" picks up "+
      LANG_THESHORT(SW) +" it is suddenly jerked away from "+HIM_HER(player)+
      " and lands in the hands of "+QTNAME(Setter)+"!\n",({player,Setter}));
    Setter->catch_msg("Just as "+QTNAME(player)+" picks up "+
      LANG_THESHORT(SW)+" you pull on your string and "+LANG_THESHORT(SW)+
      " lands in your hands.\n");
    player->catch_msg("As you pick up "+LANG_THESHORT(SW)+" it is "+
      "suddenly yanked away from you and lands in the hands of "+
      QTNAME(Setter)+"!\n");
    if (SW->move(Setter))
    {
	Setter->catch_msg("You are unable to carry "+LANG_THESHORT(SW)+
	  " so it falls to the ground.\n");
	tell_room(ENV(Setter), QCTNAME(Setter)+" is unable to carry "+
	  LANG_THESHORT(SW)+" so it falls to the ground.\n");
	SW->move(ENV(SW));
    }
}
