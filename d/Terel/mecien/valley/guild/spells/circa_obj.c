/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/*
 * This is a magic shield, protecting the wearer from blows.
 * It is invoked when the mystic order spell 'tueri' is
 * being cast successfully.
 */
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define MIN_DUR 10
#define MAX_DUR 2500
#define TO      this_object()
#define ENV environment

public void remove_shield();

object who=0;

query_recover(){ return 0; }
public void
create_armour()
{
  set_name("circa_obj");
    add_name("white_circle");
    set_adj("white");
    set_no_show();
    add_prop(OBJ_I_INVIS, 2);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MYSTIC_ARMOUR, 1);
    set_default_armour(12, A_MAGIC);
}

set_strength(int s){
  set_default_armour(s, A_MAGIC);
}

public void
set_duration(int dur)
{
    if (dur < MIN_DUR) dur = MIN_DUR;
    if (dur > MAX_DUR) dur = MAX_DUR;
    set_alarm(itof(dur), -1.0, remove_shield);
}

public void
enter_env(object dest, object old)
{
    ::enter_inv(dest, old);
    
    if (dest && living(dest)) {
        who = dest;
   who->catch_msg("The power of the white circle energizes the spirit world about you.\n");
  tell_room(ENV(who), QCTNAME(who) + " is surrounded momentarily by a sphere of white light.\n", who);
        who->wear_arm(TO);
    } else {
        who = 0;
    }
}

int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

public void
remove_shield()
{
    if (who) {
    who->catch_msg("The power of the white circle fades away.\n");
        who->remove_arm(TO);
    }
    remove_object();
}
