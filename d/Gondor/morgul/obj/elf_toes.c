/*
 * Elf toes for the Red Eye Inn in Minas Morgul.
 *
 * Gwyneth, December 29, 2000
 */
inherit "/std/food";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public int react_elf_alarm;
public int react_ot_alarm;

public void react_ot(object pl);
public void react_elf(object pl);

void
create_food()
{
    set_name(({"toes", "bowl"}));
    set_pname(({"toes", "bowls"}));
    set_pshort("bowls of sauteed elf toes");
    set_short("bowl of sauteed elf toes");
    set_adj("sauteed");
    set_adj("elf");
    set_long("@@long_desc");
    set_amount(450);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 50);
}

public string
long_desc()
{
    string desc = "Deliciously sauteed with rare spices and butter, " +
        "this bowl of elf toes is perfectly cooked!\n";

    if (!interactive(this_player()))
    {
        return "";
    }
    if (this_player()->query_npc())
    {
        return desc;
    }

    if (IS_MORGUL_MAGE(this_player()))
    {
        return desc;
    }
    switch(this_player()->query_race())
    {
    case "goblin":
        return desc;
        break;

    case "elf":
        desc = ("This is a bowl filled with cooked and mutilated elf " +
            "toes! The sight of your own race's mutilated body parts " +
            "makes you puke!\n");
        if (!get_alarm(react_elf_alarm))
            react_elf_alarm = set_alarm(2.0, 0.0, &react_elf(this_player()));
        break;

    default:
        desc = "This is a bowl filled with sauteed elf toes cooked in " +
            "butter and spices.\n";
        if (!get_alarm(react_ot_alarm))
            react_ot_alarm = set_alarm(2.0, 0.0, &react_ot(this_player()));
    }

    return desc;
}

public void
react_elf(object pl)
{
    pl->command("$puke");

    if (environment() == pl) 
    {
        pl->command("$drop elf toes");
    }

    pl->command("$groan");
}

public void
react_ot(object pl)
{
    if (pl->query_alignment() < -200)
    {
        return;
    }

    pl->command("$puke");
}
