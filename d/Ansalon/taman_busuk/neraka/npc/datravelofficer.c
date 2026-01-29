/*
 * Ashlar, 29 Nov 1998
 * A dragonarmy officer who can summon a dragon for priests to use.
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"

#define SUMMON_DRAGON   NSTD + "summon_dragon";

inherit AM_FILE
inherit SUMMON_DRAGON

static string dragonarmy_division = "blue";
static int dragonarmy_promotions = 2, dragonarmy_subrank = 0;
static string family_name;
static string special_title;
static mixed *gTitles;

mixed npcdefs = ({
    /* Full name, prepend title, adjectives, race, gender, height, weight, appearance, long description */
    ({ "Darthellin Peres of Winterholm", "", 
        "tall blue-eyed", "human", G_MALE, 193, 96, 76, 
        "The most noticeable feature of this man is his piercing blue eyes. " +
        "He is wearing a dark brown leather overcoat, unbuttoned, over a fine " +
        "white silk shirt. A scarf hangs loose over his neck and a scabbard " +
        "at his hip completes the image of a dangerous man, currently at ease, " +
        "but poised to leap at any moment. He is tall and well-built, with " +
        "short-cropped light brown hair.\n",
        /* dragonarmy division, promotions, rank */
        "blue", 2, 3,
        110, 120, 110, 120, 100, 120,
        /*              */
    }),
    
    ({ "Nicholas De Winter", "Black Crow, Storm Commander of the Black Dragonarmy",
        "dark-haired scarred", "human", G_MALE, 181, 76, 45,
        "Long description\n",
        "black", 3, 1,
        125, 130, 128, 140, 120, 145,
    }),

});

void
configure_dragonarmy_npc(object ob)
{
    int i = random(2);
    mixed *defs = npcdefs[i];

    string *names = explode(defs[0], " ");

    ob->set_name(lower_case(names[0]));
    ob->add_name(defs[3]);
    ob->set_guild_title_race(implode(names[1..], " "));
    ob->set_special_title(defs[1]);
    
    ob->set_adj(explode(defs[2]," "));
    ob->set_race(defs[3]);
    ob->set_gender(defs[4]);
    ob->add_prop(CONT_I_HEIGHT, defs[5]);
    ob->add_prop(CONT_I_WEIGHT, defs[6]*1000);

    ob->set_appearance_offset(defs[7]-50);
    ob->set_long(defs[8]);

    ob->set_dragonarmy_division(defs[9]);
    ob->set_dragonarmy_promotions(defs[10]);
    ob->set_dragonarmy_subrank(defs[11]);

    for (i = SS_STR; i <= SS_DIS; i++)
    {
        ob->set_base_stat(i, defs[12+i-SS_STR]);
    }
}

varargs void
arm_me(int level)
{
    string *arm = ({ NWEP + "scimitar", NARM + "oplate",
        NARM + "ocape" });
    object tmp;
    int i;

    setuid();
    seteuid(getuid(this_object()));
    for (i = 0; i < sizeof(arm); i++)
    {
        tmp = clone_object(arm[i]);

	    if (tmp->query_prop(OBJ_I_COLORABLE))
	        tmp->set_color(this_object()->query_dragonarmy_division());
	    tmp->move(TO);
    }

    command("wield all");
    command("wear all");
}

void
create_krynn_monster()
{
    configure_dragonarmy_npc(this_object());
    set_introduce(1);
}

int
do_summon_dragon()
{
    return summon_dragonsteed(this_object(), 0);
}

/*
 * Functions to imitate a dragonarmy guild member.
 */
void
set_dragonarmy_division(string div)
{
    dragonarmy_division = div;

    switch(div)
    {
        case "blue":
            gTitles = BLUE_TITLES;
            break;
        case "red":
            gTitles = RED_TITLES;
            break;
        default:
            gTitles = 0;
    }
}

string
query_dragonarmy_division() { return dragonarmy_division; }

void
set_dragonarmy_promotions(int prom) { dragonarmy_promotions = prom; }

int
query_dragonarmy_promotions() { return dragonarmy_promotions; }

int
query_dragonarmy_occ_member() { return 1; }

void
set_dragonarmy_subrank(int sr) { dragonarmy_subrank = sr; }

int
query_dragonarmy_subrank() { return dragonarmy_subrank; }

void
set_guild_title_race(string name) { family_name = name; }

string
query_guild_title_race() { return family_name; }

int
query_guild_family_name() { return 1; }

string
query_guild_title_occ()
{
    string title;
    int rank = query_dragonarmy_promotions();
    int subrank = query_dragonarmy_subrank();

    if (special_title != "")
        return special_title;

    if (!pointerp(gTitles))
        title = "Lieutenant";
    else
        title = gTitles[rank][subrank];

    if(rank == 4)
	    return title;
    else
	    return title+" of the "+C(query_dragonarmy_division())+" Dragonarmy";
}

void
set_special_title(string title) { special_title = title; }

string
query_special_title() { return special_title; }

