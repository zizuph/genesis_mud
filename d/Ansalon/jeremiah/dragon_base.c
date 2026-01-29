/*
 *    dragon_base.c
 *    -------------
 *
 *    Coded.........: 95/11/04
 *    By............: Jeremiah
 *
 *    Latest update.: 95/11/04
 *    By............: Jeremiah
 *
 *    Standard file creating a basic dragon for the DragonLance Domains.
 */

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit AC_FILE
inherit "/std/act/domove";    /* Allows dragon to move.*/
inherit "/std/act/action";    /* Allows dragon to act. */

string d_color,
       d_short_description,
       d_long_description;

int    d_level,
       just_cloned,
       alarm_id;

/*
 *    Prototypes.
 */

void init_dragon();
void create_dragon();
void level_me();


void
create_creature()
{
    set_name("dragon");
    set_race_name("dragon");

    init_dragon();
    create_dragon();

    add_name(d_color + " dragon");
    set_short("@@short_descr");
    set_long("@@long_descr");
    level_me();
}


void
create_dragon() { }


string
short_descr()
{
    if (strlen(d_short_description))
    {
        return d_short_description;
    }

    return "large " + d_color + " dragon";
}


string
long_descr()
{
    if (strlen(d_long_description))
    {
        return d_long_description;
    }

    return "This is a large " + d_color + " dragon.\n";
}


void
level_me()
{
    int l;

    l = 5*d_level;

    set_base_stat(0, 100+2*l+random(l));
    set_base_stat(1, 120+2*l+random(1));
    set_base_stat(2, 100+2*l+random(l));
    set_base_stat(3, 100+2*l+random(l));
    set_base_stat(4, 100+2*l+random(l));
    set_base_stat(5, 100+2*l+random(l));

    set_attack_unarmed(0, 40+l, 40+l, W_IMPALE, 30, "bite");
    set_attack_unarmed(1, 20+l, 10+l, W_BLUDGEON, 10, "right wing");
    set_attack_unarmed(2, 20+l, 10+l, W_BLUDGEON, 10, "left wing");
    set_attack_unarmed(3, 40+l, 30+l, W_SLASH, 25, "right claw");
    set_attack_unarmed(4, 40+l, 30+l, W_SLASH, 25, "left claw");

    set_hitloc_unarmed(0, 50+l, 10, "head");
    set_hitloc_unarmed(1, 40+l, 50, "body");
    set_hitloc_unarmed(2, 40+l, 20, "tail");
    set_hitloc_unarmed(3, 40+l, 10, "right wing");
    set_hitloc_unarmed(4, 40+l, 10, "left wing");

    set_skill(SS_BLIND_COMBAT, 50+l);
    set_skill(SS_DEFENCE,      50+l);
    set_skill(SS_AWARENESS,    50+l);
}


void
set_dragon_level(int level)
{
    d_level = level;

    if (d_level > 10)
    {
        d_level = 10;
    }

    if (d_level < 1)
    {
        d_level = 1;
    }
}


void
set_dragon_color(string color)
{
    if (!(strlen(color)))
    {
        return;
    }

    d_color = color;
}


void
set_dragon_short(string descr)
{
    d_short_description = descr;
}


void
set_dragon_long(string descr)
{
    d_long_description = descr;
}


void
init_dragon()
{
    just_cloned = 1;
    alarm_id = 0;
    d_color = "colorless";
    d_level = 5;
}
