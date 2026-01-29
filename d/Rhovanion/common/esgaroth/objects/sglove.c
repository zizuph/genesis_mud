inherit "/std/object";
inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Rhovanion/defs.h"

create_object()
{
    set_name("glove");
    set_adj("silk");
    set_long("This glove is shaped too strangely for you to be able to " +
        "wear, but reminds you of the kind used to challenge people to a " +
        "fight.  It looks pretty worthless.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);

    add_prop(MAGIC_AM_ID_INFO, ({ "You could probably provoke someone into " +
        "a fight with it.\n", 25, "Slapping someone with it would probably " +
        "make them angry.\n", 40, "If you slap someone with it, they will " +
        "attack you if possible.\n", 70 }));
}

init()
{
    ::init();
//    add_action("make_challenge", "challenge");
/*
 * In the present implementation, this glove disables the check
 * on the discipline of the player when a player tries to attack
 * another living.
 * This can be used my teams to allow low level players to
 * participate in combat against much larger npcs.
 *
 * At the same time, since by using this glove, the player
 * can make the npcs attack him or her, instead of attacking
 * the npc, code that will make other npcs assist an attacked
 * npc is effectively disabled.
 *
 * I have therefore disabled this code.
 *
 * Olorin, 11-feb-1996
 */
}

int
make_challenge(string str)
{
    object *ob;
    int i;

    NF("Challenge whom?\n");
    if (!strlen(str))
        return 0;

    if (query_verb() == "challenge")    
        ob = parse_this(str, "%l");
    else
        ob = parse_this(str, "%l 'with' [the] [silk] 'glove'");
    if (!sizeof(ob))
        return 0;

    for (i = 0; i < sizeof(ob); i++)
    {
        if ((query_ip_number(ob[i])) || ob[i]->query_prop(OBJ_M_NO_ATTACK)
            || ENV(ob[i])->query_prop(ROOM_M_NO_ATTACK))
        {
            TP->catch_msg("You challenge " + QTNAME(ob[i]) + " to a fight by " +
                "slapping " + HIM(ob[i]) + " in the face with your glove.\n");
            ob[i]->catch_msg(QCTNAME(TP) + " challenges you to a fight, " +
                "slapping you in the face with " + HIS(TP) + " glove.\n");
            say(QCTNAME(TP) + " slaps " + QTNAME(ob[i]) + " with " + HIS(TP)
                + " glove.\n", ({ TP, ob[i] }));
        }
        else
        {
            TP->catch_msg("You challenge " + QTNAME(ob[i]) + " to a fight, " +
            "by slapping " + HIM(ob[i]) + " with your glove, and " + HE(ob[i]) +
                " attempts to oblige you.\n");
            ob[i]->catch_msg(QCTNAME(TP) + " challenges you to a fight, " +
                "slapping you in the face with " + HIS(TP) + " glove, and " +
                "you feel compelled to oblige " + HIM(TP) + ".\n");
            ob[i]->command("kill " + TP->query_real_name());
        }
    }
    return 1;
}
