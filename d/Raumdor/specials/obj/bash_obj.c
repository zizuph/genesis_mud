#pragma strict_types
    
inherit "/d/Genesis/specials/std/stun_obj_base";

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_bash_stun_obj");
    add_name( ({"bash_stun_obj" }) );
    set_short("hidden bash stun object");    
    set_long("A bash stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());
}

public void
hook_stun_begin(object attacker, object target)
{
    // Messages handled in attack
}

