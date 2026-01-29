/* Coded by Ckrik February 1998
 * A clam that lives in the sands of the beach.
 */

#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>

#define CRUSHED_SHELL "/d/Earthsea/gont/beach/obj/clam_shell"
#define CLAM_SHELL "/d/Earthsea/gont/beach/obj/clam_shell_whole"
#define CONTAIN_WATER "_contain_water"

#define A_CLAMP 100
#define A_SPIT 101

#define H_SHELL 100

private int death_delay, alarm_on = 0;

public void
create_creature()
{
    int clam_type = random(3);
    string size = ({"small", "large", "small", "large"})[clam_type],
        color = ({"grey", "grey", "brown", "brown"})[clam_type];

    set_name("clam");
    set_pname("clams");
    set_race_name("clam");
    set_short(size + " " + color + " clam");
    set_pshort(size + " " + color + " clams");
    set_adj(size);
    add_adj(color);

    set_long(
        ({
            "A small grey clam. The locals call it " +
            "the duck clam. This species of " +
            "clams is common throughout the sandy " +
            "beaches of Gont. This particular clam is " +
            "about the size of a coin and " +
            "far too small to be full grown.\n",

             "A large grey clam. The locals call it " +
             "the duck clam. This species of " +
             "clams is common throughout the sandy " +
             "beaches of Gont. This particular clam is " +
             "about the size of a small stone and " +
             "full grown.\n",

             "A small brown clam. It is called " +
             "the surf clam. This species of clams " +
             "is common throughout the sandy " +
             "beaches of Gont. It does not like mud " +
             "and thus it prefers clean, mud free, " +
             "sand. This particular clam is " +
             "not quite full grown.\n",

             "A large brown clam. It is called " +
             "the surf clam. This species of clams " +
             "is common throughout the sandy " +
             "beaches of Gont. It does not like mud " +
             "and thus it prefers clean, mud free, " +
             "sand. This particular clam is " +
             "full grown.\n"
        })[clam_type]
    );

    remove_prop(OBJ_M_NO_GET);
    set_stats(({2, 2, 2, 2, 2, 2}));
    set_skill(SS_DEFENCE, 5);
    set_skill(SS_UNARM_COMBAT, 10);

    set_hp(10);
    set_attack_unarmed(A_CLAMP, 10, 5, W_BLUDGEON, 70, "clamping shells");
    set_attack_unarmed(A_SPIT, 15, 3, W_BLUDGEON, 30, "spit");

    set_hitloc_unarmed(H_SHELL, 10, 100, "shell");
    add_leftover(CRUSHED_SHELL, "shell", 1, 0, 0, 0);

    if(clam_type % 2 != 0)
    {
        add_prop(OBJ_I_WEIGHT, 250);
        add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
        add_prop(CONT_I_WEIGHT, 250);
        add_prop(CONT_I_VOLUME, query_prop(CONT_I_WEIGHT));
    } else {
        add_prop(OBJ_I_WEIGHT, 150);
        add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
        add_prop(CONT_I_WEIGHT, 150);
        add_prop(CONT_I_VOLUME, query_prop(CONT_I_WEIGHT));
    }
}

public void
clam_not_fresh()
{
    object corpse;

    remove_leftover("shell");
    add_leftover(CLAM_SHELL, "shell", 1, 0, 0, 0);

    corpse = clone_object("/std/corpse");
    corpse->set_name(query_name());
    corpse->change_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
    corpse->change_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
    corpse->add_prop(CORPSE_S_RACE, query_race_name());
    corpse->add_prop(CONT_I_TRANSP, 1);
    corpse->change_prop(CONT_I_MAX_WEIGHT,
                        query_prop(CONT_I_MAX_WEIGHT));
    corpse->change_prop(CONT_I_MAX_VOLUME,
                        query_prop(CONT_I_MAX_VOLUME));
    corpse->set_leftover_list(query_leftover());
    corpse->move(environment(this_object()), 1);

    move_all_to(corpse);

    remove_object();
}

public void
enter_env(object to, object from)
{
    int water = (to->query_prop(CONTAIN_WATER) ||
        to->query_prop(OBJ_I_CONTAIN_WATER));

    ::enter_env(to, from);

    if(alarm_on)
    {
        if(water)
        {
            remove_alarm(death_delay);
            alarm_on = 0;
            return;
        }
    } else {
        if(!water)
        {
            death_delay = set_alarm(180.0, 0.0, clam_not_fresh);
            alarm_on = 1;
        }
    }
}
