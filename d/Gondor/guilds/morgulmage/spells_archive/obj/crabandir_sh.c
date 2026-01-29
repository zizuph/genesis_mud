/*
 *  /d/Gondor/common/guild2/newspells/crabandir_sh.c
 *
 *  A support for the Morgul crabandir spell.
 *  Updated for the generic spell system by Eowul
 */

#include "../../morgulmage.h"

inherit "/std/shadow";

#include <macros.h>
#include <files.h>

private nomask varargs int pass_msg( object from_player );

object spell_object;

public void
attacked_by(object ob)
{
    shadow_who->catch_tell("Sudden pain violently breaks your "
        + "concentration!\n");
    shadow_who->attacked_by(ob);
    spell_object->dispel_effect(ob);
}

void catch_msg(mixed str, object from_player)
{
    if (pass_msg(from_player))
    {
        shadow_who->catch_msg(str, from_player);
    }
}

public void catch_tell(string msg)
{
    if (pass_msg())
    {
        shadow_who->catch_tell(msg);
    }
}

void set_spell_object(object ob)
{
    spell_object = ob;
}

private int source_is_craban(object source)
{
    if (!objectp(source)) return 0;
    return (MASTER_OB(source) == MORGUL_SPELL_OBJ_DIR + "crabandir_npc");
}

/*
 * Function     : pass_msg
 * Description  : It checks whether to pass a message to a mage or not.
 *              : At the moment it passes messages from the invoked craban,
 *              : messages sent by palanquendo and wizards 
 */
private nomask varargs int pass_msg( object from_player )
{
    /* A message sent by a wizard */
    if (objectp(from_player) && interactive(from_player) && 
        SECURITY->query_wiz_level(from_player->query_name()))
    {
            return 1;
    }

    /* A craban is the source of message */
    if (source_is_craban(calling_object(-1)) || source_is_craban(calling_object(-2)))
    {
        return 1;
    }

    /* Message sent by palanquendo or paralyze. */
    string source = calling_program(-1);
    if (strlen(source))
    {
        if ((source == (MORGUL_SPELL_DIR + "palanquendo.c")[1..]) 
            || (source == "std/paralyze.c")
            || (source == "cmd/wiz/apprentice.c"))
        {
            return 1;
        }
    }
    return 0;
}

