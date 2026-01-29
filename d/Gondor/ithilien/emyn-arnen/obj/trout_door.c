inherit "/std/door";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"

#define BSW_GATE_ISILDUR	"_bsw_gate_isildur"

void
create_door()
{
    set_other_room(ITH_DIR + "emyn-arnen/palace/treasury");
    set_door_id("Emyn-Arnen_Treasury_Gate");
    set_door_name(({"steel gate", "large gate", "heavy gate", "magic gate", "gate"}));
    set_door_desc(VBFC_ME("long_desc"));
    set_lock_name(({"lock", "keyhole"}));
    set_lock_desc(BSN("You can see neither a keyhole nor a lock "
      + "on the door."));
    set_unlock_command(({"call", "unlock", "xcall"}));
    set_no_pick();

    set_pass_command("south");

    set_open(0);
    set_locked(1);

    set_str(40);

    FIX_EUID
}

void
destruct_room(object pl, string arg)
{
    FIX_EUID
    TP->remove_prop(BSW_GATE_ISILDUR);
    ENV(TO)->destruct_room(pl, arg);
}

void
check_spelling(string arg, object pl)
{
    mixed   gondor = BSW_QUEST_MASTER->query_rulers("gondor"),
            arnor = BSW_QUEST_MASTER->query_rulers("arnor");

    if ( (member_array(arg, gondor) >= 0) ||
         (member_array(arg, arnor) >= 0))
    {
        set_alarm(0.0, 0.0, "destruct_room", pl, arg);
        NF("The gate starts glowing in a fierce red light!\n");
        return;
    }
    pl->catch_msg(BSN("You hear a whisper in your head: "
      + "Leave before you die, fool!"));
    NF("The blue glow of the gate remains unchanged.\n");
}

/*
 * Function name: lock_procedure
 * Description:   This function is called to determine if
 *		  a lock can be locked/unlocked.
 *
 *  Two methods are used here:
 *
 *  1: No key. You unlock by typing "<command> <door_id>".
 *  2: Key. You unlock by typing "<command> <door_id> with <key_id>".
 *
 * Arguments:	  arg - the argument given to the command lock/unlock
 * Returns:       1 - Ok, 0 - Fail.
 * 
 */
int
lock_procedure(string arg)
{
    object  tp = TP;
    string  door,
            key_str,
            isildur,
            anarion,
           *args,
            name = tp->query_real_name();

    if (query_verb() == "unlock")
    {
        if (!arg)
        {
            NF("Unlock what?\n");
            return 0;
        }
        if (sscanf(arg, "%s with %s", door, key_str) < 2)
            door = arg;
        if (member_array(door, door_name) < 0)
            NF("Unlock what?\n");
        else
            NF("There is neither a lock nor a keyhole on the gate!\n");
        return 0;
    }

    if (!lock_status)
    {
        if (open_status)
            NF("The gate is open!\n");
        else
            NF("The gate is not locked!\n");
        return 0;
    }

    NF("Call whom?\n");
    if (!strlen(arg))
        return 0;

    if ( (tp->test_bit("Gondor", MORGUL_GROUP, ANGMAR_STANDARD_BIT)) ||
         (tp->query_prop(BSW_I_FOUND_IT)) )
    {
        NF("The blue glow of the gate remains unchanged.\n");
        return 0;
    }

    arg = LOW(arg);

    if (arg == "castamir")
    {
        NF("An angry voice whispers inside you head: Do not mention the "
          + "name of the usurper again!\n");
        return 0;
    }

    args =  explode(arg, " ");
    if (sizeof(args) > 2)
        arg = implode(args, " ");
    if ((sizeof(args) > 1) && (args[1] != "i" && args[1] != "ii"))
        arg = args[0];

    if (tp->query_prop(BSW_GATE_ISILDUR))
    {
        anarion = LOW(BSW_QUEST_MASTER->query_random_ruler("gondor", name));
        if (arg == anarion)
        {
            tell_room(ENV(TO), BSN("The bluish glow of the gate flares up "
              + "for a short moment, and then it is gone."));
            tp->add_prop(BSW_I_OPENED_GATE, 1);
            tp->remove_prop(BSW_GATE_ISILDUR);
            return 1;
        }
        else
        {
            check_spelling(arg, tp);
            return 0;
        }
    }

    isildur = LOW(BSW_QUEST_MASTER->query_random_ruler("arnor", name));

    if (arg == isildur)
    {
        tp->add_prop(BSW_GATE_ISILDUR, 1);
        NF("The glow of the gate becomes a little stronger.\n");
        tell_room(ENV(TO), "The glow of the gate becomes a little "
          + "stronger.\n", tp);
        return 0;
    }
    else
    {
        check_spelling(arg, tp);
        return 0;
    }

    return 0;
}

string
long_desc()
{
    int     lang = TP->query_skill(SS_LANGUAGE);
    string  desc = "The heavy steel gate has neither a lock nor a keyhole. ",
            stnm;

    if (TO->query_locked())
        desc += "It glows in the dark with a faint bluish aura and you "
          + "can sense powerful magic emanating from it. It feels like "
          + "you probably would not like to be in this room if someone "
          + "should be foolish enough to try to open this door. ";

    switch(lang)
    {
        case  0..19:
            desc += "Etched into it are undecipherable runes.";
            break;
        case 20..34:
            desc += "Etched into it are tengwar. All you can "
              + "decipher are a large tengwar called 'hyarmen' over "
              + "the picture of a rod surrounded by smaller letters "
              + "forming a circle.";
            break;
        case 35..44:
            stnm = BSW_QUEST_MASTER->query_random_ruler("stewards",
                TP->query_real_name());
            desc += "Etched into it is a large 'hyarmen' tengwar over "
              + "the picture of a rod, the symbol of Stewardship. Surrounding "
              + "these two is a circle of smaller letters. You can make out "
              + "these words: ..... "
              + "\"I, "+stnm+", Steward of Gondor, .. ... ..... of Hurin, "
              + ".... .... .... gate built .. ....... the ......... of "
              + ".. House.\"";
            break;
        case 45..54:
            stnm = BSW_QUEST_MASTER->query_random_ruler("stewards", 
                TP->query_real_name());
            desc += "Etched into it is a large 'hyarmen' tengwar, "
              + "which is the first letter of the name 'Hurin'. Below it "
              + "is the picture of a rod, the symbol of Stewardship. "
              + "Surrounding these two is a circle of smaller letters. "
              + "You can make out these words: "
              + "\"I, "+stnm+", Steward of Gondor, .. ... House of Hurin, "
              + ".... .... this gate built to protect the Heirlooms of "
              + ".. House.\"";
            break;
        default:
            stnm = BSW_QUEST_MASTER->query_random_ruler("stewards", 
                TP->query_real_name());
            desc += "Etched into it is a large 'hyarmen' tengwar, "
              + "which is the first letter of the name 'Hurin'. Below it "
              + "is the picture of a rod, the symbol of Stewardship. "
              + "Surrounding these two is a circle of smaller letters. "
              + "You read: "
              + "\"I, "+stnm+", Steward of Gondor, of the House of Hurin, "
              + "have made this gate built to protect the Heirlooms of "
              + "my House.\"";
            break;
    }
    return BSN(desc);
}

void
do_close_door(string mess)
{
    object env;

    env = environment(this_object());
    env->change_my_desc(check_call(closed_desc));
    if (strlen(mess))
	tell_room(env, mess);
    open_status = 0;
    lock_status = 1;
}

