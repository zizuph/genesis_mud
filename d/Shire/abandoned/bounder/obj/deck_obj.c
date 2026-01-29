/*********************************************************
 ****  deck_obj.c  This object is cloned into the target's  
 ****  inventory when a bounder successfully "decks" an
 ****  opponent. Jaypeg, 27th Oct 1997
 ****/
#pragma save_binary

inherit "/std/object";
inherit "../guild.h";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_ types.h>

static int offset;


void
create_object()
{
    set_short("Bounder deck object");
    set_long("This is the object that is cloned into a target's "+
      "inventory when successfully "decked" by a bounder. This "+
      "object reduces the target's defence by a percentage depending "+
      "on the success of the special.\n");

    set_no_show();


    add_prop(OBJ_M_NO_DROP, 1);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT); 
    remove_prop(OBJ_I_VALUE);

}

void
set_offset(int offset)
{
if (living(env))
{
env->set_skill_extra(SS_DEFENSE, env->query_skill(SS_DEFENSE) * 2);
}
}

void
leave_env(object env, object from)
{
::leave_env(env, from);
remove_object
}
