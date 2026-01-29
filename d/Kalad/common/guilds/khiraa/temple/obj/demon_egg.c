inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/demon_egg.c
 * Purpose    : Summons an imp to serve someone as a container.
 * Located    : Bought from the lich werners
 * Created By : Sarr 7.Jun.97
 * Modified By: 
 */


void
create_object()
{
    set_name("egg");
    add_name("midnight-black");

    set_short("midnight-black egg");

    set_long("You hold a small, pure black egg-shaped rock. It has "+
    "many tiny and intricate symbols along its surface. In the very "+
    "center, there is a pentagram with the word 'break' etched in.\n");

    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,1008);
}

int
do_break(string st)
{
    object imp;
    seteuid(getuid());
    NF("Break what?\n");
    if(st != "egg")
        return 0;
    if(!IS_LP(TP) && !IS_DK(TP))
    {
        write("You throw the egg down to the ground and watch it "+
        "shatter into a million shards, then fade away.\n");
        say(QCTNAME(TP)+" throws a "+short()+" down to the ground, "+
        "and it shatters into a million shards, then fades away.\n");
        remove_object();
        return 1;
    }
    imp = clone_object(KHIRAA_DIR(temple/obj/imp));
    write("Chanting the magic summoning words, the "+short()+" in your "+
    "hands splits open, and a "+imp->short()+" slowly forms out if it, "+
    "at your service.\n");
    say(QCTNAME(TP)+" chants strange words, and the "+short()+" in "+HIS(TP)+
    " hands splits open, and a "+imp->short()+" slowly forms out of it.\n");
    imp->move(TP);
    remove_object();
    return 1;
}

void
init()
{
    ::init();
    AA(do_break,break);
}

