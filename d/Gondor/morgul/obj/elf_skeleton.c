/*
 * /d/Gondor/morgul/obj/elf_skeleton.c
 *
 * The sad remains of a dead elf in a crevice 
 * leading off the ravine that leads up to 
 * Shelob's Lair
 *
 * Olorin, 21-December-1993
 */
inherit "/std/container";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void decay();

create_container()
{
    seteuid(getuid());

    set_name("skeleton");
    add_name(({"warrior","elf","corpse"}));

    set_short("skeleton of an elf warrior");
    set_long("@@long_desc");

    set_adj(({"elf"}));
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_MAX_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 15000);
    add_prop(CONT_I_MAX_VOLUME, 35000);
    add_prop(OBJ_M_NO_GET, "Let him rest in peace!\n");

    add_stuff();
    set_alarm(1200.0, 0.0, decay);
}

void decay()
{
    tell_object(ENV(TO), "The "+short()+" decays, crumbling to dust.\n");
    remove_object();
}

string long_desc()
{
    string  desc =
        "These are the sad remains of what once must have been a large and mighty " +
        "elf warrior. The skeleton was hidden by rubble and rocks, and must have " +
        "been lying here for a long, long time already.";

    return BSN(desc);
}

void add_stuff()
{
    clone_object(MORGUL_DIR + "obj/elfdagger")->move(TO);
    clone_object(MORGUL_DIR + "obj/hook")->move(TO);
}
