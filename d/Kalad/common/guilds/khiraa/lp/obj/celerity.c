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
    set_adj("pure");
    add_adj("snow-white");
    set_short("pure snow-white potion");
    set_id_long(my_long());
    set_unid_long("It is a strange potion that is pure white.\n");
    set_unid_smell("It smells like salt.\n");
    set_id_smell("It smells like celerity.\n");
    set_unid_taste("It tastes sour.\n");
    set_id_taste("It tastes like celerity.\n");
    set_potion_name("celerity");
    set_potion_value(900);
    set_effect(HERB_SPECIAL,"",0);
}

string
my_long()
{
    if(IS_DK(TP) || IS_LP(TP))
        return "This potion is called celerity, which is used "+
        "for the spell 'speed.' It is milky white, and has an "+
        "almost crystaline shine to it.\n";
    return "This potion is called celerity. It is milky white, and "+
    "has an almost crystaline shine to it.\n";
}


void
special_effect()
{
    object res;
    if(present("celerity_ob",TP))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    res = clone_object(LP_DIR(obj/celerity_ob));
    res->move(TP);
    res->set_remove_time(500 + 6 * MAX(100,mixer_stats[1]));
}
        
