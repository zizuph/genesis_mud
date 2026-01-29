/*
 *  /d/Gondor/common/guild2/newnpc/mage_guard.c
 *
 *  Standard guard for the Tower of Black Sorcery.
 *
 *  Created by Olorin, November 1995
 *  Updated to work with the new spell system, Eowul, September 2004
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/newnpc/npc_mage.c";

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/halberd", MORGUL_DIR + "obj/spear", \
                     MORGUL_DIR + "obj/waraxe", MORGUL_DIR + "obj/battleaxe", \
                     MORGUL_DIR + "obj/orcmace", MORGUL_DIR + "obj/stabsword"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/blackcap"})
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/chainmail"})
#define ARM_ARRAY3 ({ })

/*
 * Prototypes
 */

/*
 * Global variables
 */
static int     alarm_id;
static object *invaders_in = ({}),
              *invaders_out = ({});

void
create_mage()
{
    seteuid(getuid());

    set_name(({ "guard", "apprentice", }));
    set_adj("young");
    set_adj("grim");
    set_race_name("human");

    default_config_npc(50 + random(21));
    set_base_stat(SS_INT, 60 + random(21));
    set_base_stat(SS_WIS, 60 + random(21));

    add_prop(LIVE_I_SEE_DARK, 2);

    set_chat_time(15+random(15));

    set_cchat_time(5+random(10));

    set_act_time(15+random(15));

    set_cact_time(2+random(2));
    add_cact("hiss");
    add_cact("growl");
    add_cact("@@emote_enemy|snarl");
}

int     query_knight_prestige() { return  (- query_alignment()); }


void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
    Arm3 = ARM_ARRAY3;

    MONEY_MAKE_CC(100)->move(TO);
}

/*
    Nonzero size of invaders_in or invaders_out denotes whether
    people are coming or going from the Tower.
*/

void
send_message()
{
    int     i,
            s;
    object *mages;
    string *names = ({}),
            msg = "";
    alarm_id = 0;
    if (! (sizeof(invaders_in) || sizeof(invaders_out)))
        return;

    mages = query_mage_list_by_rank();
    if (!sizeof(mages))
        return;

    invaders_in -= ({ 0 });
    if (sizeof(invaders_in))
    {
        for (i = 0, s = sizeof(invaders_in); i < s; i++)
            names += ({ LANG_ADDART(invaders_in[i]->query_nonmet_name()) });
        msg += CAP(COMPOSITE_WORDS(names))
            + (s == 1 ? " has" : " have") + " entered the Tower";
        invaders_in = ({});
        names = ({ });
    }

    invaders_out -= ({ 0 });
    if (sizeof(invaders_out))
    {
        for (i = 0, s = sizeof(invaders_out); i < s; i++)
            names += ({ LANG_ADDART(invaders_out[i]->query_nonmet_name()) });
        if (strlen(msg))
            msg += " and " + COMPOSITE_WORDS(names);
        else
            msg += CAP(COMPOSITE_WORDS(names));
        msg += (s == 1 ? " has" : " have") + " exited from the Tower";
        invaders_out = ({});
    }

    if (!strlen(msg))
        return;

    command("unwield all");
    set_alarm(7.0, 0.0, &command("wield "+weapon_name));
    command("cast palanquendo "+mages[0]->query_real_name()+" "+msg+"!");
}

/*
 * Function name: give_alarm
 * Description:   alert the guards to inform the Society
 * Arguments:     invader - the object pointer to the living
 *                dir - 0 entering, 1 leaving
 */
void
give_alarm(object invader, int dir)
{
    if (dir == 0)
    {
        invaders_in += ({ invader });
        command("rasp I have to alert the Society, an intruder has entered!");
    }
    else if (dir == 1)
    {
        invaders_out += ({ invader });
        command("rasp I have to alert the Society, an intruder has exited!");
    }

    if (alarm_id && sizeof(get_alarm(alarm_id)))
        return;
    alarm_id = set_alarm(4.0 + 4.0 * rnd(), 0.0, &send_message());

    if (!present("copper coin"))
        MONEY_MAKE_CC(100)->move(TO);
}

void
init_living()
{
    ::init_living();

    if (IS_MORGUL_MAGE(TP))
        set_alarm(1.0, 0.0, &command("hail "+TP->query_real_name()));
}

