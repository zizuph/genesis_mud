
// file name: silver_key.c
// creator(s): Ilyian, April 1995 (code borrowed from Grace)
// last update:
// purpose: key to the gate between green/s_shore and green/green17
// note:
// bug(s):
// to-do:

inherit "/std/key";
#include "../../bazaar.h"
#include "/d/Avenir/include/relation.h"
#include "/sys/stdproperties.h"

void     check();

void
create_key() 
{
    ::create_key();

    set_name("key");
    set_adj(({"silver", "intricate"}));
    set_pshort("large keyrings");
    set_short("intricate silver key");
    set_long("This is a beautiful key made from beaten silver and "
      +"lined with veins of obsidian stone. The craftsmanship is "
      +"like nothing you have ever seen.\n");

    set_key("_silver_gate_key_");

    add_prop(OBJ_M_NO_DROP, "You wish!\n"); 
    add_prop(OBJ_M_NO_GIVE, "You wish!\n"); 
    add_prop(OBJ_I_WEIGHT, 20000);    
    add_prop(OBJ_I_VOLUME, 30000);  
    add_prop(OBJ_M_NO_STEAL, "You can't quite seem to liberate it.\n"); 
    add_prop(OBJ_I_VALUE, 200);   // its silver
}

int
end_key(string str)
{
    if(!present(this_object(), this_player()))
    {
       NF("You would need to be holding it.\n");
       return 0;
    }

    if (str == "key")
    {
        set_alarm(0.0, 0.0, remove_object);
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();

   add_action(end_key, "bend");
}

void 
enter_env(object to, object from)
{
    ::enter_env(to, from);

    set_alarm(2.0, 0.0, check);
}

void 
check()
{
    object   who = environment(this_object());
    if(!IS_SYBARITE(who))
        set_alarm(0.0, 0.0, remove_object);      
}

