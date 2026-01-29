/* chargeob.c: For gladiator setcharge command: Serpine, 11/27/95. */
 
#pragma save_binary
#pragma strict_types
 
inherit "/std/object";
#include "defs.h"
 
string charge_desc = "charge";
 
string
query_auto_load()
{
    return (MASTER_OB(this_object()) + ":#d#" + charge_desc + "#");
}
 
void
init_arg(string arg)
{
    string garbage;
 
    if (!strlen(arg)) return;
    sscanf(arg, "%sd#%s#%s", garbage, charge_desc, garbage);
}
 
void
create_object()
{
    set_name("chargeob");
    add_name("_glad_charge_ob_");
 
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_INVIS, 100);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    set_no_show();
}
 
string return_charge_desc() { return charge_desc; }
 
void
set_charge_desc(string new_desc)
{
    if (new_desc=="charge") remove_object();
    charge_desc = new_desc;
    return;
}
 
void enter_env(object env, object from)
{
    ::enter_env(env, from);
    if(!IS_MEMBER(env)) remove_object();
/*  if (CHECK_PUNISHMENT(BAR, env->query_real_name())) remove_object(); */
    if((env->query_gladiator_level()) < CHARGE_OB_LEVEL) remove_object();
}

