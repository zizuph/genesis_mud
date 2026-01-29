/*
 * /d/Ansalon/guild/kender_occ/npc/storekeeper.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Storekeeper that tells stories.
 *
 * Gwyneth, 1999
 * Modification log:
 * Gwyneth January 2001 - Added storytelling capability
 */
inherit "/std/monster";

#include <const.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "../guild.h"

static string *gIntroducedTo = ({});

/*
 * Function name: story
 * Description  : Tell a story based on a scar
 */
public string
story()
{
    command("kstory");
    return "";
}

public void
create_monster()
{
    set_name("talltale");
    set_race_name("kender");
    set_title("Streamskimmer of Kendermore");
    set_long("This kender seems to be here quite a bit! He must really " + 
        "love listening to stories! His pack seems quite full. Perhaps " + 
        "he might sell you something.\n");
    add_name("shopkeeper");
    set_adj("tanned");
    add_adj("excited");
    set_gender(G_MALE);
    set_scar(254);

    set_stats(({80,100,80,90,90,100}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 75);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_WEP_KNIFE, 50);
    set_alignment(350);
    set_alarm(1.0, 0.0, &command("sit on bench"));
    set_default_answer("What? Would you like to hear a story?\n");
    add_ask(({"story", "tale", "adventure"}), &story());
}

/* Function name : Arm me
 * Description   : Clones, wears and wields misc. items, armours and weapons.
 */
public void
arm_me()
{
    setuid();
    seteuid(getuid(this_object()));
    clone_object(KOBJ + "lollipop")->move(this_object());
    clone_object(KOBJ + "licorice")->move(this_object());
    clone_object(KOBJ + "std_knife")->move(this_object());
    clone_object(KOBJ + "hoopak")->move(this_object());
    clone_object(KOBJ + "leggings")->move(this_object());
    clone_object(KOBJ + "boots")->move(this_object());
    clone_object(KOBJ + "cloak")->move(this_object());
    clone_object(KOBJ + "shirt")->move(this_object());
    clone_object(KGOBJ + "gitem")->move(this_object());

    command("wear all");
    command("wield all");
}

/* Function name : introduce_to_arrival
 * Description   : Introduces to new arrivals
 */
public void
introduce_to_arrival(object who)
{
    if (present(who, environment(this_object())))
    {
        command("introduce myself to " + OB_NAME(who));
        gIntroducedTo += ({ who->query_real_name() });
    }
}

public void
init_living()
{
    ::init_living();

    if (member_array(this_player()->query_real_name(), gIntroducedTo) == -1)
    {
        set_alarm(1.0, 0.0, &introduce_to_arrival(this_player()));
    }
}
