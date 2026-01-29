#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDCAPTAIN;

int intro = 0;

void
create_captain()
{
    ::create_captain();
    set_name("sennig");
    add_name("captain");
    set_living_name("sennig");
    set_race_name("gnome");
    add_adj("charcoal-cloaked");
    add_adj("tall");

    set_stats(({ 60, 130, 90, 180, 90, 100 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE, 100);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    heal_hp(10000);

    set_title("the Bandi-Merc, Surreptitious Engineer of Airborne Secre-craft,"
        + " and Captain of the Omembo");

    set_act_time(15);
    add_act("emote folds his arms beneath his charcoal cloak and stares into "
        + "the horizon.");
    add_act("emote grins with a malignant hunger.");
    add_act("asay sly This ship is unlike any in the realms. The power and "
        + "glory is mine.");
    add_act("asay slow No, I do not blur my words together unintelligibly. "
        + "Not all gnomes speak Common like addle-minded incompetents. I "
        + "studied with the Aesthetics among others.");
    add_act("emote scoffs at cities that are not Palanthas.");
    add_act("asay vora There is no greater city than Palanthas and no greater "
        + "way to reach it than by air aboard the Omembo.");
  
    add_ask(({SHIP_NAME, "omembo", "ship"}), "The captain says: The Omembo is "
        + "my ship and mine alone! The power of air is known to me and no "
        + "others.\n");
    add_ask(({"bandimerc", "bandi-merc"}), "The captain says: A Bandi-merc "
        + "is of no concern to you, but you had best never face one alone "
        + "in the shadows of night when no one can hear your screams but the "
        + "dying who have gone before you.\n");
    add_ask(({"engineer", "secrecraft", "secre-craft"}), "The captain scoffs "
        + "with a whisper: You'll likely never learn the powers of the air, "
        + "so sit back and enjoy the flight.\n");

    trig_new("%w 'introduces' %s", "react_introduce");
  
}

string
query_my_title()
{
    return "the Bandi-Merc, Surreptitious Engineer of Airborne Secre-craft, "
        + "and Captain of the Omembo";
}

void
react_introduce(string person,string who)
{
    if (!intro)
    {
        intro = set_alarm(1.0, 0.0, "introduce_me");
    }
}

void
introduce_me()
{
    tell_room(ENVX(TO),QCTNAME(TO) + " introduces himself as:\n" +
        "Sennig " + query_my_title() + ", male gnome.\n");
    FILTER_LIVE(all_inventory(ENVX(TO)))->add_introduced("sennig");
    set_alarm(1.0, 0.0, "reset_introduce");
}

void
reset_introduce()
{
      intro = 0;
}
