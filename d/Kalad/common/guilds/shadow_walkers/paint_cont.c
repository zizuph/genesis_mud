inherit "/std/object";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_object()
{
    set_name("tin");
    set_adj("tiny");
    add_adj("steel");
    set_short("tiny steel tin");
    set_long("This is a small, circular container made of "+
    "steel. A tight lid contains the black paint that is "+
    "inside of it. To use the paint, one must 'apply "+
    "paint on face'. And to remove it, use 'rub paint off face'.\n");
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,11);
    add_prop(OBJ_I_VALUE,0);
}

void
init()
{
    ::init();
    AA(do_apply,apply);
}

int
do_apply(string str)
{
    NF("Apply what?\n");
    if(str != "paint on face")
        return 0;
    NF("You already have some paint on!\n");
    if(TP->query_prop("_kalad_has_black_paint"))
        return 0;
    write("You open the tin.\n");
    say(QCTNAME(TP)+" opens the tin.\n");
    write("You smear the black paint within on your face, making "+
    "sure no part is left uncovered.\n");
    say(QCTNAME(TP)+" smears the black paint within on "+HIS(TP)+" face.\n");
    seteuid(getuid());
    clone_object("/d/Kalad/common/guilds/shadow_walkers/black_paint")->move(TP);
    write("You feel like you can hide better now.\n");
    remove_object();
    return 1;
}

