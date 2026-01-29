/* This comment tells emacs to use c++-mode  -*- C++ -*- */
inherit "/std/weapon";
inherit "/lib/keep";

/* This must be here if the weapon should be throwable, which
 * it can be if /d/Terel/std/weapon_throw also is inherited
 */
public void
init()
{
    ::init();
    
    if (this_object()->query_throwable_weapon() &&
        environment(this_object()) == this_player())
        add_action("throw", "throw");
}
