/* A sword made by Halgor 1/4/93 */
 
/* graveyard/wep/evil_sword.c  is clone by graveyard/npc/skeleton_lord */
 
 
inherit "/std/weapon";
 
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Emerald/defs.h"
 
 
void
create_weapon()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("sword");
    set_long("@@my_long");
    set_adj("evil");
 
    set_hit(25);
    set_pen(33);
 
    set_wt(W_SWORD);
    set_dt(W_SLASH);
 
    set_hands(W_ANYH);
 
 
    add_prop(OBJ_I_VOLUME,10000);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25,33) - random(100) + 50);
 
    set_wf(this_object());
 
}
 
 
 
 
string
my_long()
{
    if (this_player()->query_alignment() >= 0)
        return "This is a dark broadsword, with a blade that that seems to"+
            " radiate evil. You feel it would be unwise to wield such an "+
            "unholy weapon.\n";
 
    return "A dark and evil broadsword, that looks like a powerful weapon if "+
        "wielded in the right hands.\n";
}
 
 
public int
wield (object wep)
{
    if (this_player()->query_alignment()>=0)
    {
        this_player()->heal_hp(-(this_player()->query_max_hp())
            *(random(20) + 1) / 100);
 
        if (this_player()->query_hp() <= 0)
            this_player()->do_die(this_object());
 
        write( "As you try to wield the sword, a feeling of "+
            "extreme pain begins to creep up your arm.\n" );
 
        return -1;
    }
 
    return 0;
}
 
