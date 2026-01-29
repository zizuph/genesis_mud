/*
 * /d/Shire/charity/hob_box.c
 * Hobbiton Charity box
 * -- Finwe, February 2006
 */

inherit "/d/Shire/charity/base_cbox.c";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <filter_funs.h>

#define CHAR_DIR    "/d/Shire/charity/"
#define WEP_DIR     (CHAR_DIR)

void create_container()
{

    setuid();
    seteuid(getuid());

    set_name("charity box");
    add_name("box");
    set_long("This is a large box set alongside the road where generous " +
        "hobbits or travellers may donate extra equipment, weapons, or " +
        "things younger players may need. If you accidentally donate " +
        "something, you may retrieve it from the box.\n\n");

    add_prop(CONT_I_WEIGHT,      100000);   /* Empty box weighs 100 Kg.  */
    add_prop(CONT_I_VOLUME,      800000);   /* Max 0.8 m^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 1000000);   /* The box can max hold 1000 Kg. */
    add_prop(CONT_I_MAX_VOLUME,  920000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,            1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,            1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,           1);   /* Transparent.*/

    enable_reset();
    set_alarm(1.0, 0.0, "reset_container");
}

void
reset_container()
{
 int i = 0,
    rand_num = 4;

// weapons
/*
    fill_box(CHAR_DIR + "jagged_knife", "ch_knife", 4);
    fill_box(CHAR_DIR + "ch_dagger", "ch_dagger", 4);
    fill_box(CHAR_DIR + "ch_shortsword", "_ch_shortsword_", 4);
    fill_box(CHAR_DIR + "round_shield", "_ch_round_shield_", 4);
    fill_box(CHAR_DIR + "ch_pitchfork", "_ch_pitchfork_", 4);
    fill_box(CHAR_DIR + "ch_rapier", "_ch_rapier_", 4);
    fill_box(CHAR_DIR + "ch_spear", "_ch_spear_", 4);
    fill_box(CHAR_DIR + "ch_hickclub", "_ch_hickclub_", 4);
*/

/*
    if (!present("ch_knife"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "jagged_knife")->move(TO);
        }
    }

    if (!present("ch_dagger"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_dagger")->move(TO);
        }
    }

    if (!present("_ch_shortsword_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_shortsword")->move(TO);
        }
    }

    if (!present("_ch_round_shield_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "round_shield")->move(TO);
        }
    }

    if (!present("_ch_pitchfork_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_pitchfork")->move(TO);
        }
    }

    if (!present("_ch_rapier_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_rapier")->move(TO);
        }
    }

    if (!present("_ch_spear_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_spear")->move(TO);
        }
    }

    if (!present("_ch_hickclub_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_hickclub")->move(TO);
        }
    }
*/

// armours
/*
    fill_box(CHAR_DIR + "ch_cmail", "_ch_cmail_", 4);
    fill_box(CHAR_DIR + "ch_helm", "_ch_helm_", 4);
    fill_box(CHAR_DIR + "ch_igreaves", "_ch_igreaves_", 4);
    fill_box(CHAR_DIR + "ch_lbracers", "_ch_lbracers_", 4);
    fill_box(CHAR_DIR + "ch_lgreaves", "_ch_lgreaves_", 4);
    fill_box("/d/Sparkle/area/faerie/arm/ch_pmail", "_ch_pmail_", 4);
*/


   
}
