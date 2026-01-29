#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <herb.h>
inherit "/std/potion.c";

/* skaltakur */

int gTime;
int *mixer_stats;

string my_long();
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
    set_adj("stagnant");
    add_adj("brownish");
    set_short("stagnant brownish potion");
    set_id_long(my_long());
    set_unid_long("It is a strange potion that is brown and blackish "+
    "and looks putrid.\n");
    set_unid_smell("It smells like vomit.\n");
    set_id_smell("It smells like vomit.\n");
    set_unid_taste("It tastes rotting flesh.\n");
    set_id_taste("It tastes like rotting flesh.\n");
    set_potion_name("rot");
    set_potion_value(800);
    set_effect(HERB_SPECIAL,"",0);
}

string
my_long()
{
    if(IS_DK(TP) || IS_LP(TP))
        return "This potion is called rot, which is used "+
        "for the spell 'hands.' It is brownish black, and has a "+
        "stagnant quality to it.\n";
    return "This potion is called rot. It is brownish black, and has "+
    "a stagnant quality to it.\n";
}


void
special_effect()
{
    object res;
    if(present("rot_ob",TP))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    res = clone_object(LP_DIR(obj/rot_ob));
    res->move(TP);
    res->set_remove_time(500 + 6 * MAX(100,mixer_stats[1]));
}
        
