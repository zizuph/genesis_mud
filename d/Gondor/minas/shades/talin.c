/* A standard member of the Shades */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/private/gondor_admin.h"
#include "/d/Gondor/defs.h"

public void
create_gondor_monster()
{
    set_name("talin");
    set_living_name("talin");
    add_name(({ "man", "thief", "shade", "assassin" }));
    set_race_name("human");
    set_title("Black Member of the Shades");
    set_short("slender dark-robed man");
    set_long("The slender man is clad in black clothes, and he is wearing\n"+
      "a cloak over his shoulders. Grey, narrow eyes follow you\n"+
      "closely and suspiciously when you move around.\n");
    set_alignment(-250);

    default_config_npc(97);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_WEP_KNIFE, 95);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_OPEN_LOCK, 80);
    set_skill(SS_PICK_POCKET, 80);
    set_skill(SS_ACROBAT, 80);
    set_skill(SS_FR_TRAP, 80);
    set_skill(SS_SNEAK, 90);
    set_skill(SS_HIDE, 90);
    set_skill(SS_BACKSTAB, 100);
    set_skill(SS_CLIMB, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_TRADING, 60);
    set_skill(SS_APPR_VAL, 80);
    set_skill(SS_APPR_OBJ, 80);

    set_act_time(10);
    add_act("peek all");
    add_act("snicker");
    add_act("chuckle dem");
    set_cchat_time(7);
    add_cchat("You won't beat the Shades!");
    add_cchat("Give me all your loot, grovel on your knees, and perhaps I'll "+
        "let you live.");
    add_cchat("This is only the beginning of the Shades!");
    add_cchat("I hope you enjoy shopping at Poisons-R-Us");
    add_cchat("Give Death my regards, perhaps he will use his hatch on you!");

    set_equipment( ({ SHADES_DIR + "obj/chest_key",
		      SHADES_DIR + "obj/shadesword",
		      SHADES_DIR + "obj/daggert",
		      SHADES_DIR + "obj/blackcloak",
		      SHADES_DIR + "obj/btunic",
		      SHADES_DIR + "obj/btrousers",
		      SHADES_DIR + "obj/bgloves",
		  }) );
    TELL_ADMIN("[Talin, the Shade, clone at " + ctime(time()) + "]");

}

public void
add_introduced(string who)
{
    if (objectp(find_player(who)))
	set_alarm(4.0, 0.0, &command("introduce me to " + who));
}

/*
 * Function:    query_presentation
 * Description: Gives a presentation of the living in one line. Including
 *              Name, Race, Guild titles, Alignment and Experience level
 *              This should only be displayed to met players.
 *              E.g.: "Fatty the donut-fan, wizard, male gnome (eating)"
 * Returns:     The presentation string
 */
public string
query_presentation()
{
    string a, b, c;

    a = this_object()->query_title();

    return query_name() + ", the" +
        (strlen(a) ? (" " + a + ",") : "") +
        (strlen(b) ? (" " + b + ",") : "") + " " +
        this_object()->query_gender_string() + " " +
        this_object()->query_race_name() +
        (strlen(c) ? (" (" + c + ")") : "");
}

int query_knight_prestige() { return 600; }

void
attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("[Talin, the Shade, attacked by " + ob->query_cap_name() + "("+ob->query_average_stat()+") at " + ctime(time()) + "]");
}
