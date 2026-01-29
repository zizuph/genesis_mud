/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/stand.c
 * Purpose    : Some stands to hold stuff
 * Located    : ~khiraa/temple/rooms/temple_lp_train
 * Created By : Sarr 12.Mar.97
 * Modified By: 
 */ 

#pragma save_binary
#pragma strict_types

inherit "/std/container.c";
inherit "/lib/keep.c";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

void
add_items()
{
    seteuid(getuid());
    clone_object(KHIRAA_DIR(temple/obj/finger_chain))->move(TO);
    clone_object(KHIRAA_DIR(temple/obj/demon_beads))->move(TO);
    clone_object(KHIRAA_DIR(temple/obj/skull_ring))->move(TO);
    clone_object(KHIRAA_DIR(temple/obj/cer_dagger))->move(TO);
    clone_object(KHIRAA_DIR(temple/obj/join_bowl))->move(TO);
    clone_object(KHIRAA_DIR(temple/obj/join_chain))->move(TO);
}

public void
create_container()
{
    set_name("stand");
    set_adj("heavy");
    add_adj("silver");

    set_short("heavy silver stand");

    set_long("This is a heavy stand made of silver. It is ornately "+
    "carved with many symbols and skulls. It is used to contain holy "+
    "items of the Khiraa that are used in rituals.\n");

    add_prop(CONT_I_RIGID,          0);
    add_prop(CONT_I_WEIGHT,     10000);
    add_prop(CONT_I_VOLUME,     10000);
    add_prop(CONT_I_MAX_WEIGHT, 90000);
    add_prop(CONT_I_MAX_VOLUME, 90000);
    add_prop(OBJ_M_NO_GET,1);
    add_items();
}

