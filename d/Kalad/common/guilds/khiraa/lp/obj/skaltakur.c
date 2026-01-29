#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <herb.h>
inherit "/std/potion.c";

/* skaltakur */

int gTime;
int *mixer_stats;

void
set_mixer_stats(int *i)
{
    /* ({ int, wis, gs }) */
    mixer_stats = i;
}


void
create_potion()
{
    set_name("potion");
    set_adj("sparkling");
    add_adj("purple");
    set_short("sparkling purple potion");
    set_id_long("This potion is called skaltakur, which is used "+
    "for the spell 'drain.' It sparkles with an eerie light.\n");
    set_unid_long("It is a strange potion that is deep purple. It "+
    "sparkles with an eerie light.\n");
    set_unid_smell("It smells bad.\n");
    set_id_smell("It smells like nightshade.\n");
    set_unid_taste("It tastes rather bad.\n");
    set_id_taste("It tastes rather bad.\n");
    set_potion_name("skaltakur");
    set_potion_value(1200);
    set_effect(HERB_SPECIAL,"",0);
}

void
special_effect()
{
    object res;
    if(present("skaltakur_ob",TP))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    res = clone_object(LP_DIR(obj/skaltakur_ob));
    res->move(TP);
    res->set_remove_time(500 + 6 * MAX(100,mixer_stats[0]));
}
        
