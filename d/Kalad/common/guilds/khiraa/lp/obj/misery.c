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
    set_adj("sickly");
    add_adj("yellow");
    set_short("sickly yellow potion");
    set_id_long("The potion is pure yellow in color, and is known "+
    "as misery. It glows with a sickly light, and is used by mad "+
    "necromancers to further death and decay.\n");
    set_unid_long("It is a strange potion that is sickly yellow.\n");
    set_unid_smell("It smells like piss.\n");
    set_id_smell("It smells like misery.\n");
    set_unid_taste("Cough!! Hack! Cough!\n");
    set_id_taste("It tastes like misery.\n");
    set_potion_name("misery");
    set_potion_value(400);
    set_effect(HERB_SPECIAL,"",0);
}

void
special_effect()
{
    object res;
    if(present("_miseryob_",TP))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    res = clone_object(LP_DIR(obj/misery_ob));
    res->move(TP);
    res->set_remove_time(800 + 6 * MAX(100,mixer_stats[0]));
}
        
