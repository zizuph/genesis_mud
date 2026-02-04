/*
    Moved: 13 June 2003, by Bleys
        - Moved from /d/Terel/common/town/guitar.c to
            /d/Terel/calathin/obj/guitar.c so that the
            new Calathin wouldn't reference the old
            when this object is cloned (by ../npc/guiplayer.c)
	Lilith Apr 2022: made a holdable object per Ckrik's request
        Lilith May 2022: Oops, forgot the leave_env mod.

*/
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";
#include <stdproperties.h>
#include <macros.h>

#define TP   this_player()

public void
create_object()
{
    set_name("guitar");
    set_adj(({"large", "wooden"}));
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    set_keep(1);
	
    set_long("A fine guitar made of exotic woods.\n");
	
	if (IS_CLONE)
        set_item_expiration();
}

public int
do_play(string str)
{
  if (!id(str)) return 0;
  
  write("You play a melody on the " + short() + ".\n");
  say(QCTNAME(TP) + " plays a melody on " + TP->query_possessive() +
      " " + short() + ".\n");
  return 1;
}


// need to add this to make sure held items are released when leaving inventory.
void 
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}


public void
init()
{
    ::init();
    add_action(do_play,"play");
}

string
query_recover()
{
     return MASTER + ":";
}

