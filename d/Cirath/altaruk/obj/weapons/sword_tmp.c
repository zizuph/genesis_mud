inherit "/std/weapon";
#include "/sys/wa_types.h"
#include <stdproperties.h>

void create_weapon()
{
    set_name ("sword");
    set_pname("sword");
    set_adj  ("obsidian");
    set_short("obsidian sword");
    set_pshort("obsidian swords");
    set_long ("A sword with an obsidian blade.\n");

    set_hit(25);
    set_pen(25);
    likely_dull=30;
    likely_corr=-1;
    likely_break=30;

    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1000);
}
